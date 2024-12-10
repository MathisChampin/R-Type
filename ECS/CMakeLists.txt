cmake_minimum_required(VERSION 3.10)
project(bootstrap_rtype)

set(CXX g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g3")

set(INCLUDE_DIR ./include/)
set(INCLUDE_COMPONENT ./include/component/)
set(INCLUDE_SYSTEM ./include/system/)
set(SRC_DIR ./src/)
set(SRC_SYSTEM ./src/system/)
set(TEST_DIR ./tests/)
set(TEST_SYS ./tests/system/)

include_directories(${INCLUDE_DIR} ${INCLUDE_COMPONENT} ${INCLUDE_SYSTEM})

set(SOURCES
    ${SRC_DIR}main.cpp
    ${SRC_SYSTEM}position_system.cpp
    ${SRC_SYSTEM}controllable_system.cpp
    ${SRC_SYSTEM}collision_system.cpp
    ${SRC_SYSTEM}level_system.cpp
)

set(TEST_SOURCES
    ${TEST_DIR}testsEntity.cpp
    ${TEST_DIR}testsSparseArray.cpp
    ${TEST_DIR}testsRegistry.cpp
    ${SRC_SYSTEM}position_system.cpp
    ${SRC_SYSTEM}controllable_system.cpp
    ${SRC_SYSTEM}collision_system.cpp
    ${TEST_SYS}testsControllable.cpp
    ${TEST_SYS}testsPosition.cpp
    ${TEST_SYS}testsCollision.cpp
    ${TEST_SYS}testsLevel.cpp
)

add_library(r_type_ecs STATIC ${SOURCES})

target_include_directories(r_type_ecs PRIVATE ${INCLUDE_DIR} ${INCLUDE_COMPONENT} ${INCLUDE_SYSTEM})
target_link_libraries(r_type_ecs)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} r_type_ecs)

add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests r_type_ecs criterion)

add_custom_target(run_tests
    COMMAND unit_tests
    DEPENDS unit_tests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/*.o
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/tests/*.o
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/tests/system/*.o
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/src/system/*.o
)

add_custom_target(fclean_all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean_all
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/unit_tests
)

add_custom_target(rebuild_all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target fclean_all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME}
)
