#ifndef TSP_STRUCT_H
#define TSP_STRUCT_H

#include <cmath>

struct City {
    double x, y;
};

struct Edge{
    int a,b;
    double distance;

    //operator overload < to compare 2 edges
    bool operator<(const Edge& other) const {
        return distance < other.distance;
    }
};

double euclidean(const City& a, const City& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

vector<vector<int>> DistGraph(const vector<City>& cities){
    int n = cities.size();

    // distance matrix, time and space complexity O(n^2)
    vector<vector<int>> distances(n - 1, vector<int>(n - 1));
    for(int i=0; i<n; i++){
        for(int j = 0; j<n; j++){
            if(i == j){
                distances[i][j] = 0;
            }else{
                distances[i][j] = euclidean(cities[i], cities[j]);
            }
        }
    }

    return distances;
}

vector<Edge> BuildEdges(const vector<vector<int>>& distances, int n){
    vector<Edge> edges;

    //build edges, O(n^2)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { 
            Edge e;
            e.a = i;
            e.b = j;
            e.distance = distances[i][j];
            edges.push_back(e);
        }
    }

    //O(nlogn)
    sort(edges.begin(), edges.end());

    return edges;
}

#endif