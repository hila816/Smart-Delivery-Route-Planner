# Smart-Delivery-Route-Planner
Weighted Graph
 A graph in which the edges are already specified with suitable weight is known as a weighted graph. 
 Weighted graphs can be further classified as directed weighted graphs and undirected weighted graphs. 

Representation of Graph Data Structure:
There are multiple ways to store a graph: The following are the most common representations.

1. Adjacency Matrix
In this method, the graph is stored in the form of the 2D matrix where rows and columns denote vertices.

2. Adjacency List
 This graph is represented as a collection of linked lists. There is an array of pointer which points to the edges connected to that vertex.
Add and Remove vertex in Adjacency List representation of Graph

2. Adding a Vertex:
To add a vertex in the adjacency list, follow these steps:

Locate the Position: Iterate through the adjacency list to find the appropriate place for the new vertex.

Create New Node: Use the linked list structure to create a new node for the vertex.

Update Connections:

If the vertex needs to be inserted between two existing vertices (e.g., vertex 2 and 3), update the edges:

Create an edge from vertex 3 to the new vertex.

Create an edge from the new vertex to vertex 2.

Resulting Change: The adjacency list will reflect the addition of the new vertex and its edges.

Example:

If vertex 5 is added between vertex 2 and vertex 3, the adjacency list will be updated accordingly.

3. Removing a Vertex:
To remove a vertex in the adjacency list, follow these steps:

Iterate Through the List: Go through each vertex's list of connections.

Remove Edges: For each vertex connected to the one being deleted, remove the reference to the deleted vertex in their list.

Delete Vertex: Finally, delete the node corresponding to the vertex from the adjacency list.

c) Updating Edge Weight:

Changing the weight of an edge dynamically allows real-time updates (e.g., traffic changes).

The function traverses the adjacency list to find the edge and updates its weight.

Traversal & Shortest Path Algorithms

a) Breadth-First Search (BFS)

BFS is used to explore all possible delivery routes level by level.

It uses a queue to ensure nodes are processed in order of discovery.

BFS is useful for finding the shortest unweighted path.

b) Dijkstra’s Algorithm (Shortest Path)

Dijkstra’s Algorithm finds the shortest path from the restaurant (source) to all customers.

Uses a priority queue (min-heap) to always process the node with the smallest travel time first.

Greedy Algorithm: Expands the shortest known path to find the next shortest
