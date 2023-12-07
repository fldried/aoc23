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
   size_t ways_to_win;

   std::string time { lines[ 0 ] };
   std::string dist { lines[ 1 ] };

   size_t ms;
   size_t mm;

   size_t i;

   time.erase( std::remove_if( time.begin(), time.end(), isspace ), time.end() );
   dist.erase( std::remove_if( dist.begin(), dist.end(), isspace ), dist.end() );

   ms = std::stoll(time.substr(5));
   mm = std::stoll(dist.substr(9));

   ways_to_win = measure( ms, mm );
   std::cout << ways_to_win << std::endl;
   return 0;
}
