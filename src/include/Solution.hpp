#pragma once

#include <string>

namespace aoc
{

class Solution {
public:
	virtual std::pair<std::string, std::string> solve(const std::string& input_file) = 0;
	virtual std::string solve_part1(const std::string& input_file) = 0;
	virtual std::string solve_part2(const std::string& input_file) = 0;
};

}