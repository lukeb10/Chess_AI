#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//new header file
//need enums refering to the pieces
//need struct for pieces
//declare the functions
//FILE *text = NULL;

void setBoard(int board[8][8]);
/*
capture( *tbd* );

checkFirstMove( *tbd* );

getPiece(*tbd*);

promotion( *tbd* );

castle( *tbd* );

getCheck( *tbd* );
*/

int getCheckMate(int board[8][8], char team);

// helper functions for checkmate
int checkPos(int board[8][8], char team, int x, int y);
int kingCapture(int board[8][8], char team, int x, int y);
int anotherCase(int board[8][8], char team, int i, int j);
int anotherCaseHelper(int board[8][8], char team, int x, int y);
 
void Move(int board[8][8], int x, int y, char team, int test);

void PawnMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test);

void RookMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test);

void KingMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test);

void BishopMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test);

void KnightMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test);

void Castling(int board[8][8], int piece, int a, int b, int c, int d, char team, int test);

void Promotion(int board[8][8], int piece, int a, int b, int c, int d);

void EnPassant(int board[8][8], int piece, int a, int b, int c, int d);

int BlackCheck(int board[8][8]);

int WhiteCheck(int board[8][8]);


#endif

