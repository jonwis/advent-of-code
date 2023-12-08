#include "pch.h"
#include <regex>
#include <set>

// https://adventofcode.com/2023/day/4
//
// The input file format looks like this:
//
// Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
// Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
// Card 3: 1 21 53 59 44 | 69 82 63 72 16 21 14  1
// Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
// Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
// Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11

std::set<int> split_to_set(std::string const& src)
{
    std::set<int> result;
    std::stringstream ss(src);
    while (!ss.eof())
    {
        int a;
        ss >> a;
        result.insert(a);
    }

    return result;
}

void puzzle_4_1()
{
    std::ifstream input("aoc-input-04.txt");
    auto pat = std::regex(R"(Card\s+(\d+): (.*) \| (.*))");
    int total = 0;

    std::string line;
    while (std::getline(input, line))
    {
        std::smatch m;
        if (!std::regex_match(line, m, pat))
        {
            throw std::invalid_argument(line.c_str());
        }

        int card = std::stoi(m[1]);
        uint32_t cardValue = 0;
        auto winning = split_to_set(m[2]);
        for (auto const &has : split_to_set(m[3]))
        {
            if (winning.contains(has))
            {
                cardValue = (cardValue == 0) ? 1 : (cardValue * 2);
            }
        }

        std::cout << "Card " << card << " value " << cardValue << std::endl;
        total += cardValue;
    }

    std::cout << "Total value " << total << std::endl;
}