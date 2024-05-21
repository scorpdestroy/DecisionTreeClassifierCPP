#include "Helper.h"
#include <stdexcept>

// Функция для преобразования vector<vector<string>> в vector<vector<float>>
vector<vector<float>> convert_to_float(const vector<vector<string>>& input) {
    vector<vector<float>> output;
    output.reserve(input.size());

    for (const auto& row : input) {
        vector<float> float_row;
        float_row.reserve(row.size());

        for (const auto& item : row) {
            try {
                // Преобразование элемента строки в число с плавающей запятой
                float_row.push_back(stof(item));
            }
            catch (const invalid_argument& e) {
                // Обработка некорректных данных в строке
                // Здесь можно выполнить какое-то действие, например, пропустить этот элемент или выбросить исключение
                // В этом примере просто пропускаем этот элемент
                continue;
            }
        }

        output.push_back(float_row);
    }
    return output;
}

// Функция для преобразования vector<vector<float>> в vector<vector<string>>
vector<vector<string>> convert_to_string(const vector<vector<float>>& input) {
    vector<vector<string>> output;
    output.reserve(input.size());

    for (const auto& row : input) {
        vector<string> string_row;
        string_row.reserve(row.size());

        for (const auto& item : row) {
            // Преобразование числа с плавающей запятой в строку
            string_row.push_back(to_string(item));
        }

        output.push_back(string_row);
    }
    return output;
}

// Функция для удаления первой строки (заголовка) из вектора векторов строк
void remove_header(vector<vector<string>>& data) {
    if (data.empty()) {
        return; // Пустой вектор данных, ничего не нужно делать
    }

    // Удаление первой строки (заголовка)
    data.erase(data.begin());

    // Удаление имен признаков из каждой строки
    for (auto& row : data) {
        // Удаляем первый элемент из каждой строки
        row.erase(row.begin());
    }
}

// Функция для удаления первого столбца из вектора векторов строк
void remove_first_column(vector<vector<string>>& data) {
    for (auto& row : data) {
        if (!row.empty()) {
            // Удаляем первый элемент из каждой строки
            row.erase(row.begin());
        }
    }
}

std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>>
split_dataset(const std::vector<std::vector<std::string>>& dataset) {
    // Проверка, что dataset не пустой
    if (dataset.empty() || dataset[0].empty()) {
        // Возвращаем пустые векторы, если dataset пустой
        return { {}, {} };
    }

    // Индекс последнего элемента в строке
    size_t last_index = dataset[0].size() - 1;

    // Создаем два вектора для хранения X и Y
    std::vector<std::vector<std::string>> X;
    std::vector<std::vector<std::string>> Y;

    // Разделяем dataset на X и Y
    for (const auto& row : dataset) {
        // Вектор для текущей строки X
        std::vector<std::string> row_X(row.begin(), row.end() - 1);
        // Вектор для текущего элемента Y
        std::vector<std::string> row_Y = { row[last_index] };

        // Добавляем строку X в X
        X.push_back(row_X);
        // Добавляем строку Y в Y
        Y.push_back(row_Y);
    }

    return { X, Y };
}

pair<int, int> shape(vector<vector<string>>& input) {
    if (input.empty()) {
        return { 0, 0 };
    }
    int num_rows = static_cast<int>(input.size());
    int num_cols = static_cast<int>(input[0].size());
    return { num_rows, num_cols };
}

// Реализация для типа float
vector<float> unique(const vector<float>& input) {
    vector<float> result;
    for (float value : input) {
        if (find(result.begin(), result.end(), value) == result.end()) {
            result.push_back(value);
        }
    }
    sort(result.begin(), result.end());
    return result;
}

// Реализация для типа string
vector<string> unique(const vector<string>& input) {
    vector<string> result;
    for (const string& value : input) {
        if (find(result.begin(), result.end(), value) == result.end()) {
            result.push_back(value);
        }
    }
    sort(result.begin(), result.end());
    return result;
}

// Реализация для vector<vector<float>>
vector<vector<float>> unique(vector<vector<float>>& input) {
    vector<vector<float>> result;
    for (const auto& row : input) {
        if (find(result.begin(), result.end(), row) == result.end()) {
            result.push_back(row);
        }
    }
    sort(result.begin(), result.end());
    return result;
}

int countElements(vector<vector<string>>& vec) {
    int count = 0;
    for (const auto& innerVec : vec) {
        count += innerVec.size();
    }
    return count;
}

// Реализация для vector<vector<string>>
vector<vector<string>> unique(vector<vector<string>>& input) {
    vector<vector<string>> result;
    for (const auto& row : input) {
        if (find(result.begin(), result.end(), row) == result.end()) {
            result.push_back(row);
        }
    }
    sort(result.begin(), result.end());
    return result;
}

void print_vector(const vector<float>& vec) {
    for (const auto& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}

// Определение перегруженной функции print_vector для vector<string>
void print_vector(const vector<string>& vec) {
    for (const auto& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}

// Определение перегруженной функции print_vector для vector<vector<string>>
void print_vector(const vector<vector<string>>& vec) {
    for (const auto& row : vec) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

// Определение перегруженной функции print_vector для vector<vector<float>>
void print_vector(const vector<vector<float>>& vec) {
    for (const auto& row : vec) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}