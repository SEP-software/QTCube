project(QTCUBE-exec)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../base)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../gui)
link_directories(${CURRENT_BINARY_DIR}/../base ${CURRENT_BINARY_DIR}/../gui)
 
 
ADD_EXECUTABLE(qt_cube main.cpp )
TARGET_LINK_LIBRARIES(qt_cube gui)
TARGET_LINK_LIBRARIES(qt_cube base)
TARGET_LINK_LIBRARIES(qt_cube ${GENERICIOLIB})


if(USE_SEP)
  MESSAGE(STATUS "SEE SEP")
  TARGET_LINK_LIBRARIES(qt_cube ${LIBSEP3D})
  TARGET_LINK_LIBRARIES(qt_cube ${LIBSEP})
endif(USE_SEP)

if(USE_RSF)
  TARGET_LINK_LIBRARIES(qt_cube ${LIBRSF})
endif(USE_RSF)

target_link_libraries(qt_cube Qt4::QtGui Qt4::QtXml)
TARGET_LINK_LIBRARIES(qt_cube ${LIBTBB})

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
        message(SEND_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

enable_language(CXX)




