#include "pch.h"
#include <vector>
#include <map>
#include <cassert>

std::string trim(std::string_view str)
{
    auto first = std::find_if_not(str.begin(), str.end(), [](char c) { return std::isspace(c); });
    auto last = std::find_if_not(str.rbegin(), str.rend(), [](char c) { return std::isspace(c); }).base();
    return std::string(first, last);
}

std::vector<std::string> split(std::string_view str, std::string_view delim)
{
    std::vector<std::string> result;

    size_t pos = 0;
    while (pos < str.size())
    {
        auto next = str.find(delim, pos);
        if (next == std::string_view::npos)
        {
            result.emplace_back(trim(str.substr(pos)));
            break;
        }
        else
        {
            result.emplace_back(trim(str.substr(pos, next - pos)));
            pos = next + delim.size();
        }
    }

    return result;
}

void puzzle_2_1()
{
    std::ifstream input("aoc-input-02.txt");
    std::string line;

    int sumOfPossibleGames = 0;
    std::map<std::string, int> maxColors{
        { "red", 12 },
        { "green", 13 },
        { "blue", 14 },
    };

    while (std::getline(input, line))
    {
        // The lines are of the format:
        //
        // Game 31: 14 green, 1 blue, 8 red; 1 green, 2 blue; 1 green, 1 red, 1 blue
        // Game 43: 1 green, 18 red, 8 blue; 7 red, 4 green, 5 blue; 1 blue, 18 red; 5 red, 8 blue
        // Game 50: 9 red; 5 green, 2 blue, 10 red; 5 red, 1 green
        //
        // Split the line into the "Game NN" part and the rounds. Rounds are separated by ';'.
        auto game_and_rounds = split(line, ":");
        assert(game_and_rounds.size() == 2);

        int gameId = std::stoi(game_and_rounds[0].substr(5));
        int roundNumber = 1;
        bool tooManyCards = false;

        for (auto const& round : split(game_and_rounds[1], ";"))
        {
            for (auto const& colors : split(round, ","))
            {
                // Split the colors into the color and the number of cards.
                auto color_and_count = split(colors, " ");
                assert(color_and_count.size() == 2);
                auto color = color_and_count[1];
                auto count = std::stoi(color_and_count[0]);

                if (count > maxColors[color])
                {
                    std::cout << "Game " << gameId << " round " << roundNumber << " has too many " << color << " cards (" << count << ")" << std::endl;
                    tooManyCards = true;
                }
            }

            ++roundNumber;
        }

        if (!tooManyCards)
        {
            std::cout << "Game " << gameId << " is possible" << std::endl;
            sumOfPossibleGames += gameId;
        }
    }

    std::cout << "Sum of possible games: " << sumOfPossibleGames << std::endl;
}


void puzzle_2_2()
{
    std::ifstream input("aoc-input-02.txt");
    std::string line;
    int sumOfGamePowers = 0;

    while (std::getline(input, line))
    {
        // The lines are of the format:
        //
        // Game 31: 14 green, 1 blue, 8 red; 1 green, 2 blue; 1 green, 1 red, 1 blue
        // Game 43: 1 green, 18 red, 8 blue; 7 red, 4 green, 5 blue; 1 blue, 18 red; 5 red, 8 blue
        // Game 50: 9 red; 5 green, 2 blue, 10 red; 5 red, 1 green
        //
        // Split the line into the "Game NN" part and the rounds. Rounds are separated by ';'.
        auto game_and_rounds = split(line, ":");
        assert(game_and_rounds.size() == 2);

        std::map<std::string, int> minColors{
            { "red", 0 },
            { "green", 0 },
            { "blue", 0 },
        };

        int gameId = std::stoi(game_and_rounds[0].substr(5));

        for (auto const& round : split(game_and_rounds[1], ";"))
        {
            for (auto const& colors : split(round, ","))
            {
                // Split the colors into the color and the number of cards.
                auto color_and_count = split(colors, " ");
                assert(color_and_count.size() == 2);
                auto color = color_and_count[1];
                auto count = std::stoi(color_and_count[0]);
                
                minColors[color] = std::max(minColors[color], count);
            }
        }

        std::cout << "Game " << gameId << " has min colors: " << minColors["red"] << " red, " << minColors["green"] << " green, " << minColors["blue"] << " blue" << std::endl;

        sumOfGamePowers += minColors["red"] * minColors["green"] * minColors["blue"];
    }

    std::cout << "Sum of min powers: " << sumOfGamePowers << std::endl;
}