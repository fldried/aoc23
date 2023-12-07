#define path "./input05.txt"
#include "../utils.h"

struct Mapping {
    size_t destination_range_start;
    size_t source_range_start;
    size_t range_length;
};

std::vector<Mapping> parse_mappings(const std::vector<std::string>& lines) {
    std::vector<Mapping> mappings;
    for (const auto& line : lines) {
        std::istringstream iss(line);
        Mapping mapping;
        iss >> mapping.destination_range_start >> mapping.source_range_start >> mapping.range_length;
        mappings.push_back(mapping);
    }
    return mappings;
}

size_t source_to_destination(size_t source, const std::vector<Mapping>& mappings) {
    for (const auto& mapping : mappings) {
        if (mapping.source_range_start <= source && source < mapping.source_range_start + mapping.range_length) {
            return mapping.destination_range_start + (source - mapping.source_range_start);
        }
    }
    return source;
}

std::vector<size_t> resolve_mapping(const std::vector<size_t>& sources, const std::vector<Mapping>& mappings) {
    std::vector<size_t> destinations;
    for (const auto& source : sources) {
        destinations.push_back(source_to_destination(source, mappings));
    }
    return destinations;
}

int main() {
    std::vector<std::string> lines = read_file(path);
    std::istringstream iss(lines[0]);
    std::vector<size_t> seeds;
    size_t i;
    iss.ignore(6);
    while (iss >> i) seeds.push_back(i);

    lines.erase(lines.begin(), lines.begin() + 2);

    std::vector<std::vector<Mapping>> all_mappings;
    std::vector<std::string> mapping_lines;
    for (const auto& line : lines) {
        if (!line.empty()) {
            mapping_lines.push_back(line);
        } else {
            all_mappings.push_back(parse_mappings(mapping_lines));
            mapping_lines.clear();
        }
    }
    all_mappings.push_back(parse_mappings(mapping_lines));

    for (const auto& mappings : all_mappings) {
        seeds = resolve_mapping(seeds, mappings);
    }

    const size_t min_location = *std::min_element(seeds.begin(), seeds.end());
    std::cout << min_location << std::endl;

    return 0;
}