#include <iostream> 
#include <list>
#include "set_class.h"
#include "search_algorithms.h"

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
        int pos = exponentialSearch(actual_set, size, e);
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

int main(){
    int k = 4;
    Set <int> sets[k];

    int a[] = {1,2,3,7,8,10};
    int b[] = {3,4,8};
    int c[] = {1,3,8,10};
    int d[] = {1,2,3,4,5,8};

    sets[0] = Set<int>(6,a);
    sets[1] = Set<int>(3,b);
    sets[2] = Set<int>(4,c);
    sets[3] = Set<int>(6,d);
    int  n = 6;
    int x = 3;
    list<int> intersection; 
    //exponentialSearch(a, n, x);
    barbayKenyon(sets, k, &intersection);
    cout << "Intersection set:" << "\n" << "{ ";
    list<int>::iterator it;
    for (it = intersection.begin(); it != intersection.end(); it++){
        cout << *it << " "; 
    }
    cout <<"}" << "\n";
    
    return 0;
}