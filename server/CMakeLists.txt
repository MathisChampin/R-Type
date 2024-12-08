# server/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

# Déclaration du projet
project(r_type_server)

# Répertoires d'inclusion
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/component)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/system)

# Ajouter le sous-répertoire ECS
add_subdirectory(../ECS ${CMAKE_BINARY_DIR}/ecs_build)

# Sources du serveur
set(SRC_DIR src)
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Server.cpp
    ${SRC_DIR}/Binary.cpp
    ${SRC_DIR}/Packet.cpp
    ${SRC_DIR}/ProtocoleHandler.cpp
)

# Créer l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Spécifier les options de compilation
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -DASIO_STANDALONE -Wall -Wextra -Werror)

# Lier les bibliothèques nécessaires
target_link_libraries(${PROJECT_NAME} PRIVATE pthread r_type_ecs)
