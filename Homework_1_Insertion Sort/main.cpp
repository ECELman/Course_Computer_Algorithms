#include <iostream>
using namespace std;

void insertion_sort(int [], int); // using insertion sort to be sorting
void show(int [], int); // show the all elements in array

int main()
{
    int arr[10] = {7, 5, 10, 8, 3, 4, 1, 6, 9, 2};

    cout << "Before sorting :" << endl << endl;
    show(arr, 10);

    insertion_sort(arr, 10);

    cout << endl << "After sorting :" << endl << endl;
    show(arr, 10);

    return 0;
}

// implementation of insertion sort
void insertion_sort(int arr[], int size)
{
    for(int i = 1; i < size; i++)
    {
        int j = i;
        int temp = arr[j];

        while(j > 0 && arr[j-1] > temp)
        {
            arr[j] = arr[j-1];

            j--;
        }

        arr[j] = temp;
    }
}

void show(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(i!=size-1) cout << arr[i] << " ";
        else cout << arr[i] << endl;
    }
}
