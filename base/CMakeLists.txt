cmake_minimum_required(VERSION 2.8)
project(qtcube-base)

include_directories(${GENERICIOINCDIR})
include_directories(${TBB_INCLUDE_DIRS})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(CMAKE_MACOSX_RPATH 1)
endif()
# include_directories(/sep/bob/genericIO/include)
set(SOURCES dynamic.cpp pqueue.cpp)
set(SOURCES
    ${SOURCES}
    fastmarch.cpp
    orient_cube.cpp
    orient_map.cpp
    outcore_data.cpp
    buffer.cpp
    buffers_data.cpp
    incore_data.cpp
    pick_new.cpp
    position.cpp
    orientation_server.cpp
    float_buffer.cpp
    float_buffer_buffer.cpp
    byte_buffer_buffer.cpp
    byte_buffer.cpp
    partial_data.cpp
    io_func.cpp
    fileIO.cpp
    pairs_new.cpp
    created_data.cpp
    autopick_2d.cpp
    auto_brown.cpp
    auto_viteribi.cpp
    pick_bucket.cpp)
set(SOURCES ${SOURCES} lloyd_1d.cpp path.cpp util.cpp trace_io.cpp)
set(SOURCES ${SOURCES} lloyd.cpp percentile.cpp viterbi.cpp dataset.cpp)
set(INCLUDES percentile.h dataset.h)
set(INCLUDES
    ${INCLUDES}
    lloyd_1d.h
    autopick_2d.h
    auto_brown.h
    auto_viteribi.h
    lloyd.h
    pick_bucket.h
    pairs_new.h
    incore_data.h
    fastmarch.h
    buffers_data.h
    buffer.h
    position.h
    created_data.h
        float_buffer_buffer.h
    orientation_server.h
    pick_new.h
    outcore_data.h
    orient_cube.h
    byte_buffer_buffer.h
    orient_map.h
    partial_data.h
    fileIO.h
    util.h)
set(INCLUDES
    pqueue.h
    viterbi.h
    my_score.h
    dynamic.h
    path.h
    bar_pt.h
    io_func.h
    trace_io.h)

add_library(base ${SOURCES} ${INCLUDES})
