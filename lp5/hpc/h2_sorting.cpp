#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

void merge(int arr[], int first0, int last0, int first1, int last1)
{
    int temp[1000];
    int i, j, k;
    i = first0;
    j = first1;
    k = 0;
    while (i <= last0 && j <= last1)
    {
        if (arr[i] < arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }
    while (i <= last0)
    {
        temp[k++] = arr[i++];
    }
    while (j <= last1)
    {
        temp[k++] = arr[j++];
    }
    for (i = first0, j = 0; i <= last1; i++, j++)
    {
        arr[i] = temp[j];
    }
}

void parallel_mergesort(int arr[], int first, int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                parallel_mergesort(arr, first, mid);
            }
#pragma omp section
            {
                parallel_mergesort(arr, mid + 1, last);
            }
        }
        merge(arr, first, mid, mid + 1, last);
    }
}

void normal_mergesort(int arr[], int first, int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        normal_mergesort(arr, first, mid);
        normal_mergesort(arr, mid + 1, last);
        merge(arr, first, mid, mid + 1, last);
    }
}

void parallel_bubblesort(int arr[], int arr_size)
{
    for (int i = 0; i < arr_size - 1; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < arr_size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
#pragma omp parallel critical
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

void normal_bubblesort(int arr[], int arr_size)
{
    for (int i = 0; i < arr_size - 1; i++)
    {
        for (int j = 0; j < arr_size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int arr_size;
    cout << "Enter Number of Elements: ";
    cin >> arr_size;

    int arr0[arr_size], arr1[arr_size], arr2[arr_size], arr3[arr_size];
    cout << "Enter " << arr_size << " Elements: ";
    for (int i = 0; i < arr_size; i++)
    {
        int temp;
        cin >> temp;
        arr0[i] = arr1[i] = arr2[i] = arr3[i] = temp;
    }

    auto normal_start = chrono::steady_clock::now();
    normal_bubblesort(arr0, arr_size);
    cout << "\nNormal Bubble Sort: ";
    for (int i = 0; i < arr_size; i++)
        cout << arr0[i] << " ";
    cout << "\n";

    normal_mergesort(arr1, 0, arr_size - 1);
    cout << "Normal Merge Sort: ";
    for (int i = 0; i < arr_size; i++)
        cout << arr1[i] << " ";
    cout << "\n";
    auto normal_end = chrono::steady_clock::now();

    auto normal_duration = chrono::duration_cast<chrono::milliseconds>(normal_end - normal_start);
    cout << "Normal Time taken: " << normal_duration.count() << " milliseconds\n";

    auto parallel_start = chrono::steady_clock::now();
    parallel_bubblesort(arr2, arr_size);
    cout << "\nParallel Bubble Sort: ";
    for (int i = 0; i < arr_size; i++)
        cout << arr2[i] << " ";
    cout << "\n";

    parallel_mergesort(arr3, 0, arr_size - 1);
    cout << "Parallel Merge Sort: ";
    for (int i = 0; i < arr_size; i++)
        cout << arr3[i] << " ";
    cout << "\n";
    auto parallel_end = chrono::steady_clock::now();

    auto parallel_duration = chrono::duration_cast<chrono::milliseconds>(parallel_end - parallel_start);
    cout << "Parallel Time taken: " << parallel_duration.count() << " milliseconds\n";

    return 0;
}