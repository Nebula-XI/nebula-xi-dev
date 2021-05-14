cmake_minimum_required(VERSION 3.19)

project(nebula_xi_dev_spi_test
	DESCRIPTION "Nebula-XI Dev SPI Test"
)

add_executable(${PROJECT_NAME} test_dev_spi.cpp)
add_test("test_dev_spi" ${PROJECT_NAME})
