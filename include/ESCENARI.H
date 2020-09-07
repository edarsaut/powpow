


#include "Tanque.h"




class Escenario  
{



private:
/*
	unsigned char XPoint1; //coordenada X del primer punto donde comienza el desnivel del terreno

	unsigned char XPoint2; //coordenada X del segundo punto donde comienza el desnivel del terreno
*/

	int XPoint;	//coordenada X donde se produce el desnivel

	int YPoint1; //coordenada Y del primer punto donde comienza el desnivel del terreno

	int YPoint2; //coordenada Y del segundo punto donde comienza el desnivel del terreno




	/*declaración de función amiga*/
	friend int Tanque::DioEnElBlanco(int x, int y, const Tanque* Rival, const Escenario* Piso);

public:

	Escenario(int X1, int X2);


	~Escenario();


	/*dibuja el suelo del escenario*/
	void DibujaPiso(void);


};

