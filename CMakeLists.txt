cmake_minimum_required(VERSION 3.21)
project(ex1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(
        IsraeliQueue.h
        IsraeliQueue.c
        tool/HackEnrollment.c
        tool/HackEnrollment.h
        tool/main.c)
