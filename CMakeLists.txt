cmake_minimum_required(VERSION 3.26)
project(among_us_server)
set(CMAKE_CXX_STANDARD 23)

include_directories(plog/include)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
SET(BOOST_REQUESTED_VERSION 1.81.0)
FIND_PACKAGE(Boost COMPONENTS system program_options)

add_executable(among_us_server
        src/main.cpp
        src/net/connection.cpp
        src/net/buffer/buffer.cpp
        src/net/inner/options.cpp
        src/net/inner/constants.hpp
        src/net/packet/packets.cpp
        src/net/packet/option/root/roots.cpp
        src/net/game_code.cpp)

