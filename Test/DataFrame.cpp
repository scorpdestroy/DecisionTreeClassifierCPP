#include "DataFrame.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

vector<vector<string>> readCSV(const string filename) {
    vector<vector<string>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream lineStream(line);
        string cell;

        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }

    file.close();
    return data;
}
