#pragma once

#include <istream>
#include <string>
#include <vector>
#include "../../include/Solution.hpp"

namespace aoc::year2022::day7
{

struct Command {
	std::string command;
	std::vector<std::string> output;
};

class Solution : public aoc::Solution {
public:
	std::pair<std::string, std::string> solve(const std::string& input_file) override;
	std::string solve_part1(const std::string& input_file) override;
	std::string solve_part2(const std::string& input_file) override;
private:
	std::string part1(const std::vector<Command>& commands);
	std::string part2(const std::vector<Command>& commands);
};

}