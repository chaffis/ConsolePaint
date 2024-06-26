#include "Utilerias.h"
#include <iostream>
#include <string>
#include <windows.h>
#include "FiguraGeometricaCuadrado.h"
#include "FiguraGeometricaRectangulo.h"
#include "FiguraGeometricaTriangulo.h"
#include "FiguraGeometricaCirculo.h"
#include "FiguraGeometricaLinea.h"
#include "FiguraGeometricaRombo.h"
#include "FiguraGeometricaHexagono.h"
#include "Entidades.h"
#include <list>
#include "GestionArchivo.h"

using namespace std;
int _coordenadaXGuardada, _coordenadaYGuardada;
//Variables para guardar las ultimas figuras realizadas (ya no se uso)
Cuadrado _ultimoCuadrado;
Circulo _ultimoCirculo;
Rectangulo _ultimoRectangulo;
Triangulo _ultimoTriangulo;

//variables de coordenadas.
int _coordenadaX = 0;
int _coordenadaY = 0;
//Variables para guardar el tama�o de la pantalla
int _columnas;
int _filas;
//Caracter para escribir e iniciarlo en *
char _caracterDibujo = '*';
//Color de los caracteres:
int _colorCaracteres = 15; //iniciar el color principal en blanco :D
const int _colorTextoBlanco = 15;
//Lista de objetos con las coordenada en pantalla
std::list<PosicionPantalla> _posicionesEnPantalla;


