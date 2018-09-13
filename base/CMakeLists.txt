cmake_minimum_required(VERSION 2.8)
project(qtcube-base)

include_directories(${GENERICIOINCDIR})
include_directories(${TBB_INCLUDE_DIRS})

# include_directories(/sep/bob/genericIO/include)
set(SOURCES dynamic.cpp pqueue.cpp)
set(SOURCES ${SOURCES} fastmarch.cpp)
set(SOURCES ${SOURCES} lloyd_1d.cpp path.cpp)
set(SOURCES ${SOURCES} lloyd.cpp percentile.cpp viterbi.cpp)
set(INCLUDES percentile.h )
set(INCLUDES ${INCLUDES}  lloyd_1d.h lloyd.h fastmarch.h)
set(INCLUDES pqueue.h viterbi.h my_score.h dynamic.h path.h)

add_library(base ${SOURCES} ${INCLUDES})
