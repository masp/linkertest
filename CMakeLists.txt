cmake_minimum_required(VERSION 3.15)
project(linkerscriptstest C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(pub STATIC pub.c)
target_compile_options(pub PRIVATE -fvisibility=hidden)
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/libwrap_pub.a
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ${CMAKE_OBJCOPY}
        ARGS --redefine-syms=${CMAKE_CURRENT_SOURCE_DIR}/wrap.map ${CMAKE_CURRENT_BINARY_DIR}/libpub.a ${CMAKE_CURRENT_BINARY_DIR}/libwrap_pub.a)

add_library(wrap SHARED wrap.cpp ${CMAKE_CURRENT_BINARY_DIR}/libwrap_pub.a)
target_link_libraries(wrap PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/libwrap_pub.a)
target_compile_options(wrap PRIVATE "-fvisibility=hidden")

add_executable(testexe main.cpp)
target_link_libraries(testexe wrap)