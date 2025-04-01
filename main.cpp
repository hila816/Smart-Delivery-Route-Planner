#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class Graph {
public:
    unordered_map<int, vector<pair<int, int>>> adjList; // Adjacency list to store nodes and weighted edges

    void addLocation(int location) {
        adjList[location] = {}; // Add a new location (node)
    }

    void addRoad(int u, int v, int weight) {
        adjList[u].push_back({v, weight}); 
        adjList[v].push_back({u, weight}); // Undirected graph
    }

   

    void updateRoad(int u, int v, int newWeight) {
        for (auto &edge : adjList[u]) {
            if (edge.first == v) edge.second = newWeight;
        }
        for (auto &edge : adjList[v]) {
            if (edge.first == u) edge.second = newWeight;
        }
    }

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

            for (auto &neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void dijkstra(int src) {
        unordered_map<int, int> dist;
        unordered_map<int, int> prev;

        for (auto &pair : adjList) {
            dist[pair.first] = numeric_limits<int>::max();
        }
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Shortest Delivery Routes from Restaurant:" << endl;
        for (auto &pair : dist) {
            cout << "To Location " << pair.first << " -> " << pair.second << " mins" << endl;
        }
    }
};

int main() {
    Graph g;

    // Add locations: Restaurant, Customers (1 = Qura Hotel, 2-6 = Customers)
    g.addLocation(1); // Qura Hotel
    g.addLocation(2); // Abebe
    g.addLocation(3); // Alemu
    g.addLocation(4); // Samual
    g.addLocation(5); // Aster
    g.addLocation(6); // Helen

    // Add edges: roads between locations
    g.addRoad(1, 2, 4); // Qura Hotel -> Abebe
    g.addRoad(1, 3, 7); // Qura Hotel -> Alemu
    g.addRoad(2, 4, 3); // Abebe -> Samual
    g.addRoad(3, 5, 2); // Alemu -> Aster
    g.addRoad(4, 6, 6); // Samual -> Helen
    g.addRoad(5, 6, 5); // Aster -> Helen

    // Update road: Change the time from Customer 3 (Alemu) to Customer 4 (Samual)
    g.updateRoad(3, 4, 10); // Alemu -> Samual (updated travel time)

    // Add new road: Aster (Customer 5) to Qura Hotel (Restaurant)
    g.addRoad(5, 1, 8); // Aster -> Qura Hotel

    // Display BFS traversal from the restaurant (Qura Hotel)
    g.BFS(1);

    // Find the shortest path from Qura Hotel (1) to other customers
    g.dijkstra(1);

    return 0;
}
