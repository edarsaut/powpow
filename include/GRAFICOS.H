/**************				definición de constantes		***********************/

//modos de la función rectángulo
#define VACIO 1
#define LLENO 2








/**************				declaración de funciones		***********************/

/*esta función hace todos esos pasos tediosos de poner el modo gráfico con interrupciones de bios*/
/*debería setear en modo 0DH: 320x200 16 colores*/
void PonerModoGrafico(void);

/*la función hace todos los pasos tediosos de imprimir un punto en pantalla en la coordenada X e Y con el color clr*/
void Punto (int X, int Y, int clr);


/*hace los pasos para poner en modo texto*/
void PonerModoTexto(void);


/*oculta el cursor*/
void OcultarCursor(void);


/*muestra el cursor*/
void MostrarCursor(void);


/*dibuja un rectángulo con extremo superior izquierdo en X1, Y1 y extremo inferior derecho en X2,Y2*/
void Rectangulo(int X1,int Y1,int X2,int Y2,int mode, int color);