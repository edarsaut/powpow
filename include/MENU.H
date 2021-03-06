







/**************************************************************************************
*																					  *
*																					  *
*				Declaraci�n de las clases Menu e Item								  * 
*																					  *
*																					  *
*																					  *
**************************************************************************************/



class Item;



//-------------------------------------------------------------------------------------------------


class Menu
{





private:
	

	/*este es un vector de punteros a las opciones del men�*/
	Item* Opcion[TOTAL_ITEMS];      //puse un puntero a puntero en lugar vector de punteros

	/*esta variable cuenta la cantidad de items agregados al men� (si sac�s o agreg�s se actualiza)*/
	int TotalItems;

	/*esta variable representa el item seleccionado dentro del men� (var�a entre 1 y TOTAL_ITEMS) */
	int Cursor;	

	/*esta variable te dice cu�nta es la cantidad de l�neas entre opci�n y opci�n en el men�*/
	int Division;

	/*esta es la funci�n que agrega las opciones al men�*/
	void AddItem(Item*);

	/*esta es la funci�n que imprime el men�*/
	void ImprimeMenu (void);

	/*esta funci�n saca el item del men�*/
	void QuitItem(Item*);




public:

	/*esta funci�n llama a la funci�n correspondiente al item seleccionado del men�*/
	void CallOption();

	Menu();

	~Menu();

	/*retorna el valor del item seleccionado del men�*/
	int GetSelection(void);

	/*setea la selecci�n del item del men�*/
	void SetSelection(int ItemNo);

	/*imprime un string a partir de la fila y columna indicada*/
	void PrintPositionedText (char* Str, int fila, int columna);
	


};


//-------------------------------------------------------------------------------------------------


class Item /*cada objeto de esta clase es una opci�n para meter en el men�*/
{




private:

	/*nombre de la opcion del menu*/
	char Nombre[20];

	/*puntero a la funci�n que va a llamar la opci�n*/
	void (*Action)();

	friend void Menu::ImprimeMenu(void);

	friend void Menu::CallOption(void);

public:

	/*el constructor recibe el texto de la opci�n y el puntero a la funci�n que llama la opci�n*/
	Item (char*,void(*)());



};