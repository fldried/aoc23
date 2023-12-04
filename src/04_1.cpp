#define path "../res/input04.txt"
#include "utils.h"

std::pair<std::vector<int>, std::vector<int>> parse_line( std::string line ) {
   std::vector<std::string> tokens = split( line.substr( line.find( ':' ) + 1 ), '|' );
   std::vector<int> winning_nums, numbers;

   std::istringstream winning_ss( tokens[ 0 ] ), num_ss( tokens[ 1 ] );
   int num;

   while ( winning_ss >> num ) winning_nums.push_back( num );
   while ( num_ss >> num ) numbers.push_back( num );

   return std::make_pair( winning_nums, numbers );
}

int calculatePoints( const std::vector<int>& numbers, const std::vector<int>& winning_nums ) {
   int points { 0 };
   for ( int i { 0 }; i < numbers.size( ); i++ ) {
      for ( int j { 0 }; j < winning_nums.size( ); j++ ) {
         if ( numbers[ i ] == winning_nums[ j ] ) {
            if ( points == 0 ) points++;
            else points *= 2;
         }
      }
   }
   return points;
}

int main( void ) {
   std::vector<std::string> lines = read_file( path );

   std::vector<int> total_points;
   for ( std::string line : lines ) {
      auto [winning_nums, numbers] = parse_line( line );
      total_points.push_back( calculatePoints( numbers, winning_nums ) );
   }
   std::cout << std::accumulate( total_points.begin( ), total_points.end( ), 0 ) << std::endl;
   return 0;
}





