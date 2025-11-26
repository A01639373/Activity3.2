#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include "./headers/tsp_loader.h"
#include "./headers/NN.h"
#include "./headers/CheapestLink.h"
//#include "./headers/MST.h"

using namespace std;

int main(){
    vector<City> total_cities;
    try{
        total_cities = loadTSP("dsj1000.txt");
        cout << "Loaded " << total_cities.size() << endl;
    } catch(const exception& e){
        cerr << e.what() << '\n';
    }

    int number_of_cities;
    cout << "How many cities? ";
    cin >> number_of_cities;

    if(number_of_cities > total_cities.size()){
        number_of_cities = total_cities.size();
    }

    // funcion random de n ciudades para guardarlas en cities no repetidas
    vector<int> unique_n(total_cities.size());
    for(int i = 0; i <= total_cities.size(); ++i){
        unique_n[i] = i;
    }

    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < number_of_cities; ++i) {
        uniform_int_distribution<> dis(i, total_cities.size() - 1);
        int j = dis(gen);
        swap(unique_n[i], unique_n[j]);
    }

    vector<City> cities;
    for (int i = 0; i < number_of_cities; ++i) {
        cities.push_back(total_cities[unique_n[i]]);
    }

    cout << fixed << setprecision(0);
    cout << "Nearest Neighbor: " << NearestNeighbor(cities) << endl;
    cout << "Cheapest Link: " << CheapestLink(cities) << endl;
    //cout << "Minimum Spanning Tree: " << MST(cities) << endl;


    return 0;
}