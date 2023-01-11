#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "othello.h"


//main function
int main(){
    // call welcomeScreen
    welcomeScreen();
    //call clearScreen
    clearScreen();
    //call displayExplicitBoard
    //displayExplicitBoard();

    // call playGame
    playGame();

    return 0;
}

 void welcomeScreen(){
     //create separation at top
     printf("\n\n");
     //Hello graphic
     printf("\t\t  OOOO   TTTTTTTT  HH  HH  EEEEE  LL       LL        OOOO \n");
     printf("\t\t OO  OO     TT     HH  HH  EE     LL       LL       OO  OO \n");
     printf("\t\t OO  OO     TT     HHHHHH  EEEEE  LL       LL       OO  OO \n");
     printf("\t\t OO  OO     TT     HH  HH  EE     LL       LL       OO  OO \n");
     printf("\t\t  OOOO      TT     HH  HH  EEEEE  LLLLLLL  LLLLLLL   OOOO \n");
     printf("\n\n");

     //Create section to display rules
     printf("  OTHELLO GAME RULES:\n");
     //list out rules
     printf("\t\t 1. A square 8 x 8 board\n");
     printf("\t\t 2. 64 discs colored black (X) on one side and white (O) on the opposite side.\n");
     printf("\t\t 3. The board will start with 2 black discs (X) and 2 white discs (O) at the center of the board.\n");
     printf("\t\t 4. They are arranged with black (X) forming a North-East to South-West direction. White (O) is forming a North-West to South-East direction. \n");
     printf("\t\t 5. The goal is to get the majority of color discs on the board at the end of the game.\n");
     printf("\t\t 6. Each player gets 32 discs and black (X) always starts the game. \n");
     printf("\t\t 7. The game alternates between white (O) and black (X) until one player can not make a valid move to outflank the opponent or both players have no valid moves. \n");
     printf("\t\t 8. When a player has no valid moves, they pass their turn and the opponent continues. \n");
     printf("\t\t 9. A player cannot voluntarily forfeit their turn. \n");
     printf("\t\t 10. When both players can not make a valid move the game ends. \n");
     printf("\n\n");



 }

 void displayExplicitBoard(){
     //create game board
     //use dashed lines to separate rows and vertical lines to define boxes/game spaces
     printf("|--------------------------------------|\n");
     printf("|      | A | B | C | D | E | F | G | H |\n");
     printf("|--------------------------------------|\n");
     printf("|  1   |   |   |   |   |   |   |   |   |\n");
     printf("|--------------------------------------|\n");
     printf("|  2   |   |   |   |   |   |   |   |   |\n");
     printf("|--------------------------------------|\n");
     printf("|  3   |   |   |   |   |   |   |   |   |\n");
     printf("|--------------------------------------|\n");
     printf("|  4   |   |   |   | O | X |   |   |   |\n");
     printf("|--------------------------------------|\n");
     printf("|  5   |   |   |   | X | O |   |   |   |\n");
     printf("|--------------------------------------|\n");
     printf("|  6   |   |   |   |   |   |   |   |   |\n");
     printf("|--------------------------------------|\n");
     printf("|  7   |   |   |   |   |   |   |   |   |\n");
     printf("|--------------------------------------|\n");
     printf("|  8   |   |   |   |   |   |   |   |   |\n");
     printf("|--------------------------------------|\n");

 }

 void clearScreen(){
     //prompt user to hit enter to show game screen
     printf("\t\t\t\t Hit <ENTER> to continue! \n");
     char clearer;
     scanf("%c", &clearer);
     //windows
     system("cls");
     //system("clear"); not for Windows

 }

 void playGame(){
    //create board variable
    char board[ROW][COL];

    //variables for player names
    struct Player playerX;
    struct Player playerO;

    // variable for current player; X goes first
    int currentPlayer = PLAYER_X;

    // variable for loop control
    int loop = ZERO;

    // prompt and read Player X name
    printf("Player X, please enter your name\n");
    scanf("%s", playerX.playerName);
    playerX.playerNum = PLAYER_X;
    playerX.discCount = ZERO;
    playerX.playChar = 'X';

    // prompt and read Player O name
    printf("Player O, please enter your name\n");
    scanf("%s", playerO.playerName);
    playerO.playerNum = PLAYER_O;
    playerO.discCount = ZERO;
    playerO.playChar = 'O';

    // print statement using names to play Othello
    printf("%s and %s, let's play Othello!\n", playerX.playerName, playerO.playerName);

    //calling functions
    initializeBoard(board);

    //create variable to end game
    int endGame = FALSE;

    // while loop to change turns
    while(endGame == FALSE){
        endGame = isEndGame(board);
        displayBoard(board);

       if (endGame == TRUE){
            gameOver(board, playerX, playerO);
            break;
        }

        // if Player X is up, notify them of their turn then change current player
        if (currentPlayer == PLAYER_X){
            if (validMoveExists(board, playerX.playChar) == TRUE){
                makeMove(&playerX, board);
                currentPlayer = PLAYER_O;
            }
            else {
                currentPlayer = PLAYER_O;
            }
        }

        // do the same for Player O
        else if (currentPlayer == PLAYER_O){
            if (validMoveExists(board, playerO.playChar) == TRUE){
                makeMove(&playerO, board);
                currentPlayer = PLAYER_X;
            }
            else{
                currentPlayer = PLAYER_X;
            }

        }
        updateDiscCount(board, &playerX);
        updateDiscCount(board, &playerO);
        displayStats(playerX);
        displayStats(playerO);
    }
 }

 void initializeBoard(char board[ROW][COL]){
     //loop through rows and columns to fill out table
     for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COL; col++){
            // fill out X and O to replicate initial table
            if ((row == 3 && col == 3) || (row == 4 && col == 4)){
                board[row][col] = 'O';
            }
            else if((row == 3 && col == 4 ) || (row == 4 && col == 3)){
                board[row][col] = 'X';
            }
            else {
                board[row][col] = SPACE;
            }
        }
     }
 }

 void displayBoard(char board[ROW][COL]){
     //printf statements
     printf("|----------------------------------------------------|\n");
     printf("|    |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |\n");
     printf("|----------------------------------------------------|\n");
     //for loop to show row value and value stored in element
     for (int row = 0; row < ROW; row++){
        printf("| %d  |", row + 1);
        for (int col = 0; col < COL; col++){
            printf("  %c  |", board[row][col]);
        }
        //move to next line and create separation
        printf("\n");
        printf("|----------------------------------------------------|\n");
     }
 }

 void makeMove(struct Player *player, char board[ROW][COL]){
     // create variable to measure length of move input
     char move[THREE];
     int valid = FALSE;

     // loop to ensure move entered is valid
     while (valid == FALSE){
        printf("%s, enter your move location.(e.g. b6)\n", player->playerName);
        scanf("%s", move);
        printf("%s, you entered %s\n", player->playerName, move);
        int length = (int)strlen(move);
        if (length == TWO){
            valid = TRUE;
        } else{
            valid = FALSE;
        }
        // if not length of 2, prompt user to reinput move
        if (valid == FALSE){
            printf("Invalid move, try again.\n\n");
        }
        else {
            valid = isValid(move, board, player);
        }

        if (valid == FALSE){
            printf("Invalid move, try again.\n\n");
        }
        else{
            printf("Selected move is valid!\n\n");
        }
     }
 }

 int isValid(char move[THREE], char board[ROW][COL], struct Player* player){
    int valid = FALSE;
    valid = isOpen(move, board);
    if (valid == FALSE){
        return valid;
    }
    //get value from isOutFlank, if it is a flank update the board
    valid = isOutFlank(move, board, player->playChar);
    if (valid == TRUE){
         updateBoard(move, board, player);
    }

    return valid;
 }

 int isOpen(char move[THREE], char board[ROW][COL]){
    int open = FALSE;
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);

    if (rowInt != INVALID && colInt != INVALID){
        if (board[rowInt][colInt] == SPACE){
            open = TRUE;
        }
        else{
            open = FALSE;
        }
    }
    return open;

}

