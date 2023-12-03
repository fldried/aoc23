#define path "../res/03.txt"

#include "utils.h"

int get_full_number( std::vector<std::string>& grid, int x, int& y ) {
    std::string number = "";
    int left { y }, right { y };

    while ( left >= 0 && isdigit( grid[ x ][ left ] ) ) {
        left--;
    }

    while ( right < grid[ x ].length( ) && isdigit( grid[ x ][ right ] ) ) {
        right++;
    }

    number = grid[ x ].substr( left, right - ( ++left ) );

    y = right;
    // prevents a segfault that I spent 2 hours on, debugging.
    // ref of y is passed, so it's incremented in the main function 

    return std::stoi( number );
}

int get_gear_ratio( std::vector<std::string>& grid, int i, int j ) {
    int adjacent { 0 };
    int numbers[ 2 ];

    int x { 0 };

    for ( int row { i - 1 }; row <= i + 1; row++ ) {
        for ( int col { j - 1 }; col <= j + 1; col++ ) {
            if ( !isdigit( grid[ row ][ col ] ) ) continue;
            numbers[ x ] = get_full_number( grid, row, col );
            adjacent++;
            x++;
        }
    }
    if ( adjacent == 2 ) return numbers[ 0 ] * numbers[ 1 ];
    return 0;
}


int gear_ratios_sum( std::vector<std::string>& grid ) {
    int sum = { 0 };

    for ( const auto& line : grid )
        for ( const auto& character : line )
            if ( character == '*' )
                sum += get_gear_ratio( grid, &line - &grid[ 0 ], &character - &line[ 0 ] );

    return sum;
}

int main( void )
{
    std::vector<std::string> lines = read_file( path );

    std::cout << gear_ratios_sum( lines ) << std::endl;
    return 0;
}
