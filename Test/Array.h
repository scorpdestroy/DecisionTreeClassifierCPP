#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <vector>
#include <string>
#include <functional>

using namespace std;

// Объявление функции для фильтрации строк
std::vector<std::vector<std::string>> Array(const std::vector<std::vector<std::string>>& dataset,
    int feature_index, float threshold,
    std::function<bool(const std::vector<std::string>&, int, float)> condition);

#endif // ARRAY_UTILS_H