int getMoveRow(char move[THREE]){
    char row = move[1];
    int valueRow = row - '1';
    if(valueRow == INVALID || valueRow > ROW){
        return INVALID;
    }
    else{
        return valueRow;
    }
}

int getMoveCol(char move[THREE]){
    char col = move[0];
    int valueCol = col - 'a';
    if (valueCol == INVALID || valueCol >= COL){
        return INVALID;
    }
    else {
        return valueCol;
    }

}

void displayStats(struct Player player){
    printf("\nPlayer name: %s\n", player.playerName);
    printf("Player number: %d\n", player.playerNum);
    printf("Player character: %c\n", player.playChar);
    printf("Player discs: %d\n", player.discCount);

}

int isOutFlank (char move[THREE], char board[ROW][COL], char playChar){
    int flank = FALSE;
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);
    // if any of the checks return > 0, return that it is a flank
    if ((checkHorizontal(rowInt, colInt, board, playChar) > ZERO) ||
        (checkVertical(rowInt, colInt, board, playChar) > ZERO) ||
        (checkDiagonal(rowInt, colInt, board, playChar) > ZERO)){
        flank = TRUE;
    }
    return flank;

}

int checkVertical(int row, int col, char board[ROW][COL], char playerChar){
    //start a variable to hold flank and disc value
    int flank = FALSE;
    int disc = 0;

    //if value above is not a space and is equal to current character it is a flank
    if (board[row-1][col] != SPACE){
        if (board[row-1][col] == playerChar){
            flank = TRUE;
        }
        //if not the current players character, find the amount of rows in between the two and return the amount of discs minus one(the input value)
        else{
            for (int i = 1; row - i > ZERO; i++){
                if(board[row - i][col] == playerChar){
                    disc = row - (row - i) - 1;
                    flank = TRUE;
                }
            }
        }
    }
    //do nothing if it is a space
    else if (board[row - 1][col] == SPACE){
    }

    //if value below is not a space and is equal to playChar, return flank
    if (board[row+1][col] != SPACE){
        if (board[row+1][col] == playerChar){
            flank = TRUE;
        }
        //if not, check all rows until playChar is found and return the amount of discs between the two.
        else{
            for (int i = 1; row + i < ROW; i++){
                if (board [row + i][col] == playerChar){
                    disc = (row + i) - row - 1;
                    flank = TRUE;
                    }
                }
            }
        }
    else if (board[row + 1][col] == SPACE){
    }

    //if more than one disc between the two characters and it is a flank, return the amount of discs. If not return ZERO
    if (disc > ZERO && flank == TRUE){
        return disc;
    }
    else{
        return ZERO;
    }
}

