#ifndef SEARCH_ALGORITHMS_H_
#define SEARCH_ALGORITHMS_H_

template<typename T>
int recursiveBinarySearch(T arr[], int l, int r, T x, int size);

template<typename T>
int iterativeBinarySearch(T array[], int low, int high, T x, int size);

template<typename T>
int exponentialSearch(T arr[], int n, T x);

template<typename T>
int linearSearch(T arr[], int n, T x);

#endif