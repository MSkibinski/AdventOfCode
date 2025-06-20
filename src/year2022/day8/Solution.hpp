#pragma once

#include <istream>
#include <string>
#include <vector>
#include "../../include/Solution.hpp"

namespace aoc::year2022::day8
{

using Matrix = std::vector<std::string>;

class Solution : public aoc::Solution {
public:
	std::pair<std::string, std::string> solve(const std::string& input_file) override;
	std::string solve_part1(const std::string& input_file) override;
	std::string solve_part2(const std::string& input_file) override;
private:
	std::string part1(const Matrix& map_of_trees);
	std::string part2(const Matrix& map_of_trees);
};

}