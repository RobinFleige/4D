
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(Prototype)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  CommonTransforms
  FiltersCore
  FiltersGeneral
  FiltersModeling
  FiltersSources
  InteractionStyle
  RenderingAnnotation
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  RenderingLICOpenGL2
  InteractionWidgets
        ImagingCore
        IOLegacy
  IOXML
  REQUIRED
)

message(STATUS "VTK_VERSION: ${VTK_VERSION}")


# Main library; can be used by e.g. executables
add_library(prototype_lib STATIC )
target_sources(prototype_lib PRIVATE
        lib/Slider/Slider.cpp
        lib/Filter/LIC.cpp
        lib/Renderer/ImageRenderer.cpp
        lib/Source/VectorFieldSource.cpp
        lib/Filter/Subspace.cpp
        lib/Filter/CriticalPointsSet.cpp
        lib/Filter/DrawPointsOnImage.cpp
        lib/Filter/PointSetSubspace.cpp
        lib/Filter/Subspace4D2D.cpp
        lib/Filter/PointSetToScalarField.cpp
        lib/DataTypeFilter/GetPointsSet.cpp
        lib/Filter/VectorFieldToImageData.cpp
        lib/Filter/FFF.cpp
        lib/Source/PointSource.cpp
        lib/Source/TestSource.cpp
        lib/DataType/VectorField4D.cpp
        lib/DataType/VectorField2D.cpp
        lib/DataType/CriticalPoint.cpp
        lib/DataType/BifurcationPoint.cpp
        lib/DataType/Point.cpp
        lib/DataType/FeatureFlowField.cpp
        lib/DataType/ProcessObject.cpp
        lib/Renderer/DoubleImageRenderer.cpp
        lib/Renderer/ImageRenderer.cpp
        lib/Renderer/ImageRenderer3D.cpp
        lib/Filter/PointSetTo3D.cpp)

target_compile_features(prototype_lib PUBLIC cxx_std_17)

target_link_libraries(
        prototype_lib PRIVATE ${VTK_LIBRARIES}
)
target_include_directories(
        prototype_lib
        PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/lib>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
vtk_module_autoinit(
        TARGETS prototype_lib MODULES ${VTK_LIBRARIES}
)


# Executable for demonstration purposes
add_executable(Prototype)
target_sources(Prototype PRIVATE src/Main.cxx)
target_link_libraries(
        Prototype PRIVATE ${VTK_LIBRARIES} prototype_lib
)
target_include_directories(Prototype PRIVATE ${CMAKE_SOURCE_DIR}/src)

vtk_module_autoinit(TARGETS Prototype MODULES ${VTK_LIBRARIES})