int checkHorizontal(int row, int col, char board[ROW][COL], char playerChar){
    //start variable for flank and discs
    int flank = FALSE;
    int disc = 0;

    //if value to the left isn't a space or playerChar, it is a flank
    if (board[row][col-1] != SPACE){
        if (board[row][col-1] == playerChar){
            flank = TRUE;
        }
        // else check the columns to the left and find the amount of discs until current players character is found
        else{
            for (int i = 1; col - i > ZERO; i++){
                if(board[row][col - i] == playerChar){
                    disc = col - (col - i) - 1;
                    flank = TRUE;
                }
            }
        }
    }
    //do nothing if it is a space
    else if (board[row][col - 1] == SPACE){
    }

    //check if column to the right is not a space and is equal to playChar, return flank if it is
    if (board[row][col + 1] != SPACE){
        if (board[row][col + 1] == playerChar){
            flank = TRUE;
        }
        //loop through columns to the right and find the amount of discs needed to be flipped
        else{
            for (int i = 1; col + i < COL; i++){
                if (board [row][col + i] == playerChar){
                    disc = (col + i) - col - 1;
                    flank = TRUE;
                    }
                }
            }
        }
    // do nothing if it is a space
    else if (board[row][col + 1] == SPACE){
    }

    //if there are discs to be flipped and is a flank, return the amount of discs. If not return 0
    if (disc > ZERO && flank == TRUE){
        return disc;
    }
    else{
        return ZERO;
    }
}

