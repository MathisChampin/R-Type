cmake_minimum_required(VERSION 3.16)

project(RType)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /wd4244 /wd4267 /wd4996")
    add_definitions(-D_WIN32_WINNT=0x0601)  
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror") 
endif()

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)

CPMAddPackage(
    NAME sfml
    URL https://github.com/SFML/SFML/archive/refs/tags/2.6.1.tar.gz
)

CPMAddPackage(
    NAME asio
    URL https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-30-2.tar.gz
)


add_subdirectory(ECS)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(client_2)

if(DEFINED ENV{GITHUB_ACTIONS})
    message(STATUS "Running in CI environment: Forcing CPM include directories")
    include_directories(${asio_SOURCE_DIR}/asio/include)
endif()

if(WIN32)
    find_package(Threads REQUIRED)  
endif()
