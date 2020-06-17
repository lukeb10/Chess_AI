#ifndef AI_H
#define AI_H
 
// (a,b) = initial position -> (c,d) the new position
typedef struct {
	int piece;
	int a;
	int b;
	int c;
	int d;
	int value;
} MOVE;

// Find and make best move for AI
MOVE AIMove(int board[8][8], int AIColor, int turn);

// normal search of board for best move 
MOVE Search(int board[8][8], int depth, int color);

// scan for total value of pieces on board (your pieces value - opponent's pieces values)
int getMaterial(int board[8][8], int color);

// scan for good/bad piece placement
int getMobility(int board[8][8], int color);

// get possible moves
int getMoves(int board[8][8], int color, MOVE moves[100]);

// move utility function
void makeMove(int board[8][8], MOVE move, char charcolor, int test);

// used to test future moves
void resetTestBoard(int board[8][8], int testBoard[8][8]);

// switch color value utility
char switchColor(char color);

// is color in check?
int getCheck(int board[8][8], int color);

// reset moves array
void resetMoves(MOVE moves[100]);

#endif