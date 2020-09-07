

/***********************        Librerías             *************************/
/*
#include "main.h"
#include "menu.h"
#include "game.h"
#include "Tanque.h"
#include "Escenari.h"
#include "graficos.h"

*/

#include <iostream.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
#include <stdio.h>




/***********************   Definiciones de constantes  ************************/


//constantes para la función Tecla()
//arriba 72, abajo 80, izquierda 75, derecha 77

#define AR		72
#define AB		80
#define IZ		75
#define DE		77
#define ENTER	13





//constantes de retorno de la funcíón Tanque::DioEnElBlanco

#define BOOM 1	//para cuando le pega al tanque
#define NADA 2	//para cuando todavía no tocó nada (o sea el tiro está en el aire todavía)
#define MISS 3	//para cuando pega en el piso o se va a la mierda





//constantes misceláneas
#define TOTAL_ITEMS 2
#define PI 3.141592

