#pragma once

#include <istream>
#include <string>
#include <vector>
#include "../../include/Solution.hpp"

namespace aoc::year2022::day4
{

using Range = std::pair<int, int>;
using Assignment = std::pair<Range, Range>;

class Solution : public aoc::Solution {
public:
	std::pair<std::string, std::string> solve(const std::string& input_file) override;
	std::string solve_part1(const std::string& input_file) override;
	std::string solve_part2(const std::string& input_file) override;
private:
	std::string part1(std::vector<Assignment>& rucksacks);
	std::string part2(std::vector<Assignment>& rucksacks);
};

}