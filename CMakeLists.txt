cmake_minimum_required(VERSION 3.26)
project(among_us_server)
set(CMAKE_CXX_STANDARD 23)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "lib/boost_1_81_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "lib/boost_1_81_0/libs")

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost)
IF(Boost_FOUND)
    MESSAGE("found")
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

add_executable(among_us_server
        src/main.cpp
        src/net/packet/packets.hpp)

