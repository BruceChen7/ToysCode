#include "base/sort.h"
#include <stdio.h>

static void printArr(int* arr, int n) {
       for(int i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

static void testBubbleSort() {
    int arr1[] = {1, 5, 3, 4, 2};
    int arr2[] = {2, 1, 4, 3, 5};
    int arr3[] = {1, 1, 1, 1, 1};
    int arr4[] = {5, 4, 3, 2, 1};
    int arr5[] = {6, 2, 1, 3, 4};
    int arr6[] = {6, 5, 4, 3, 2};
    
    bubbleSort(arr1, 5);
    bubbleSort(arr2, 5);
    bubbleSort(arr3, 5);
    bubbleSort(arr4, 5);
    bubbleSort(arr5, 5);
    bubbleSort(arr6, 5);
    printArr(arr1, 5);
    printArr(arr2, 5);
    printArr(arr3, 5);
    printArr(arr4, 5);
    printArr(arr5, 5);
    printArr(arr6, 5);
}

static void testSelectSort() {
    int arr1[] = {1, 5, 3, 4, 2};
    int arr2[] = {2, 1, 4, 3, 5};
    int arr3[] = {1, 1, 1, 1, 1};
    int arr4[] = {5, 4, 3, 2, 1};
    int arr5[] = {6, 2, 1, 3, 4};
    int arr6[] = {6, 5, 4, 3, 2};
    selectSort(arr2, 5);
    selectSort(arr3, 5);
    selectSort(arr4, 5);
    selectSort(arr5, 5);
    selectSort(arr6, 6);
    printArr(arr2, 5);
    printArr(arr3, 5);
    printArr(arr4, 5);
    printArr(arr5, 5);
    printArr(arr6, 5);
}

static void testQuickSort() {
    int arr1[] = {1, 5, 3, 4, 2};
    int arr2[] = {2, 1, 4, 3, 5};
    int arr3[] = {1, 1, 1, 1, 1};
    int arr4[] = {5, 4, 3, 2, 1};
    int arr5[] = {6, 2, 1, 3, 4};
    int arr6[] = {6, 5, 4, 3, 2};
    quickSort(arr1, 5);
    quickSort(arr2, 5);
    quickSort(arr3, 5);
    quickSort(arr4, 5);
    quickSort(arr5, 5);
    quickSort(arr6, 5);
    printArr(arr1, 5);
    printArr(arr2, 5);
    printArr(arr3, 5);
    printArr(arr4, 5);
    printArr(arr5, 5);
    printArr(arr6, 6);
}

static void testMergeSort() {
    int arr1[] = {1, 5, 3, 4, 2};
    int arr2[] = {2, 1, 4, 3, 5};
    int arr3[] = {1, 1, 1, 1, 1};
    int arr4[] = {5, 4, 3, 2, 1};
    int arr5[] = {6, 2, 1, 3, 4};
    int arr6[] = {6, 5, 4, 3, 2};    
    mergeSort(arr2, 5);
    mergeSort(arr3, 5);
    mergeSort(arr4, 5);
    mergeSort(arr5, 5);
    printArr(arr2, 5);
    printArr(arr3, 5);
    printArr(arr4, 5);
    printArr(arr5, 5);
}

static void testHeapSort() {
    int arr1[] = {1, 5, 3, 4, 2};
    int arr2[] = {2, 1, 4, 3, 5};
    int arr3[] = {1, 1, 1, 1, 1};
    int arr4[] = {5, 4, 3, 2, 1};
    int arr5[] = {6, 2, 1, 3, 4};
    int arr6[] = {6, 5, 4, 3, 2};  
    heapSort(arr1, 5);
    heapSort(arr2, 5);
    heapSort(arr3, 5);
    heapSort(arr4, 5);
    heapSort(arr5, 5);
    heapSort(arr6, 5);
    printArr(arr1, 5);
    printArr(arr2, 5);
    printArr(arr3, 5);
    printArr(arr4, 5);
    printArr(arr5, 5);
}

int main() {
    testBubbleSort();
    testSelectSort();
    testQuickSort();
    testMergeSort();
    testHeapSort();
    return 0;
}