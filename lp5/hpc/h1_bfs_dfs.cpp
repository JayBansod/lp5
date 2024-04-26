#include <iostream>
#include <omp.h>
#include <queue>

#define ARR_SIZE 5

using namespace std;

void parallel_bfs(int graph[ARR_SIZE][ARR_SIZE], int start_index)
{
    bool visited[ARR_SIZE] = {false};
    queue<int> q;

    q.push(start_index);
    visited[start_index] = true;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        cout << "Visited: " << current << "\n";

#pragma omp parallel for
        for (int i = 0; i < ARR_SIZE; i++)
        {
            if (graph[current][i] && !visited[i])
            {
#pragma omp critical
                {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }
}

void parallelDFS(int graph[ARR_SIZE][ARR_SIZE], int node, bool visited[ARR_SIZE])
{
    visited[node] = true;

    cout << "Visited Node: " << node << endl;

#pragma omp parallel for
    for (int i = 0; i < ARR_SIZE; ++i)
    {
        if (graph[node][i] && !visited[i])
        {
            parallelDFS(graph, i, visited);
        }
    }
}

int main()
{
    int graph[ARR_SIZE][ARR_SIZE] = {
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
    };
    int start = 2;

    cout << "Parallel BFS:\n";
    parallel_bfs(graph, start);

    bool visited[ARR_SIZE] = {false};

    cout << "\nParallel DFS:\n";
    parallelDFS(graph, start, visited);

    return 0;
}
