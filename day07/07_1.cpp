#define path "./input07.txt"
#include "../utils.h"

std::map<char, int> values = {
    {'A', 14},
    {'K', 13},
    {'Q', 12},
    {'J', 11},
    {'T', 10},
    {'9', 9},
    {'8', 8},
    {'7', 7},
    {'6', 6},
    {'5', 5},
    {'4', 4},
    {'3', 3},
    {'2', 2}
};

int evaluateHand( const std::string& hand ) {
   std::map<char, int> freq;
   for ( const auto& ch : hand ) {
      freq[ ch ]++;
   }

   std::vector<int> counts;
   for ( const auto& pair : freq ) {
      counts.push_back( pair.second );
   }
   sort( counts.begin( ), counts.end( ) );

   if ( counts == std::vector<int>{5} ) {
      return 9; // five of a kind
   }
   else if ( counts == std::vector<int>{1, 4} ) {
      return 8; // four of a kind
   }
   else if ( counts == std::vector<int>{2, 3} ) {
      return 7; // full house
   }
   else if ( counts == std::vector<int>{1, 1, 3} ) {
      return 6; // three of a kind
   }
   else if ( counts == std::vector<int>{1, 2, 2} ) {
      return 5; // two pair
   }
   else if ( counts == std::vector<int>{1, 1, 1, 2} ) {
      return 4; // one pair
   }
   else {
      return 3; // highest card
   }
}

bool compareHands( const std::tuple<int, std::string, int>& a, const std::tuple<int, std::string, int>& b ) {
   if ( std::get<0>( a ) != std::get<0>( b ) ) {
      return std::get<0>( a ) < std::get<0>( b );
   }
   else {
      std::string hand_a = std::get<1>( a );
      std::string hand_b = std::get<1>( b );
      for ( int i = 0; i < hand_a.size( ); ++i ) {
         if ( values[ hand_a[ i ] ] != values[ hand_b[ i ] ] ) {
            return values[ hand_a[ i ] ] < values[ hand_b[ i ] ];
         }
      }
      return false;
   }
}

int calculateSum( const std::vector<std::tuple<int, std::string, int>>& hands ) {
   int sum = 0;
   for ( int i = 0; i < hands.size( ); i++ ) {
      sum += std::get<2>( hands[ i ] ) * ( i + 1 );
   }
   return sum;
}

int main( ) {
   std::vector<std::string> lines = read_file( path );
   std::vector<std::tuple<int, std::string, int>> hands;

   for ( const auto& line : lines ) {
      int hand_value = evaluateHand( line.substr( 0, 5 ) );
      hands.push_back( std::make_tuple( hand_value, line.substr( 0, 5 ), std::stoi( line.substr( 6 ) ) ) );
   }

   std::sort( hands.begin( ), hands.end( ), compareHands );

   int sum = calculateSum( hands );

   std::cout << sum << std::endl;
}