cmake_minimum_required(VERSION 3.10)
project(ECS)

set(CXX g++)
set(CMAKE_CXX_STANDARD 20)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244")  
    add_definitions(-D_WIN32_WINNT=0x0601) 
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror") 
endif()
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDE_COMPONENT ${INCLUDE_DIR}/component)
set(INCLUDE_SYSTEM ${INCLUDE_DIR}/system)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC_SYSTEM ${SRC_DIR}/system)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(TEST_SYS ${TEST_DIR}/system)

include_directories(${INCLUDE_DIR} ${INCLUDE_COMPONENT} ${INCLUDE_SYSTEM})

set(SOURCES
    ${SRC_SYSTEM}/position_system.cpp
    ${SRC_SYSTEM}/controllable_system.cpp
    ${SRC_SYSTEM}/collision_system.cpp
    ${SRC_SYSTEM}/level_system.cpp
    ${SRC_SYSTEM}/shoot_system.cpp
    ${SRC_SYSTEM}/kill_system.cpp
    ${SRC_SYSTEM}/lose_system.cpp
    ${SRC_SYSTEM}/win_system.cpp
    ${SRC_SYSTEM}/collision_power_up_move_system.cpp
    ${SRC_SYSTEM}/collision_power_up_shoot_system.cpp
)

set(MAIN_SOURCES
    ${SRC_DIR}/main.cpp  
)
if(UNIX)
set(TEST_SOURCES
    ${TEST_DIR}/testsEntity.cpp
    ${TEST_DIR}/testsSparseArray.cpp
    ${TEST_DIR}/testsRegistry.cpp
    ${SRC_SYSTEM}/position_system.cpp
    ${SRC_SYSTEM}/controllable_system.cpp
    ${SRC_SYSTEM}/collision_system.cpp
    ${TEST_SYS}/testsControllable.cpp
    ${TEST_SYS}/testsPosition.cpp
    ${TEST_SYS}/testsCollision.cpp
    ${TEST_SYS}/testsLevel.cpp
    ${TEST_SYS}/testsShoot.cpp
    ${TEST_SYS}/testsKill.cpp
)
endif()

if (NOT TARGET r_type_ecs)
    add_library(r_type_ecs STATIC ${SOURCES})
    target_include_directories(r_type_ecs PRIVATE ${INCLUDE_DIR} ${INCLUDE_COMPONENT} ${INCLUDE_SYSTEM})
endif()

if (NOT TARGET bootstrap_rtype)
    add_executable(bootstrap_rtype ${MAIN_SOURCES})
    target_link_libraries(bootstrap_rtype r_type_ecs)
endif()

if(UNIX)
if (NOT TARGET unit_tests)
    add_executable(unit_tests ${TEST_SOURCES})
    target_link_libraries(unit_tests r_type_ecs criterion)

    add_custom_target(run_tests
        COMMAND unit_tests
        DEPENDS unit_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()
endif()


if (NOT TARGET clean_all)
    add_custom_target(clean_all
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/*.o
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/tests/*.o
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/tests/system/*.o
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/src/system/*.o
    )
endif()

if (NOT TARGET fclean_all)
    add_custom_target(fclean_all
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean_all
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/bootstrap_rtype
        COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/unit_tests
    )
endif()

if (NOT TARGET rebuild_all)
    add_custom_target(rebuild_all
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target fclean_all
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target bootstrap_rtype
    )
endif()