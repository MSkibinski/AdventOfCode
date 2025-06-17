#include <iostream>
#include "Solution.hpp"

int main(int argc, char* argv[])
{  
    std::string input_file{};
    if (argc == 1)
    {
		input_file = "../day4/input.txt";
	}
    else if (argc == 2)
    {
		input_file = argv[1];
	}
    else 
    {
		std::cerr << "Incorrect number of arguments. Usage: " << argv[0] << " [input_file]" << std::endl;
        return 1;
    }

    aoc::year2022::day4::Solution solution;
	auto result = solution.solve(input_file);
	std::cout << "Part 1: " << result.first << std::endl;
    std::cout << "Part 2: " << result.second << std::endl;
}