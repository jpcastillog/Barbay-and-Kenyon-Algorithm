
#include <iostream> 
#include <list>
#include "search_algorithms.h"
#include "set_class.h"

using namespace std;

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
    if (l > size-1){
        return r;
    }
    if (r < 0){
        return l;
    }
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


/* ---------------------Intervals implemetantions---------------------*/

template<typename T> 
int intervalExponentialSearch(Interval<T> arr[], int n , Interval<T> x)
{
    T x_low = x.low;
    T x_high = x.high;

    if (arr[0] ){}
    if (arr[n-1].high < x.low){
        return -1;
    }
}

