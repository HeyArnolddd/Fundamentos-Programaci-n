//=========================================================================================================================================
//PROYECTO SNAKE 
//Este programa cumplira la función de emular al clasico juego de serpiente famoso en los clasicos celulares nokkia tambien llamado (snake)
//version 1.3
//Docente: Sergio gelvez 
//Fundamentos de programacion 
//===========================================================================================================================================

#include <iostream>//libreria para utilizar el input y el oupt
#include <stdlib.h>
#include <time.h>// para usar el srand 
#include <conio.h>// libreria que nos permite utilizar la funcion kbhit y getch para detectar pulsaciones por teclado 
#include <windows.h> // libreria que necesitaremos para la funcion sleep y para limpiar el terminal

using namespace std;//Permite tener un alcance directo a todas las funciones declaradas en un espacio de nombres "std"

//Variables
char simbolo1=186; // estas variables tipo caracter las usare principalmente para darle la forma a la serpiente y el tablero para que sea un  poco mas estetico
char simbolo2=205;
char simbolo3=254;
const int Horizontal = 50, Vertical = 20; // vamos a utulizar dos constantes para definir el tamaño del tablero de juego una que nos represente el eje x y otra que nos represente el eje y
int Cabeza[2], Comida[2], puntos; // definimos la funcion cabeza, comida y puntos, la cabeza y la comida como tendran una posicion bidimensional necesitan estar posicionadas en x,y por eso lo haremos tipo vector que define estas dos posiciones 
int ColaPosicionX[100], ColaPosicionY[100], LongitudCola; // la cola como puede tener varios tamaños le daremos un vector mas grande

enum DireccionEnum { STOP = 0, IZQUIERDA, DERECHA, ARRIBA, ABAJO }; // para la direccion de la serpiente vamos a usar enumeradores que son una serie de datos que son definidos por el usuario y tienen valores enteros consecutivos 
DireccionEnum DireccionSerpiente;

bool Moriste; // variable tipo bolean para determinar cuando es el fin del juego ejemplo: si chocas con una pared termina el juego 


void Inicializar() //donde se van a inicializar todo 
{
	system("cls"); // para que cuando inicie el juego limpie la pantalla directamente 
	//vamos a iniciar las posiciones que tendras los objetos visibles en el tablero
	Moriste = false;
	DireccionSerpiente = STOP;
	Cabeza[0] = Horizontal /2; // dividir el eje x en dos para que la cabeza este en el centro del eje
	Cabeza[1] = Vertical / 2; // dividir el eje y en dos igualmete y asi aseguramos que la cabeza de la serpiente inicie en la mitad del tablero
	Comida[0] = rand() % Horizontal;// de igual manera vamos a determinar la posicion de la comida en el tablero
	Comida[1] = rand() % Vertical;// pero usaremos la funcion rand para que sea de manera aleatoria 
	puntos = 0; // iniciamos la puntuacion en 0 por que no ha comido nada :v
}


void render()// renderizar todo en pantalla 
{
	//system("cls"); // importante si no ponemos esto va ha estar imprimiendo cada rato uno detras de otro
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
	for(int i = 0; i < Horizontal + 2; i++)// se pone mas 2 por que horizontal como vertical tiene dos columnas 
	{
		cout<<simbolo2; // este es el caracter que le dara la apariencia al borde del tablero
	}
	cout<<endl;

	for(int i = 0; i < Vertical + 2; i++) // igual manera cliclo para que se imprima la pared vertical
	{
		for(int j = 0; j < Horizontal; j++)// clico de nuestra condicon horizontal 
		{
			if(j == 0)// condicion para renderizar la fila
				cout<<simbolo1; // simbolo de la pared horizontal

			if(j == Cabeza[0] && i == Cabeza[1]) //condicon para renderizar la cabeza en el eje x, y
				cout<<simbolo3;

			else if(j == Comida[0] && i == Comida[1]) //si  no se cumple lo primero entonces tenemos el caso de renderizar la comida
				cout<<"*";

			else
			{
				bool ImprimirCola = false; //  Variable tipo bool para saber cuando imprimir la cola

				for(int k = 0; k < LongitudCola; k++) // ciclo para imprimir la cola 
				{

					if(ColaPosicionX[k] == j && ColaPosicionY[k] == i)
					{
						cout<<simbolo3;
						ImprimirCola = true;
					}
				}

				if(!ImprimirCola) // en caso contrario que la cola no este ocupando un espacio en el vector entonces imprimir espacio vacio 
					cout<<" ";
			}

			if(j == Horizontal - 1) // renderizar la otra parte de la fila 
				cout<<simbolo1;
		}

		cout<<endl;
	}

	for(int i = 0; i < Horizontal + 2; i++)
	{
		cout<<simbolo2;
	}

	cout<<endl<<endl;

	cout<<"PUNTOS: "<<puntos<<endl; // para mostar los puntos que llevamos en pantalla
}


