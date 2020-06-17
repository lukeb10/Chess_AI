#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Display.h"
#include "Functions.h"

int pos(char p[3]) {

	if (strcmp(p, "a8") == 0) return 0;
	else if (strcmp(p, "b8") == 0) return 1;
	else if (strcmp(p, "c8") == 0) return 2;
	else if (strcmp(p, "d8") == 0) return 3;
	else if (strcmp(p, "e8") == 0) return 4;
	else if (strcmp(p, "f8") == 0) return 5;
	else if (strcmp(p, "g8") == 0) return 6;
	else if (strcmp(p, "h8") == 0) return 7;
	
	else if (strcmp(p, "a7") == 0) return 10;
	else if (strcmp(p, "b7") == 0) return 11;
	else if (strcmp(p, "c7") == 0) return 12;
	else if (strcmp(p, "d7") == 0) return 13;
	else if (strcmp(p, "e7") == 0) return 14;
	else if (strcmp(p, "f7") == 0) return 15;
	else if (strcmp(p, "g7") == 0) return 16;
	else if (strcmp(p, "h7") == 0) return 17;

	else if (strcmp(p, "a6") == 0) return 20;
	else if (strcmp(p, "b6") == 0) return 21;
	else if (strcmp(p, "c6") == 0) return 22;
	else if (strcmp(p, "d6") == 0) return 23;
	else if (strcmp(p, "e6") == 0) return 24;
	else if (strcmp(p, "f6") == 0) return 25;
	else if (strcmp(p, "g6") == 0) return 26;
	else if (strcmp(p, "h6") == 0) return 27;

	else if (strcmp(p, "a5") == 0) return 30;
	else if (strcmp(p, "b5") == 0) return 31;
	else if (strcmp(p, "c5") == 0) return 32;
	else if (strcmp(p, "d5") == 0) return 33;
	else if (strcmp(p, "e5") == 0) return 34;
	else if (strcmp(p, "f5") == 0) return 35;
	else if (strcmp(p, "g5") == 0) return 36;
	else if (strcmp(p, "h5") == 0) return 37;

	else if (strcmp(p, "a4") == 0) return 40;
	else if (strcmp(p, "b4") == 0) return 41;
	else if (strcmp(p, "c4") == 0) return 42;
	else if (strcmp(p, "d4") == 0) return 43;
	else if (strcmp(p, "e4") == 0) return 44;
	else if (strcmp(p, "f4") == 0) return 45;
	else if (strcmp(p, "g4") == 0) return 46;
	else if (strcmp(p, "h4") == 0) return 47;

	else if (strcmp(p, "a3") == 0) return 50;
	else if (strcmp(p, "b3") == 0) return 51;
	else if (strcmp(p, "c3") == 0) return 52;
	else if (strcmp(p, "d3") == 0) return 53;
	else if (strcmp(p, "e3") == 0) return 54;
	else if (strcmp(p, "f3") == 0) return 55;
	else if (strcmp(p, "g3") == 0) return 56;
	else if (strcmp(p, "h3") == 0) return 57;

	else if (strcmp(p, "a2") == 0) return 60;
	else if (strcmp(p, "b2") == 0) return 61;
	else if (strcmp(p, "c2") == 0) return 62;
	else if (strcmp(p, "d2") == 0) return 63;
	else if (strcmp(p, "e2") == 0) return 64;
	else if (strcmp(p, "f2") == 0) return 65;
	else if (strcmp(p, "g2") == 0) return 66;
	else if (strcmp(p, "h2") == 0) return 67;

	else if (strcmp(p, "a1") == 0) return 70;
	else if (strcmp(p, "b1") == 0) return 71;
	else if (strcmp(p, "c1") == 0) return 72;
	else if (strcmp(p, "d1") == 0) return 73;
	else if (strcmp(p, "e1") == 0) return 74;
	else if (strcmp(p, "f1") == 0) return 75;
	else if (strcmp(p, "g1") == 0) return 76;
	else if (strcmp(p, "h1") == 0) return 77;

	else return 100;
}

