cmake_minimum_required(VERSION 3.10)

project(XRAY_SIM VERSION 1.0)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(DEBUGGING "Toggle debugging mode for symbol generation etc." ON)
option(ENABLE_TESTING "Choose whether to compile test files." ON)

if(DEBUGGING)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_11)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_subdirectory(LIBRARY)
list(APPEND XR_LIBS XRaySimulator)

if(ENABLE_TESTING)
  add_subdirectory(TESTS)
endif()