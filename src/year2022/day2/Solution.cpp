#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "Solution.hpp"

namespace aoc::year2022::day2
{

std::string Solution::part1(const std::vector<std::string>& input)
{
    const std::map<std::string, int> points{
        {"A X", 1 + 3},
        {"A Y", 2 + 6},
        {"A Z", 3 + 0},
        {"B X", 1 + 0},
        {"B Y", 2 + 3},
        {"B Z", 3 + 6},
        {"C X", 1 + 6},
        {"C Y", 2 + 0},
        {"C Z", 3 + 3},
    };

	int total_points = 0;
    for (const auto& round : input)
    {
		total_points += points.at(round);
    }
    return std::to_string(total_points);
}
std::string Solution::part2(const std::vector<std::string>& input)
{
    const std::map<std::string, int> points{
        {"A X", 3 + 0},
        {"A Y", 1 + 3},
        {"A Z", 2 + 6},
        {"B X", 1 + 0},
        {"B Y", 2 + 3},
        {"B Z", 3 + 6},
        {"C X", 2 + 0},
        {"C Y", 3 + 3},
        {"C Z", 1 + 6},
    };

    int total_points = 0;
    for (const auto& round : input)
    {
        total_points += points.at(round);
    }
    return std::to_string(total_points);
}

//==============================================================================

std::vector<std::string> parse(const std::string& input_file)
{
	std::ifstream file_stream(input_file);
    std::vector<std::string> result;
    std::string line;
    for (getline(file_stream, line); !line.empty(); getline(file_stream, line))
    {
        result.push_back(line);
    }
	return result;
}

std::pair<std::string, std::string> Solution::solve(const std::string& input_file)
{
	auto input = parse(input_file);
    return { part1(input), part2(input) };
}
std::string Solution::solve_part1(const std::string& input_file)
{
    auto input = parse(input_file);
    return part1(input);
}
std::string Solution::solve_part2(const std::string& input_file)
{
    auto input = parse(input_file);
    return part2(input);
}

}