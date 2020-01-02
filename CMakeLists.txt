cmake_minimum_required(VERSION 3.15)
project(linkerscriptstest C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(PUB_OPTS "")
if(WIN32)
    set(PUB_LINK_OPTS "/def:${CMAKE_CURRENT_SOURCE_DIR}/wrap.def")
    set(ORIG_PUB_LIB ${CMAKE_CURRENT_BINARY_DIR}/pub.lib)
    set(WRAPPED_PUB_LIB ${CMAKE_CURRENT_BINARY_DIR}/pub.lib)
else()
    set(PUB_OPTS -fvisibility=hidden)
    set(ORIG_PUB_LIB ${CMAKE_CURRENT_BINARY_DIR}/libpub.a)
    set(WRAPPED_PUB_LIB ${CMAKE_CURRENT_BINARY_DIR}/libwrap_pub.a)
endif()

add_library(pub STATIC pub.c)
target_compile_options(pub PRIVATE ${PUB_OPTS})
if (LINUX)
    add_custom_command(
            OUTPUT ${WRAPPED_PUB_LIB}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND ${CMAKE_OBJCOPY}
            ARGS --redefine-syms=${CMAKE_CURRENT_SOURCE_DIR}/wrap.map ${ORIG_PUB_LIB} ${WRAPPED_PUB_LIB})
endif()

add_library(wrap SHARED wrap.cpp ${WRAPPED_PUB_LIB})
target_link_libraries(wrap PRIVATE ${WRAPPED_PUB_LIB})
target_compile_options(wrap PRIVATE ${PUB_OPTS})
target_link_options(wrap PRIVATE ${PUB_LINK_OPTS})

add_executable(testexe main.cpp)
target_link_libraries(testexe wrap)