const char *inv(int a, int b) {

    static char pos[3] ;
    char letter ;
    char number ;

    pos[0] = '\0' ;

    switch(a) {
        case 0 :
            number = '8' ;    
            break ;
        case 1 :
            number = '7' ;           
            break ;
        case 2 :
            number = '6' ;
            break ;
        case 3 :
            number = '5' ;
            break ;
        case 4 :
            number = '4' ;
            break ;
        case 5 :
            number = '3' ;
            break ;
        case 6 :
            number = '2' ;
            break ;
        case 7 :
            number = '1' ;
            break ;
        default :
            break ;
    }

    switch(b) {
        case 0 :
            letter = 'a' ;
            break ;
        case 1 :
            letter = 'b' ;
            break ;
        case 2 :
            letter = 'c' ;
            break ;
        case 3 :
            letter = 'd' ;
            break ;
        case 4 :
            letter = 'e' ;
            break ;
        case 5 :
            letter = 'f' ;
            break ;
        case 6 :
            letter = 'g' ;
            break ;
        case 7 :
            letter = 'h' ;
            break ;
        default :
            break ;
    }

    strncat(pos, &letter, 1) ;
    strncat(pos, &number, 1) ;

    return pos ;
}

PIECE createPiece(int team) {

    PIECE black ;
    PIECE white ;
    PIECE temp ;

    /* create piece string names */
    if (team == 1) {
        strcpy(black.pawn, "bP") ;
        strcpy(black.rook, "bR") ;
        strcpy(black.knight, "bN") ;
        strcpy(black.bishop, "bB") ;
        strcpy(black.queen, "bQ") ;
        strcpy(black.king, "bK") ;

        temp = black ;
    } else if (team == 0) {
        strcpy(white.pawn, "wP") ;
        strcpy(white.rook, "wR") ;
        strcpy(white.knight, "wN") ;
        strcpy(white.bishop, "wB") ;
        strcpy(white.queen, "wQ") ;
        strcpy(white.king, "wK") ;
        
        temp = white ;
    } 
    return temp ;
}


void printBoard(int board[8][8]) {

    char line[44] = "  +----+----+----+----+----+----+----+----+" ;
    char row[44] = "    a    b    c    d    e    f    g    h   " ;
    char empty[3] = "  " ;

    int x, y ; // x -> row | y -> column | (0,0) -> top left | (7,7) bottom right
    int team ; // white = 0 | black = 1
    int counter = 8 ; // tracks which row is being printed

    /* create white pieces */
    team = 0 ;
    PIECE white = createPiece(team) ;
    /* create black pieces */
    team = 1 ;
    PIECE black = createPiece(team) ;

    printf("\n%s\n", line) ;

    for (x = 0; x < 8; x++) {
        printf("%d | ", counter) ; // counter--
        counter-- ;

        for (y = 0; y < 8; y++) {
            switch(board[x][y]) {
                case -8 :
                    printf("%s", white.king) ;
                    break ;
                case -6 :
                    printf("%s", white.king) ;
                    break ;
                case -5 :
                    printf("%s", white.queen) ;
                    break ;
                case -4 :
                    printf("%s", white.bishop) ;
                    break ;
                case -3 :
                    printf("%s", white.knight) ;
                    break ;
                case -2 :
                    printf("%s", white.rook) ;
                    break ;
                case -7 :
                    printf("%s", white.rook) ;
                    break ;
                case -17 :
                    printf("%s", white.rook) ;
                    break ;
                case -1 :
                    printf("%s", white.pawn) ;
                    break ;
                case -10 :
                    printf("%s", white.pawn) ;
                    break ;
                case 0 :
                    printf("%s", empty) ;
                    break ;
                case 8 :
                    printf("%s", black.king) ;
                    break ;
                case 6 :
                    printf("%s", black.king) ;
                    break ;
                case 5 :
                    printf("%s", black.queen) ;
                    break ;
                case 4 :
                    printf("%s", black.bishop) ;
                    break ;
                case 3 :
                    printf("%s", black.knight) ;
                    break ;
                case 2 :
                    printf("%s", black.rook) ;
                    break ;
                case 7 :
                    printf("%s", black.rook) ;
                    break ;
                case 17 :
                    printf("%s", black.rook) ;
                    break ;
                case 10 :
                    printf("%s", black.pawn) ;
                    break ;
                case 1 :
                    printf("%s", black.pawn) ;
                    break ;
                default :
                    break ;
            }
            printf(" | ") ;
        }

        printf("\n%s\n", line) ;
    }

    printf("%s\n", row) ;

}

FILE *createLogFile(const char filename[]) {

    // create full file path
    char filepath[20] = "./bin/" ; // where do we output the text file???
    strcat(filepath, filename) ;
    strcat(filepath, ".txt") ;
   
    FILE *LogFile = fopen(filepath, "w") ;

    if (LogFile == NULL) {
        filepath[0] = '\0' ;
        strcpy(filepath, "./") ;
        strcat(filepath, filename) ;
        strcat(filepath, ".txt") ;
        LogFile = NULL ;
        LogFile = fopen(filepath, "w") ;
        return LogFile ;
    }

    // exception handling
    if (LogFile == NULL) {
        printf("Log File cannot be created.\n") ;
        printf("Either change current working directory to the Team 18 directory\n") ;
        printf("Or change output directory in createLogFile function.\n") ;
        exit(1) ;
    }

    return LogFile ;

}

