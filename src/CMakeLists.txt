cmake_minimum_required(VERSION 3.15.0)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.h")
file(COPY "inputs/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(src ${sources} ${headers})

target_link_libraries(src PRIVATE advent2020 parsing)
