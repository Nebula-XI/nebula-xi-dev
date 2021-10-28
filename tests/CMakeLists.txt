cmake_minimum_required(VERSION 3.19)

project(nebula-xi-dev-tests)

set(PROJECT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/ctest/)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(test_dev_gpio)
add_subdirectory(test_dev_i2c)
add_subdirectory(test_dev_sdram)
add_subdirectory(test_dev_spi)
