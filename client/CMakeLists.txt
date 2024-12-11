project(r_type_client)

file(GLOB_RECURSE CLIENT_SOURCES "${CMAKE_SOURCE_DIR}/client/src/*.cpp")
file(GLOB_RECURSE CLIENT_HEADERS "${CMAKE_SOURCE_DIR}/client/include/*.hpp")

add_executable(r_type_client ${CLIENT_SOURCES} ${CLIENT_HEADERS})

target_include_directories(r_type_client PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/client/include
    ${CMAKE_BINARY_DIR}/include
    ${CMAKE_SOURCE_DIR}/_deps/asio-src/asio/include
    ${CMAKE_SOURCE_DIR}/_deps/sfml-src/include
)

target_link_libraries(r_type_client
    PRIVATE sfml-system sfml-window sfml-graphics sfml-audio pthread
)

target_compile_definitions(r_type_client PRIVATE ASIO_STANDALONE)

file(GLOB_RECURSE CLIENT_HEADERS_TO_COPY "${CMAKE_SOURCE_DIR}/client/include/*.hpp")
foreach(header ${CLIENT_HEADERS_TO_COPY})
    file(COPY ${header} DESTINATION ${CMAKE_BINARY_DIR}/include)
endforeach()

add_custom_command(
    TARGET r_type_client PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include/client
)

add_custom_command(
    TARGET r_type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/client/assets ${CMAKE_BINARY_DIR}/client/assets
)
