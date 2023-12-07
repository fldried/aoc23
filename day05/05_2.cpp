#define path "./input05.txt"
#include "../utils.h"

struct Mapping {
   size_t destination_range_start;
   size_t source_range_start;
   size_t range_length;
};

struct SeedPair {
   size_t seed;
   size_t range;
};

std::vector<Mapping> parse_mappings( const std::vector<std::string>& lines ) {
   std::vector<Mapping> mappings;
   for ( const auto& line : lines ) {
      std::istringstream iss( line );
      Mapping mapping;
      iss >> mapping.destination_range_start >> mapping.source_range_start >> mapping.range_length;
      mappings.push_back( mapping );
   }
   return mappings;
}

size_t source_to_destination( size_t source, const std::vector<Mapping>& mappings ) {
   for ( const auto& mapping : mappings ) {
      if ( mapping.source_range_start <= source && source < mapping.source_range_start + mapping.range_length ) {
         return mapping.destination_range_start + ( source - mapping.source_range_start );
      }
   }
   return source;
}

std::vector<size_t> resolve_mapping( const std::vector<size_t>& sources, const std::vector<Mapping>& mappings ) {
   std::vector<size_t> destinations;
   for ( const auto& source : sources ) {
      destinations.push_back( source_to_destination( source, mappings ) );
   }
   return destinations;
}

int main( ) {
   auto start = std::chrono::high_resolution_clock::now( );

   std::vector<std::string> lines = read_file( path );
   std::istringstream iss( lines[ 0 ] );
   std::vector<SeedPair> seeds;
   std::vector<size_t> all_seeds;
   size_t min = std::numeric_limits<size_t>::max( );
   size_t i, j;

   iss.ignore( 6 );
   while ( iss >> i >> j ) {
      seeds.push_back( { i, j } );
   }

   lines.erase( lines.begin( ), lines.begin( ) + 2 );

   std::vector<std::vector<Mapping>> all_mappings;
   std::vector<std::string> mapping_lines;
   for ( const auto& line : lines ) {
      if ( !line.empty( ) ) {
         mapping_lines.push_back( line );
      }
      else {
         all_mappings.push_back( parse_mappings( mapping_lines ) );
         mapping_lines.clear( );
      }
   }
   all_mappings.push_back( parse_mappings( mapping_lines ) );

   for ( const SeedPair& pair : seeds ) {
      for ( size_t i = 0; i < pair.range; ++i ) {
         std::vector<size_t> skip;
         size_t seed = pair.seed + i;
         for ( size_t j = 0; j < all_mappings.size( ); ++j ) {
            for ( const Mapping& range : all_mappings[ j ] ) {
               if ( seed >= range.source_range_start && seed < range.source_range_start + range.range_length ) {
                  skip.push_back( range.source_range_start + range.range_length - 1 - seed );
                  seed = range.destination_range_start + ( seed - range.source_range_start );
                  break;
               }
            }
         }
         if ( !skip.empty( ) ) {
            i += *std::min_element( skip.begin( ), skip.end( ) );
         }
         min = std::min( min, seed );
      }
   }

   auto end = std::chrono::high_resolution_clock::now( );
   std::cout << min << std::endl;
   std::cout << "Execution time: " << std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count( ) << "μs" << std::endl;

   return 0;
}