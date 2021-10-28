# Units Device Classes (UDC)

[![MIT License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/mit-license.php)
[![CMake](https://github.com/Nebula-XI/nebula-xi-dev/actions/workflows/cmake.yml/badge.svg)](https://github.com/Nebula-XI/nebula-xi-dev/actions/workflows/cmake.yml)

## Requirements

CMake 3.21, Ninja 1.10.2, GCC 10.3

## Configuring

### Linux x86_64

`cmake --preset linux-x64-release`

`cmake --preset linux-x64-debug`

## Building

### Linux x86_64


`cmake --build --preset linux-x64-release`

`cmake --build --preset linux-x64-release-rebuild`

`cmake --build --preset linux-x64-release-verbose`

`cmake --build --preset linux-x64-debug`

`cmake --build --preset linux-x64-debug-rebuild`

`cmake --build --preset linux-x64-debug-verbose`

## Testing

### Linux x86_64


`ctest --preset linux-x64-release`

`ctest --preset linux-x64-debug`
