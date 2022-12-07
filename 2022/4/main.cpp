#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>

using rpair_t = std::pair<int, int>;

std::pair<rpair_t, rpair_t> parse_line(const std::string& line)
{
    const auto middle_idx = line.find(',');
    const auto first_dash_idx = line.find('-');
    const auto second_dash_idx = line.find('-', middle_idx);

    return {
        {
            std::stoi(line.substr(0, first_dash_idx)),
            std::stoi(line.substr(first_dash_idx + 1, middle_idx))
        },{
            std::stoi(line.substr(middle_idx + 1, second_dash_idx)),
            std::stoi(line.substr(second_dash_idx + 1))
        }
    };
}

int range_size(const rpair_t& a)
{
    return a.second - a.first + 1;
}

std::set<int> combine_ranges(const rpair_t& a, const rpair_t& b)
{
    std::set<int> ret;
    
    for (int i = a.first; i <= a.second; ++i)
        ret.insert(i);
    
    for (int i = b.first; i <= b.second; ++i)
        ret.insert(i);
    
    return ret;
}

bool inclusive_range(const rpair_t& a, const rpair_t& b)
{
    const auto combined = combine_ranges(a, b);
    const int asize = range_size(a);
    const int bsize = range_size(b);
    return combined.size() == std::max(asize, bsize);
}

bool overlapping_range(const rpair_t& a, const rpair_t& b)
{
    const auto combined = combine_ranges(a, b);
    const int asize = range_size(a);
    const int bsize = range_size(b);
    return combined.size() < asize + bsize;
}

int count_inclusive_ranges(const char* input_filename)
{
    std::ifstream input(input_filename);
    std::string line;
    std::size_t count = 0;
    while (std::getline(input, line))
    {
        const auto ranges = parse_line(line);
        if (inclusive_range(ranges.first, ranges.second))
            ++count;
    }

    return count;
}

int count_overlapping_ranges(const char* input_filename)
{
    std::ifstream input(input_filename);
    std::string line;
    std::size_t count = 0;
    while (std::getline(input, line))
    {
        const auto ranges = parse_line(line);
        if (overlapping_range(ranges.first, ranges.second)
                || inclusive_range(ranges.first, ranges.second))
            ++count;
    }

    return count;
}

int main(int argc, char *argv[])
{
    std::cout << count_inclusive_ranges(argv[1]) << '\n';
    std::cout << count_overlapping_ranges(argv[1]) << '\n';
}