#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

#include "Solution.hpp"


namespace aoc::year2022::day8
{

void check_visibility(char tree,  int& highest_tree, char& is_visible)
{
    if (tree > highest_tree) {
        is_visible = 1;
        highest_tree = tree;
    }
}

//==============================================================================

std::string Solution::part1(const Matrix& map_of_trees)
{
	std::vector<std::vector<char>> visible_trees(map_of_trees.size(), std::vector<char>(map_of_trees[0].size(), 0));

    for (int row = 0; row < map_of_trees.size(); row++) {
        for (int col = 0, highest_tree=-1; col < map_of_trees[row].size(); col++)
            check_visibility(map_of_trees[row][col], highest_tree, visible_trees[row][col]);
		for (int col = map_of_trees[row].size() - 1, highest_tree = -1; col >= 0; col--)
            check_visibility(map_of_trees[row][col], highest_tree, visible_trees[row][col]);
    }

    for (int col = 0; col < map_of_trees[0].size(); col++) {
        for (int row = 0, highest_tree = -1; row < map_of_trees.size(); row++)
			check_visibility(map_of_trees[row][col], highest_tree, visible_trees[row][col]);
		for (int row = map_of_trees.size() - 1, highest_tree = -1; row >= 0; row--)
            check_visibility(map_of_trees[row][col], highest_tree, visible_trees[row][col]);
	}
    
    return std::to_string(std::accumulate(visible_trees.begin(), visible_trees.end(), 0, [](int sum, const std::vector<char>& row) {
        return sum + std::count(row.begin(), row.end(), 1);
    }));
}
std::string Solution::part2(const Matrix& map_of_trees)
{
	int best_scenic_score = 0;
    for (int row = 1; row < map_of_trees.size()-1; row++) {
        for (int col = 1; col < map_of_trees[row].size()-1; col++) {
            int tree = map_of_trees[row][col];
            int left = 1, right = 1, up = 1, down = 1;
            for (int c = col - 1; c > 0 && map_of_trees[row][c] < tree; c--)
                left++;
            for (int c = col + 1; c < map_of_trees[row].size()-1 && map_of_trees[row][c] < tree; c++)
                right++;
            for (int r = row - 1; r > 0 && map_of_trees[r][col] < tree; r--)
                up++;
            for (int r = row + 1; r < map_of_trees.size()-1 && map_of_trees[r][col] < tree; r++)
                down++;
            int scenic_score = left  * right * up * down;
            best_scenic_score = std::max(best_scenic_score, scenic_score);
        }
    }
	return std::to_string(best_scenic_score);
}

//==============================================================================

Matrix parse(const std::string& input_file)
{
    std::ifstream file_stream(input_file);

    Matrix m;
    for (std::string line; getline(file_stream, line);)
    {
        m.push_back(line);
    }
    return m;
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