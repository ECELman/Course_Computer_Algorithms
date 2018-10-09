#include <iostream>
using namespace std;

void quick_sort(int [], int, int); // implementation of quick sort
void swap(int &, int &); // change data
void show(int [], int); // show the data in array

int main()
{
    int num[10]={6, 12, 2, 30, 17, 11, 5, 9, 75, 1};

    cout << "Before sorting :" << endl;
    show(num, 10);

    quick_sort(num, 0, 9);

    cout << endl << "After sorting :" << endl;
    show(num, 10);

    return 0;
}

// implementation of quick sort
void quick_sort(int num[], int left, int right)
{
    if(left > right) return;

    int divider = num[left];
    int i = left;
    int j = right;

    while(i<j)
    {
        while(i < j && num[j] >= divider) j--;
        swap(num[i], num[j]);

        while(i < j && num[i] <= divider) i++;
        swap(num[i], num[j]);
    }

    quick_sort(num, left, j-1);
    quick_sort(num, j+1, right);
}

// change data
void swap(int &data1, int &data2)
{
    int temp = data1;
    data1 = data2;
    data2 = temp;
}

// show the data in array
void show(int num[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(i!=size-1) cout << num[i] << " ";
        else cout << num[i] << endl;
    }
}
