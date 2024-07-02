cmake_minimum_required(VERSION 3.1)
project(oculta)

add_executable(function_tests functions_test.cpp functions.cpp testing.cpp)
add_executable(aes_tests aes_test.cpp functions.cpp testing.cpp SymmetricEncryption.cpp SimpleAes.cpp)
