#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <chrono>
#include "interval_set_class.h"
#include "set_class.h"
#include "search_algorithms.h"
#include "barbay_and_kenyon.h"
#include "dip.h"
#include "load_tupples.h"

// template <typename T> 
bool compareInterval2(Interval<int>& interval1, Interval<int>& interval2){
    if (interval1.low == interval2.low ){
        return interval1.high < interval2.high;
    }
    return interval1.low < interval2.low;
}
// template bool compareInterval<int>(Interval<int>& interval1, Interval<int>& interval2);


template <typename T>
void writeOutput(list <Interval <T> > intersection_set, string name_file){
    // Sort list 
    intersection_set.sort(compareInterval2);
    ofstream file;
    file.open(name_file);
    list< Interval<int> >::iterator it;
    for (it = intersection_set.begin(); it != intersection_set.end(); it++){
        file << it->low << " " << it->high << endl; 
    }
    file.close();
}


void freeHeap(heap< Partition<int>*, vector< Partition <int>* >, orderIntervalsHeap<int> > &h){
    for(Partition<int>* p: h){
        delete p;
    }
}


template <typename T> 
void bruteForce(IntervalSet<T>* set1, IntervalSet<T>* set2, list< Interval<T> >* result){
    for (auto i: set1 -> elements){
        Interval<T> intersection;
        for (auto j: set2 -> elements){
            if (!(i.high <= j.low || j.high  <= i.low)){
                T lowRange, highRange;
                if (i.low < j.low)
                    lowRange = j.low;
                else
                    lowRange = i.low;

                if (i.high < j.high)
                    highRange = i.high;
                else    
                    highRange = j.high;
                
                intersection.low = lowRange;
                intersection.high = highRange;
                result -> push_back(intersection);
            }
        }
    }
}

