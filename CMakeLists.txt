cmake_minimum_required(VERSION 3.16)

project(RType)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244") 
    add_definitions(-D_WIN32_WINNT=0x0601)  
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror") 
endif()

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME nlohmann_json
    GITHUB_REPOSITORY nlohmann/json
    GIT_TAG v3.11.2
)


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
add_subdirectory(client_2)

if(WIN32)
    find_package(Threads REQUIRED)  
endif()
