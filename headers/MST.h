#ifndef MST_H
#define MST_H

#include "MST.h"
#include "tsp_struct.h"
#include "tsp_loader.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Disjoint set data struture
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }

    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else parent[s2] = s1, rank[s1]++;
        }
    }
};
bool comparator(vector<int> &a,vector<int> &b){
   return a[2] < b[2]; 
}


int kruskalsMST(int number_of_cities, const vector<City>& cities) {
    
    // distance matrix, time and space complexity O(n^2)
    vector<vector<double>> distances = DistGraph(cities);

    //build edges, O(n^2)
    vector<Edge> edges = BuildEdges(distances, number_of_cities);
    
    // Traverse edges in sorted order
    DSU dsu(number_of_cities);
    int cost = 0, count = 0;
    
    for (auto &e : edges) {

        if (dsu.find(e.a) != dsu.find(e.b)) {
            dsu.unite(e.a, e.b);
            cost += e.distance;
            if (++count == number_of_cities - 1) break;
        }
    }
    return cost;
}

#endif
