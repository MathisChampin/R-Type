project(r_type_client)

include_directories(include/client)

set(SRC_DIR src)

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Client.cpp
    ${SRC_DIR}/Binary.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE -DASIO_STANDALONE -Wall -Wextra -Werror)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
