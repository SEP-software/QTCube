cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(qtcuber_MAJOR_VERSION LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SUPPORT_LIBRARIES_BUILD ON)
set(BUILD_PYTHON OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE True)
find_package(PythonInterp 3 REQUIRED)
set(qtcube_MAJOR_VERSION 1)
set(qtcube_MINOR_VERSION 2)
set(qtcube_VERSION_STRING ${qtcuber_MAJOR_VERSION}.${qtcube_MINOR_VERSION})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
  include_directories(${CMAKE_CURRENT_BINARY_DIR})


find_package(TBB REQUIRED)
find_library(LIBTBB tbb REQUIRED)

if(NOT TARGET displaySlice)
  set(BUILD_PYTHON OFF)
  set(BUILD_EXECUTABLES OFF)

  execute_process(COMMAND git submodule update --init --recursive --
                          external/displayslice
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  add_subdirectory(external/displayslice)
 
endif(NOT TARGET displaySlice)

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

add_subdirectory(gui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gui)

find_package(Boost 1.40 COMPONENTS program_options unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already (but later on when
# installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH which point to directories
# outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/qt_cube.qrc)

# generate rules for building source files from the resources
qt5_add_resources(RESOURCE_ADDED ${RESOURCE})
add_executable(qt_cube main.cpp ${RESOURCE_ADDED})
set_property(TARGET qt_cube PROPERTY LINKER_LANGUAGE CXX)
target_link_libraries(qt_cube gui)

target_link_libraries(qt_cube Qt5::Widgets  Qt5::PrintSupport)

install(TARGETS qt_cube DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${qtcube_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${qtcube_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "qtcube")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)
