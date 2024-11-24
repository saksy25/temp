#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100  // Maximum number of vertices

// Node structure for adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph {
    int numVertices;
    struct Node* adjList[MAX_VERTICES];
};

// Function to create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Function to add an edge
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // For undirected graph, add reverse edge
    newNode = malloc(sizeof(struct Node));
    newNode->vertex = src;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to check if the current color assignment is safe for vertex v
bool isSafe(struct Graph* graph, int color[], int v, int c) {
    struct Node* temp = graph->adjList[v];
    while (temp) {
        if (color[temp->vertex] == c) {
            return false;  // An adjacent vertex has the same color
        }
        temp = temp->next;
    }
    return true;
}

// Recursive function to solve the graph coloring problem
bool graphColoringUtil(struct Graph* graph, int m, int color[], int v) {
    if (v == graph->numVertices) {
        return true;  // All vertices are assigned a color
    }

    for (int c = 1; c <= m; c++) {  // Try different colors
        if (isSafe(graph, color, v, c)) {
            color[v] = c;  // Assign color c to vertex v

            // Recur to assign colors to the rest of the vertices
            if (graphColoringUtil(graph, m, color, v + 1)) {
                return true;
            }

            // Backtrack
            color[v] = 0;  // Remove assigned color
        }
    }
    return false;  // No valid coloring found
}

// Function to solve the m-coloring problem
void graphColoring(struct Graph* graph, int m) {
    int color[MAX_VERTICES];  // Array to store color assignments
    for (int i = 0; i < graph->numVertices; i++) {
        color[i] = 0;  // Initialize all vertices as uncolored
    }

    if (graphColoringUtil(graph, m, color, 0) == false) {
        printf("Solution does not exist\n");
        return;
    }

    // Print the solution
    printf("Solution exists: Following are the assigned colors:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d ---> Color %d\n", i, color[i]);
    }
}

// Driver code
int main() {
    int vertices, edges, m, src, dest;

    // Input the number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    struct Graph* graph = createGraph(vertices);

    // Input edges
    printf("Enter the edges (src dest):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    // Input the number of colors
    printf("Enter the number of colors: ");
    scanf("%d", &m);

    // Solve the graph coloring problem
    graphColoring(graph, m);

    return 0;
}
