#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <memory>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <ranges>

#include "Solution.hpp"

namespace aoc::year2022::day7
{

class FilesystemTree
{
public:
    struct Directory
    {
        unsigned size = 0;
        Directory* parent = nullptr;
        std::map<std::string, std::unique_ptr<Directory>> children;
        std::map<std::string, unsigned> files;
    };

    FilesystemTree() : root(new Directory()) {}
    Directory* get_root() const { return root.get(); }

    // Forward iterator (preorder traversal)
    class Iterator {
    public:
        using value_type = Directory;
        using pointer = Directory*;
        using reference = Directory&;

        Iterator() = default;
        explicit Iterator(pointer root) {
            if (root) stack.emplace_back(root);
        }

        reference operator*() const { return *stack.back(); }
        pointer operator->() const { return stack.back(); }

        Iterator& operator++() {
            pointer current = stack.back();
            stack.pop_back();
            // Dodaj dzieci w odwrotnej kolejnoœci, aby pierwszy by³ na górze stosu
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                stack.push_back(it->second.get());
            }
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return stack == other.stack;
        }
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        std::vector<pointer> stack;
    };

    Iterator begin() const { return Iterator(root.get()); }
    Iterator end() const { return Iterator(); }

private:
    std::unique_ptr<Directory> root;
};

void build_filesystem_tree(FilesystemTree& tree, const std::vector<Command>& commands)
{
    using Directory = FilesystemTree::Directory;
    Directory* current = tree.get_root();

    for (const auto& cmd : commands) {
        if (cmd.command.substr(0, 2) == "cd") {
            std::string arg = cmd.command.substr(3);
            if (arg == "/") {
                current = tree.get_root();
            }
            else if (arg == "..") {
                if (current->parent) current = current->parent;
            }
            else {
                if (current->children.count(arg) == 0) {
                    auto dir = std::make_unique<Directory>();
                    dir->parent = current;
                    current->children[arg] = std::move(dir);
                }
                current = current->children[arg].get();
            }
        }
        else if (cmd.command == "ls") {
            for (const auto& line : cmd.output) {
                if (line.substr(0, 4) == "dir ") {
                    std::string dirname = line.substr(4);
                    if (current->children.count(dirname) == 0) {
                        auto dir = std::make_unique<Directory>();
                        dir->parent = current;
                        current->children[dirname] = std::move(dir);
                    }
                }
                else {
                    std::string file_name;
					unsigned file_size;
                    std::stringstream ss(line);
					ss >> file_size >> file_name;
                    current->files[file_name] = file_size;
                }
            }
        }
    }
}

unsigned calculate_size(FilesystemTree::Directory* dir)
{
    for (auto& [child_name, child_dir] : dir->children)
        dir->size += calculate_size(child_dir.get());
    for (const auto& [file_name, file_size] : dir->files)
        dir->size += file_size;
	return dir->size;
}

//==============================================================================

std::string Solution::part1(const std::vector<Command>& commands)
{
    FilesystemTree fs_tree;
	build_filesystem_tree(fs_tree, commands);
	calculate_size(fs_tree.get_root());

    return std::to_string(
        std::accumulate(fs_tree.begin(), fs_tree.end(), 0u, [](unsigned acc, const FilesystemTree::Directory& dir) {
            return acc + (dir.size <= 100000 ? dir.size : 0);
        }));
}
std::string Solution::part2(const std::vector<Command>& commands)
{
    FilesystemTree fs_tree;
    build_filesystem_tree(fs_tree, commands);
    calculate_size(fs_tree.get_root());
	auto space_needed = 30000000 - (70000000 - fs_tree.get_root()->size);

	/*auto filtered = fs_tree | std::views::filter([space_needed](const FilesystemTree::Directory& dir) {
            return dir.size >= space_needed;
        });

    auto min_size = std::ranges::min_element(filtered, {}, [](const FilesystemTree::Directory& dir) {
            return dir.size;
        });*/
	auto min_size = std::numeric_limits<unsigned>::max();
    for (const auto& dir : fs_tree) {
        if (dir.size >= space_needed)
            min_size = std::min(min_size, dir.size);
	}

    return std::to_string(min_size);
}

//==============================================================================

std::vector<Command> parse(const std::string& input_file)
{
    std::ifstream file_stream(input_file);

    std::vector<Command> out;

    for (std::string line; getline(file_stream, line);)
    {
        if (line[0] == '$')
        {
            out.push_back(Command{ line.substr(2), std::vector<std::string>{} });
        }
        else
        {
            out.back().output.emplace_back(line);
        }
    }
    return out;
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