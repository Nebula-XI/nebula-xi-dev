cmake_minimum_required(VERSION 3.19)

project(nebula_xi_dev_sdram_test
	DESCRIPTION "Nebula-XI Dev SDRAM Test"
)

add_executable(${PROJECT_NAME} test_dev_sdram.cpp)
add_test("test_dev_sdram" ${PROJECT_NAME})
