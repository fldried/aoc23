#define path "./input01.txt"

#include "../utils.h"

int main( void ) 
{
    std::vector<std::string> lines = read_file(path);

    std::vector<int> nums = std::vector<int>();

    for (auto line : lines)
    {
        std::vector<int> digits = std::vector<int>();
        for (int i = 0; i < line.length(); i++)
        {
            if (isdigit(line[i]))
            {
                digits.push_back(line[i] - '0');
            }
        }
        nums.push_back(digits.front() * 10 + digits.back());
    }
    const auto sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << sum << std::endl;
    return 0;
}
