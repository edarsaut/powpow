#include "master.h"

#include "main.h"
#include "menu.h"
#include "game.h"
//#include "Tanque.h"
#include "Escenari.h"
#include "graficos.h"
#include "display.h"







Menu* menu;
Display* display;

void main (void)
{
	clrscr();
	
	OcultarCursor();

	menu = new Menu;

	int CurrentSelection = menu->GetSelection(); //esta sirve para manejar el cursor desde el main usando GetSelection()  SetSelection()

	int salir = 0;

//ac� vendr�an funciones que manejen la seleccion de la opci�n del men�
	do
	{

		switch (Tecla())
		{
		case AR:
				if (CurrentSelection>1)
				CurrentSelection--;
			
			break;

		case AB:
			if (CurrentSelection<TOTAL_ITEMS)
				CurrentSelection++;

			break;

		case ENTER:
			
			salir = 1;
			
			break;

		default:
			
			break;
			
		}

		menu->SetSelection(CurrentSelection);

		
/************************************************************************************
*																					*
*	ac� habr�a que detectar la tecla apretada y hacer la acci�n correspondiente:	*
*	incrementar selecci�n, decrementar selecci�n o salir cuando se acepte una opci�n*
*																					*
*								YA EST� HECHO										*
************************************************************************************/

	} while (!salir); 


	clrscr();


	menu->CallOption();

	PonerModoTexto();

	MostrarCursor();

	delete display;



}




//-------------------------------------------------------------------------------------------------


void Juego(void)
{

	delete menu; /*hay que "deletear" men� reci�n despu�s de llamar a Juego(), ya que la llamamos desde menu->CallOption()*/

	int Player1=0, Player2=0, Res;

	

	display = new Display;

	display->Mostrar( 0x00, 0x00);
	


/*

ac� habr�a que meter algo que vaya viendo los puntajes y mand�ndolos al puerto paralelo
la idea es hacer un while que crea y destruye el objeto de la clase game por cada vez que
los tanques se ponen un tiro adem�s de ir actualizando el marcador del puerto paralelo
habr�a que meter un par de variables ac� que registren los puntajes	
	
*/
	Game* game;

	do
	{
		
		game = new Game;

		Res = MISS;
		
		
		do
		{
			
			if (Res == MISS)
			{
				game->tanque1->Apuntar();
				if (game->tanque1->quit)
				{
					delete game;
					return;
				}
				Res = game->tanque1->Shoot(game->tanque2, game->escenario);
				if (Res == BOOM)
					Player1++;
			
			}

		
			if (Res == MISS)
			{
				game->tanque2->Apuntar();
				if (game->tanque2->quit)
				{
					delete game;
					return;
				}
				Res = game->tanque2->Shoot(game->tanque1, game->escenario);
				if (Res == BOOM)
					Player2++;
			}


		} while (Res == MISS);

		delete game;

		PonerModoGrafico(); //esto va porque no tengo ganas de borrar la pantalla pixel por pixel

		
		gotoxy(14,8);
		printf("Jugador 1: %d",Player1);//funca para el modo gr�fico y queda un poco m�s lindo


		gotoxy(14,16);
		printf("Jugador 2: %d",Player2);//�dem anterior

		//manda resultados al paralelo
		display->Mostrar((unsigned char)Player1,(unsigned char)Player2);



		getch();
		

//		delay(1);




	} while (Player1<7 && Player2<7);


	/*ac� habr�a que poner alg�n mensajito choto que diga quien gan� y tambi�n hacer parpadear lo del paralelo*/

	PonerModoGrafico();

	gotoxy(20-7, 10);
	printf("El ganador es:");

	gotoxy(20-5, 16);
	printf("%s",(Player1==7)?"Jugador 1":"Jugador 2");

	while(!kbhit())
	{
		display->Apagar();
		delay(500);
		display->Prender();
		display->Mostrar((unsigned char)Player1, (unsigned char)Player2);
		delay(500);
	};


	


}


//-------------------------------------------------------------------------------------------------


void Raje(void)
{

      delete menu;



}


//-------------------------------------------------------------------------------------------------


unsigned char Tecla() //es como un getch(), pero est� hecho para detectar las teclas de las flechas y el enter
{
	unsigned char c;


	while (!kbhit)
	{
	};


	c = getch();

	if (c == 0x00)
	{
		c = getch();
		
		switch (c)
		{
		case AR:
		case AB:
		case IZ:
		case DE:
			fflush(stdin);
			return c;
			break;
		default:
			break;
		}
	}/*
	else
	{
		if (c == ENTER)
		{
			fflush(stdin);
			return c;
		}
	}*/

	fflush(stdin);

	return c;

}