#ifndef SEARCH_ALGORITHMS_H_
#define SEARCH_ALGORITHMS_H_

#include "set_class.h"
#include <vector>
#include <list>

template<typename T>
int recursiveBinarySearch(T arr[], int l, int r, T x, int size);

template<typename T>
int iterativeBinarySearch(T array[], int low, int high, T x, int size);

template<typename T>
int exponentialSearch(T arr[], int n, T x);

template<typename T>
int linearSearch(T arr[], int n, T x);

template<typename T>
int if_intersection(Interval<T> a, Interval<T> b, Interval<T>* intersection);

template<typename T>
int intervalExponentialSearch(vector< Interval<T> > &arr, int n , Interval<T> x, Interval<T>* intersection, int initial_position);

template<typename T>
int intervalBinarySearch(vector< Interval<T> > &array, int low, int high, T x, int size, Interval<T>* intersection);

template<typename T>
int intervalLinearSearch(vector < Interval<T> > &arr, int n, Interval<T> x, list< Interval<T> > *intersections, int initial_position, int *last_comparision);


// template<typename T>
// int if_intersection(Interval<T> a, Interval<T> b, Interval<T>* intersection);

#endif