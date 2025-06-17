#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Solution.hpp"

namespace aoc::year2022::day3
{

int priority(char c)
{
	return std::islower(c) ? c - 'a' + 1 : c - 'A' + 27;
}

std::string Solution::part1(std::vector<std::string>& rucksacks)
{
    int total_priority = 0;
    for (const auto& rucksack : rucksacks)
    {
		auto first_compartment = rucksack.substr(0, rucksack.size() / 2);
		auto second_compartment = rucksack.substr(rucksack.size() / 2);

        auto common_element = first_compartment[first_compartment.find_first_of(second_compartment)];
        total_priority += priority(common_element);
    }

    return std::to_string(total_priority);
}
std::string Solution::part2(std::vector<std::string>& rucksacks)
{
    std::for_each(rucksacks.begin(), rucksacks.end(), [](auto& r) { sort(r.begin(), r.end()); });

    int total_priority = 0;
    for (unsigned i = 0; i < rucksacks.size(); i += 3)
    {
        std::string common_elements;
        std::set_intersection(rucksacks[i].begin(), rucksacks[i].end(),
            rucksacks[i + 1].begin(), rucksacks[i + 1].end(),
            std::back_inserter(common_elements));
        auto common_element = rucksacks[i+2][rucksacks[i+2].find_first_of(common_elements)];
        total_priority += priority(common_element);
    }

    return std::to_string(total_priority);
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