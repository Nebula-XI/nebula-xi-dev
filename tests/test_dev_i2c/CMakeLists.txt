cmake_minimum_required(VERSION 3.19)

project(nebula_xi_dev_i2c_test
	DESCRIPTION "Nebula-XI Dev I2C Test"
)

add_executable(${PROJECT_NAME} test_dev_i2c.cpp)
add_test("test_dev_i2c" ${PROJECT_NAME})