void IllegalMove(FILE *text, char team) {

    if (team == 'w') {

        fprintf(text, "Illegal move!\n\n") ;
        fprintf(text, "Black Team Wins!\n\n") ; 

    } else if (team == 'b') {

        fprintf(text, "Illegal move!\n\n") ;
        fprintf(text, "White Team Wins!\n\n") ; 

    }

}

// flag: default = 0 | check = 1 | checkmate = 2 | stalemate = 3
void LogFile(FILE *text, int board[8][8], char init[3], char fin[3], int flag) {

    int team ;
    /* create white pieces */
    team = 0 ;
    PIECE white = createPiece(team) ;
    /* create black pieces */
    team = 1 ;
    PIECE black = createPiece(team) ;
    char cap[3] ; // captured piece

    // get coordinates for initial position
    int a = pos(init) / 10 ;
    int b = pos(init) % 10 ;
    // get coordinates for final position
    int c = pos(fin) / 10 ;
    int d = pos(fin) % 10 ;

    // for captures
    if ((board[a][b] == 1 && (board[a][b - 1] == -10 || board[a][b + 1] == -10) && board[c][d] == 0) || 
        (board[a][b] == -1 && (board[a][b - 1] == 10 || board[a][b + 1] == 10) && board[c][d] == 0)) { // en passant
        if (board[a][b] < 0) { // white pawn moving | black piece captured
            strcpy(cap, black.pawn) ;
        } else if (board[a][b] > 0) { // black pawn moving | white piece captured
            strcpy(cap, white.pawn) ;
        }
    } else if (board[c][d] < 0) { // white pawn captured
        switch(board[c][d]) {
            case -10 :
                strcpy(cap, white.pawn) ;
                break ;
            case -1 :
                strcpy(cap, white.pawn) ;
                break ;
            case -2 :
                strcpy(cap, white.rook) ;
                break ;
            case -3 :
                strcpy(cap, white.knight) ;
                break ;
            case -4 :
                strcpy(cap, white.bishop) ;
                break ;
            case -5 :
                strcpy(cap, white.queen) ;
                break ;
            case -6 :
                strcpy(cap, white.king) ;
                break ;
            case -7 :
                strcpy(cap, white.rook) ;
                break ;
            case -8 :
                strcpy(cap, white.king) ;
                break ;
            case -17 :
                strcpy(cap, white.rook) ;
                break ;
            default :
                break ;
        }
    } else if (board[c][d] > 0) { // black pawn captured
        switch(board[c][d]) {
            case 10 :
                strcpy(cap, black.pawn) ;
                break ;
            case 1 :
                strcpy(cap, black.pawn) ;
                break ;
            case 2 :
                strcpy(cap, black.rook) ;
                break ;
            case 3 :
                strcpy(cap, black.knight) ;
                break ;
            case 4 :
                strcpy(cap, black.bishop) ;
                break ;
            case 5 :
                strcpy(cap, black.queen) ;
                break ;
            case 6 :
                strcpy(cap, black.king) ;
                break ;
            case 7 :
                strcpy(cap, black.rook) ;
                break ;
            case 8 :
                strcpy(cap, black.king) ;
                break ;
            case 17 :
                strcpy(cap, black.rook) ;
                break ;
            default :
                break ;
        }
    }

    // print which piece is moving
    if (board[a][b] < 0) { // white piece
        switch(board[a][b]) {
            case -10 :
                fprintf(text, "%s ", white.pawn) ;
                break ;
            case -1 :
                fprintf(text, "%s ", white.pawn) ;
                break ;
            case -2 :
                fprintf(text, "%s ", white.rook) ;
                break ;
            case -3 :
                fprintf(text, "%s ", white.knight) ;
                break ;
            case -4 :
                fprintf(text, "%s ", white.bishop) ;
                break ;
            case -5 :
                fprintf(text, "%s ", white.queen) ;
                break ;
            case -6 :
                fprintf(text, "%s ", white.king) ;
                break ;
            case -7 :
                fprintf(text, "%s ", white.rook) ;
                break ;
            case -8 :
                fprintf(text, "%s ", white.king) ;
                break ;
            case -17 :
                fprintf(text, "%s ", white.rook) ;
                break ;
            default :
                break ;
        }
    } else if (board[a][b] > 0) { // black piece
        switch(board[a][b]) {
            case 10 :
                fprintf(text, "%s ", black.pawn) ;
                break ;
            case 1 :
                fprintf(text, "%s ", black.pawn) ;
                break ;
            case 2 :
                fprintf(text, "%s ", black.rook) ;
                break ;
            case 3 :
                fprintf(text, "%s ", black.knight) ;
                break ;
            case 4 :
                fprintf(text, "%s ", black.bishop) ;
                break ;
            case 5 :
                fprintf(text, "%s ", black.queen) ;
                break ;
            case 6 :
                fprintf(text, "%s ", black.king) ;
                break ;
            case 7 :
                fprintf(text, "%s ", black.rook) ;
                break ;
            case 8 :
                fprintf(text, "%s ", black.king) ;
                break ;
            case 17 :
                fprintf(text, "%s ", black.rook) ;
                break ;
            default :
                break ;
        }
    }

    // print the action of the piece
    if ((board[a][b] == 1 && (board[a][b - 1] == -10 || board[a][b + 1] == -10) && board[c][d] == 0) || 
        (board[a][b] == -1 && (board[a][b - 1] == 10 || board[a][b + 1] == 10) && board[c][d] == 0)) { // en passant
        fprintf(text, "captures %s and moves en passant from %s to %s", cap, init, fin) ;
    } else if ((board[a][b] == 8 && (board[c][d] == 7 || board[c][d] == 17)) || 
               (board[c][d] == 8 && (board[a][b] == 7 || board[a][b] == 17)) || 
               (board[a][b] == -8 && (board[c][d] == -7 || board[c][d] == -17)) ||
               (board[c][d] == -8 && (board[a][b] == -7 || board[a][b] == -17))) { // castling
        if (board[a][b] < 0) { // white castling
            if ((strcmp(init, "a1") && strcmp(fin, "e1")) == 0) {
                fprintf(text, "castles from %s to d1, %s castles from %s to c1", init, white.king, fin) ;
            } else if ((strcmp(init, "e1") && strcmp(fin, "a1")) == 0) {
                fprintf(text, "castles from %s to c1, %s castles from %s to d1", init, white.rook, fin) ;
            } else if ((strcmp(init, "h1") && strcmp(fin, "e1")) == 0) {
                fprintf(text, "castles from %s to f1, %s castles from %s to g1", init, white.king, fin) ;
            } else if ((strcmp(init, "e1") && strcmp(fin, "g1")) == 0) {
                fprintf(text, "castles from %s to g1, %s castles from %s to f1", init, white.rook, fin) ;
            }
        } else if (board[a][b] > 0) { // black castling
            if ((strcmp(init, "a8") && strcmp(fin, "e8")) == 0) {
                fprintf(text, "castles from %s to d8, %s castles from %s to c8", init, black.king, fin) ;
            } else if ((strcmp(init, "e8") && strcmp(fin, "a8")) == 0) {
                fprintf(text, "castles from %s to c8, %s castles from %s to d8", init, black.rook, fin) ;
            } else if ((strcmp(init, "h8") && strcmp(fin, "e8")) == 0) {
                fprintf(text, "castles from %s to f8, %s castles from %s to g8", init, black.king, fin) ;
            } else if ((strcmp(init, "e8") && strcmp(fin, "g8")) == 0) {
                fprintf(text, "castles from %s to g8, %s castles from %s to f8", init, black.rook, fin) ;
            }
        }
    } else if (flag == 1) { // check
        if (board[c][d] != 0) {
            fprintf(text, "captures %s from %s to %s, ", cap, init, fin) ;
            if (board[a][b] < 0) { // black king in check
                fprintf(text, "%s in check", black.king) ;
            } else if (board[a][b] > 0) { // white king in check
                fprintf(text, "%s in check", white.king) ;
            }
        } else {
            fprintf(text, "moves from %s to %s, ", init, fin) ;
            if (board[a][b] < 0) { // black king in check
                fprintf(text, "%s in check", black.king) ;
            } else if (board[a][b] > 0) { // white king in check
                fprintf(text, "%s in check", white.king) ;
            }
        }
    } else if (flag == 2) { // checkmate
        if (board[c][d] != 0) {
            fprintf(text, "captures %s from %s to %s, ", cap, init, fin) ;
            if (board[a][b] < 0) { // white wins
                fprintf(text, "%s in checkmate\n\n", black.king) ;
                fprintf(text, "WHITE WINS THE GAME!") ;
            } else if (board[a][b] > 0) { // black wins
                fprintf(text, "%s in checkmate\n\n", white.king) ;
                fprintf(text, "BLACK WINS THE GAME!") ;
            }
        } else {
            fprintf(text, "moves from %s to %s, ", init, fin) ;
            if (board[a][b] < 0) { // white wins
                fprintf(text, "%s in checkmate\n\n", black.king) ;
                fprintf(text, "WHITE WINS THE GAME!") ;
            } else if (board[a][b] > 0) { // black wins
                fprintf(text, "%s in checkmate\n\n", white.king) ;
                fprintf(text, "BLACK WINS THE GAME!") ;
            }
        }
    } else if (flag == 3) { // stalemate
        if (board[c][d] != 0) {
            fprintf(text, "captures %s from %s to %s, ", cap, init, fin) ;
            fprintf(text, "game is in stalemate\n\n") ;
            fprintf(text, "TIE GAME!") ;
        } else {
            fprintf(text, "moves from %s to %s", init, fin) ;
            fprintf(text, "game is in stalemate\n\n") ;
            fprintf(text, "TIE GAME!") ;
        }
    } else if (board[c][d] != 0) { // capture
        fprintf(text, "captures %s from %s to %s", cap, init, fin) ;
    } else { // regular move
        fprintf(text, "moves from %s to %s", init, fin) ;
    }

    fprintf(text, "\n\n") ;
}

