#include <iostream> 
#include <list>
#include <queue>
#include <vector>
#include "set_class.h"
#include "interval_set_class.h"
#include "search_algorithms.h"
#include "dip.h"

//using namespace std;

template <typename T1, typename T2, typename T3>
int barbayKenyon(T1 *sets, T2 k, list<T3> *intersection)
{
    // set eliminator element in [0,0], first element of first set
    T2 e = sets[0].elements[0];
    // Set index
    int i = 1;
    // ocurrences of e
    int occr = 1;

    int n = 0; // -> Eliminar
    // Init actual elements and size of initial set
    T2* actual_set=sets[i].elements;
    int size = sets[i].size;

    while ( e != -1 ){
        cout << "i: "<< i <<"\n";
        // position of e in i-set
        // int pos = exponentialSearch(actual_set, size, e);
        int pos = linearSearch(actual_set, size, e);
        cout << "pos: " << pos << "\n"; 
        cout << "e: " << e << "\n";
        if (actual_set[pos] == e){
            occr +=1;
            sets[i].pos = pos;
            if(occr == k){
                n+=1;
                intersection -> push_back(e);
                cout << "elemento de la intersección: " << e << "\n";
            }
        } 
        if(occr == k || actual_set[pos] != e){
            // Position remain and size of next set
            int next_set_pos = sets[i].pos;
            int next_set_size = sets[i].size;

            // No elements remain in the smallest set
            if (next_set_pos == next_set_size-1){
                e = -1;
                return 0;
            }

            // e is part of sets intersection      
            if (occr == k){   
                e = actual_set[pos+1];
                cout << "nuevo e: " << e << "\n";
                sets[i].pos = pos+1;
            }
            // e is not found in actual set
            else{   
                // pos it's a succesor index of e
                e = actual_set[pos];
                sets[i].pos = pos;
                cout << "nuevo e: " << e << "\n";
                
            }
            // restart occurrences
            occr = 1;
        }
        cout << "-------------------\n";
        // Cyclical index of sets
        i = (i+1)%k;
        actual_set = sets[i].elements;
        size = sets[i].size;
    }

    return 0;
}


template <typename T1, typename T2>
int forceBruteIntersection(T1 *sets, int k, list<T2> *intersection){
    // find smallest set to intersect
    int min = sets[0].size;
    int set_index = 0;
    for(int i=0; i < k; ++i){
        if (sets[i].size < min){
            min = sets[i].size;
            set_index = i;
        }
    }
    // Search elements of smallest set in a rest of sets
    T1 smallest_set = sets[set_index];
    for(int i=0; i < smallest_set.size; ++i){
        T2 e = smallest_set.elements[i];
        int occr = 1;
        for(int j=0; j < k; ++j){
            if (j != set_index){
                T1 set_to_search = sets[j];
                int pos = linearSearch(set_to_search.elements, set_to_search.size, e);
                if (set_to_search.elements[pos] == e){
                    occr++;
                    if (occr == k){
                        intersection -> push_back(e);
                    }
                }
            }
        }
    }
    return 0;
}


template <typename T>
int intervalBarbayKenyon(IntervalSet<T> *sets, int k, list< Interval<T> > *intersection)
{
    Interval<T> e = sets[0].elements[0]; // set eliminator element in [0,0], first element of first set
    sets[0].pos = 1; // mark first element of first set as visited

    int i = 1;  // Set index
    int occr = 1;  // ocurrences of e
    int size = sets[i].size;

    IntervalSet<T> actual_set = sets[i]; // Init actual elements and size of initial set

    while ( 1 ){
        Interval<T> intersect;
        
        cout << "i: "<< i <<"\n";
        
        // position of e in i-set
        int pos = intervalExponentialSearch(actual_set.elements, size, e, &intersect, actual_set.pos);
        cout << "pos: " << pos << "\n"; 
        cout << "e: [" << e.low << "," << e.high << "]\n";

        if (intersect.low != -1){
            cout<<"se encontro interseccion\n";
            e.low = intersect.low;
            e.high = intersect.high;
            occr += 1;
            sets[i].pos = pos + 1;
            if(occr == k){
                intersection -> push_back(e);
                cout << "elemento de la intersección: [" << e.low << "," << e.high << "]\n";
            }
        } 
        if(occr == k || intersect.low == -1){
            // Position remain and size of next set
            int next_set_pos = sets[i].pos;
            int next_set_size = sets[i].size;

            // No elements remain in the smallest set
            if (next_set_pos == next_set_size-1){
                return 0;
            }

            // e is part of sets intersection      
            if (occr == k){
                if (e.high < actual_set.elements[pos].high){
                    e.low = e.high ;
                    e.high = actual_set.elements[pos].high;
                    cout << "nuevo e: [" << e.low << "," << e.high << "]\n";
                }
                else{
                    e = actual_set.elements[pos+1];
                    cout << "nuevo e: [" << e.low << "," << e.high << "]\n";
                    sets[i].pos = pos+1;   
                }
            }
            
            // e is not found in actual set
            else{   
                // pos it's a succesor index of e
                e = actual_set.elements[pos];
                sets[i].pos = pos;
                cout <<"intersect --> [" << intersect.low << "," << intersect.high << "]\n";
                cout << "nuevo e: [" << e.low << "," << e.high << "]\n";
                
            }
            // restart occurrences
            occr = 1;
        }
        cout << "-------------------\n";
        // Cyclical index of sets
        i = (i+1)%k;
        actual_set = sets[i];
        size = sets[i].size;
    }

    return 0;
}


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
    
    list< Interval<int> > intersection;
    intervalBarbayKenyon(sets, 2, &intersection);

    cout << "Intersection Set:" << "\n" << "{ ";
    list< Interval<int> >::iterator it;
    for (it = intersection.begin(); it != intersection.end(); it++){
        cout <<"[" << it->low << "," << it->high << "] "; 
    }

    cout <<"}" << "\n";
    

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
    IntervalSet<int> set(2, a2);

    /* Initialize minheap of partitions*/
    // priority_queue< Partition<int> >  Q;
    /* Initialize minheap of partitions*/
    heap< Partition<int>, vector< Partition <int> >, greater< Partition <int> > > Q;

    createDIP<int>(&set, Q);


    cout << Q.size() << endl;
    for(auto e: Q) cout<< e.set.elements[0].high <<endl;

    /* while (!Q.empty()) {
        Partition<int> p = Q.top(); 
        Q.pop();
        cout << p.id << " " << p.lastInterval.high << "\n"; 
    } */
    /* cout << "Primer elemento en a2: " << "[" << set.elements[0].low <<", "<< set.elements[0].high << "]" << endl; */
    return 0;
}