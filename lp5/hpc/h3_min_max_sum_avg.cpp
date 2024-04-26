#include <iostream>
#include <omp.h>
#include <climits>

using namespace std;

void min(int arr[], int arr_size)
{
    int min_value = INT_MAX;

#pragma parallel for reduction(min : min_value)

    for (int i = 0; i < arr_size; i++)
        if (arr[i] < min_value)
            min_value = arr[i];

    cout << "Min: " << min_value << "\n";
}

void max(int arr[], int arr_size)
{
    int max_value = INT_MIN;

#pragma parallel for reduction(max : max_value)

    for (int i = 0; i < arr_size; i++)
        if (arr[i] > max_value)
            max_value = arr[i];

    cout << "Max: " << max_value << "\n";
}

void sum_and_avg(int arr[], int arr_size)
{
    int sum = 0;

#pragma parallel for reduction(+ : sum)

    for (int i = 0; i < arr_size; i++)
        sum += arr[i];

    cout << "Sum: " << sum << "\n";
    cout << "Avg: " << sum / arr_size << "\n";
}

int main()
{
    int arr_size;
    cout << "Enter Number of Elements: ";
    cin >> arr_size;

    int arr[arr_size];
    cout << "Enter " << arr_size << " Elements: ";
    for (int i = 0; i < arr_size; i++)
        cin >> arr[i];

    cout << "\n";
    min(arr, arr_size);
    max(arr, arr_size);
    sum_and_avg(arr, arr_size);

    return 0;
}