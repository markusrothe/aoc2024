#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <ranges>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <unordered_map>

int get_distance(std::vector<int>& left, std::vector<int>& right)
{
	std::ranges::sort(left);
	std::ranges::sort(right);
	auto sum = 0;
	for (auto const& [l, r] : std::views::zip(left, right))
	{
		sum += abs(l - r);
	}
	return sum;
}

TEST_CASE("AOC24_Day1_example_distance", "[day1]")
{
	std::vector left = {3, 4, 2, 1, 3, 3};
	std::vector right = {4, 3, 5, 3, 9, 3};

	REQUIRE(get_distance(left, right) == 11);
}

int get_similarity(std::vector<int> const& left, std::vector<int> const& right)
{
	std::unordered_map<int, std::pair<int, int>> map;
	for (auto const i : left)
	{
		map[i].first++;
	}

	for (auto const i : right)
	{
		map[i].second++;
	}

	int similarity{0};
	for (auto i = 0; i < map.size(); ++i)
	{
		auto const& [l, r] = map[i];
		similarity += i * l * r;
	}

	return similarity;
}

TEST_CASE("AOC24_Day1_example_similarity", "[day1]")
{
	std::vector const left = {3, 4, 2, 1, 3, 3};
	std::vector const right = {4, 3, 5, 3, 9, 3};

	REQUIRE(get_similarity(left, right) == 31);
}

TEST_CASE("AOC24_day1_input", "[day1]")
{
	std::ifstream ifs("day1_input");
	std::vector<int> left, right;
	int l, r;
	while (ifs >> l >> r)
	{
		left.push_back(l);
		right.push_back(r);
	}

	SECTION("get_distance for input")
	{
		std::cout << get_distance(left, right) << std::endl;
	}

	SECTION("get_similarity for input")
	{
		std::cout << get_similarity(left, right) << std::endl;
	}
}