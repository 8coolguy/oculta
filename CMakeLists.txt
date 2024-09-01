include(FetchContent)



cmake_minimum_required(VERSION 3.1)

#Setting C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_NAME oculta)
set(PROJECT_SOURCE_DIR src)
set(LIBRARIES_DIR libs)
set(LIBRARIES 
    mongoose
)
project(${PROJECT_NAME})
enable_testing()

foreach(LIBRARY ${LIBRARIES})
    add_subdirectory("${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

add_executable(${PROJECT_NAME} src/server.cpp src/net.cpp)

foreach(LIBRARY ${LIBRARIES})
    target_link_libraries("${PROJECT_NAME}" PUBLIC "${LIBRARY}")
    target_include_directories("${PROJECT_NAME}" PUBLIC "${LIBRARIES_DIR}/${LIBRARY}" "${LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)
FetchContent_Declare(
  libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG a6b1d60e74c1427c8ac2324b85cd4a0dc2068332
)
set(PQXX_LIBRARIES pqxx_static)

FetchContent_MakeAvailable(libpqxx)

target_link_libraries(${PROJECT_NAME} PUBLIC "${PQXX_LIBRARIES}")
# Add executable
add_executable(functions_test.o src/functions_test.cpp src/functions.cpp src/testing.cpp)
add_executable(aes_test.o src/aes_test.cpp src/functions.cpp src/testing.cpp src/SymmetricEncryption.cpp src/SimpleAes.cpp src/Base64Encoder.cpp)
add_executable(rsa_test.o src/rsa_test.cpp src/functions.cpp src/testing.cpp src/AsymmetricEncryption.cpp src/Rsa.cpp src/Base64Encoder.cpp)
add_executable(base64_test.o src/base64_test.cpp src/functions.cpp src/testing.cpp src/Base64Encoder.cpp)


add_test(NAME Functions COMMAND functions_test.o)
add_test(NAME Aes COMMAND aes_test.o)
add_test(NAME Rsa COMMAND rsa_test.o)
add_test(NAME Base64 COMMAND base64_test.o)

