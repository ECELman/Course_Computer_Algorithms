#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

// the struct of point
struct point
{
    int x, y, rank;
    char alphabet;
};

void show_graph(point []); // show the X-Y plane
void quick_sort_alphabet(point [], int, int); // sort the alphabet
void quick_sort_x(point [], int, int); // sort the x coordinate
void quick_sort_y(point [], int, int); // sort the y coordinate
void ranking_finding(point [], int, int); // find all point rank

int main()
{
    // the coordinate of points
    point coordinate[10] = {{8,10,0,'F'}, {2,9,0,'E'}, {9,8,0,'G'}, {7,7,0,'H'}, {4,6,0,'D'},
                            {3,5,0,'C'}, {6,4,0,'I'}, {1,3,0,'B'}, {10,2,0,'J'}, {5,1,0,'A'} };

    show_graph(coordinate); // show the X-Y plane

    ranking_finding(coordinate, 0, 9); // find all point rank

    // output the result
    cout << endl << "All point rank :" << endl << endl;

    quick_sort_alphabet(coordinate, 0, 9);

    for(int i = 0; i < 10; i++)
        printf("%c (%2d,%2d) Rank(%c) = %2d\n", coordinate[i].alphabet,coordinate[i].x, coordinate[i].y,
                                                coordinate[i].alphabet,coordinate[i].rank);

    return 0;
}

// show the X-Y plane
void show_graph(point temp_coordinate[])
{
    cout << "X-Y plane :" << endl << endl;

    int y = 10;
    cout << "| y" << endl;
    for(int i = 0; i < 10; i++)
    {
        printf("|%2d", 10-i);

        for(int k = 0; k <= 10; k++)
        {
            if(temp_coordinate[i].x == k && temp_coordinate[i].y == y)
                cout << temp_coordinate[i].alphabet
                     << " (" << temp_coordinate[i].x << "," << temp_coordinate[i].y << ")";
            else cout << "      ";
        }
        cout << endl;

        y--;
    }

    cout << "| 0      1     2     3     4     5     6     7     8     9     10    x" << endl;
    cout << "______________________________________________________________________" << endl;
}

// sort the alphabet
void quick_sort_alphabet(point temp_coordinate[], int left, int right)
{
    if(left > right) return;

    char divider = temp_coordinate[left].alphabet;
    int i = left;
    int j = right;

    while(i<j)
    {
        while(i < j && temp_coordinate[j].alphabet >= divider) j--;
        swap(temp_coordinate[i], temp_coordinate[j]);

        while(i < j && temp_coordinate[i].alphabet <= divider) i++;
        swap(temp_coordinate[i], temp_coordinate[j]);
    }

    quick_sort_alphabet(temp_coordinate, left, j-1);
    quick_sort_alphabet(temp_coordinate, j+1, right);
}

// sort the x coordinate
void quick_sort_x(point temp_coordinate[], int left, int right)
{
    if(left > right) return;

    int divider = temp_coordinate[left].x;
    int i = left;
    int j = right;

    while(i<j)
    {
        while(i < j && temp_coordinate[j].x >= divider) j--;
        swap(temp_coordinate[i], temp_coordinate[j]);

        while(i < j && temp_coordinate[i].x <= divider) i++;
        swap(temp_coordinate[i], temp_coordinate[j]);
    }

    quick_sort_x(temp_coordinate, left, j-1);
    quick_sort_x(temp_coordinate, j+1, right);
}

// sort the y coordinate
void quick_sort_y(point temp_coordinate[], int left, int right)
{
    if(left > right) return;

    int divider = temp_coordinate[left].y;
    int i = left;
    int j = right;

    while(i<j)
    {
        while(i < j && temp_coordinate[j].y >= divider) j--;
        swap(temp_coordinate[i], temp_coordinate[j]);

        while(i < j && temp_coordinate[i].y <= divider) i++;
        swap(temp_coordinate[i], temp_coordinate[j]);
    }

    quick_sort_y(temp_coordinate, left, j-1);
    quick_sort_y(temp_coordinate, j+1, right);
}

// find all point rank
void ranking_finding(point temp_coordinate[], int low, int high)
{
    if(low >= high) return;

    quick_sort_x(temp_coordinate, low, high);

    int mid = (low + high) / 2;
    int mid_x = temp_coordinate[mid].x;

    ranking_finding(temp_coordinate, low, mid);
    ranking_finding(temp_coordinate, mid+1, high);

    quick_sort_y(temp_coordinate, low, high);

    int count = 0, record = -1, count_same_y = 0;
    for(int i = low; i <= high; i++)
    {
        if(temp_coordinate[i].x <= mid_x)
        {
            if(temp_coordinate[i].y != record)
            {
                count_same_y = 1;
                record = temp_coordinate[i].y;
            }
            else count_same_y++;

            count++;
        }
        else
        {
            if(temp_coordinate[i].y == record) temp_coordinate[i].rank += (count - count_same_y);
            else temp_coordinate[i].rank += count;
        }
    }
}
