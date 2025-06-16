add_executable(aoc main.cpp "utility/FileReader.cpp")

target_include_directories(aoc PUBLIC utility)

add_subdirectory(year2022)
#add_subdirectory(year2023)
#add_subdirectory(year2024)
