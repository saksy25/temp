#include<stdio.h>

void initializeBoard(char board[3][3]){
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            board[i][j] = ' ';
}

void displayInitializeBoard(){
    printf("-------------------\n");
    printf("| 1 1 | 1 2 | 1 3 |\n");
    printf("-------------------\n");
    printf("| 2 1 | 2 2 | 2 3 |\n");
    printf("-------------------\n");
    printf("| 3 1 | 3 2 | 3 3 |\n");
    printf("-------------------\n");
}

void displayBoard(char board[3][3]){
    printf("-------------\n");
    printf("| %c | %c | %c |\n", board[0][0], board[0][1], board[0][2]);
    printf("-------------\n");
    printf("| %c | %c | %c |\n", board[1][0], board[1][1], board[1][2]);
    printf("-------------\n");
    printf("| %c | %c | %c |\n", board[2][0], board[2][1], board[2][2]);
    printf("-------------\n");
}

int isValidMove(char board[3][3], int row, int col){
    if(row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') return 1;
    else return 0;
}

int checkWinner(char board[3][3]){
    for(int i=0; i<3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
            return (board[i][0] == 'X')? 1 : 2;
    }
    for(int i=0; i<3; i++){
        if(board[0][i] == board[1][i] && board[2][i] == board[0][i] && board[0][i] != ' ')
            return (board[0][i] == 'X')? 1 : 2;
    }

    if((board[0][0] == board[1][1] && board[2][2] == board[0][0] && board[0][0] != ' ') ||
       (board[0][2] == board[1][1] && board[2][0] == board[0][2] && board[0][2] != ' '))
            return (board[1][1] == 'X')? 1 : 2;

    if(!movesLeft(board)) return -1;

    return 0;
}

int movesLeft(char board[3][3]){
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(board[i][j] == ' ')
                return 1;
    return 0;
}

int evaluate(char board[3][3]){
    for(int i=0; i<3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
            return (board[i][0] == 'O')? 10 : -10;
    }
    for(int i=0; i<3; i++){
        if(board[0][i] == board[1][i] && board[2][i] == board[0][i] && board[0][i] != ' ')
            return (board[0][i] == 'O')? 10 : -10;
    }

    if((board[0][0] == board[1][1] && board[2][2] == board[0][0] && board[0][0] != ' ') ||
       (board[0][2] == board[1][1] && board[2][0] == board[0][2] && board[0][2] != ' '))
            return (board[1][1] == 'O')? 10 : -10;

    return 0;
}

void aiMove(char board[3][3]){
    int best = -1000;
    int row = -1;
    int col = -1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j] == ' '){
                board[i][j] = 'O';
                int moveVal = minMax(board, 0, 0);
                if(moveVal > best){
                    best = moveVal;
                    row = i;
                    col = j;
                }
                board[i][j] = ' ';
            }
        }
    }
    board[row][col] = 'O';
}

int minMax(char board[3][3], int depth, int isAi){
    int score = evaluate(board);
    if(score == 10 || score == -10) return score;
    if(!movesLeft(board)) return 0;

    if(isAi){
        int best = -1000;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] == ' '){
                    board[i][j] = 'O';
                    int moveVal = minMax(board, depth+1, 0);
                    best = (moveVal > best)? moveVal : best;
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else{
        int best = 1000;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] == ' '){
                    board[i][j] = 'X';
                    int moveVal = minMax(board, depth+1, 1);
                    best = (moveVal < best)? moveVal : best;
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void main(){
    char board[3][3];
    int player = 1;
    int playerChoice;
    int winner = 0;
    int row = -1;
    int col = -1;

    printf("Player : 'X' and AI : 'O' \n");
    printf("You want to play first or second? ");
    scanf("%d", &playerChoice);

    initializeBoard(board);
    displayInitializeBoard();
    printf("**User should enter the move in the format of rows and columns[1-3][1-3](for e.g. 1 2)**\n");
    do{
        displayBoard(board);
        if(player == 1 && playerChoice == 1 || player == 2 && playerChoice == 2){
            do{
                printf("Enter your move: ");
                scanf("%d%d", &row, &col);
                row--;
                col--;
            }while(!isValidMove(board, row, col));
            board[row][col] = 'X';
            player = 2;
        }
        else{
            printf("AI Move:\n");
            aiMove(board);
            player = 1;
        }

        winner = checkWinner(board);

    }while(winner == 0);

    displayBoard(board);
    if(winner == 1) printf("Player wins!");
    else if(winner == 2) printf("AI wins!");
    else printf("Its a draw!");
}
