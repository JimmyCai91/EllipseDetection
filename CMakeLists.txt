cmake_minimum_required(VERSION 2.8)
project(EllipseDetection)

# The version number.
set(EllipseDetection_VERSION_MAJOR 1)
set(EllipseDetection_VERSION_MINOR 0)

# GDB Debug
set(CMAKE_MAKE_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

# add the binary tree to the search path for include files
#  so that we will find ...
include_directories("${PROJECT_BINARY_DIR}")

# add the utils library
include_directories("${PROJECT_BINARY_DIR}/utils")
  add_subdirectory(utils)
  set(EXTRA_LIBS ${EXTRA_LIBS} utils)

# add opencv package
find_package(OpenCV REQUIRED)
# add_executable(EllipseDetection fitellipse.cpp)
add_executable(EllipseDetection EllipseDetection.cxx)
target_link_libraries(EllipseDetection ${OpenCV_LIBS} ${EXTRA_LIBS})
