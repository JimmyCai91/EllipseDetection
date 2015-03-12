cmake_minimum_required(VERSION 2.8)
project(EllipseDetection)

# The version number.
set(EllipseDetection_VERSION_MAJOR 1)
set(EllipseDetection_VERSION_MINOR 0)

# GDB Debug
set(CMAKE_MAKE_TYPE Debug)

find_package(OpenCV REQUIRED)
# add_executable(EllipseDetection fitellipse.cpp)
add_executable(EllipseDetection EllipseDetection.cxx)
target_link_libraries(EllipseDetection ${OpenCV_LIBS})
