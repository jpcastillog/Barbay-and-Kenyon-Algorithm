#ifndef DIP_H_
#define DIP_H_

#include <iostream>
#include <vector>
#include "set_class.h"
#include "interval_set_class.h"


template <typename T>class Partition{
    public:
        int id;
        Interval <T> lastInterval;
        IntervalSet<T> set;

        // Constructors
        Partition(){
            Partition::id = 0;
        }

        Partition(int id, Interval<T> lastInterval, IntervalSet<T> &set){
            Partition::id = id;
            Partition::lastInterval = lastInterval;
            Partition::set = set;
        }
};
template <typename T>
bool operator>(const Partition<T>& partition1, const Partition<T>& partition2);

template <typename T>
int DIP (IntervalSet <T>* set, priority_queue< Partition<T>, vector< Partition<T> >, greater< Partition<T> > >& partitions);

#endif