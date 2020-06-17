//Functions.c 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Functions.h"
#include "Display.h"
#include "Definitions.h"

void setBoard(int board[8][8]){
	int i, j;

	//setting all spaces to zero
	for(i=0; i<8; i++){
		for(j=0; j<8;j++){
			board[i][j]=0;
		}
	}

	//setting pawn values on the board
	for(i=0; i<8; i++){	
		board[1][i]= 1;
		board[6][i]= -1;	
	}	
	
	
	//setting rooks 
	board[0][0]= 7;
	board[0][7]= 17;
	board[7][0]=-7;
	board[7][7]=-17;
	
	
	//setting knights
	board[0][1]=3;
	board[0][6]=3;
	board[7][1]=-3;
	board[7][6]=-3;
	

	//settng bishops
	board[0][2]=4;
	board[0][5]=4;
	board[7][2]=-4;
	board[7][5]=-4;
	

	//setting queen
	board[0][3]=5;
	board[7][3]=-5;


	//setting kings
	board[0][4]=8;
	board[7][4]=-8;

}

void PawnMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test){
	//pawn moving
	if(piece == 1|| piece== 10){
		if(board[c][d]==0){
			if(&board[c][d] == &board[a+1][b]){       //moves pawn forward one space
				if(c==7){			//check last row then promote
					Promotion(board, piece, a, b, c, d); 
				}
				else{
					board[c][d]=1;
					board[a][b]=0;
				}
			}
			else if(a==1 && (&board[c][d]==&board[a+2][b])){	//moves pawn forward two spaces from initial spot
				board[c][d]= 10;
				board[a][b]=0;				//10 keeps track of pawn that moved forward two
			}
			else if(board[c][d]==0 && c==5 && a==4 && (b-1==d || b+1 ==d) && board[a][d]==-10 ){
				EnPassant(board, piece, a, b, c, d);	//check for En Passant
			}
			else{
			    if (test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
					}
				IllegalMove(text, team);
				exit(0); 
			    }
			}
		}
		else if(board[c][d]<0){	
			if((a+1 == c)&&((b+1 == d)|| (b-1 == d))){  // pawn capturing
				if(c==7){				//on last row from capturing, then promote
					Promotion(board, piece, a, b, c, d);
				}
				else{
					board[c][d]=1;
					board[a][b]=0;
				}
			}
			else{
			    if(test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
					}
				IllegalMove(text, team);
				exit(0); 
			    }
			}
		}
		else{
		     if( test==1){						//case where it lands on its own piece
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0); 
  		    }
		}		
	}	

	else if(piece == -1 || piece == -10){

		if(board[c][d]==0){
			if(&board[c][d] == &board[a-1][b]){       //moves pawn forward one space
				if(c==0){			//on last row then promote
					Promotion(board, piece, a, b, c, d);
				}
				else{
					board[c][d]=-1;
					board[a][b]=0;
				}
			}
			else if(a==6 && (&board[c][d]== &board[a-2][b])){	//moves pawn forward two spaces from initial spot
				board[c][d]= -10;				//-10 keeps track it moved up two
				board[a][b]=0;
			}
			else if(board[c][d]==0 && c==2 && a==3 && (b-1==d || b+1 == d) && board[a][d]==10){
			
				EnPassant(board, piece, a, b, c, d);	//Checks for En Passant
			}
			else{
			     if(test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0); 
			    }
			}	
		}
		else if(board[c][d]>0){	
			if((a-1 == c)&&((b+1 == d)|| (b-1 == d))){  // pawn capturing
				if(c==0){
					Promotion(board, piece, a, b, c, d);
				}
				else{
					board[c][d]=-1;
					board[a][b]=0;
				}
			}
			else{
		 	    if(test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0); 
			    }
			}
		}
		else{
		    if(test==1){
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0); 
		   }
		}
		
	}

}

void RookMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test){
	if(piece == 2 || piece== 5 || piece ==7 || piece == 17){
		int pieceCheck=0;
		int i;
		int clear=0;
		
		//check castling first
		if((board[c][d]== 8 && (board[a][b] ==7 || board[a][b] == 17))){
			Castling(board, piece, a, b, c, d, team, test);
		}
		//then check other rook functions
		else if(board[c][d]<=0 && (a==c || b==d)){
			if(a==c){
				pieceCheck= b-d;
				if(pieceCheck<0){
					 pieceCheck=d-b;
				}
			
				if(b>d){
					for(i=1; i<pieceCheck; i++){
						if(board[a][b-i]!=0){
							clear++;
						}
					}
				}
				else if(d>b){
					for(i=1; i<pieceCheck; i++){
						if(board[a][d-i]!=0){
							clear++;
						}
					}
				}
			}
			else if(b==d){
				pieceCheck= a-c;
				if(pieceCheck<0){
					pieceCheck= c-a;
				}
				
				if(a>c){
					for(i=1; i<pieceCheck; i++){
						if(board[a-i][b] != 0){
							clear++;
						}
					}
				}
				else if(c>a){
					for(i=1; i<pieceCheck; i++){
						if(board[c-i][b] != 0){
							clear++;
						}
					}
				}
			
			}
			
			if(clear==0){
				if(piece==5){
					board[c][d]= piece;
				}
				else{
					board[c][d]= 2;	
				}
				board[a][b]=0;
			}
			else{
			    if(test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0); 
			    }
			}
		}
		else{
		    if(test==1){
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0); 
		    }
		}
	}

	else if(piece == -2 || piece==-5 || piece == -7 || piece == -17){
		int pieceCheck=0;
		int i;
		int clear=0;
		
		//check castle function first
		if((board[c][d] == -8 && (board[a][b] == -7 || board[a][b]== - 17))){
			Castling(board, piece, a, b, c, d, team, test);
		}
		// check other rook functions next
		else if(board[c][d]>=0 && (a==c || b==d)){
			if(a==c){
				pieceCheck= b-d;
				if(pieceCheck<0){
					 pieceCheck=d-b;
				}
			
				if(b>d){
					for(i=1; i<pieceCheck; i++){
						if(board[a][b-i]!=0){
							clear++;
						}
					}
				}
				else if(d>b){
					for(i=1; i<pieceCheck; i++){
						if(board[a][d-i]!=0){
							clear++;
						}
					}
				}
			}
			else if(b==d){
				pieceCheck= a-c;
				if(pieceCheck<0){
					pieceCheck= c-a;
				}
				
				if(a>c){
					for(i=1; i<pieceCheck; i++){
						if(board[a-i][b] != 0){
							clear++;
						}
					}
				}
				else if(c>a){
					for(i=1; i<pieceCheck; i++){
						if(board[c-i][b] != 0){
							clear++;
						}
					}
				}
			}
			if(clear==0){
				if(piece==-5){
					board[c][d]= piece;
				}
				else{
					board[c][d]= -2;	
				}
				board[a][b]=0;
			}	
			else{
			    if(test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0); 
			    }
			}
		}
		else{
		    if(test==1){
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0); 
		    }
		}
	}
}

void BishopMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test)   //Bishop Movement
{
	if(piece == 4 || piece==5)
	{
		int pieceCheck=0;
		int i;
		int xd;
		int yd;
		int n;
		if(board[c][d]<=0)
		{
			if(abs(c-a)==abs(d-b) && abs(c-a)>0)       //If true, legal move
			{
		    		n=abs(c-a);                                //n is the distance the piece is attempting to move
		    		xd = (c-a)/n;                              //Gets X Direction
		    		yd = (d-b)/n;                              //Gets Y Direction
		    		for(i = 1; i<n; i++)
				{
		      			if(board[a+(i*xd)][b+(i*yd)] !=0)       //This is the only check because xd and yd is the direction
						pieceCheck++;
		      	      	}
		  		if(pieceCheck==0)
				{
					board[c][d]= piece;
					board[a][b]=0;
		  		}
			}
			else
			{
			    if(test==1){
				printf("Illegal Move!\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0);
			    }
			}
		}
	}

	else if(piece == -4|| piece== -5)
	{
		int pieceCheck=0;
		int i;
		int xd;
		int yd;
		int n;
		if(board[c][d]>=0)
		{
			if(abs(c-a)==abs(d-b) && abs(c-a)>0)        //If true, legal move
			{
		    		n=abs(c-a);                                //n is the distance the piece is attempting to move
		    		xd = (c-a)/n;                              //Gets X Direction
		    		yd = (d-b)/n;                              //Gets Y Direction
		    		for(i=1; i<n; i++)
				{
		      			if(board[a+(i*xd)][b+(i*yd)] !=0)       //This is the only check because xd and yd is the direction
						pieceCheck++;
		      		}	    
		  		if(pieceCheck==0)
				{
		               		board[c][d]= piece;
		               		board[a][b]=0;
		  		}
			}
			else
			{
			    if(test==1){
				printf("Illegal Move!\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0);
			    }
			}	
		 }
	}
}

void KingMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test){

	// if castle
	if (piece == 8 && (d == 0 || d == 7)) {
		Castling(board, piece, a, b, c, d, team, test);
	}
	else if (piece == -8 && (d == 0 || d == 7)) {
		Castling(board, piece, a, b, c, d, team, test);
	}

	else if(piece==6 || piece== 8){
		if(board[c][d]<=0){
		//8 ways a king can move
			if(&board[a-1][b-1]==&board[c][d]){
				board[c][d]=6;
				board[a][b]=0;
			}	
			else if(&board[a-1][b]==&board[c][d]){
				board[c][d]=6;
				board[a][b]=0;
			}
			else if(&board[a-1][b+1]==&board[c][d]){
				board[c][d]=6;
				board[a][b]=0;
			}
			else if(&board[a][b-1]==&board[c][d]){
				board[c][d]=6;
				board[a][b]=0;
			}
			else if(&board[a][b+1]==&board[c][d]){
				board[c][d]=6;
				board[a][b]=0;
			}
			else if(&board[a+1][b-1]==&board[c][d]){
				board[c][d]=6;
				board[a][b]=0;
			}
			else if(&board[a+1][b]==&board[c][d]){
				board[c][d]=6;
				board[a][b]=0;
			}
			else if(&board[a+1][b+1]==&board[c][d]){
				board[c][d]=6;
				board[a][b]=0;
			}
			else{
			    if(test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0); 
			    }
			}	
		}
		else{
		    if(test==1){
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0);
		    } 
		}
	}
	else if(piece==-6 || piece==-8){
		if(board[c][d]>=0){
		//8 ways a king can move
			if(&board[a-1][b-1]==&board[c][d]){
				board[c][d]=-6;
				board[a][b]=0;
			}	
			else if(&board[a-1][b]==&board[c][d]){
				board[c][d]=-6;
				board[a][b]=0;
			}
			else if(&board[a-1][b+1]==&board[c][d]){
				board[c][d]=-6;
				board[a][b]=0;
			}
			else if(&board[a][b-1]==&board[c][d]){
				board[c][d]=-6;
				board[a][b]=0;
			}
			else if(&board[a][b+1]==&board[c][d]){
				board[c][d]=-6;
				board[a][b]=0;
			}
			else if(&board[a+1][b-1]==&board[c][d]){
				board[c][d]=-6;
				board[a][b]=0;
			}
			else if(&board[a+1][b]==&board[c][d]){
				board[c][d]=-6;
				board[a][b]=0;
			}
			else if(&board[a+1][b+1]==&board[c][d]){
				board[c][d]=-6;
				board[a][b]=0;
			}
			else{
			    if(test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0); 
			    }
			}
		}
		else{
		    if(test==1){
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0); 
		    }
		}
	}
}

