#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Functions.h"
#include "Display.h"
#include "AI.h"
#include "Definitions.h"

int board[8][8] = {{0}};

int main(void) {	
	// setting the initial board
	setBoard(board);

    // name text file
    char filename[20] ;
    printf("name the game log file:\n") ;
    fgets(filename, sizeof(filename), stdin) ; // using fgets instead of scanf to account for white space
    strtok(filename, "\n") ; // get rid of newline
    text = createLogFile(filename) ; // open text file
	
	// choosing team side
	int game;
	char team;
	int flag = 0;
	int pass=1; 

	//set bounds in case of typo/ errors
	while(pass)
	{
		printf("Choose a team! 'w' for white, 'b' for black team!: ");
		team= getchar();
		getchar();
		//scanf(" %c", &team);
		if(team == 'w')
		{
			pass=0;
		}
		else if(team == 'b')
		{
			pass=0;
		}
		else
		{
			printf("incorrect input, please rechoose valid input\n\n");
			pass=1;
		}
	}


	//print menu
	printf("Choose game: 1 for Player vs Player, 2 for Player vs Computer: ");
	scanf(" %d", &game);
	//set bounds incase of errors or typos
	while(game > 2 || game < 1)
	{
		printf("incorrect input, please choose one of the following numbers\n\n");
		printf("Choose game: 1 for Player vs Player, 2 for Player vs Computer");
		scanf(" %d", &game);
	}
	

	int AITeam;
	// if user is white, make AI black and vice-versa
	if (team == 119) 
	{
		AITeam = 1;	
	}
	else 
	{
		AITeam = 0;
	}
	
	//print initail board for player to see
	printBoard(board);

	int turn = 1;
	
	//player v player gamestate
	if(game == 1)
	{
		char init[3];
		char fin[3];
		int x,y;	
		if(team == 'b')
		{
			team='w';
		}
		
		while(flag != 2 || flag != 3)
		{
			if(team == 'w')
			{
				printf("Move %d \n", turn);
				printf("WHITE MOVE \n");
				
				//WhiteCheck(board);

				printf("initial spot:");
				scanf("%s", init);
				x = pos(init);

				printf("final spot: ");
				scanf("%s", fin);
				y = pos(fin);

                LogFile(text, board, init, fin, flag) ;
				Move(board, x, y, team, 1);		
				printBoard(board);
				team = 'b';
				
				if(BlackCheck(board) == 1)
				{
				    fprintf(text, "\nBlack is in check!\n");
				    flag = getCheckMate(board, 'b');
				    if (flag == 2) 
				    {
						fprintf(text, "\nCheckmate! White Wins!\n") ;
						printf("\nCheckmate! White Wins!\n");
						break;
				    }
				}

				turn++;
			}
			else if(team == 'b')
			{
				printf("Move %d\n", turn);
				printf("BLACK MOVE \n");
				
				//BlackCheck(board);

				printf("initial spot:");
				scanf("%s", init);
				x = pos(init);

				printf("final spot: ");
				scanf("%s", fin);
				y = pos(fin);
                
                LogFile(text, board, init, fin, flag) ;
				Move(board, x, y, team, 1);		
				printBoard(board);
				team = 'w';

				if(WhiteCheck(board) == 1)
				{
				    fprintf(text, "\nWhite is in check!\n");
				    flag = getCheckMate(board, 'w');
				    if (flag == 2) 
					{
						fprintf(text, "\nCheckmate! Black Wins!\n") ;
						printf("\nCheckmate! Black Wins!\n");
						break;
				    }
				}

				turn++;
			}
		}
	}
	
	//player v ai gamestate
	else 
	{
		while (flag != 2 || flag != 3) 
		{
	       	char init[3];
			char fin[3];
			int x, y;
			MOVE move_ai;

	        // if user is white
   		    if (team == 119) 
			{
	        	// user move
				printf("\n\n------------------------------\nWHITE MOVE (USER)\n");
				     
				//WhiteCheck(board);
				     
				printf("initial spot: ");
				scanf("%s", init);
				x = pos(init);

				printf("final spot: ");
				scanf("%s", fin);
				y = pos(fin);
                
	          	LogFile(text, board, init, fin, flag) ;
				Move(board, x, y, team, 1);		
				printBoard(board);
				if(BlackCheck(board) == 1)
				{
				    flag = getCheckMate(board, 'b');
				    if (flag == 2) 
				    {
						fprintf(text, "\nCheckmate! White Wins!\n") ;
						printf("Checkmate! White Wins!\n");
						continue;
				    }
				}

				// AI move
				printf("\n\n------------------------------\nBLACK MOVE (AI)\n");
			//	BlackCheck(board);
				move_ai = AIMove(board, AITeam, turn);
				printBoard(board);

				if(WhiteCheck(board) == 1)
				{
				    flag = getCheckMate(board, 'w');
				    if (flag == 2) 
				    {
						fprintf(text, "\nCheckmate! Black Wins!\n") ;
						printf("Checkmate! Black Wins!\n");
						continue;
				    }
				}
		            LogFileAI(text, move_ai, flag) ;
		    }
		    else	// if user is black
			{ 
				// AI move
				printf("\n\n------------------------------\nWHITE MOVE (AI)\n");
				     
			//	WhiteCheck(board);
				     
				move_ai = AIMove(board, AITeam, turn);
				printBoard(board);

				if(BlackCheck(board) == 1)
				{
				    flag = getCheckMate(board, 'b');
				    if (flag == 2) 
				    {
						printf("Checkmate! White Wins!\n");
						continue;
				    }
				}
	            LogFileAI(text, move_ai, flag) ;
				// user move
				printf("\n\n------------------------------\nBLACK MOVE (USER)\n");
				
			//	BlackCheck(board);     
				     
				printf("initial spot: ");
				scanf("%s", init);
				x = pos(init);

				printf("final spot: ");
				scanf("%s", fin);
				y = pos(fin);

                LogFile(text, board, init, fin, flag) ;
				Move(board, x, y, team, 1);		
				printBoard(board);
			
				if(WhiteCheck(board) == 1)
				{
				    flag = getCheckMate(board, 'w');
				    if (flag == 2) 
				    {
						fprintf(text, "\nCheckmate! Black Wins!\n") ;
						printf("Checkmate! Black Wins!\n");
						continue;
				    }
				}
			    }
			turn++;
		}
	}
    fclose(text) ; // close text file

	return 0;
}
