#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include "Solution.hpp"

namespace aoc::year2022::day1
{

std::vector<int> accumulate_groups(const std::vector<std::vector<int>>& input)
{
    std::vector<int> result;
    result.reserve(input.size());

    for (const auto& group : input)
    {
        result.push_back(std::accumulate(group.begin(), group.end(), 0));
    }
    return result;
}

std::string Solution::part1(const std::vector<std::vector<int>>& input)
{
    auto calories_carried = accumulate_groups(input);
    return std::to_string(
        *std::max_element(calories_carried.begin(), calories_carried.end())
    );
}
std::string Solution::part2(const std::vector<std::vector<int>>& input)
{
    auto calories_carried = accumulate_groups(input);
    const int nth = 3;
    std::nth_element(calories_carried.begin(), calories_carried.begin() + (nth - 1), calories_carried.end(), std::greater{});
    return std::to_string(
        std::accumulate(calories_carried.begin(), calories_carried.begin() + nth, 0)
    );
}

//==============================================================================

std::vector<std::vector<int>> parse(const std::string& input_file)
{
	std::ifstream file_stream(input_file);
    std::vector<std::vector<int>> result;
	std::vector<int> single_group;
    std::string line;
    while (std::getline(file_stream, line))
    {
        if (!line.empty())
        {
            single_group.push_back(std::stoi(line));
        }
        else
        {
            result.push_back(single_group);
            single_group.clear();
		}
    }
    if (!single_group.empty())
    {
        result.push_back(single_group);
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