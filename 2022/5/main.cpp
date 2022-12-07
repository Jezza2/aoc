#include <vector>
#include <fstream>
#include <numeric>
#include <iostream>
#include <algorithm>

class stack
{
public:
    // Push on in reverse order
    void push(std::vector<char> s)
    {
        for (char c : s)
            push(c);
    }

    void push(char c)
    {
        _s.push_back(c);
    }

    char pop()
    {
        const char ret = _s.back();
        _s.pop_back();
        return ret;
    }

    std::vector<char> pop(int count)
    {
        std::vector<char> ret;
        while (count-- > 0)
            ret.push_back(pop());
        return ret;
    }

    char top() const
    {
        return _s.back();
    }

private:
    std::vector<char> _s;
};

class supplies
{
public:
    explicit supplies(std::vector<stack> stacks)
    : _stacks(std::move(stacks))
    {
    }

    void move(int count, int from, int to)
    {
        while (count-- > 0)
            _stacks.at(to - 1).push(_stacks.at(from - 1).pop());
    }

    void move_together(int count, int from, int to)
    {
        auto in_transit = _stacks.at(from - 1).pop(count);
        std::reverse(in_transit.begin(), in_transit.end());
        _stacks.at(to - 1).push(std::move(in_transit));
    }

    std::string message() const
    {
        std::string ret;
        for (const stack& s : _stacks)
            ret += s.top();
        return ret;
    }

private:
    std::vector<stack> _stacks;
};

bool is_number(char c)
{
    return c >= '0' && c <= '9';
}

// The last line is used to get the index of a stack in the line
// e.g. stack 1 is all the second characters, stack 2 is all sixth
// characters etc.
std::vector<int> stack_indeces(const std::string& s)
{
    // We don't bother converting the characters to numbers
    std::vector<int> ret;
    for (std::size_t i = 0; i < s.size(); ++i)
    {
        if (is_number(s.at(i)))
            ret.push_back(i);
    }
    return ret;
}

supplies parse_supplies(std::vector<std::string> crate_rows)
{
    auto row = crate_rows.rbegin();
    const auto stack_idcs = stack_indeces(*row++);
    std::vector<stack> stacks(stack_idcs.size());

    for (; row != crate_rows.rend(); ++row)
    {
        for (std::size_t i = 0; i < stack_idcs.size(); ++i)
        {
            const char c = row->at(stack_idcs.at(i));
            if (c != ' ')
                stacks.at(i).push(c);
        }
    }

    return supplies{std::move(stacks)};
}

int extract_next_int(const std::string& desc, const std::string& str)
{
    const auto int_idx = str.find(desc) + desc.size();
    return std::stoi(str.substr(int_idx));
}

std::string message_9000(const char* input_filename)
{
    std::ifstream input(input_filename);

    std::string line;

    std::vector<std::string> stack_init;
    while (std::getline(input, line))
    {
        if (line.empty())
            break;
        stack_init.push_back(line);
    }

    supplies supply_arrangement = parse_supplies(std::move(stack_init));

    const std::string move = "move";
    const std::string from = "from";
    const std::string to = "to";

    while (std::getline(input, line))
    {
        const int count = extract_next_int(move, line);
        const int from_idx = extract_next_int(from, line);
        const int to_idx = extract_next_int(to, line);
        supply_arrangement.move(count, from_idx, to_idx);
    }

    return supply_arrangement.message();
}

std::string message_9001(const char* input_filename)
{
    std::ifstream input(input_filename);

    std::string line;

    std::vector<std::string> stack_init;
    while (std::getline(input, line))
    {
        if (line.empty())
            break;
        stack_init.push_back(line);
    }

    supplies supply_arrangement = parse_supplies(std::move(stack_init));

    const std::string move = "move";
    const std::string from = "from";
    const std::string to = "to";

    while (std::getline(input, line))
    {
        const int count = extract_next_int(move, line);
        const int from_idx = extract_next_int(from, line);
        const int to_idx = extract_next_int(to, line);
        supply_arrangement.move_together(count, from_idx, to_idx);
    }

    return supply_arrangement.message();
}

int main(int argc, char* argv[])
{
    std::cout << message_9000(argv[1]) << '\n';
    std::cout << message_9001(argv[1]) << '\n';
}