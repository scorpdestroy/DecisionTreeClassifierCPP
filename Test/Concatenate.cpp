#include <vector>
#include <string>
#include <sstream>
#include "Concatenate.h"

vector<vector<string>> concatenate(const vector<vector<string>>& vec1,
    const vector<vector<string>>& vec2) {
    vector<vector<string>> result;

    // Преобразование и добавление первого вектора
    for (const auto& row : vec1) {
        vector<string> string_row;
        for (const auto& item : row) {
            string_row.push_back(item); // Преобразование числа в строку
        }
        result.push_back(string_row);
    }

    // Добавление второго вектора к первому
    for (size_t i = 0; i < vec2.size(); ++i) {
        result[i].push_back(vec2[i][0]); // Добавление элемента из второго вектора в соответствующий элемент первого вектора
    }

    return result;
}
