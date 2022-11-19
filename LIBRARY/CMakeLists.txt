add_library(XRaySimulator utilities.cpp tube.cpp geometry.cpp logic.cpp)

target_include_directories(XRaySimulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})