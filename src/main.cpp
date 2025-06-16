#include <iostream>

// ToDo: depending on provided parameters run specific solutions
// aoc.exe --all		- all solutions
// aoc.exe <year>		- all solutions for specific year
// aoc.exe <year> <day>	- one solution
// aoc.exe				- interactive mode where user can provide year, day and input

int main(int argc, char *argv[]) {
	if (argc > 1) {
		std::cout << "Arguments provided: ";
		for (int i = 1; i < argc; ++i) {
			std::cout << argv[i] << " ";
		}
		std::cout << std::endl;
	} else {
		std::cout << "No arguments provided." << std::endl;
	}

	std::cout << "Hello, World!" << std::endl;
	return 0;
}