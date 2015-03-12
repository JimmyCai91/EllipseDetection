% load image
Img = imread('../data/bin_im_for_count14.bmp');

% edge detection
edge_Img = edge(Img, 'canny', [0.1, 0.3]);

% ellipse detection
bsetFits = ellipseDetection(edge_Img);

