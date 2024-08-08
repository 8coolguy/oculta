cmake_minimum_required(VERSION 3.1)

#Setting C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_NAME oculta)
set(PROJECT_SOURCE_DIR src)
set(LIBRARIES_DIR libs)
set(LIBRARIES 
    mongoose
    sha256
)
project(${PROJECT_NAME})
enable_testing()

foreach(LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

add_executable("${PROJECT_NAME}" "src/server.cpp")

foreach(LIBRARY ${LIBRARIES})
    target_link_libraries("${PROJECT_NAME}" PUBLIC "${LIBRARY}")
    target_include_directories("${PROJECT_NAME}" PUBLIC "${LIBRARIES_DIR}/${LIBRARY}" "${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

# Add executable
add_executable(functions_test.o src/functions_test.cpp src/functions.cpp src/testing.cpp)
add_executable(aes_test.o src/aes_test.cpp src/functions.cpp src/testing.cpp src/SymmetricEncryption.cpp src/SimpleAes.cpp src/Base64Encoder.cpp)
add_executable(rsa_test.o src/rsa_test.cpp src/functions.cpp src/testing.cpp src/AsymmetricEncryption.cpp src/Rsa.cpp src/Base64Encoder.cpp)
add_executable(base64_test.o src/base64_test.cpp src/functions.cpp src/testing.cpp src/Base64Encoder.cpp)


add_test(NAME Functions COMMAND functions_test.o)
add_test(NAME Aes COMMAND aes_test.o)
add_test(NAME Rsa COMMAND rsa_test.o)
add_test(NAME Base64 COMMAND base64_test.o)

