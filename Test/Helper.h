#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>
using namespace std;

// Функция для преобразования vector<vector<string>> в vector<vector<float>>
vector<vector<float>> convert_to_float(const vector<vector<string>>& input);

// Функция для преобразования vector<vector<float>> в vector<vector<string>>
vector<vector<string>> convert_to_string(const vector<vector<float>>& input);

// Функция для удаления первой строки (заголовка) из вектора векторов строк
void remove_header(vector<vector<string>>& data);

// Функция для удаления первого столбца из вектора векторов строк
void remove_first_column(vector<vector<string>>& data);

std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>>
split_dataset(const std::vector<std::vector<std::string>>& dataset);
pair<int, int> shape(vector<vector<string>>& input);

vector<float> unique(const vector<float>& input);
vector<string> unique(const vector<string>& input);

int countElements(std::vector<std::vector<std::string>>& vec);

// Для vector<vector<float>>
std::vector<std::vector<float>> unique(std::vector<std::vector<float>>& input);

// Для vector<vector<string>>
std::vector<std::vector<std::string>> unique(std::vector<std::vector<std::string>>& input);

void print_vector(const std::vector<float>& vec);

void print_vector(const std::vector<std::string>& vec);

void print_vector(const std::vector<std::vector<std::string>>& vec);

void print_vector(const std::vector<std::vector<float>>& vec);


#endif // DATAUTILS_H
