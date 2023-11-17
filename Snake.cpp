//=========================================================================================================================================
//PROYECTO SNAKE 
//Este programa cumplira la función de emular al clasico juego de serpiente famoso en los clasicos celulares nokkia tambien llamado (snake)
//version 1
//Docente: Sergio gelvez 
//Fundamentos de programacion 
//===========================================================================================================================================

#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

using namespace std;
//voy a crear las funciones para el funcionamiento del juego, uno para iniciar las variables (variables), uno para renderizar los muros
//la serpiente y la comida(render), otro modulo que funcione como un input para resivir la informacion del teclado para movilizar la serpierte
//(input) y una funcion para realizar toda la logica del juego (logic)
bool gameOver;
// con la variable tipo boleana una variable de este tipo puede tener valores true y false entonces la usare para determinar cuando acabe el juego
const int X=60, Y=40;
// asi asigno dos constantes necesarias para determinar el tamaño del tablero del juego (el tablero del juego funcionara basicamente como si fuera un matriz)
int Cabeza[2], Comida[2];
int Puntos;//variable tipo entera para almacenar los puntos 

enum direccionEnum {STOP=0,LEFT,RIGHT,UP,DOWN}; // usando la variable "enum" para como dice enumerar constantes simbolicas
direccionEnum snakeDirection;
//con vectores de dos posiciones X,Y para asignar la posicion de la cabeza de la serpiente como de la comida
void init()
{
    system("cls");// usando el cls que siempre se usa para limpiar la pantallada 
 //vamos a asignar que la serpiente inicie en la mitad del tablero
    Cabeza[0]=X/2;
    Cabeza[1]=Y/2;
// para que la comida aparezca aleatoriamente en el tablero
    Comida[0]=rand()%X;
    Comida[1]=rand()%Y;
    snakeDirection=STOP; //entonces diciendo que snakeDirection=STOP para que inicie parada la serpiente
    Puntos=0;// iniciar con 0 puntos claro hasta que coma la serpiente 
    gameOver = false;
}
void render()
{
    for(int i=0; i<Y+2; i++)//se pone +2 por que hay que tener en cuenta que los bordes del tablero son dos en vertical 
        {
            char caracter1=186;
            cout<<caracter1;// con un caracter especial diremos que lo imprima para determinar los bordes del programa 
        }

    for(int i=0; i<X+2; i++) 
        {
            char caracter2=205;
            cout<<caracter2;
        }
}
void input()
{

}
void gameLogic()
{

}

int main()
{
    srand(time(0));
    init();//metodo init para inicializar todas las variables antes de que empiece el juego 
    while(!gameOver)//condición para que mientras gameOver sea falso entonces el juego continue
    {
        //voy a empezar a llamar todas mis funciones 
        render(); 
        input();
        gameLogic();
        Sleep(50);
        

    }
}