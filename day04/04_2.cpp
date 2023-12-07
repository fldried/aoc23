#define path "./input04.txt"
#include "../utils.h"

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
   for ( int i { 0 }; i < numbers.size( ); i++ )
      for ( int j { 0 }; j < winning_nums.size( ); j++ )
         if ( numbers[ i ] == winning_nums[ j ] ) points++;
   return points;
}

int main( void ) {
   std::vector<std::string> lines = read_file( path );
   std::vector<std::pair<int, int>> game_points;
   std::queue<std::pair<int, int>> cards_queue;
   int total_cards { 0 };

   for ( std::string line : lines ) {
      auto [winning_nums, numbers] = parse_line( line );
      game_points.push_back( 
         std::make_pair( 
            std::stoi( line.substr( line.find_first_of( ' ' ) + 1, line.find( ':' ) ) ),
            calculatePoints( numbers, winning_nums )
         ) 
      );
   }

   for ( std::pair<int, int> card : game_points )
      cards_queue.push( card );

   while ( !cards_queue.empty( ) ) {
      std::pair<int, int> current_card = cards_queue.front( );
      cards_queue.pop( );

      total_cards += current_card.second;

      for ( 
         int i = current_card.first;
         i < current_card.first + current_card.second && i < game_points.size( );
         i++ 
      ) cards_queue.push( game_points[ i ] );
   }

   total_cards += lines.size( );
   std::cout << total_cards << std::endl;

   return 0;
}
