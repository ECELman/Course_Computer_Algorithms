#include <iostream>
#include <vector>
using namespace std;

struct edge
{
    int node1, node2, weight;
};

void quick_sort(edge [], int, int); // implementation of quick sort
void Prims_Algorithm(edge []); // implementation of Prim Algorithm

int main()
{
    edge graph[6] = {{1,3,4}, {1,2,16}, {2,3,7}, {3,5,7}, {5,1,2}, {4,5,9}};

    cout << "The connected edges and weight :" << endl << endl;
    cout << " edge     weight" << endl;
    for(int i = 0; i < 6; i++)
        cout << graph[i].node1 << " - " << graph[i].node2 << "       " << graph[i].weight << endl;

    cout << endl << "Minimum Spanning Tree :" << endl;
    Prims_Algorithm(graph);

    return 0;
}

// implementation of quick sort
void quick_sort(edge temp_graph[], int left, int right)
{
    if(left > right) return;

    int divider = temp_graph[left].weight;
    int i = left;
    int j = right;

    while(i<j)
    {
        while(i < j && temp_graph[j].weight >= divider) j--;
        swap(temp_graph[i], temp_graph[j]);

        while(i < j && temp_graph[i].weight <= divider) i++;
        swap(temp_graph[i], temp_graph[j]);
    }

    quick_sort(temp_graph, left, j-1);
    quick_sort(temp_graph, j+1, right);
}

// implementation of Prim Algorithm
void Prims_Algorithm(edge temp_graph[])
{
    quick_sort(temp_graph, 0, 5);

    vector<int> A,B;
    for(int i = 1; i <= 5; i++)
    {
        if(i==3) A.push_back(i);
        else B.push_back(i);
    }

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            bool check_A = false;
            for(int k = 0; k < A.size(); k++)
            {
                if(temp_graph[j].node1 == A[k] || temp_graph[j].node2 == A[k])
                {
                    check_A = true;

                    break;
                }
            }

            bool check_B = false;
            int record_another_node;
            for(int k = 0; k < B.size(); k++)
            {
                if(temp_graph[j].node1 == B[k])
                {
                    check_B = true;

                    record_another_node = temp_graph[j].node1;

                    break;
                }
                else if(temp_graph[j].node2 == B[k])
                {
                    check_B = true;

                    record_another_node = temp_graph[j].node2;

                    break;
                }
            }

            if(check_A && check_B)
            {
                A.push_back(record_another_node);

                for(int k = 0; k < B.size(); k++)
                {
                    if(B[k] == record_another_node)
                    {
                        B[k] = -1;
                        break;
                    }
                }

                cout << temp_graph[j].node1 << " - " << temp_graph[j].node2 << endl;

                break;
            }
        }

        int count_B_NULL = 0;
        for(int j = 0; j < B.size(); j++)
            if(B[j] == -1) count_B_NULL++;
        if(count_B_NULL == B.size()) break;
    }
}
