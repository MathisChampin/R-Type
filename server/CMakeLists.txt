cmake_minimum_required(VERSION 3.15)

project(r_type_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fichiers sources et d'en-tête du SERVEUR
file(GLOB_RECURSE SERVER_SOURCES "src/*.cpp")
# Exclure main.cpp des sources de la bibliothèque
list(FILTER SERVER_SOURCES EXCLUDE REGEX "src/main.cpp$")

file(GLOB_RECURSE SERVER_HEADERS "include/*.hpp")

# Création de la bibliothèque statique
add_library(${PROJECT_NAME} STATIC ${SERVER_SOURCES} ${SERVER_HEADERS})

# Propriétés de sortie pour la bibliothèque
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/server/Debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/server/Release"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/server/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/server/Release"
)

# Fichier source pour l'exécutable
set(SERVER_MAIN_SOURCE "src/main.cpp")

# Création de l'exécutable
add_executable(${PROJECT_NAME}_exec ${SERVER_MAIN_SOURCE})

# Propriétés de sortie pour l'exécutable
set_target_properties(${PROJECT_NAME}_exec PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/server/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/server/Release"
)

# Inclusion des répertoires d'en-tête
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/build/_deps/asio-src/asio/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/component>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/system>
)

target_include_directories(${PROJECT_NAME}_exec PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/build/_deps/asio-src/asio/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/component>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../ECS/include/system>
)

# Ajout des options de compilation
if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _WINDLL ASIO_STANDALONE)
    target_compile_definitions(${PROJECT_NAME}_exec PRIVATE ASIO_STANDALONE)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE ASIO_STANDALONE)
    target_compile_definitions(${PROJECT_NAME}_exec PRIVATE ASIO_STANDALONE)
endif()

# Lien avec les bibliothèques nécessaires
if(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE r_type_ecs ws2_32)
    target_link_libraries(${PROJECT_NAME}_exec PRIVATE r_type_ecs ws2_32 ${PROJECT_NAME})
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE r_type_ecs pthread)
    target_link_libraries(${PROJECT_NAME}_exec PRIVATE r_type_ecs pthread ${PROJECT_NAME})
endif()

# Lien avec les bibliothèques JSON
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)
target_link_libraries(${PROJECT_NAME}_exec PRIVATE nlohmann_json ${PROJECT_NAME})

