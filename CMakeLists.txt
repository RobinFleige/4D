
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

        lib/DataType/CriticalPoint.cpp
        lib/DataType/ParameterDependentVectorField.cpp
        lib/DataType/Point.cpp
        lib/DataType/Vector.cpp
        lib/DataType/VectorField.cpp

        lib/DataTypeFilter/GetPointsSet.cpp

        lib/Source/PointSource.cpp
        lib/Source/VectorFieldSource.cpp

        lib/Filter/CalculateBifurcationPoints.cpp
        lib/Filter/CalculateCriticalPoints.cpp
        lib/Filter/CalculateFFField.cpp
        lib/Filter/DrawPointsOnImage.cpp
        lib/Filter/LIC.cpp
        lib/Filter/PointSetSubspace.cpp
        lib/Filter/PointSetToScalarField.cpp
        lib/Filter/Subspace.cpp
        lib/DataTypeFilter/GetVectorField.cpp
        lib/Filter/VectorFieldToImageData.cpp

        lib/Renderer/DoubleImageRenderer2D.cpp
        lib/Renderer/ImageRenderer2D.cpp
        lib/Renderer/ImageRenderer3D.cpp
        lib/Renderer/ImageRenderer4D.cpp
        )

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