void KnightMove(int board[8][8], int piece, int a, int b, int c, int d, char team, int test)
{
	if(piece==3)
	{
		if(board[c][d]<=0)
		{
			if(&board[a-1][b-2]==&board[c][d])
			{
				board[c][d]=piece;
				board[a][b]=0;
			}
			else if(&board[a-2][b-1]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a-2][b+1]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a-1][b+2]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}
			else if(&board[a+2][b-1]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a+1][b-2]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a+2][b+1]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a+1][b+2]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}					
			else{
			    if(test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0); 
			    }
			}
		}
		else{
		    if(test==1){
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0); 
		    }
		}
	}
	if(piece==-3)
	{
		if(board[c][d]>=0)
		{
			if(&board[a-1][b-2]==&board[c][d])
			{
				board[c][d]=piece;
				board[a][b]=0;
			}
			else if(&board[a-2][b-1]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a-2][b+1]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a-1][b+2]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}
			else if(&board[a+2][b-1]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a+1][b-2]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a+2][b+1]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}			
			else if(&board[a+1][b+2]==&board[c][d])
			{
				board[c][d]= piece;
				board[a][b]= 0;	
			}					
			else{
			    if(test==1){
				perror("illegal move. Game ending\n");
				if(team== 'w'){
					printf("Black team wins\n");
				}
				else{
					printf("White team wins\n");
				}
				IllegalMove(text, team);
				exit(0); 
			    }
			}
		}
		else{
		    if(test==1){
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0); 
		    }
		}
	}
} 

