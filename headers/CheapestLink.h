#ifndef CHEAPEST_LINK_H
#define CHEAPEST_LINK_H

#include "tsp_struct.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Set{
    vector<int> parent;

    Set(int n){
        parent.resize(n);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int Find(int x){
        if(parent[x] == x) 
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
    if (n < 2) return 0.0;

    vector<vector<double>> distances = DistGraph(cities);
    vector<Edge> edges = BuildEdges(distances, n);

    sort(edges.begin(), edges.end());

    vector<int> degree(n, 0);
    Set sets(n);
    vector<Edge> chosen;

    for(int i = 0; i<edges.size(); i++){
        const Edge &e = edges[i];
        int a = e.a;
        int b = e.b;

        if(degree[a] == 2 || degree[b] == 2)
            continue;

        if(sets.Equal(a, b) && chosen.size() < n-1)
            continue;

        chosen.push_back(e);
        degree[a]++;
        degree[b]++;
        sets.CombineSets(a, b);

        if(chosen.size() == n - 1)
            break;
    }

    vector<int> endpoints;
    for(int i = 0; i < n; i++){
        if(degree[i] == 1)
            endpoints.push_back(i);
    }

    if(endpoints.size() != 2){
        for(int i = 0; i < n && endpoints.size() < 2; i++){
            if(degree[i] < 2) endpoints.push_back(i);
        }
    }

    int u = endpoints[0];
    int v = endpoints[1];
    chosen.push_back(Edge{u, v, distances[u][v]});
    degree[u]++;
    degree[v]++;

    // Build adjacency list
    vector<vector<int>> adj(n);
    for(int i = 0; i<chosen.size(); i++){
        const Edge &e = chosen[i];
        adj[e.a].push_back(e.b);
        adj[e.b].push_back(e.a);
    }

    // Build tour
    vector<int> tour;
    tour.reserve(n);

    int current = 0;
    int prev = -1;
    for (int i = 0; i < n; i++) {
        tour.push_back(current);
        int next = (adj[current][0] == prev ? adj[current][1] : adj[current][0]);
        prev = current;
        current = next;
    }

    double distance = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        distance += distances[tour[i]][tour[j]];
    }

    return distance;
}

#endif
