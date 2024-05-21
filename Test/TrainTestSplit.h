#ifndef TRAIN_TEST_SPLIT_H
#define TRAIN_TEST_SPLIT_H

#include <vector>
#include <tuple>
using namespace std;

template<typename T>
std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>>& matrix);

template<typename T>
std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<T>>>
train_test_split(const std::vector<std::vector<T>>& X, double test_size = 0.5);

#endif // TRAIN_TEST_SPLIT_H
