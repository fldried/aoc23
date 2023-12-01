#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <map>

std::vector<std::string> read_file(std::string name)
{
  std::vector<std::string> lines = std::vector<std::string>();
  std::string line;

  std::fstream file(name);

  while (getline(file, line))
  {
    lines.push_back(line);
  }

  return lines;
}