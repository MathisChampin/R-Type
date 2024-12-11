cmake_minimum_required(VERSION 3.16)

project(RType)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME sfml
    GITHUB_REPOSITORY SFML/SFML
    GIT_TAG 2.6.1
)

CPMAddPackage(
    NAME asio
    GITHUB_REPOSITORY chriskohlhoff/asio
    GIT_TAG asio-1-30-2
)

add_subdirectory(ECS)
add_subdirectory(server)
add_subdirectory(client)
