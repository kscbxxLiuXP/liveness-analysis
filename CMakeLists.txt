cmake_minimum_required(VERSION 3.27)
project(liveness)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.84.0 COMPONENTS system filesystem REQUIRED)
if (Boost_FOUND)
    message(STATUS "Boost Include dirs " ${Boost_INCLUDE_DIRS})
    message(STATUS "Boost libraries " ${Boost_LIBRARIES})
    message(STATUS "Boost version " ${Boost_VERSION})
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

add_executable(liveness main.cpp
        Block.cpp
        Block.h
        Func.cpp
        Func.h
        Instruction.cpp
        Instruction.h
        init.h
        operand.h
        utils.cpp
        utils.h)

if (Boost_FOUND)
    target_link_libraries(liveness ${Boost_LIBRARIES})
endif ()
