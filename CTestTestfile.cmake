# CMake generated Testfile for 
# Source directory: /root/dev/oculta
# Build directory: /root/dev/oculta
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Functions "/root/dev/oculta/functions_test.o")
set_tests_properties(Functions PROPERTIES  _BACKTRACE_TRIPLES "/root/dev/oculta/CMakeLists.txt;35;add_test;/root/dev/oculta/CMakeLists.txt;0;")
add_test(Aes "/root/dev/oculta/aes_test.o")
set_tests_properties(Aes PROPERTIES  _BACKTRACE_TRIPLES "/root/dev/oculta/CMakeLists.txt;36;add_test;/root/dev/oculta/CMakeLists.txt;0;")
add_test(Rsa "/root/dev/oculta/rsa_test.o")
set_tests_properties(Rsa PROPERTIES  _BACKTRACE_TRIPLES "/root/dev/oculta/CMakeLists.txt;37;add_test;/root/dev/oculta/CMakeLists.txt;0;")
add_test(Base64 "/root/dev/oculta/base64_test.o")
set_tests_properties(Base64 PROPERTIES  _BACKTRACE_TRIPLES "/root/dev/oculta/CMakeLists.txt;38;add_test;/root/dev/oculta/CMakeLists.txt;0;")
subdirs("libs/mongoose")
subdirs("libs/sha256")
