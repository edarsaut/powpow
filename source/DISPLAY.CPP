
#include "master.h"



#include "display.h"


//-------------------------------------------------------------------------------------------------


Display::~Display()
{


}


//-------------------------------------------------------------------------------------------------


Display::Display()
{


	int far* pBase;


	pBase = (int far*)0x00000408;



	for(int i=0; i<4; i++, pBase++)
	{
		if (*pBase)
		{
			Base = *pBase;
			break;
		}

	}


	outport(Base+2, 0x00);


}


//-------------------------------------------------------------------------------------------------


void Display::SendData(unsigned char data)
{


	outportb(Base, data);


}


//-------------------------------------------------------------------------------------------------


void Display::Mostrar(unsigned char Iz, unsigned char De)
{


	/*****primero mando el número del display izquierdo*****/


	SendData(Iz|0x60);//0110: 1 en BI, 0 en LED y 1 en LEI, desactiva el LEI
	delay(2);
	
	
	SendData(Iz|0x70); //0111: activa el LEI
	delay(2);


	
	/*****ahora mando el número del display derecho*****/

		
	SendData(De|0x50); //0101: desactiva LED
	delay(2);


	SendData(Iz|0x70); //0111: activa LED
	delay(2);


}


//-------------------------------------------------------------------------------------------------


void Display::Apagar(void)
{

	SendData(inportb(Base) & 0xBF);

	delay(1);

}


//-------------------------------------------------------------------------------------------------


void Display::Prender(void)
{

	SendData(inportb(Base) | 0x40);

	delay(1);

}


//-------------------------------------------------------------------------------------------------