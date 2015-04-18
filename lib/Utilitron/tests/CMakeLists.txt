cmake_minimum_required(VERSION 2.6)
project (Tests)

set(SRCS
    Tests.cpp
)

find_package(Boost)

set(BASEPATH "${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_definitions(-DBOOST_TEST_DYN_LINK -std=c++11)

include_directories("${BASEPATH}" ${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})

link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

add_executable(Tests ${SRCS})

target_link_libraries(Tests
    ${Boost_LIBRARIES}

    -lboost_system
    -lboost_iostreams
    -lboost_filesystem
    -lboost_unit_test_framework
)
