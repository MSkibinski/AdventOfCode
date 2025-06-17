#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Solution.hpp"

namespace aoc::year2022::day4
{

std::string Solution::part1(std::vector<Assignment>& assignments)
{
    auto fully_contained = std::count_if(assignments.begin(), assignments.end(),
        [](const auto& assignment) {
            return (assignment.first.first <= assignment.second.first && assignment.first.second >= assignment.second.second) ||
                   (assignment.second.first <= assignment.first.first && assignment.second.second >= assignment.first.second);
		});

    return std::to_string(fully_contained);
}
std::string Solution::part2(std::vector<Assignment>& assignments)
{
    auto overlapping = std::count_if(assignments.begin(), assignments.end(),
        [](const auto& assignment) {
            return (assignment.first.first <= assignment.second.second && assignment.first.second >= assignment.second.first) ||
				   (assignment.second.first <= assignment.first.second && assignment.second.second >= assignment.first.first);
        });

    return std::to_string(overlapping);
}

//==============================================================================

std::istream& operator>> (std::istream& is, Assignment& a)
{
    char c;
    is >> a.first.first >> c >> a.first.second >> c >> a.second.first >> c >> a.second.second;
    return is;
}

std::vector<Assignment> parse(const std::string& input_file)
{
	std::ifstream file_stream(input_file);
    std::vector<Assignment> result;
    for(Assignment a; file_stream >> a;)
        result.push_back(a);

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