project(r_type_server)

set(SRC_DIR src)

set(SOURCES
    ${SRC_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
