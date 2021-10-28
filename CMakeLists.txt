cmake_minimum_required(VERSION 3.19)
project(nebula-xi-dev)

set(PROJECT_COMPILE_OPTIONS)
set(PROJECT_COMPILE_DEFINES)
set(PROJECT_LINK_LIBRARIES)

set(PROJECT_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}
)
set(PROJECT_INCLUDES )

add_library(${PROJECT_NAME} INTERFACE)

option(NEBULAXI_DEV_TEST_VERBOSE "Verbose output nebula-xi-dev test." OFF)

if(NEBULAXI_DEV_TEST_VERBOSE)
    set(PROJECT_COMPILE_DEFINES ${PROJECT_COMPILE_DEFINES} NEBULAXI_DEV_TEST_VERBOSE)
endif()

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} INTERFACE ${PROJECT_COMPILE_DEFINES})

option(NEBULAXI_DEV_BUILD_TEST "Build nebula-xi-dev test." OFF)

if(NEBULAXI_DEV_BUILD_TEST)
    enable_testing()
    add_subdirectory(tests)
endif()