void Castling(int board[8][8], int piece, int a, int b, int c, int d, char team, int test){
	//check boxes for king and rook if they are in the initial position, if they are the make the proper switch so long as the entries in between are empty
	//note: we have no way to check if they have initial moved before
	int clear=0;

	if((board[a][b] == 8 && board[c][d] == 7) || (board[a][b] == 7 && board[c][d] == 8))	//castle between king and top left rook
	{	
		if (board[0][1] == 0 && board[0][2] == 0 && board[0][3] == 0) {
			clear = 1;
		}

		if(clear){
			board[0][0] = 0;
			board[0][1] = 0;
			board[0][2] = 6;
			board[0][3] = 2;
			board[0][4] = 0;
		}
		else{
		   if(test==1){
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0); 
		    }
		}	
	}
	else if ((board[a][b] == 8 && board[c][d] == 17)|| (board[a][b] == 17 && board[c][d]== 8))	//castle between king and top left rook
	{	
		if (board[0][5] == 0 && board[0][6] == 0) {
			clear = 1;
		}

		if(clear){
			board[0][6] = 6;
			board[0][5] = 2;
			board[0][4] = 0;
			board[0][7] = 0;
		}
		else{
		    if(test==1){
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0); 
		    }
		}
		
	}
	else if((board[a][b] == -8 && board[c][d] == -7)|| (board[a][b] == -7 && board[c][d] == -8))	//castle between king and top left rook
	{	
		if (board[7][1] == 0 && board[7][2] == 0 && board[7][3] == 0) {
			clear = 1;
		}

		if(clear){
			board[7][1] = 0;
			board[7][2] = -6;
			board[7][3] = -2;
			board[7][0] = 0;
			board[7][4] = 0;
		}
		else{
		    if(test){
			printf("illegal move.\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0);
		    }
		}
	}
	else if((board[a][b] == -8 && board[c][d] == -17) || ( board[a][b] == -17 && board[c][d] ==-8))	//castle between king and top left rook
	{	
		if (board[7][5] == 0 && board[7][6] == 0) {
			clear = 1;
		}

		if(clear){
			board[7][5] = -2;
			board[7][6] = -6;
			board[7][7] = 0;
			board[7][4] = 0;
		}
		else{
		    if(test==1){
			printf("illegal move.\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(0);
		    }
		}
	}
	else{
   	    if(test==1){
		perror("illegal move. Game ending\n");
		if(team== 'w'){
			printf("Black team wins\n");
		}
		else{
			printf("White team wins\n");
		}
		IllegalMove(text, team);
		exit(0); 
	    }
	}
}	


void Promotion(int board[8][8], int piece, int a, int b, int c, int d){
	char newPiece[8];
	char queenP[]= "Queen";
	char bishopP[]= "Bishop";
	char rookP[]= "Rook"; 
	char knightP[]= "Knight";
	int value=0;

	if(piece==1){
		while(value==0){
			printf("Promotion! Please type in new type of piece for pawn: \"Queen\", \"Bishop\", \"Rook\", \"Knight\" \n");
			scanf("%s", newPiece);
			if(strcmp(newPiece, queenP) == 0){
				value=5;
			}
			else if(strcmp(newPiece, bishopP) ==0){
				value=4;
			}
			else if(strcmp(newPiece, rookP) == 0){
				value= 2;
			}
			else if(strcmp(newPiece, knightP)== 0){
				value= 3;
			}
			else{
				printf("invalid input, please type in the correct piece\n");
				value=0;
			}
		}
	}	
	else if(piece==-1){
		while(value==0){
			printf("Promotion! Please type in new type of piece for pawn: \"Queen\", \"Bishop\", \"Rook\", \"Knight\" \n");
			scanf("%s", newPiece);
			if(strcmp(newPiece, queenP) == 0){
				value= -5;
			}
			else if(strcmp(newPiece, bishopP) ==0){
				value= -4;
			}
			else if(strcmp(newPiece, rookP) == 0){
				value= -2;
			}
			else if(strcmp(newPiece, knightP)== 0){
				value= -3;
			}
			else{
				printf("invalid input, please type in the correct piece\n");
			}
		}
	}

	board[c][d]= value;
	board[a][b]= 0;


}

void EnPassant(int board[8][8], int piece, int a, int b, int c, int d){
	//1. only for pawns
	//2. capturing pawn must be on fifth rank for W, fourth rank for B
	//3. captured paswn must have moved two squares up
	//4. must pass the pawn on that turn
	if(piece==1){
		if(board[c][d]==0 && c==5 && a==4 && (b-1==d || b+1 ==d) && board[a][d]==-10){
			printf("This piece is captured by En Passant\n");
			board[c][d]=1;
			board[a][b]=0;
			board[a][d]=0;
		}
	}
	else if(piece==-1){
		if(board[c][d]==0 && c==2 && a==3 && (b-1==d || b+1 == d) && board[a][d]==10){
			printf("This piece is captured by En Passant \n");
			board[c][d]=-1;
			board[a][b]=0;
			board[a][d]=0;
	
		}
	}	

}

void Move(int board[8][8], int x, int y, char team, int test)
{

	//tens digit place initial spot
	int a= x/10;
	//ones digit place from initial spot
	int b= x%10;

	//tens digit place of the final spot
	int c= y/10;

	//ones digit place of final spot
	int d= y%10;

	int piece= board[a][b];

	//empty spot
	if(&board[a][b]== &board[c][d])
	{
		printf("illegal move\n");
	}	
	else
	{
	  	if((team == 'w' && piece<0) || (team=='b' && piece>0)){	
		if(piece==0)
		{
			printf("Space is empty\n");
		}	
	
	//pawn moving
		else if(piece==1 || piece == -1 || piece== 10 || piece == -10)
		{
			PawnMove(board, piece, a, b, c, d, team, test);
		}
	
	//Rook moving
		else if(piece==2 || piece==-2 || piece == 7 || piece == -7 || piece == 17 || piece == -17)
		{
			RookMove(board, piece, a, b, c, d, team, test);
		}

	//Knight moving
		else if(piece==3 || piece==-3)
		{
			KnightMove(board, piece, a, b, c, d, team, test);
		}	

	//Bishop moving
		else if(piece==4 || piece==-4)
		{
			BishopMove(board, piece, a, b, c, d, team, test);
		}

	//queen moving
		else if(piece==5 || piece==-5)
		{
			if(a==c || b==d)
			{
				RookMove(board, piece, a, b, c, d, team, test);
			} 
			else
			{
				BishopMove(board, piece, a, b, c, d, team, test);
			}
		
	//King moving
		}
		else if(piece==6 || piece ==-6 || piece== 8 || piece == -8)
		{
			KingMove(board, piece, a, b, c, d, team, test);
		}
		}
		else{
			perror("illegal move. Game ending\n");
			if(team== 'w'){
				printf("Black team wins\n");
			}
			else{
				printf("White team wins\n");
			}
			IllegalMove(text, team);
			exit(10); 
			}
	}		
}





int BlackCheck(int board[8][8])
{
	for(int i=0; i<8; i++)		//Row
	{
		for(int j=0; j<8; j++)		//Column
		{
			if(board[i][j] == -1 || board[i][j] == -10) //Pawn
			{
				// to prevent seg fault
				if (i > 0 && j < 7) 
				{
					if(board[i-1][j+1] == 6|| board[i-1][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// to prevent seg fault
				else if (i > 0 && j > 0)
				{
					if (board[i-1][j-1] == 6 || board[i-1][j-1] == 8)	//Another possible movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
			}



			else if (board[i][j] == -2 || board[i][j] == -7 || board[i][j] == -17) //Rook (vertical and Horizontal)
			{
				int x,y;
				
				x = i;
				y = j;
				
				do 			//Going right
				{
					x++;
					if(board[x][y] == 6|| board[x][y] == 8)
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}while(board[x][y] == 0 && x < 7); //Post check allows it to check for a king first 

				x = i;
				y = j;

				do 			//Going left
				{
					x--;
					if(board[x][y] == 6|| board[x][y] == 8)
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}

				}while(board[x][y] == 0 && x > 0); //Post check allows it to check for a king first	
				

				y = j;
				x = i;
				do 			//Going down
				{
					y++;
					if(board[x][y] == 6|| board[x][y] == 8)
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}while(board[x][y] == 0 && y < 7); //Post check allows it to check for a king first 
					
				y = j;
				x = i;
				do 			//Going up
				{
					y--;
					if(board[x][y] == 6|| board[x][y] == 8)
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}while(board[x][y] == 0 && y > 0); //Post check allows it to check for a king first
				


			}

			else if (board[i][j] == -5) //queen
			{
			 
					int x, y; // temps
					
					x = i;
					y = j;
					// Going top right
					do
					{
						y++;
						x--;
						if (y > 7 || x < 0)
							break;
						
						if (board[x][y] == 6|| board[x][y] == 8)
						{
							printf("Black Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x >= 0 && y <= 7);
						
					
					x = i;
					y = j;
					// Going Bottom Left
					do
					{
						x++;
						y--;
						// to prevent seg fault
						if (x > 7 || y < 0)
							break;
						
						if (board[x][y] == 6|| board[x][y] == 8) 
						{	
							printf("Black Team, you are in Check!\n");
							return 1;
						}

					} while (board[x][y] == 0 && x <= 7 && y >= 0);
						
						
					x = i;
					y = j;
					// Going Bottom Right
					do
					{
						x++;
						y++;
						// to prevent seg fault
						if (x > 7 || y > 7)
							break;
						
						if (board[x][y] == 6|| board[x][y] == 8) 
						{	
							printf("Black Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x <= 7 && y <= 7);
						
					x = i;
					y = j;
					// Going Top Left
					do
					{
						x--;
						y--;
						// to prevent seg fault
						if (x < 0 || y < 0)
							break;
						
						if (board[x][y] == 6|| board[x][y] == 8) 
						{	
							printf("Black Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x >= 0 && y >= 0);

					x = i;
				y = j;
				
				do 			//Going right
				{
					x++;
					if(board[x][y] == 6|| board[x][y] == 8)
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}while(board[x][y] == 0 && x < 7); //Post check allows it to check for a king first 

				x = i;
				y = j;

				do 			//Going left
				{
					x--;
					if(board[x][y] == 6|| board[x][y] == 8)
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}

				}while(board[x][y] == 0 && x > 0); //Post check allows it to check for a king first	
				

				y = j;
				x = i;
				do 			//Going down
				{
					y++;
					if(board[x][y] == 6|| board[x][y] == 8)
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}while(board[x][y] == 0 && y < 7); //Post check allows it to check for a king first 
					
				y = j;
				x = i;
				do 			//Going up
				{
					y--;
					if(board[x][y] == 6|| board[x][y] == 8)
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}while(board[x][y] == 0 && y > 0); //Post check allows it to check for a king first
				
			}

			else if (board[i][j] == -4) // bishop
			{
			  
					int x, y; // temps
					
					x = i;
					y = j;
					// Going top right
					do
					{
						y++;
						x--;
						if (y > 7 || x < 0)
							break;
						
						if (board[x][y] == 6|| board[x][y] == 8)
						{
							printf("Black Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x >= 0 && y <= 7);
						
					
					x = i;
					y = j;
					// Going Bottom Left
					do
					{
						x++;
						y--;
						// to prevent seg fault
						if (x > 7 || y < 0)
							break;
						
						if (board[x][y] == 6|| board[x][y] == 8) 
						{	
							printf("Black Team, you are in Check!\n");
							return 1;
						}

					} while (board[x][y] == 0 && x <= 7 && y >= 0);
						
						
					x = i;
					y = j;
					// Going Bottom Right
					do
					{
						x++;
						y++;
						// to prevent seg fault
						if (x > 7 || y > 7)
							break;
						
						if (board[x][y] == 6|| board[x][y] == 8) 
						{	
							printf("Black Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x <= 7 && y <= 7);
						
					x = i;
					y = j;
					// Going Top Left
					do
					{
						x--;
						y--;
						// to prevent seg fault
						if (x < 0 || y < 0)
							break;
						
						if (board[x][y] == 6|| board[x][y] == 8) 
						{	
							printf("Black Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x >= 0 && y >= 0);
				
			}


			

			else if(board[i][j] == -3) // Knight
			{
				// top left edges
				if (i == 0 && j == 0) 
				{
					// bottom right
					if(board[i+2][j+1] == 6|| board[i+2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == 6|| board[i+1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				} 
				else if (i == 0 && j == 1)
				{
					// bottom right
					if(board[i+2][j+1] == 6|| board[i+2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == 6|| board[i+1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					} 
					// bottom left 1
					else if(board[i+2][j-1] == 6|| board[i+2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 1 && j == 0) 
				{
					// bottom right
					if(board[i+2][j+1] == 6|| board[i+2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == 6||board[i+1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					} 
					// top right 1
					else if(board[i-1][j+2] == 6||board[i-1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// top right edges
				else if (i == 0 && j == 7)
				{
					// bottom left
					if(board[i+2][j-1] == 6|| board[i+2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					if(board[i+1][j-2] == 6|| board[i+1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 0 && j == 6) 
				{
					// bottom left
					if(board[i+2][j-1] == 6|| board[i+2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == 6|| board[i+1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom right 1
					else if(board[i+2][j+1] == 6|| board[i+2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 1 && j == 7)
				{
					// bottom left
					if(board[i+2][j-1] == 6|| board[i+2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == 6|| board[i+1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// top left 1
					else if(board[i-1][j-2] == 6|| board[i-1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// bottom left edges
				else if (i == 7 && j == 0)
				{
					// top right
					if(board[i-2][j+1] == 6|| board[i-2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == 6|| board[i-1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				} 
				else if (i == 6 && j == 0)
				{
					// top right
					if(board[i-2][j+1] == 6|| board[i-2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == 6|| board[i-1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom right 1
					else if(board[i+1][j+2] == 6|| board[i+1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 7 && j == 1)
				{
					// top right
					if(board[i-2][j+1] == 6|| board[i-2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == 6|| board[i-1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					} 
					// top right 1
					else if(board[i-2][j-1] == 6|| board[i-2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// bottom right edges
				else if (i == 7 && j == 7)
				{
					// top left
					if(board[i-1][j-2] == 6|| board[i-1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == 6|| board[i-2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 7 && j == 6)
				{
					// top left
					if(board[i-1][j-2] == 6|| board[i-1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == 6|| board[i-2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// top right 1
					else if(board[i-2][j+1] == 6||board[i-2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 6 && j == 7)
				{
					// top left
					if(board[i-1][j-2] == 6||board[i-1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == 6||board[i-2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					} 
					// bottom left 1
					else if(board[i+1][j-2] == 6||board[i+1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// when i == 0
				else if (i == 0 && j <= 5 && j >= 3)
				{
					// bottom left
					if(board[i+2][j-1] == 6||board[i+2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == 6||board[i+1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom right
					else if(board[i+2][j+1] == 6||board[i+2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == 6||board[i+1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// when i == 1
				else if (i == 1 && j <= 5 && j >= 3)
				{
					// bottom left
					if(board[i+2][j-1] == 6||board[i+2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == 6||board[i+1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom right
					else if(board[i+2][j+1] == 6||board[i+2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == 6||board[i+1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// top left 1
					else if(board[i-1][j-2] == 6||board[i-1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// top right 1
					else if(board[i-1][j+2] == 6||board[i-1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// when i == 7
				else if (i == 7 && j <= 5 && j >= 3) 
				{
					// top left
					if(board[i-1][j-2] == 6||board[i-1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == 6||board[i-2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}	
					// top right
					else if(board[i-2][j+1] == 6||board[i-2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == 6||board[i-1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// when i == 6
				else if (i == 6 && j <= 5 && j >= 3) 
				{
					// top left
					if(board[i-1][j-2] == 6||board[i-1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == 6||board[i-2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}	
					// top right
					else if(board[i-2][j+1] == 6||board[i-2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == 6||board[i-1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom left 1
					else if(board[i+1][j-2] == 6||board[i+1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom right 1
					else if(board[i+1][j+2] == 6||board[i+1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// when j == 0
				else if (j == 0 && i >= 2 && i <= 5)
				{
					// top right
					if(board[i-2][j+1] == 6||board[i-2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == 6||board[i-1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom right
					else if(board[i+2][j+1] == 6||board[i+2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == 6||board[i+1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// when j == 1
				else if (j == 1 && i >= 2 && i <= 5)
				{
					// top right
					if(board[i-2][j+1] == 6||board[i-2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == 6||board[i-1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom right
					else if(board[i+2][j+1] == 6||board[i+2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == 6||board[i+1][j+2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// top left 1
					else if(board[i-2][j-1] == 6||board[i-2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom left 1
					else if(board[i+2][j-1] == 6||board[i+2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// when j == 7
				else if (j == 7 && i >= 2 && i <= 5)
				{
					// top left
					if(board[i-1][j-2] == 6||board[i-1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == 6||board[i-2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom left
					else if(board[i+2][j-1] == 6||board[i+2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == 6||board[i+1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// when j == 6
				else if (j == 6 && i >= 2 && i <= 5)
				{
					// top left
					if(board[i-1][j-2] == 6||board[i-1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == 6||board[i-2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom left
					else if(board[i+2][j-1] == 6||board[i+2][j-1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == 6||board[i+1][j-2] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// top right 1
					else if(board[i-2][j+1] == 6||board[i-2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
					// bottom right 1
					else if(board[i+2][j+1] == 6||board[i+2][j+1] == 8)	//Possible Movement
					{
						printf("Black Team, you are in Check!\n");
						return 1;
					}
				}
				// the rest
				// top left
				else if(board[i-1][j-2] == 6||board[i-1][j-2] == 8)	//Possible Movement
				{
					printf("Black Team, you are in Check!\n");
					return 1;
				}
				else if(board[i-2][j-1] == 6||board[i-2][j-1] == 8)	//Possible Movement
				{
					printf("Black Team, you are in Check!\n");
					return 1;
				}
				
				// top right
				else if(board[i-2][j+1] == 6||board[i-2][j+1] == 8)	//Possible Movement
				{
					printf("Black Team, you are in Check!\n");
					return 1;
				}
				else if(board[i-1][j+2] == 6||board[i-1][j+2] == 8)	//Possible Movement
				{
					printf("Black Team, you are in Check!\n");
					return 1;
				}
				
				// bottom left
				else if(board[i+2][j-1] == 6||board[i+2][j-1] == 8)	//Possible Movement
				{
					printf("Black Team, you are in Check!\n");
					return 1;
				}
				else if(board[i+1][j-2] == 6||board[i+1][j-2] == 8)	//Possible Movement
				{
					printf("Black Team, you are in Check!\n");
					return 1;
				}
				
				// bottom right
				else if(board[i+2][j+1] == 6||board[i+2][j+1] == 8)	//Possible Movement
				{
					printf("Black Team, you are in Check!\n");
					return 1;
				}
				else if(board[i+1][j+2] == 6||board[i+1][j+2] == 8)	//Possible Movement
				{
					printf("Black Team, you are in Check!\n");
					return 1;
				}
			}
			


			
		}//Ending j For Loop
	}//Ending i For Loop
	return 0;
}//Ending Check Function




int WhiteCheck(int board[8][8])
{
	for(int i=0; i<8; i++)		//Row
	{
		for(int j=0; j<8; j++)		//Column
		{
			if(board[i][j] == 1||board[i][j] == 10) //Pawn
			{
				// to prevent seg fault
				if (i < 7 && j < 7) 	
				{
					if(board[i+1][j+1] == -6||board[i+1][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// to prevent seg fault
				else if (i < 7 && j > 0)		
				{
					if (board[i+1][j-1] == -6||board[i+1][j-1] == -8)	//Another possible movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
			}



			else if (board[i][j] == 2) //Rook (vertical and Horizontal)
			{
			  int x;
			  int y;

			  x = i;
			  y = j;
				do 			//Going right
				{
					x++;
					if(board[x][y] == -6||board[x][y] == -8)
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}while(board[x][y] == 0 && x < 7); //Post check allows it to check for a king first 

				x = i;
				y = j;
				do 			//Going left
				{
					x--;
					if(board[x][y] == -6||board[x][y] == -8)
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}

				}while(board[x][j] == 0 && x > 0); //Post check allows it to check for a king first 
 
					
				y = j;
				x = i;
				do 			//Going down
				{
					y++;
					if(board[x][y] == -6||board[x][y] == -8)
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}while(board[x][y] == 0 && y < 7); //Post check allows it to check for a king first 
					
				y = j;
				x = i;
				do 			//Going up
				{
					y--;
					if(board[x][y] == -6||board[x][y] == -8)
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}while(board[x][y] == 0 && y > 0); //Post check allows it to check for a king first


			}

			else if (board[i][j] == 5) //queen
			{
					int x, y; // temps
					
					x = i;
					y = j;
					// Going top right
					do
					{
						y++;
						x--;
						if (y > 7 || x < 0)
							break;
						
						if (board[x][y] == -6||board[x][y] == -8)
						{
							printf("White Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x >= 0 && y <= 7);
						
					
					x = i;
					y = j;
					// Going Bottom Left
					do
					{
						x++;
						y--;
						// to prevent seg fault
						if (x > 7 || y < 0)
							break;
						
						if (board[x][y] == -6||board[x][y] == -8) 
						{	
							printf("White Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x >= 0 && y <= 7);

						
					x = i;
					y = j;
					// Going Bottom Right
					do
					{
						x++;
						y++;
						// to prevent seg fault
						if (x > 7 || y > 7)
							break;
						
						if (board[x][y] == -6||board[x][y] == -8) 
						{	
							printf("White Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x <= 7 && y <= 7);
						
					x = i;
					y = j;
					// Going Top Left
					do
					{
						x--;
						y--;
						// to prevent seg fault
						if (x < 0 || y < 0)
							break;
						
						if (board[x][y] == -6||board[x][y] == -8) 
						{	
							printf("White Team, you are in Check!\n");
							return 1;
						}
						
					}while (board[x][y] == 0 && x >= 0 && y >= 0);
					
					 x = i;
					 y = j;
					 do 			//Going right
					 {
					     x++;
					     if(board[x][y] == -6||board[x][y] == -8)
					       {
						 printf("White Team, you are in Check!\n");
						 return 1;
					       }
					 }while(board[x][y] == 0 && x < 7); //Post check allows it to check for a king first 

					 x = i;
					 y = j;
					 do 			//Going left
					 {
					     x--;
					     if(board[x][y] == -6||board[x][y] == -8)
					       {
						 printf("White Team, you are in Check!\n");
						 return 1;
					       }

					 }while(board[x][j] == 0 && x > 0); //Post check allows it to check for a king first 
 
					
					 y = j;
					 x = i;
					 do 			//Going down
					 {
					   y++;
					   if(board[x][y] == -6||board[x][y] == -8)
					   {
					     printf("White Team, you are in Check!\n");
					     return 1;
					   }
					 }while(board[x][y] == 0 && y < 7); //Post check allows it to check for a king first 
					
					 y = j;
					 x = i;
					 do 			//Going up
					   {
					     y--;
					     if(board[x][y] == -6||board[x][y] == -8)
					       {
						 printf("White Team, you are in Check!\n");
						 return 1;
					       }
					   }while(board[x][y] == 0 && y > 0); //Post check allows it to check for a king first

				
			}
			
			else if (board[i][j] == 4) // bishop
			{
					int x, y; // temps
					
					x = i;
					y = j;
					// Going top right
					do
					{
						y++;
						x--;
						if (y > 7 || x < 0)
							break;
						
						if (board[x][y] == -6||board[x][y] == -8)
						{
							printf("White Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x >= 0 && y <= 7);
						
					
					x = i;
					y = j;
					// Going Bottom Left
					do
					{
						x++;
						y--;
						// to prevent seg fault
						if (x > 7 || y < 0)
							break;
						
						if (board[x][y] == -6||board[x][y] == -8) 
						{	
							printf("White Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x >= 0 && y <= 7);

						
					x = i;
					y = j;
					// Going Bottom Right
					do
					{
						x++;
						y++;
						// to prevent seg fault
						if (x > 7 || y > 7)
							break;
						
						if (board[x][y] == -6||board[x][y] == -8) 
						{	
							printf("White Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x <= 7 && y <= 7);
						
					x = i;
					y = j;
					// Going Top Left
					do
					{
						x--;
						y--;
						// to prevent seg fault
						if (x < 0 || y < 0)
							break;
						
						if (board[x][y] == -6||board[x][y] == -8) 
						{	
							printf("White Team, you are in Check!\n");
							return 1;
						}
						
					} while (board[x][y] == 0 && x >= 0 && y >= 0);

				
			}

			else if(board[i][j] == 3) // Knight
			{
				// top left edges
				if (i == 0 && j == 0) 
				{
					// bottom right
					if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				} 
				else if (i == 0 && j == 1)
				{
					// bottom right
					if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					} 
					// bottom left 1
					else if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 1 && j == 0) 
				{
					// bottom right
					if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					} 
					// top right 1
					else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// top right edges
				else if (i == 0 && j == 7)
				{
					// bottom left
					if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 0 && j == 6) 
				{
					// bottom left
					if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom right 1
					else if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 1 && j == 7)
				{
					// bottom left
					if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// top left 1
					else if(board[i-1][j-2] == -6||board[i-1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// bottom left edges
				else if (i == 7 && j == 0)
				{
					// top right
					if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				} 
				else if (i == 6 && j == 0)
				{
					// top right
					if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom right 1
					else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 7 && j == 1)
				{
					// top right
					if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					} 
					// top right 1
					else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// bottom right edges
				else if (i == 7 && j == 7)
				{
					// top left
					if(board[i-1][j-2] == -6||board[i-1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 7 && j == 6)
				{
					// top left
					if(board[i-1][j-2] == -6||board[i-1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// top right 1
					else if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				else if (i == 6 && j == 7)
				{
					// top left
					if(board[i-1][j-2] == -6||board[i-1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					} 
					// bottom left 1
					else if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// when i == 0
				else if (i == 0 && j <= 5 && j >= 3)
				{
					// bottom left
					if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom right
					else if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// when i == 1
				else if (i == 1 && j <= 5 && j >= 3)
				{
					// bottom left
					if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom right
					else if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// top left 1
					else if(board[i-1][j-2] == -6||board[i-1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// top right 1
					else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// when i == 7
				else if (i == 7 && j <= 5 && j >= 3) 
				{
					// top left
					if(board[i-1][j-2] == -6||board[i-1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}	
					// top right
					else if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// when i == 6
				else if (i == 6 && j <= 5 && j >= 3) 
				{
					// top left
					if(board[i-1][j-2] == -6||board[i-1][j-2] -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}	
					// top right
					else if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom left 1
					else if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom right 1
					else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// when j == 0
				else if (j == 0 && i >= 2 && i <= 5)
				{
					// top right
					if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom right
					else if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// when j == 1
				else if (j == 1 && i >= 2 && i <= 5)
				{
					// top right
					if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom right
					else if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// top left 1
					else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom left 1
					else if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// when j == 7
				else if (j == 7 && i >= 2 && i <= 5)
				{
					// top left
					if(board[i-1][j-2] == -6||board[i-1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom left
					else if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// when j == 6
				else if (j == 6 && i >= 2 && i <= 5)
				{
					// top left
					if(board[i-1][j-2] == -6||board[i-1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom left
					else if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					else if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// top right 1
					else if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
					// bottom right 1
					else if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
					{
						printf("White Team, you are in Check!\n");
						return 1;
					}
				}
				// the rest
				// top left
				else if(board[i-1][j-2] == -6||board[i-1][j-2] == -8)	//Possible Movement
				{
					printf("White Team, you are in Check!\n");
					return 1;
				}
				else if(board[i-2][j-1] == -6||board[i-2][j-1] == -8)	//Possible Movement
				{
					printf("White Team, you are in Check!\n");
					return 1;
				}
				
				// top right
				else if(board[i-2][j+1] == -6||board[i-2][j+1] == -8)	//Possible Movement
				{
					printf("White Team, you are in Check!\n");
					return 1;
				}
				else if(board[i-1][j+2] == -6||board[i-1][j+2] == -8)	//Possible Movement
				{
					printf("White Team, you are in Check!\n");
					return 1;
				}
				
				// bottom left
				else if(board[i+2][j-1] == -6||board[i+2][j-1] == -8)	//Possible Movement
				{
					printf("White Team, you are in Check!\n");
					return 1;
				}
				else if(board[i+1][j-2] == -6||board[i+1][j-2] == -8)	//Possible Movement
				{
					printf("White Team, you are in Check!\n");
					return 1;
				}
				
				// bottom right
				else if(board[i+2][j+1] == -6||board[i+2][j+1] == -8)	//Possible Movement
				{
					printf("White Team, you are in Check!\n");
					return 1;
				}
				else if(board[i+1][j+2] == -6||board[i+1][j+2] == -8)	//Possible Movement
				{
					printf("White Team, you are in Check!\n");
					return 1;
				}
			}
			
		}//Ending j For Loop
	}//Ending i For Loop
	return 0;
}//Ending Check Function

// 0 == false
// 1 == true
// black pieces are positive
// white pieces are negative

int getCheckMate(int board[8][8], char team)
{
	if (team == 'w') 
	{
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				// as soon as one possible move is found for the king
				if (board[i][j] == -6 || board[i][j] == -8)
				{
					// case where a piece can block the check piece
					if (anotherCase(board, team, i, j) == 1)
						return 0;
					
					int temp1 = i;
					int temp2 = j;
					// examine each position, there is at most 8 possibilities
					// 1
					temp1 += 1;
					temp2 += 1;
					if (temp1 <= 7 && temp2 <= 7)
					{
						// if king can move 
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
							{
								return 0; // means not checkmate
							}
						}
						// if opponent's piece, if capture is possible
						if (board[temp1][temp2] > 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					} 
					// 2
					temp1 = i+1;
					temp2 = j;
					if (temp1 <= 7)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
							{
								return 0; // means not checkmate
							}
						}
						// if opponent's piece, if capture is possible
						if (board[temp1][temp2] > 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 3
					temp1 = i+1;
					temp2 = j-1;
					if (temp1 <= 7 && temp2 >= 0)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
							{
								return 0; // means not checkmate
							}
						}
						// if opponent's piece, if capture is possible
						if (board[temp1][temp2] > 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 4
					temp1 = i;
					temp2 = j-1;
					if (temp2 >= 0)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
							{
								return 0; // means not checkmate
							}
						}
						// if opponent's piece, if capture is possible
						if (board[temp1][temp2] > 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 5
					temp1 = i-1;
					temp2 = j-1;
					if (temp1 >= 0 && temp2 >= 0)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
							{
								return 0; // means not checkmate
							}
						}
						// if opponent's piece, if capture is possible
						if (board[temp1][temp2] > 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 6
					temp1 = i-1;
					temp2 = j;
					if (temp1 >= 0)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
							{		
								return 0; // means not checkmate
							}
						}
						// if opponent's piece, if capture is possible
						if (board[temp1][temp2] > 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 7
					temp1 = i-1;
					temp2 = j+1;
					if (temp1 >= 0 && temp2 <= 7)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
							{
								return 0; // means not checkmate
							}
						}
						// if opponent's piece, if capture is possible
						if (board[temp1][temp2] > 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 8
					temp1 = i;
					temp2 = j+1;
					if (temp2 <= 7)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
							{
								return 0; // means not checkmate
							}
						}
						// if opponent's piece, if capture is possible
						if (board[temp1][temp2] > 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
				}
			}
		}
	}
	else if (team == 'b') 
	{
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (board[i][j] == 6 || board[i][j] == 8)
				{
					// case where a piece can block the check piece
					if (anotherCase(board, team, i, j) == 1)
						return 1;
					int temp1 = i;
					int temp2 = j;
					// examine each position, there is at most 8 possibilities
					// 1
					temp1 += 1;
					temp2 += 1;
					if (temp1 <= 7 && temp2 <= 7)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
								return 0; // means not checkmate
						}
						// if opponent's piece, if capture is possible
						if (board[temp1][temp2] < 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 2
					temp1 = i+1;
					temp2 = j;
					if (temp1 <= 7)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
								return 0; // means not checkmate
						}
						if (board[temp1][temp2] < 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 3
					temp1 = i+1;
					temp2 = j-1;
					if (temp1 <= 7 && temp2 >= 0)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
								return 0; // means not checkmate
						}
						if (board[temp1][temp2] < 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 4
					temp1 = i;
					temp2 = j-1;
					if (temp2 >= 0)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
								return 0; // means not checkmate
						}
						if (board[temp1][temp2] < 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 5
					temp1 = i-1;
					temp2 = j-1;
					if (temp1 >= 0 && temp2 >= 0)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
								return 0; // means not checkmate
						}
						if (board[temp1][temp2] < 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 6
					temp1 = i-1;
					temp2 = j;
					if (temp1 >= 0)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
								return 0; // means not checkmate
						}
						if (board[temp1][temp2] < 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 7
					temp1 = i-1;
					temp2 = j+1;
					if (temp1 >= 0 && temp2 <= 7)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
								return 0; // means not checkmate
						}
						if (board[temp1][temp2] < 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
					// 8
					temp1 = i;
					temp2 = j+1;
					if (temp2 <= 7)
					{
						if (board[temp1][temp2] == 0)
						{
							if (checkPos(board, team, temp1, temp2) == 0)
								return 0; // means not checkmate
						}
						if (board[temp1][temp2] < 0)
						{
							if (kingCapture(board, team, temp1, temp2) == 0)
								return 0;
						}
					}
				}
			}
		}
	}
	
	return 2; // means checkmate
}

int checkPos(int board[8][8], char team, int x, int y)
{
	if (team == 'w') // have to check opponent's possible movements, so the black pieces
	{
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (board[i][j] == 0)
					;
				// if pawns can attack at x,y
				else if (board[i][j] == 1 || board[i][j] == 10)
				{
					if (i+1 <= 7 && j+1 <= 7)
					{
						if (i+1 == x && j+1 == y)
							return 1; // means attack is possible at x,y
					} 
					if (i+1 <= 7 && j-1 >= 0)
					{
						if (i+1 == x && j-1 == y)
							return 1;
					}
				}
				// if rook or queen can attack at x,y
				else if (board[i][j] == 2 || board[i][j] == 5 || board[i][j] == 7 || board[i][j] == 17)
				{
					// to the right
					int z = j+1;
					while (board[i][z] == 0 && z <= 7) 
					{
						if (i == x && z == y)
							return 1;
						else if (z+1 <= 7)
						{
							if (board[i][z+1] == -6 && i == x && z+2 == y) // if position is a posible move for rook
								return 1;
						}
						z++; // keep moving to the right
					}
					// to the left
					z = j-1;
					while (board[i][z] == 0 && z >= 0) 
					{
						if (i == x && z == y)
							return 1;
						else if (z-1 >= 0)
						{
							if (board[i][z-1] == -6 && i == x && z-2 == y) // if position is a posible move for rook
								return 1;
						}
						z--; // keep moving to the left
					}
					// moving down
					z = i+1;
					while (board[z][j] == 0 && z <= 7) 
					{
						if (z == x && j == y)
							return 1;
						else if (z+1 <= 7)
						{
							if (board[z+1][j] == -6 && z+2 == x && j == y) // if position is a posible move for rook
								return 1;
						}
						z++; // keep moving down
					}
					// moving up
					z = i-1;
					while (board[z][j] == 0 && z >= 0) 
					{
						if (z == x && j == y)
							return 1;
						else if (z-1 >= 0)
						{
							if (board[z-1][j] == -6 && z-2 == x && j == y) // if position is a posible move for rook and queen
								return 1;
						}
						z--; // keep moving to up
					}
				}
				// bishop and queen
				if (board[i][j] == 4 || board[i][j] == 5)
				{
					int t1 = i;
					int t2 = j;
					// left to right up
					t1--;
					t2++;
					while (t1 >= 0 && t2 <= 7 && board[t1][t2] == 0)
					{
						if (t1 == x && t2 == y)
							return 1;
						else if (t1-1 >= 0 && t2+1 <= 7)
						{
							if (board[t1-1][t2+1] == -6 && t1-2 == x && t2+2 == y) // posible move for queen and bishop
								return 1;
						}
						t1--;
						t2++;
					}
					// left to right down
					t1 = i;
					t2 = j;
					t1++;
					t2--;
					while (t1 <= 7 && t2 >= 0 && board[t1][t2] == 0)
					{
						if (t1 == x && t2 == y)
							return 1;
						else if (t2-1 >= 0 && t1+1 <= 7)
						{
							if (board[t1+1][t2-1] == -6 && t1+2 == x && t2-2 == y) // posible move for queen and bishop
								return 1;
						}
						t1++;
						t2--;
					}
					// right to left up
					t1 = i;
					t2 = j;
					t1--;
					t2--;
					while (t1 >= 0 && t2 >= 0 && board[t1][t2] == 0)
					{
						if (t1 == x && t2 == y)
							return 1;
						else if (t2-1 >= 0 && t1-1 >= 0)
						{
							if (board[t1-1][t2-1] == -6 && t1-2 == x && t2-2 == y) // posible move for queen and bishop
								return 1;
						}
						t1--;
						t2--;
					}
					// right to left down
					t1 = i;
					t2 = j;
					t1++;
					t2++;
					while (t1 <= 7 && t2 <= 7 && board[t1][t2] == 0)
					{
						if (t1 == x && t2 == y)
							return 1;
						else if (t2+1 <= 7 && t1+1 <= 7)
						{
							if (board[t1+1][t2+1] == -6 && t1+2 == x && t2+2 == y) // posible move for queen and bishop
								return 1;
						}
						t1++;
						t2++;
					}
				}
				// knight
				else if (board[i][j] == 3)
				{
					// all possible attacks
					if (i-1 == x && j-2 == y)
						return 1;
					else if (i-2 == x && j-1 == y)
						return 1;
					else if (i-2 == x && j+1 == y)
						return 1;
					else if (i-1 == x && j+2 == y)
						return 1;
					else if (i+2 == x && j-1 == y)
						return 1;
					else if (i+1 == x && j-2 == y)
						return 1;
					else if (i+2 == x && j+1 == y)
						return 1;
					else if (i+1 == x && j+2 == y)
						return 1;
				}
			}
		}
	}
	else if (team == 'b')
	{
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (board[i][j] == 0)
					;
				// if pawns can attack at x,y
				else if (board[i][j] == -1 || board[i][j] == -10)
				{
					if (i-1 >= 0 && j+1 <= 7)
					{
						if (i-1 == x && j+1 == y)
							return 1; // means attack is possible at x,y
					}	 
					if (i-1 >= 0 && j-1 >= 0)
					{
						if (i-1 == x && j-1 == y)
							return 1;
					}
				}
				// if rook or queen can attack at x,y
				else if (board[i][j] == -2 || board[i][j] == -5 || board[i][j] == -7 || board[i][j] == -17)
				{
					// to the right
					int z = j+1;
					while (board[i][z] == 0 && z <= 7) 
					{
						if (i == x && z == y)
							return 1;
						else if (z+1 <= 7)
						{
							if (board[i][z+1] == 6 && i == x && z+2 == y) // if position is a posible move for rook
								return 1;
						}
						z++; // keep moving to the right
					}
					// to the left
					z = j-1;
					while (board[i][z] == 0 && z >= 0) 
					{
						if (i == x && z == y)
							return 1;
						else if (z-1 >= 0)
						{
							if (board[i][z-1] == 6 && i == x && z-2 == y) // if position is a posible move for rook
								return 1;
						}
						z--; // keep moving to the left
					}
					// moving down
					z = i+1;
					while (board[z][j] == 0 && z <= 7) 
					{
						if (z == x && j == y)
							return 1;
						else if (z+1 <= 7)
						{
							if (board[z+1][j] == 6 && z+2 == x && j == y) // if position is a posible move for rook
								return 1;
						}
						z++; // keep moving to the down
					}
					// moving up
					z = i-1;
					while (board[z][j] == 0 && z >= 0) 
					{
						if (z == x && j == y)
							return 1;
						else if (z-1 >= 0)
						{
							if (board[z-1][j] == 6 && z-2 == x && j == y) // if position is a posible move for rook
								return 1;
						}
						z--; // keep moving to the down
					}
				}
				// bishop and queen
				if (board[i][j] == -4 || board[i][j] == -5)
				{
					int t1 = i;
					int t2 = j;
					// left to right up
					t1--;
					t2++;
					while (t1 >= 0 && t2 <= 7 && board[t1][t2] == 0)
					{
						if (t1 == x && t2 == y)
							return 1;
						else if (t1-1 >= 0 && t2+1 <= 7)
						{
							if (board[t1-1][t2+1] == 6 && t1-2 == x && t2+2 == y) // posible move for queen and bishop
								return 1;
						}
						t1--;
						t2++;
					}
					// left to right down
					t1 = i;
					t2 = j;
					t1++;
					t2--;
					while (t1 <= 7 && t2 >= 0 && board[t1][t2] == 0)
					{
						if (t1 == x && t2 == y)
							return 1;
						else if (t2-1 >= 0 && t1+1 <= 7)
						{
							if (board[t1+1][t2-1] == 6 && t1+2 == x && t2-2 == y) // posible move for queen and bishop
								return 1;
						}
						t1++;
						t2--;
					}
					// right to left up
					t1 = i;
					t2 = j;
					t1--;
					t2--;
					while (t1 >= 0 && t2 >= 0 && board[t1][t2] == 0)
					{
						if (t1 == x && t2 == y)
							return 1;
						else if (t2-1 >= 0 && t1-1 >= 0)
						{
							if (board[t1-1][t2-1] == 6 && t1-2 == x && t2-2 == y) // posible move for queen and bishop
								return 1;
						}
						t1--;
						t2--;
					}
					// right to left down
					t1 = i;
					t2 = j;
					t1++;
					t2++;
					while (t1 <= 7 && t2 <= 7 && board[t1][t2] == 0)
					{
						if (t1 == x && t2 == y)
							return 1;
						else if (t2+1 <= 7 && t1+1 <= 7)
						{
							if (board[t1+1][t2+1] == 6 && t1+2 == x && t2+2 == y) // posible move for queen and bishop
								return 1;
						}
						t1++;
						t2++;
					}
				}
				// knight
				else if (board[i][j] == -3)
				{
					// all possible attacks
					if (i-1 == x && j-2 == y)
						return 1;
					else if (i-2 == x && j-1 == y)
						return 1;
					else if (i-2 == x && j+1 == y)
						return 1;
					else if (i-1 == x && j+2 == y)
						return 1;
					else if (i+2 == x && j-1 == y)
						return 1;
					else if (i+1 == x && j-2 == y)
						return 1;
					else if (i+2 == x && j+1 == y)
						return 1;
					else if (i+1 == x && j+2 == y)
						return 1;
				}
			}
		}
	}
	
	// means attack is not possible at x,y
	return 0;
}
// return 1 means king can't capture
// return 0 means king can capture
int kingCapture(int board[8][8], char team, int x, int y)
{
	if (team == 'w') // check BLACK PIECE, which are positive
	{
		// go thru the whole loop and check each positive piece can go to x,y
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				// if empty do nothing
				if (board[i][j] == 0)
					;
				else if (i == x && j == y)
					;
				// if pawns can attack at x,y
				else if (board[i][j] == 1 || board[i][j] == 10)
				{
					if (i+1 <= 7 && j+1 <= 7)
					{
						if (board[i+1][j+1] > 0 && i+1 == x && j+1 == y)
							return 1; // means attack is possible at x,y
					} 
					if (i+1 <= 7 && j-1 >= 0)
					{
						if (board[i+1][j+1] > 0 && i+1 == x && j-1 == y)
							return 1;
					}
				}
				// if rook or queen can attack at x,y
				else if (board[i][j] == 2 || board[i][j] == 5 || board[i][j] == 7 || board[i][j] == 17)
				{
					// to the right
					int z = j;
					do
					{
						z++;
						if (z > 7)
							break;
			
						if (board[i][z] > 0 && i == x && z == y)
							return 1;
							
					} while (board[i][z] == 0 && z <= 7);
					// to the left
					z = j;
					do
					{
						z--;
						if (z < 0)
							break;
			
						if (board[i][z] > 0 && i == x && j == y)
							return 1;
							
					} while (board[i][z] == 0 && z >= 0);
					
					// moving down
					z = i;
					do
					{
						z++;
						if (z > 7)
							break;
			
						if (board[i][z] > 0 && i == x && y == z)
							return 1;
							
					} while (board[i][z] == 0 && z <= 7);
					
					// moving up
					z = i;
					do
					{
						z--;
						if (z < 0)
							break;
						if (board[i][z] > 0 && i == x && y == z)
							return 1;
					} while (board[i][z] == 0 && z >= 0);	
				}
				// bishop and queen
				if (board[i][j] == 4 || board[i][j] == 5)
				{
					int t1 = i;
					int t2 = j;
					// left to right up
					do 
					{
						t1--;
						t2++;
						if (t1 < 0 || t2 > 7)
							break;
						if (board[t1][t2] > 0 && t1 == x && t2 == y)
							return 1;
					} while (board[t1][t2] == 0 && t1 >= 0 && t2 <= 7);
					// left to right down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2--;
						if (t1 > 7 || t2 < 0)
							break;
						if (board[t1][t2] > 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 <= 7 && t2 >= 0 && board[t1][t2] == 0);
					// right to left up
					t1 = i;
					t2 = j;
					do 
					{
						t1--;
						t2--;
						if (t1 < 0 || t2 < 0)
							break;
						if (board[t1][t2] > 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 >= 0 && t2 >= 0 && board[t1][t2] == 0);
					// right to left down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2++;
						if (t1 > 7 || t2 > 7)
							break;
						if (board[t1][t2] > 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 <= 7 && t2 <= 7 && board[t1][t2] == 0);
				}
				// knight
				else if (board[i][j] == 3)
				{
					// all possible attacks
					if (i-1 == x && j-2 == y && board[i-1][j-2] > 0)
						return 1;
					else if (i-2 == x && j-1 == y && board[i-2][j-1] > 0)
						return 1;
					else if (i-2 == x && j+1 == y && board[i-2][j+1] > 0)
						return 1;
					else if (i-1 == x && j+2 == y && board[i-1][j+2] > 0)
						return 1;
					else if (i+2 == x && j-1 == y && board[i+2][j-1] > 0)
						return 1;
					else if (i+1 == x && j-2 == y && board[i+1][j-2] > 0)
						return 1;
					else if (i+2 == x && j+1 == y && board[i+2][j+1] > 0)
						return 1;
					else if (i+1 == x && j+2 == y && board[i+1][j+2] > 0)
						return 1;
				}
				
			}
		}
	}
	else if (team == 'b') // check BLACK PIECE, which are positive
	{
		// go thru the whole loop and check each positive piece can go to x,y
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				// if empty do nothing
				if (board[i][j] == 0)
					;
				else if (i == x && j == y)
					;
				// if pawns can attack at x,y
				else if (board[i][j] == -1 || board[i][j] == -10)
				{
					if (i-1 <= 7 && j+1 <= 7)
					{
						if (board[i+1][j+1] < 0 && i+1 == x && j+1 == y)
							return 1; // means attack is possible at x,y
					} 
					if (i-1 <= 7 && j-1 >= 0)
					{
						if (board[i+1][j+1] < 0 && i+1 == x && j-1 == y)
							return 1;
					}
				}
				// if rook or queen can attack at x,y
				else if (board[i][j] == -2 || board[i][j] == -5 || board[i][j] == -7 || board[i][j] == -17)
				{
					// to the right
					int z = j;
					do
					{
						z++;
						if (z > 7)
							break;
			
						if (board[i][z] < 0 && i == x && y == z)
							return 1;
							
					} while (board[i][z] == 0 && z <= 7);
					
					
					// to the left
					z = j;
					do
					{
						z--;
						if (z < 0)
							break;
						if (board[i][z] < 0 && i == x && y == z)
							return 1;
					} while (board[i][z] == 0 && z >= 0);
					// moving down
					z = i;
					do
					{
						z++;
						if (z > 7)
							break;
						if (board[i][z] < 0 && i == x && y == z)
							return 1;
					} while (board[i][z] == 0 && z <= 7);
					// moving up
					z = i;
					do
					{
						z--;
						if (z < 0)
							break;
						if (board[i][z] < 0 && i == x && y == z)
							return 1;
					} while (board[i][z] == 0 && z >= 0);	
				}
				// bishop and queen
				if (board[i][j] == -4 || board[i][j] == -5)
				{
					int t1 = i;
					int t2 = j;
					// left to right up
					do 
					{
						t1--;
						t2++;
						if (t1 < 0 || t2 > 7)
							break;
						if (board[t1][t2] < 0 && t1 == x && t2 == y)
							return 1;
					} while (board[t1][t2] == 0 && t1 >= 0 && t2 <= 7);
					// left to right down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2--;
						if (t1 > 7 || t2 < 0)
							break;
						if (board[t1][t2] < 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 <= 7 && t2 >= 0 && board[t1][t2] == 0);
					// right to left up
					t1 = i;
					t2 = j;
					do 
					{
						t1--;
						t2--;
						if (t1 < 0 || t2 < 0)
							break;
						if (board[t1][t2] < 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 >= 0 && t2 >= 0 && board[t1][t2] == 0);
					// right to left down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2++;
						if (t1 > 7 || t2 > 7)
							break;
						if (board[t1][t2] < 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 <= 7 && t2 <= 7 && board[t1][t2] == 0);
				}
				// knight
				else if (board[i][j] == -3)
				{
					// all possible attacks
					if (i-1 == x && j-2 == y && board[i-1][j-2] < 0)
						return 1;
					else if (i-2 == x && j-1 == y && board[i-2][j-1] < 0)
						return 1;
					else if (i-2 == x && j+1 == y && board[i-2][j+1] < 0)
						return 1;
					else if (i-1 == x && j+2 == y && board[i-1][j+2] < 0)
						return 1;
					else if (i+2 == x && j-1 == y && board[i+2][j-1] < 0)
						return 1;
					else if (i+1 == x && j-2 == y && board[i+1][j-2] < 0)
						return 1;
					else if (i+2 == x && j+1 == y && board[i+2][j+1] < 0)
						return 1;
					else if (i+1 == x && j+2 == y && board[i+1][j+2] < 0)
						return 1;
				}
			}
		}
	}
	
	
	return 0; // means king can capture
}

int anotherCase(int board[8][8], char team, int x, int y)
{
	if (team == 'w') // check if black pieces can check the white king
	{
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (board[i][j] == 0)
					;
				else if (i == x && j == y)
					;
				else if (board[i][j] == 2 || board[i][j] == 5 || board[i][j] == 7 || board[i][j] == 17)
				{
					// if check is possible
					// to the right
					int z = j;
					do
					{
						z++;
						if (z > 7)
							break;
						if (i == x && y == z) // if check
						{
							for (int f = j; f < z; f++)
							{
								if (anotherCaseHelper(board, team, i, f) == 1)  // if block is possible
									return 1; // block is possible
							}
						}
					} while (board[i][z] == 0 && z <= 7);
					// to the left
					z = j;
					do
					{
						z--;
						if (z < 0)
							break;
						if (i == x && y == z) // if check
						{
							for (int f = j; f > z; f--)
							{
								if (anotherCaseHelper(board, team, i, f) == 1)  // if block is possible
									return 1; // block is possible
							}
						}	
					} while (board[i][z] == 0 && z >= 0);
					// moving down
					z = i;
					do
					{
						z++;
						if (z > 7)
							break;
						if (i == x && y == z) // if check
						{
							for (int f = i; f < z; f++)
							{
								if (anotherCaseHelper(board, team, f, j) == 1)  // if block is possible
									return 1; // block is possible
							}
						}	
					} while (board[z][j] == 0 && z <= 7);
					// moving up
					z = i;
					do
					{
						z--;
						if (z < 0)
							break;
						if (i == x && y == z) // if check
						{
							for (int f = i; f > z; f--)
							{
								if (anotherCaseHelper(board, team, f, j) == 1)  // if block is possible
									return 1; // block is possible
							}
						}	
					} while (board[z][j] == 0 && z >= 0);	
				}
				// bishop and queen
				if (board[i][j] == 4 || board[i][j] == 5)
				{
					int t1 = i;
					int t2 = j;
					// left to right up
					do 
					{
						t1--;
						t2++;
						if (t1 < 0 || t2 > 7)
							break;
						if (t1 == x && t2 == y) // if check
						{
							for (int f = i; f > t1; f--)
							{
								for (int k = j; k < t2; k++)
								{
									if (anotherCaseHelper(board, team, f, k) == 1) // if block is possible
										return 1;
								}
							}
						}
					} while (board[t1][t2] == 0 && t1 >= 0 && t2 <= 7);
					// left to right down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2--;
						if (t1 > 7 || t2 < 0)
							break;
						if (t1 == x && t2 == y) // if check
						{
							for (int f = i; f < t1; f++)
							{
								for (int k = j; k > t2; k--)
								{
									if (anotherCaseHelper(board, team, f, k) == 1) // if block is possible
										return 1;
								}
							}
						}
					} while (t1 <= 7 && t2 >= 0 && board[t1][t2] == 0);
					// right to left up
					t1 = i;
					t2 = j;
					do 
					{
						t1--;
						t2--;
						if (t1 < 0 || t2 < 0)
							break;
						if (t1 == x && t2 == y) // if check
						{
							for (int f = i; f > t1; f--)
							{
								for (int k = j; k > t2; k--)
								{
									if (anotherCaseHelper(board, team, f, k) == 1) // if block is possible
										return 1;
								}
							}
						}
					} while (t1 >= 0 && t2 >= 0 && board[t1][t2] == 0);
					// right to left down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2++;
						if (t1 > 7 || t2 > 7)
							break;
						if (t1 == x && t2 == y) // if check
						{
							for (int f = i; f < t1; f++)
							{
								for (int k = j; k < t2; k++)
								{
									if (anotherCaseHelper(board, team, f, k) == 1) // if block is possible
										return 1;
								}
							}
						}
					} while (t1 <= 7 && t2 <= 7 && board[t1][t2] == 0);
				}
				// knight
				else if (board[i][j] == 3)
				{
					// all possible attacks
					if (i-1 == x && j-2 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i-2 == x && j-1 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i-2 == x && j+1 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i-1 == x && j+2 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i+2 == x && j-1 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i+1 == x && j-2 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i+2 == x && j+1 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i+1 == x && j+2 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
				}
			}		
		}
	}
	else if (team == 'b') // check if black pieces can check the white king
	{
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (board[i][j] == 0)
					;
				else if (i == x && j == y)
					;
				else if (board[i][j] == -2 || board[i][j] == -5 || board[i][j] == -7 || board[i][j] == -17)
				{
					// if check is possible
					// to the right
					int z = j;
					do
					{
						z++;
						if (z > 7)
							break;
						if (i == x && y == z) // if check
						{
							for (int f = j; f < z; f++)
							{
								if (anotherCaseHelper(board, team, i, f) == 1)  // if block is possible
									return 1; // block is possible
							}
						}
					} while (board[i][z] == 0 && z <= 7);
					// to the left
					z = j;
					do
					{
						z--;
						if (z < 0)
							break;
						if (i == x && y == z) // if check
						{
							for (int f = j; f > z; f--)
							{
								if (anotherCaseHelper(board, team, i, f) == 1)  // if block is possible
									return 1; // block is possible
							}
						}	
					} while (board[i][z] == 0 && z >= 0);
					// moving down
					z = i;
					do
					{
						z++;
						if (z > 7)
							break;
						if (i == x && y == z) // if check
						{
							for (int f = i; f < z; f++)
							{
								if (anotherCaseHelper(board, team, f, j) == 1)  // if block is possible
									return 1; // block is possible
							}
						}	
					} while (board[z][j] == 0 && z <= 7);
					// moving up
					z = i;
					do
					{
						z--;
						if (z < 0)
							break;
						if (i == x && y == z) // if check
						{
							for (int f = i; f > z; f--)
							{
								if (anotherCaseHelper(board, team, f, j) == 1)  // if block is possible
									return 1; // block is possible
							}
						}	
					} while (board[z][j] == 0 && z >= 0);	
				}
				// bishop and queen
				if (board[i][j] == -4 || board[i][j] == -5)
				{
					int t1 = i;
					int t2 = j;
					// left to right up
					do 
					{
						t1--;
						t2++;
						if (t1 < 0 || t2 > 7)
							break;
						if (t1 == x && t2 == y) // if check
						{
							for (int f = i; f > t1; f--)
							{
								for (int k = j; k < t2; k++)
								{
									if (anotherCaseHelper(board, team, f, k) == 1) // if block is possible
										return 1;
								}
							}
						}
					} while (board[t1][t2] == 0 && t1 >= 0 && t2 <= 7);
					// left to right down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2--;
						if (t1 > 7 || t2 < 0)
							break;
						if (t1 == x && t2 == y) // if check
						{
							for (int f = i; f < t1; f++)
							{
								for (int k = j; k > t2; k--)
								{
									if (anotherCaseHelper(board, team, f, k) == 1) // if block is possible
										return 1;
								}
							}
						}
					} while (t1 <= 7 && t2 >= 0 && board[t1][t2] == 0);
					// right to left up
					t1 = i;
					t2 = j;
					do 
					{
						t1--;
						t2--;
						if (t1 < 0 || t2 < 0)
							break;
						if (t1 == x && t2 == y) // if check
						{
							for (int f = i; f > t1; f--)
							{
								for (int k = j; k > t2; k--)
								{
								if (anotherCaseHelper(board, team, f, k) == 1) // if block is possible
										return 1;
								}
							}
						}
					} while (t1 >= 0 && t2 >= 0 && board[t1][t2] == 0);
					// right to left down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2++;
						if (t1 > 7 || t2 > 7)
							break;
						if (t1 == x && t2 == y) // if check
						{
							for (int f = i; f < t1; f++)
							{
								for (int k = j; k < t2; k++)
								{
									if (anotherCaseHelper(board, team, f, k) == 1) // if block is possible
										return 1;
								}
							}
						}
					} while (t1 <= 7 && t2 <= 7 && board[t1][t2] == 0);
				}
				// knight
				else if (board[i][j] == -3)
				{
					// all possible attacks
					if (i-1 == x && j-2 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i-2 == x && j-1 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i-2 == x && j+1 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i-1 == x && j+2 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i+2 == x && j-1 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i+1 == x && j-2 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i+2 == x && j+1 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
					else if (i+1 == x && j+2 == y)
					{
						if (anotherCaseHelper(board, team, i, j) == 1)
							return 1;
					}
				}
			}			
		}
	}
	// block is not possible
	return 0;
}

int anotherCaseHelper(int board[8][8], char team, int x, int y)
{
	if (team == 'w') // check if white piece can block or attack
	{
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				// if empty do nothing
				if (board[i][j] == 0)
					;
				// if pawns can block at x,y
				else if (board[i][j] == -1 || board[i][j] == -10)
				{
					if (i == 6) // initial position, can make two blocks up
					{
						if (i-2 == x && j == y && board[i-2][j] == 0)
							return 1; // means blocking is possible
					}
					if (i-1 >= 0) // to prevent seg fault
					{
						if (i-1 == x && j == y && board[i-1][j] == 0)
							return 1; // means blocking is possible
					}
				}
				// if rook or queen can attack at x,y
				else if (board[i][j] == -2 || board[i][j] == -5 || board[i][j] == -7 || board[i][j] == -17)
				{
					// to the right
					int z = j;
					do
					{
						z++;
						if (z > 7)
							break;
						if (board[i][z] == 0 && i == x && y == z)
							return 1;
						if (board[i][z] > 0 && i == x && y == z)
							return 1;
					} while (board[i][z] == 0 && z <= 7);
					// to the left
					z = j;
					do
					{
						z--;
						if (z < 0)
							break;
						if (board[i][z] == 0 && i == x && y == z)
							return 1;
						if (board[i][z] > 0 && i == x && y == z)
							return 1;
					} while (board[i][z] == 0 && z >= 0);
					// moving down
					z = i;
					do
					{
						z++;
						if (z > 7)
							break;
						if (board[i][z] == 0 && i == x && y == z)
							return 1;
						if (board[i][z] > 0 && i == x && y == z)
							return 1;
					} while (board[z][j] == 0 && z <= 7);
					// moving up
					z = i;
					do
					{
						z--;
						if (z < 0)
							break;
						if (board[i][z] == 0 && i == x && y == z)
							return 1;
						if (board[i][z] > 0 && i == x && y == z)
							return 1;
					} while (board[z][j] == 0 && z >= 0);	
				}
				// bishop and queen
				if (board[i][j] == -4 || board[i][j] == -5)
				{
					int t1 = i;
					int t2 = j;
					// left to right up
					do 
					{
						t1--;
						t2++;
						if (t1 < 0 || t2 > 7)
							break;
						if (board[t1][t2] == 0 && t1 == x && t2 == y)
							return 1;
						if (board[t1][t2] > 0 && t1 == x && t2 == y)
							return 1;
					} while (board[t1][t2] == 0 && t1 >= 0 && t2 <= 7);
					// left to right down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2--;
						if (t1 > 7 || t2 < 0)
							break;
						if (board[t1][t2] == 0 && t1 == x && t2 == y)
							return 1;
						if (board[t1][t2] > 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 <= 7 && t2 >= 0 && board[t1][t2] == 0);
					// right to left up
					t1 = i;
					t2 = j;
					do 
					{
						t1--;
						t2--;
						if (t1 < 0 || t2 < 0)
							break;
						if (board[t1][t2] == 0 && t1 == x && t2 == y)
							return 1;
						if (board[t1][t2] > 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 >= 0 && t2 >= 0 && board[t1][t2] == 0);
					// right to left down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2++;
						if (t1 > 7 || t2 > 7)
							break;
						if (board[t1][t2] == 0 && t1 == x && t2 == y)
							return 1;
						if (board[t1][t2] > 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 <= 7 && t2 <= 7 && board[t1][t2] == 0);
				}
				// knight
				else if (board[i][j] == -3)
				{
					// all possible attacks
					if (i-1 == x && j-2 == y)
					{
						if (board[i-1][j-2] == 0 || board[i-1][j-2] > 0)
							return 1;
					}
					else if (i-2 == x && j-1 == y)
					{
						if (board[i-2][j-1] == 0 || board[i-2][j-1] > 0)
							return 1;
					}
					else if (i-2 == x && j+1 == y)
					{
						if (board[i-2][j+1] == 0 || board[i-2][j+1] > 0)
							return 1;
					}
					else if (i-1 == x && j+2 == y)
					{
						if (board[i-1][j+2] == 0 || board[i-1][j+2] > 0)
							return 1;
					}
					else if (i+2 == x && j-1 == y)
					{
						if (board[i+2][j-1] == 0 || board[i+2][j-1] > 0)
							return 1;
					}
					else if (i+1 == x && j-2 == y)
					{
						if (board[i+1][j-2] == 0 || board[i+1][j-2] > 0)
							return 1;
					}
					else if (i+2 == x && j+1 == y)
					{
						if (board[i+2][j+1] == 0 || board[i+2][j+1] > 0)
							return 1;
					}
					else if (i+1 == x && j+2 == y)
					{
						if (board[i+1][j+2] == 0 || board[i+1][j+2] > 0)
							return 1;
					}
				}
			}
		}
	}
	else if (team == 'b') // check if black piece can block or attack
	{
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				// if empty do nothing
				if (board[i][j] == 0)
					;
				// if pawns can block at x,y
				else if (board[i][j] == 1 || board[i][j] == 10)
				{
					if (i == 1) // initial position, can make two blocks up
					{
						if (i+2 == x && j == y && board[i+2][j] == 0)
							return 1; // means blocking is possible
					}
					if (i+1 <= 7)
					{
						if (i+1 == x && j == y && board[i+1][j] == 0)
							return 1; // means blocking is possible
					}
				}
				// if rook or queen can attack at x,y
				else if (board[i][j] == 2 || board[i][j] == 5 || board[i][j] == 7 || board[i][j] == 17)
				{
					// to the right
					int z = j;
					do
					{
						z++;
						if (z > 7)
							break;
						if (board[i][z] == 0 && i == x && y == z)
							return 1;
						if (board[i][z] < 0 && i == x && y == z)
							return 1;
					} while (board[i][z] == 0 && z <= 7);
					// to the left
					z = j;
					do
					{
						z--;
						if (z < 0)
							break;
						if (board[i][z] == 0 && i == x && y == z)
							return 1;
						if (board[i][z] < 0 && i == x && y == z)
							return 1;
					} while (board[i][z] == 0 && z >= 0);
					// moving down
					z = i;
					do
					{
						z++;
						if (z > 7)
							break;
						if (board[i][z] == 0 && i == x && y == z)
							return 1;
						if (board[i][z] < 0 && i == x && y == z)
							return 1;
					} while (board[z][j] == 0 && z <= 7);
					// moving up
					z = i;
					do
					{
						z--;
						if (z < 0)
							break;
						if (board[i][z] == 0 && i == x && y == z)
							return 1;
						if (board[i][z] < 0 && i == x && y == z)
							return 1;
					} while (board[z][j] == 0 && z >= 0);	
				}
				// bishop and queen
				if (board[i][j] == 4 || board[i][j] == 5)
				{
					int t1 = i;
					int t2 = j;
					// left to right up
					do 
					{
						t1--;
						t2++;
						if (t1 < 0 || t2 > 7)
							break;
						if (board[t1][t2] == 0 && t1 == x && t2 == y)
							return 1;
						if (board[t1][t2] < 0 && t1 == x && t2 == y)
							return 1;
					} while (board[t1][t2] == 0 && t1 >= 0 && t2 <= 7);
					// left to right down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2--;
						if (t1 > 7 || t2 < 0)
							break;
						if (board[t1][t2] == 0 && t1 == x && t2 == y)
							return 1;
						if (board[t1][t2] < 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 <= 7 && t2 >= 0 && board[t1][t2] == 0);
					// right to left up
					t1 = i;
					t2 = j;
					do 
					{
						t1--;
						t2--;
						if (t1 < 0 || t2 < 0)
							break;
						if (board[t1][t2] == 0 && t1 == x && t2 == y)
							return 1;
						if (board[t1][t2] < 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 >= 0 && t2 >= 0 && board[t1][t2] == 0);
					// right to left down
					t1 = i;
					t2 = j;
					do 
					{
						t1++;
						t2++;
						if (t1 > 7 || t2 > 7)
							break;
						if (board[t1][t2] == 0 && t1 == x && t2 == y)
							return 1;
						if (board[t1][t2] < 0 && t1 == x && t2 == y)
							return 1;
					} while (t1 <= 7 && t2 <= 7 && board[t1][t2] == 0);
				}
				// knight
				else if (board[i][j] == 3)
				{
					// all possible attacks
					if (i-1 == x && j-2 == y)
					{
						if (board[i-1][j-2] == 0 || board[i-1][j-2] < 0)
							return 1;
					}
					else if (i-2 == x && j-1 == y)
					{
						if (board[i-2][j-1] == 0 || board[i-2][j-1] < 0)
							return 1;
					}
					else if (i-2 == x && j+1 == y)
					{
						if (board[i-2][j+1] == 0 || board[i-2][j+1] < 0)
							return 1;
					}
					else if (i-1 == x && j+2 == y)
					{
						if (board[i-1][j+2] == 0 || board[i-1][j+2] < 0)
							return 1;
					}
					else if (i+2 == x && j-1 == y)
					{
						if (board[i+2][j-1] == 0 || board[i+2][j-1] < 0)
							return 1;
					}
					else if (i+1 == x && j-2 == y)
					{
						if (board[i+1][j-2] == 0 || board[i+1][j-2] < 0)
							return 1;
					}
					else if (i+2 == x && j+1 == y)
					{
						if (board[i+2][j+1] == 0 || board[i+2][j+1] < 0)
							return 1;
					}
					else if (i+1 == x && j+2 == y)
					{
						if (board[i+1][j+2] == 0 || board[i+1][j+2] < 0)
							return 1;
					}
				}
			}
		}
	}
	return 0;
}

