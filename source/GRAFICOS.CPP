

#include "master.h"


#include "main.h"
#include "menu.h"
#include "game.h"
//#include "Tanque.h"
#include "Escenari.h"
#include "graficos.h"

//-------------------------------------------------------------------------------------------------


void PonerModoGrafico() //pone el modo gráfico 0DH: 320x200 16 colores
{

	union REGS r;


	/*se pone el modo gráfico*/
	
	r.h.ah = 0x00; //selección de función de selección de modo de video
	r.h.al = 0x0D; //modo gráfico 320*200 / 16 colores

	int86(0x10,&r,&r); //llama a la interrupción 10H, la de las funciones de video


	/*se selecciona la página 0 de video*/
	r.h.ah = 0x05;  //selección de función de seteo de página de vídeo
	r.h.al = 0x00;  //selección de página 0 de vídeo
	
	int86(0x10,&r,&r); //llamada a interrupción de bios, funciones de vídeo

}


//-------------------------------------------------------------------------------------------------


void Punto(int X, int Y, int clr)
{


	union REGS r;

	r.h.bh = 0;
	r.h.ah = 0x0C; //selección de función de bios que dibuja un punto en pantalla
	r.x.cx = X;	 //columna donde se colocará el punto
	r.x.dx = 200 - Y;	 //fila donde se colocará el punto
	r.h.al = clr;	 //color del punto


	int86(0x10,&r,&r);	//llama a la interrupcion de las funciones de video



}


//-------------------------------------------------------------------------------------------------


void PonerModoTexto(void)
{
	

union REGS r;


	/*se pone el modo texto*/
	
	r.h.ah = 0x00; //selección de función de selección de modo de video
	r.h.al = 0x02; //modo texto 80*25 16 colores

	int86(0x10,&r,&r); //llama a la interrupción 10H, la de las funciones de video


	/*se selecciona la página 0 de video*/
	r.h.ah = 0x05;  //selección de función de seteo de página de vídeo
	r.h.al = 0x00;  //selección de página 0 de vídeo
	
	int86(0x10,&r,&r); //llamada a interrupción de bios, funciones de vídeo



}


//-------------------------------------------------------------------------------------------------


void MostrarCursor(void)
{

	union REGS r;

	r.h.ah = 0x01; //función de modificar el tamaño del cursor
	r.h.cl = 8; //inicio del cursor
	r.h.ch = 7; //fin del cursor

	int86(0x10,&r,&r);


}




//-------------------------------------------------------------------------------------------------


void OcultarCursor(void)
{

	union REGS r;

	r.h.ah = 0x01; //función de modificar el tamaño del cursor
	r.h.cl = 0; //inicio del cursor
	r.h.ch = 32; //fin del cursor

	int86(0x10,&r,&r);



}


//-------------------------------------------------------------------------------------------------


void Rectangulo(int X1,int Y1,int X2,int Y2,int mode, int color)
{


	int largo;
	int alto;

	largo = X2 - X1 ;
	alto = Y1 - Y2 + 1;


	switch(mode)
	{
	case LLENO:
		{
			for(int i=0; i<alto; i++)
				for(int j=0; j<largo; j++)
					Punto(X1+j, Y1-i, color); //pongo Y1-i para que se dibuje de arriba pa' abajo
				
		}
		break;

	case VACIO:
		{
		

			for(int i=0; i<largo; i++)
			{
				Punto(X1+i, Y1, color);
				Punto(X1+i, Y2, color);
			}
			
			for(i=0; i<alto; i++)
			{
				Punto(X1, Y1-i, color);
				Punto(X2, Y1-i, color);
			}

		}
		break;

	}


}


//-------------------------------------------------------------------------------------------------