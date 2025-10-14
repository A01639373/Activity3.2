#ifndef NN_H
#define NN_H

#include <vector>
#include "tsp_struct.h"

using namespace std;

double NearestNeighbor(const vector<City>& cities){
    if(cities.empty())
        return 0.0;

    vector<bool> visited(cities.size(), false);
    double distance = 0;
    int current = 0;

    visited[current] = true;

    for (int i = 1; i < cities.size(); ++i) {
        double bestDist = 1e9;
        int next = -1;
        for (int j = 0; j < cities.size(); ++j) {
            if (!visited[j]) {
                double dist = euclidean(cities[current], cities[j]);
                if (dist < bestDist) {
                    bestDist = dist;
                    next = j;
                }
            }
        }
        visited[next] = true;
        distance += bestDist;
        current = next;
    }

    distance += euclidean(cities[current], cities[0]);

    return distance;
}   

#endif