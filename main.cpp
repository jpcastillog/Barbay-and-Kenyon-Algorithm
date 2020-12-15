#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include "interval_set_class.h"
#include "set_class.h"
#include "search_algorithms.h"
#include "barbay_and_kenyon.h"
#include "dip.h"
#include "load_tupples.h"



int main(){
    int k = 2;
    IntervalSet <int> sets[k];

    // int a[] = {1,2,3,7,8,10};
    // int b[] = {3,4,8};
    // int c[] = {1,3,8,10};
    // int d[] = {1,2,3,4,5,8};

    vector< Interval<int> >a{Interval<int>(1,2), Interval<int>(3,7)};
    vector< Interval<int> >b{Interval<int>(2,5), Interval<int>(6,7), Interval<int>(8,10)};

    sets[0] = IntervalSet<int>(2, a);
    sets[1] = IntervalSet<int>(3, b);
    // sets[2] = Set<int>(4,c);
    // sets[3] = Set<int>(6,d);

    cout<< a[0].low << "," << a[0].high <<"\n";

    // Test Interval Class
    Interval<int> interval_intersection = Interval<int> (0,0);
    Interval<int> interval1 = Interval<int>(6, 7);
    Interval<int> interval2 = Interval<int>(5, 8);
    int if_intersect = if_intersection(interval1, interval2, &interval_intersection);
    cout<<"Intersection: " << (if_intersect ? "True" : "False") << "\n"; 
    cout<< "low: "<< interval_intersection.low << '\n';
    cout<< "high: "<< interval_intersection.high << '\n';

    // Set of numbers
    // list<int> intersection; 
    // barbayKenyon(sets, k, &intersection);
    // forceBruteIntersection(sets, k, &intersection);
    cout << "*****************************************" << endl;
    list< Interval<int> > intersection;
    intervalBarbayKenyon(sets, 2, &intersection);

    cout << "Intersection Set:" << "\n" << "{ ";
    list< Interval<int> >::iterator it;
    for (it = intersection.begin(); it != intersection.end(); it++){
        cout <<"[" << it->low << "," << it->high << "] "; 
    }

    cout <<"}" << "\n";
    cout << "*****************************************" << endl;
    

    // Test min heap
    /* priority_queue< Interval<int>, vector< Interval <int> >, greater< Interval <int> > > Q;
    Q.push(interval1);
    Q.push(interval2);

    while (!Q.empty()) {
  
        Interval<int> p = Q.top(); 
  
        Q.pop();
        cout << p.low << " " << p.high << "\n"; 
    }
    
    cout << endl;
 */

    // test DIP
    vector< IntervalSet<int> > partitions;

    vector< Interval<int> > a2 {Interval<int>(3,7), Interval<int>(1,2), Interval<int>(3,6)};
    vector< Interval<int> > b2 {Interval<int>(2,5), Interval<int>(4,7), Interval<int>(8,10), Interval<int>(1,3)};
    IntervalSet<int> set1(3, a2);
    IntervalSet<int> set2(4, b2);

    /* Initialize minheap of partitions*/
    // priority_queue< Partition<int> >  Q;
    /* Initialize minheap of partitions*/
    heap< Partition<int>, vector< Partition <int> >, greater< Partition <int> > > Q1;
    heap< Partition<int>, vector< Partition <int> >, greater< Partition <int> > > Q2;

    createDIP<int> (&set1, Q1);
    createDIP<int> (&set2, Q2);

    cout << "Size Q1: " << Q1.size() << endl;
    cout << "Size Q2: " << Q2.size() << endl;
    // cout << Q1.size() << endl;
    // for(auto e: Q1) cout<< e.set.elements[0].high <<endl;

    list< Interval<int> > intersectionResult;
    intersectionDIP<int>(Q1, Q2, &intersectionResult, 1);

    cout << "************Disjoint Set Of Intervals Implementation************\n Intersection Set:" << "\n" << "{ ";
    list< Interval<int> >::iterator it2;
    for (it2 = intersectionResult.begin(); it2 != intersectionResult.end(); it2++){
        cout <<"[" << it2->low << "," << it2->high << "] "; 
    }

    cout <<"}" << "\n";

    IntervalSet<int> s1;
    IntervalSet<int> s2;
    // char file_path1[] = "./DataSets/Flight_tuples.txt";
    char file_path1[] = "./DataSets/Increment_data_0_1";
    char file_path2[] = "./DataSets/Increment_data_0_2";

    // Se cargan los conjuntos de intervalos
    load_interval_set(file_path1, &s1);
    load_interval_set(file_path2, &s2);

    cout << "tamaño del conjunto de pruebas s1: " << s1.elements.size() << endl;
    cout << "tamaño del conjunto de pruebas s2: " << s2.elements.size() << endl;
    // Se crean las particiones disjuntas
    heap< Partition<int>, vector< Partition <int> >, greater< Partition <int> > > H1;
    heap< Partition<int>, vector< Partition <int> >, greater< Partition <int> > > H2;

    createDIP<int> (&s1, H1);
    createDIP<int> (&s2, H2);

    // Perform de DiP intersection
    list< Interval<int> > r;
    intersectionDIP<int>(H1, H2, &r, 0);

    cout << "Size of intersection: " << r.size() << endl;
    cout << "FIN" << endl;
    

    return 0;
}