cmake_minimum_required(VERSION 3.15)

project(r_type_client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fichiers sources et headers
file(GLOB_RECURSE CLIENT_SOURCES "${CMAKE_SOURCE_DIR}/client/src/*.cpp")
file(GLOB_RECURSE CLIENT_HEADERS "${CMAKE_SOURCE_DIR}/client/include/*.hpp")

if(NOT CLIENT_SOURCES)
    message(FATAL_ERROR "No source files found in ${CMAKE_SOURCE_DIR}/client/src/")
endif()

# Vérification d'ASIO
if(NOT DEFINED asio_SOURCE_DIR AND NOT EXISTS ${CMAKE_SOURCE_DIR}/build/_deps/asio-src/asio/include/asio.hpp)
    message(FATAL_ERROR "ASIO not found. Ensure it is downloaded via CPM or exists in the expected directory.")
endif()

# Exécutable
add_executable(r_type_client ${CLIENT_SOURCES} ${CLIENT_HEADERS})
add_dependencies(r_type_client r_type_server)

# Include directories
target_include_directories(r_type_client PRIVATE
    ${CMAKE_SOURCE_DIR}/ECS/include
    ${CMAKE_SOURCE_DIR}/ECS/include/component
    ${CMAKE_SOURCE_DIR}/ECS/include/system
    ${CMAKE_SOURCE_DIR}/server/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/client/include
    $<IF:$<BOOL:${asio_SOURCE_DIR}>,${asio_SOURCE_DIR}/asio/include,${CMAKE_SOURCE_DIR}/build/_deps/asio-src/asio/include>
    ${CMAKE_SOURCE_DIR}/build/_deps/sfml-src/include
)

# Linking directories
# Linking directories
target_link_directories(r_type_client PRIVATE
    ${CMAKE_BINARY_DIR}/server
    ${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug
)


# Gestion des bibliothèques et fichiers spécifiques par plateforme
if(UNIX)
    # Compilation sous Linux
    target_link_libraries(r_type_client PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        pthread
        r_type_ecs
        r_type_server
    )
elseif(WIN32)
    # Compilation sous Windows
    target_link_libraries(r_type_client PRIVATE
        debug sfml-system-d optimized sfml-system
        debug sfml-window-d optimized sfml-window
        debug sfml-graphics-d optimized sfml-graphics
        debug sfml-audio-d optimized sfml-audio
        ws2_32
        r_type_ecs
        r_type_server
    )

    # Copie des DLL nécessaires
    add_custom_command(
        TARGET r_type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-system-d-2.dll"
            "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-window-d-2.dll"
            "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-graphics-d-2.dll"
            "${CMAKE_SOURCE_DIR}/build/_deps/sfml-build/lib/Debug/sfml-audio-d-2.dll"
            "${CMAKE_SOURCE_DIR}/build/_deps/sfml-src/extlibs/bin/x64/OpenAL32.dll"
            $<TARGET_FILE_DIR:r_type_client>
        COMMENT "Copie des DLL SFML et OpenAL32 dans le répertoire binaire"

    )

    add_custom_command(
        TARGET r_type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/client/assets
            $<TARGET_FILE_DIR:r_type_client>/../assets
        COMMENT "AH lA AH ME DOU LI LO R G E"
    )

    add_custom_command(
    TARGET r_type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/client/config
        $<TARGET_FILE_DIR:r_type_client>/../config
    COMMENT "Copie des fichiers de configuration dans le répertoire binaire"
)

add_custom_command(
    TARGET r_type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/server/configFile
        $<TARGET_FILE_DIR:r_type_client>/../../server/configFile
    COMMENT "Copie des fichiers de configuration dans le répertoire binaire"
)


endif()




# Copie des fichiers de configuration
add_custom_command(
    TARGET r_type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/client/config
        $<TARGET_FILE_DIR:r_type_client>
    COMMENT "Copie des fichiers de configuration dans le répertoire binaire"
)

# Copie des assets
add_custom_command(
    TARGET r_type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/client/assets
        $<TARGET_FILE_DIR:r_type_client>/assets
    COMMENT "Copie des assets dans le répertoire binaire"
)

# Définitions de compilation
target_compile_definitions(r_type_client PRIVATE ASIO_STANDALONE)

# Création des répertoires d'includes pour Windows
foreach(header ${CLIENT_HEADERS})
    file(COPY ${header} DESTINATION ${CMAKE_BINARY_DIR}/include)
endforeach()

add_custom_command(
    TARGET r_type_client PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include/client
)

# Lien avec les bibliothèques JSON, ECS, et serveur
target_link_libraries(r_type_client PRIVATE nlohmann_json r_type_ecs r_type_server)
