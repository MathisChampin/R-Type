cmake_minimum_required(VERSION 3.15)

project(r_type_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fichiers sources et d'en-tête du SERVEUR
file(GLOB_RECURSE SERVER_SOURCES "src/*.cpp")
# Exclure main.cpp des sources de la bibliothèque
list(FILTER SERVER_SOURCES EXCLUDE REGEX "src/main.cpp$")

file(GLOB_RECURSE SERVER_HEADERS "include/*.hpp")

# Création de la bibliothèque partagée
add_library(${PROJECT_NAME} SHARED ${SERVER_SOURCES} ${SERVER_HEADERS})

# Fichier source pour l'exécutable
set(SERVER_MAIN_SOURCE "src/main.cpp")

# Création de l'exécutable
add_executable(${PROJECT_NAME}_exec ${SERVER_MAIN_SOURCE})

# Inclusion des répertoires d'en-tête pour la bibliothèque et l'exécutable
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/component>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/system>
)

target_include_directories(${PROJECT_NAME}_exec PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/component>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/system>
)

# Gestion des dépendances
if(NOT DEFINED asio_SOURCE_DIR AND NOT EXISTS ${CMAKE_SOURCE_DIR}/_deps/asio-src/asio/include/asio.hpp)
    message(FATAL_ERROR "ASIO not found. Ensure it is downloaded via CPM or exists in the expected directory.")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<IF:$<BOOL:${asio_SOURCE_DIR}>,${asio_SOURCE_DIR}/asio/include,${CMAKE_SOURCE_DIR}/_deps/asio-src/asio/include>
)

target_include_directories(${PROJECT_NAME}_exec PUBLIC
    $<IF:$<BOOL:${asio_SOURCE_DIR}>,${asio_SOURCE_DIR}/asio/include,${CMAKE_SOURCE_DIR}/_deps/asio-src/asio/include>
)

# Ajout des options de compilation
target_compile_definitions(${PROJECT_NAME} PRIVATE ASIO_STANDALONE)
target_compile_definitions(${PROJECT_NAME}_exec PRIVATE ASIO_STANDALONE)

# Ajout des chemins de recherche de bibliothèques
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/ECS/ecs_build)
target_link_directories(${PROJECT_NAME}_exec PRIVATE ${CMAKE_SOURCE_DIR}/ECS/ecs_build)

# Lier avec les bibliothèques nécessaires
if(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE r_type_ecs ws2_32)
    target_link_libraries(${PROJECT_NAME}_exec PRIVATE r_type_ecs ws2_32)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE r_type_ecs pthread)
    target_link_libraries(${PROJECT_NAME}_exec PRIVATE r_type_ecs pthread)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)
target_link_libraries(${PROJECT_NAME}_exec PRIVATE nlohmann_json r_type_server)