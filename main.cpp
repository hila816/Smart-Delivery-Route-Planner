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
    int weight;  // Travel time (edge weight)
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
    unordered_map<int, AdjNode*> adjList; // Stores adjacency list
public:
    // Function to add an edge
    void addEdge(int src, int dest, int weight) {
        AdjNode* newNode = new AdjNode(dest, weight);
        newNode->next = adjList[src];
        adjList[src] = newNode;

        // Add reverse edge if graph is undirected
        newNode = new AdjNode(src, weight);
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
    }

    // Function to delete a vertex
    void delVertex(int vertex) {
        adjList.erase(vertex); // Remove the vertex
        for (auto& pair : adjList) {
            AdjNode* temp = pair.second;
            AdjNode* prev = NULL;
            while (temp) {
                if (temp->vertex == vertex) {
                    if (prev) {
                        prev->next = temp->next;
                    } else {
                        adjList[pair.first] = temp->next;
                    }
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
        }
    }

    // Function to update edge weight
    void updateWeight(int src, int dest, int newWeight) {
        // Update weight for src -> dest
        AdjNode* temp = adjList[src];
        while (temp) {
            if (temp->vertex == dest) {
                temp->weight = newWeight;
                break;
            }
            temp = temp->next;
        }

        // Update weight for dest -> src (for undirected graph)
        temp = adjList[dest];
        while (temp) {
            if (temp->vertex == src) {
                temp->weight = newWeight;
                break;
            }
            temp = temp->next;
        }

        cout << "Updated weight between " << src << " and " << dest << " to " << newWeight << " mins." << endl;
    }

    // BFS traversal
    void BFS(int start) {
        unordered_map<int, bool> visited;
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            AdjNode* temp = adjList[node];
            while (temp) {
                if (!visited[temp->vertex]) {
                    q.push(temp->vertex);
                    visited[temp->vertex] = true;
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }

    // Dijkstra's Algorithm for shortest path
    void dijkstra(int src) {
        unordered_map<int, int> dist;
        for (auto& pair : adjList) {
            dist[pair.first] = numeric_limits<int>::max();
        }
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            AdjNode* temp = adjList[u];
            while (temp) {
                int v = temp->vertex;
                int weight = temp->weight;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
                temp = temp->next;
            }
        }

        cout << "Shortest Delivery Routes from Qura Restaurant:" << endl;
        for (auto& d : dist) {
            if (d.second == numeric_limits<int>::max()) 
                cout << "To Location " << d.first << " -> Unreachable" << endl;
            else
                cout << "To Location " << d.first << " -> " << d.second << " mins" << endl;
        }
    }

    // Function to print the graph
    void printGraph() {
        for (auto& pair : adjList) {
            cout << pair.first << ": ";
            AdjNode* temp = pair.second;
            while (temp) {
                cout << "-> " << temp->vertex << "(" << temp->weight << " mins) ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

// Main function
int main() {
    Graph g;

    // Adding initial edges (delivery routes)
    g.addEdge(0, 1, 4);  // Qura Restaurant (0) → Customer 1 (1)
    g.addEdge(0, 2, 7);  // Qura Restaurant (0) → Customer 2 (2)
    g.addEdge(1, 3, 3);  // Customer 1 (1) → Customer 3 (3)
    g.addEdge(2, 4, 2);  // Customer 2 (2) → Customer 4 (4)
    g.addEdge(3, 5, 6);  // Customer 3 (3) → Customer 5 (5)
    g.addEdge(4, 6, 5);  // Customer 4 (4) → Customer 6 (6)

    cout << "Initial Adjacency List:" << endl;
    g.printGraph();

    // Add a new vertex (Location 7) and edges
    g.addEdge(3, 7, 5);
    g.addEdge(7, 2, 5);
    cout << "Adjacency List after adding vertex 7:" << endl;
    g.printGraph();

    // Delete vertex (Customer 4: Helen)
    g.delVertex(4);
    cout << "Adjacency List after deleting vertex 4:" << endl;
    g.printGraph();

    // Update weight between vertex 3 and 7 to 8 minutes
    g.updateWeight(3, 7, 8);
    cout << "Adjacency List after updating weight between 3 and 7:" << endl;
    g.printGraph();

    // Perform BFS
    g.BFS(0);

    // Perform Dijkstra's algorithm to find the shortest path
    g.dijkstra(0);

    return 0;
}
