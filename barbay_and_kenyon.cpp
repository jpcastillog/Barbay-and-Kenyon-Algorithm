#include <iostream> 
#include <list>
#include <queue>
#include <vector>
#include "set_class.h"
#include "interval_set_class.h"
#include "search_algorithms.h"
#include "dip.h"

//using namespace std;

template <typename T>
int barbayKenyon(Set<T> *sets, int k, list<T> *intersection)
{
    // set eliminator element in [0,0], first element of first set
    T e = sets[0].elements[0];
    // Set index
    int i = 1;
    // ocurrences of e
    int occr = 1;

    int n = 0; // -> Eliminar
    // Init actual elements and size of initial set
    T* actual_set=sets[i].elements;
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
template int barbayKenyon<int>(Set<int> *sets, int k, list<int> *intersection); 



template <typename T>
int forceBruteIntersection(Set<T> *sets, int k, list<T> *intersection){
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
    Set<T> smallest_set = sets[set_index];
    for(int i=0; i < smallest_set.size; ++i){
        T e = smallest_set.elements[i];
        int occr = 1;
        for(int j=0; j < k; ++j){
            if (j != set_index){
                Set<T> set_to_search = sets[j];
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
template int forceBruteIntersection<int>(Set<int> *sets, int k, list<int> *intersection);


template <typename T>
int intervalBarbayKenyon(IntervalSet<T> *sets, int k, list< Interval<T> > *intersection)
{
    Interval<T> e = sets[0].elements[0]; // set eliminator element in [0,0], first element of first set
    // sets[0].pos = 0; // mark first element of first set as visited

    int i = 1;  // Set index
    int occr = 1;  // ocurrences of e
    int size = sets[i].size;
    IntervalSet<T> actual_set = sets[i]; // Init actual elements and size of initial set

    while ( 1 ){
        actual_set = sets[i];
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
            
            if(occr == k){
                intersection -> push_back(e);
                cout << "elemento de la intersección: [" << e.low << "," << e.high << "]\n";
            }
        } 
        if(occr == k || intersect.low == -1){
            // Position remain and size of next set
            int next_set_pos = sets[i].pos;
            int next_set_size = sets[i].size;


            // e is part of sets intersection      
            if (occr == k){
                if (e.high < sets[i].elements[pos].high){
                    e.low = e.high ;
                    e.high = sets[i].elements[pos].high;
                    cout << "nuevo e: [" << e.low << "," << e.high << "]\n";
                    sets[i].pos = pos;

                }
                else{
                    e = actual_set.elements[pos+1];
                    cout << "nuevo e: [" << e.low << "," << e.high << "]\n";
                    sets[i].pos = pos+1;
                }
            }
            
            // No elements remain in the smallest set
            else if (next_set_pos == next_set_size-1){
                return 0;
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
        size = sets[i].size;
    }

    return 0;
}
template int intervalBarbayKenyon<int>(IntervalSet<int> *sets, int k, list< Interval<int> > *intersection);


template <typename T>
void intersectionDIP(heap< Partition<T>, vector< Partition<T> >, greater< Partition<T> > > &partitions1, heap< Partition<T>, vector< Partition<T> >, greater< Partition<T> > > &partitions2, list< Interval<T> > *intersection){
    for (auto i: partitions1){
        IntervalSet<T> p1 = i.set;
        for (auto j: partitions2){
            IntervalSet<T> p2 = j.set;
            IntervalSet<T> sets_to_intersect [] = {p1, p2};
            cout << "***Intersection Between partitions " << i.id << " and " << j.id << endl;
            intervalBarbayKenyon(sets_to_intersect, 2, intersection);
        }
    }
}
template void intersectionDIP<int>(heap< Partition<int>, vector< Partition<int> >, greater< Partition<int> > > &partitions1, heap< Partition<int>, vector< Partition<int> >, greater< Partition<int> > > &partitions2, list< Interval<int> > *intersection);