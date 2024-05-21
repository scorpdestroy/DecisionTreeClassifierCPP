#include "traintestsplit.h"
#include <random>

template<typename T>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>& matrix) {
    std::vector<std::vector<T>> transposed(matrix[0].size(), std::vector<T>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

template<typename T>
std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<T>>>
train_test_split(const std::vector<std::vector<T>>& X, double test_size) {
    std::vector<size_t> indices(X.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        indices[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    size_t test_samples = static_cast<size_t>(X.size() * test_size);

    std::vector<std::vector<T>> X_train, X_test, Y_train, Y_test;
    for (size_t i = 0; i < X.size(); ++i) {
        if (i < test_samples) {
            X_test.push_back(X[indices[i]]);
        }
        else {
            X_train.push_back(X[indices[i]]);
        }
    }

    return std::make_tuple(X_train, X_test);
}

// Explicit instantiation for supported types
template std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>>& matrix);
template std::vector<std::vector<float>> transpose(const std::vector<std::vector<float>>& matrix);
template std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& matrix);
template std::vector<std::vector<std::string>> transpose(const std::vector<std::vector<std::string>>& matrix);

template std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
train_test_split(const std::vector<std::vector<int>>& X, double test_size);
template std::tuple<std::vector<std::vector<float>>, std::vector<std::vector<float>>>
train_test_split(const std::vector<std::vector<float>>& X, double test_size);
template std::tuple<std::vector<std::vector<double>>, std::vector<std::vector<double>>>
train_test_split(const std::vector<std::vector<double>>& X, double test_size);
template std::tuple<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>>
train_test_split(const std::vector<std::vector<std::string>>& X, double test_size);
