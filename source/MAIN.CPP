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

//acá vendrían funciones que manejen la seleccion de la opción del menú
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
*	acá habría que detectar la tecla apretada y hacer la acción correspondiente:	*
*	incrementar selección, decrementar selección o salir cuando se acepte una opción*
*																					*
*								YA ESTÁ HECHO										*
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

	delete menu; /*hay que "deletear" menú recién después de llamar a Juego(), ya que la llamamos desde menu->CallOption()*/

	int Player1=0, Player2=0, Res;

	

	display = new Display;

	display->Mostrar( 0x00, 0x00);
	


/*

acá habría que meter algo que vaya viendo los puntajes y mandándolos al puerto paralelo
la idea es hacer un while que crea y destruye el objeto de la clase game por cada vez que
los tanques se ponen un tiro además de ir actualizando el marcador del puerto paralelo
habría que meter un par de variables acá que registren los puntajes	
	
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
		printf("Jugador 1: %d",Player1);//funca para el modo gráfico y queda un poco más lindo


		gotoxy(14,16);
		printf("Jugador 2: %d",Player2);//ídem anterior

		//manda resultados al paralelo
		display->Mostrar((unsigned char)Player1,(unsigned char)Player2);



		getch();
		

//		delay(1);




	} while (Player1<7 && Player2<7);


	/*acá habría que poner algún mensajito choto que diga quien ganó y también hacer parpadear lo del paralelo*/

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


unsigned char Tecla() //es como un getch(), pero está hecho para detectar las teclas de las flechas y el enter
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