#include "master.h"


#include "main.h"
#include "menu.h"
#include "game.h"
//#include "Tanque.h"
#include "Escenari.h"
#include "graficos.h"













//-------------------------------------------------------------------------------------------------


Menu::Menu() /*construye el menu*/
{

	/*inicializa Cursor en 0*/
//	Cursor = 0;

	/*incializa TotalItems en 0*/
	TotalItems = 0;

	/*crea la primera opción del menú*/
	AddItem (new Item("Jugar",Juego)); 


	/*crea la segunda opción del menú*/
	AddItem (new Item("Salir",Raje));


	ImprimeMenu();


	SetSelection(1);

}



//-------------------------------------------------------------------------------------------------


Menu::~Menu()   /*borra los objetos de la clase item creados dinámicamente y agregados al menú*/
{
	int Repeticiones = TotalItems;

	for (int i=0; i<Repeticiones; i++)

		QuitItem(Opcion[i]);



	TotalItems = 0;


}



//-------------------------------------------------------------------------------------------------


void Menu::ImprimeMenu(void) /*imprime los nombres de las opciones del menú*/
{

	printf("\n\n");
	printf("   °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
	printf("   °°²²²²²²²²°°°°²²²²²²²²²²°°²²°°²²°°²²°°²²²²²²²²°°°°²²²²²²²²²²°°²²°°²²°°²²°°\n");
	printf("   °°²²°°°°°°²²°°²²°°°°°°°°°°²²°°²²°°²²°°²²°°°°°°²²°°²²°°°°°°°°°°²²°°²²°°²²°°\n");
	printf("   °°²²°°°°°°²²°°²²°°°°°°°°°°²²°°²²°°²²°°²²°°°°°°²²°°²²°°°°°°°°°°²²°°²²°°²²°°\n");
	printf("   °°²²°°°°°°²²°°²²°°°°°°°°°°²²°°²²°°²²°°²²°°°°°°²²°°²²°°°°°°°°°°²²°°²²°°²²°°\n");
	printf("   °°²²²²²²²²°°°°²²²²²²²²²²°°²²°°²²°°²²°°²²²²²²²²°°°°²²²²²²²²²²°°²²°°²²°°²²°°\n");
	printf("   °°²²°°°°°°°°°°²²°°°°°°°°°°°°²²°°²²°°°°²²°°°°°°°°°°²²°°°°°°°°°°°°²²°°²²°°°°\n");
	printf("   °°²²°°°°°°°°°°²²°°°°°°°°°°°°²²°°²²°°°°²²°°°°°°°°°°²²°°°°°°°°°°°°²²°°²²°°°°\n");
	printf("   °°²²°°°°°°°°°°²²°°°°°°°°°°°°²²°°²²°°°°²²°°°°°°°°°°²²°°°°°°°°°°°°²²°°²²°°°°\n");
	printf("   °°²²°°°°°°°°°°²²²²²²²²²²°°°°²²°°²²°°°°²²°°°°°°°°°°²²²²²²²²²²°°°°²²°°²²°°°°\n");
	printf("   °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");






	Division = (int)(15/*25*//(TOTAL_ITEMS+1));  //este número divide las filas en partes iguales dependiendo de la cantidad de items

	for (int I=0; I<TOTAL_ITEMS; I++)
	{
		PrintPositionedText (Opcion[I]->Nombre, Division * (I+1) + 10 , 40 - (int) ((strlen(Opcion[I]->Nombre))/2) );
		


	}

}

//-------------------------------------------------------------------------------------------------


void Menu::AddItem(Item* item) /*agrega un item al menú apuntando un puntero a un objeto de la clase item*/
{

	
	Opcion[TotalItems] = item;


	TotalItems++;


}


//-------------------------------------------------------------------------------------------------


Item::Item(char* Titulo, void (*Func)()) /*construye el elemento de la clase item poniéndole el nombre y asignándole la función a la que llama*/
{

	strcpy(Nombre,Titulo);

	Action = Func;




}


//-------------------------------------------------------------------------------------------------


void Menu::PrintPositionedText(char * Pal, int fila, int columna)
{



	unsigned char far* Video = (unsigned char far*)0xB8000000L;
	
	Video += (2 * columna + 160 *  fila); //pone el puntero en la posición que corresponde a la fila y la columna

	for (int I=0; I<(int)strlen(Pal); I++, Video+=2) //pone el string caracter por caracter corriendose un lugar por vuelta

		*Video = Pal[I];



	
}


//-------------------------------------------------------------------------------------------------


int Menu::GetSelection(void)
{


	return Cursor;


}


//-------------------------------------------------------------------------------------------------


void Menu::SetSelection(int ItemNo)
{

	int fila, columna = 30;

	fila = Division * Cursor + 10;

	PrintPositionedText("   ",fila,columna); //borra el cursor de la opción seleccionada antes

	fila = Division * ItemNo + 10;

	PrintPositionedText("==>",fila,columna); //dibuja el cursor en la nueva opción seleccionada

	Cursor = ItemNo;
	

}


//-------------------------------------------------------------------------------------------------


void Menu::QuitItem(Item* item)
{

	delete item;

	TotalItems--;


}


//-------------------------------------------------------------------------------------------------


void Menu::CallOption()
{

	Opcion[Cursor-1]->Action();

}
