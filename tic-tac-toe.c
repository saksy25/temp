#include <stdio.h>

void initialize_board(char board[3][3]);
void display_board(char board[3][3]);
int is_valid_move(int row, int col, char board[3][3]);
int check_winner(char board[3][3]);

int main() {
    char board[3][3];
    int row, col;
    int player = 1;
    int winner = 0;

    initialize_board(board);
    do {
        display_board(board);
        do {
            printf("Player %d, enter your move (row [1-3] column [1-3]): ", player);
            scanf("%d %d", &row, &col);
            row--;
            col--;
        } while (!is_valid_move(row, col, board));

        if (player == 1) {
            board[row][col] = 'X';
            player = 2;
        } else {
            board[row][col] = 'O';
            player = 1;
        }
        winner = check_winner(board);

    } while (winner == 0);
  
    display_board(board);

    if (winner == 1) {
        printf("Player 1 (X) wins!\n");
    } else if (winner == 2) {
        printf("Player 2 (O) wins!\n");
    } else {
        printf("It's a draw!\n");
    }
    return 0;
}

void initialize_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void display_board(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int is_valid_move(int row, int col, char board[3][3]) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        return 1;
    } else {
        printf("Invalid move. Please try again.\n");
        return 0;
    }
}

int check_winner(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return (board[i][0] == 'X') ? 1 : 2;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
            return (board[0][j] == 'X') ? 1 : 2;
        }
    }

    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')) {
        return (board[1][1] == 'X') ? 1 : 2;
    }

    int draw = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                draw = 0;
                break;
            }
        }
        if (!draw) break;
    }
    if (draw) return -1;
    return 0;
}
