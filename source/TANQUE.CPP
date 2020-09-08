#include "master.h"



#include "main.h"
#include "menu.h"
#include "game.h"
//#include "Tanque.h"
#include "Escenari.h"
#include "graficos.h"












//-------------------------------------------------------------------------------------------------



Tanque::Tanque(int XPos, int YPos)
{


	/*inicializa el flag para la salida*/
	quit = 0;

	/*se copian a las propiedades los valores de posición recibidos en el constructor*/
	XPosition = XPos;
	YPosition = YPos;

	tiro.Angulo = 90;
	tiro.V0 = 25;


	/*se elige al azar un color para pintar el tanque*/
//	randomize();
	do
	{
		Color = random(15);
		delay(7);
		
	} while (Color == 0x0A || Color == 0x00); //si el color que sale al azar es el negro o el verde se vuelve a probar


	/*se dibuja el tanque usando las propiedades antes almacenadas*/
	DibujaTanque();

	/*se dibuja la torreta en la posición inicial (ángulo de 90 grados)*/
	DibujaTorreta();

	
}


//-------------------------------------------------------------------------------------------------


Tanque::~Tanque()
{





}


//-------------------------------------------------------------------------------------------------


void Tanque::PolToRec(void)
{
	double angulo;

	angulo = DegToRad((double)(tiro.Angulo));

	tiro.XV0 = (int)(tiro.V0 * cos(angulo));

	tiro.YV0 = (int)(tiro.V0 * sin(angulo));



}


//-------------------------------------------------------------------------------------------------


void Tanque::DibujaTanque(void)
{

	int puntoX, puntoY;

	puntoX = XPosition-4; //inicializa puntoX para empezar a dibujar el tanque desde abajo a la izquierda
	puntoY = YPosition;	  //inicializa puntoY para dibujar la base	


	/*borra todo lo que hay en el espacio que va el tanque para corregir lo de la torreta*/
	BorraTanque();


	/*estos dos for dibujan las dos primeras filas de la base*/

	for (int i=0; i<2; i++, puntoY++) //filas a trazar
	{
		
		for (int j=0, puntoX = XPosition-4; j<9; j++, puntoX++) //ancho de fila

			Punto(puntoX, puntoY, Color);
	}
	
	
	puntoX = XPosition-3; //inicializa puntoX para las próximas dos filas que son más cortas
	puntoY = YPosition+2; //inicializa puntoY para las próximas dos filas

	/*estos dos for dibujan la tercera y cuarta fila de la base*/


	for (i=0; i<2; i++, puntoY++)
	{
		for (int j=0, puntoX = XPosition-3; j<7;j++, puntoX++)
			
			Punto(puntoX, puntoY, Color);

	}


	puntoX = XPosition-2; //inicializa puntoX para la próxima fila que es más corta todavía
	puntoY = YPosition+4; //inicializa puntoY para la última fila




	/*este último for dibuja la última línea del tanque*/
	for (int j=0; j<5; j++, puntoX++)
		Punto(puntoX, puntoY, Color);


}


//-------------------------------------------------------------------------------------------------


void Tanque::Apuntar(void)//tendría que hacer de devuelva un int para hacer un return en la función juego.
{

	int flag = 0;
	float angulo;


	Rectangulo( 4, 199-4, 105, 199-10, VACIO, Color); //parte de afuera de la barra de 102*12
     //	getch();

	Rectangulo( 5+((tiro.V0)/2), 199-5, 105,199 - 9, LLENO, 0x00); //relleno de la barra (inicialización)

	Rectangulo( 5, 199-5, 5+((tiro.V0)/2),199 - 9, LLENO, Color); //relleno de la barra (inicialización)


	do
	{
		
	
		delay(10); //40 milisegundos, 20 veces por segundo (probar bajando esto)
		
		
		
		switch (Tecla())
		{
		case AR:
			if (tiro.V0<200)
			{
				tiro.V0++;
				for(int i=0; i<5; i++)
					Punto(4+((tiro.V0)/2), 199-5-i, Color);

			}
			break;

		case AB:
			if (tiro.V0>0)
			{
				tiro.V0--;
				for(int i=0; i<5; i++)
					Punto(5+((tiro.V0)/2), 199-5-i, 0x00);
			}
			break;

		case DE:
			if (tiro.Angulo>0)
			{
				tiro.Angulo--;
				DibujaTanque();
				DibujaTorreta();
			}
			break;

		case IZ:

			if (tiro.Angulo<180)
			{
				tiro.Angulo++;
				DibujaTanque();
				DibujaTorreta();
			}
			break;

		case ENTER:

			flag = 1;
			break;

		case 'q':
			quit = 1;
			flag = 1;
			break;

		}


	} while (!flag);




}


//-------------------------------------------------------------------------------------------------


