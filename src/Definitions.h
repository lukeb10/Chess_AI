#ifndef DEFINITIONS_H
#define DEFINITIONS_H

FILE *text ;

enum { pawn=1, rook, knight, bishop, queen, king }; 

enum { wP=1, wR, wN, wB, wQ, wK, bP=-1, bR=-2, bN=-3, bB=-4, bQ=-5, bK=-6};

enum {   a1=0, b1, c1, d1, e1, f1, g1, h1,
	 a2=10, b2, c2, d2, e2, f2, g2, h2,
	 a3=20, b3, c3, d3, e3, f3, g3, h3,
	 a4=30, b4, c4, d4, e4, f4, g4, h4,
	 a5=40, b5, c5, d5, e5, f5, g5, h5,
	 a6=50, b6, c6, d6, e6, f6, g6, h6,
 	 a7=60, b7, c7, d7, e7, f7, g7, h7,
	 a8=70, b8, c8, d8, e8, f8, g8, h8  };

//int board[8][8];

#endif
