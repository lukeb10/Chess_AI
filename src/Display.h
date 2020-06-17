/* Display.h: header file for the board display */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Definitions.h"
//#include "Functions.h"
#include "AI.h"

typedef struct {

    char pawn[3] ;   // "wP" or "bP"
    char rook[3] ;   // "wR" or "bR"
    char knight[3] ; // "wN" or "bN"
    char bishop[3] ; // "wB" or "bB"
    char queen[3] ;  // "wQ" or "bQ"
    char king[3] ;   // "wK" or "bK"

} PIECE ;

// converts letter and number to a position
int pos(char p[3]) ;

// converts a position to letter and number
const char *inv(int a, int b) ;

// function that takes in int board[8][8] as a parameter
// and then prints the display according to each piece type and position
void printBoard(int board[8][8]) ;

// function that creates the string representation of pieces for the display
PIECE createPiece(int team) ;

// function that creates the file pointer to the log text file
// and opens the file in write mode
FILE *createLogFile(const char filename[]) ;

// function that writes illegal move to the log file
// and which team wins the game
void IllegalMove(FILE *text, char team) ;

// function that gets the type of piece, type of move, initial and final positions
// and writes it to the output text file
void LogFile(FILE *text, int board[8][8], char init[3], char fin[3], int flag) ;
/* this function must be called BEFORE the Move() function is called */

// function that writes the AI move to the output text file
void LogFileAI(FILE *text, const MOVE move, int flag) ;
/* this function must be called AFTER the AIMove() function is called */

#endif
