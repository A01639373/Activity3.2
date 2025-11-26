#ifndef CHEAPEST_LINK_H
#define CHEAPEST_LINK_H

#include "tsp_struct.h"
#include <vector>
#include <algorithm>

using namespace std;

struct Set{
    vector<int> parent;

    Set(int n){
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i; 
    }

    int Find(int x) {
        if (parent[x] == x) 
            return x;
        return parent[x] = Find(parent[x]); 
    }

    void CombineSets(int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a != b)
            parent[b] = a;
    }

    bool Equal(int a, int b) {
        return Find(a) == Find(b);
    }
};

double CheapestLink(const vector<City>& cities){
    int n = cities.size();

    // distance matrix, time and space complexity O(n^2)
    vector<vector<int>> distances = DistGraph(cities);

    //build edges, O(n^2)
    vector<Edge> edges = BuildEdges(distances, n);
    
    vector<int> connections(n, 0);
    Set sets(n);
    vector<Edge> touredEdges;

    for(int i=0; i<edges.size(); i++){
        int a = edges[i].a;
        int b = edges[i].b;

        if(connections[a] < 2 && connections[b] < 2 && !sets.Equal(a, b)){
            touredEdges.push_back(edges[i]);

            connections[a]++;
            connections[b]++;

            sets.CombineSets(a,b);
        }

        if(touredEdges.size() == n)
        break;
    }

    //adjacency matrix
    vector<vector<int>> adj(n);
    for(int i = 0; i < touredEdges.size(); i++){
        const Edge &e = touredEdges[i];
        adj[e.a].push_back(e.b);
        adj[e.b].push_back(e.a);
    }

    vector<int> tour;
    tour.reserve(n);

    int current = 0;
    int prev = -1;

    tour.push_back(current);

    for(int i = 1; i < n; i++){
        int next = (adj[current][0] == prev ? adj[current][1] : adj[current][0]);
        prev = current;
        current = next;
        tour.push_back(current);
    }

    double distance = 0.0;
    for(int i = 0; i < tour.size(); i++){
        distance += distances[tour[i]][tour[i+1]];
    }
    distance += distances[tour[n-1]][tour[0]];

    return distance;
}

#endif