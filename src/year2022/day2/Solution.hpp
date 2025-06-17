#pragma once

#include <string>
#include <vector>
#include "../../include/Solution.hpp"

namespace aoc::year2022::day2
{

class Solution : public aoc::Solution {
public:
	std::pair<std::string, std::string> solve(const std::string& input_file) override;
	std::string solve_part1(const std::string& input_file) override;
	std::string solve_part2(const std::string& input_file) override;
private:
	std::string part1(const std::vector<std::string> &input);
	std::string part2(const std::vector<std::string> &input);
};

}