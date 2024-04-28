#include<iostream>
#include<vector>
//*important to add following library to allow a programmer to use parallel paradigms**
#include<omp.h>
#include<queue>
#include<stdio.h>
using namespace std;

queue<int> q; // Declare a queue for BFS traversal

// Function to perform Breadth First Search (BFS) starting from 'start' vertex
void bfs(int start, int* arr, int n, int visit[])
{
    // OpenMP parallel for loop to iterate through all vertices
    #pragma omp parallel for ordered
    for(int i=0; i<n; i++)
    {
        // Ordered directive ensures ordered execution of the loop iterations
        #pragma omp ordered
        
        // Check if there is an edge from 'start' to 'i' and 'i' is not visited yet
        if(*(arr + (n*start) + i) == 1 && visit[i] == 0)
        {
            // Print the vertex 'i', mark it visited, and push it into the queue
            cout << i << " ";
            q.push(i);
            visit[i] = 1;
        }
    }

    // Remove the front element from the queue
    q.pop();

    // If the queue is not empty, perform BFS from the front element of the queue
    if(!q.empty()) bfs(q.front(), (int*)arr, n, visit);
}

int main()
{
    // Input the number of vertices
    cout << "Enter the number of vertices: ";
    int n;
    cin >> n;

    // Declare an adjacency matrix to represent the graph
    int arr[n][n] = {0};

    // Input the number of edges
    cout << "Enter the number of edges: ";
    int edges;
    cin >> edges;

    // Input the edges and update the adjacency matrix

        for(int j=0; j < edges; j++)
    {
        int a, b;
        cout << "Enter the two edges:" << endl;
        cin >> a >> b;
        // Mark the edges as connected in the adjacency matrix
        arr[a][b] = 1;
        arr[b][a] = 1;
    }

    // Initialize the visit array to keep track of visited vertices
    int visit[n] = {0};

    // Input the start vertex for BFS traversal
    cout << "Enter the start vertex: ";
    int start;
    cin >> start;

    // Record the start time for measuring execution time
    //clock_t strt = clock();

    // Mark the start vertex as visited, print it, and push it into the queue
    visit[start] = 1;
    cout << start << " ";
    q.push(start);

    // Perform BFS traversal starting from the start vertex
    bfs(start, (int*)arr, n, visit);

    // Record the stop time for measuring execution time
    //clock_t stop = clock();

    // Calculate and print the execution time
    //cout << "\nTime required : " << (double)(stop-strt) << " ms" << endl;

    return 0;
}

/*
o/p:
zoro2030@onepiece:~$ g++ par_bfs.cpp -fopenmp
zoro2030@onepiece:~$ ./a.out
Enter the number of vertices: 4
Enter the number of edges: 6
Enter the two edges:
1 0
Enter the two edges:
1 2
Enter the two edges:
1 3
Enter the two edges:
0 3
Enter the two edges:
2 3
Enter the two edges:
0 2
Enter the start vertex: 3
3 0 1 2 


*/