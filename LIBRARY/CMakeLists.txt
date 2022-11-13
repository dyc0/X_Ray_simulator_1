add_library(XRaySimulator INTERFACE geometry.hpp utilities.hpp)

target_include_directories(XRaySimulator INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})