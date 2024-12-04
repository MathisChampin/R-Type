cmake_minimum_required(VERSION 3.16)
project(RType)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_subdirectory(server)
add_subdirectory(ECS)
