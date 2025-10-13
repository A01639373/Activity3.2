#ifndef TSP_LOADER_H
#define TSP_LOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

struct City {
    int x, y;
};

int euclidean(const City& a, const City& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

vector<City> loadTSP(const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Error: could not open file " + filename);
    }

    string line;
    vector<City> cities;

    while (getline(file, line)) {
        if (line.find("NODE_COORD_SECTION") != string::npos)
            break;
    }

    while (getline(file, line)) {
        if (line == "EOF" || line.empty()) break;
        stringstream ss(line);
        int id;
        City c;
        ss >> id >> c.x >> c.y;
        cities.push_back(c);
    }

    return cities;
}

#endif 
