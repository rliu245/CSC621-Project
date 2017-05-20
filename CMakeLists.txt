cmake_minimum_required(VERSION 2.8)

Project(CSC621-Project)

# Include the ITK packages
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Create the Image Processing application
add_executable(ImageProcessing ImageProcessing.cpp DicomSeriesReadImageWrite2.cxx ImageReadImageSeriesWrite.cxx WatershedSegmentation2.cxx BSplineRegistration.cxx)
target_link_libraries(ImageProcessing ${ITK_LIBRARIES})