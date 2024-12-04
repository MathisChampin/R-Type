project(r_type_server)

include_directories(include)

set(SRC_DIR src)

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Server.cpp
    ${SRC_DIR}/Binary.cpp
    ${SRC_DIR}/Packet.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -DASIO_STANDALONE -Wall -Wextra -Werror)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)