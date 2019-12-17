cmake_minimum_required(VERSION 3.14)
project(semestral)

set(CMAKE_CXX_STANDARD 14)

add_executable(semestral main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(semestral Threads::Threads)