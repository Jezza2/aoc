#include <set>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    std::ifstream input(argv[1]);

    std::set<int> calorie_counts;

    std::string line;
    int calorie_count = 0;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            calorie_counts.insert(calorie_count);
            calorie_count = 0;
        }
        else
        {
            calorie_count += std::stoi(line);
        }
    }

    auto max_count_rit = calorie_counts.rbegin();
    std::cout << "Largest count: " << *max_count_rit << '\n';
    
    int top3 = 0;
    for (int i = 0; i < 3; ++i)
        top3 += *max_count_rit++;
    std::cout << "Top 3 counts: " << top3 << '\n';
}
