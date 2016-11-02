cmake_minimum_required(VERSION 3.3)
project(LatencyTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

link_libraries(stdc++ m pthread)

set(
        SOURCE_FILES

        application.cpp
        abstract_profiler.hpp
        abstract_transport.hpp
        default_transport.cpp
        default_transport.hpp
        your_profiler.cpp
        your_profiler.hpp
        your_transport.cpp
        your_transport.hpp
)
add_executable(LatencyTest ${SOURCE_FILES})