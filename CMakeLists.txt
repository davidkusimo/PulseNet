cmake_minimum_required(VERSION 3.10)
project(VehicleNetworkSimulator)

# Use C++20 (Standard for modern automotive dev)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the 'include' directory
include_directories(include)

# Executable 1: The Gateway
add_executable(gateway src/gateway.cpp)

# Executable 2: The Multi-ECU Node (Changed from sensor_ecu to ecu_node)
add_executable(ecu_node src/ecu_node.cpp)