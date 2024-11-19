
cmake_minimum_required(VERSION 3.8)
project(ExampleG4)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
add_definitions(-DTOOLS_USE_NATIVE_MPI) 

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})

add_executable(ExampleG4 ExampleG4.cc ${sources} ${headers})

target_link_libraries(ExampleG4 ${Geant4_LIBRARIES})
set(ExampleG4_SCRIPTS
  run.mac
  vis.mac
  )

foreach(_script ${ExampleG4_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
install(TARGETS ExampleG4 DESTINATION bin)
