cmake_minimum_required(VERSION 3.22.1)
project(syclOfHell LANGUAGES CXX)   
find_package(IntelSYCL REQUIRED)

file(GLOB files "*.cpp")
foreach(file_name ${files})
	 get_filename_component(exe_name ${file_name} NAME_WE)
	 add_executable(${exe_name} ${file_name} argparse.hpp)
  	 add_sycl_to_target(TARGET ${exe_name} SOURCES ${file_name})
endforeach()
