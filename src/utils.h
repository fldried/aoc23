#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <map>
#include <ranges>
#include <tuple>
#include <string_view>
#include <regex>
#include <set>
#include <queue>


std::vector< std::string > split( std::string line, char delimiter )
{
    std::vector< std::string > tokens;
    std::string token;
    std::istringstream tokenStream( line );
    
    while ( std::getline( tokenStream, token, delimiter ) )
    {
        tokens.push_back( token );
    }
    
    return tokens;
}

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