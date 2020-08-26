#ifndef INTERVAL_SET_CLASS_H_
#define INTERVAL_SET_CLASS_H_

#include <iostream>
#include "set_class.h"

using namespace std;

template <typename T>class IntervalSet{
    public:
        int size;
        Interval<T>* elements;
        int pos;
        // Constructors
        IntervalSet(){
            IntervalSet::pos=0;
        }

        IntervalSet(int size, Interval<T>* array){
            IntervalSet::pos = 0;
            IntervalSet::size = size;
            IntervalSet::elements = new Interval<int>[size];
            IntervalSet::elements = array;
        }
};
#endif