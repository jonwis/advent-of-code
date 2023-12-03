#include "pch.h"
#include <vector>
#include <format>

// The format of the input file looks like this:
//
// 467..114..
// ...*......
// ..35..633.
// ......#...
// 617*......
// .....+.58.
// ..592.....
// ......755.
// ...$.*....
// .664.598..
//
// A run of numbers is a "part number". A dot is an empty cell. Anything else is a "symbol".
// The goal is to find the sum of all part numbers that are adjacent to a symbol, even diagonally.

bool is_part_marker(char ch)
{
    return !(std::isdigit(ch) || (ch == '.'));
}

std::vector<std::string> load_map_content(std::string const& fileName)
{
    std::ifstream inputFile(fileName);

    std::string line;
    std::vector<std::string> mapContent;
    size_t maxMapLineLength = 0;

    while (std::getline(inputFile, line))
    {
        line = '.' + line + '.';
        maxMapLineLength = std::max(maxMapLineLength, line.size());
        mapContent.emplace_back(line);
    }

    // Reprocess the map; ensure it's rectangular off the right edge by padding it out.
    for (auto& l : mapContent)
    {
        l += std::string(maxMapLineLength - l.size(), '.');
    }

    // Add two new padding lines full of space markers
    mapContent.insert(mapContent.begin(), std::string(maxMapLineLength, '.'));
    mapContent.insert(mapContent.end(), std::string(maxMapLineLength, '.'));

    return mapContent;
}

bool has_surrounding_part_marker(std::vector<std::string> const& map, int row, int col)
{
    for (int r = row - 1; r <= row + 1; ++r)
    {
        for (int c = col - 1; c <= col + 1; ++c)
        {
            if (is_part_marker(map[r][c]))
            {
                return true;
            }
        }
    }

    return false;
}

void puzzle_3_1()
{
    auto mapContent = load_map_content("aoc-input-03.txt");

    // Walk the map content row by row. When we start seeing a number, set a flag that
    // we're processing a number. Look around numbers and see if there's a part marker
    // around it. Set a flag if so. When we stop finding numbers, if the part marker
    // is set, accumulate it into the sum.
    int partIdsTotal = 0;
    for (int row = 0; row < mapContent.size(); ++row)
    {
        int currentPartId = 0;
        bool inPartId = false;
        bool sawPartMarker = false;
        for (int col = 0; col < mapContent[row].size(); ++col)
        {
            const auto ch = mapContent[row][col];

            if (std::isdigit(ch))
            {
                inPartId = true;
                sawPartMarker |= has_surrounding_part_marker(mapContent, row, col);
                currentPartId = currentPartId * 10 + (ch - '0');
            }
            else
            {
                // No longer in a number. Finish up.
                if (inPartId)
                {
                    std::cout << std::format("[{},{}] - ID {} part-marker {}", row, col, currentPartId, sawPartMarker) << std::endl;

                    if (sawPartMarker)
                    {
                        partIdsTotal += currentPartId;
                    }
                }

                inPartId = false;
                sawPartMarker = false;
                currentPartId = 0;
            }
        }
    }

    std::cout << "Total of parts' IDs: " << partIdsTotal << std::endl;
}