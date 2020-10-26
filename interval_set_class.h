#ifndef INTERVAL_SET_CLASS_H_
#define INTERVAL_SET_CLASS_H_

#include <iostream>
#include <vector>
#include "set_class.h"

using namespace std;

template <typename T>class IntervalSet{
    public:
        int size;
        // Interval<T>* elements;
        vector< Interval<T> > elements;
        int pos;
        // Constructors
        IntervalSet(){
            IntervalSet::pos=0;
        }

        IntervalSet(int size, vector < Interval<T> > array){
            IntervalSet::pos = 0;
            IntervalSet::size = size;
            // IntervalSet::elements = vector< Interval<int>;
            IntervalSet::elements = array;
        }
};
#endif