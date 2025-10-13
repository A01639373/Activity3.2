#ifndef TSP_STRUCT_H
#define TSP_STRUCT_H

#include <cmath>

struct City {
    double x, y;
};

int euclidean(const City& a, const City& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

#endif