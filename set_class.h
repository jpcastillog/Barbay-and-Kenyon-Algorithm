#ifndef SET_CLASS_H_
#define SET_CLASS_H_

#include <iostream>
#include <vector>

using namespace std;

template <typename T>class Set{
    public: 
        int size;
        vector<T> elements;
        int pos;
        // Constructors
        Set(){
            pos=0;
        }
         
        Set(int size, vector<T> array){
            Set::pos = 0;
            Set::size = size;
            Set::elements = array;
        }
};

template <typename T>class Interval{
    public:
        T low;
        T high;
        //Constructor  
        Interval(){
            Interval::low = -1;
            Interval::high = -1;
        } 
        Interval(T low, T high){
            Interval::low = low;
            Interval::high = high;
        }
};

/* template <typename T>
bool operator>(const Interval<T>& interval1, const Interval<T>& interval2){
    return interval1.high > interval2.high;
} */

#endif