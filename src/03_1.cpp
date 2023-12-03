#define path "../res/input03.txt"

#include "utils.h"

int part_numbers_sum( const std::vector<std::string>& grid )
{
    int sum = 0;
    int dx[ ] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[ ] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for ( int i = 0; i < grid.size( ); ++i ) {
        for ( int j = 0; j < grid[ i ].size( ); ++j ) {
            if ( isdigit( grid[ i ][ j ] ) ) {
                std::string number;
                int start_idx = j;
                while ( j < grid[ i ].size( ) && isdigit( grid[ i ][ j ] ) ) {
                    number += grid[ i ][ j ];
                    ++j;
                }
                int end_idx = j - 1; 
                bool adjacent_symbol = false;
                for ( int x = std::max( 0, i - 1 ); x <= std::min( i + 1, ( int ) grid.size( ) - 1 ) && !adjacent_symbol; ++x ) {
                    for ( int y = std::max( 0, start_idx - 1 ); y <= std::min( end_idx + 1, ( int ) grid[ x ].size( ) - 1 ); ++y ) {
                        if ( grid[ x ][ y ] != '.' && !isdigit( grid[ x ][ y ] ) ) {
                            adjacent_symbol = true;
                            break;
                        }
                    }
                }
                if ( adjacent_symbol ) {
                    sum += std::stoi( number );
                }
            }
        }
    }
    return sum;
}

int main( void )
{
    std::vector<std::string> lines = read_file( path );
    std::cout << part_numbers_sum( lines ) << std::endl;
    return 0;
}