cmake_minimum_required(VERSION 3.0)

project(libglad)

set(SRCS glad.c)

set(INCS glad.h khrplatform.h)

add_library(glad ${SRCS} ${INCS})
