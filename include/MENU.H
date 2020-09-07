







/**************************************************************************************
*																					  *
*																					  *
*				Declaración de las clases Menu e Item								  * 
*																					  *
*																					  *
*																					  *
**************************************************************************************/



class Item;



//-------------------------------------------------------------------------------------------------


class Menu
{





private:
	

	/*este es un vector de punteros a las opciones del menú*/
	Item* Opcion[TOTAL_ITEMS];      //puse un puntero a puntero en lugar vector de punteros

	/*esta variable cuenta la cantidad de items agregados al menú (si sacás o agregás se actualiza)*/
	int TotalItems;

	/*esta variable representa el item seleccionado dentro del menú (varía entre 1 y TOTAL_ITEMS) */
	int Cursor;	

	/*esta variable te dice cuánta es la cantidad de líneas entre opción y opción en el menú*/
	int Division;

	/*esta es la función que agrega las opciones al menú*/
	void AddItem(Item*);

	/*esta es la función que imprime el menú*/
	void ImprimeMenu (void);

	/*esta función saca el item del menú*/
	void QuitItem(Item*);




public:

	/*esta función llama a la función correspondiente al item seleccionado del menú*/
	void CallOption();

	Menu();

	~Menu();

	/*retorna el valor del item seleccionado del menú*/
	int GetSelection(void);

	/*setea la selección del item del menú*/
	void SetSelection(int ItemNo);

	/*imprime un string a partir de la fila y columna indicada*/
	void PrintPositionedText (char* Str, int fila, int columna);
	


};


//-------------------------------------------------------------------------------------------------


class Item /*cada objeto de esta clase es una opción para meter en el menú*/
{




private:

	/*nombre de la opcion del menu*/
	char Nombre[20];

	/*puntero a la función que va a llamar la opción*/
	void (*Action)();

	friend void Menu::ImprimeMenu(void);

	friend void Menu::CallOption(void);

public:

	/*el constructor recibe el texto de la opción y el puntero a la función que llama la opción*/
	Item (char*,void(*)());



};