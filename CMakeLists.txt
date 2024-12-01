cmake_minimum_required(VERSION 3.10)
project(AOC24)
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

fetchcontent_declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.4.0)

fetchcontent_makeavailable(
	Catch2)

add_executable(AOC main.cpp)

target_link_libraries(AOC
	PRIVATE
	Catch2::Catch2WithMain)

include(ctest)
include(catch)