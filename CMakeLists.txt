cmake_minimum_required(VERSION 3.18.4)

project(lab_2)

set (CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(app)