//procedimiento para cambiar el color
void Utilerias::CambiarColor(int Color){
    //Obtener el output de la consola
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //colocar el buffer
    FlushConsoleInputBuffer(hConsole);
    //asignar el color :D
    SetConsoleTextAttribute(hConsole, Color);
}
void Utilerias::EscribirEnPantalla(std::string Mensaje, bool Borrar){
    int x = ObtenerCoordenadaX();
    int y = ObtenerCoordenadaY();
    //cambiar color del texto de la consola antes de graficar
    if(_colorCaracteres != 0){ // verificar que se escogiera un color
            CambiarColor(_colorCaracteres);
    }
    for(auto letra:Mensaje){
            //pasar al otro lado de la pantalla al llegar al borde :D
            if(x >= ObtenerColumnas()){
                x = 0;
            }
            //objeto con la posicion y el caracter.
            PosicionPantalla pos;
            pos.CoordenadaX = x;
            pos.CoordenadaY = y;
            pos.Caracter = letra;
            pos.Color = _colorCaracteres;
            if(letra != ' ')
                _posicionesEnPantalla.push_back(pos);
            else if(letra == ' ' && Borrar)
                _posicionesEnPantalla.push_back(pos);
        x++;
    }
    cout << Mensaje;
    MoverACoordenada(x, y, true);

    //Revertir el cambio de color :D
    CambiarColor(_colorTextoBlanco);
}
void Utilerias::ReescribirEnPantalla(){
    //Recorrer todos los caracteres que estan en la lista de caracteres graficados :D
    for(auto CaracterPantalla:_posicionesEnPantalla){
        //Mover a la coordenada que indique el caracter
        MoverACoordenada(CaracterPantalla.CoordenadaX, CaracterPantalla.CoordenadaY, true);
        //cambiar el color del caracter antes de escribirlo en la pantalla
        CambiarColor(CaracterPantalla.Color);
        cout << CaracterPantalla.Caracter;
    }
    //al terminar cambiar el color al color blanco.
    CambiarColor(_colorTextoBlanco);
}
//Metodo para imprimir un mensaje.
void Utilerias::MostrarMensaje(std::string Mensaje, bool SaltoLinea){
    //Guardar coordenadas
    GuardarCoordenadasActuales();
    //Mover al final de y
    MoverACoordenada(0, ObtenerFilas()-1, true);
    cout << "[Mensaje] " << Mensaje << " ";
    system("pause");
    MoverACoordenada(_coordenadaXGuardada, _coordenadaYGuardada, true);
    //reescribir
    LimpiarPantalla();
    ReescribirEnPantalla();
    MostrarControles();
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
    //Guardar coordenadas
    GuardarCoordenadasActuales();
    //Mover al final de y
    MoverACoordenada(0, ObtenerFilas()-1, true);
    cout << "[Texto] " << Mensaje << " ";
    //declarar variable para guardar el resultado.
    char TextoIngresadoPorUsuario[TamanoTexto] = "";
    //leer valor ingresado
    cin.getline(TextoIngresadoPorUsuario, TamanoTexto);
    cin.ignore();
    MoverACoordenada(_coordenadaXGuardada, _coordenadaYGuardada, true);
    //reescribir
    LimpiarPantalla();
    ReescribirEnPantalla();
    MostrarControles();
    //retornar el valor ingresado
    return TextoIngresadoPorUsuario;
}
int Utilerias::LeerValorNumerico(std::string Mensaje){
    //Guardar coodenadas
    GuardarCoordenadasActuales();
    //Mostrar mensaje al usuario
    MoverACoordenada(0, ObtenerFilas()-1, true);
    //mostrar mensaje
    cout << "[Numero] " << Mensaje << " ";
    //declarar variable para guardar el resultado.
    int ValorIngresadoPorUsuario;
    //leer valor ingresado
    cin >> ValorIngresadoPorUsuario;
    cin.ignore();
    MoverACoordenada(_coordenadaXGuardada, _coordenadaYGuardada, true);
    //reescribir
    LimpiarPantalla();
    ReescribirEnPantalla();
    MostrarControles();
    //retornar el valor ingresado
    return ValorIngresadoPorUsuario;
}
//Metodo para imprimir el men� -- ya no se usa por fase 2
int Utilerias::MenuPrincipal(){
    int Opcion;
    GuardarCoordenadasActuales();
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
    switch(Opcion){
    case 1:
        Opcion = MostrarSubMenuFiguras();
        break;
    }
    return Opcion;
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
    switch(Opcion){
    case 1:
        MostrarSubMenuTriangulo();
        break;
    case 2:
        MostrarSubMenuCuadro();
        break;
    case 3:
        MostrarSubMenuRectangulo();
        break;
    case 4:
        MostrarSubMenuCirculo();
        break;
    }
    return Opcion;
}
void Utilerias::MostrarSubMenuCuadro(){
    GuardarCoordenadasActuales();
    //objeto cuadrado
    Cuadrado NuevoCuadrado;
    //Asignar Valores al objeto :D
    NuevoCuadrado.CoordenadaX = _coordenadaXGuardada;
    NuevoCuadrado.CoordenadaY = _coordenadaYGuardada;
    NuevoCuadrado.MostrarRelleno = false;
    NuevoCuadrado.Caracter = _caracterDibujo;

    //Usar funci�n para solicitar valores numericos :D
    NuevoCuadrado.Ancho = LeerValorNumerico("Ancho del cuadro:");
    //Clase para graficar cuadrado
    FiguraGeometricaCuadrado Cuadrado;
    Cuadrado.ImprimirCuadrado(NuevoCuadrado);
}
void Utilerias::MostrarSubMenuRectangulo(){
    GuardarCoordenadasActuales();
    //Objeto Rectangulo
    Rectangulo NuevoRect;
    //asignar valores al objeto
    NuevoRect.CoordenadaX = _coordenadaXGuardada;
    NuevoRect.CoordenadaY = _coordenadaYGuardada;
    NuevoRect.MostrarRelleno = false;
    NuevoRect.Caracter = _caracterDibujo;


    //Solicitar valores al usuario
    NuevoRect.Ancho = LeerValorNumerico("Ancho del rectangulo:");
    NuevoRect.Alto = LeerValorNumerico("Alto del rectangulo:");

    FiguraGeometricaRectangulo Rectangulo;
    Rectangulo.ImprimirRectangulo(NuevoRect);

}
void Utilerias::MostrarSubMenuTriangulo(){
    GuardarCoordenadasActuales();
    //Objeto triangulo
    Triangulo NuevoTri;
    //Asignar los valores
    NuevoTri.CoordenadaX = _coordenadaXGuardada;
    NuevoTri.CoordenadaY = _coordenadaYGuardada;
    NuevoTri.MostrarRelleno = false;
    NuevoTri.Caracter = _caracterDibujo;

    //Solicitar la informaci�n al usuario
    NuevoTri.Base = LeerValorNumerico("Base del triangulo:");
    //Solicitar la orientaci�n
    int op;
    op = LeerValorNumerico("Orientacion: [^ = 1] [v = 2] [<- = 3] [-> = 4]");
    switch(op){
    case 1:
        NuevoTri.Arriba = true;
        NuevoTri.Abajo = false;
        NuevoTri.Izquierda = false;
        NuevoTri.Derecha = false;
        break;
    case 2:
        NuevoTri.Arriba = false;
        NuevoTri.Abajo = true;
        NuevoTri.Izquierda = false;
        NuevoTri.Derecha = false;
        break;
    case 3:
        NuevoTri.Arriba = false;
        NuevoTri.Abajo = false;
        NuevoTri.Izquierda = true;
        NuevoTri.Derecha = false;
        break;
    case 4:
        NuevoTri.Arriba = false;
        NuevoTri.Abajo = false;
        NuevoTri.Izquierda = false;
        NuevoTri.Derecha = true;
        break;
    default:
        NuevoTri.Arriba = true;
        NuevoTri.Abajo = false;
        NuevoTri.Izquierda = false;
        NuevoTri.Derecha = false;
        break;
    }
    FigurageometricaTriangulo Tri;
    Tri.ImprimirTriangulo(NuevoTri);
}
void Utilerias::MostrarSubMenuCirculo(){
    GuardarCoordenadasActuales();
    //Objeto circulo
    Circulo NuevoCirculo;
    //asignar valores
    NuevoCirculo.CoordenadaX = _coordenadaXGuardada;
    NuevoCirculo.CoordenadaY = _coordenadaYGuardada;
    NuevoCirculo.MostrarRelleno = false;
    NuevoCirculo.Caracter = _caracterDibujo;

    //Solicitar la informaci�n al usuario
    MoverCursor(0, 1);
    NuevoCirculo.Radio = LeerValorNumerico("Ingrese el radio del circulo:");

    FiguraGeometricaCirculo Cir;
    Cir.ImprimirCirculo(NuevoCirculo);
}
void Utilerias::MostrarSubMenuRombo(){
    //Guardar las coordenadas
    GuardarCoordenadasActuales();
    //Objeto rombo
    Rombo NuevoRombo;
    //Asignar valores
    NuevoRombo.CoordenadaX = _coordenadaXGuardada;
    NuevoRombo.CoordenadaY = _coordenadaYGuardada;
    NuevoRombo.Caracter = _caracterDibujo;

    //Solicitar la informaci�n al usuario
    NuevoRombo.Base = LeerValorNumerico("Ingrese la longitud de los lados:");
    int Orientacion;
    Orientacion = LeerValorNumerico("Orientacion [^ = 1] [v = 2]: ");

    switch(Orientacion){
    case 1:
        NuevoRombo.Arriba = true;
        break;
    default:
        NuevoRombo.Abajo = true;
        break;
    }

    FiguraGeometricaRombo Rom;
    Rom.ImprimirRombo(NuevoRombo);
}
void Utilerias::MostrarSubMenuLinea(){
    //Guardar coordenadas para dibujar el rombo
    //Ya no recuerdo para que se guardaban las coordenadas :(
    GuardarCoordenadasActuales();

    //Objeto linea
    Linea Lin;
    Lin.Caracter = _caracterDibujo;
    Lin.CoordenadaX = _coordenadaXGuardada;
    Lin.CoordenadaY = _coordenadaYGuardada;

    //Solicitar la informaci�n al usuario
    Lin.Longitud = LeerValorNumerico("Indique la longitud de la linea:");

    int Direccion;
    Direccion = LeerValorNumerico("Direccion [| = 1] [- = 2] [\\ = 3] [/ = 4]:");

    switch(Direccion){
        case 1:
            Lin.Vertical = true;
            Lin.Horizontal = false;
            Lin.InclinacionDerecha = false;
            Lin.InclinacionIzquierda = false;
            break;
        case 2:
            Lin.Vertical = false;
            Lin.Horizontal = true;
            Lin.InclinacionDerecha = false;
            Lin.InclinacionIzquierda = false;
            break;
        case 3:
            Lin.Vertical = false;
            Lin.Horizontal = false;
            Lin.InclinacionDerecha = true;
            Lin.InclinacionIzquierda = false;
            break;
        case 4:
            Lin.Vertical = false;
            Lin.Horizontal = false;
            Lin.InclinacionDerecha = false;
            Lin.InclinacionIzquierda = true;
            break;
    }


    //Objeto para graficar la linea
    FiguraGeometricaLinea NuevaLinea;
    NuevaLinea.ImprimirLinea(Lin);

}
void Utilerias::MostrarSubMenuHexagono(){
     //Guardar las coordenadas
    GuardarCoordenadasActuales();
    //Objeto rombo
    Hexagono NuevoHexagono;
    //Asignar valores
    NuevoHexagono.CoordenadaX = _coordenadaXGuardada;
    NuevoHexagono.CoordenadaY = _coordenadaYGuardada;
    NuevoHexagono.Caracter = _caracterDibujo;

    //Solicitar la informaci�n al usuario
    NuevoHexagono.Base = LeerValorNumerico("Ingrese la longitud de los lados:");

    FiguraGeometricaHexagono Hexa;
    Hexa.ImprimirHexagono(NuevoHexagono);
}
void Utilerias::MostrarSubMenuGuardarArchivo(){
    //Guardar las coordenadas
    GuardarCoordenadasActuales();
    //solicitar al usuario el nombre del archivo
    string NombreArchivo = LeerValorTexto("Ingrese el nombre para el archivo:", 50);
    //Asignar extensi�n
    NombreArchivo += ".txt";
    //Clase de gesti�n de archivos
    GestionArchivo Archi;
    //Crear el achivo con el nombre que el usuario elija
    //Archi.CrearArchivo(NombreArchivo);
    //Exportar la pantalla al archivo recien creado
    Archi.Exportar(("Exportados\\" + NombreArchivo), _posicionesEnPantalla, ObtenerColumnas(), ObtenerFilas());
}
void Utilerias::MostrarSubMenuImportarArchivo(){
    //Guardar coordenadas
    GuardarCoordenadasActuales();
    //Solicitar nombre del archivo
    string NombreArchivo = LeerValorTexto("Ingrese el nombre del archivo a abrir:", 50);
    //agregar extensi�n
    NombreArchivo += ".txt";
    //Clase de gesti�n de archivos
    GestionArchivo Archi;
    list<PosicionPantalla> Resultado = Archi.LeerArchivo(("Exportados\\" + NombreArchivo), ObtenerFilas(), ObtenerColumnas(), _colorCaracteres, _caracterDibujo);

    _posicionesEnPantalla = Resultado;
    ReescribirEnPantalla();

}
void Utilerias::MostrarControles(){
    MoverACoordenada(0,0, true);
    cout << "F1: Triangulo | F2: Cuadrado | F3: Rectangulo | F4: Circulo | F5: Linea | F6: Rombo | F7: Hexagono | F8: Nuevo Caracter" << endl;
    cout << "F9: Limpiar Pantalla | F10: Color de Caracter | F12: Grabar Pantalla | Ctrl+A: Abrir archivo |Esc: Salir | paint 1.5.0";
}

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
void Utilerias::MoverACoordenada(int PosicionX, int PosicionY, bool PermitirCero){
    //Asignar nuevos valores a las variables de coordenada para guardar la posicio.
    if(PosicionX != 0)
        _coordenadaX = PosicionX;
    if(PosicionY != 0)
        _coordenadaY = PosicionY;
    if(PermitirCero){
        _coordenadaX = PosicionX;
        _coordenadaY = PosicionY;
    }
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
//obtener el tama�o de la pantalla actual
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
//Guardar coordenadas actuales en las variables.
void Utilerias::GuardarCoordenadasActuales(){
    _coordenadaXGuardada = ObtenerCoordenadaX();
    _coordenadaYGuardada = ObtenerCoordenadaY();
}
//Simular tecla
void Utilerias::SimularTecla(WORD Tecla){
     //simular F11 para pantalla completa
    INPUT Entrada;
    //Evento del teclado
    Entrada.type = INPUT_KEYBOARD;
    Entrada.ki.wScan = 0;
    Entrada.ki.time = 0;
    Entrada.ki.dwExtraInfo = 0;

    //Ingreso de la tecla F11
    Entrada.ki.wVk = Tecla;
    Entrada.ki.dwFlags = 0;
    //Enviar la tencla a ser presionada.
    SendInput(1, &Entrada, sizeof(INPUT));
}

//Obtener el caracter de dibujo actual.
char Utilerias::ObtenerCaracterDibujo(){

    cout << "EL caracter para graficar actual es: " << _caracterDibujo;
    return _caracterDibujo;
}
//Asignar un nuevo caracter para dibujar
void Utilerias::AsignarCaracterDibujo(){
     //Guardar coodenadas
    GuardarCoordenadasActuales();
    //mover
    MoverACoordenada(0, ObtenerFilas()-1, true);
    //solicitar la informaci�n
    cout << "[char] Ingrese el nuevo caracter para graficar: ";
    cin >>_caracterDibujo;
    //Mostrar mensaje al usuario
    MoverACoordenada(_coordenadaXGuardada, _coordenadaYGuardada, true);
    //reescribir
    LimpiarPantalla();
    ReescribirEnPantalla();
    MostrarControles();
}

//Cambiar el color
void Utilerias::CambiarColor(){

    //Guardar coodenadas
    GuardarCoordenadasActuales();
    //Mover
    MoverACoordenada(0, ObtenerFilas()-1, true);
    //Solicitar la informaci�n

    //Seleccionar
    int Opcion;
    cout << "Seleccione un color para el texto(1=Rojo, 2=Azul, 3=Verde, 4=Personalizado): ";
    cin >> Opcion;
    cin.ignore();

    //Mostrar mensaje al usuario
    MoverACoordenada(_coordenadaXGuardada, _coordenadaYGuardada, true);
    //reescribir
    LimpiarPantalla();
    ReescribirEnPantalla();
    MostrarControles();


    switch(Opcion){
        case 1:
            _colorCaracteres = FOREGROUND_RED;
            break;
        case 2:
            _colorCaracteres = FOREGROUND_BLUE;
            break;
        case 3:
            _colorCaracteres = FOREGROUND_GREEN;
            break;
        case 4:
    //Mover
    MoverACoordenada(0, ObtenerFilas()-1, true);
    //Solicitar la informaci�n

    //Seleccionar
    cout << "Ingrese el codigo de color: ";
            cin >> _caracterDibujo;
            cin.ignore();
            break;

    //Mostrar mensaje al usuario
    MoverACoordenada(_coordenadaXGuardada, _coordenadaYGuardada, true);
    //reescribir
    LimpiarPantalla();
    ReescribirEnPantalla();
    MostrarControles();

    }
}
//Elimiar registros de pantalla
void Utilerias::EliminarRegistrosDePantalla(){
    _posicionesEnPantalla.clear();
}

//Esto ya no lo use, la idea era tener un registro de cada una de las ultimas figuras graficadas, no fue necesario al final :D
Cuadrado Utilerias::ObtenerUltimoCuadrado(){
    return _ultimoCuadrado;
}
Circulo Utilerias::ObtenerUltimoCirculo(){
    return _ultimoCirculo;
}
Triangulo Utilerias::ObtenerUltimoTriangulo(){
    return _ultimoTriangulo;
}
Rectangulo Utilerias::ObtenerUltimoRectangulo(){
    return _ultimoRectangulo;
}