int checkDiagonal(int row, int col, char board[ROW][COL], char playerChar){
    int disc = 0;
    int flank = FALSE;
    int c = col;
    int r = row;

    //check up and left first
    r--;
    c--;

    //if space above and to the left is space, stop checking
    //if the same character as the player, stop checking, if not count the disc
    while(c >= MIN && r >= MIN){
        if (board[r][c] == SPACE){
            break;
        }
        else{
            if (board[r][c] != playerChar){
                disc++;
            }
            else{
                flank = TRUE;
                break;
            }
        }
        r--;
        c--;
    }


    //check down and left
    r = row;
    c = col;

    r++;
    c--;

    //if space below and to the left is space, stop checking
    //if the same character as the player, stop checking, if not count the disc
    while(c >= MIN && r <= MAX){
        if (board[r][c] == SPACE){
            break;
        }
        else{
            if (board[r][c] != playerChar){
                disc++;
            }
            else{
                flank = TRUE;
                break;
            }
        }
        r++;
        c--;
    }

    //check up and right
    r = row;
    c = col;

    r--;
    c++;

    //if space above and to the right is space, stop checking
    //if the same character as the player, stop checking, if not count the disc
    while(c <= MAX && r >= MIN){
        if (board[r][c] == SPACE){
            break;
        }
        else{
            if (board[r][c] != playerChar){
                disc++;
            }
            else{
                flank = TRUE;
                break;
            }
        }
        r--;
        c++;
    }

    //check down and right
    r = row;
    c = col;

    r++;
    c++;

    //if space below and to the right is space, stop checking
    //if the same character as the player, stop checking, if not count the disc
    while(c <= MAX && r <= MAX){
        if (board[r][c] == SPACE){
            break;
        }
        else{
            if (board[r][c] != playerChar){
                disc++;
            }
            else{
                flank = TRUE;
                break;
            }
        }
        r++;
        c++;
    }

    if (disc > ZERO && flank == TRUE){
        return disc;
    }
    else{
        return ZERO;
    }

}

void updateBoard(char move[THREE], char board[ROW][COL], struct Player* player){
    int rowInt = getMoveRow(move);
    int colInt = getMoveCol(move);
    //if any of the checks found discs to be replaced, call update functions to swap characters
    if (checkHorizontal(rowInt, colInt, board, player->playChar) > ZERO){
        updateHorizontal(rowInt, colInt, board, player);
    }
    if (checkVertical(rowInt, colInt, board, player->playChar) > ZERO){
        updateVertical(rowInt, colInt, board, player);
    }
    if (checkDiagonal(rowInt, colInt, board, player->playChar) > ZERO){
        updateDiagonal(rowInt, colInt, board, player);
    }
}

void updateHorizontal(int row, int col, char board[ROW][COL], struct Player* player){
    //input character at move location
    board[row][col] = player->playChar;
    if (board[row][col-1] != SPACE && board[row][col-1] != player->playChar){
        //loop through all columns to the left
        for (int i = 1; col - i > ZERO; i++){
            //replace characters until current player's character is found
            if (board[row][col-i] == player->playChar){
                break;
            }
            else {
                if (board[row][col-i] == 'X'){
                    board[row][col-i] = 'O';
                }
                else if (board[row][col-i] == 'O'){
                    board[row][col-i] = 'X';
                }
            }
        }
    }
     if ((board[row][col+1] != SPACE) && (board[row][col+1] != player->playChar)){
        //loop through all characters the the right
        for (int i = 1; col + i < COL; i++){
            // replace all characters until current player's character is found
            if (board[row][col+i] == player->playChar){
                break;
            }
            else {
                if (board[row][col+i] == 'X'){
                    board[row][col+i] = 'O';
                }
                else if (board[row][col+i] == 'O'){
                    board[row][col+i] = 'X';
                }
            }
        }
    }
}

