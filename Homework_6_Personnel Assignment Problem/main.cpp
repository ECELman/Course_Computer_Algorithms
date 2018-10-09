#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

// job node
struct job_node{
	int num = 0, level = 0, cost = 0;
	bool last_node = false, check = false, old = false;

	job_node *left_job_node;
	job_node *right_job_node;

	job_node(int job_num, int job_level, int job_cost, bool tree_last_node){
	    num = job_num;
	    level = job_level;
		cost = job_cost;
		last_node = tree_last_node;

		left_job_node = NULL;
		right_job_node = NULL;
	}
};

// create the job tree
job_node* create_job_tree(job_node *job_tree, int cost[][4], int cost_lower_bound)
{
    job_node *root;
	job_node *new_job_node;
	job_node *temp1_job_tree;
	job_node *temp2_job_tree;
	job_node *temp3_job_tree;

	// level 0 (0)
	root = new job_node(0, 0, cost_lower_bound, false);
	job_tree = root;

	// level 0 (0-1)
	new_job_node = new job_node(1, 1, cost[0][0], false);
	job_tree->left_job_node = new_job_node;

	// level 0 (0-2)
	new_job_node = new job_node(2, 1, cost[0][1], false);
	job_tree->right_job_node = new_job_node;

	// level 1 (1)
	temp1_job_tree = job_tree->left_job_node;

	// level 1 (1-2)
	new_job_node = new job_node(2, 2, cost[1][1], false);
	temp1_job_tree->left_job_node = new_job_node;

	// level 1 (1-3)
	new_job_node = new job_node(3, 2, cost[1][2], false);
	temp1_job_tree->right_job_node = new_job_node;

	// level 1 (2)
	temp1_job_tree = job_tree->right_job_node;

	// level 1 (2-1)
	new_job_node = new job_node(1, 2, cost[1][0], false);
	temp1_job_tree->left_job_node = new_job_node;

	// level 2 (2)
	temp2_job_tree = job_tree->left_job_node->left_job_node;

	// level 2 (2-3)
	new_job_node = new job_node(3, 3, cost[2][2], false);
	temp2_job_tree->left_job_node = new_job_node;

	// level 2 (2-4)
	new_job_node = new job_node(4, 3, cost[2][3], false);
	temp2_job_tree->right_job_node = new_job_node;

	// level 2 (3)
	temp2_job_tree = job_tree->left_job_node->right_job_node;

	// level 2 (3-2)
	new_job_node = new job_node(2, 3, cost[2][1], false);
	temp2_job_tree->left_job_node = new_job_node;

	// level 2 (1)
	temp2_job_tree = job_tree->right_job_node->left_job_node;

	// level 2 (1-3)
	new_job_node = new job_node(3, 3, cost[2][2], false);
	temp2_job_tree->left_job_node = new_job_node;

	// level 2 (1-4)
	new_job_node = new job_node(4, 3, cost[2][3], false);
	temp2_job_tree->right_job_node = new_job_node;

	// level 3 (3)
	temp3_job_tree = job_tree->left_job_node->left_job_node->left_job_node;

	// level 3 (3-4)
	new_job_node = new job_node(4, 4, cost[3][3], true);
	temp3_job_tree->left_job_node = new_job_node;

	// level 3 (4)
	temp3_job_tree = job_tree->left_job_node->left_job_node->right_job_node;

	// level 3 (4-3)
	new_job_node = new job_node(3, 4, cost[3][2], true);
	temp3_job_tree->left_job_node = new_job_node;

	// level 3 (2)
	temp3_job_tree = job_tree->left_job_node->right_job_node->left_job_node;

	// level 3 (2-4)
	new_job_node = new job_node(4, 4, cost[3][3], true);
	temp3_job_tree->left_job_node = new_job_node;

	// level 3 (3)
	temp3_job_tree = job_tree->right_job_node->left_job_node->left_job_node;

	// level 3 (3-4)
	new_job_node = new job_node(4, 4, cost[3][3], true);
	temp3_job_tree->left_job_node = new_job_node;

	// level 3 (4)
	temp3_job_tree = job_tree->right_job_node->left_job_node->right_job_node;

	// level 3 (4-3)
	new_job_node = new job_node(3, 4, cost[3][2], true);
	temp3_job_tree->left_job_node = new_job_node;

	return job_tree;
}

// create the reduced cost matrix
int create_reduced_cost_matrix(int cost[][4])
{
    int cost_lower_bound = 0;

    for(int i=0; i<4; i++)
    {
        bool check = false;
        int min;
        for(int j=0; j<4; j++)
        {
            if(check==false)
            {
                min = cost[i][j];

                check = true;

                continue;
            }

            if(cost[i][j] < min) min = cost[i][j];
        }

        for(int j=0; j<4; j++) cost[i][j] -= min;

        cost_lower_bound += min;
    }

    for(int i=0; i<4; i++)
    {
        bool check = false, check_zero = false;
        int min;
        for(int j=0; j<4; j++)
        {
            if(cost[j][i] == 0)
            {
                check_zero = true;

                break;
            }

            if(check==false)
            {
                min = cost[j][i];

                check = true;

                continue;
            }

            if(cost[j][i] < min) min = cost[j][i];
        }

        if(check_zero == true) continue;

        for(int j=0; j<4; j++) cost[j][i] -= min;

        cost_lower_bound += min;
    }

    return cost_lower_bound;
}

