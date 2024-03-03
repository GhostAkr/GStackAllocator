cmake_minimum_required(VERSION 3.28.3)
project(GStackAllocator VERSION 0.1.0 LANGUAGES C CXX)

set(HEADERS gstackallocator/gstackallocator.hpp)
set(SRC main.cpp)

add_executable(GStackAllocator ${SRC} ${HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