void updateVertical(int row, int col, char board[ROW][COL], struct Player* player){
    //input character at move location
    board[row][col] = player->playChar;
    if (board[row-1][col] != SPACE && board[row-1][col] != player->playChar){
        //loop through all rows above
        for (int i = 1; row - 1 > ZERO; i++){
            //if the value does not equal the character of the current player, switch the character out
            if (board[row-i][col] == player->playChar){
                break;
            }
            else {
                if (board[row-i][col] == 'X'){
                    board[row-i][col] = 'O';
                }
                else if (board[row-i][col] == 'O'){
                    board[row-i][col] = 'X';
                }
            }
        }
    }
     if (board[row+1][col] != SPACE && board[row+1][col] != player->playChar){
        //loop through all rows below
        for (int i = 1; row + i < ROW; i++){
            //replace all characters until the character of the currentplayer is found
            if (board[row+i][col] == player->playChar){
                break;
            }
            else {
                if (board[row+i][col] == 'X'){
                    board[row+i][col] = 'O';
                }
                else if (board[row+i][col] == 'O'){
                    board[row+i][col] = 'X';
                }
            }
        }
    }
}

void updateDiagonal(int row, int col, char board[ROW][COL], struct Player* player){
    //update board with players move
    board[row][col] = player->playChar;
    int r = row;
    int c = col;

    //go up and left
    r--;
    c--;

    // if character above and to the left is a space, stop checking
    // if it is a different character from the player, switch it
    while (r >= MIN && c >= MIN){
        if (board[r][c] == SPACE){
            break;
        }
        else {
            if (board[r][c] != player->playChar){
                board[r][c] = player->playChar;
            }
            else{
                break;
            }
        }
        r--;
        c--;
    }

    //go down and left
    r = row;
    c = col;

    r++;
    c--;

    // if character down and to the left is a space, stop checking
    // if it is a different character from the player, switch it
    while (r <= MAX && c >= MIN){
        if (board[r][c] == SPACE){
            break;
        }
        else {
            if (board[r][c] != player->playChar){
                board[r][c] = player->playChar;
            }
            else{
                break;
            }
        }
        r++;
        c--;
    }

    //go up and right
    r = row;
    c = col;

    r--;
    c++;

    // if character above and to the right is a space, stop checking
    // if it is a different character from the player, switch it
    while (r >= MIN && c <= MAX){
        if (board[r][c] == SPACE){
            break;
        }
        else {
            if (board[r][c] != player->playChar){
                board[r][c] = player->playChar;
            }
            else{
                break;
            }
        }
        r--;
        c++;
    }

    //go down and right
    r = row;
    c = col;

    r++;
    c++;

    // if character down and to the right is a space, stop checking
    // if it is a different character from the player, switch it
    while (r <= MAX && c <= MAX){
        if (board[r][c] == SPACE){
            break;
        }
        else {
            if (board[r][c] != player->playChar){
                board[r][c] = player->playChar;
            }
            else{
                break;
            }
        }
        r++;
        c++;
    }

}

void updateDiscCount(char board[ROW][COL], struct Player* player){
    //set discCount to 0 for new round
    player->discCount = ZERO;
    // loop through rows and columns and update discCount for every character found
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if (board[i][j] == player->playChar){
                player->discCount++;
            }
        }
    }
}

int isEndGame(char board[ROW][COL]){
    //full board scenario
    /*setFullBoard(board);
    displayBoard(board);
    system("pause");*/

    //if the amount of discs is 64, there are no more spaces to play, therefore game is over
    if (getDiscCount(board) == SQUARES){
        return TRUE;
    }

    //no move scenario
    /*setNoMoveBoard(board);
    displayBoard(board);
    system("pause");*/

    //if no valid move exists for either player, game is over
    if (validMoveExists(board, 'X') == FALSE &&
        validMoveExists(board, 'O') == FALSE){
        return TRUE;
    }


    return FALSE;

}

int getDiscCount(char board[ROW][COL]){
    int disc = ZERO;

    // loop through rows and columns and increment variable for spaces
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if (board[i][j] != SPACE){
                disc++;
            }
        }
    }
    return disc;
}

