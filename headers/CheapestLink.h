#ifndef CHEAPEST_LINK_H
#define CHEAPEST_LINK_H

#include "tsp_struct.h"
#include <vector>
#include <algorithm>

using namespace std;

double CheapestLink(const vector<City>& cities){
    int n = cities.size();

    // distance matrix, time and space complexity O(n^2)
    vector<vector<int>> distances = DistGraph(cities);

    //build edges, O(n^2)
    vector<Edge> edges = BuildEdges(distances, n);
    
}

#endif