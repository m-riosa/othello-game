#ifndef OTHELLO_H_INCLUDED
#define OTHELLO_H_INCLUDED

// Macros
#define TRUE 1
#define FALSE 0
#define NAME 20
#define ROW 8
#define COL 8
#define SPACE ' '
#define PLAYER_X 1
#define PLAYER_O 2
#define ZERO 0
#define ONE 1
#define TWO 2
#define FOUR 4
#define INVALID -1
#define THREE 3
#define MIN 0
#define MAX 7
#define EIGHT 8
#define SQUARES 64

struct Player{
    int playerNum;
    char playerName[20];
    int discCount;
    char playChar;
};

//write prototypes for functions
void welcomeScreen ();
void displayExplicitBoard();
void clearScreen();
void playGame();
void initializeBoard(char board[ROW][COL]);
void displayBoard(char board[ROW][COL]);
void makeMove(struct Player *player, char board[ROW][COL]);
int isValid(char move[TWO], char board[ROW][COL], struct Player* player);
int getMoveRow(char move[TWO]);
int getMoveCol(char move[TWO]);
int isOpen(char move[TWO], char board[ROW][COL]);
void displayStats(struct Player player);
int isOutFlank(char move[THREE], char board[ROW][COL], char playChar);
int checkHorizontal(int row, int col, char board[ROW][COL], char playerChar);
int checkVertical(int row, int col, char board[ROW][COL], char playerChar);
int checkDiagonal(int row, int col, char board[ROW][COL], char playerChar);
void updateBoard(char move[THREE], char board[ROW][COL], struct Player* player);
void updateHorizontal(int row, int col, char board[ROW][COL], struct Player* player);
void updateVertical(int row, int col, char board[ROW][COL], struct Player* player);
void updateDiagonal(int row, int col, char board[ROW][COL], struct Player* player);
void updateDiscCount(char board[ROW][COL], struct Player* player);
int isEndGame (char board[ROW][COL]);
int getDiscCount (char board[ROW][COL]);
int validMoveExists (char board[ROW][COL], char playerChar);
void gameOver(char board[ROW][COL], struct Player playerX, struct Player playerO);
void setFullBoard (char board[ROW][COL]);
void setNoMoveBoard (char board[ROW][COL]);


#endif
