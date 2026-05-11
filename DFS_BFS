#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // ================= PARALLEL BFS =================
    void parallelBFS(int start) {

        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nParallel BFS Traversal: ";

        while (!q.empty()) {

            int size = q.size();
            vector<int> currentLevel;

            // Store current level nodes
            for (int i = 0; i < size; i++) {
                currentLevel.push_back(q.front());
                q.pop();
            }

            // Parallel processing
            #pragma omp parallel for
            for (int i = 0; i < currentLevel.size(); i++) {

                int node = currentLevel[i];

                #pragma omp critical
                cout << node << " ";

                for (int j = 0; j < adj[node].size(); j++) {

                    int neighbor = adj[node][j];

                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }

        cout << endl;
    }

    // ================= PARALLEL DFS =================
    void dfsUtil(int node, vector<bool> &visited) {

        bool alreadyVisited = false;

        #pragma omp critical
        {
            if (visited[node])
                alreadyVisited = true;
            else {
                visited[node] = true;
                cout << node << " ";
            }
        }

        if (alreadyVisited)
            return;

        for (int i = 0; i < adj[node].size(); i++) {

            int neighbor = adj[node][i];

            #pragma omp task
            dfsUtil(neighbor, visited);
        }

        #pragma omp taskwait
    }

    void parallelDFS(int start) {

        vector<bool> visited(V, false);

        cout << "\nParallel DFS Traversal: ";

        #pragma omp parallel
        {
            #pragma omp single
            {
                dfsUtil(start, visited);
            }
        }

        cout << endl;
    }
};

int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++) {

        int u, v;
        cin >> u >> v;

        g.addEdge(u, v);
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    g.parallelBFS(start);

    g.parallelDFS(start);

    return 0;
}
