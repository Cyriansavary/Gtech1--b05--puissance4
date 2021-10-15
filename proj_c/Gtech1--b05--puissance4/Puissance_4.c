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

int main(void) {
	char CaseTable[10];
	memset(CaseTable, 'O', sizeof(CaseTable));
	printf(" %c . . . . .\n . . . . . .\n . . . . . .\n . . . . . .\n . . . . . .\n . . . . . .\n . . . . . .\n",CaseTable[1]);
	return EXIT_SUCCESS;
}

void Title(void){
	printf(" Puissance 4\n");
	printf(" Mode Simple\n");
}


