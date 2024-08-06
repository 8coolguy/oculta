#add_executable(function_tests.o functions_test.cpp functions.cpp testing.cpp)
#add_executable(aes_tests.o aes_test.cpp functions.cpp testing.cpp SymmetricEncryption.cpp SimpleAes.cpp)
#add_executable(rsa_tests.o rsa_test.cpp functions.cpp testing.cpp AsymmetricEncryption.cpp Rsa.cpp Base64Enc#oder.cpp)
#add_executable(base64_tests.o base64_test.cpp functions.cpp testing.cpp Base64Encoder.cpp)
add_executable(oculta.o server.cpp)

target_link_libraries(oculta.o mongoose sha256)