int validMoveExists(char board[ROW][COL], char playerChar){
    int spaces = ZERO;
    int result = FALSE;

    // loop through rows and columns, if value is a space increment the counter
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if (board[i][j] == SPACE){
                spaces++;
            }
            // if there is at least one space left check to see if any moves are possible, if not return no valid move exists
            if (spaces > ZERO){
                if (checkHorizontal(i, j, board, playerChar) == ZERO
                    && checkVertical(i, j, board, playerChar) == ZERO
                    && checkDiagonal(i, j, board, playerChar) == ZERO){
                        result = FALSE;
                }
                //otherwise there still exists some valid move
                else{
                    result = TRUE;
                    break;
                }
            }
            }
        if (result == TRUE){
            break;
            }
        }
    return result;
}

void gameOver(char board[ROW][COL], struct Player playerX, struct Player playerO){
    printf("******************************************************\n");
    printf("********************* GAME OVER **********************\n");
    printf("******************************************************\n");

    //display the board and stats for the players at the end of the game
    displayBoard(board);
    updateDiscCount(board, &playerO);
    updateDiscCount(board, &playerX);

    displayStats(playerX);
    displayStats(playerO);
}

// test end game support function
void setFullBoard(char board[ROW][COL])
{
    for(int row = ZERO; row < ROW; row++)
    {
        for(int col = ZERO; col < COL; col++)
        {
            if(row % TWO == ZERO && col % TWO == ZERO)
                board[row][col] = 'X';
            else
                board[row][col] = 'O';
        }
    }
}
// test end game support function
void setNoMoveBoard(char board[ROW][COL])
{
    // row 0
    // {'X','X','X','X','X','O','X','O'}
    board[0][0] = 'X';
    board[0][1] = 'X';
    board[0][2] = 'X';
    board[0][3] = 'X';
    board[0][4] = 'X';
    board[0][5] = 'O';
    board[0][6] = 'X';
    board[0][7] = 'O';
    // row 1
    // {'O','X','X','O','O','O','X','O'}
    board[1][0] = 'O';
    board[1][1] = 'X';
    board[1][2] = 'X';
    board[1][3] = 'O';
    board[1][4] = 'O';
    board[1][5] = 'O';
    board[1][6] = 'X';
    board[1][7] = 'O';
    // row 2
    // {'X','X','X','X','X','X','X','O'}
    board[2][0] = 'X';
    board[2][1] = 'X';
    board[2][2] = 'X';
    board[2][3] = 'X';
    board[2][4] = 'X';
    board[2][5] = 'X';
    board[2][6] = 'X';
    board[2][7] = 'O';
    // row 3
    // {'X','X','X','X','X','X','X','O'}
    board[3][0] = 'X';
    board[3][1] = 'X';
    board[3][2] = 'X';
    board[3][3] = 'X';
    board[3][4] = 'X';
    board[3][5] = 'X';
    board[3][6] = 'X';
    board[3][7] = 'O';
    // row 4
    // {'O','X','X','O','X','X','X','O'}
    board[4][0] = 'O';
    board[4][1] = 'X';
    board[4][2] = 'X';
    board[4][3] = 'O';
    board[4][4] = 'X';
    board[4][5] = 'X';
    board[4][6] = 'X';
    board[4][7] = 'O';
    // row 5
    // {'O','O','X','O','O','X','X','O'}
    board[5][0] = 'O';
    board[5][1] = 'O';
    board[5][2] = 'X';
    board[5][3] = 'O';
    board[5][4] = 'O';
    board[5][5] = 'X';
    board[5][6] = 'X';
    board[5][7] = 'O';
    // row 6
    // {'O','O','X','X','O','O','X','O'}
    board[6][0] = 'O';
    board[6][1] = 'O';
    board[6][2] = 'X';
    board[6][3] = 'x';
    board[6][4] = 'O';
    board[6][5] = 'O';
    board[6][6] = 'X';
    board[6][7] = 'O';
    // row 7
    // {'O','O','O','O','O','O','O',' '}
    board[7][0] = 'O';
    board[7][1] = 'O';
    board[7][2] = 'O';
    board[7][3] = 'O';
    board[7][4] = 'O';
    board[7][5] = 'O';
    board[7][6] = 'O';
    board[7][7] = ' ';
}
