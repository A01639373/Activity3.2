#ifndef TSP_STRUCT_H
#define TSP_STRUCT_H

#include <cmath>

struct City {
    double x, y;
};

double euclidean(const City& a, const City& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

#endif