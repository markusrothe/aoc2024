#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>

bool is_safe(std::vector<int> const& report)
{
	std::optional<bool> descending = std::nullopt;
	for (auto i = 0; i < report.size() - 1; ++i)
	{
		auto const first = report[i];
		auto const second = report[i + 1];

		if (!descending.has_value())
		{
			descending = second < first;
		}
		else if (*descending != second < first)
		{
			return false;
		}

		auto const diff = abs(first - second);
		if (diff < 1 || diff > 3)
		{
			return false;
		}
	}
	return true;
}

int get_number_of_safe_reports(std::vector<std::vector<int>> const& reports, bool dampened)
{
	return static_cast<int>(std::ranges::count_if(reports, [&](auto const& report) {
		if (is_safe(report))
		{
			return true;
		}

		if (dampened)
		{
			for (auto i = 0; i < report.size(); ++i)
			{
				std::vector<int> reduced;
				for (auto j = 0; j < report.size(); ++j)
				{
					if (i != j)
					{
						reduced.push_back(report[j]);
					}
				}

				if (is_safe(reduced))
				{
					return true;
				}
			}
		}

		return false;
	}));
}

TEST_CASE("AOC24_Day2_example_num_safe_reports", "[day2]")
{
	std::vector<std::vector<int>> const input = {
		{7, 6, 4, 2, 1},
		{1, 2, 7, 8, 9},
		{9, 7, 6, 2, 1},
		{1, 3, 2, 4, 5},
		{8, 6, 4, 4, 1},
		{1, 3, 6, 7, 9}};

	REQUIRE(get_number_of_safe_reports(input, false) == 2);
	REQUIRE(get_number_of_safe_reports(input, true) == 4);
}

TEST_CASE("AOC24_Day2_input_num_safe_reports", "[day2]")
{
	std::ifstream ifs("day2_input");
	std::vector<std::vector<int>> reports;
	std::string line;
	while (std::getline(ifs, line))
	{
		std::vector<int> report;
		std::istringstream iss{line};
		int val;
		while (iss >> val)
		{
			report.push_back(val);
		}
		if (!report.empty())
		{
			reports.emplace_back(std::move(report));
		}
	}

	std::cout << "part1 " << get_number_of_safe_reports(reports, false) << std::endl;
	std::cout << "part2 " << get_number_of_safe_reports(reports, true) << std::endl;
}