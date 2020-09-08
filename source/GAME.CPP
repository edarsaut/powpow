#include "master.h"



#include "main.h"
#include "menu.h"
#include "game.h"
//#include "Tanque.h"
#include "Escenari.h"
#include "graficos.h"








//-------------------------------------------------------------------------------------------------


Game::Game()
{

	int YT1 = 0, YT2 = 0;


	PonerModoGrafico();	/*modo 0DH: 320x200 16 colores*/

	/*pongo el randomize para hacer aleatoria a la función random() que uso después*/
	randomize();

	YT1 = 4 + random (155);
	delay(7);
	YT2 = 4 + random (155);

	/*crea el primer tanque en una posición aleatoria X entre 10 y 110 e Y entre 1 y 160*/
	tanque1 = new Tanque(10 + random(100), YT1);

	delay(7);

	/*crea el segundo tanque en una posición aleatoria X entre 204 y 310 e Y entre 1 y 160*/
	tanque2 = new Tanque(310-random(106), YT2);

	/*crea el piso*/
	escenario = new Escenario(YT1, YT2);



}


//-------------------------------------------------------------------------------------------------


Game::~Game()
{


	delete tanque1;

	delete tanque2;

	delete escenario;



}