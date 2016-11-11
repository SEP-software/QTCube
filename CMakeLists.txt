project(QTCUBE)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)




  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -O3")
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
        message(SEND_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

enable_language(CXX)



find_path(SEPINCDIR seplib.h HINTS ENV SEP PATH_SUFFIXES PATHS  include /usr/local/SEP /usr/local/SEP/SEP8.0 /opt/SEP/opt/SEP/SEP8.0)
find_library(LIBSEP sep HINTS ENV SEP PATH_SUFFIXES lib PATHS  /usr/local/SEP /usr/local/SEP/SEP8.0 /opt/SEP /opt/SEP/SEP8.0)
find_path(RSFINCDIR rsf.h HINTS ENV RSF PATH_SUFFIXES include PATHS /opt/RSF/1.7 /opt/RSF)
find_path(GENERICIOINCDIR genericIO.h ENV GENERICIO PATH_SUFFIXES include PATHS /sep/bob/genericIO)
find_library(GENERICIOLIB genericCpp ENV GENERICIO PATH_SUFFIXES lib PATHS /sep/bob/genericIO REQUIRED)
find_library(LIBSEP sep HINTS ENV SEP PATH_SUFFIXES lib PATHS  /usr/local/SEP/lib)
find_library(LIBRSF rsf HINTS ENV RSF PATH_SUFFIXES lib PATHS  /opt/RSF/1.7/lib)
find_library(LIBSEP3D sep3d HINTS ENV SEP PATH_SUFFIXES lib PATHS /usr/local/SEP/lib)
find_library(LIBTBB tbb REQUIRED)

if(LIBSEP3D)
else(LIBSEP3D)
  message(FATAL_ERROR "Could not find library sep3d")
endif(LIBSEP3D)

if(LIBSEP)
else(LIBSEP)
  message(FATAL_ERROR "Could not find library sep")
endif(LIBSEP)

if(LIBRSF)
else(LIBRSF)
  message(FATAL_ERROR "Could not find library rsf")
endif(LIBRSF)


if (RSFINCDIR)
  message(STATUS "Compiling with RSF")
  set(USE_RSF true)
    include_directories(${RSFINCDIR})

else(RSFINCDIR)
  message(STATUS "Not Compiling with RSF")
endif(RSFINCDIR)

#!if (SEPINCDIR AND LIBSEP AND LIBSEP3D)
if (SEPINCDIR)
  message(STATUS "Compiling with SEPlib")
  set(USE_SEP true)
    include_directories(${SEPINCDIR})

else(SEPINCDIR)
  message(STATUS "Not Compiling with SEPlib")
endif(SEPINCDIR)

if(GENERICIO)
  include_directories(${GENERICIO})
else(GENERICIO)
  message(FATAL_ERRROR "Could not find generic IO can't compile")
endif(GENERICIO)

add_subdirectory(base)
add_subdirectory(gui)
add_subdirectory(build)

