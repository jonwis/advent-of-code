// aoc2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <algorithm>

void check_bool(bool b)
{
    if (!b)
    {
        throw std::runtime_error("Failed");
    }
}

std::pair<int, int> p1_number_pair(std::string_view v)
{
    auto first = v.find_first_of("0123456789");
    auto last = v.find_last_of("0123456789");
    if (first == std::string::npos || last == std::string::npos)
    {
        throw std::runtime_error("Could not find number in string");
    }

    return { v[first] - '0', v[last] - '0' };
}

void puzzle_1_1()
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
    while (std::getline(input, line))
    {
        auto [first, last] = p1_number_pair(line);
        std::cout << line << ": " << first << last << std::endl;
        sum += first * 10 + last;
    }

    std::cout << "Puzzle 1.1 answer: " << sum << std::endl;
}

std::string replace_digit_names(std::string_view src)
{
    constexpr std::pair<std::string_view, std::string_view> replacements[] =
    {
        { "one", "1" },
        { "two", "2" },
        { "three", "3" },
        { "four", "4" },
        { "five", "5"},
        { "six", "6"},
        { "seven", "7"},
        { "eight", "8"},
        { "nine", "9"},
    };

    std::string output;

    while (!src.empty())
    {
        // If the prefix of the string matches one of the replacements, replace _just_ the first
        // character with the digit value, then move on. That way, the string "twoneight" will
        // be replaced with "2w1n8ight" instead of "2n8", for instance.
        bool replaced = false;
        for (auto [from, to] : replacements)
        {
            if (src.starts_with(from))
            {
                output.append(to);
                src.remove_prefix(1);
                replaced = true;
            }
        }

        if (replaced)
        {
            continue;
        }

        // If we didn't replace anything, just copy the first character and move on.
        if (!src.empty())
        {
            output.append(src.substr(0, 1));
            src.remove_prefix(1);
        }
    }

    return output;
}

void puzzle_1_2()
{
    std::ifstream input("aoc-input-01.txt", std::ios::in);
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open input file");
    }

    // Tests from the problem description
    constexpr std::pair<std::string_view, std::pair<int, int>> testCases[] =
    {
        { "two1nine", { 2, 9 } },
        { "eightwothree", { 8, 3 } },
        { "abcone2threexyz", { 1, 3 } },
        { "xtwone3four", { 2, 4 } },
        { "4nineeightseven2", { 4, 2 } },
        { "zoneight234", { 1, 4 } },
        { "7pqrstsixteen", { 7, 6 } },
    };

    // Turns out that "twoneight" is a valid input, and should produce the output "218"
    check_bool(replace_digit_names("twoneight") == "2w1n8ight");

    int testSum = 0;
    for (auto [input, expected] : testCases)
    {
        auto [first, last] = p1_number_pair(replace_digit_names(input));
        std::cout << input << ": " << first << last << std::boolalpha << (std::pair{first, last} == expected) << std::endl;
        testSum += first * 10 + last;
    }
    check_bool(testSum == 281);

    // The input stream consists of a list of strings, one per line, like "f4dxxx7r" or "fthree5g7".
    // This method reads each line and find the first and last single digit in each line, converting
    // them into a two-digit number. This time, turn strings like "two" into the value "2" before finding
    // the first and last digits. The sum of all these numbers is the answer.
    int sum = 0;
    std::string line;
    std::string_view numbers{ "0123456789" };
    while (std::getline(input, line))
    {
        auto [first, last] = p1_number_pair(replace_digit_names(line));
        std::cout << line << ": " << first << last << std::endl;
        sum += first * 10 + last;
    }

    std::cout << "Puzzle 1.2 answer: " << sum;
}

int main(int argc, char** argv)
{
    constexpr std::pair<std::string_view, void(*)()> puzzles[] = {
        { "1", puzzle_1_1 },
        { "2", puzzle_1_2 },
    };

    for (auto& [puzzle, func] : puzzles)
    {
        if ((argc > 1) && (puzzle != argv[1]))
        {
            continue;
        }

        std::cout << "Puzzle " << puzzle << std::endl;
        func();
        std::cout << std::endl;
        std::cout << std::endl;
    }
}
