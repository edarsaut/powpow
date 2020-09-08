#include "master.h"


#include "main.h"
#include "menu.h"
#include "game.h"
//#include "Tanque.h"
#include "Escenari.h"
#include "graficos.h"






//-------------------------------------------------------------------------------------------------


Escenario::Escenario(int Y1, int Y2)
{

	YPoint1 = Y1; //alturas generadas al azar en el constructor de la clase Game
	YPoint2 = Y2;
/*
	XPoint1 = 106;//coordenada x de los puntos donde empieza y termina
	XPoint2 = 213;//la pendiente que separa los terrenos de los tanques
*/
	XPoint = 159; //punto donde está el precipicio


	/*dibuja el piso usando las propiedades recien cargadas*/
	DibujaPiso();


}


//-------------------------------------------------------------------------------------------------


Escenario::~Escenario()
{



}


//-------------------------------------------------------------------------------------------------


void Escenario::DibujaPiso() //esta función es medio jodida, así que hay que probarla y corregirla
{


	/*dibuja el primer segmento de piso, donde se apoya el tanque1*/
	for (int j=0; j<YPoint1-1; j++)
		for (int i=0; i<160; i++)
			Punto(i, YPoint1-1-j, 0x0A); //color verde claro (supuestamente)

	
	/*dibuja el segundo segmento de piso, donde se apoya el tanque2*/
	for (j=0; j<YPoint2-1; j++)
		for (i=0; i<160; i++)
			Punto(i+XPoint, YPoint2-1-j, 0x0A); //color verde claro (supuestamente)
	

	/*dibuja el segmento de piso del medio (el inclinado)*/
//	float pendiente = (float)((YPoint2-YPoint1)/(XPoint2-YPoint1));


	if (YPoint1<YPoint2)
	{
		
		for (int i=0; i<(YPoint2-YPoint1); i++)
			Punto(XPoint, YPoint1+i,0x0A);

	}
	else
	{

		for (int i=0; i<(YPoint1-YPoint2); i++)
			Punto(XPoint, YPoint2+i, 0x0A);

	}


}