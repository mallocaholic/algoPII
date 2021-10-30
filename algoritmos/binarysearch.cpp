#include <iostream>

using namespace std;
#define N 256

int binarySearch_r(int arr[], int l, int r, int x){
    
    if(r >= l){
        int mid = l - (l-r)/2;

        if( arr[mid] == x ) 
            return mid;

        else if( arr[mid] < x ) 
            return binarySearch_r( arr, mid+1, r, x);

        else
            return binarySearch_r( arr, l, mid-1, x );
    
    }
    
    return -1;

}

int main(){
    
    int arr[] = { 1, 3, 4, 7, 10, 15, 16, 18, 19, 20, 26, 27, 29, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 16;
    int result = binarySearch_r(arr, 0, n - 1, x);
    (result == -1) ? printf("Element is not present in array")
                   : printf("Element is present at index %d",
                            result);
    return 0;

}