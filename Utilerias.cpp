#include "Utilerias.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
//Metodo para imprimir un mensaje.
void Utilerias::MostrarMensaje(std::string Mensaje, bool SaltoLinea){
    cout << Mensaje << endl;
}
//metodo para ajustar el tama�o de la pantalla.
void Utilerias::AjustarTamanoVentana(int ancho, int alto){
    HWND hwnd = GetConsoleWindow();
    SetWindowPos(hwnd, HWND_TOP, 0,0, ancho, alto, SWP_NOMOVE);
}
//Metodo para limpiar pantalla
void Utilerias::LimpiarPantalla(){
    system("cls");
}
//Leer texto
std::string Utilerias::LeerValorTexto(std::string Mensaje, int TamanoTexto){
    //Mostrar mensaje al usuario
    MostrarMensaje(Mensaje);
    //declarar variable para guardar el resultado.
    char TextoIngresadoPorUsuario[TamanoTexto] = "";
    //leer valor ingresado
    cin.getline(TextoIngresadoPorUsuario, TamanoTexto);
    //retornar el valor ingresado
    return TextoIngresadoPorUsuario;
}
int Utilerias::LeerValorNumerico(std::string Mensaje){
    //Mostrar mensaje al usuario
    MostrarMensaje(Mensaje);
    //declarar variable para guardar el resultado.
    int ValorIngresadoPorUsuario;
    //leer valor ingresado
    cin >> ValorIngresadoPorUsuario;
    //retornar el valor ingresado
    return ValorIngresadoPorUsuario;
}
//Metodo para imprimir el men�
int Utilerias::MenuPrincipal(){
    int Opcion;
    cout << ":::::::::::::::::" << endl;
    MoverCursor(0,1);
    cout << ":: Paint 1.0.0 ::" << endl;
    MoverCursor(0,1);
    cout << ":::::::::::::::::" << endl;
    MoverCursor(0,1);
    cout << "::1 Graficar   ::" << endl;
    MoverCursor(0,1);
    cout << "::2 Guardar    ::" << endl;
    MoverCursor(0,1);
    cout << "::3 Abrir      ::" << endl;
    MoverCursor(0,1);
    cout << ":::::::::::::::::" << endl;
    MoverCursor(0,1);
    cout << ">";
    cin >> Opcion;
    cin.ignore();
    if(Opcion == 1){
        MostrarSubMenuFiguras();
    }
    return 0;
}
int Utilerias::MostrarSubMenuFiguras(){
    int Opcion;
    MoverCursor(10,1);
    cout << ":::::::::::::::::" << endl;
    MoverCursor(0,1);
    cout << "::   Figuras   ::" << endl;
    MoverCursor(0,1);
    cout << ":::::::::::::::::" << endl;
    MoverCursor(0,1);
    cout << "::1 Triangulo  ::" << endl;
    MoverCursor(0,1);
    cout << "::2 Cuadrado   ::" << endl;
    MoverCursor(0,1);
    cout << "::3 Rectangulo ::" << endl;
    MoverCursor(0,1);
    cout << "::4 Circulo    ::" << endl;
    MoverCursor(0,1);
    cout << ":::::::::::::::::" << endl;
    MoverCursor(0,1);
    cout << ">";
    cin >> Opcion;
    cin.ignore();
}
void Utilerias::MostrarControles(){
    cout << "F12: Abrir menu | paint 1.0.0";
}
//variables de coordenadas.
int _coordenadaX = 0;
int _coordenadaY = 0;
//obtener coordenada x
int Utilerias::ObtenerCoordenadaX(){
    return _coordenadaX;
}
//obtener coordenada y
int Utilerias::ObtenerCoordenadaY(){
    return _coordenadaY;
}
//metodo para mover el cursor
void Utilerias::MoverCursor(int PosicionX, int PosicionY){
    //Asignar nuevos valores a las variables de coordenada para guardar la posicio.
    _coordenadaX += PosicionX;
    _coordenadaY += PosicionY;
    //verificar que el cursor no salga de la pantalla :D
    //verificar coordenada x
    if(_coordenadaX >= ObtenerColumnas()){
        _coordenadaX = 0;
        //_coordenadaY ;
    }
    else if(_coordenadaX < 0){
        _coordenadaX = ObtenerColumnas();
        //_coordenadaY--;
    }
    //verificar coordenada y
    if(_coordenadaY >= ObtenerFilas()){
        _coordenadaY = 0;
        //_coordenadaX ++;
    }
    else if(_coordenadaY < 0){
        //_coordenadaX--;
        _coordenadaY = ObtenerFilas()-1;
    }
    COORD CoordenadaNueva;
    CoordenadaNueva.X = _coordenadaX;
    CoordenadaNueva.Y = _coordenadaY;

    //asignar la nueva coordenada.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CoordenadaNueva);
}
void Utilerias::MoverACoordenada(int PosicionX, int PosicionY){
    COORD CoordenadaNueva;
    CoordenadaNueva.X = PosicionX;
    CoordenadaNueva.Y = PosicionY;
    _coordenadaX = PosicionX;
    _coordenadaY = PosicionY;
    //asignar la nueva coordenada.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CoordenadaNueva);
}
//Variables para guardar el tama�o de la pantalla
int _columnas;
int _filas;
void Utilerias::ObtenerTamanoDePantalla(){
    //buffer de la pantalla
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //obtener la informacion de la pantalla
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    //asignar las columnas de la pantalla
    _columnas = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    //asignar las filas de la pantalla
    _filas = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
//Obtener columnas
int Utilerias::ObtenerColumnas(){
    ObtenerTamanoDePantalla();
    return _columnas;
}
//Obtener filas
int Utilerias::ObtenerFilas(){
    ObtenerTamanoDePantalla();
    return _filas;
}
