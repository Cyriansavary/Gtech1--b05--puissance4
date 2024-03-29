/*
 ============================================================================
 Name        : Puissance_4.c
 Author      : 
 Version     :
 Copyright   : Cyrian SAVARY & Maxime STAJSZCZYK
 Description : Puissance 4 game
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#define NBL 7
#define NBC 6
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int Column;
int Line;
int NbWin[2];
       
void ScreenGame(char GameTable[Column][Line]);
void PlaceToken(int TokenPlayer);
int Cursorplayer(int PosCursor);
char VictoryHon (int c, int l);
char VictoryVer (int c, int l);
char VictoryDiaUp (int c, int l);
char VictoryDiaDown (int c, int l);
char PlayeableGame(void);
void Title(void);
int TestGameFull(void);
int PlayerWinScreen(char Player);
void Scoreboard(void);
void delay(int number_of_seconds);

char CaseTable[NBC][NBL];

int main(void) {
	char PlayerWin = '.';
	char Input;
	memset (NbWin, 0, sizeof(NbWin));
	Title();										// Title of the game	
	while (1)
	{
		memset(CaseTable, '.', sizeof(CaseTable));		//Init Casetable
		system("@cls||clear");							//clear terminal
		Input='.';
		printf(" v");
		ScreenGame(CaseTable);							//Make Game screen
		PlayerWin = PlayeableGame();					// Main Game 
		if (PlayerWin =='O' || PlayerWin == 'X' || PlayerWin == 'E') //test if game is end 
		{
			PlayerWinScreen(PlayerWin);								// screen of the end 
			Scoreboard();											//Scoreboard of the game
			printf("\nVoulez-vous rejouer ?\n");
			scanf(" %s",&Input);
			Input=tolower(Input);
			if (Input != 'y')	
			{
				printf("\nAurevoir !");
				delay(5);
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}


void Title(void) //Show the tilte of the game.
{
	char Input; 
	printf(".---.        _                                          .-. \n: .; :      :_;                                        .'.' \n:  _.'.-..-..-. .--.  .--.  .--.  ,-.,-. .--.  .--.   .'.'_ \n: :   : :; :: :`._-.'`._-.'' .; ; : ,. :'  ..'' '_.'  :_ ` :\n:_;   `.__.':_;`.__.'`.__.'`.__,_;:_;:_;`.__.'`.__.'    :_: \n");
	printf(" Press an input to play\n");
	scanf("%c",&Input);
	system("@cls||clear");
}

void ScreenGame (char GameTable[NBC][NBL]) //Initialisation of the game.
{
	for (int L=0; L < NBL; L++){
		printf("\n");
		for (int C=0; C < NBC; C++){
			//printf("%d%d",C,L); 	Seeing all lines numbers for debuging.
			if (GameTable[C][L] == 'X')
			{
				printf("%s %c ",KRED,GameTable[C][L]);
			}
			else if (GameTable[C][L] == 'O')
			{
				printf("%s %c ",KYEL,GameTable[C][L]);
			}
			else 
			{
				printf("%s %c ",KBLU,GameTable[C][L]);
			}
			printf("%s",KWHT);
		}
		}
}


int Cursorplayer(int Cursor) //Create a cursor to give viewing choice to the player.
{
	int InputUser;
	char CursorPlayer[NBC];
	memset(CursorPlayer, ' ', sizeof(CursorPlayer));
	for (int Column = 1; Column < NBC; Column++)
	{
		printf(" %c ", CursorPlayer[Column]);
	}
	while (1)
	{	
 		InputUser=getch();		
		if (InputUser==0 || InputUser==0xE0) 
		{
			InputUser=getch();
		}
		if (InputUser==80) 
		{ 
			break;
		}
		else if (InputUser==75)
		{
			Cursor--;
			break;
		}
		else if (InputUser==77)
		{
			Cursor++;
			break;
		}			
 	}
 	system("@cls||clear");
	if (Cursor < 0)
	{
		Cursor=0;
	}
	if (Cursor > 5)
	{
		Cursor = 5;
	}
	memset(CursorPlayer, ' ', sizeof(CursorPlayer));
	CursorPlayer[Cursor]= 'v';

	 for (int Column = 0; Column < NBC; Column++)
	{
	printf(" %c ", CursorPlayer[Column]);
	}
	 ScreenGame(CaseTable);
    	printf("\n");
		if (InputUser ==80)
		{	
			if (CaseTable[Cursor][0]!='.' )
		{	
			return Cursorplayer(Cursor);
		}
			system("@cls||clear");
			return Cursor;
		}
	Cursorplayer(Cursor);
}

void PlaceToken(int TokenPlayer) //Place a 'O' on the board for the first player or a 'X' if it's the second player.
{
	int Test = 0;
	int PosCursor = 0;
	int PlayerChoice;
	char Token[2]= {'X','O'};
	PlayerChoice=Cursorplayer(PosCursor);
	Test=0;
	do 
	{
		Test++;
	}
	while (CaseTable[PlayerChoice][Test] == '.'  && Test < 6);
	if (CaseTable[PlayerChoice][Test]=='O' || CaseTable[PlayerChoice][Test]=='X' )
	{
		Test--;
	}
	CaseTable[PlayerChoice][Test]= Token[TokenPlayer];
	ScreenGame(CaseTable);
}

char VictoryHon (int c, int l) //Looking if there is a possible win in horizontal way on the board.
  {
	 	  int TokenWin = 1;

	while ((CaseTable[c][l]==CaseTable[c][l-1]) && (CaseTable[c][l]!='.'))
	{
		l--;
		TokenWin++;						
	}
	if(l>3)
	{	
		l--;
		return VictoryHon(c,l);
	}
	if (TokenWin >= 4)
	{	
		return CaseTable[c][l];
	}
	return 0;
  }
char VictoryVer (int c, int l) //Looking if there is a possible win in vertical way on the board.
  {
	  int TokenWin = 1;

	while ((CaseTable[c][l]==CaseTable[c+1][l]) && (CaseTable[c][l]!='.'))
	{
		c++;
		TokenWin++;						
	}
	if(c<2)
	{	
		c++;
		return VictoryVer(c,l);
	}
	if (TokenWin >= 4)
	{	
		return CaseTable[c][l];
	}
	return 0; 
  }

char VictoryDiaUp (int c, int l) //Looking if there is a possible win in diagonal from bottom left to top right on the board.
  {
	int TokenWin = 1;
	while ((CaseTable[c][l]==CaseTable[c+1][l-1]) && (CaseTable[c][l]!='.'))
	{
		l--;
		c++;
		TokenWin++;	
			if (l<= 0)
		{
			l=0;
		}						
	}
	if (TokenWin >= 4)
	{	
		return CaseTable[c][l];
	}
	return 0; 
  }
  char VictoryDiaDown (int c, int l) //Looking if there is a possible win in diagonal from bottom right to top left on the board.
  {
	  int TokenWin = 1;

	while ((CaseTable[c][l]==CaseTable[c-1][l-1]) && (CaseTable[c][l]!='.'))
	{
		l--;
		c--;
		TokenWin++;
						
	}
	if (TokenWin >= 4)
	{	
		return CaseTable[c][l];
	}
	return 0; 
  }
char PlayeableGame(void) //The entire game.
{
	int TokenPlayer =0;
	char test;
	int Gamefull;
	while (test!='O' && test !='X')
	{
		if (TokenPlayer==0)
		{
			TokenPlayer++;
		}
		else
		{
			TokenPlayer=0;
		}
		Gamefull=TestGameFull();
		if (Gamefull == 0)
		{
			test = 'E';
			return test;
		}
		PlaceToken(TokenPlayer);
		for (int c = 0; c < NBC; c++)
		{
			test = VictoryHon(c,6);
			if (test=='O' || test =='X')
			{
				return test;
			}
		}
		if (test!='O' && test !='X')
			{
					for (int l = 0; l < NBL; l++)
			{
			test = VictoryVer(0,l);	
			if (test=='O' || test =='X'){
				return test;
			}
			}
			}
			if (test!='O' && test !='X')
			{
				for (int c = 0; c < NBC; c++)
				{
					for (int l = 6; l > 0 ;l--)
					{					
												
			test = VictoryDiaUp(c,l);
			
			if (test=='O' || test =='X'){
				return test;
			}
			}
			}
			}
			if (test!='O' && test !='X')
			{
				for (int c = 5; c > 0; c--)
				{
					for (int l = 6; l > 0 ;l--)
					{							
										
			test = VictoryDiaDown(c,l);
			
			if (test=='O' || test =='X')
			{
				return test;
			}
			}
			}
			}			
	}
  }
int TestGameFull(void) //Testing if the game board is full.
{
	for (int c = 0; c < NBC; c++)
	{
		for (int l = 0; l < NBL; l++)
		{
			if(CaseTable[c][l]=='.')
			{
				return 1;
			}
		}
			  
	}
	return 0;
}

int PlayerWinScreen (char Player) //Showing which player won the game.
	{
                switch (Player)
				{
				case 'O' :
					 printf("\nLe joueur 1 a gagne !\n");
					 NbWin[0]++;
					break;	
				case 'X' :
					printf("\nLe joueur 2 a gagne !\n");
					NbWin[1]++;
					break;	
				case 'E' :
					 printf("\nMatch nul !\n");
					break;	

				}
				return 0;
	}

void Scoreboard(void) //Showing a scoreboard of the two players wins. 
	{
		printf("|---------------------------------------|\n""|               Scoreboard              |\n""|                                       |\n""|                                       |\n""|      Nombre de partie(s) gagnee(s)    |\n""|                                       |\n""|- Joueur 1 :%27d|\n""|- Joueur 2 :%27d|\n""|                                       |\n""|                                       |\n""|---------------------------------------|\n",NbWin[0],NbWin[1]);

	}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}	
