#define path "../res/01.txt"

#include "utils.h"

int main(void)
{
    std::vector<std::string> lines = read_file(path);

    std::vector<int> nums = std::vector<int>();

    std::vector<std::string> num_strings = {
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    for (auto line : lines)
    {
        std::vector<int> digits = std::vector<int>();
        for (int i = 0; i < line.length(); i++)
        {
            const auto c = line[i];
            if (isdigit(c))
            {
                digits.push_back(c - '0');
            }
            else if (isalpha(c))
            {
                for (int j = 0; j < num_strings.size(); j++)
                {
                    const auto& n = num_strings[j];
                    if (line.size() >= i + n.size() && line.substr(i, n.size()) == n) {
                        digits.push_back(j + 1);
                    }
                }
            }
        }
        nums.push_back(digits.front() * 10 + digits.back());
    }
    const auto sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << sum << std::endl;
    return 0;
}
