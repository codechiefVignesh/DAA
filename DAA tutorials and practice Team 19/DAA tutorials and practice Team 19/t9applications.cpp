#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int vertices) : V(vertices) 
    {
        adj.resize(V);
    }

    // Add an edge to the graph
    void addEdge(int v, int w) 
    {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    // Breadth-First Search (BFS)
    void BFS(int start) 
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) 
        {
            int current = q.front();
            cout << current << " ";
            q.pop();

            for (int neighbor : adj[current]) 
            {
                if (!visited[neighbor]) 
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    // Depth-First Search (DFS)
    void DFS(int start) 
    {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(start);

        while (!s.empty()) 
        {
            int current = s.top();
            s.pop();

            if (!visited[current]) 
            {
                cout << current << " ";
                visited[current] = true;
            }

            for (int neighbor : adj[current]) 
            {
                if (!visited[neighbor]) 
                {
                    s.push(neighbor);
                }
            }
        }
    }

    // Test if the graph is connected using BFS
    bool isConnected() 
    {
        vector<bool> visited(V, false);
        BFS(0); // Start BFS from the first vertex

        for (int i = 0; i < V; i++) 
        {
            if (!visited[i]) 
            {
                return false; // If there are unvisited nodes, the graph is not connected
            }
        }
        return true;
    }

    // Check if the graph is a tree
    bool isTree() 
    {
        vector<bool> visited(V, false);
        return isConnected() && !hasCycle(0, -1, visited);
    }

    // Check if the graph has a cycle
    bool hasCycle(int v, int parent, vector<bool>& visited) 
    {
        visited[v] = true;
        for (int neighbor : adj[v]) 
        {
            if (!visited[neighbor]) 
            {
                if (hasCycle(neighbor, v, visited)) 
                {
                    return true;
                }
            } else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }

    // Check if the graph is bipartite
    bool isBipartite() {
        vector<int> color(V, -1);
        for (int i = 0; i < V; i++) 
        {
            if (color[i] == -1 && !isBipartiteUtil(i, color)) 
            {
                return false;
            }
        }
        return true;
    }

    bool isBipartiteUtil(int u, vector<int>& color) 
    {
        color[u] = 1;
        queue<int> q;
        q.push(u);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : adj[current]) 
            {
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[current];
                    q.push(neighbor);
                } 
                else if (color[neighbor] == color[current]) 
                {
                    return false;
                }
            }
        }
        return true;
    }

    // Check if the graph is 2-colorable
    bool is2Colorable() 
    {
        vector<int> color(V, -1);
        for (int i = 0; i < V; i++) 
        {
            if (color[i] == -1 && !is2ColorableUtil(i, color, 0)) 
            {
                return false;
            }
        }
        return true;
    }

    bool is2ColorableUtil(int u, vector<int>& color, int c) 
    {
        color[u] = c;
        for (int neighbor : adj[u]) 
        {
            if (color[neighbor] == -1) 
            {
                if (!is2ColorableUtil(neighbor, color, 1 - c)) 
                {
                    return false;
                }
            } 
            else if (color[neighbor] == c) 
            {
                return false;
            }
        }
        return true;
    }

    // Check if the graph has an odd cycle
    bool hasOddCycle() 
    {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++) 
        {
            if (!visited[i] && hasOddCycleUtil(i, -1, visited)) 
            {
                return true;
            }
        }
        return false;
    }

    bool hasOddCycleUtil(int u, int parent, vector<bool>& visited) 
    {
        visited[u] = true;
        for (int neighbor : adj[u]) 
        {
            if (!visited[neighbor]) 
            {
                if (hasOddCycleUtil(neighbor, u, visited)) 
                {
                    return true;
                }
            } 
            else if (neighbor != parent) 
            {
                return true;
            }
        }
        return false;
    }

    // Find articulation points using DFS
    void findArticulationPoints() 
    {
        vector<int> parent(V, -1);
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<bool> articulationPoint(V, false);

        for (int i = 0; i < V; i++) 
        {
            if (disc[i] == -1) 
            {
                findArticulationPointsUtil(i, parent, disc, low, articulationPoint);
            }
        }

        cout << "Articulation Points: ";
        for (int i = 0; i < V; i++) 
        {
            if (articulationPoint[i]) 
            {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    void findArticulationPointsUtil(int u, vector<int>& parent, vector<int>& disc, vector<int>& low, vector<bool>& articulationPoint) 
    {
        static int time = 0;
        int children = 0;
        disc[u] = low[u] = time++;
        for (int neighbor : adj[u]) 
        {
            if (disc[neighbor] == -1) 
            {
                children++;
                parent[neighbor] = u;
                findArticulationPointsUtil(neighbor, parent, disc, low, articulationPoint);
                low[u] = min(low[u], low[neighbor]);
                if (low[neighbor] >= disc[u] && parent[u] != -1) 
                {
                    articulationPoint[u] = true;
                }
                if (parent[u] == -1 && children > 1) 
                {
                    articulationPoint[u] = true;
                }
            } 
            else if (neighbor != parent[u]) 
            {
                low[u] = min(low[u], disc[neighbor]);
            }
        }
    }

    // Find bridges using DFS
    void findBridges() {
        vector<int> parent(V, -1);
        vector<int> disc(V, -1);
        vector<int> low(V, -1);

        for (int i = 0; i < V; i++) 
        {
            if (disc[i] == -1) 
            {
                findBridgesUtil(i, parent, disc, low);
            }
        }
    }

    void findBridgesUtil(int u, vector<int>& parent, vector<int>& disc, vector<int>& low) 
    {
        static int time = 0;
        disc[u] = low[u] = time++;

        for (int neighbor : adj[u]) 
        {
            if (disc[neighbor] == -1) 
            {
                parent[neighbor] = u;
                findBridgesUtil(neighbor, parent, disc, low);
                low[u] = min(low[u], low[neighbor]);
                if (low[neighbor] > disc[u]) 
                {
                    cout << "Bridge: " << u << " - " << neighbor << endl;
                }
            } 
            else if (neighbor != parent[u]) 
            {
                low[u] = min(low[u], disc[neighbor]);
            }
        }
    }
};

int main() 
{
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(4, 6);

    cout << "BFS starting from vertex 0: ";
    g.BFS(0);
    cout << endl;

    cout << "DFS starting from vertex 0: ";
    g.DFS(0);
    cout << endl;

    if (g.isConnected()) 
    {
        cout << "The graph is connected." << endl;
    } 
    else 
    {
        cout << "The graph is not connected." << endl;
    }

    if (g.isTree()) 
    {
        cout << "The graph is a tree." << endl;
    } 
    else 
    {
        cout << "The graph is not a tree." << endl;
    }

    if (g.isBipartite()) 
    {
        cout << "The graph is bipartite." << endl;
    } 
    else 
    {
        cout << "The graph is not bipartite." << endl;
    }

    if (g.is2Colorable()) 
    {
        cout << "The graph is 2-colorable." << endl;
    } 
    else 
    {
        cout << "The graph is not 2-colorable." << endl;
    }

    if (g.hasOddCycle()) 
    {
        cout << "The graph has an odd cycle." << endl;
    } 
    else 
    {
        cout << "The graph does not have an odd cycle." << endl;
    }

    g.findArticulationPoints();
    g.findBridges();

    return 0;
}