void Tanque::DibujaTorreta()
{

	int x, y;
	float fx, fy;
	double angulo;


	angulo = DegToRad((double)tiro.Angulo);


	x = (int)(10 * cos(angulo)); //componente x de la torreta

	y = (int)(10 * sin(angulo)); //componente y de la torreta

	
	fx = ((float)x)/10;
	fy = ((float)y)/10;


	for (int i=1; i<12; i++) // la maniobra del 1 y el 9 en lugar de 0 y 8 es para hacer 8 veces una cosa y poder meter la i adentro como multiplicador
	{

		TXPosition = (int)((float)XPosition +(float)i * fx);// se guarda la coordenada x del punto de la torreta a dibujar

		TYPosition =(int)((float)YPosition +(float)i * fy);// se guarda la coordenada y del punto de la torreta a dibujar

		Punto(TXPosition, TYPosition, Color); 


	}

	/*Una vez que salió del for queda cargado en TXPosition y TYPosition la coordenada de la punta de la torreta*/



}


//-------------------------------------------------------------------------------------------------


int Tanque::Shoot(const Tanque* Rival, const Escenario* Piso) // voy a tener que probar bastante acá, va a haber
{						// que corregir como la gran puta los multiplicadores en la ecuación cinemática

	int Res, x, y, tiempo = 1;
	
	float t;

	Res = NADA;

	x = TXPosition;

	y = TYPosition;
	
	PolToRec();


	do
	{

		t = ((float)tiempo)/75;
		
		delay(1); //30 ms para 30 fps aprox

		if (Res == NADA)
			Punto( x, y, Color);//dibuja el tiro en el aire


		x = (int)((float)TXPosition + ((float)(tiro.XV0)) * t); //ecuación de disparo en x (M.R.U.) - Creo que voy a tener que meter unos cuantos casteos mejor

		y = (int)((float)TYPosition + ((float)(tiro.YV0)) * t - 5 * t * t); //acá consideré a g como 10.. total ni se va a notar xD

		Res = DioEnElBlanco( x, y, Rival, Piso);

		if (Res == NADA)
			Punto(x, y, 0x0F); //dibuja la trayectoria del tiro (que salame, me la había olvidado)


		tiempo++;

	} while(Res == NADA); //acá saldría si la condición es "toca piso", "toca tanque" o "se va a la mierda"


	return Res;




}


//-------------------------------------------------------------------------------------------------


int Tanque::DioEnElBlanco(int x, int y, const Tanque* Rival, const Escenario* Piso) //acá hay que ver las condiciones de "toca piso", "toca tanque", "no toca nada por ahora" y "se fue a la mier.."
{


	/*primero vemos si se fue a la mierda*/
	if (x<0 || x>319)
		return MISS;





	/*ahora vemos si le dió al tanque*/

	if (((Rival->XPosition) - x) < 6 && ((Rival->XPosition) - x) > -6 ) //chequea si el tiro está píxels antes o 5 píxels después
		//si la coordenada x está en el rango de tanque chequeamos las coordenada Y 
		if ((y - (Rival->YPosition)) < 11 && (y - (Rival->YPosition)) >= 0)
			return BOOM;


		
	/*ahora vemos si pegó en el piso*/

	
	if (x < Piso->XPoint)			//está en el primer segmento del piso?
		if (y < Piso->YPoint1)		//toca el piso?
			return MISS;

	if (x > Piso->XPoint)			//está en el segundo segmento del piso?
		if (y < Piso->YPoint2)		//toca el piso?
			return MISS;

/*	float pendiente =(float) (((Piso->YPoint2)-(Piso->YPoint1))/((Piso->XPoint2)-(Piso->YPoint1)));

	if ((x > Piso->XPoint1) && (x < Piso->XPoint2))	//está en el segundo segmento del piso?
		if (y < (Piso->YPoint1)+pendiente*x)		//toca el piso inclinado?
			return MISS;
		
*/



	/*si no pasó nada de lo anterior el tiro todavía está en el aire, así que retornamos el valor correspondiente*/

	return NADA;



}


//-------------------------------------------------------------------------------------------------


void Tanque::BorraTanque(void)
{

	int puntoX, puntoY;

 //	puntoX = XPosition-6; 
	puntoY = YPosition;	  	


	/*estos dos for dibujan las dos primeras filas de la base*/

	for (int i=0; i<11; i++, puntoY++) //filas a trazar
	{
		
		for (int j=0, puntoX = XPosition-12; j<24; j++, puntoX++) //ancho de fila

			Punto(puntoX, puntoY, 0x00); //pinta de negro
	}
	


}


//-------------------------------------------------------------------------------------------------


double Tanque::DegToRad(double grados)
{

	
	return (grados * PI / 180);

	


}