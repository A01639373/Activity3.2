#include <iostream>
#include <vector>
#include "./headers/tsp_loader.h"
//#include "./headers/NN.h"
//#include "./headers/CheapestLink.h"
//#include "./headers/MST.h"

using namespace std;

int main(){
    try{
        vector<City> total_cities = loadTSP("dsj1000.txt");
        cout << "Loaded " << total_cities.size() << endl;

        if (total_cities.size() >= 2) {
            cout << "Distance between first two: "
                      << euclidean(total_cities[0], total_cities[1]) << "\n";
        }
    } catch(const exception& e){
        cerr << e.what() << '\n';
    }

    int number_of_cities;
    cin >> number_of_cities;

    vector<City> cities(number_of_cities - 1);
    // funcion random de n ciudades para guardarlas en cities no repetidas

    //cout << "Nearest Neighbor: " << NearestNeighbor(cities) << endl;
    //cout << "Cheapest Link: " << CheapestLink(cities) << endl;
    //cout << "Minimum Spanning Tree: " << MST(cities) << endl;


    return 0;
}