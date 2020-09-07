

#include "main.h"


class Escenario;


class Tanque  
{




	friend void Juego(void);


private:


	/*Posición X de la punta de la torreta*/
	int TXPosition;
	
	/*Posición Y de la punta de la torreta*/
	int TYPosition;

	/*se toma como posición del tanque el píxel del medio de la base del tanque*/
	/*guarda la coordenada X del punto donde está el tanque*/
	int XPosition;

	/*guarda la coordenada Y del punto donde está el tanque*/
	int YPosition;

	struct Tiro {
		
		unsigned char Angulo;	
		
		unsigned char V0;

		int XV0;

		int YV0;

	
	} tiro;
	
	/*Almacena el color del tanquecito*/
	unsigned char Color;

	/*Pasa de coordenadas polarea a rectangulares los valores de la estructura tiro*/
	void PolToRec(void);

	/*tranforma un ángulo en grados en un ángulo en radianes*/
	double DegToRad(double grados);

	/*Dibuja el tanque que mide unos 8 píxels de alto por 9 de ancho*/
	void DibujaTanque(void);

	/*Borra el tanque (Se usa dentro de DibujaTanque() antes de dibujar a modo de refresh)*/
	void BorraTanque(void);

	/*Dibuja la torreta del tanque con la apuntada correspondiente*/
	void DibujaTorreta(void);

	/*comprueba si el tiro dio en el blanco, se fue a la mierda, pegó en el piso o nada*/
	int DioEnElBlanco(int x, int y, const Tanque* Rival, const Escenario* Piso);
	
public:

	/*permite al jugador setear un ángulo de tiro y una velocidad inicial de disparo*/
	void Apuntar(void);  
	
	/*construye el tanque dibujandolo, inicializando propiedades*/
	Tanque(int XPos,int YPos);
	
	~Tanque();

	/*hace el disparo de la bomba y retorna si pegó o pifió*/
	int Shoot (const Tanque* Rival, const Escenario* Piso);

	/*puntero a clase Escenario* para acceder desde las funciones sin andar pasándolo como param*/
//	const Escenario* Piso;

	/*flag para detectar la orden de salir*/
	int quit;


};
