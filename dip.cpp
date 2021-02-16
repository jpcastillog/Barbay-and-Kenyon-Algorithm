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
bool operator>(const Partition<T> &partition1, const Partition<T> &partition2){
    return partition1.lastInterval.high > partition2.lastInterval.high;
}


// template <typename T>
// bool operator>(const (numbersPartition<T>*) &partition1, const (numbersPartition<T>*) &partition2){
//     return partition1->lastInterval.high > partition2->lastInterval.high;
// }
// template bool operator> <int>(const numbersPartition<int> *partition1, const numbersPartition<int> *partition2);


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


template<typename T> 
int if_intersection_spaced(Interval<T> a, Interval<T> b)
{
    // Not intersection case 
    if (a.high < b.low || b.high  < a.low){
        return 0;
    }

    // Exist intersection between a and b
    else{
        return 1;
    }
}
template int if_intersection_spaced<int>(Interval<int> a, Interval<int> b);


/* Disjoint interval partitions */
template <typename T>
void createDIP (IntervalSet <T>* set, heap< Partition<T>*, vector< Partition<T>* >, orderIntervalsHeap<T> > &partitions){

    /* First sort set of intervals by low value */
    sort(set->elements.begin(), set->elements.end(), compareInterval);
    cout << "-> Termino Sort!!!" << endl;
    
    typename vector< Interval <T> > ::iterator it;
    int id_partitions = 0;
    for (it = set->elements.begin(); it != set->elements.end(); ++it){
    // for (auto x: set->elements){
        if (id_partitions == 0){
            vector< Interval <T> > intervalVector;
            intervalVector.push_back(*it);
            IntervalSet <T> set = IntervalSet<T> (1, intervalVector);
            Partition <T> *partition = new Partition<T> (id_partitions, *it, set);
            partitions.push(partition);
            id_partitions++;
        }

        else {
            if (if_intersection<T>(partitions.top()->lastInterval, *it)){
                vector< Interval <T> > intervalVector;
                intervalVector.push_back(*it);
                IntervalSet <T> set = IntervalSet<T> (1, intervalVector);
                Partition <T> *partition = new Partition<T> (id_partitions, *it, set);
                partitions.push(partition);
                id_partitions++;
            }
            else {
                Partition<T> *p = partitions.top();
                p -> set.elements.push_back(*it);
                p -> set.size++;
                p -> lastInterval = *it;
                partitions.pop();
                partitions.push(p);  
            }
            
        }
    }
}
template void createDIP<int>(IntervalSet <int>* set, heap< Partition<int>*, vector< Partition<int>* >, orderIntervalsHeap<int> > &partitions);


template <typename T>
// void createNumbersDIP (IntervalSet <T>* set, heap< numbersPartition<T>*, vector< numbersPartition<T>* >, greater< numbersPartition<T>* > > &partitions){
void createNumbersDIP (IntervalSet <T>* set, heap< numbersPartition<T>*, vector< numbersPartition<T>* >, orderNumbersHeap<T> > &partitions){
    /* First sort set of intervals by low value */
    sort(set->elements.begin(), set->elements.end(), compareInterval);
    cout << "-> Termino Sort!!!" << endl;

    int id_partitions = 0;
    typename vector< Interval <T> > ::iterator it;
    for (it = set->elements.begin(); it != set->elements.end(); ++it){
        if (id_partitions == 0){
            vector<T> numbersVector;
            for (int number = it->low; number < it->high; ++number) {
                numbersVector.push_back(number);
            }
            Set <T> set = Set<T> ((it->high - it->low), numbersVector);
            numbersPartition <T> *partition = new numbersPartition<T> (id_partitions, *it, set);
            partitions.push(partition);
            id_partitions++;
        }
        else {
            if (if_intersection_spaced<T>(partitions.top()->lastInterval, *it)){
                vector<T> numbersVector;
                for (int number=it->low; number < it->high; ++number) {
                    numbersVector.push_back(number);
                }
                Set <T> set = Set<T> ((it->high - it->low), numbersVector);
                numbersPartition<T> *partition = new numbersPartition<T> (id_partitions, *it, set);
                partitions.push(partition);
                id_partitions++;
            }
            else {
                numbersPartition<T> *p = partitions.top(); 
                for (T number=it->low; number < it->high; ++number)
                    p->set.elements.push_back(number);
                
                p -> set.size = p -> set.size + (it->high - it->low);
                p -> lastInterval = *it;
                partitions.pop();
                partitions.push(p);
            }
        }
    }
}
// template void createNumbersDIP<int>(IntervalSet<int> *set, heap< numbersPartition<int>*, vector< numbersPartition<int>* >, greater< numbersPartition<int>* > > &partitions);
template void createNumbersDIP<int>(IntervalSet<int> *set, heap< numbersPartition<int>*, vector< numbersPartition<int>* >, orderNumbersHeap<int> > &partitions);