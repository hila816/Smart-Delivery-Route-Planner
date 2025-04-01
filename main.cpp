#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

// Node to store adjacency list
class AdjNode {
public:
    int vertex;
    int weight;  // To store the weight (travel time) of the edge
    AdjNode* next;

    AdjNode(int data, int w = 0) {
        vertex = data;
        weight = w;
        next = NULL;
    }
};

// Adjacency List representation
class Graph {
private:
    int v;  // Number of vertices (locations)
    AdjNode** graph;  // Adjacency list

public:
    Graph(int vertices) {
        v = vertices;
        graph = new AdjNode*[v];
        for (int i = 0; i < v; ++i)
            graph[i] = NULL;
    }

    // Function to add an edge with weight (travel time) between two vertices
    void addEdge(int source, int destination, int weight) {
        AdjNode* node = new AdjNode(destination, weight);
        node->next = graph[source];
        graph[source] = node;
    }

    // Function to add a vertex between two vertices
    void addVertex(int vk, int source, int destination, int weight) {
        addEdge(source, vk, weight);
        addEdge(vk, destination, weight);
    }

    // Function to print the adjacency list
    void printGraph() {
        for (int i = 0; i < v; ++i) {
            if (graph[i] == NULL)
                continue;
            cout << i << ": ";
            AdjNode* temp = graph[i];
            while (temp != NULL) {
                cout << "-> " << temp->vertex << "(" << temp->weight << " mins) ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    // Function to delete a vertex
    void delVertex(int k) {
        for (int i = 0; i < v; ++i) {
            AdjNode *curr = graph[i], *prev = nullptr;
            if (i == k) {
                graph[i] = nullptr;
                while (curr != nullptr) {
                    AdjNode* next = curr->next;
                    delete (curr);
                    curr = next;
                }
            } else {
                while (curr != nullptr) {
                    if (curr->vertex == k) {
                        if (prev == nullptr) {
                            graph[i] = curr->next;  // Remove from the beginning
                        } else {
                            prev->next = curr->next;  // Remove from the middle/end
                        }
                        delete curr;
                        break;
                    }
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }

    // BFS function to explore delivery routes
    void BFS(int start) {
        queue<int> q;
        unordered_map<int, bool> visited;

        q.push(start);
        visited[start] = true;

        cout << "BFS Traversal (Exploring Delivery Routes): ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (AdjNode* neighbor = graph[node]; neighbor != NULL; neighbor = neighbor->next) {
                if (!visited[neighbor->vertex]) {
                    visited[neighbor->vertex] = true;
                    q.push(neighbor->vertex);
                }
            }
        }
        cout << endl;
    }

    // Dijkstra’s Algorithm to find the shortest delivery route from a starting location
    void dijkstra(int src) {
        unordered_map<int, int> dist; // Stores the shortest distance from src to other nodes

        // Initialize all distances as "infinity"
        for (int i = 0; i < v; ++i) {
            dist[i] = numeric_limits<int>::max();
        }
        dist[src] = 0; // Distance from source to itself is 0

        // Min-heap (priority queue) for selecting the shortest distance node
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (AdjNode* neighbor = graph[u]; neighbor != NULL; neighbor = neighbor->next) {
                int v = neighbor->vertex;
                int weight = neighbor->weight;

                // Relaxation step: Update the shortest distance if a shorter path is found
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // Output the shortest delivery routes
        cout << "Shortest Delivery Routes from Qura Restaurant:" << endl;
        for (auto& pair : dist) {
            if (pair.second == numeric_limits<int>::max()) {
                cout << "To Location " << pair.first << " -> Unreachable" << endl;
            } else {
                cout << "To Location " << pair.first << " -> " << pair.second << " mins" << endl;
            }
        }
    }
};

int main() {
    int V = 8;  // 8 locations (Qura Restaurant + 7 Customers)
    Graph g(V);

    // Initial roads (edges with weights)
    g.addEdge(0, 1, 4); // Qura Restaurant (0) -> Abebe (1)
    g.addEdge(0, 2, 7); // Qura Restaurant (0) -> Alemu (2)
    g.addEdge(1, 3, 3); // Abebe (1) -> Aster (3)
    g.addEdge(2, 4, 2); // Alemu (2) -> Helen (4)
    g.addEdge(3, 5, 6); // Aster (3) -> Belaynsh (5)
    g.addEdge(4, 6, 5); // Helen (4) -> Kebede (6)

    // Print initial adjacency list
    cout << "Initial Adjacency List:" << endl;
    g.printGraph();

    // Add vertex (New Customer 7: Kebede)
    g.addVertex(7, 3, 2, 5); // Add Kebede (7) between Aster (3) and Alemu (2) with 5 minutes
    cout << "Adjacency List after adding vertex 7:" << endl;
    g.printGraph();

    // Delete vertex (Customer 4: Helen)
    g.delVertex(4); // Delete Helen (4)
    cout << "Adjacency List after deleting vertex 4:" << endl;
    g.printGraph();

    // Perform BFS starting from the Qura Restaurant (vertex 0)
    g.BFS(0);

    // Perform Dijkstra's algorithm to find the shortest path from Qura Restaurant (vertex 0)
    g.dijkstra(0);

    return 0;
}
