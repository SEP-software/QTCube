project(QTCUBE)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)


set(qtcube_MAJOR_VERSION 1)
set(qtcube_MINOR_VERSION 2)
set(qtcube_VERSION_STRING
  ${qtcuber_MAJOR_VERSION}.${qtcube_MINOR_VERSION})

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O3")
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
        message(SEND_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

enable_language(CXX)
find_library(LIBTBB tbb REQUIRED)

FIND_PACKAGE(genericIO)
FIND_PACKAGE(sepVector)
FIND_PACKAGE(hypercube)
if(genericIO_FOUND)
  message("Found genericIO")
  INCLUDE_DIRECTORIES(${genericIO_DIRNAME_include})
  INCLUDE_DIRECTORIES(${hypercube_DIRNAME_include})
  INCLUDE_DIRECTORIES(${sepVector_DIRNAME_include})
  link_directories(${hypercube_DIRNAME_lib} ${genericIO_DIRNAME_lib} ${sepVector_DIRNAME_lib})
else(genericIO_FOUND)
  message("Unable to find genericIO")
  execute_process(COMMAND git submodule update --init --recursive  -- external/genericIO
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  add_subdirectory(external/genericIO)
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/external/genericIO)
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/external/genericIO/cpp)
  if(sepVector_FOUND)
    message("Found sepVector")
    INCLUDE_DIRECTORIES(${hypercube_DIRNAME_include})
    INCLUDE_DIRECTORIES(${sepVector_DIRNAME_include})
    link_directories(${hypercube_DIRNAME_lib} ${sepVector_DIRNAME_lib})
  else(sepVector_FOUND)
    message("Did not find sepVector")
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/external/genericIO/external/sepVector/lib)
    if(hypercube_FOUND)
      message("Found hypercube")
      INCLUDE_DIRECTORIES(${hypercube_DIRNAME_include})
      link_directories(${hypercube_DIRNAME_lib})
    else(hypercube_FOUND)
      message("Did not find hypercube")
      INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/external/genericIO/external/sepVector/external/hypercube/lib)
    endif(hypercube_FOUND)
  endif(sepVector_FOUND)
endif(genericIO_FOUND)





configure_file (
  "${PROJECT_SOURCE_DIR}/Sep_cube.in"
  "${PROJECT_BINARY_DIR}/Sep_cube"
  )

install(PROGRAMS ${PROJECT_BINARY_DIR}/Sep_cube  
 
 DESTINATION bin
)

add_subdirectory(base)
add_subdirectory(gui)



FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gui)
link_directories(${CURRENT_BINARY_DIR}/base ${CURRENT_BINARY_DIR}/gui)

SET(QtApp_RCCS qt_cube.qrc)

# generate rules for building source files from the resources
QT4_ADD_RESOURCES(QtApp_RCC_SRCS ${QtApp_RCCS})


ADD_EXECUTABLE(qt_cube main.cpp ${QtApp_RCC_SRCS} )
set_property(TARGET qt_cube PROPERTY LINKER_LANGUAGE CXX)
TARGET_LINK_LIBRARIES(qt_cube gui)
TARGET_LINK_LIBRARIES(qt_cube base)
TARGET_LINK_LIBRARIES(qt_cube genericCpp ${GENERIC_EXPORT_LIBS} hypercube ${LIBTBB})


get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

target_link_libraries(qt_cube Qt4::QtGui Qt4::QtXml)
TARGET_LINK_LIBRARIES(qt_cube ${LIBTBB})

install(TARGETS qt_cube  
 
 DESTINATION bin
)



include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${qtcube_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${qtcube_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "qtcube")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)

