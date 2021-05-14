cmake_minimum_required(VERSION 3.19)

project(nebula_xi_dev_gpio_test
	DESCRIPTION "Nebula-XI Dev GPIO Test"
)

add_executable(${PROJECT_NAME} test_dev_gpio.cpp)
add_test("test_dev_gpio" ${PROJECT_NAME})
