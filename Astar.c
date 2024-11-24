#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 100
#define INF 1e9

typedef struct {
    int x, y;
    float gCost, hCost;
} Node;

Node openSet[MAX_NODES];
int openSetSize = 0;
Node cameFrom[MAX_NODES];
float gScore[MAX_NODES * MAX_NODES];

int heuristic(Node a, Node b) {
    return abs(a.x - b.x) + abs(a.y - b.y); // Manhattan distance
}

int inOpenSet(Node node) {
    for (int i = 0; i < openSetSize; i++) {
        if (openSet[i].x == node.x && openSet[i].y == node.y) {
            return 1;
        }
    }
    return 0;
}

void addToOpenSet(Node node) {
    openSet[openSetSize++] = node;
}

Node getLowestFCostNode() {
    Node lowest = openSet[0];
    for (int i = 1; i < openSetSize; i++) {
        if ((openSet[i].gCost + openSet[i].hCost) < (lowest.gCost + lowest.hCost)) {
            lowest = openSet[i];
        }
    }
    return lowest;
}

void reconstructPath(Node start, Node goal) {
    Node current = goal;
    printf("Path found:\n");
    while (current.x != start.x || current.y != start.y) {
        printf("(%d, %d) ", current.x, current.y);
        current = cameFrom[current.x * MAX_NODES + current.y];
    }
    printf("(%d, %d)\n", start.x, start.y);
}

void aStar(int **grid, int gridSize, Node start, Node goal) {
    addToOpenSet(start);
    gScore[start.x * gridSize + start.y] = 0;

    while (openSetSize > 0) {
        Node current = getLowestFCostNode();
        
        if (current.x == goal.x && current.y == goal.y) {
            reconstructPath(start, current);
            return;
        }

        // Remove current node from open set
        for (int i = 0; i < openSetSize; i++) {
            if (openSet[i].x == current.x && openSet[i].y == current.y) {
                openSet[i] = openSet[--openSetSize];
                break;
            }
        }

        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

        for (int i = 0; i < 4; i++) {
            int newX = current.x + directions[i][0];
            int newY = current.y + directions[i][1];

            if (newX >= 0 && newY >= 0 && newX < gridSize && newY < gridSize && grid[newX][newY] == 0) {
                Node neighbor = {newX, newY, current.gCost + 1, heuristic((Node){newX, newY}, goal)};
                if (!inOpenSet(neighbor) || neighbor.gCost < gScore[newX * gridSize + newY]) {
                    cameFrom[newX * gridSize + newY] = current;
                    gScore[newX * gridSize + newY] = neighbor.gCost;
                    if (!inOpenSet(neighbor)) {
                        addToOpenSet(neighbor);
                    }
                }
            }
        }
    }

    printf("No path found.\n");
}

int main() {
    int gridSize;
    printf("Enter the grid size (N x N): ");
    scanf("%d", &gridSize);

    // Dynamic memory allocation for grid
    int **grid = malloc(gridSize * sizeof(int *));
    for (int i = 0; i < gridSize; i++) {
        grid[i] = malloc(gridSize * sizeof(int));
    }

    printf("Enter the grid (0 for walkable, 1 for obstacle):\n");
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    Node start, goal;
    printf("Enter the start position (x y): ");
    scanf("%d %d", &start.x, &start.y);
    printf("Enter the goal position (x y): ");
    scanf("%d %d", &goal.x, &goal.y);

    // Initialize gScore for all nodes to infinity
    for (int i = 0; i < MAX_NODES * MAX_NODES; i++) {
        gScore[i] = INF;
    }

    aStar(grid, gridSize, start, goal);

    // Free allocated memory
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}