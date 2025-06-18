#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

#include "Solution.hpp"

namespace aoc::year2022::day5
{

std::string concatenate_top_elements(const std::vector<std::string>& stacks)
{
    return std::accumulate(stacks.begin(), stacks.end(), std::string(),
        [](const std::string& acc, const std::string& stack) {
            return acc + (stack.empty() ? "" : std::string{ stack.back() });
        });
}

std::string Solution::part1(Input_data input)
{
    for(const auto& command : input.commands)
    {
        auto& from_stack = input.stacks[command.from - 1];
        auto& to_stack = input.stacks[command.to - 1];
		to_stack.insert(to_stack.end(), from_stack.rbegin(), from_stack.rbegin() + command.count);
		from_stack.erase(from_stack.end() - command.count, from_stack.end());
	}

    return concatenate_top_elements(input.stacks);
}
std::string Solution::part2(Input_data input)
{
    for (const auto& command : input.commands)
    {
        auto& from_stack = input.stacks[command.from - 1];
        auto& to_stack = input.stacks[command.to - 1];
        to_stack.insert(to_stack.end(), from_stack.end() - command.count, from_stack.end());
        from_stack.erase(from_stack.end() - command.count, from_stack.end());
    }

    return concatenate_top_elements(input.stacks);
}

//==============================================================================

std::istream& operator>> (std::istream& is, Crane_command& command)
{
    std::string s;
    is >> s >> command.count >> s >> command.from >> s >> command.to;
    return is;
}

Input_data parse(const std::string& input_file)
{
	std::ifstream file_stream(input_file);
    Input_data result;

    std::string line;
    for (getline(file_stream, line); !isdigit(line[1]); getline(file_stream, line))
    {
        for (unsigned i = 1, j = 0; i < line.size(); i += 4, j++)
            if (line[i] != ' ')
                result.stacks[j].push_back(line[i]);
    }
    for (auto& stack : result.stacks)
		std::reverse(stack.begin(), stack.end()); // Reverse each stack to have the top item at the end of the stack

	getline(file_stream, line); // Skip the empty line after the stacks definition

    for(Crane_command c; file_stream >> c;)
        result.commands.push_back(c);

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