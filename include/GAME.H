
  

#include "main.h"



class Tanque;
class Escenario;


   


class Game {






private:

	/*puntero a clase del tipo escenario*/
	Escenario* escenario;

	/*puntero a clase del tipo tanque (para el tanque del primer jugador)*/
	Tanque* tanque1;

	/*puntero a clase del tipo tanque (para el tanque del segundo jugador)*/
	Tanque* tanque2;

	/*declaración de función amiga*/
	friend void Juego(void);


public:


	/*crea dos objetos de la clase tanque y uno de la clase escenario*/
	Game();

	/*destruye los objetos creados dinamicamente por el constructor*/
	~Game();



};