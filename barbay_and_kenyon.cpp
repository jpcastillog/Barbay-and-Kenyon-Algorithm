#include <iostream> 
#include <list>
#include "set_class.h"
#include "search_algorithms.h"

//using namespace std;

template <typename T1, typename T2>
int barbayKenyon(T1 *sets, T2 k)
{
    // set eliminator element in 0,0 
    T2 e = sets[0].elements[0];
    int i = 1; // set index
    int occr = 1;

    int n = 0;

    T2* actual_set=sets[i].elements;
    int size = sets[i].size;

    while (e < 1909877961){
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
                cout << "elemento de la intersección: " << e << "\n";
            }
        } 
        if(occr == k || actual_set[pos] != e){
            int next_set_pos = sets[i].pos;
            int next_set_size = sets[i].size;
            if (next_set_pos == next_set_size-1)
                return 0;
                  
            if (occr ==k){   
                e = actual_set[pos+1];
                cout << "nuevo e: " << e << "\n";
                sets[i].pos = pos+1;
            }
                
            else{
                if (next_set_pos == next_set_size-1)
                    return 0;
                e = actual_set[pos];
                sets[i].pos = pos;
                cout << "nuevo e: " << e << "\n";
                
            }
            occr = 1;
        }
        cout << "-------------------\n";
        //if (n==5) break;
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
    //exponentialSearch(a, n, x);
    barbayKenyon(sets, k);
    return 0;
}