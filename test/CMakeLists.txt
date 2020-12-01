cmake_minimum_required(VERSION 3.15.0)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.h")

source_group("Source files" FILES ${sources}})
source_group("Header files" FILES ${headers})

add_executable(test ${sources} ${headers})

target_link_libraries(test PRIVATE advent2020 parsing gppUnit)
	
file(GLOB_RECURSE approved_files CONFIGURE_DEPENDS "*.approved.txt")
foreach(approved_file ${approved_files})
	configure_file(${approved_file} ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)
endforeach()