// start Personnel Assignment
bool find_upper_bound = false;
int upper_bound;
job_node* person_assign(job_node *job_tree)
{
    job_node *temp_job_tree = job_tree;

    if(job_tree->num == 0) job_tree->check = true;

    int left, right;
    if(job_tree->left_job_node!=NULL)
    {
        left = job_tree->cost + job_tree->left_job_node->cost;
        job_tree->left_job_node->cost = left;

        job_tree->left_job_node->check = true;
        job_tree->left_job_node->old = true;
    }
    else left = 0;

    if(job_tree->right_job_node!=NULL)
    {
        right = job_tree->cost + job_tree->right_job_node->cost;
        job_tree->right_job_node->cost = right;

        job_tree->right_job_node->check = true;
        job_tree->right_job_node->old = true;
    }
    else right = 0;

    if(left==0 && right!=0)
    {
        if(job_tree->right_job_node->last_node == true)
        {
            find_upper_bound = true;

            upper_bound = job_tree->right_job_node->cost;
        }
        else
        {
            job_tree = job_tree->right_job_node;

            person_assign(job_tree);
        }
    }
    else if(left!=0 && right==0)
    {
        if(job_tree->left_job_node->last_node == true)
        {
            find_upper_bound = true;

            upper_bound = job_tree->left_job_node->cost;
        }
        else
        {
            job_tree = job_tree->left_job_node;

            person_assign(job_tree);
        }
    }
    else if(left < right)
    {
        if(job_tree->left_job_node->last_node == true)
        {
            find_upper_bound = true;

            upper_bound = job_tree->left_job_node->cost;
        }
        else if(job_tree->left_job_node!=NULL)
        {
            job_tree = job_tree->left_job_node;

            person_assign(job_tree);
        }
        else return temp_job_tree;
    }
    else
    {
        if(job_tree->right_job_node->last_node == true)
        {
            find_upper_bound = true;

            upper_bound = job_tree->right_job_node->cost;
        }
        else if(job_tree->right_job_node!=NULL)
        {
            job_tree = job_tree->right_job_node;

            person_assign(job_tree);
        }
        else return temp_job_tree;
    }

    if(find_upper_bound) return temp_job_tree;
}

// find the final solution
bool find_best_answer = false;
int final_assign[5] = {0};
int i = 4;
void find_better(job_node *job_tree)
{
    if(job_tree==NULL) return;

    if(job_tree->check == true && job_tree->num == 0)
    {
        find_better(job_tree->left_job_node);
        find_better(job_tree->right_job_node);
    }
    else if(job_tree->check == true && job_tree->num!=0)
    {
        if(job_tree->cost < upper_bound && job_tree->last_node == true)
        {
            upper_bound = job_tree->cost;

            final_assign[i--] = upper_bound;
            final_assign[i--] = job_tree->num;

            find_best_answer = true;

            return;
        }
        else if(job_tree->last_node == false && job_tree->num!=0)
        {
            if(job_tree->cost > upper_bound) return;
            else
            {
                if(job_tree->left_job_node!=NULL && job_tree->left_job_node->old == false)
                {
                    job_tree->left_job_node->cost = job_tree->cost + job_tree->left_job_node->cost;

                    job_tree->left_job_node->check = true;
                }

                if(job_tree->right_job_node!=NULL && job_tree->right_job_node->old == false)
                {
                    job_tree->right_job_node->cost = job_tree->cost + job_tree->right_job_node->cost;

                    job_tree->right_job_node->check = true;
                }

                find_better(job_tree->left_job_node);
                find_better(job_tree->right_job_node);
            }
        }
    }

    if(find_best_answer) final_assign[i--] = job_tree->num;
}

// show result
void show_result()
{
    for(int i=0; i<4; i++)
        cout<< "Person " << i+1 << " do job " << final_assign[i]<<endl;

    cout << endl << "Min Total Cost : " << final_assign[4] << endl;
}

// print the solution tree
void print_solution_tree(job_node *solution_tree)
{
    if(solution_tree == NULL) return;

    cout << solution_tree->num << " ";
    print_solution_tree(solution_tree->right_job_node);
    print_solution_tree(solution_tree->left_job_node);
}

int main()
{
    int cost[4][4] = {{29, 19, 17, 12},
                      {32, 30, 26, 28},
                      { 3, 21,  7,  9},
                      {18, 13, 10, 15}};

    cout << "Personnel Assignment Problem Solution Tree (Root R L) :" << endl << endl;
    job_node *solution_tree = create_job_tree(solution_tree, cost, 0);
    print_solution_tree(solution_tree);
    cout << endl;

    cout << "-------------------------------------------------------" << endl;

    cout << "Orign Cost Matrix :" << endl << endl;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++) printf("%2d ", cost[i][j]);
        cout << endl;
    }
    cout << endl;

    double start, end;
    start = clock();

    job_node *job_tree_orign = create_job_tree(job_tree_orign, cost, 0);

    job_tree_orign = person_assign(job_tree_orign);

    find_better(job_tree_orign);

    cout << "Personnel Assignment (Use the Orign Cost Matrix) :" << endl << endl;
    show_result();

    end = clock();
    cout << "Run Time : " << (end-start)/CLOCKS_PER_SEC << endl;

    cout << "-------------------------------------------------------" << endl;

    find_upper_bound = false;
    find_best_answer = false;
    for(int i=0; i<5; i++) final_assign[i] = 0;
    i = 4;

    int cost_lower_bound = create_reduced_cost_matrix(cost);

    cout << "Reduced Cost Matrix :" << endl << endl;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++) printf("%2d ", cost[i][j]);
        cout << endl;
    }

    cout << endl << "The cost lower bound : " << cost_lower_bound << endl;

    start = clock();

    job_node *job_tree = create_job_tree(job_tree, cost, cost_lower_bound);

    job_tree = person_assign(job_tree);

    find_better(job_tree);

    cout << endl << "Personnel Assignment (Use the Reduced Cost Matrix) :" << endl << endl;
    show_result();

    end = clock();
    cout << "Run Time : " << (end-start)/CLOCKS_PER_SEC << endl << endl;

    return 0;
}
