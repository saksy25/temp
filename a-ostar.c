#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 100
#define MAX_CONDITIONS 10
#define MAX_NAME_LENGTH 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    int cost;
} Node;

typedef struct {
    char or_nodes[MAX_CONDITIONS][MAX_NAME_LENGTH];
    int or_count;
    char and_nodes[MAX_CONDITIONS][MAX_NAME_LENGTH];
    int and_count;
} Condition;

Node nodes[MAX_NODES];
Condition conditions[MAX_NODES];
int node_count = 0;
int condition_count = 0;

// Function to get the cost of a node by its name
int get_node_cost(const char *name) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].name, name) == 0) {
            return nodes[i].cost;
        }
    }
    return INT_MAX; // Return a large value if node not found
}

// Function to calculate costs based on AND/OR conditions
int calculate_cost(const Condition *condition) {
    int total_cost = 0;

    // Calculate AND cost
    if (condition->and_count > 0) {
        for (int i = 0; i < condition->and_count; i++) {
            total_cost += get_node_cost(condition->and_nodes[i]);
        }
    }

    // Calculate OR cost
    if (condition->or_count > 0) {
        int min_or_cost = INT_MAX;
        for (int i = 0; i < condition->or_count; i++) {
            int cost = get_node_cost(condition->or_nodes[i]);
            if (cost < min_or_cost) {
                min_or_cost = cost;
            }
        }
        total_cost += min_or_cost;
    }

    return total_cost;
}

// Function to update the costs for all nodes based on conditions
void update_costs() {
    for (int i = 0; i < condition_count; i++) {
        int cost = calculate_cost(&conditions[i]);
        nodes[i].cost = cost;
        printf("Updated Cost for %s: %d\n", nodes[i].name, nodes[i].cost);
    }
}

// Function to print the shortest path
void print_shortest_path(const char *start) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].name, start) == 0) {
            printf("Shortest Path from %s: Cost = %d\n", start, nodes[i].cost);
            return;
        }
    }
    printf("Node %s not found!\n", start);
}

int main() {
    // Initialize nodes and their costs
    strcpy(nodes[node_count].name, "A"); nodes[node_count++].cost = -1;
    strcpy(nodes[node_count].name, "B"); nodes[node_count++].cost = 5;
    strcpy(nodes[node_count].name, "C"); nodes[node_count++].cost = 2;
    strcpy(nodes[node_count].name, "D"); nodes[node_count++].cost = 4;
    strcpy(nodes[node_count].name, "E"); nodes[node_count++].cost = 7;
    strcpy(nodes[node_count].name, "F"); nodes[node_count++].cost = 9;
    strcpy(nodes[node_count].name, "G"); nodes[node_count++].cost = 3;
    strcpy(nodes[node_count].name, "H"); nodes[node_count++].cost = 0;
    strcpy(nodes[node_count].name, "I"); nodes[node_count++].cost = 0;
    strcpy(nodes[node_count].name, "J"); nodes[node_count++].cost = 0;

    // Initialize conditions
    // A: OR(B), AND(C, D)
    strcpy(conditions[condition_count].or_nodes[0], "B");
    conditions[condition_count].or_count = 1;
    strcpy(conditions[condition_count].and_nodes[0], "C");
    strcpy(conditions[condition_count].and_nodes[1], "D");
    conditions[condition_count].and_count = 2;
    condition_count++;

    // B: OR(E, F)
    strcpy(conditions[condition_count].or_nodes[0], "E");
    strcpy(conditions[condition_count].or_nodes[1], "F");
    conditions[condition_count].or_count = 2;
    conditions[condition_count].and_count = 0; // No AND conditions
    condition_count++;

    // C: OR(G), AND(H, I)
    strcpy(conditions[condition_count].or_nodes[0], "G");
    conditions[condition_count].or_count = 1;
    strcpy(conditions[condition_count].and_nodes[0], "H");
    strcpy(conditions[condition_count].and_nodes[1], "I");
    conditions[condition_count].and_count = 2;
    condition_count++;

    // D: OR(J)
    strcpy(conditions[condition_count].or_nodes[0], "J");
    conditions[condition_count].or_count = 1;
    conditions[condition_count].and_count = 0; // No AND conditions
    condition_count++;

    printf("Updated Costs:\n");
    update_costs();
    printf("\n");

    print_shortest_path("A");

    return 0;
}