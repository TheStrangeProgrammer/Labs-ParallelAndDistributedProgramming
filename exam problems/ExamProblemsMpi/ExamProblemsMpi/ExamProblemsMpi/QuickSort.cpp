// QucikSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <mpi.h>

using namespace std;

void swap(int*a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void printArray(int arr[], int size) {
	cout << "Array: ";
	for (int i = 0; i < size; i++) {
		cout << " " << arr[i];
	}
	cout << endl;
}

int partition(int arr[], int low, int high) {
	cout << "low: " << low << " high: " << high << endl;
	int pivot = arr[high];//pivot
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);

}

void quicksort(int arr[], int low, int high) {
	if (low < high) {
		int p = partition(arr, low, high);
		cout << p << " " << arr[p] << endl;
		quicksort(arr, low, p - 1);
		quicksort(arr, p + 1, high);
	}

}

int main()
{
	MPI_Init(0, 0);
	//int arr[] = { 10,7,9, 8, 1,5 };
	int arr[] = { 7,2,1,5,8,5,3,4 };
	int n = sizeof(arr) / sizeof(arr[0]);
	printArray(arr, n);

	quicksort(arr, 0, n - 1);

	printArray(arr, n);
	MPI_Finalize();
	return 0;
}

