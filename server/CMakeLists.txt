project(r_type_server)

include_directories(include)

set(SRC_DIR src)

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Server.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
