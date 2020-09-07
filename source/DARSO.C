#include <stdio.h>
#include <conio.h>
#include <string.h>



void IMPR_POS(char *, int, int);



void main()
{
	char Nom[20];
	int fil, col;

	clrscr();

	scanf("%d", &fil);

	fflush(stdin);

	scanf("%d", &col);

	fflush(stdin);

	gets(Nom);
	
	clrscr();
	
	getch();
	
	PrintPositionedText(Nom, fil, col);
	
	getch();
}



void PrintPositionedText(char * Pal, int fila, int columna)
{



	unsigned char far* Video = 0xB8000000L;
	
	Video += (2 * columna + 160 *  fila); //pone el puntero en la posición que corresponde a la fila y la columna

	for (int I=0; I<strlen(Pal); I++, Video+=2) //pone el string caracter por caracter corriendose un lugar por vuelta

		*Video = Pal[I];



	
}