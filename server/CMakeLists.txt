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
    ${SRC_DIR}/Parser.cpp
    ${SRC_DIR}/LobbyServerTCP.cpp

)

add_executable(${PROJECT_NAME} ${SOURCES})

if(MSVC)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/_deps/asio-src/asio/include)
    target_link_libraries(${PROJECT_NAME} PRIVATE r_type_ecs ws2_32)
elseif(UNIX)
    target_include_directories(${PROJECT_NAME} PRIVATE ${Asio_SOURCE_DIR}/asio/include)
    target_link_libraries(${PROJECT_NAME} PRIVATE r_type_ecs pthread)
endif()

target_link_libraries(r_type_server PRIVATE nlohmann_json)