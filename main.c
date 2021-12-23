#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000
#define shuffle_count 1000000

void shuffle(int *arr, int size);
void copy(int *a, int *b, int size);

int compare(int a, int b, int asc);
void swap(int *a, int *b);

void bubble_sort(int *arr, int size, int asc);
void selection_sort(int *arr, int size, int asc);
void insert_sort(int *arr, int size, int asc);
void merge_sort(int *arr, int *tmp, int start, int end, int asc);
void merge(int *arr, int *tmp, int start, int end, int asc);
void quick_sort(int *arr, int start, int end, int asc);

void print_arr(int *arr, int size);

int main(){
    srand((unsigned)time(NULL));

    int *arr1 = (int *)malloc(sizeof(int) * SIZE);
    int *arr2 = (int *)malloc(sizeof(int) * SIZE);
    clock_t start;

    for(int i = 1; i <= SIZE; i++){
        arr1[i - 1] = i;
    }

    printf("generating random array (size: %d)...\n", SIZE);
    shuffle(arr1, SIZE);
    printf("complete!\n\n");

    copy(arr1, arr2, SIZE);
    printf("performing bubble sort...\n");
    start = clock();
    bubble_sort(arr2, SIZE, 1);
    printf("bubble sort: %dms\n\n", clock() - start);

    copy(arr1, arr2, SIZE);
    printf("performing selection sort...\n");
    start = clock();
    selection_sort(arr2, SIZE, 1);
    printf("selection sort: %dms\n\n", clock() - start);

    copy(arr1, arr2, SIZE);
    printf("performing insert sort...\n");
    start = clock();
    insert_sort(arr2, SIZE, 1);
    printf("insert sort: %dms\n\n", clock() - start);

    copy(arr1, arr2, SIZE);
    int *tmp = (int *)malloc(sizeof(int) * SIZE);
    printf("performing merge sort...\n");
    start = clock();
    merge_sort(arr2, tmp, 0, SIZE - 1, 1);
    printf("merge sort: %dms\n\n", clock() - start);
    free(tmp);

    copy(arr1, arr2, SIZE);
    printf("performing quick sort...\n");
    start = clock();
    quick_sort(arr2, 0, SIZE - 1, 1);
    printf("quick sort: %dms\n\n", clock() - start);

    return 0;

    /*
    srand((unsigned)time(NULL));

    int *arr1 = (int *)malloc(sizeof(int) * SIZE);
    int *arr2 = (int *)malloc(sizeof(int) * SIZE);
    clock_t start, duration;
    clock_t bubble_duration = 0, selection_duration = 0, insert_duration = 0, merge_duration = 0, quick_duration = 0;
    double iter = 100;

    for(int i = 1; i <= SIZE; i++){
        arr1[i - 1] = i;
    }

    for(int i = 1; i <= iter; i++){
        printf("%d. generating random array (size: %d)...\n", i, SIZE);
        shuffle(arr1, SIZE);
        printf("complete!\n\n");

        copy(arr1, arr2, SIZE);
        start = clock();
        bubble_sort(arr2, SIZE, 1);
        duration = clock() - start;
        printf("bubble sort: %dms\n", duration);
        bubble_duration += duration;

        copy(arr1, arr2, SIZE);
        start = clock();
        selection_sort(arr2, SIZE, 1);
        duration = clock() - start;
        printf("selection sort: %dms\n", duration);
        selection_duration += duration;

        copy(arr1, arr2, SIZE);
        start = clock();
        insert_sort(arr2, SIZE, 1);
        duration = clock() - start;
        printf("insert sort: %dms\n", duration);
        insert_duration += duration;

        copy(arr1, arr2, SIZE);
        int *tmp = (int *)malloc(sizeof(int) * SIZE);
        start = clock();
        merge_sort(arr2, tmp, 0, SIZE - 1, 1);
        duration = clock() - start;
        printf("merge sort: %dms\n", duration);
        merge_duration += duration;
        free(tmp);

        copy(arr1, arr2, SIZE);
        start = clock();
        quick_sort(arr2, 0, SIZE - 1, 1);
        duration = clock() - start;
        printf("quick sort: %dms\n\n", duration);
        quick_duration += duration;
    }

    printf("avg bubble sort runtime: %.2fms\n", bubble_duration / iter);
    printf("avg selection sort runtime: %.2fms\n", selection_duration / iter);
    printf("avg insert sort runtime: %.2fms\n", insert_duration / iter);
    printf("avg merge sort runtime: %.2fms\n", merge_duration / iter);
    printf("avg quick sort runtime: %.2fms\n", quick_duration / iter);

    return 0;
    */
}

void shuffle(int *arr, int size){
    for(int i = 0; i < shuffle_count; i++){
        int a, b;
        a = rand() * rand() % size;
        b = rand() * rand() % size;
        swap(&arr[a], &arr[b]);
    }
}

void copy(int *a, int *b, int size){
    for(int i = 0; i < size; i++)
        b[i] = a[i];
}

int compare(int a, int b, int asc){
    if(asc == 0) return a < b;
    return a > b;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *arr, int size, int asc){
    int temp;
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(compare(arr[i], arr[j], asc))
                swap(&arr[i], &arr[j]);
        }
    }
}

void selection_sort(int *arr, int size, int asc){
    for(int i = 0; i < size; i++){
        int selected_idx = i;
        for(int j = i + 1; j < size; j++){
            if(compare(arr[selected_idx], arr[j], asc))
                selected_idx = j;
        }
        swap(&arr[i], &arr[selected_idx]);
    }
}

void insert_sort(int *arr, int size, int asc){
    int k;
    for(int i = 1; i < size; i++){
        k = arr[i];
        int j;
        for(j = i - 1; j >= 0 && compare(arr[j], k, asc); j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = k;
    }
}

void merge_sort(int *arr, int *tmp, int start, int end, int asc){
    if(start == end) return;
    int mid = (start + end) / 2;
    merge_sort(arr, tmp, start, mid, asc);
    merge_sort(arr, tmp, mid + 1, end, asc);
    merge(arr, tmp, start, end, asc);
}

void merge(int *arr, int *tmp, int start, int end, int asc){
    int mid = (start + end) / 2;
    int L = start, R = mid + 1, k = start, a;
    while(L <= mid && R <= end)
        tmp[k++] = (compare(arr[R], arr[L], asc)) ? arr[L++] : arr[R++];
    if(L > mid)
        for(a = R; a <= end; a++)
            tmp[k++] = arr[a];
    else
        for(a = L; a <= mid; a++)
            tmp[k++] = arr[a];
    for(a = start; a <= end; a++)
        arr[a] = tmp[a];
}

void quick_sort(int *arr, int start, int end, int asc){
    if(start >= end) return;
    int i = start, j = end, pivot = arr[start];
    while(i < j){
        while(compare(pivot, arr[j], asc)) j--;
        while(i < j && !compare(pivot, arr[i], asc)) i++;
        swap(&arr[i], &arr[j]);
    }
    swap(&arr[start], &arr[i]);
    quick_sort(arr, start, i - 1, asc);
    quick_sort(arr, i + 1, end, asc);
}

void print_arr(int *arr, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
