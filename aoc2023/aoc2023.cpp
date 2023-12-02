// aoc2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

void puzzle_1()
{
    std::ifstream input("aoc-input-01.txt", std::ios::in);
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open input file");
    }

    // The input stream consists of a list of strings, one per line, like "f4dxxx7r" or "fthree5g7".
    // This method reads each line and find the first and last single digit in each line, converting
    // them into a two-digit number. The sum of all these numbers is the answer.
    int sum = 0;
    std::string line;
    std::string_view numbers{"0123456789"};
    while (std::getline(input, line))
    {
        auto first = line.find_first_of(numbers);
        auto last = line.find_last_of(numbers);
        if (first != std::string::npos && last != std::string::npos)
        {
            sum += (line[first] - '0') * 10 + (line[last] - '0');
        }
    }

    std::cout << sum;
}

int main(int argc, char** argv)
{
    constexpr std::pair<std::string_view, void(*)()> puzzles[] = {
        { "1", puzzle_1 },
    };

    if (argc < 2)
    {
        for (auto& [puzzle, func] : puzzles)
        {
            std::cout << "Puzzle " << puzzle << std::endl;
            func();
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }
    else
    {
        for (const auto& puzzle : puzzles)
        {
            if (puzzle.first == argv[1])
            {
                puzzle.second();
                return 0;
            }
        }
    }
}
