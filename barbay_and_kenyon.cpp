#include <iostream> 
#include <list>

using namespace std;

class Set{
    public: 
        int size;
        int *elements;
        int pos;
        Set(){
            pos=0;
        }
        Set(int size, int *array){
            Set::pos = 0;
            Set::size = size;
            Set::elements = new int[size];
            Set::elements = array;
        }
};


/*  ---------- Search Functions ----------  */

int binarySearch(int arr[], int l, int r, int x, int size) 
{ 
    if (r >= l) 
    { 
        int mid = l + (r - l)/2; 
  
        if (arr[mid] == x) 
            return mid; 
  
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid-1, x, size); 
  
        return binarySearch(arr, mid+1, r, x, size); 
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

int iterativeBinarySearch(int array[], int low, int high, int x, int size)
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


int exponentialSearch(int arr[], int n, int x) 
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

/* ---------- End Search Functions ---------- */

int barbayKenyon(Set *sets, int k)
{
    // set eliminator element in 0,0 
    long int e = sets[0].elements[0];
    int i = 1; // set index
    int occr = 1;

    int n = 0;

    int* actual_set=sets[i].elements;
    int size = sets[i].size;

    while (e < 1909877961){
        cout << "i: "<< i <<"\n";
        // position of e in i-set
        int pos = exponentialSearch(actual_set, size, e);
        cout << "pos: " << pos << "\n"; 
        cout << "e: " << e << "\n";
        if (actual_set[pos] == e){
            occr +=1;
            sets[i].pos = pos;
            if(occr == k){
                n+=1;
                cout << "elemento de la intersección: " << e << "\n";
            }
        } 
        if(occr == k || actual_set[pos] != e){
            if (occr ==k){
                int next_set_pos = sets[i].pos;
                int next_set_size = sets[i].size;
                if (next_set_pos == next_set_size-1)
                    return 0;
                e = actual_set[pos+1];
                cout << "nuevo e: " << e << "\n";
                sets[i].pos = pos+1;
            }
                
            else{
                int next_set_pos = sets[i].pos;
                int next_set_size = sets[i].size;
                if (next_set_pos == next_set_size-1)
                    return 0;
                e = actual_set[pos];
                sets[i].pos = pos;
                cout << "nuevo e: " << e << "\n";
                
            }
            occr = 1;
        }
        cout << "-------------------\n";
        //if (n==5) break;
        i = (i+1)%k;
        actual_set = sets[i].elements;
        size = sets[i].size;
    }

    return 0;
}

int main(){
    int k = 4;
    Set sets[k];

    int a[] = {1,2,3,7,8,10};
    int b[] = {3,4,8};
    int c[] = {1,3,8,10};
    int d[] = {1,2,3,4,5,8};

    sets[0] = Set(6,a);
    sets[1] = Set(3,b);
    sets[2] = Set(4,c);
    sets[3] = Set(6,d);
    
    barbayKenyon(sets, k);
    return 0;
}