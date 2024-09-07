cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_NAME mongoose)
set(LIBRARY_NAME mongoose)
set(LIBRARY_SOURCE mongoose.c)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCE})


