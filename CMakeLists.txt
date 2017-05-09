cmake_minimum_required(VERSION 3.8)

Project(CSC621-Project)

# Create the DicomSeries to mha(meta image files)
add_executable(DicomSeriesReadImageWrite2 DicomSeriesReadImageWrite2.cxx)
target_link_libraries(DicomSeriesReadImageWrite2  ${ITK_LIBRARIES})

# Include the ITK packages
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})