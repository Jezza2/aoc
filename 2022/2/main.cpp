#include <fstream>
#include <iostream>

// There must be some fancy modular arithmetic you can do here, but this
// does work

namespace s1
{

int opponent_score(char c)
{
    return c - 'A' + 1;
}

int my_score(char c)
{
    return c - 'X' + 1;
}

// Boring, obvious solution
int round_score(char opponent_play, char my_play)
{
    if (opponent_score(opponent_play) == my_score(my_play))
        return 3;

    if (opponent_play == 'A' && my_play == 'Y')
        return 6;
    if (opponent_play == 'B' && my_play == 'Z')
        return 6;
    if (opponent_play == 'C' && my_play == 'X')
        return 6;
    
    return 0;
}

int score(const char* input_filename)
{
    std::ifstream input(input_filename);

    std::string line;
    int score = 0;
    while (std::getline(input, line))
    {
        const char opponent_play = line.at(0);
        const char my_play = line.at(2);
        score += round_score(opponent_play, my_play) + my_score(my_play);
    }

    return score;
}

}

namespace s2
{

int round_score(char result)
{
    return (result - 'X') * 3;
}

char my_play(char opponent_play, char result)
{
    // lose
    if (result == 'X')
    {
        switch (opponent_play)
        {
        case 'A': return 'C';
        case 'B': return 'A';
        case 'C': return 'B';
        }
    }
    // Win
    else if (result == 'Z')
    {
        switch (opponent_play)
        {
        case 'A': return 'B';
        case 'B': return 'C';
        case 'C': return 'A';
        }
    }
    // Draw
    return opponent_play;
}

int my_score(char c)
{
    return c - 'A' + 1;
}

int score(const char* input_filename)
{
    std::ifstream input(input_filename);

    std::string line;
    int score = 0;
    while (std::getline(input, line))
    {
        const char opponent_play = line.at(0);
        const char result = line.at(2);
        score += round_score(result) + my_score(my_play(opponent_play, result));
    }

    return score;
}

}

int main(int argc, char *argv[])
{
    std::cout << "Score 1: " << s1::score(argv[1]) << '\n';
    std::cout << "Score 2: " << s2::score(argv[1]) << '\n';
}
