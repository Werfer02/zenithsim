cmake_minimum_required(VERSION 3.10.0)
project(zenithsim VERSION 0.1.0 LANGUAGES C CXX)

add_executable(zenithsim zenithsim/main.cpp zenithsim/node.cpp zenithsim/evalfunction.cpp)
target_include_directories(zenithsim PRIVATE zenithsim)
