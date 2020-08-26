#ifndef SET_CLASS_H_
#define SET_CLASS_H_

#include <iostream>

using namespace std;

template <typename T>class Set{
    public: 
        int size;
        T *elements;
        int pos;
        // Constructors
        Set(){
            pos=0;
        }
         
        Set(int size, T *array){
            Set::pos = 0;
            Set::size = size;
            Set::elements = new T[size];
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

#endif