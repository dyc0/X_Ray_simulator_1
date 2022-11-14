add_library(XRaySimulator geometry.cpp utilities.cpp)

target_include_directories(XRaySimulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})