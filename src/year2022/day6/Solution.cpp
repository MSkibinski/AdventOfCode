#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

#include "Solution.hpp"

namespace aoc::year2022::day6
{

unsigned find_sequence_without_repeats(const std::string& input, int to_find)
{
    int letter_count[26] = {};
    unsigned different_letters = 0;
    auto start_of_sequence = input.begin();
    auto end_of_sequence = input.begin();

    for (; end_of_sequence-input.begin() < to_find; end_of_sequence++)
        if (++letter_count[*end_of_sequence - 'a'] == 1)
            different_letters++;

    for (; different_letters != to_find; start_of_sequence++, end_of_sequence++)
    {
        if (--letter_count[*start_of_sequence - 'a'] == 0)
            different_letters--;
        if (++letter_count[*end_of_sequence - 'a'] == 1)
            different_letters++;
    }
    return end_of_sequence - input.begin();
}

std::string Solution::part1(const std::string& input)
{
    return std::to_string(find_sequence_without_repeats(input, 4));
}
std::string Solution::part2(const std::string& input)
{
    return std::to_string(find_sequence_without_repeats(input, 14));
}

//==============================================================================

std::string parse(const std::string& input_file)
{
	std::ifstream file_stream(input_file);
    std::string line;
    getline(file_stream, line);
    return line;
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