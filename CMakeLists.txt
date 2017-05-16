cmake_minimum_required(VERSION 2.8)

Project(CSC621-Project)

# Include the ITK packages
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Create the DicomSeries to mha(meta image files)
add_executable(Final Final.cpp DicomSeriesReadImageWrite2.cxx ImageReadImageSeriesWrite.cxx)
target_link_libraries(Final ${ITK_LIBRARIES})

# Create Hello World application to test for proper ITK installation
add_executable(HelloWorld main.cpp)
target_link_libraries(HelloWorld ${ITK_LIBRARIES})

# Create WatershedSegmentation 1
if (ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

add_executable(WatershedSegmentation2 WatershedSegmentation2.cxx )
target_link_libraries(WatershedSegmentation2 ${ITK_LIBRARIES})

if(BUILD_TESTING)
  add_subdirectory(test)
endif()