Project(CSC621-Project)

# Create the DicomSeries to mha(meta image files)
add_executable(DicomSeriesReadImageWrite2 DicomSeriesReadImageWrite2.cxx)
target_link_libraries(DicomSeriesReadImageWrite2  ${ITK_LIBRARIES})

# Include the ITK packages
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

target_link_libraries(Heart-Disease ITKCommon)

# Include the VTK packages
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

if(VTK_LIBRARIES)
  target_link_libraries(Heart-Disease ${VKT_LIBRARIES})
else()
  target_link_libraries(Heart-Disease vtkHybrid vtkWidgets)
endif()

# Create an executable
add_executable(Heart-Disease main.cpp)
