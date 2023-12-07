#define path "./input06.txt"
#include "../utils.h"


size_t measure( size_t ms, size_t mm ) {
   double x1 = ( ms - std::sqrt( std::pow(ms, 2) - 4 * mm ) ) / 2;
   double x2 = ( ms + std::sqrt( std::pow(ms, 2) - 4 * mm ) ) / 2;

   const double x = std::round( x1 ) == x1 ? x1 + 1 : std::floor( x1 );
   return ( x2 - x );
}

int main( void ) {
   std::vector<std::string> lines = read_file( path );
   std::vector<size_t> ways_to_win;

   std::vector<size_t> ms;
   std::vector<size_t> mm;

   size_t i;

   std::istringstream iss( lines[ 0 ].substr( 6 ) );
   while ( iss >> i ) ms.push_back( i );

   iss = std::istringstream( lines[ 1 ].substr( 10 ) );
   while ( iss >> i ) mm.push_back( i );

   std::transform(ms.begin(), ms.end(), mm.begin(), std::back_inserter(ways_to_win), measure);
   size_t total_ways_to_win = std::accumulate(ways_to_win.begin(), ways_to_win.end(), 1, std::multiplies<size_t>());

   std::cout << total_ways_to_win << std::endl;
   return 0;
}
