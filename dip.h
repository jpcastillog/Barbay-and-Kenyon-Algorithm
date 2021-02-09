#ifndef DIP_H_
#define DIP_H_

#include <iostream>
#include <vector>
#include "set_class.h"
#include "interval_set_class.h"


template <typename T>
class Partition{
    public:
        int id;
        Interval<T> lastInterval;
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
class numbersPartition{
    public:
        int id;
        Interval <T> lastInterval;
        Set <T> set;

    // Constructors
    numbersPartition(){
        numbersPartition::id = 0;
    }

    numbersPartition(int id, Interval<T> lastInterval, Set<T> &set) {
        numbersPartition:: id = id;
        numbersPartition::lastInterval = lastInterval;
        numbersPartition::set = set;
    }
};

// Custom queue to create heap
template<class T, class Container, class Compare>
 class heap : public std::priority_queue<T, Container, Compare>{
    public:
        typename Container::iterator begin(){
            return std::priority_queue<T, Container, Compare>::c.begin();
        }
        typename Container::iterator end(){
            return std::priority_queue<T, Container, Compare>::c.end();
        }
};


template <typename T>
bool operator>(const Partition<T>& partition1, const Partition<T>& partition2);

template <typename T>
bool operator>(const numbersPartition<T> &partition1, const numbersPartition<T> &partition2);

template <typename T>
void createDIP (IntervalSet <T>* set, heap< Partition<T>, vector< Partition<T> >, greater< Partition<T> > > &partitions);

template <typename T>
void createNumbersDIP (IntervalSet <T>* set, heap< numbersPartition<T>, vector< numbersPartition<T> >, greater< numbersPartition<T> > > &partitions);
#endif