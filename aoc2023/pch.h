#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <algorithm>

inline void check_bool(bool b)
{
    if (!b)
    {
        throw std::runtime_error("Failed");
    }
}
