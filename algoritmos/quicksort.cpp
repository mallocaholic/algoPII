#include <iostream>
#define N 10
using namespace std;
//P is pivot
void swap(int arr[], int x, int y){

	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;

}

int partition(int arr[], int p, int r){
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

void quicksort(int arr[], int p, int r){
	if( p < r ){
		int q = partition(arr, p, r);
		quicksort(arr, p, q-1);
		quicksort(arr, q+1, r);
	}
		for(int i = 0; i <= r; i++)
			std::cout << arr[i] << " "; 
	std::cout << std::endl;
}

int main(){

	int arr[] = {3, 1, 4, 6, 8 , 2, 10};
	int size = sizeof(arr)/sizeof(arr[0]);
	quicksort(arr, 0, size-1); 
	return 0;  
}
