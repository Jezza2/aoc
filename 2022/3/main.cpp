#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <cstddef>

int priority(char c)
{
    if (c >= 'a')
        return c - 'a' + 1;
    else
        return c - 'A' + 27;
}

std::string common_chars(std::string a, std::string b)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    
    std::string intersection;
    std::set_intersection(
            a.begin(), a.end(),
            b.begin(), b.end(),
            std::back_inserter(intersection));
    
    return intersection;
}

char common_char(std::string a, std::string b)
{
    const std::string intersection = common_chars(a, b);
    std::set<char> unique_intersection(intersection.begin(), intersection.end());

    if (unique_intersection.size() != 1)
    {
        std::cerr << "Bad line: " << intersection.size() << " common types\n";
        abort();
    }

    return *unique_intersection.begin();
}

char badge_type(std::string a, std::string b, std::string c)
{
    const std::string ab_intersection = common_chars(a, b);
    const std::string intersection = common_chars(ab_intersection, c);
    std::set<char> unique_intersection(intersection.begin(), intersection.end());

    if (unique_intersection.size() != 1)
    {
        std::cerr << "Bad triple: " << intersection.size() << " common types\n";
        abort();
    }

    return *unique_intersection.begin();
}

std::pair<std::string, std::string> split_string(const std::string& str)
{
    const std::size_t mid_point = str.size() / 2;

    if (mid_point * 2 != str.size())
    {
        std::cerr << "Bad line: odd number of items\n";
        abort();
    }

    return {
            str.substr(0, mid_point),
            str.substr(mid_point)
    };
}

int misplaced_priorities(const char* input_filename)
{
    std::ifstream input(input_filename);
    std::string line;
    int prisum = 0;
    while (std::getline(input, line))
    {
        const auto compartments = split_string(line);
        const char common_type = common_char(compartments.first, compartments.second);
        prisum += priority(common_type);
    }

    return prisum;
}

int badge_priorities(const char* input_filename)
{
    std::ifstream input(input_filename);
    std::string line;
    int prisum = 0;
    while (input)
    {
        std::string a, b, c;
        if (!std::getline(input, a)) break;
        if (!std::getline(input, b)) break;
        if (!std::getline(input, c)) break;
        const char btype = badge_type(a, b, c);
        prisum += priority(btype);
    }

    return prisum;
}

int main(int argc, char* argv[])
{
    std::cout << "Misplaced priorities: " << misplaced_priorities(argv[1]) << '\n';
    std::cout << "Badge priorities: " << badge_priorities(argv[1]) << '\n';
}