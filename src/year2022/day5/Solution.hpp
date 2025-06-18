#pragma once

#include <istream>
#include <string>
#include <vector>
#include "../../include/Solution.hpp"

namespace aoc::year2022::day5
{

struct Crane_command
{
	int count;
	int from;
	int to;
};

struct Input_data
{
	std::vector<std::string> stacks{9};
	std::vector<Crane_command> commands;
};

class Solution : public aoc::Solution {
public:
	std::pair<std::string, std::string> solve(const std::string& input_file) override;
	std::string solve_part1(const std::string& input_file) override;
	std::string solve_part2(const std::string& input_file) override;
private:
	std::string part1(Input_data input);
	std::string part2(Input_data input);
};

}