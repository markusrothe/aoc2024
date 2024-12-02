cmake_minimum_required(VERSION 3.10)
project(AOC24)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

include(FetchContent)

fetchcontent_declare(Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.4.0)

fetchcontent_makeavailable(Catch2)

add_executable(AOC
	src/day_one.cpp
	src/day_two.cpp)

target_link_libraries(AOC
	PRIVATE
	Catch2::Catch2WithMain)

target_include_directories(AOC
	PRIVATE
	src)

include(ctest)
include(catch)

install(TARGETS AOC DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/input/ DESTINATION bin)