void LogFileAI(FILE *text, const MOVE move, int flag) {

    int team ;
    /* create white pieces */
    team = 0 ;
    PIECE white = createPiece(team) ;
    /* create black pieces */
    team = 1 ;
    PIECE black = createPiece(team) ;
    
    char init[3], fin[3] ;
    strcpy(init, inv(move.a, move.b)) ;
    strcpy(fin, inv(move.c, move.d)) ;

    // print which piece is moving
    if (move.piece < 0) { // white piece
        switch(move.piece) {
            case -10 :
                fprintf(text, "%s ", white.pawn) ;
                break ;
            case -1 :
                fprintf(text, "%s ", white.pawn) ;
                break ;
            case -2 :
                fprintf(text, "%s ", white.rook) ;
                break ;
            case -3 :
                fprintf(text, "%s ", white.knight) ;
                break ;
            case -4 :
                fprintf(text, "%s ", white.bishop) ;
                break ;
            case -5 :
                fprintf(text, "%s ", white.queen) ;
                break ;
            case -6 :
                fprintf(text, "%s ", white.king) ;
                break ;
            case -7 :
                fprintf(text, "%s ", white.rook) ;
                break ;
            case -8 :
                fprintf(text, "%s ", white.king) ;
                break ;
            case -17 :
                fprintf(text, "%s ", white.rook) ;
                break ;
            default :
                break ;
        }
    } else if (move.piece > 0) { // black piece
        switch(move.piece) {
            case 10 :
                fprintf(text, "%s ", black.pawn) ;
                break ;
            case 1 :
                fprintf(text, "%s ", black.pawn) ;
                break ;
            case 2 :
                fprintf(text, "%s ", black.rook) ;
                break ;
            case 3 :
                fprintf(text, "%s ", black.knight) ;
                break ;
            case 4 :
                fprintf(text, "%s ", black.bishop) ;
                break ;
            case 5 :
                fprintf(text, "%s ", black.queen) ;
                break ;
            case 6 :
                fprintf(text, "%s ", black.king) ;
                break ;
            case 7 :
                fprintf(text, "%s ", black.rook) ;
                break ;
            case 8 :
                fprintf(text, "%s ", black.king) ;
                break ;
            case 17 :
                fprintf(text, "%s ", black.rook) ;
                break ;
            default :
                break ;
        }
    }

    fprintf(text, "moves from %s to %s", init, fin) ;

    if (flag == 1) { // check
        if (move.piece < 0) {
            fprintf(text, ", %s in check", black.king) ;
        } else if (move.piece > 0) {
            fprintf(text, ", %s in check", white.king) ;
        }
    } else if (flag == 2) { // checkmate
        if (move.piece < 0) {
            fprintf(text, ", %s in checkmate\n\n", black.king) ;
            fprintf(text, "WHITE WINS THE GAME!") ;
        } else if (move.piece > 0) {
            fprintf(text, ", %s in checkmate\n\n", white.king) ;
            fprintf(text, "BLACK WINS THE GAME!") ;
        }
    } else if (flag == 3) { // stalemate
        fprintf(text, ", game is in stalemate\n\n") ;
        fprintf(text, "TIE GAME!") ;
    }

    fprintf(text, "\n\n") ;

}
