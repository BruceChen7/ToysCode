#include "sort.h"
#include <assert.h>
#include <stdlib.h>

void swap(int a[], int pos, int another_pos) {
    int temp = a[pos];
    a[pos] = a[another_pos];
    a[another_pos] = temp;
}


static int partition(int* a, int from, int end) {
    int i = from;
    int last = from;
    for (i = from + 1; i <=  end - 1; i++) {
        if (a[i] < a[from]) {
          swap(a, ++last, i);
        }
    } 
    swap(a, from, last);
    return last;
}



// Quick Sort
void quickSort(int a[], int n) {
    if (n <= 1)
        return; 
    int pivot = rand() % n; 
    // Swap the privot element to the position 0
    swap(a, 0, pivot);
    int last = partition(a, 0, n);
    quickSort(a, last);
    quickSort(a + last + 1, n - last - 1);
}

// Bubble sort
void bubbleSort(int* arr, int n) {

    for(int i = n-1; i>=0; i--) {
        for(int j = 0; j <= i-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr, j, j+1);
            }            
        }
    }
}



// Select sort
void selectSort(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        int min = arr[i];
        int k = i;
        for(int j = i + 1; j < n; j++)  {
            if(arr[j]  < min) {
                min = arr[j];
                k = j;
            }
        }
 
        swap(arr,i, k);
    } 
}

// Insert Sort
void insertSort(int* arr, int n) {
    for(int i = 0; i < n ; i++) {
        for(int j = i+1 ; j >= 0 ; j--) {
            if(j>=1 && arr[j] < arr[j-1]) {
                swap(arr, j, j-1);
            }
        }
    }
} 

void mergeFromTo(int* arr, int from, int mid, int to) {

    assert(from <= mid);
    assert(mid <= to);

    if(from == to) {
        return; 
    }   
    int* a = (int *) malloc(to - from + 1);
    int i = mid; 
    int j = to;
    int k = to - from ;
  
    while( i>= from && j>= mid + 1) {
        if(arr[i] > arr[j]) {
            a[k--] = arr[i--]; 
        } else {
            a[k--] = arr[j--];
        }
    }

    assert(i < from || j == mid);
    
    while(i >= from )  {
        a[k--] = arr[i--];
    }
    
    while(j >= mid+1) {
        a[k--] = arr[j--];
    }
    assert(k == -1);
    k = 0;
    for(int i = from ; i <= to ; i++) {
        arr[i] = a[k++];
    }

    free(a);
}

void mergeSortHelper(int* arr, int from, int to) {
    if(from >= to) {
        return;
    }
    mergeSortHelper(arr, from,  from + (to - from) / 2);
    mergeSortHelper(arr, from + (to - from) /2  + 1, to);
    mergeFromTo(arr, from ,from + (to - from)/2 , to);
}

void mergeSort(int* arr, int n) {
    mergeSortHelper(arr, 0, n-1);
}

