#include <iostream>
#include <vector>
#include <random>
#include <tuple>
#include <utility>
#include <map>
#include <unordered_map>
#include "DataFrame.h"
#include "Helper.h"
#include "TrainTestSplit.h"
#include "array.h"
#include "concatenate.h"
using namespace std;

class Node {
public:
    int feature_index;
    float threshold;
    Node* left;
    Node* right;
    float info_gain;
    string value; 

    // Конструктор
    Node(int feature_index, float threshold,
        Node* left = nullptr, Node* right = nullptr,
        float info_gain = 0.0, string value = {})
        : feature_index(feature_index), threshold(threshold),
        left(left), right(right), info_gain(info_gain), value(value) {}
};

struct BestSplit {
    int feature_index;
    float threshold;
    vector<vector<string>> dataset_left;
    vector<vector<string>> dataset_right;
    float info_gain;
};

class DecisionTreeClassifier {
private:
    Node* root;
    int min_samples_split;
    int max_depth;

    Node* build_tree(vector<vector<string>>& dataset, int curr_depth = 0) {
        vector<vector<string>> X;
        vector<vector<string>> Y;
        
        string leaf_value;

        pair<vector<vector<string>>, vector<vector<string>>> split_data = split_dataset(dataset);
        X = split_data.first;
        Y = split_data.second;

        pair<int, int> pair_data = shape(dataset);

        int num_samples = pair_data.first; 
        int num_features = pair_data.second - 1; //сюда 
        
        if (num_samples >= min_samples_split && curr_depth <= max_depth) {
            BestSplit best_split = get_best_split(dataset, num_samples, num_features);
            if (best_split.info_gain > 0) {

                cout << "Left" << endl;
                cout << best_split.info_gain << endl;
                print_vector(best_split.dataset_left);
                cout << "Right" << endl;
                print_vector(best_split.dataset_right);

                Node *left_subtree = build_tree(best_split.dataset_left, curr_depth + 1);
                Node *right_subtree = build_tree(best_split.dataset_right, curr_depth + 1);
                return new Node(best_split.feature_index, best_split.threshold,
                    left_subtree, right_subtree, best_split.info_gain, leaf_value);
            }
        }

        leaf_value = calculate_leaf_value(Y);
        return new Node(NULL, NULL, nullptr, nullptr, NULL, leaf_value);
    };

    BestSplit get_best_split(vector<vector<string>>& dataset, int num_samples, int num_features) {
        BestSplit best_split;
        best_split.info_gain = -numeric_limits<float>::infinity();

        for (int feature_index = 0; feature_index < num_features; ++feature_index) {
            vector<float> feature_values;
            for (const auto& row : dataset) {
                feature_values.push_back(stof(row[feature_index]));
            }

            vector<float> possible_thersholds = unique(feature_values);

            for (const auto& threshold : possible_thersholds) {
                vector<vector<string>> dataset_left;
                vector<vector<string>> dataset_right;

                pair<vector<vector<string>>, vector<vector<string>>> splitter = split(dataset, feature_index, threshold);
                dataset_left = splitter.first;
                dataset_right = splitter.second;

                if (!dataset_left.empty() && !dataset_right.empty()) {
                    vector<vector<string>> y, left_y, right_y;

                    y = split_dataset(dataset).first;
                    left_y = split_dataset(dataset_left).first;
                    right_y = split_dataset(dataset_right).first;

                    float curr_info_gain = information_gain(y, left_y, right_y);

                    if (curr_info_gain > best_split.info_gain) {
                        best_split.feature_index = feature_index;
                        best_split.threshold = threshold;
                        best_split.dataset_left = dataset_left;
                        best_split.dataset_right = dataset_right;
                        best_split.info_gain = curr_info_gain;
                    }
                }
            }
        }

        return best_split;
    };

    pair<vector<vector<string>>, vector<vector<string>>> split(vector<vector<string>>& dataset, int feature_index, float threshold) {
        auto lessThanOrEqualLambda = [](const vector<string>& row, int feature_index, float threshold) {
            return stof(row[feature_index]) <= threshold;
            };

        auto greaterThanLambda = [](const vector<string>& row, int feature_index, float threshold) {
            return stof(row[feature_index]) > threshold;
            };

        vector<vector<string>> dataset_left = Array(dataset, feature_index, threshold, lessThanOrEqualLambda);
        vector<vector<string>> dataset_right = Array(dataset, feature_index, threshold, greaterThanLambda);

        return make_pair(dataset_left, dataset_right);
    };
    
    float information_gain(vector<vector<string>>& parent, vector<vector<string>>& l_child, vector<vector<string>>& r_child) {
        float weight_l = static_cast<float>(l_child.size()) / static_cast<float>(parent.size());
        float weight_r = static_cast<float>(r_child.size()) / static_cast<float>(parent.size());

        float gain = gini_index(parent) - (weight_l * gini_index(l_child) + weight_r * gini_index(r_child));
        return gain;
    }

    float gini_index(vector<vector<string>>& y) {
        unordered_map<string, int> class_counts;
        int total_elements = 0;

        for (const auto& sublist : y) {
            for (const auto& label : sublist) {
                class_counts[label]++;
                total_elements++;
            }
        }

        float gini = 0.0f;
        for (const auto& pair : class_counts) {
            float p_cls = static_cast<float>(pair.second) / total_elements;
            gini += p_cls * p_cls;
        }

        return 1.0f - gini;
    }

    string calculate_leaf_value(vector<vector<string>>& Y) {
        unordered_map<string, int> count_map;

        for (const vector<string>& row : Y) {
            for (const string& value : row) {
                count_map[value]++;
            }
        }

        string most_common;
        int max_count = 0;
        for (const auto& pair : count_map) {
            if (pair.second > max_count) {
                most_common = pair.first;
                max_count = pair.second;
            }
        }

        return most_common;
    };
    

    int make_prediction(vector<float>& x, Node* tree);

public:
    DecisionTreeClassifier(int min_samples_split = 2, int max_depth = 3)
        : min_samples_split(min_samples_split), max_depth(max_depth), root(nullptr) {
    }

    void fit(vector<vector<string>>& X, vector<vector<string>>& Y) {
        vector<vector<string>> dataset = concatenate(X, Y);
        root = build_tree(dataset);
    };

    void print_tree(Node* tree = nullptr, string indent = " ") {
        if (!tree) {
            tree = root;
        }

        if (tree->value != "") {
            std::cout << tree->value << std::endl;
        }
        else {
            std::cout << "X_" << tree->feature_index << " <= " << tree->threshold << " ? " << tree->info_gain << std::endl;
            std::cout << indent << "left: ";
            print_tree(tree->left, indent + indent);
            std::cout << indent << "right: ";
            print_tree(tree->right, indent + indent);
        }
    };

    vector<int> predict(vector<vector<float>>& X);
};

int main() {
    std::vector<std::vector<std::string>> data = readCSV("Iris.csv");

    remove_header(data);

    vector<vector<string>> X_train, X_test, Y_train, Y_test, test;
    tie(X_train, X_test) = train_test_split(data, 0.1);

    pair<vector<vector<string>>, vector<vector<string>>> split_data = split_dataset(X_train);
    X_train = split_data.first;
    Y_train = split_data.second;

    split_data = split_dataset(X_test);
    X_test = split_data.first;
    Y_test = split_data.second;

    DecisionTreeClassifier tree;

    tree.fit(X_train, Y_train);
    tree.print_tree();


    return 0;
}

