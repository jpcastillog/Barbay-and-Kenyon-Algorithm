#include <iostream>
#include <fstream>
#include <vector>
#include "set_class.h"
#include "interval_set_class.h"

template <typename T>
void load_interval_set(char file_path [], IntervalSet<T> *set){
    ifstream inFile;
    inFile.open(file_path);

    if (!inFile){
        cout << "No se puede abrir el archivo: " << file_path << endl;
        exit(1);
    }

    int a, b;
    while (inFile >> a >> b){
        Interval <T> t;
        t.low = a;
        t.high = b;
        set -> elements.push_back(t);
        // cout << "[" << a << "," << b << ")" << endl;
    }

    inFile.close();
}
template void load_interval_set<int>(char file_path[], IntervalSet<int> *set);