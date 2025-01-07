cmake_minimum_required(VERSION 3.15)

project(r_type_client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CLIENT_SOURCES "${CMAKE_SOURCE_DIR}/client/src/*.cpp")
file(GLOB_RECURSE CLIENT_HEADERS "${CMAKE_SOURCE_DIR}/client/include/*.hpp")

if(NOT CLIENT_SOURCES)
    message(FATAL_ERROR "No source files found in ${CMAKE_SOURCE_DIR}/client/src/")
endif()

add_executable(r_type_client ${CLIENT_SOURCES} ${CLIENT_HEADERS})

target_include_directories(r_type_client PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/client/include
    ${CMAKE_SOURCE_DIR}/_deps/asio-src/asio/include
    ${CMAKE_SOURCE_DIR}/_deps/sfml-src/include
)

if(UNIX)
    target_link_libraries(r_type_client
        PRIVATE sfml-system sfml-window sfml-graphics sfml-audio pthread
    )
elseif(MSVC)
    set(SFML_LIB_DIR "${CMAKE_SOURCE_DIR}/_deps/sfml-build/lib/Debug")
    target_link_directories(r_type_client PRIVATE ${SFML_LIB_DIR})

    target_link_libraries(r_type_client
        PRIVATE
        debug sfml-system-d optimized sfml-system
        debug sfml-window-d optimized sfml-window
        debug sfml-graphics-d optimized sfml-graphics
        debug sfml-audio-d optimized sfml-audio
        ws2_32
    )

    add_custom_command(
        TARGET r_type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_LIB_DIR}/sfml-system-d-2.dll"
            "${SFML_LIB_DIR}/sfml-window-d-2.dll"
            "${SFML_LIB_DIR}/sfml-graphics-d-2.dll"
            "${SFML_LIB_DIR}/sfml-audio-d-2.dll"
            $<TARGET_FILE_DIR:r_type_client>
        COMMENT "Copie des DLL SFML dans le répertoire binaire"
    )

    add_custom_command(
        TARGET r_type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/_deps/sfml-src/extlibs/bin/x64/OpenAL32.dll
            $<TARGET_FILE_DIR:r_type_client>
        COMMENT "Copie de OpenAL32.dll dans le répertoire binaire"
    )
endif()

add_custom_command(
    TARGET r_type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/client/assets
        $<TARGET_FILE_DIR:r_type_client>/assets
    COMMENT "Copie des assets dans le répertoire binaire"
)

add_custom_command(
    TARGET r_type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/client/config
        $<TARGET_FILE_DIR:r_type_client>/config
    COMMENT "Copie des config dans le répertoire binaire"
)

target_compile_definitions(r_type_client PRIVATE ASIO_STANDALONE)

foreach(header ${CLIENT_HEADERS})
    file(COPY ${header} DESTINATION ${CMAKE_BINARY_DIR}/include)
endforeach()

add_custom_command(
    TARGET r_type_client PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include/client
)
