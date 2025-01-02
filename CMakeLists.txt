cmake_minimum_required(VERSION 3.22.1)
project(VulkanPlayground VERSION 1.0 LANGUAGES CXX C)

include("./deps/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_subdirectory(src)