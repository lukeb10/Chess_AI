#include "Functions.h"
#include "AI.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int white_pawn_positions[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{-1, 4, 0, 0, 0, 0, 4, -1},
	{0, 0, 0, -2, -2, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int black_pawn_positions[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, -2, -2, 0, 0, 0},
	{-1, 4, 0, 0, 0, 0, 4, -1},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int black_knight_positions[8][8] = {
	{-5, -3, -3, -3, -3, -3, -3, -5},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-3, 0, 2, 0, 0, 2, 0, -1},
	{-1, 0, 0, 1, 1, 0, 0, -1},
	{-1, 0, 1, 1, 1, 1, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-3, 0, 0, 0, 0, 0, 0, -3},
	{-1, 0, 0, 0, 0, 0, 0, -1}
};

int white_knight_positions[8][8] = {
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-3, 0, 0, 0, 0, 0, 0, -3},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 1, 1, 1, 1, 0, -1},
	{-1, 0, 0, 1, 1, 0, 0, -1},
	{-1, 0, 2, 0, 0, 2, 0, -1},
	{-1, 0, 0, -15, 0, 0, 0, -1},
	{-5, -3, -3, -3, -3, -3, -3, -5}
};

int black_bishop_positions[8][8] = {
	{-2, -2, -2, -2, -2, -2, -2, -2},
	{0, 2, 0, 0, 0, 0, 2, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int white_bishop_positions[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 2, 0, 0, 0, 0, 2, 0},
	{-2, -2, -2, -2, -2, -2, -2, -2}
};

int black_rook_positions[8][8] = {
	{0, 2, 2, 2, 2, 2, 2, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int white_rook_positions[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 2, 2, 2, 2, 2, 2, 0}
};

int black_queen_positions[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int white_queen_positions[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{-15, 0, 0, 0, 0, 0, 0, -15},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int black_king_positions[8][8] = {
	{0, 1, 1, 0, 0, 0, 2, 0},
	{-2, -2, -2, -2, -2, -2, -2, -2},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

int white_king_positions[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{-2, -2, -2, -2, -5, -2, -2, -2},
	{0, 1, 1, 0, 0, 0, 2, 0}
};


// for printing ai move
char print_board[8][8][3] = {
	{"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"},
	{"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"},
	{"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"},
	{"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"},
	{"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"},
	{"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"},
	{"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"},
	{"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"}
};


MOVE AIMove (int board[8][8], int AIcolor, int turn) {

	MOVE move = Search(board, 1, AIcolor);

	char charcolor;

	if (AIcolor) {
		charcolor = 'b';
	}
	else {
		charcolor = 'w';
	}

	// make predefined moves during opening
	if (turn < 3) {
		// if white, go for 4 move checkmate
		if (!AIcolor) {
			switch(turn) {
				case 1: 
					PawnMove(board, -1, 6, 3, 4, 3, 'w', 1);
					return move;
				case 2:
					KnightMove(board, -3, 7, 6, 5, 5, 'w', 1);
					return move;
			}
		} 
		else {
			// if black, play sicilian opening
			switch(turn) {
				case 1: 
					PawnMove(board, 1, 1, 2, 3, 2, 'b', 1);
					return move;
				case 2:
					PawnMove(board, 1, 1, 3, 2, 3, 'b', 1);
					return move;
			}
		}
	}

	printf("AI move is: %s -> %s\n", print_board[move.a][move.b], print_board[move.c][move.d]);

	makeMove(board, move, charcolor, 1);

	return move;
	
}

void makeMove(int board[8][8], MOVE move, char charcolor, int test) {
	// call move function based on piece type
	switch(abs(move.piece)) {
		case 1: // Pawn
			PawnMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
			return;
		case 10: // Pawn
			PawnMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
			return;
		case 2: // Rook
			RookMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
			return;
		case 7: // Rook
			RookMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
			return;
		case 17: // Rook
			RookMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
			return;
		case 3: // Knight
			KnightMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
			return;
		case 4: // Bishop
			BishopMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
			return;
		case 5: // Queen
			if (move.b == move.d || move.a == move.c) {
				RookMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
				return;
			}
			else {
				BishopMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
				return;
			}
		case 6: //King
			KingMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
			return;
		case 8: //King
			KingMove(board, move.piece, move.a, move.b, move.c, move.d, charcolor, test);
			return;
	}
}




// return struct of best move info
MOVE Search(int board[8][8], int depth, int color) {

	char color_ai, color_op;
	int op_color;
	if (color) {
		color_ai = 'b';
		color_op = 'w';
		op_color = 0;
	}
	else {
		color_ai = 'w';
		color_op = 'b';
		op_color = 1;
	}

	int moves_calc = 0;

	int i, j, k, m, n, o;

	MOVE moves[100];
	int board_d0[8][8], board_d1[8][8], board_d2[8][8];
	int move_count_d1, move_count_d2, move_count_d3;

	// get all valid moves
	int numMoves = getMoves(board, color, moves);

	moves_calc += numMoves;

	if (numMoves == 0) {
		printf("AI RESIGNS\n");
		MOVE resign = {0, 0, 0, 0, 0, 0};
		return resign;
	}

	/* if in check
	if ((color && getCheck(board, 1)) || (op_color && getCheck(board, 0))) {
		printf("Possible Moves\n");
		// find highest value move
		for (i = 0; i < numMoves; i++) {
			printf("( %d , %d ) -> ( %d , %d )\n", moves[i].a, moves[i].b, moves[i].c, moves[i].d);
			if (moves[i].value > bestmove.value) {
				bestmove = moves[i];
			}
		}
		return bestmove;
	}*/

	MOVE bestmove_d1, bestmove_d2, bestmove_d3;

	// depth 1 moves
	MOVE moves_d1[100];

	// depth 2 moves
	MOVE moves_d2[100];

	// depth 3 moves
	MOVE moves_d3[100];

	//printf("Number of moves found: %d\n", numMoves);

	// search for best move with depth of 4

	for (i = 0; i < numMoves; i++) {
		move_count_d1 = 0;
		resetMoves(moves_d1);
		resetTestBoard(board, board_d0);
		makeMove(board_d0, moves[i], color_ai, 0);

		// find opponent moves and store in d1
		move_count_d1 = getMoves(board_d0, op_color, moves_d1);

		moves_calc += move_count_d1;
		
		/* find ai moves for each move opponent can make in d1
		for (j = 0; j < move_count_d1; j++) {
			move_count_d2 = 0;
			resetMoves(moves_d2);
			resetTestBoard(board_d0, board_d1);
			makeMove(board_d1, moves_d1[j], color_op, 0);

			// get ai moves to opponent's response and store in d2
			move_count_d2 = getMoves(board_d1, color, moves_d2);

			moves_calc += move_count_d2;
			
			// find opponent moves for each ai move in d2
			for (n = 0; n < move_count_d2; n++) {
				move_count_d3 = 0;
				resetMoves(moves_d3);
				resetTestBoard(board_d1, board_d2);
				makeMove(board_d2, moves_d2[n], color_ai, 0);

				move_count_d3 = getMoves(board_d2, op_color, moves_d3);

				moves_calc += move_count_d3;

				// for each move in d3, find the highest value move
				bestmove_d3 = moves_d3[0];
				for (o = 0; o < move_count_d3; o++) {
					if (moves_d3[o].value > bestmove_d3.value) {
						bestmove_d3 = moves_d3[o];
					}
				}

				// subtract the best opponent move from ai best move in d2
				moves_d2[n].value += (-1 * bestmove_d3.value);
			}

			bestmove_d2 = moves_d2[0];
			for (k = 0; k < move_count_d2; k++) {
				if (moves_d2[k].value > bestmove_d2.value) {
					bestmove_d2 = moves_d2[k];
				}
			}

			moves_d1[j].value += bestmove_d2.value;
		}*/
		

		// find best opponent move after first ai move
		bestmove_d1 = moves_d1[0];
		for (m = 1; m < move_count_d1; m++) {
			if (moves_d1[m].value > bestmove_d1.value) {
				bestmove_d1 = moves_d1[m];
			}
		}

		moves[i].value += (-1 * bestmove_d1.value);

	}
	
	//printf("Total moves calculated: %d\n", moves_calc);

	// set the current best move to the first one of array
	MOVE bestmove = moves[0];

	// find highest value move
	for (i = 0; i < numMoves; i++) {
		//printf("( %d , %d ) -> ( %d , %d ) | Value: %d\n", moves[i].a, moves[i].b, moves[i].c, moves[i].d, moves[i].value);
		if (moves[i].value > bestmove.value) {
			bestmove = moves[i];
		}
	}

	//printf("best value: %d\n", bestmove.value);
	return bestmove;
}


int getMaterial(int board[8][8], int color) {
	int i, j;
	int material_white = 0;
	int material_black = 0;

	if (getCheck(board, 1)) {
		material_white += 3;
		if (getCheckMate(board, 'b') == 2) {
			material_white += 30;
		}
	}
	if (getCheck(board, 0)) {
		material_black += 3;
		if (getCheckMate(board, 'w') == 2) {
			material_black += 30;
		}
	}

	// loop through each space on board
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
				switch (board[i][j]) {
					case -1:  // pawn
						material_white += 3 + white_pawn_positions[i][j];
						// check for good pawn structure
						if (i < 7 && j < 7 && board[i+1][j+1] == -1) {
							material_white += 1;
						}
						if (i > 0 && j > 0 && board[i+1][j-1] == -1) {
							material_white += 1;
						}
						break;
					case -10:  // pawn
						material_white += 3 + white_pawn_positions[i][j];
						if (i < 7 && j < 7 && board[i+1][j+1] == -1) {
							material_white += 1;
						}
						if (i > 0 && j > 0 && board[i+1][j-1] == -1) {
							material_white += 1;
						}
						break;
					case -2: // rook
						material_white += 15 + white_rook_positions[i][j];
						if (i > 0 && j > 0 && board[i-1][j-1] == 1) {
							material_white -= 2;
						}
						if (i > 0 && j < 7 && board[i-1][j+1] == 1) {
							material_white -= 2;
						}
						break;
					case -7: // rook
						material_white += 15 + white_rook_positions[i][j];
						if (i > 0 && j > 0 && board[i-1][j-1] == 1) {
							material_white -= 2;
						}
						if (i > 0 && j < 7 && board[i-1][j+1] == 1) {
							material_white -= 2;
						}
						break;
					case -17: // rook
						material_white += 15 + white_rook_positions[i][j];
						if (i > 0 && j > 0 && board[i-1][j-1] == 1) {
							material_white -= 2;
						}
						if (i > 0 && j < 7 && board[i-1][j+1] == 1) {
							material_white -= 2;
						}
						break;
					case -3: // knight
						material_white += 9 + white_knight_positions[i][j];

						if (board[6][3] == -3 && board[3][6] == -3) {
							material_white -= 8;
						}

						if (i < 7 && j < 7 && board[i+1][j+1] == -1) {
							material_white += 1;
						}
						if (i < 7 && j > 0 && board[i+1][j-1] == -1) {
							material_white += 1;
						}
						if (i > 0 && j > 0 && board[i-1][j-1] == 1) {
							material_white -= 2;
						}
						if (i > 0 && j < 7 && board[i-1][j+1] == 1) {
							material_white -= 2;
						}
						break;
					case -4: // bishop
						material_white += 10 + white_bishop_positions[i][j];
						if (i > 0 && j > 0 && board[i-1][j-1] == 1) {
							material_white -= 2;
						}
						if (i > 0 && j < 7 && board[i-1][j+1] == 1) {
							material_white -= 2;
						}
						break;
					case -5: // queen
						material_white += 28 + white_queen_positions[i][j];
						if (i > 0 && j > 0 && board[i-1][j-1] == 1) {
							material_white -= 4;
						}
						if (i > 0 && j < 7 && board[i-1][j+1] == 1) {
							material_white -= 4;
						}
						break;

					case 1:  // pawn
						material_black += 3 + black_pawn_positions[i][j];
						if (i > 0 && j < 7 && board[i-1][j+1] == 1) {
							material_black += 1;
						}
						if (i > 0 && j > 0 && board[i-1][j-1] == 1) {
							material_black += 1;
						}
						break;
					case 10:  // pawn
						material_black += 3 + black_pawn_positions[i][j];
						if (i > 0 && j < 7 && board[i-1][j+1] == 1) {
							material_black += 1;
						}
						if (i > 0 && j > 0 && board[i-1][j-1] == 1) {
							material_black += 1;
						}
						break;
					case 2: // rook
						material_black += 15 + black_rook_positions[i][j];
						if (i < 7 && j < 7 && board[i+1][j+1] == -1) {
							material_black -= 2;
						}
						if (i < 7 && j > 0 && board[i+1][j-1] == -1) {
							material_black -= 2;
						}
						break;
					case 7: // rook
						material_black += 15 + black_rook_positions[i][j];
						if (i < 7 && j < 7 && board[i+1][j+1] == -1) {
							material_black -= 2;
						}
						if (i < 7 && j > 0 && board[i+1][j-1] == -1) {
							material_black -= 2;
						}
						break;
					case 17: // rook
						material_black += 15 + black_rook_positions[i][j];
						if (i < 7 && j < 7 && board[i+1][j+1] == -1) {
							material_black -= 2;
						}
						if (i < 7 && j > 0 && board[i+1][j-1] == -1) {
							material_black -= 2;
						}
						break;
					case 3: // knight
						material_black += 9 + black_knight_positions[i][j];
						if (i > 0 && j < 7 && board[i-1][j+1] == 1) {
							material_black += 1;
						}
						if (i > 0 && j > 0 && board[i-1][j-1] == 1) {
							material_black += 1;
						}
						if (i < 7 && j < 7 && board[i+1][j+1] == -1) {
							material_black -= 2;
						}
						if (i < 7 && j > 0 && board[i+1][j-1] == -1) {
							material_black -= 2;
						}
						break;
					case 4: // bishop
						material_black += 10 + black_bishop_positions[i][j];
						if (i < 7 && j < 7 && board[i+1][j+1] == -1) {
							material_black -= 2;
						}
						if (i < 7 && j > 0 && board[i+1][j-1] == -1) {
							material_black -= 2;
						}
						break;
					case 5: // queen
						material_black += 28 + black_queen_positions[i][j];
						if (i < 7 && j < 7 && board[i+1][j+1] == -1) {
							material_black -= 2;
						}
						if (i < 7 && j > 0 && board[i+1][j-1] == -1) {
							material_black -= 2;
						}
				}
		}
	}

	// if black, return black material - white material and vice-versa
	if (color) {
		return (material_black - material_white);
	}
	else {
		return (material_white - material_black);
	}
}

void resetMoves(MOVE moves[100]) {
	int i;
	for (i = 0; i < 100; i++) {
		moves[i].value = 0;
		moves[i].a = 0;
		moves[i].b = 0;
		moves[i].c = 0;
		moves[i].d = 0;
		moves[i].piece = 0;
	}
}

int getMoves(int board[8][8], int color, MOVE moves[100]) {
	int numMoves = 0;
	int testBoard[8][8];
	int i, j, checkNext, inc;

	// set test board equal to game board
	resetTestBoard(board, testBoard);

	// find white move
	if (!color) {
		numMoves = 0;

		// queen side castle
		if (board[7][4] == -8 && board[7][0] == -7) {
			if (board[7][1] == 0 && board[7][2] == 0 && board[7][3] == 0) {
				if (!getCheck(board, 0)) {
					KingMove(testBoard, -8, 7, 4, 7, 3, 'w', 0);
					if (!getCheck(testBoard, 0)) {
						resetTestBoard(board, testBoard);
						KingMove(testBoard, -8, 7, 4, 7, 0, 'w', 0);
						if (!getCheck(testBoard, 0)) {
							moves[numMoves].piece = -8;
							moves[numMoves].a = 7;
							moves[numMoves].b = 4;
							moves[numMoves].c = 7;
							moves[numMoves].d = 0;
							moves[numMoves].value = getMaterial(testBoard, color) + white_king_positions[7][2] + 8;
							resetTestBoard(board, testBoard);
							numMoves++;
						}
					}
				}
			}
		}
		
		// king side castle
		if (board[7][4] == -8 && board[7][7] == -17) {
			if (board[7][5] == 0 && board[7][6] == 0) {
				if (!getCheck(board, 0)) {
					KingMove(testBoard, -8, 7, 4, 7, 5, 'w', 0);
					if (!getCheck(testBoard, 0)) {
						resetTestBoard(board, testBoard);
						KingMove(testBoard, -8, 7, 4, 7, 7, 'w', 0);
						if (!getCheck(testBoard, 0)) {
							moves[numMoves].piece = -8;
							moves[numMoves].a = 7;
							moves[numMoves].b = 4;
							moves[numMoves].c = 7;
							moves[numMoves].d = 7;
							moves[numMoves].value = getMaterial(testBoard, color) + white_king_positions[7][6] + 8;
							resetTestBoard(board, testBoard);
							numMoves++;
						}
					}
				}
			}
		}

		resetTestBoard(board, testBoard);

		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (board[i][j] < 0) {
					switch(board[i][j]) {			
						case -1:
							// move forward
							if (i > 0 && board[i-1][j] == 0) {
								if (i == 1) {
									if (!getCheck(board, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i - 1;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
									}
								}
								else {
									PawnMove(testBoard, -1, i, j, i-1,j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -1;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i - 1;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										resetTestBoard(board, testBoard);
									}
								}
							}
							//capture right
							if (i > 0 && j < 7 && board[i-1][j+1] > 0) {
								if (i == 1) {
									if (!getCheck(board, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i - 1;
										moves[numMoves].d = j + 1;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
									}
								}
								else {
									PawnMove(testBoard, -1, i, j, i-1,j+1, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -1;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i - 1;
										moves[numMoves].d = j + 1;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										resetTestBoard(board, testBoard);
									}
								}
							}
							// capture left
							if (i > 0 && j > 0 && board[i-1][j-1] > 0) {
								if (i == 1) {
									if (!getCheck(board, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i - 1;
										moves[numMoves].d = j - 1;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
									}
								}
								else {
									PawnMove(testBoard, -1, i, j, i-1,j-1, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -1;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i - 1;
										moves[numMoves].d = j - 1;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										resetTestBoard(board, testBoard);
									}
								}
							}
							break;
						case -3:
							// up 2 right 1
							if ((i - 2 >= 0) && (j + 1 < 8) && (board[i-2][j+1] >= 0)) {
								KnightMove(testBoard, -3, i, j, i-2, j+1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-2;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									if (board[i-2][j+1] == 8 || board[i-2][j+1] == 6) {
										moves[numMoves].value += 10;
									}
									resetTestBoard(board, testBoard);
									numMoves++;
								}
							}
							// up 1 right 2
							if ((i - 1 >= 0) && (j + 2 < 8) && (board[i-1][j+2] > -1)) {
								KnightMove(testBoard, -3, i, j, i-1, j+2, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j+2;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}
							// down 1 right 2
							if ((i + 1 < 8) && (j + 2 < 8) && (board[i+1][j+2] > -1)) {
								KnightMove(testBoard, -3, i, j, i+1, j+2, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j+2;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}
							// down 2 right 1
							if ((i + 2 < 8) && (j + 1 < 8) && (board[i+2][j+1] > -1)) {
								KnightMove(testBoard, -3, i, j, i+2, j+1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+2;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}
							// down 2 left 1
							if ((i + 2 < 8) && (j - 1 >= 0) && (board[i+2][j-1] > -1)) {
								KnightMove(testBoard, -3, i, j, i+2, j-1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+2;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}
							// down 1 left 2
							if ((i + 1 < 8) && (j - 2 >= 0) && (board[i+1][j-2] > -1)) {
								KnightMove(testBoard, -3, i, j, i+1, j-2, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j-2;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}								
							}
							// up 1 left 2
							if ((i - 1 >= 0) && (j - 2 >= 0) && (board[i-1][j-2] > -1)) {
								KnightMove(testBoard, -3, i, j, i-1, j-2, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j-2;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}								
							}
							// up 2 left 1
							if ((i - 2 >= 0) && (j - 1 >= 0) && (board[i-2][j-1] > -1)) {
								KnightMove(testBoard, -3, i, j, i-2, j-1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-2;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}								
							}
							break;
						case -4:
							// up left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && (board[i-inc][j-inc] == 0)) {
									BishopMove(testBoard, -4, i, j, i - inc, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && board[i-inc][j-inc] > 0) {
									BishopMove(testBoard, -4, i, j, i - inc, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
									checkNext = 0;
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else {
									checkNext = 0;
								}
							}
							// up right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] == 0)) {
									BishopMove(testBoard, -4, i, j, i - inc, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] > 0)) {
									BishopMove(testBoard, -4, i, j, i - inc, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
										numMoves++;
										
										checkNext = 0;
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else {
									checkNext = 0;
								}
							}
							// down right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] == 0)) {
									BishopMove(testBoard, -4, i, j, i + inc, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] > 0)) {
									BishopMove(testBoard, -4, i, j, i + inc, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down left
							checkNext = 1;
							inc = 1;
							resetTestBoard(board, testBoard);
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] == 0)) {
									BishopMove(testBoard, -4, i, j, i + inc, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] > 0)) {
									BishopMove(testBoard, -4, i, j, i + inc, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
									resetTestBoard(board, testBoard);
								}
									inc++;
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case -5:
							// up left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && (board[i-inc][j-inc] == 0)) {
									BishopMove(testBoard, -5, i, j, i - inc, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
											moves[numMoves].piece = -5;
											moves[numMoves].a = i;
											moves[numMoves].b = j;
											moves[numMoves].c = i-inc;
											moves[numMoves].d = j-inc;
											moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && board[i-inc][j-inc] > 0) {
									BishopMove(testBoard, -5, i, j, i - inc, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
									checkNext = 0;
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else {
									checkNext = 0;
								}
							}
							// up right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] == 0)) {
									BishopMove(testBoard, -5, i, j, i - inc, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] > 0)) {
									BishopMove(testBoard, -5, i, j, i - inc, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									

									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] == 0)) {
									BishopMove(testBoard, -5, i, j, i + inc, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] > 0)) {
									BishopMove(testBoard, -5, i, j, i + inc, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] == 0)) {
									BishopMove(testBoard, -5, i, j, i + inc, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] > 0)) {
									BishopMove(testBoard, -5, i, j, i + inc, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
								
								}
								inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									RookMove(testBoard, -5, i, j, i - inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] > 0)) {
									RookMove(testBoard, -5, i, j, i - inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									RookMove(testBoard, -5, i, j, i + inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] > 0)) {
									RookMove(testBoard, -5, i, j, i + inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									inc++;
								}
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									RookMove(testBoard, -5, i, j, i, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] > 0)) {
									RookMove(testBoard, -5, i, j, i, j - inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									RookMove(testBoard, -5, i, j, i, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									}inc++;

									resetTestBoard(board, testBoard);
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] > 0)) {
									RookMove(testBoard, -5, i, j, i, j + inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case -7: // unmoved rook
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									RookMove(testBoard, -7, i, j, i-inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -7;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] > 0)) {
									RookMove(testBoard, -7, i, j, i-inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -7;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
														
									numMoves++;
									
								}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									RookMove(testBoard, -7, i, j, i, j+inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -7;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
																	
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] > 0)) {
									RookMove(testBoard, -7, i, j, i, j+inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -7;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									inc++;
								}
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case -17:
							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									RookMove(testBoard, -17, i, j, i, j-inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -17;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] > 0)) {
									RookMove(testBoard, -17, i, j, i, j-inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -17;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									inc++;
								}
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									RookMove(testBoard, -17, i, j, i-inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -17;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] > 0)) {
									RookMove(testBoard, -17, i, j, i-inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -17;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									inc++;
								}
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case -2:
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									resetTestBoard(board, testBoard);
									RookMove(testBoard, -2, i, j, i-inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] > 0)) {
									resetTestBoard(board, testBoard);
									RookMove(testBoard, -2, i, j, i-inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
										numMoves++;
										checkNext = 0;
									}
										inc++;
										resetTestBoard(board, testBoard);
								}
								else {
									checkNext = 0;
								}
							}

							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									resetTestBoard(board, testBoard);
									RookMove(testBoard, -2, i, j, i, j-inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
										numMoves++;	
								}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] > 0)) {
									resetTestBoard(board, testBoard);
									RookMove(testBoard, -2, i, j, i, j-inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										checkNext = 0;
									}
									inc++;
									resetTestBoard(board, testBoard);
									
								}
								else {
									checkNext = 0;
								}
							}
							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									resetTestBoard(board, testBoard);
									RookMove(testBoard, -2, i, j, i, j+inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] > 0)) {
									resetTestBoard(board, testBoard);
									RookMove(testBoard, -2, i, j, i, j+inc, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
									
										numMoves++;
										checkNext = 0;
									}
										inc++;
										resetTestBoard(board, testBoard);
								}
								else {
									checkNext = 0;
								}
							}

							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									resetTestBoard(board, testBoard);
									RookMove(testBoard, -2, i, j, i+inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
									
								}
								inc++;
									resetTestBoard(board, testBoard);
								
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] > 0)) {
									RookMove(testBoard, -2, i, j, i+inc, j, 'w', 0);
									if (!getCheck(testBoard, 0)) {
										moves[numMoves].piece = -2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
									
									numMoves++;
								
									
									checkNext = 0;
								}
								inc++;
								resetTestBoard(board, testBoard);
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case -8: // unmoved king
							// up
							if ((i > 0) && (board[i-1][j] > -1)) {
								KingMove(testBoard, -8, i, j, i-1, j, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// up right
							if ((i > 0) && (j < 7) && (board[i-1][j+1] > -1)) {
								KingMove(testBoard, -8, i, j, i-1, j+1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// up left
							if ((i > 0) && (j > 0) && (board[i-1][j-1] > -1)) {
								KingMove(testBoard, -8, i, j, i-1, j-1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down left
							if ((i < 7) && (j > 0) && (board[i+1][j-1] > -1)) {
								KingMove(testBoard, -8, i, j, i+1, j-1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down right
							if ((i < 7) && (j < 7) && (board[i+1][j+1] > -1)) {
								KingMove(testBoard, -8, i, j, i+1, j+1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down 
							if ((i < 7) && (board[i+1][j] > -1)) {
								KingMove(testBoard, -8, i, j, i+1, j, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// right
							if ((j < 7) && (board[i][j+1] > -1)) {
								KingMove(testBoard, -8, i, j, i, j+1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// left
							if ((j > 0) && (board[i][j-1] > -1)) {
								KingMove(testBoard, -8, i, j, i, j-1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}
							break;
						case -6: // king
							// up
							if ((i > 0) && (board[i-1][j] > -1)) {
								KingMove(testBoard, -6, i, j, i-1, j, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// up right
							if ((i > 0) && (j < 7) && (board[i-1][j+1] > -1)) {
								KingMove(testBoard, -6, i, j, i-1, j+1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// up left
							if ((i > 0) && (j > 0) && (board[i-1][j-1] > -1)) {
								KingMove(testBoard, -6, i, j, i-1, j-1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down left
							if ((i < 7) && (j > 0) && (board[i+1][j-1] > -1)) {
								KingMove(testBoard, -6, i, j, i+1, j-1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down right
							if ((i < 7) && (j < 7) && (board[i+1][j+1] > -1)) {
								KingMove(testBoard, -6, i, j, i+1, j+1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down 
							if ((i < 7) && (board[i+1][j] > -1)) {
								KingMove(testBoard, -6, i, j, i+1, j, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// right
							if ((j < 7) && (board[i][j+1] > -1)) {
								KingMove(testBoard, -6, i, j, i, j+1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// left
							if ((j > 0) && (board[i][j-1] > -1)) {
								KingMove(testBoard, -6, i, j, i, j-1, 'w', 0);
								if (!getCheck(testBoard, 0)) {
									moves[numMoves].piece = -6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}
					}
				}
			}
		}
		
	}

	// find moves for black
	else {
		numMoves = 0;

		// queen side castle
		if (board[0][4] == 8 && board[0][0] == 7) {
			if (board[0][1] == 0 && board[0][2] == 0 && board[0][3] == 0) {
				if (!getCheck(board, 1)) {
					KingMove(testBoard, 8, 0, 4, 0, 3, 'b', 0);
					if (!getCheck(testBoard, 1)) {
						resetTestBoard(board, testBoard);
						KingMove(testBoard, 8, 0, 4, 0, 0, 'b', 0);
						if (!getCheck(testBoard, 1)) {
							moves[numMoves].piece = 8;
							moves[numMoves].a = 0;
							moves[numMoves].b = 4;
							moves[numMoves].c = 0;
							moves[numMoves].d = 0;
							moves[numMoves].value = getMaterial(testBoard, color) + black_king_positions[0][2] + 8;
							resetTestBoard(board, testBoard);
							numMoves++;
						}
					}
				}
			}
		}

		// king side castle
		if (board[0][4] == 8 && board[0][7] == 17) {
			if (board[0][5] == 0 && board[0][6] == 0) {
				if (!getCheck(board, 1)) {
					KingMove(testBoard, 8, 0, 4, 0, 5, 'b', 0);
					if (!getCheck(testBoard, 1)) {
						resetTestBoard(board, testBoard);
						KingMove(testBoard, 8, 0, 4, 0, 7, 'b', 0);
						if (!getCheck(testBoard, 1)) {
							moves[numMoves].piece = 8;
							moves[numMoves].a = 0;
							moves[numMoves].b = 4;
							moves[numMoves].c = 0;
							moves[numMoves].d = 7;
							moves[numMoves].value = getMaterial(testBoard, color) + black_king_positions[0][6] + 8;
							resetTestBoard(board, testBoard);
							numMoves++;
						}
					}
				}
			}
		}

		resetTestBoard(board, testBoard);

		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (board[i][j] > 0) {
					switch(board[i][j]) {			
						case 1:
							// move forward
							if (i < 7 && board[i+1][j] == 0) {
								if (i == 6) {
									if (!getCheck(board, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i + 1;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										resetTestBoard(board, testBoard);
									}
								}
								else {
									PawnMove(testBoard, 1, i, j, i+1,j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 1;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i + 1;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										resetTestBoard(board, testBoard);
									}
								}
							}
							//capture left
							if (i < 7 && j < 7 && board[i+1][j+1] < 0) {
								if (i == 6) {
									if (!getCheck(board, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i + 1;
										moves[numMoves].d = j + 1;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										resetTestBoard(board, testBoard);
									}
								}
								else {
									PawnMove(testBoard, 1, i, j, i+1,j+1, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 1;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i + 1;
										moves[numMoves].d = j + 1;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										resetTestBoard(board, testBoard);
									}
								}
							}
							// capture left
							if (i < 7 && j > 0 && board[i+1][j-1] < 0) {
								
								if (i == 6) {
									if (!getCheck(board, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i + 1;
										moves[numMoves].d = j - 1;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										resetTestBoard(board, testBoard);
									}
								}
								else {
									PawnMove(testBoard, 1, i, j, i+1,j-1, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 1;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i + 1;
										moves[numMoves].d = j - 1;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										resetTestBoard(board, testBoard);
									}
								}
							}
							break;
						case 3:
							// up 2 right 1
							if ((i > 1) && (j < 7) && (board[i-2][j+1] < 1)) {
								resetTestBoard(board, testBoard);
								KnightMove(testBoard, 3, i, j, i-2, j+1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-2;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
								}
							}
							// up 1 right 2
							if ((i - 1 >= 0) && (j + 2 < 8) && (board[i-1][j+2] < 1)) {
								resetTestBoard(board, testBoard);
								KnightMove(testBoard, 3, i, j, i-1, j+2, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j+2;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
								}
							}
							// down 1 right 2
							if ((i + 1 < 8) && (j + 2 < 8) && (board[i+1][j+2] < 1)) {
								resetTestBoard(board, testBoard);
								KnightMove(testBoard, 3, i, j, i+1, j+2, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j+2;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
								}
							}
							// down 2 right 1
							if ((i + 2 < 8) && (j + 1 < 8) && (board[i+2][j+1] < 1)) {
								resetTestBoard(board, testBoard);
								KnightMove(testBoard, 3, i, j, i+2, j+1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+2;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
								}
							}
							// down 2 left 1
							if ((i + 2 < 8) && (j - 1 >= 0) && (board[i+2][j-1] < 1)) {
								resetTestBoard(board, testBoard);
								KnightMove(testBoard, 3, i, j, i+2, j-1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+2;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
								}
							}
							// down 1 left 2
							if ((i + 1 < 8) && (j - 2 >= 0) && (board[i+1][j-2] < 1)) {
								resetTestBoard(board, testBoard);
								KnightMove(testBoard, 3, i, j, i+1, j-2, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j-2;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
								}								
							}
							// up 1 left 2
							if ((i - 1 >= 0) && (j - 2 >= 0) && (board[i-1][j-2] < 1)) {
								resetTestBoard(board, testBoard);
								KnightMove(testBoard, 3, i, j, i-1, j-2, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j-2;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
								}								
							}
							// up 2 left 1
							if ((i - 2 >= 0) && (j - 1 >= 0) && (board[i-2][j-1] < 1)) {
								resetTestBoard(board, testBoard);
								KnightMove(testBoard, 3, i, j, i-2, j-1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 3;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-2;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
								}								
							}
							break;
						case 4:
							// up left
							checkNext = 1;
							inc = 1;
							resetTestBoard(board, testBoard);
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && (board[i-inc][j-inc] == 0)) {
									BishopMove(testBoard, 4, i, j, i-inc, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && board[i-inc][j-inc] < 0) {
									BishopMove(testBoard, 4, i, j, i-inc, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
										checkNext = 0;
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else {
									checkNext = 0;
								}
							}
							// up right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] == 0)) {
									BishopMove(testBoard, 4, i, j, i-inc, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] < 0)) {
									BishopMove(testBoard, 4, i, j, i-inc, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] == 0)) {
									BishopMove(testBoard, 4, i, j, i+inc, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] < 0)) {
									BishopMove(testBoard, 4, i, j, i+inc, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] == 0)) {
									BishopMove(testBoard, 4, i, j, i+inc, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] < 0)) {
									BishopMove(testBoard, 4, i, j, i+inc, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 4;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case 5:
							// up left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && (board[i-inc][j-inc] == 0)) {
									BishopMove(testBoard, 5, i, j, i-inc, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && board[i-inc][j-inc] < 0) {
									BishopMove(testBoard, 5, i, j, i-inc, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
										checkNext = 0;
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else {
									checkNext = 0;
								}
							}
							// up right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] == 0)) {
									BishopMove(testBoard, 5, i, j, i-inc, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] < 0)) {
									BishopMove(testBoard, 5, i, j, i-inc, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
									
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] == 0)) {
									BishopMove(testBoard, 5, i, j, i+inc, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (j + inc - 1  < 7) && (board[i+inc][j+inc] < 0)) {
									BishopMove(testBoard, 5, i, j, i+inc, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = -5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] == 0)) {
									BishopMove(testBoard, 5, i, j, i+inc, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] < 0)) {
									BishopMove(testBoard, 5, i, j, i+inc, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									RookMove(testBoard, 5, i, j, i-inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] < 0)) {
									RookMove(testBoard, 5, i, j, i-inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										inc++;
									}
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									RookMove(testBoard, 5, i, j, i+inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] < 0)) {
									RookMove(testBoard, 5, i, j, i+inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									RookMove(testBoard, 5, i, j, i, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
									
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] < 0)) {
									RookMove(testBoard, 5, i, j, i, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									RookMove(testBoard, 5, i, j, i, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] < 0)) {
									RookMove(testBoard, 5, i, j, i, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 5;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case 7: // unmoved rook
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									RookMove(testBoard, 7, i, j, i+inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 7;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] < 0)) {
									RookMove(testBoard, 7, i, j, i+inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 7;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									RookMove(testBoard, 7, i, j, i, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 7;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] < 0)) {
									RookMove(testBoard, 7, i, j, i, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 7;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case 17:
							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									RookMove(testBoard, 17, i, j, i, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 17;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] < 0)) {
									RookMove(testBoard, 17, i, j, i, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 17;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									RookMove(testBoard, 17, i, j, i+inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 17;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] < 0)) {
									RookMove(testBoard, 17, i, j, i+inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 17;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case 2:
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									RookMove(testBoard, 2, i, j, i+inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] < 0)) {
									RookMove(testBoard, 2, i, j, i+inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i+inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 >= 1) && (board[i][j-inc] == 0)) {
									RookMove(testBoard, 2, i, j, i, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
									
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j - inc + 1 >= 1) && (board[i][j-inc] < 0)) {
									RookMove(testBoard, 2, i, j, i, j-inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j-inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}


							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									RookMove(testBoard, 2, i, j, i, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] < 0)) {
									RookMove(testBoard, 2, i, j, i, j+inc, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i;
										moves[numMoves].d = j+inc;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
										
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									RookMove(testBoard, 2, i, j, i-inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
									
									}
									inc++;
									resetTestBoard(board, testBoard);
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] < 0)) {
									RookMove(testBoard, 2, i, j, i-inc, j, 'b', 0);
									if (!getCheck(testBoard, 1)) {
										moves[numMoves].piece = 2;
										moves[numMoves].a = i;
										moves[numMoves].b = j;
										moves[numMoves].c = i-inc;
										moves[numMoves].d = j;
										moves[numMoves].value = getMaterial(testBoard, color);
										numMoves++;
								
									}
									inc++;
									resetTestBoard(board, testBoard);
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case 8: // unmoved king
							// up
							if ((i > 0) && (board[i-1][j] < 1)) {
								KingMove(testBoard, 8, i, j, i-1, j, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// up right
							if ((i > 0) && (j < 7) && (board[i-1][j+1] < 1)) {
								KingMove(testBoard, 8, i, j, i-1, j+1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// up left
							if ((i > 0) && (j > 0) && (board[i-1][j-1] < 1)) {
								KingMove(testBoard, 8, i, j, i-1, j-1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down left
							if ((i < 7) && (j > 0) && (board[i+1][j-1] < 1)) {
								KingMove(testBoard, 8, i, j, i+1, j-1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down right
							if ((i < 7) && (j < 7) && (board[i+1][j+1] < 1)) {
								KingMove(testBoard, 8, i, j, i+1, j+1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down 
							if ((i < 7) && (board[i+1][j] < 1)) {
								KingMove(testBoard, 8, i, j, i+1, j, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// right
							if ((j < 7) && (board[i][j+1] < 1)) {
								KingMove(testBoard, 8, i, j, i, j+1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// left
							if ((j > 0) && (board[i][j-1] < 1)) {
								KingMove(testBoard, 8, i, j, i, j-1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 8;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}
							break;
						case 6: // king
							// up
							if ((i > 0) && (board[i-1][j] < 1)) {
								KingMove(testBoard, 6, i, j, i-1, j, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// up right
							if ((i > 0) && (j < 7) && (board[i-1][j+1] < 1)) {
								KingMove(testBoard, 6, i, j, i-1, j+1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// up left
							if ((i > 0) && (j > 0) && (board[i-1][j-1] < 1)) {
								KingMove(testBoard, 6, i, j, i-1, j-1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i-1;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down left
							if ((i < 7) && (j > 0) && (board[i+1][j-1] < 1)) {
								KingMove(testBoard, 6, i, j, i+1, j-1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down right
							if ((i < 7) && (j < 7) && (board[i+1][j+1] < 1)) {
								KingMove(testBoard, 6, i, j, i+1, j+1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// down 
							if ((i < 7) && (board[i+1][j] < 1)) {
								KingMove(testBoard, 6, i, j, i+1, j, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i+1;
									moves[numMoves].d = j;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// right
							if ((j < 7) && (board[i][j+1] < 1)) {
								KingMove(testBoard, 6, i, j, i, j+1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i;
									moves[numMoves].d = j+1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}

							// left
							if ((j > 0) && (board[i][j-1] < 1)) {
								KingMove(testBoard, 6, i, j, i, j-1, 'b', 0);
								if (!getCheck(testBoard, 1)) {
									moves[numMoves].piece = 6;
									moves[numMoves].a = i;
									moves[numMoves].b = j;
									moves[numMoves].c = i;
									moves[numMoves].d = j-1;
									moves[numMoves].value = getMaterial(testBoard, color);
									numMoves++;
									resetTestBoard(board, testBoard);
								}
							}
					}
				}
			}
		}
		
	}
	return numMoves;
}

void resetTestBoard(int board[8][8], int testBoard[8][8]) {
	int i, j;

	// copy of board to test without altering real game board
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			testBoard[i][j] = board[i][j];
		}
	}
}

char switchColor(char color) {
	if (color == 'w') {
		return 'b';
	}
	else {
		return 'w';
	}
}


int getCheck(int board[8][8], int color) {
	int numMoves = 0;
	int testBoard[8][8];
	int i, j, checkNext, inc;

	// if black in check
	if (color) {
		numMoves = 0;

		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (board[i][j] < 0) {
					switch(board[i][j]) {			
						case -1:
							//capture right
							if (i > 0 && j < 7 && board[i-1][j+1] > 0 && board[i-1][j+1] != 6 && board[i-1][j+1] != 8) {
								if (board[i-1][j+1] == 6 || board[i-1][j+1] == 8) {
									return 1;
								}
							}
							// capture left
							if (i > 0 && j > 0 && board[i-1][j-1] > 0 && board[i-1][j-1] != 6 && board[i-1][j-1] != 8) {
								if (board[i-1][i-1] == 6 || board[i-1][j-1] == 8) {
									return 1;
								}
							}
							break;
						case -3:
							// up 2 right 1
							if ((i - 2 >= 0) && (j + 1 < 8) && (board[i-2][j+1] >= 0)) {
								if (board[i-2][j+1] == 6 || board[i-2][j+1] == 8) {
									return 1;
								}
							}
							// up 1 right 2
							if ((i - 1 >= 0) && (j + 2 < 8) && (board[i-1][j+2] > -1)) {
								if (board[i-1][j+2] == 6 || board[i-1][j+2] == 8) {
									return 1;
								}
							}
							// down 1 right 2
							if ((i + 1 < 8) && (j + 2 < 8) && (board[i+1][j+2] > -1)) {
								if (board[i+1][j+2] == 6 || board[i-1][j+2] == 8) {
									return 1;
								}
							}
							// down 2 right 1
							if ((i + 2 < 8) && (j + 1 < 8) && (board[i+2][j+1] > -1)) {
								if (board[i+2][j+1] == 6 || board[i+2][j+1] == 8) {
									return 1;
								}
							}
							// down 2 left 1
							if ((i + 2 < 8) && (j - 1 >= 0) && (board[i+2][j-1] > -1)) {
								if (board[i+2][j-1] == 6 || board[i+2][j-1] == 8) {
									return 1;
								}
							}
							// down 1 left 2
							if ((i + 1 < 8) && (j - 2 >= 0) && (board[i+1][j-2] > -1)) {
								if (board[i+1][j-2] == 6 || board[i+1][j-2] == 8) {
									return 1;
								}							
							}
							// up 1 left 2
							if ((i - 1 >= 0) && (j - 2 >= 0) && (board[i-1][j-2] > -1)) {
								if (board[i-1][j-2] == 6 || board[i-1][j-2] == 8) {
									return 1;
								}								
							}
							// up 2 left 1
							if ((i - 2 >= 0) && (j - 1 >= 0) && (board[i-2][j-1] > -1)) {
								if (board[i-2][j-1] == 6 || board[i-2][j-1] == 8) {
									return 1;
								}								
							}
							break;
						case -4:
							// up left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && (board[i-inc][j-inc] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && board[i-inc][j-inc] > 0) {
									if (board[i-inc][j-inc] == 6 || board[i-inc][j-inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// up right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] > 0)) {
									if (board[i-inc][j+inc] == 6 || board[i-inc][j+inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] > 0)) {
									if (board[i+inc][j+inc] == 6 || board[i+inc][j+inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] > 0)) {
									if (board[i+inc][j-inc] == 6 || board[i+inc][j-inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case -5:
							// up left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && (board[i-inc][j-inc] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && board[i-inc][j-inc] > 0) {
									if (board[i-inc][j-inc] == 6 || board[i-inc][j-inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// up right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] > 0)) {
									if (board[i-inc][j+inc] == 6 || board[i-inc][j+inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] > 0)) {
									if (board[i+inc][j+inc] == 6 || board[i+inc][j+inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] > 0)) {
									if (board[i+inc][j-inc] == 6 || board[i+inc][j-inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] > 0)) {
									if (board[i-inc][j] == 6 || board[i-inc][j] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] > 0)) {
									if (board[i+inc][j] == 6 || board[i+inc][j] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									inc++;
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] > 0)) {
									if (board[i][j-inc] == 6 || board[i][j-inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									inc++;
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] > 0)) {
									if (board[i][j+inc] == 6 || board[i][j+inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case -7: // unmoved rook
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] > 0)) {
									if (board[i-inc][j] == 6 || board[i-inc][j] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									inc++;
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] > 0)) {
									if (board[i][j+inc] == 6 || board[i][j+inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case -17:
							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									inc++;
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] > 0)) {
									if (board[i][j-inc] == 6 || board[i][j-inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] > 0)) {
									if (board[i-inc][j] == 6 || board[i-inc][j] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case -2:
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] > 0)) {
									if (board[i-inc][j] == 6 || board[i-inc][j] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									inc++;
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] > 0)) {
									resetTestBoard(board, testBoard);
									if (board[i][j-inc] == 6 || board[i][j-inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									inc++;
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] > 0)) {
									if (board[i][j+inc] == 6 || board[i][j+inc] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									inc++;
								
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] > 0)) {
									if (board[i+inc][j] == 6 || board[i+inc][j] == 8) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}						
					}
				}
			}
		}
		return 0;
	}

	// find moves for black
	else {
		numMoves = 0;

		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (board[i][j] > 0) {
					switch(board[i][j]) {			
						case 1:
							//capture left
							if (i < 7 && j < 7 && board[i+1][j+1] < 0 && board[i+1][j+1] != -6 && board[i+1][j+1] != -8) {
								if (board[i+1][j+1] == -8 || board[i+1][j+1] == -6) {
									return 1;
								}
							}
							// capture left
							if (i < 7 && j > 0 && board[i+1][j-1] < 0 && board[i+1][j-1] != -6 && board[i+1][j-1] != -8) {
								if (board[i+1][j-1] == -8 || board[i+1][j-1] == -6) {
									return 1;
								}
							}
							break;
						case 3:
							// up 2 right 1
							if ((i > 1) && (j < 7) && (board[i-2][j+1] < 1)) {
								if (board[i-2][j+1] == -8 || board[i-2][j+1] == -6) {
									return 1;
								}
							}
							// up 1 right 2
							if ((i - 1 >= 0) && (j + 2 < 8) && (board[i-1][j+2] < 1)) {
								if (board[i-1][j+2] == -8 || board[i-1][j+2] == -6) {
									return 1;
								}
							}
							// down 1 right 2
							if ((i + 1 < 8) && (j + 2 < 8) && (board[i+1][j+2] < 1)) {
								if (board[i+1][j+2] == -8 || board[i+1][j+2] == -6) {
									return 1;
								}
							}
							// down 2 right 1
							if ((i + 2 < 8) && (j + 1 < 8) && (board[i+2][j+1] < 1)) {
								if (board[i+2][j+1] == -8 || board[i+2][j+1] == -6) {
									return 1;
								}
							}
							// down 2 left 1
							if ((i + 2 < 8) && (j - 1 >= 0) && (board[i+2][j-1] < 1)) {
								if (board[i+2][j-1] == -8 || board[i+2][j-1] == -6) {
									return 1;
								}
							}
							// down 1 left 2
							if ((i + 1 < 8) && (j - 2 >= 0) && (board[i+1][j-2] < 1)) {
								if (board[i+1][j-2] == -8 || board[i+1][j-2] == -6) {
									return 1;
								}
							}
							// up 1 left 2
							if ((i - 1 >= 0) && (j - 2 >= 0) && (board[i-1][j-2] < 1)) {
								if (board[i-1][j-2] == -8 || board[i-1][j-2] == -6) {
									return 1;
								}						
							}
							// up 2 left 1
							if ((i - 2 >= 0) && (j - 1 >= 0) && (board[i-2][j-1] < 1)) {
								if (board[i-2][j-1] == -8 || board[i-2][j-1] == -6) {
									return 1;
								}
							}
							break;
						case 4:
							// up left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && (board[i-inc][j-inc] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && board[i-inc][j-inc] < 0) {
									if (board[i-inc][j-inc] == -8 || board[i-inc][j-inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// up right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] < 0)) {
									if (board[i-inc][j+inc] == -8 || board[i-inc][j+inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] < 0)) {
									if (board[i+inc][j+inc] == -8 || board[i+inc][j+inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] < 0)) {
									if (board[i+inc][j-inc] == -8 || board[i+inc][j-inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case 5:
							// up left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && (board[i-inc][j-inc] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (j - inc + 1 > 0) && board[i-inc][j-inc] < 0) {
									if (board[i-inc][j-inc] == -8 || board[i-inc][j-inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// up right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (j + inc - 1 < 7) && (board[i-inc][j+inc] < 0)) {
									if (board[i-inc][j+inc] == -8 || board[i-inc][j+inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j + inc - 1 < 7) && (board[i+inc][j+inc] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (j + inc - 1  < 7) && (board[i+inc][j+inc] < 0)) {
									if (board[i+inc][j+inc] == -8 || board[i+inc][j+inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (j - inc + 1 > 0) && (board[i+inc][j-inc] < 0)) {
									if (board[i+inc][j-inc] == -8 || board[i+inc][j-inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] < 0)) {
									if (board[i-inc][j] == -8 || board[i-inc][j] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] < 0)) {
									if (board[i+inc][j] == -8 || board[i+inc][j] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									inc++;
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] < 0)) {
									if (board[i][j-inc] == -8 || board[i][j-inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									inc++;
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] < 0)) {
									if (board[i][j+inc] == -8 || board[i][j+inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case 7: // unmoved rook
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] < 0)) {
									if (board[i+inc][j] == -8 || board[i+inc][j] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									inc++;
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] < 0)) {
									if (board[i][j+inc] == -8 || board[i][j+inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case 17:
							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 > 0) && (board[i][j-inc] == 0)) {
									inc++;
								}
								else if ((j - inc + 1 > 0) && (board[i][j-inc] < 0)) {
									if (board[i][j-inc] == -8 || board[i][j-inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									inc++;
								}
								else if ((i + inc - 1 < 7) && (board[i+inc][j] < 0)) {
									if (board[i+inc][j] == -8 || board[i+inc][j] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							break;
						case 2:
							// up
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i - inc + 1 > 0) && (board[i-inc][j] == 0)) {
									inc++;
								}
								else if ((i - inc + 1 > 0) && (board[i-inc][j] < 0)) {
									if (board[i+inc][j] == -8 || board[i-inc][j] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
							// left
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j - inc + 1 >= 1) && (board[i][j-inc] == 0)) {
									inc++;
								}
								else if ((j - inc + 1 >= 1) && (board[i][j-inc] < 0)) {
									if (board[i][j-inc] == -8 || board[i][j-inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}


							// right
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((j + inc - 1 < 7) && (board[i][j+inc] == 0)) {
									inc++;
								}
								else if ((j + inc - 1 < 7) && (board[i][j+inc] < 0)) {
									if (board[i][j+inc] == -8 || board[i][j+inc] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}

							// down
							checkNext = 1;
							inc = 1;
							while (checkNext) {
								if ((i + inc - 1 < 7) && (board[i+inc][j] == 0)) {
									inc++;
								}
								else if ((i + inc -1 < 7) && (board[i+inc][j] < 0)) {
									if (board[i+inc][j] == -8 || board[i+inc][j] == -6) {
										return 1;
									}
									checkNext = 0;
								}
								else {
									checkNext = 0;
								}
							}
					}
				}
			}
		}
		return 0;
	}
}







