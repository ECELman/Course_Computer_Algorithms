#include <iostream>
using namespace std;

void insertion_sort(int [], int); // using insertion sort to be sorting
int binary_search(int [], int, int); // using binary search to be searching
void show(int [], int); // show the all elements in array

int main()
{
    int arr[10] = {7, 5, 10, 8, 3, 4, 1, 6, 9, 2};

    cout << "Before sorting :" << endl << endl;
    show(arr, 10);

    insertion_sort(arr, 10);

    cout << endl << "After sorting :" << endl << endl;
    show(arr, 10);

    cout << endl << "Searching :" << endl << endl;

    int search = 6;
    cout << "Search => " << search << endl << endl;
    int index = binary_search(arr, 10, search);
    if(index == -1) cout << "The number " << search << " can't find in array" << endl;
    else cout << "The number " << search << " is at " << index+1 << " position in array" << endl;

    cout << endl;

    search = 13;
    cout << "Search => " << search << endl << endl;
    index = binary_search(arr, 10, search);
    if(index == -1) cout << "The number " << search << " can't find in array" << endl;
    else cout << "The number " << search << " is at " << index+1 << "position in array" << endl;

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

// implementation of binary search
int binary_search(int arr[], int size, int search)
{
    int low = 0;
    int high = size-1;

    while(low <= high)
    {
        int middle = (low+high)/2;

        if(arr[middle] == search) return middle;
        else
        {
            if(search < arr[middle]) high = middle-1;
            else low = middle+1;
        }
    }

    return -1;
}

void show(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(i!=size-1) cout << arr[i] << " ";
        else cout << arr[i] << endl;
    }
}
