cmake_minimum_required(VERSION 2.8.9)
project(rad-LED)

set(CMAKE_CXX_FLAGS "-pthread")

INCLUDE_DIRECTORIES(lib/wiiuse/src)
LINK_DIRECTORIES(lib/wiiuse/build/src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(run.exe ${SOURCES})
target_link_libraries(run.exe wiiuse serialport)
