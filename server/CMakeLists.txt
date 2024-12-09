# server/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(r_type_server)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/component)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/system)

add_subdirectory(../ECS ${CMAKE_BINARY_DIR}/ecs_build)

set(SRC_DIR src)
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Server.cpp
    ${SRC_DIR}/Binary.cpp
    ${SRC_DIR}/Packet.cpp
    ${SRC_DIR}/ProtocoleHandler.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -DASIO_STANDALONE -Wall -Wextra -Werror)

target_link_libraries(${PROJECT_NAME} PRIVATE pthread r_type_ecs)
