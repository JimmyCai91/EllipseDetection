%  modified from .Martin Simonovsky.  by yuanpu  to make it robust to local redundant
%  detections
%   yuanpu xie , 2014 4 4.

function bestFits = ellipseDetection(img, params)
% ellipseDetection: Ellipse detection

% Overview:
% --------
% Fits an ellipse by examining all possible major axes (all pairs of points) and
% getting the minor axis using Hough transform. The algorithm complexity depends on 
% the number of valid non-zero points, therefore it is beneficial to provide as many 
% restrictions in the "params" input arguments as possible if there is any prior
% knowledge about the problem.
%
% The code is reasonably fast due to (optional) randomization and full code vectorization.
% However, as the algorithm needs to compute pairwise point distances, it can be quite memory
% intensive. If you get out of memory errors, either downsample the input image or somehow 
% decrease the number of non-zero points in it.
% It can deal with big amount of noise but can have severe problem with occlusions (major axis
% end points need to be visible)
%
% Input arguments:
% --------    
% img
%   - One-channel input image (greyscale or binary).
% params
%   - Parameters of the algorithm:
%       minMajorAxis: Minimal length of major axis accepted.
%       maxMajorAxis: Maximal length of major axis accepted.
%        rotation, rotationSpan: Specification of restriction on the angle of the major axis in degrees.
%                                If rotationSpan is in (0,90), only angles within [rotation-rotationSpan,
%                               rotation+rotationSpan] are accepted.
%       minAspectRatio: Minimal aspect ratio of an ellipse (in (0,1))
%       randomize: Subsampling of all possible point pairs. Instead of examining all N*N pairs, runs
%                  only on N*randomize pairs. If 0, randomization is turned off.
%       numBest: Top numBest to return
%       uniformWeights: Used to prefer some points over others. If false, accumulator points are weighted 
%                       by their grey intensity in the image. If true, the input image is regarded as binary.
%       smoothStddev: In order to provide more stability of the solution, the accumulator is convolved with
%                     a gaussian kernel. This parameter specifies its standard deviation in pixels.
%
% Return value:
% --------    
% Returns a matrix of best fits. Each row (there are params.numBest of them) contains six elements:
% [x0 y0 a b alpha score] being the center of the ellipse, its major and minor axis, its angle in degrees and score.
%
% Based on:
% --------    
% - "A New Efficient Ellipse Detection Method" (Yonghong Xie Qiang , Qiang Ji / 2002)
% - random subsampling inspired by "Randomized Hough Transform for Ellipse Detection with Result Clustering"
%   (CA Basca, M Talos, R Brad / 2005)
%

