cmake_minimum_required(VERSION 3.26)
project(among_us_server)
set(CMAKE_CXX_STANDARD 23)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
SET(BOOST_REQUESTED_VERSION 1.81.0)
FIND_PACKAGE(Boost COMPONENTS system program_options)

#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "lib/boost_1_81_0")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "lib/boost_1_81_0/libs")
#
#SET(Boost_USE_STATIC_LIBS OFF)
#SET(Boost_USE_MULTITHREAD ON)
#FIND_PACKAGE(Boost)
#IF(Boost_FOUND)
#    MESSAGE("found")
#    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#ENDIF(Boost_FOUND)
#
#SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

add_executable(among_us_server
        src/main.cpp
        src/net/connection.cpp
        src/net/buffer/buffer.hpp
        src/net/buffer/hazel.hpp
        src/net/packet/packets.cpp
        src/net/packet/option/root/roots.cpp
        src/net/game_code.cpp)

