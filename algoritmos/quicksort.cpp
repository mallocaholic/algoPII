#include <iostream>
#define N 10
using namespace std;
//P is pivot
void swap(int arr[], int x, int y){

	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;

}

int partition(int arr[], int p, int r, int size){
	int i = p-1, j;
	for( j = p; j < r; j++ ){
		
		
		if( arr[j] <= arr[r] ){
			i++;
			swap(arr[j], arr[i]);			
		}	
	}
	swap( arr[i+1], arr[r] );
			
	return i+1;	
}

int quicksort(int arr[], int p, int r, int size){
	if( p < r ){
		int q = partition(arr, p, r, size);
		for( int m = size-1; m > 0; m-- )
			std::cout << arr[m] << " ";
		std::cout << std::endl; 
		quicksort(arr, p, q-1, size);
		quicksort(arr, q+1, r, size);
	}
		// for(int i = 0; i <= r; i++)
			// std::cout << arr[i] << " "; 
	// std::cout << std::endl;
}

int main(){

	int n, D, num;
	cin >> N >> D;

	int arr[] = {6,4,0,3,8,5,2,7,1,9};
	int size = sizeof(arr)/sizeof(arr[0]);
	quicksort(arr, 0, size-1, size); 
	return 0;  
}
