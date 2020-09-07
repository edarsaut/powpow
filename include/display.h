



/********************	asignaciones de cada bit de datos	******************



						D6	D5		D4		D3	D2	D1	D0
						BI*	LED*	LEI*	D	C	B	A


LEI* = Latch Enable Izquierdo
LED* = Latch Enable Derecho
BI* = Blanking Input (ambos displays)


******************************************************************************/




class Display
{





private:

	/*almacena la dirección base del puerto*/
	int Base;

	/*manda un byte al puerto paralelo*/
	void SendData(unsigned char data);




public:

	/*busca puertos LPT y guarda la dirección del primero que encuentra en Base*/
	Display();

	~Display();

	/*Manda los dos valores y los muestra en el display*/
	void Mostrar(unsigned char Iz, unsigned char De);
	
	/*Apaga poniendo blanking input en 0*/
	void Apagar(void);

	/*Prende poniedo blanking input en 1*/
	void Prender(void);



};

