#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100
#define INF 1e9

typedef struct {
    int size;
    int data[MAX_NODES];
} PriorityQueue;

// Priority Queue Functions
void pqInsert(PriorityQueue *pq, int node, double fScores[]) {
    pq->data[pq->size++] = node;
}

int pqExtractMin(PriorityQueue *pq, double fScores[]) {
    if (pq->size == 0) return -1;

    int minIndex = 0;
    for (int i = 1; i < pq->size; i++) {
        if (fScores[pq->data[i]] < fScores[pq->data[minIndex]]) {
            minIndex = i;
        }
    }

    int minNode = pq->data[minIndex];
    pq->data[minIndex] = pq->data[--pq->size];
    return minNode;
}

int pqContains(PriorityQueue *pq, int node) {
    for (int i = 0; i < pq->size; i++) {
        if (pq->data[i] == node) return 1;
    }
    return 0;
}

// A* Algorithm
void aStar(int nodeCount, double heuristic[], double adjMatrix[MAX_NODES][MAX_NODES], int start, int goal) {
    double gScores[MAX_NODES], fScores[MAX_NODES];
    int cameFrom[MAX_NODES];
    PriorityQueue openSet = { .size = 0 };

    // Initialize scores and cameFrom
    for (int i = 0; i < nodeCount; i++) {
        gScores[i] = INF;
        fScores[i] = INF;
        cameFrom[i] = -1;
    }

    gScores[start] = 0;
    fScores[start] = heuristic[start];
    pqInsert(&openSet, start, fScores);

    while (openSet.size > 0) {
        int current = pqExtractMin(&openSet, fScores);

        if (current == goal) {
            // Reconstruct path
            printf("Path found: ");
            int path[MAX_NODES], pathSize = 0;
            for (int temp = goal; temp != -1; temp = cameFrom[temp]) {
                path[pathSize++] = temp;
            }

            // Print path in correct order
            for (int i = pathSize - 1; i >= 0; i--) {
                printf("%d%s", path[i], (i > 0) ? " -> " : "\n");
            }
            return;
        }

        for (int neighbor = 0; neighbor < nodeCount; neighbor++) {
            if (adjMatrix[current][neighbor] == INF) continue; // Skip if no edge exists

            double tentativeGScore = gScores[current] + adjMatrix[current][neighbor];

            if (tentativeGScore < gScores[neighbor]) {
                cameFrom[neighbor] = current;
                gScores[neighbor] = tentativeGScore;
                fScores[neighbor] = gScores[neighbor] + heuristic[neighbor];

                if (!pqContains(&openSet, neighbor)) {
                    pqInsert(&openSet, neighbor, fScores);
                }
            }
        }
    }

    printf("No path found.\n");
}

int main() {
    int nodeCount, edgeCount;
    double heuristic[MAX_NODES];
    double adjMatrix[MAX_NODES][MAX_NODES];

    printf("Enter the number of nodes: ");
    scanf("%d", &nodeCount);

    // Initialize adjacency matrix
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            adjMatrix[i][j] = INF;
        }
    }

    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < nodeCount; i++) {
        printf("Node %d: ", i);
        scanf("%lf", &heuristic[i]);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edgeCount);

    printf("Enter edges (from to weight):\n");
    for (int i = 0; i < edgeCount; i++) {
        int from, to;
        double weight;
        scanf("%d %d %lf", &from, &to, &weight);
        adjMatrix[from][to] = weight;
        adjMatrix[to][from] = weight; // Remove this line if graph is directed
    }

    int start, goal;
    printf("Enter the start and goal nodes: ");
    scanf("%d %d", &start, &goal);

    aStar(nodeCount, heuristic, adjMatrix, start, goal);

    return 0;
}

// Enter the number of nodes: 10
// Enter heuristic values for each node:
// Node 0: 10
// Node 1: 8
// Node 2: 5
// Node 3: 7
// Node 4: 
// 3
// Node 5: 0
// Node 6: 1
// Node 7: 5
// Node 8: 6
// Node 9: 3
// Enter the number of edges: 14
// Enter edges (from to weight):
// 0 1 6
// 1 2 3
// 2 3 1
// 2 4 5
// 3 4 8
// 4 6 5
// 4 5 5 
// 6 7 3
// 6 9 2
// 8 9 7
// 0 8 3
// 5 6 3
// 7 8 1
// 1 3 2
// Enter the start and goal nodes: 0 5
// Path found: 0 -> 8 -> 7 -> 6 -> 5

// Time Complexity : O(V^2 + E)
