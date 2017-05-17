cmake_minimum_required(VERSION 2.8)

Project(CSC621-Project)

# Include the ITK packages
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Create the DicomSeries to mha(meta image files)
add_executable(ImageProcessing ImageProcessing.cpp DicomSeriesReadImageWrite2.cxx ImageReadImageSeriesWrite.cxx WatershedSegmentation2.cxx)
target_link_libraries(ImageProcessing ${ITK_LIBRARIES})

# Create Hello World application to test for proper ITK installation
add_executable(HelloWorld main.cpp)
target_link_libraries(HelloWorld ${ITK_LIBRARIES})

if(BUILD_TESTING)
  add_subdirectory(test)
endif()