% --------    
%
% Redistribution and use in source and binary forms, with or without 
% modification, are permitted provided that the following conditions are 
% met:
% 
%     * Redistributions of source code must retain the above copyright 
%       notice, this list of conditions and the following disclaimer.
%     * Redistributions in binary form must reproduce the above copyright 
%       notice, this list of conditions and the following disclaimer in 
%       the documentation and/or other materials provided with the distribution
%       


    % default values
    if nargin==1; params=[]; end
    % - parameters to contrain the search
    if ~isfield(params,'minMajorAxis');     params.minMajorAxis = 10; end
     if ~isfield(params,'maxMajorAxis');     params.maxMajorAxis = 50; end
    if ~isfield(params,'rotation');            params.rotation = 0; end
    if ~isfield(params,'rotationSpan');        params.rotationSpan = 0; end
    if ~isfield(params,'minAspectRatio');    params.minAspectRatio = 0.04; end
    if ~isfield(params,'randomize');        params.randomize = 10; end
    % - others
    if ~isfield(params,'numBest');            params.numBest = 61; end
    if ~isfield(params,'uniformWeights');   params.uniformWeights = true; end
    if ~isfield(params,'smoothStddev');        params.smoothStddev = 4; end
    numEllipse = 0;
    disThresh = 3.5*3.5;
    eps = 0.0001;
    bestFits = zeros(params.numBest,6);
    params.rotationSpan = min(params.rotationSpan, 90);    
    H = fspecial('gaussian', [params.smoothStddev*6 1], params.smoothStddev);

    [Y,X]=find(img);
    Y = single(Y); X = single(X);
    N = length(Y);
    
    fprintf('Possible major axes: %d * %d = %d\n', N, N, N*N);

    % compute pairwise distances between points (memory intensive!) and filter
    % TODO: do this block-wise, just appending the filtered results (I,J)
    distsSq = bsxfun(@minus,X,X').^2 + bsxfun(@minus,Y,Y').^2;
    [I,J] = find(distsSq>=params.minMajorAxis^2 & distsSq<=params.maxMajorAxis^2);
    idx = I<J;
    I = uint32(I(idx)); J = uint32(J(idx));
    
    fprintf('..after distance constraint: %d\n', length(I));
    
    % compute pairwise angles and filter
    if params.rotationSpan>0
        tangents = (Y(I)-Y(J)) ./ (X(I)-X(J));
        tanLo = tand(params.rotation-params.rotationSpan);
        tanHi = tand(params.rotation+params.rotationSpan);    
        if tanLo<tanHi
            idx = tangents > tanLo & tangents < tanHi;
        else
            idx = tangents > tanLo | tangents < tanHi;
        end
        I = I(idx); J = J(idx);
        fprintf('..after angular constraint: %d\n', length(I));
    else
        fprintf('..angular constraint not used\n');
    end
    
    npairs = length(I);

    % compute random choice and filter
    if params.randomize>0
        perm = randperm(npairs);
        pairSubset = perm(1:min(npairs,N*params.randomize));
        clear perm;
        fprintf('..after randomization: %d\n', length(pairSubset));
    else
        pairSubset = 1:npairs;
    end
    
    % check out all hypotheses
    for p=pairSubset
        x1=X(I(p)); y1=Y(I(p));
        x2=X(J(p)); y2=Y(J(p));
        
        %compute center & major axis
        x0=(x1+x2)/2; y0=(y1+y2)/2;
        aSq = distsSq(I(p),J(p))/4;
        thirdPtDistsSq = (X-x0).^2 + (Y-y0).^2;
        K = thirdPtDistsSq <= aSq; % (otherwise the formulae in paper do not work)
    %% The following is changed to move redundant detection --yuanpu xie
        %get minor ax propositions for all other points
        fSq = (X(K)-x2).^2 + (Y(K)-y2).^2;
        cosTau = (aSq + thirdPtDistsSq(K) - fSq) ./ (2*sqrt(aSq*thirdPtDistsSq(K)));
        cosTau = min(1,max(-1,cosTau)); %inexact float arithmetic?!
        sinTauSq = 1 - cosTau.^2;
        b = sqrt( (aSq * thirdPtDistsSq(K) .* sinTauSq) ./ (aSq - thirdPtDistsSq(K) .* cosTau.^2 + eps) );

        %proper bins for b
        idxs = ceil(b+eps);
        
        if params.uniformWeights
            weights = 1;
        else
            weights = img(sub2ind(size(img),Y(K),X(K)));
        end
        accumulator = accumarray(idxs, weights, [params.maxMajorAxis 1]);

        %a bit of smoothing and finding the most busy bin
        accumulator = conv(accumulator,H,'same');
        accumulator(1:ceil(sqrt(aSq)*params.minAspectRatio)) = 0;
        [score, idx] = max(accumulator);

        %keeping only the params.numBest best hypothesis (no non-maxima suppresion)
        if (bestFits(end,end) <= score)
            Xr = bestFits(1:numEllipse,1);
            Yc = bestFits(1:numEllipse,2);
            fSq = (Xr-x0).^2 + (Yc-y0).^2;
            a = sqrt(fSq) < disThresh;
            [lm,ln] = size(find(a == 1));
            if(lm*ln ==0) %not in a near distance
            bestFits(end,:) = [x0 y0 sqrt(aSq) idx atand((y1-y2)/(x1-x2)) score];
            numEllipse = min(params.numBest, numEllipse + 1);
            if params.numBest>1
                [~,si]=sort(bestFits(:,end),'descend');
                bestFits = bestFits(si,:);
            end
            
            else % find similar results
            [row, col] = find(a == 1);
            if (length(row) >= 2)
            row;
            end
            indxofbad = 1;
            numreduce = 0;
            for idxrow = 1 : 1 : length(row)
                if bestFits(row(idxrow),end) <= score
                      bestFits(row(idxrow),:) = [0 0 0 0 0 0]; 
                      indxofbad = idxrow;
                      numreduce = numreduce +1;
                end
            end
            if (numreduce ~= 0 )
            bestFits(row(indxofbad),:) = [x0 y0 sqrt(aSq) idx atand((y1-y2)/(x1-x2)) score];
            numEllipse = numEllipse - numreduce +1;
            
            else
                
            end
            
            if params.numBest>1
                [~,si]=sort(bestFits(:,end),'descend');
                bestFits = bestFits(si,:);
            end
                
        end
        end
    end
end
