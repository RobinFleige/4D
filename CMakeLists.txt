
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

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
        ImagingCore
  IOXML
  REQUIRED
)

message(STATUS "VTK_VERSION: ${VTK_VERSION}")


# Main library; can be used by e.g. executables
add_library(prototype_lib)
target_compile_features(prototype_lib PUBLIC cxx_std_14)
target_sources(prototype_lib
        PRIVATE lib/4DSource.cxx
        )
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
target_sources(Prototype PRIVATE src/Main.cxx )
target_link_libraries(
        Prototype ${VTK_LIBRARIES} prototype_lib
)
target_include_directories(Prototype PUBLIC ${CMAKE_SOURCE_DIR}/src)

vtk_module_autoinit(TARGETS Prototype MODULES ${VTK_LIBRARIES})

