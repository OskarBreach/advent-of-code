cmake_minimum_required(VERSION 3.15.0)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.h")

source_group("Source files" FILES ${sources}})
source_group("Header files" FILES ${headers})

add_library(advent2020 ${sources} ${headers})

target_link_libraries(advent2020)
target_include_directories(advent2020 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
