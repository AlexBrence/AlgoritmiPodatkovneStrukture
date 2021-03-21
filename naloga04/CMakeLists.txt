cmake_minimum_required(VERSION 3.17)
project(naloga04)
include_directories(include)
file(GLOB_RECURSE SOURCES "src/*".cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pedantic-errors -Wall -Wextra -Weffc++")

add_executable(main ${SOURCES})
install(TARGETS main DESTINATION /usr/bin)
