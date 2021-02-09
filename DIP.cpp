#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "set_class.h"
#include "interval_set_class.h"
#include "dip.h"
#include "search_algorithms.h"


/* Function to sort interval set by start side of interval  */
bool compareInterval(Interval<int>& interval1, Interval<int>& interval2){
    if (interval1.low == interval2.low ){
        return interval1.high < interval2.high;
    }
    return interval1.low < interval2.low;
}

/* Operator to compare partitions in a minheap */
template <typename T>
bool operator>(const Partition<T>& partition1, const Partition<T>& partition2){
    return partition1.lastInterval.high > partition2.lastInterval.high;
}

template <typename T>
bool operator>(const numbersPartition<T> &partition1, const numbersPartition<T> &partition2){
    return partition1.lastInterval.high > partition2.lastInterval.high;
}

template<typename T> 
int if_intersection(Interval<T> a, Interval<T> b)
{
    // Not intersection case 
    if (a.high <= b.low || b.high  <= a.low){
        return 0;
    }

    // Exist intersection between a and b
    else{
        return 1;
    }
}
template int if_intersection<int>(Interval<int> a, Interval<int> b);


/* Disjoint interval partitions */
template <typename T>
void createDIP (IntervalSet <T>* set, heap< Partition<T>, vector< Partition<T> >, greater< Partition<T> > > &partitions){

    /* First sort set of intervals by low value */
    sort(set->elements.begin(), set->elements.end(), compareInterval);
    cout << "-> Termino Sort!!!" << endl;

    // cout << "Intervals sorted by start time : \n"; 
    // for (auto x : set->elements) 
        // cout << "[" << x.low << ", " << x.high << "] ";
    // cout << endl;
    
    int id_partitions = 0;
    for (auto x: set->elements){
        if (id_partitions == 0){
            vector< Interval <T> > intervalVector;
            intervalVector.push_back(x);
            IntervalSet <T> set = IntervalSet<T> (1, intervalVector);
            Partition <T> partition = Partition<T> (id_partitions, x, set);
            partitions.push(partition);
            id_partitions++;
        }

        else {
            if (if_intersection<T>(partitions.top().lastInterval, x)){
                vector< Interval <T> > intervalVector;
                intervalVector.push_back(x);
                IntervalSet <T> set = IntervalSet<T> (1, intervalVector);
                Partition <T> partition = Partition<T> (id_partitions, x, set);
                partitions.push(partition);
                id_partitions++;
            }
            else {
                Partition<T> p = partitions.top();
                p.set.elements.push_back(x);
                p.set.size++;
                p.lastInterval = x;
                partitions.pop();
                partitions.push(p);  
            }
            
        }
    }
    // for(auto e: partitions) cout<< e.set.elements[0].high <<endl;
}
template void createDIP<int>(IntervalSet <int>* set, heap< Partition<int>, vector< Partition<int> >, greater< Partition<int> > > &partitions);


template <typename T>
void createNumbersDIP (IntervalSet <T>* set, heap< numbersPartition<T>, vector< numbersPartition<T> >, greater< numbersPartition<T> > > &partitions){

    /* First sort set of intervals by low value */
    sort(set->elements.begin(), set->elements.end(), compareInterval);
    cout << "-> Termino Sort!!!" << endl;

    int id_partitions = 0;
    for (auto x: set->elements){
            if (id_partitions == 0){
                vector<T> numbersVector;
                for (int number = x.low; number<x.high; ++number) {
                    numbersVector.push_back(number);
                }
                Set <T> set = Set<T> ((x.high-x.low)+1, numbersVector);
                numbersPartition <T> partition = numbersPartition<T> (id_partitions, x, set);
                partitions.push(partition);
                id_partitions++;
            }
            else {
                if (if_intersection<T>(partitions.top().lastInterval, x)){
                    vector<T> numbersVector;
                    for (int number=x.low; number<x.high; ++number) {
                        numbersVector.push_back(number);
                    }
                    Set <T> set = Set<T> ((x.high-x.low)+1, numbersVector);
                    numbersPartition <T> partition = numbersPartition<T> (id_partitions, x, set);
                    partitions.push(partition);
                    id_partitions++;
                }
                else {
                    numbersPartition<T> p = partitions.top();
                    for (int number=x.low; number<x.high; ++number) {
                        p.set.elements.push_back(number);
                    }
                    p.set.size = p.set.size + (x.high - x.low) + 1;
                    p.lastInterval = x;
                    partitions.pop();
                    partitions.push(p);
                }
            }
        }
}
template void createNumbersDIP<int>(IntervalSet <int>* set, heap< numbersPartition<int>, vector< numbersPartition<int> >, greater< numbersPartition<int> > > &partitions);