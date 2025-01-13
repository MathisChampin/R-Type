cmake_minimum_required(VERSION 3.15)

project(r_type_client_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CLIENT_SOURCES_2 "${CMAKE_SOURCE_DIR}/client_2/src/*.cpp")
file(GLOB_RECURSE CLIENT_HEADERS_2 "${CMAKE_SOURCE_DIR}/client_2/include/*.hpp")

if(NOT CLIENT_SOURCES_2)
    message(FATAL_ERROR "No source files found in ${CMAKE_SOURCE_DIR}/client_2/src/")
endif()

add_executable(r_type_client_2 ${CLIENT_SOURCES_2} ${CLIENT_HEADERS_2})

target_include_directories(r_type_client_2 PRIVATE
    ${CMAKE_SOURCE_DIR}/client_2/include
    ${CMAKE_SOURCE_DIR}/_deps/sfml-src/include
)

set(ECS_DIR ${CMAKE_SOURCE_DIR}/ECS)
if(EXISTS ${ECS_DIR})
    add_subdirectory(${ECS_DIR} ${CMAKE_BINARY_DIR}/ecs_build_2)

    target_include_directories(r_type_client_2 PRIVATE
        ${ECS_DIR}/include
        ${ECS_DIR}/include/component
        ${ECS_DIR}/include/system
    )
    target_link_libraries(r_type_client_2 PRIVATE r_type_ecs)
else()
    message(FATAL_ERROR "ECS directory not found at ${ECS_DIR}")
endif()

if(UNIX)
    target_link_libraries(r_type_client_2
        PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        pthread
    )
elseif(MSVC)
    set(SFML_LIB_DIR "${CMAKE_SOURCE_DIR}/_deps/sfml-build/lib/Debug")
    target_link_directories(r_type_client_2 PRIVATE ${SFML_LIB_DIR})

    target_link_libraries(r_type_client_2
        PRIVATE
        debug sfml-system-d optimized sfml-system
        debug sfml-window-d optimized sfml-window
        debug sfml-graphics-d optimized sfml-graphics
        debug sfml-audio-d optimized sfml-audio
        ws2_32
    )

    add_custom_command(
        TARGET r_type_client_2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_LIB_DIR}/sfml-system-d-2.dll"
            "${SFML_LIB_DIR}/sfml-window-d-2.dll"
            "${SFML_LIB_DIR}/sfml-graphics-d-2.dll"
            "${SFML_LIB_DIR}/sfml-audio-d-2.dll"
            $<TARGET_FILE_DIR:r_type_client_2>
        COMMENT "Copie des DLL SFML dans le répertoire binaire"
    )

    add_custom_command(
        TARGET r_type_client_2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/_deps/sfml-src/extlibs/bin/x64/OpenAL32.dll
            $<TARGET_FILE_DIR:r_type_client_2>
        COMMENT "Copie de OpenAL32.dll dans le répertoire binaire"
    )
endif()

add_custom_command(
    TARGET r_type_client_2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/client_2/assets
        $<TARGET_FILE_DIR:r_type_client_2>/assets
    COMMENT "Copie des assets dans le répertoire binaire"
)

add_custom_command(
    TARGET r_type_client_2 PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include/
)

foreach(header ${CLIENT_HEADERS_2})
    file(COPY ${header} DESTINATION ${CMAKE_BINARY_DIR}/include)
endforeach()
