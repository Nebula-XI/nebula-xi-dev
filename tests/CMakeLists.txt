cmake_minimum_required(VERSION 3.19)

project(nebula_xi_dev_tests
	DESCRIPTION "Nebula-XI Dev Tests"
)

enable_testing()

add_subdirectory(test_dev_gpio)
add_subdirectory(test_dev_i2c)
add_subdirectory(test_dev_sdram)
add_subdirectory(test_dev_spi)
