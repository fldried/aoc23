#define path "./input02.txt"
#include "../utils.h"

bool processRound(const std::string& round, const std::map<std::string, int>& colors, std::regex& amountRegex) {
    for (const std::string& token : split(round, ',')) {
        std::smatch match;
        if (std::regex_search(token, match, amountRegex)) {
            int amount = std::stoi(match[1]);
            std::string color = match[2];
            if (colors.at(color) < amount) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    std::vector<std::string> lines = read_file(path);
    int sum = 0;

    std::map<std::string, int> colors = {
        {"red", 12},
        {"green", 13},
        {"blue", 14}
    };

    std::regex amountRegex(R"((\d+)\s+(\w+))");

    for (const std::string& line : lines) {
        int gameId = std::stoi(line.substr(5, line.find(':')));
        std::string game = line.substr(line.find(':') + 1);
        std::vector<std::string> rounds = split(game, ';');
        bool valid = std::all_of(rounds.begin(), rounds.end(), [&](const std::string& round) {
            return processRound(round, colors, amountRegex);
        });
        if (valid) {
            sum += gameId;
        }
    }

    std::cout << sum << std::endl;
    return 0;
}