void input() // para recoger la informacion que venga por teclado 
{
	if(_kbhit()) // en caso de detectar la pulsacion de una tecla
	{
		switch(_getch()) // usamos la funcion getch para optener cual fue la tecla que se presiono 
		{
			case 'a':
				DireccionSerpiente = IZQUIERDA;
				break;
			case 'd':
				DireccionSerpiente = DERECHA;
				break;
			case 'w':
				DireccionSerpiente = ARRIBA;
				break;
			case 's':
				DireccionSerpiente = ABAJO;
				break;
			case 'q':
				Moriste = true;
				break;
		}
	}
}


void LogicaGame() //  se va a encargar toda la logica del juego 
{
	// lo que queremos lograr es que la posicion anterior de la cola siga a la primera posicion de la cola 
	int PosicionPreviaX = ColaPosicionX[0];
	int PosicionPreviaY = ColaPosicionY[0];
	int PosicionPrevia2X, PosicionPrevia2Y;
// y tambien queremos que la primera posicion de la cola siga a la cabeza y asi hacer el efecto de movimiento 
	ColaPosicionX[0] = Cabeza[0];
	ColaPosicionY[0] = Cabeza[1];

	for(int i = 1; i < LongitudCola; i++) //obviamente se debe verificar todas las posiciones de la cola entonces usaremos un bucle for 
	{
		PosicionPrevia2X = ColaPosicionX[i];
		PosicionPrevia2Y = ColaPosicionY[i];

		ColaPosicionX[i] = PosicionPreviaX;
		ColaPosicionY[i] = PosicionPreviaY;

		PosicionPreviaX = PosicionPrevia2X;
		PosicionPreviaY = PosicionPrevia2Y;
	}

	//Move the snake
	switch(DireccionSerpiente)// para los casos de movimiento de la serpiente segun el teclado dirigida a la cabeza 
	{
		//VAMOS A DISMINUIR O RESTAR EN NUESTRA POSICION 0 O 1 DE NUESTRO VECTO QUE REPRESENTA EL EJE X,Y
		case STOP:// no hacer nada
			break;

		case IZQUIERDA: // como nuestra serpiente esta en un vector de dos direcciones, si queremos movernos a la izquierda le vamos a restar en la cordenada X
			Cabeza[0]--;
			break;

		case DERECHA:
			Cabeza[0]++; // como nuestra serpiente esta en un vector de dos direcciones, si queremos movernos a la derecha le vamos a sumar en la cordenada X
			break;

		case ARRIBA:
			Cabeza[1]--;  //como nuestra serpiente esta en un vector de dos direcciones, si queremos movernos hacia arriba le vamos a restar en la cordenada Y
			Sleep(8);
			break;

		case ABAJO:
			Cabeza[1]++; // como nuestra serpiente esta en un vector de dos direcciones, si queremos movernos hacia abajo le vamos a sumar en la cordenada Y
			Sleep(8);
			break;
	}

	// de manera sencilla sin mucha logica pues basicamente si la posicion de uno de los muros coincide con la posicion de la cabeza pues te moriste
	if(Cabeza[0] >= Horizontal || Cabeza[0] < 0 || Cabeza[1] >= Vertical || Cabeza[1] < 0)
		Moriste = true; // en caso de cumplise alguna de estas condiciones entonces morirse es verdadero y acaba el bucle while 

	for(int i = 0; i < LongitudCola; i++) // tambien queremos un bucle que revise en caso de que la posicion de nuestra cabeza choque con la posicion de la cola
	{
		if(ColaPosicionX[i] == Cabeza[0] && ColaPosicionY[i] == Cabeza[1])
			Moriste = true;
	}

// de igual manera 	que hicimos con los muros hacemos con la comida para dar la logica que la serpiente comio 
	if(Cabeza[0] == Comida[0] && Cabeza[1] == Comida[1])
	{
		puntos += 1; // cuando la serpiente come entonces vamos a aumentar la puntuacion 
		// cuando ya la serpiente comio entoces se debe generar otra cordenada nueva para la comida 
		Comida[0] = rand() % Horizontal;
		Comida[1] = rand() % Vertical;

		LongitudCola++; // como la serpiente comio entonces aumentamos nuestra variable de la
	}
}


//donde va ha correr todo el juego como tal y llamamos a los modulos que ya hicimos 
int main()
{
	srand(time(0));// para cuando usemos la funcion rand esta no repita los numeros aleatorios 

	Inicializar();// vamos a llamar todas las variables, es importante colocarlo arriba para que empiece el juego

	while(!Moriste)// creamos un bucle que diga que mientras no mueras pues seguimos jugando 
	{
		render();// llamamos al encargado de renderizar 
		Sleep(10); //como lo vamos a ejecutar por terminal usaremos la funcion sleep basicamente para bajar la velocidad 

		input();// llamamos a input para optener los datos del teclado 
		LogicaGame();//llamamos al que se encarga de nuestra logica del juego
	}
	cout << "PERDISTE :( VUELVE A INTENTARLO :)" << endl;
	return 0;
}