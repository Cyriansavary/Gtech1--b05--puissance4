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
	
char CaseTable[NBC][NBL];

int main(void) {
	char PlayerWin = '.';
	char Input;
	Title();

	
	while (1)
	{
	memset(CaseTable, '.', sizeof(CaseTable));
	system("@cls||clear");	
	Input='.';
	printf(" v");
	ScreenGame(CaseTable);
	PlayerWin = PlayeableGame();

	if (PlayerWin == 'E')
	{
		printf("Game end");
		break;
	}	  
	if (PlayerWin =='O' || PlayerWin == 'X')
	{
		printf("\nVoulez-vous rejouer ?\n");
		scanf(" %s",&Input);
		printf("%c",Input);
		if (Input != 'y')
		{
			break;
		}
	}
	}
	

	return EXIT_SUCCESS;
}


void Title(void){
	char Input; 
	printf(".---.        _                                          .-. \n: .; :      :_;                                        .'.' \n:  _.'.-..-..-. .--.  .--.  .--.  ,-.,-. .--.  .--.   .'.'_ \n: :   : :; :: :`._-.'`._-.'' .; ; : ,. :'  ..'' '_.'  :_ ` :\n:_;   `.__.':_;`.__.'`.__.'`.__,_;:_;:_;`.__.'`.__.'    :_: \n");
	printf(" Press an input to play\n");
	scanf("%c",&Input);
	system("@cls||clear");
}

void ScreenGame (char GameTable[NBC][NBL]){

for (int L=0; L < NBL; L++){
		printf("\n");
		for (int C=0; C < NBC; C++){
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

	
	//printf("%d %d", C ,L );

		}
		}
}


int Cursorplayer(int Cursor)
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
		if (InputUser==0 || InputUser==0xE0) {
			InputUser=getch();
		}
		if (InputUser==80){ //Down for exit 
			break;
		}
		else if (InputUser==75){
			Cursor--;
			break;
		}
		else if (InputUser==77){
			Cursor++;
			break;
		}			
 }
 system("@cls||clear");
 
	if (Cursor < 0){
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
			printf("%d",Cursor);
			return Cursorplayer(Cursor);
		}
			system("@cls||clear");
			return Cursor;
		}
	Cursorplayer(Cursor);
}


void PlaceToken(int TokenPlayer)
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

char VictoryHon (int c, int l)
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
	//printf("\n   %d %d %d",TokenWin,c ,l );
	if (TokenWin >= 4)
	{	
		//printf(" WIN ");
		return CaseTable[c][l];
	}
	return 0;
  }
char VictoryVer (int c, int l)
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
	//printf("\n   %d %d %d",TokenWin,c ,l );
	if (TokenWin >= 4)
	{	
		//printf(" WIN ");
		return CaseTable[c][l];
	}
	return 0; 
  }

char VictoryDiaUp (int c, int l)
  {
	  int TokenWin = 1;

	while ((CaseTable[c][l]==CaseTable[c+1][l-1]) && (CaseTable[c][l]!='.'))
	{
		l--;
		c++;
		TokenWin++;						
	}
	//printf("\n   %d %d %d",TokenWin,c ,l );
	if (TokenWin >= 4)
	{	
		//printf(" WINdiaup ");
		return CaseTable[c][l];
	}
	return 0; 
  }
  char VictoryDiaDown (int c, int l)
  {
	  int TokenWin = 1;

	while ((CaseTable[c][l]==CaseTable[c-1][l-1]) && (CaseTable[c][l]!='.'))
	{
		l--;
		c--;
		TokenWin++;						
	}
	//printf("\n   %d %d %d",TokenWin,c ,l );
	if (TokenWin >= 4)
	{	
		//printf(" WINdiadown ");
		return CaseTable[c][l];
	}
	return 0; 
  }
  char PlayeableGame(void)
  {
	int TokenPlayer =0;
	char test;
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
			if (TestGameFull() == 0)
			{
				printf("dhqgdiqg");
				test = 'E';
				return test;
			}
			PlaceToken(TokenPlayer);
			for (int c = 0; c < NBC; c++)
			{
			test = VictoryHon(c,6);
			//printf("\n %c",test);
			if (test=='O' || test =='X'){
				return test;
			}
			}
			if (test!='O' && test !='X')
			{
					for (int l = 0; l < NBL; l++)
			{
			test = VictoryVer(0,l);
			//printf("\n %c",test);
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
			
			if (test=='O' || test =='X'){
				return test;
			}
			}
			}
			}
			
				
	}
  }
  int TestGameFull(void)
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