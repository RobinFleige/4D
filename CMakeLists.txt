
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
        lib/Slider.cpp
        lib/LIC.cpp
        lib/ImageRenderer.cpp
        lib/Source4D.cpp
        lib/Subspace.cpp
        lib/CriticalPointsTrivial.cpp
        lib/CriticalPointsSet.cpp
        lib/CriticalPointsSubdivide.cpp
        lib/DrawPointsOnImage.cpp
        lib/PointSetToScalarField.cpp
        lib/StrucutredGridToImage.cpp
        lib/StructuredGridnD.cpp
        lib/MultiparameterDependentStructuredGridnD.cpp
        lib/PointSource.cpp
        lib/DoubleImageRenderer.cpp
        lib/PointSource.h
        lib/PointSetSubspace.cpp
        lib/PointSetSubspace.h
        lib/FeatureFlowField4D.cpp
        lib/FeatureFlowField4D.h)

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

