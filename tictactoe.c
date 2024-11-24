#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printSolution(int **board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int **board, int row, int col, int N) {
    // Check this row on left side
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQUtil(int **board, int col, int N) {
    // base case: If all queens are placed, return true
    if (col >= N)
        return true;

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            // Place this queen in board[i][col]
            board[i][col] = 1;

            // recur to place the rest of the queens
            if (solveNQUtil(board, col + 1, N))
                return true;

            // If placing queen in board[i][col] doesn't lead to a solution
            board[i][col] = 0; // backtrack
        }
    }

    return false;
}

bool solveNQ(int N) {
    // Dynamically allocate memory for the chessboard
    int **board = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        board[i] = (int *)malloc(N * sizeof(int));

    // Initialize the board with 0s
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    if (solveNQUtil(board, 0, N) == false) {
        printf("Solution does not exist\n");
        return false;
    }

    printSolution(board, N);

    // Free allocated memory
    for (int i = 0; i < N; i++)
        free(board[i]);
    free(board);

    return true;
}

int main() {
    int N;
    printf("Enter the number of queens (N): ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    solveNQ(N);
    return 0;
}

