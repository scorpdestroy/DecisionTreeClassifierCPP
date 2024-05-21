#include "Helper.h"
#include <stdexcept>

// ������� ��� �������������� vector<vector<string>> � vector<vector<float>>
vector<vector<float>> convert_to_float(const vector<vector<string>>& input) {
    vector<vector<float>> output;
    output.reserve(input.size());

    for (const auto& row : input) {
        vector<float> float_row;
        float_row.reserve(row.size());

        for (const auto& item : row) {
            try {
                // �������������� �������� ������ � ����� � ��������� �������
                float_row.push_back(stof(item));
            }
            catch (const invalid_argument& e) {
                // ��������� ������������ ������ � ������
                // ����� ����� ��������� �����-�� ��������, ��������, ���������� ���� ������� ��� ��������� ����������
                // � ���� ������� ������ ���������� ���� �������
                continue;
            }
        }

        output.push_back(float_row);
    }
    return output;
}

// ������� ��� �������������� vector<vector<float>> � vector<vector<string>>
vector<vector<string>> convert_to_string(const vector<vector<float>>& input) {
    vector<vector<string>> output;
    output.reserve(input.size());

    for (const auto& row : input) {
        vector<string> string_row;
        string_row.reserve(row.size());

        for (const auto& item : row) {
            // �������������� ����� � ��������� ������� � ������
            string_row.push_back(to_string(item));
        }

        output.push_back(string_row);
    }
    return output;
}

// ������� ��� �������� ������ ������ (���������) �� ������� �������� �����
void remove_header(vector<vector<string>>& data) {
    if (data.empty()) {
        return; // ������ ������ ������, ������ �� ����� ������
    }

    // �������� ������ ������ (���������)
    data.erase(data.begin());

    // �������� ���� ��������� �� ������ ������
    for (auto& row : data) {
        // ������� ������ ������� �� ������ ������
        row.erase(row.begin());
    }
}

// ������� ��� �������� ������� ������� �� ������� �������� �����
void remove_first_column(vector<vector<string>>& data) {
    for (auto& row : data) {
        if (!row.empty()) {
            // ������� ������ ������� �� ������ ������
            row.erase(row.begin());
        }
    }
}

std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>>
split_dataset(const std::vector<std::vector<std::string>>& dataset) {
    // ��������, ��� dataset �� ������
    if (dataset.empty() || dataset[0].empty()) {
        // ���������� ������ �������, ���� dataset ������
        return { {}, {} };
    }

    // ������ ���������� �������� � ������
    size_t last_index = dataset[0].size() - 1;

    // ������� ��� ������� ��� �������� X � Y
    std::vector<std::vector<std::string>> X;
    std::vector<std::vector<std::string>> Y;

    // ��������� dataset �� X � Y
    for (const auto& row : dataset) {
        // ������ ��� ������� ������ X
        std::vector<std::string> row_X(row.begin(), row.end() - 1);
        // ������ ��� �������� �������� Y
        std::vector<std::string> row_Y = { row[last_index] };

        // ��������� ������ X � X
        X.push_back(row_X);
        // ��������� ������ Y � Y
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

// ���������� ��� ���� float
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

// ���������� ��� ���� string
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

// ���������� ��� vector<vector<float>>
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

// ���������� ��� vector<vector<string>>
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

// ����������� ������������� ������� print_vector ��� vector<string>
void print_vector(const vector<string>& vec) {
    for (const auto& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}

// ����������� ������������� ������� print_vector ��� vector<vector<string>>
void print_vector(const vector<vector<string>>& vec) {
    for (const auto& row : vec) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

// ����������� ������������� ������� print_vector ��� vector<vector<float>>
void print_vector(const vector<vector<float>>& vec) {
    for (const auto& row : vec) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}