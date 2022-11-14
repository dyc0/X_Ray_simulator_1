add_library(XRaySimulator geometry.cpp tube.cpp utilities.cpp logic.cpp)

target_include_directories(XRaySimulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})