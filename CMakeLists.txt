project(QTCUBE)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(PythonInterp 3 REQUIRED)
set(qtcube_MAJOR_VERSION 1)
set(qtcube_MINOR_VERSION 2)
set(qtcube_VERSION_STRING ${qtcuber_MAJOR_VERSION}.${qtcube_MINOR_VERSION})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  message(
    SEND_ERROR
      "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler."
    )
endif()

enable_language(CXX)
find_package(TBB REQUIRED)
find_library(LIBTBB tbb REQUIRED)

if(NOT TARGET genericCpp)
  execute_process(COMMAND git submodule update --init --recursive --
                          external/genericIO
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  add_subdirectory(external/genericIO)
  include_directories(${CMAKE_CURRENT_BINARY_DIR}/external/genericIO)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/genericIO/cpp)
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/genericIO/external/sepVector/lib)
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/genericIO/external/sepVector/external/hypercube/lib
    )
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/genericIO/external/buffers/external/json
    )
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/genericIO/external/buffers/lib
    )
endif(NOT TARGET genericCpp)

configure_file("${PROJECT_SOURCE_DIR}/Sep_cube.in"
               "${PROJECT_BINARY_DIR}/Sep_cube")

install(PROGRAMS ${PROJECT_BINARY_DIR}/Sep_cube DESTINATION bin)

find_package(Qt5
             COMPONENTS Core
                        Widgets
                        Multimedia
                        Gui
                        PrintSupport
                        REQUIRED)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -fPIC")

# The Qt5Widgets_INCLUDES also includes the include directories for dependencies
# QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS} ${Qt5Gui_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration without
# -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} ${CMAKE_CXX_FLAGS}")

add_subdirectory(base)
add_subdirectory(gui)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gui
                    ${CMAKE_CURRENT_SOURCE_DIR}/base)

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(RESOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/qt_cube.qrc)

# generate rules for building source files from the resources
qt5_add_resources(RESOURCE_ADDED ${RESOURCE})
add_executable(qt_cube main.cpp ${RESOURCE_ADDED})
set_property(TARGET qt_cube PROPERTY LINKER_LANGUAGE CXX)
target_link_libraries(qt_cube gui)
target_link_libraries(qt_cube base)
target_link_libraries(qt_cube
                      genericCpp
                      buffers
                      ${GENERIC_EXPORT_LIBS}
                      hypercube
                      ${LIBTBB})

target_link_libraries(qt_cube Qt5::Widgets Qt5::PrintSupport)
target_link_libraries(qt_cube ${LIBTBB})

install(TARGETS qt_cube DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${qtcube_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${qtcube_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "qtcube")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)