int main(){


    // test DIP
    // vector< IntervalSet<int> > partitions;

    // vector< Interval<int> > a2 {Interval<int>(3,7), Interval<int>(1,2), Interval<int>(3,6)};
    // vector< Interval<int> > b2 {Interval<int>(2,5), Interval<int>(4,7), Interval<int>(8,10), Interval<int>(1,3)};
    // IntervalSet<int> set1(3, a2);
    // IntervalSet<int> set2(4, b2);

    // /* Initialize minheap of partitions*/
    // // priority_queue< Partition<int> >  Q;
    // /* Initialize minheap of partitions*/
    // heap< Partition<int>, vector< Partition <int> >, greater< Partition <int> > > Q1;
    // heap< Partition<int>, vector< Partition <int> >, greater< Partition <int> > > Q2;

    // createDIP<int> (&set1, Q1);
    // createDIP<int> (&set2, Q2);

    // cout << "Size Q1: " << Q1.size() << endl;
    // cout << "Size Q2: " << Q2.size() << endl;
    // // cout << Q1.size() << endl;
    // // for(auto e: Q1) cout<< e.set.elements[0].high <<endl;

    // list< Interval<int> > intersectionResult;
    // intersectionDIP<int>(Q1, Q2, &intersectionResult, 1);

    // cout << "************ Disjoint Set Of Intervals Implementation ************\n Intersection Set:" << "\n" << "{ ";
    // list< Interval<int> >::iterator it2;
    // for (it2 = intersectionResult.begin(); it2 != intersectionResult.end(); it2++){
    //     cout <<"[" << it2->low << "," << it2->high << "] "; 
    // }

    // cout <<"}" << "\n";

    IntervalSet<int> s1;
    IntervalSet<int> s2;

    // char file_path1[] = "./IntervalSets/Flight_tuples.txt";
    // char file_path2[] = "./IntervalSets/Flight_tuples.txt";

    // char file_path1[] = "./IntervalSets/Increment_data_0_1";
    // char file_path2[] = "./IntervalSets/Increment_data_0_2";

    // char file_path1[] = "./IntervalSets/Random_Uniform_1000000";
    // char file_path2[] = "./IntervalSets/Random_Uniform_10000002";

    // char file_path1[] = "./IntervalSets/Random_Uniform_10001";
    // char file_path2[] = "./IntervalSets/Random_Uniform_10002";

    // char file_path1[] = "./IntervalSets/Random_Uniform_10001";
    // char file_path2[] = "./IntervalSets/Random_Uniform_10002";

    // char file_path1[] = "./IntervalSets/brFlights/brFlightsA_100.txt";
    // char file_path2[] = "./IntervalSets/brFlights/brFlightsB_100.txt";

    // char file_path1[] = "./IntervalSets/brFlights/brFlightsA_1000.txt";
    // char file_path2[] = "./IntervalSets/brFlights/brFlightsB_1000.txt";

    // char file_path1[] = "./IntervalSets/brFlights/brFlightsA_10000.txt";
    // char file_path2[] = "./IntervalSets/brFlights/brFlightsB_10000.txt";

    // char file_path1[] = "./IntervalSets/brFlights/brFlightsA_100000.txt";
    // char file_path2[] = "./IntervalSets/brFlights/brFlightsB_100000.txt";

    // char file_path1[] = "./IntervalSets/brFlights/brFlightsA_1000000.txt";
    // char file_path2[] = "./IntervalSets/brFlights/brFlightsB_1000000.txt";

    // char file_path1[] = "./IntervalSets/brFlights/brFlightsA_500000.txt";
    // char file_path2[] = "./IntervalSets/brFlights/brFlightsB_500000.txt";


    // char file_path1[] = "./IntervalSets/atusac/atusacA_100.txt";
    // char file_path2[] = "./IntervalSets/atusac/atusacB_100.txt";

    // char file_path1[] = "./IntervalSets/atusac/atusacA_1000.txt";
    // char file_path2[] = "./IntervalSets/atusac/atusacB_1000.txt";

    // char file_path1[] = "./IntervalSets/atusac/atusacA_10000.txt";
    // char file_path2[] = "./IntervalSets/atusac/atusacB_10000.txt";

    // char file_path1[] = "./IntervalSets/atusac/atusacA_100000.txt";
    // char file_path2[] = "./IntervalSets/atusac/atusacB_100000.txt";

    // char file_path1[] = "./IntervalSets/atusac/atusacA_500000.txt";
    // char file_path2[] = "./IntervalSets/atusac/atusacB_500000.txt";

    // char file_path1[] = "./IntervalSets/atusac/atusacA_1000000.txt";
    // char file_path2[] = "./IntervalSets/atusac/atusacB_1000000.txt";


    // char file_path1[] = "./../../../data/intervals/invertedIndex/invertedIndexA10_10000000.txt";
    // char file_path2[] = "./../../../data/intervals/invertedIndex/invertedIndexB10_10000000.txt";

    // char file_path1[] = "./../../../data/intervals/invertedIndex/invertedIndexA10_1000000.txt";
    // char file_path2[] = "./../../../data/intervals/invertedIndex/invertedIndexB10_1000000.txt";

    char file_path1[] = "./../../../data/intervals/atusac/atusacA_100000.txt";
    char file_path2[] = "./../../../data/intervals/atusac/atusacB_100000.txt";

    // char file_path1[] = "./../../../data/intervals/atusac/atusacA_500000.txt";
    // char file_path2[] = "./../../../data/intervals/atusac/atusacB_500000.txt";

    // char file_path1[] = "./../../../data/intervals/atusac/atusacA_1000000.txt";
    // char file_path2[] = "./../../../data/intervals/atusac/atusacB_1000000.txt";


    // Se cargan los conjuntos de intervalos
    load_interval_set(file_path1, &s1);
    load_interval_set(file_path2, &s2);

    cout << "tamaño del conjunto de pruebas s1: " << s1.elements.size() << endl;
    cout << "tamaño del conjunto de pruebas s2: " << s2.elements.size() << endl;
    // Se crean las particiones disjuntas
    heap< Partition<int>*, vector< Partition <int>* >, orderIntervalsHeap<int> > H1;
    heap< Partition<int>*, vector< Partition <int>* >, orderIntervalsHeap<int> > H2;


    // heap< numbersPartition<int>*, vector< numbersPartition <int>* >, greater< numbersPartition <int>* > > NH1;
    // heap< numbersPartition<int>*, vector< numbersPartition <int>* >, greater< numbersPartition <int>* > > NH2;

    heap< numbersPartition<int>*, vector< numbersPartition <int>* >, orderNumbersHeap<int> > NH1;
    heap< numbersPartition<int>*, vector< numbersPartition <int>* >, orderNumbersHeap<int> > NH2;

    // createNumbersDIP(&s1, NH1);
    // createNumbersDIP(&s2, NH2);

    createDIP<int> (&s1, H1);
    createDIP<int> (&s2, H2);

    // s1.elements.clear();
    // s2.elements.clear();

    cout << "Partitions set 1 size: " << H1.size() << endl;
    cout << "Partitions set 2 size: " << H2.size() << endl;

    // cout << "Partitions set 1 size: " << NH1.size() << endl;
    // cout << "Partitions set 2 size: " << NH2.size() << endl;

    // auto start_dip = std::chrono::high_resolution_clock::now();
    // list< Interval<int> > rr;
    // intersectionNumbersDIP<int>(NH1, NH2, &rr);
    // auto end_dip = std::chrono::high_resolution_clock::now();
    // auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_dip - start_dip);
    // cout << "Time execution: " << elapsed.count() * 10e-9 << "[ns]" << endl; 
    // cout << "Size of intersection Barbay and Kenyon: " << rr.size() << endl;

    // list< Interval<int> >::iterator it;
    // for (it = rr.begin(); it != rr.end(); it++){
    //     cout << "[" << it->low << ", " << it->high << "] ";
    // }
    // cout << endl;

    // Perform de Barbay and Kenyon DiP intersection
    auto start_dip = std::chrono::high_resolution_clock::now();
    list< Interval<int> > r;
    intersectionDIP<int>(H1, H2, &r, 0);
    auto end_dip = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end_dip - start_dip);
    
    cout << "Time execution: " << elapsed.count() * 10e-9 << "[ns]" << endl; 
    cout << "Size of intersection DIP: " << r.size() << endl;
    cout << "FIN" << endl;
    r.clear();

    // // writeOutput(r, "Resultado_1000_DIP.txt");
    
    // // Perform de classic DiP intersection
    auto start_classic_dip = std::chrono::high_resolution_clock::now();
    list< Interval<int> > r1;
    intersectionDIP<int>(H1, H2, &r1, 1);
    auto end_classic_dip = std::chrono::high_resolution_clock::now();
    auto elapsed_classic_dip = std::chrono::duration_cast<std::chrono::nanoseconds>(end_classic_dip - start_classic_dip);

    cout << "Time execution: " << elapsed_classic_dip.count() * 10e-9 << "[ns]" << endl;
    cout << "Size of intersection classic DIP: " << r1.size() << endl;
    cout << "FIN" << endl;
    r1.clear();
    // list< Interval<int> > r2;
    // bruteForce(&s1, &s2, &r2);  

    // cout << "Size of intersection Brute Force: " << r2.size() << endl;
    // cout << "FIN" << endl;
    // writeOutput(r2, "Resultado_1000_BF.txt");


    auto start_exp_dip = std::chrono::high_resolution_clock::now();
    list< Interval<int> > r2;
    intersectionDIP<int>(H1, H2, &r2, 2);
    auto end_exp_dip = std::chrono::high_resolution_clock::now();
    auto elapsed_exp_dip = std::chrono::duration_cast<std::chrono::nanoseconds>(end_exp_dip - start_exp_dip);

    cout << "Time execution: " << elapsed_exp_dip.count() * 10e-9 << "[ns]" << endl;
    cout << "Size of intersection classic DIP: " << r2.size() << endl;
    cout << "FIN" << endl;
    r2.clear();

    freeHeap(H1);
    freeHeap(H2);

    return 0;
}