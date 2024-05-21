#include "array.h"

std::vector<std::vector<std::string>> Array(const std::vector<std::vector<std::string>>& dataset,
    int feature_index, float threshold,
    std::function<bool(const std::vector<std::string>&, int, float)> condition) {
    std::vector<std::vector<std::string>> result;
    for (const auto& row : dataset) {
        if (condition(row, feature_index, threshold)) {
            result.push_back(row);
        }
    }
    return result;
}