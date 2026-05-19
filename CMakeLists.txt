cmake_minimum_required(VERSION 3.10)
project(examples)
option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PRINT_VERSION_MAJOR 1)
set(PRINT_VERSION_MINOR 0)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

add_executable(chat_room chat_room.cpp)
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)

    file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    	add_executable(check chat_room.cpp ${TEST_SOURCES})
    	target_link_libraries(check gtest_main)
    add_test(NAME check COMMAND check)
endif() 
install(TARGETS chat_room
        DESTINATION bin
        COMPONENT applications)

include(CPackConfig.cmake)
