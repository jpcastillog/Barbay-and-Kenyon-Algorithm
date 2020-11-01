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


// template<class T, class C, class O>
// struct heap : std::priority_queue<T, C, O>{
//     using priority_queue<T, C, O>::priority_queue;
//     typename C::iterator begin() {return std::priority_queue<T, C, O>::c.begin(); }
//     typename C::iterator end() {return std::priority_queue<T, C, O>::c.end(); }    
// };


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
void createDIP (IntervalSet <T>* set, heap< Partition<T>, vector< Partition<T> >, greater< Partition<T> > >& partitions);

#endif