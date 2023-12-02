#define path "../res/02.txt"
#include "utils.h"

int main( void )
{
    std::vector< std::string > lines = read_file( path );
    int sum = 0;

    std::map<std::string, int> maxColors;
    std::regex amountRegex( R"((\d+)\s+(\w+))" );

    for ( std::string line : lines )
    {
        std::map<std::string, int> maxColors;
        int power = 1;
        std::vector<std::string> rounds = split( line.substr( line.find( ':' ) + 1 ), ';' );
        for ( auto& round : rounds ) {
            std::smatch match;
            std::string::const_iterator searchStart( round.cbegin( ) );
            while ( std::regex_search( searchStart, round.cend( ), match, amountRegex ) ) {
                int amount = std::stoi( match[ 1 ] );
                std::string color = match[ 2 ];
                if ( maxColors.find( color ) == maxColors.end( ) || amount > maxColors[ color ] ) {
                    maxColors[ color ] = amount;
                }
                searchStart = match.suffix( ).first;
            }
        }
        for ( const auto& color : maxColors ) {
            power *= color.second;
        }
        sum += power;
    }

    std::cout << sum << std::endl;
}