#include <iostream>
#include <vector>
#include "./headers/tsp_loader.h"

using namespace std;

int main(){
    try{
        vector<City> cities = loadTSP("dsj1000.txt");
        cout << "Loaded " << cities.size() << endl;

        if (cities.size() >= 2) {
            cout << "Distance between first two: "
                      << euclidean(cities[0], cities[1]) << "\n";
        }
    } catch(const exception& e){
        cerr << e.what() << '\n';
    }

    return 0;
}