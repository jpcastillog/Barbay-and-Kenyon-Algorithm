
#include <iostream> 
#include <list>
#include "search_algorithms.h"
#include "set_class.h"

using namespace std;


/* 
        All functions to search return the index of element 
        in array or succesor if not in array
 */


template <typename T>
int recursiveBinarySearch(T arr[], int l, int r, T x, int size) 
{ 
    if (r >= l) 
    { 
        int mid = l + (r - l)/2; 
  
        if (arr[mid] == x) 
            return mid; 
  
        if (arr[mid] > x) 
            return recursiveBinarySearch(arr, l, mid-1, x, size); 
  
        return recursiveBinarySearch(arr, mid+1, r, x, size); 
    } 
    // if the element not in a set 
    if (l > size-1){
        return r;
    }
    if (r < 0){
        return l;
    }
    // check
    int delta_l = abs(arr[l] - x);
    int delta_r = abs(arr[r] - x);
    if (delta_l > x && delta_r > x){
        if (delta_l < delta_r){
            return l;
        }
        else 
            return r;
    }

    return arr[l]>arr[r]?l:r; 
} 
// Instantation of template function 
template int recursiveBinarySearch<int>(int arr[], int l, int r, int x, int size);


template <typename T>
int iterativeBinarySearch(T array[], int low, int high, T x, int size)
{
	while (low <= high)
	{
		int mid = low + (high - low) / 2;

		if (array[mid] == x)
			return mid;

		if (array[mid] < x)
			low = mid + 1;

		else
			high = mid - 1;
	}

    if (low > size - 1){
        return high;
    }
    if (high < 0){
        return low;
    }
    
    return array[low] < array[high]?high:low;
}
//Instantation of template function
template int iterativeBinarySearch<int>(int array[], int low, int high, int x, int size);


template<typename T>
int linearSearch(T arr[], int n, T x){

    for(int i=0; i < n; i++){
        // if x in arr return index of x in arr
        if (arr[i] == x){
            return i;   
        }
        // if x not in arr return succesor index
        if (arr[i] > x){
            return i;
        }    
    }
    
    return n-1;
}
//Instantation of template function
template int linearSearch<int>(int arr[], int n, int x);


template<typename T> 
int exponentialSearch(T arr[], int n, T x) 
{ 
    if (arr[0] == x) 
        return 0; 
    if (arr[n-1] < x)
        return n-1;
  
    int i = 1; 
    while (i < n && arr[i] <= x) 
        i = i*2; 
  
    return iterativeBinarySearch(arr, i/2, min(i, n), x, n); 
}
// Instantation of template function
template int exponentialSearch<int>(int arr[], int n, int x);


/* --------------------- Intervals implemetantions ---------------------*/

/* Return 1 if exist intersection and 0 if not */
template<typename T> 
int if_intersection(Interval<T> a, Interval<T> b, Interval<T>* intersection)
{
    T minLow, minHigh;
    // Not intersection case 
    if (a.high < b.low || b.high  < a.low){
        return 0;
    }

    // Exist intersection between a and b
    else{
        T lowRange, highRange;

        if (a.low < b.low)
            lowRange = b.low;
        else
            lowRange = a.low;

        if (a.high < b.high)
            highRange = a.high;
        else    
            highRange = b.high;
        
        intersection -> low = lowRange;
        intersection -> high = highRange;

        return 1;
    }
}
template int if_intersection<int>(Interval<int> a, Interval<int> b, Interval<int>* intersection);


template<typename T>
int intervalBinarySearch(vector< Interval<T> > &array, int low, int high, Interval<T> x, int size, Interval<T>* intersection)
{
    while (low <= high)
	{
		int mid = low + (high - low) / 2;
        
        int if_intersect = if_intersection(array[mid], x, intersection);
		if (if_intersect)
			return mid;

		if (array[mid].high < x.low)
			low = mid + 1;

		else
			high = mid - 1;
	}

    if (low > size - 1){
        return high;
    }
    if (high < 0){
        return low;
    }
    
    return array[low].high<array[high].low ? high : low;
}
template int intervalBinarySearch<int>(vector< Interval<int> > &array, int low, int high, Interval<int> x, int size, Interval<int>* intersection);


template<typename T> 
int intervalExponentialSearch(vector< Interval<T> > &arr, int n , Interval<T> x, Interval<T>* intersection, int initial_position)
{   
    Interval <T> interval_intersection;
    int if_intersect = if_intersection(arr[initial_position], x, intersection); 
    if (if_intersect){
        // intersection -> low = interval_intersection;
        return initial_position;
    }

    if (arr[n-1].high < x.low) {
        intersection -> low = -1;
        intersection -> high = -1;
        return n-1;
    }
    
    int i = initial_position + 1; 
    while (i < n && arr[i].high >= x.low) 
        i = i*2;
  
    return intervalBinarySearch(arr, i/2, min(i, n), x, n, intersection);
}
template int intervalExponentialSearch<int>(vector< Interval<int> > &arr, int n, Interval<int> x, Interval<int>* intersection, int initial_position);