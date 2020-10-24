#include <iostream>
#include <algorithm>
#include "set_class.h"
#include "interval_set_class.h"


/* Function to sort interval set by start side of interval  */
bool comparator_start(Interval<int>& interval1, Interval<int>& interval2){
    return interval1.low < interval2.low;
}


/* Disjoint interval partitions */
void DIP (IntervalSet <int>* set, vector< IntervalSet<int> >* partitions){
    /* First sort set of intervals by low value */
    

}