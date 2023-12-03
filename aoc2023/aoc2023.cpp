#include "pch.h"


void puzzle_1_1();
void puzzle_1_2();
void puzzle_2_1();
void puzzle_2_2();
void puzzle_3_1();

int main(int argc, char** argv)
{
    constexpr std::pair<std::string_view, void(*)()> puzzles[] = {
        { "1.1", puzzle_1_1 },
        { "1.2", puzzle_1_2 },
        { "2.1", puzzle_2_1 },
        { "2.2", puzzle_2_2 },
        { "3.1", puzzle_3_1 },
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
