cmake_minimum_required(VERSION 2.8)

Project(CSC621-Project)

# Include the ITK packages
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

# Create the DicomSeries to mha(meta image files)
add_executable(DicomSeriesReadImageWrite2 DicomSeriesReadImageWrite2.cxx)
target_link_libraries(DicomSeriesReadImageWrite2  ${ITK_LIBRARIES})

# Create Hello World application to test for proper ITK installation
add_executable(HelloWorld main.cpp)
target_link_libraries(HelloWorld ${ITK_LIBRARIES})

# Create BSpline Registration
add_executable(BSpline-Registration BSpline-Registration.cxx)
target_link_libraries(BSpline-Registration ${ITK_LIBRARIES})

# Create Demon's Registration Algorithm
add_executable(Demons-Registration Demons-Registration.cxx)
target_link_libraries(Demons-Registration ${ITK_LIBRARIES})