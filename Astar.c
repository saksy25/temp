//cORRECT CODE;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef struct Edge Edge;
typedef struct Node Node;

struct Edge {
    Node* target;
    double cost;
};

struct Node {
    char name[2];
    Edge* neighbors;
    int neighborCount;
    double gCost; // Cost from start to this node
    double hCost; // Heuristic cost to the goal
    Node* parent;
};

// Initialize a node with its name and heuristic cost
Node* createNode(char* name, double hCost) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->hCost = hCost;
    node->gCost = INFINITY;
    node->neighbors = NULL;
    node->neighborCount = 0;
    node->parent = NULL;
    return node;
}

void addEdge(Node* from, Node* to, double cost) {
    from->neighbors = realloc(from->neighbors, sizeof(Edge) * (from->neighborCount + 1));
    from->neighbors[from->neighborCount].target = to;
    from->neighbors[from->neighborCount].cost = cost;
    from->neighborCount++;
}


void reconstructPath(Node* goal) {
    if (goal == NULL) return;
    reconstructPath(goal->parent);
    printf("%s ", goal->name);
}

int compareNodes(const void* a, const void* b) {
    Node* nodeA = (Node*)a;
    Node* nodeB = (Node*)b;
    double fCostA = nodeA->gCost + nodeA->hCost;
    double fCostB = nodeB->gCost + nodeB->hCost;
    return (fCostA > fCostB) - (fCostA < fCostB);
}

// A* algorithm implementation

void aStar(Node* start, Node* goal) {
    Node* openList[100]; // Priority queue for open list
    int openListSize = 0;
    Node* closedList[100];
    int closedListSize = 0;

    start->gCost = 0;
    openList[openListSize++] = start;

    while (openListSize > 0) {
        qsort(openList, openListSize, sizeof(Node*), compareNodes);
        Node* current = openList[0];

        // If the goal node is reached
        if (current == goal) {
            printf("Path found: ");
            reconstructPath(goal);
            printf("\n");
            return;
        }

        // Remove current node from openList
        for (int i = 1; i < openListSize; i++) {
            openList[i - 1] = openList[i];
        }
        openListSize--;

        closedList[closedListSize++] = current;

        // Explore neighbors
        for (int i = 0; i < current->neighborCount; i++) {
            Node* neighbor = current->neighbors[i].target;
            double tentativeGCost = current->gCost + current->neighbors[i].cost;

            int inClosedList = 0;
            for (int j = 0; j < closedListSize; j++) {
                if (closedList[j] == neighbor) {
                    inClosedList = 1;
                    break;
                }
            }
            if (inClosedList) continue;

            if (tentativeGCost < neighbor->gCost) {
                neighbor->gCost = tentativeGCost;
                neighbor->parent = current;

                int inOpenList = 0;
                for (int j = 0; j < openListSize; j++) {
                    if (openList[j] == neighbor) {
                        inOpenList = 1;
                        break;
                    }
                }
                if (!inOpenList) {
                    openList[openListSize++] = neighbor;
                }
            }
        }
    }
    printf("No path found.\n");
}
//O(V 2 logV+E)

int main() {

    Node* S = createNode("S", 14);
   Node* B = createNode("B", 12);
    Node* C = createNode("C", 4);
    Node* D = createNode("D", 3);
    Node* E = createNode("E", 5);
    Node* F = createNode("F", 6);
    Node* G = createNode("G", 2);
    addEdge(S, C, 2);
    addEdge(S, D, 2);
    addEdge(D, G, 2);
    addEdge(D, B, 2);
    addEdge(C, F, 2);
    addEdge(C, E, 2);
    // addEdge(E, G, 6);
    // addEdge(F, G, 16);
    // addEdge(D, E, 2);
    aStar(S, G);
    free(S);
    free(B);
    free(C);
    free(D);
    free(E);
    free(F);
    free(G);

    return 0;
}
