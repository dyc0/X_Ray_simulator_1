cmake_minimum_required(VERSION 3.10)

project(XRAY_SIM VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(LIBRARY)
list(APPEND EXTRA_LIBS XRaySimulator)

add_executable(Util_test TESTS/utilities_test.cpp)

target_link_libraries(Util_test PUBLIC ${EXTRA_LIBS})

target_include_directories(Util_test PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )