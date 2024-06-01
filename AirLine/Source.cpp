#include <Windows.h>
#include "resource.h"
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <conio.h>
#include "commctrl.h"
#include <stdio.h>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <atlstr.h>
#include <format>  
#include <oleauto.h> //Administrar fechas
//#include <winuser.h>

using namespace std;
bool redirection = false;

// Estructuras
#pragma region Structs
struct DatoUsuario {
	int type;
	char nick[30];
	char nombre[30];
	char apellidoP[30];
	char apellidoM[30];
	char nombreComp[60];
	char password[30];
	double nacimiento;
	int genero;
	char email[100];
	char foto[500];
	double registro;
};
struct NodoUsuario
{
	DatoUsuario* dato;
	NodoUsuario* ant;  //Izquierda
	NodoUsuario* sig;  //Derecha
};
NodoUsuario* iniUsuario, * auxUsuario, * auxUsuario2, * auxUsuario3, * miUsuario = nullptr;

struct DatoVuelo {
	char usuarioRegistro[30];
	char origen[30];
	char destino[30];
	char modelo[30];
	int asientos;
	int asientosT;
	int asientosE;
	int asientosCT;
	int asientosCE;
	int asientosN;
	int asientosA;
	int asientosM;
	int num;
	int status;
	double fecha;
	double registro;
	//char claveChar[20];
};
struct NodoVuelo
{
	DatoVuelo* dato;
	NodoVuelo* ant;
	NodoVuelo* sig;
};
NodoVuelo* iniVuelo, * auxVuelo, * auxVuelo2, * auxVuelo3 = nullptr;

struct DatoBoleto {
	char nombreCompPasajero[60];
	int numVuelo;
	int num;
	int clase;
	int pase;
	int status;
	double registroBoleto;
	double registroPase;
	char usuarioRegistro[30];
	//char diasChar[30];
};
struct NodoBoleto
{
	DatoBoleto* dato;
	NodoBoleto* ant;
	NodoBoleto* sig;
};
NodoBoleto* iniBoleto, * auxBoleto, * auxBoleto2, * auxBoleto3 = nullptr;

struct DatoPasajero {
	char usuarioRegistro[30];
	char nombre[30];
	char apellidoP[30];
	char apellidoM[30];
	char nombreComp[60];
	char nacionalidad[20];
	int genero;
	int num;
	double nacimiento;
	double registro;
};
struct NodoPasajero
{
	
	DatoPasajero* dato;
	NodoPasajero* ant;
	NodoPasajero* sig;
};
NodoPasajero* iniPasajero, * auxPasajero, * auxPasajero2, * auxPasajero3 = nullptr;

#pragma region Structs Fijos

int i = 0;

// Nacionalidades
struct nacionalidad
{
	nacionalidad* ant;
	char Nacionalidad[30];
	nacionalidad* sig;
};
nacionalidad* ini, * aux = nullptr;
// Modelos
struct modelo
{
	modelo* ant;
	char Modelo[30];
	int asientos;
	int asientosT;
	int asientosE;
	int asientosCT;
	int asientosCE;
	int asientosN;
	int asientosA;
	int asientosM;
	modelo* sig;
};
modelo* ini2, * aux2 = nullptr;
// Lugares
struct lugar
{
	lugar* ant;
	char Lugar[30];
	lugar* sig;
};
lugar* ini3, * aux3 = nullptr;

#pragma endregion
#pragma endregion

HINSTANCE hInstanceGlobal = 0;
bool inicio = false;
char zFile[MAX_PATH]; //256 caracteres
HWND hDialog1 = 0;

#pragma region CallBacks
BOOL CALLBACK cDialog1(HWND, UINT, WPARAM, LPARAM); // Inicio
BOOL CALLBACK cDialog2(HWND, UINT, WPARAM, LPARAM); // Registro
bool cMenu(HWND hWnd, long opcion);
BOOL CALLBACK cDialog3(HWND, UINT, WPARAM, LPARAM); // Perfil
BOOL CALLBACK cDialog4(HWND, UINT, WPARAM, LPARAM); // Lista Usuarios
BOOL CALLBACK cDialog5(HWND, UINT, WPARAM, LPARAM); // Registro Vuelos
BOOL CALLBACK cDialog6(HWND, UINT, WPARAM, LPARAM); // Lista Vuelos
BOOL CALLBACK cDialog7(HWND, UINT, WPARAM, LPARAM); // Manifiesto
BOOL CALLBACK cDialog8(HWND, UINT, WPARAM, LPARAM); // Manifiesto2
BOOL CALLBACK cDialog9(HWND, UINT, WPARAM, LPARAM); // Reporte Vuelos
BOOL CALLBACK cDialog10(HWND, UINT, WPARAM, LPARAM); // Registro Pasajeros
BOOL CALLBACK cDialog11(HWND, UINT, WPARAM, LPARAM); // Lista Pasajeros
BOOL CALLBACK cDialog12(HWND, UINT, WPARAM, LPARAM); // Boletos
BOOL CALLBACK cDialog13(HWND, UINT, WPARAM, LPARAM); // Boletos2
BOOL CALLBACK cDialog14(HWND, UINT, WPARAM, LPARAM); // Pase abordar
#pragma endregion

//Prototipos
#pragma region Prototipos
#pragma region Generales
char* formatoFecha(LPSYSTEMTIME, char*);
int formatoEdad(double fecha);
bool adminComprobation(NodoUsuario*);
#pragma endregion

#pragma region Funciones de Listas Usuarios
void nuevoUsuarioLista(NodoUsuario* nuevo);
void eliminarUsuarioLista(char nomUsu[30]);
void escribirUsuarios();
void leerUsuarios();
//QuickSort
void swapData(NodoUsuario*, NodoUsuario*);
NodoUsuario* lastNode(NodoUsuario*);
NodoUsuario* partitionNick(NodoUsuario*, NodoUsuario*);
void _quickSortNick(NodoUsuario*, NodoUsuario*);
void quickSortNick(NodoUsuario*);
//void printListNick(NodoUsuario*);
//Arbol
NodoUsuario* sortedListToBST(NodoUsuario*);
NodoUsuario* sortedListToBSTRecur(NodoUsuario**, int);
int countNodes(NodoUsuario*);
NodoUsuario* BinaryTree2DoubleLinkedList(NodoUsuario*);
NodoUsuario* newNode(DatoUsuario*);
void insertTree(NodoUsuario*&, NodoUsuario*);
NodoUsuario* searchTree(struct NodoUsuario*, DatoUsuario*);
NodoUsuario* deleteTreeNodeByNick(NodoUsuario*, char*);

void preOrderList(NodoUsuario*, HWND);
void inOrderList(NodoUsuario*, HWND);
#pragma endregion

#pragma region Funciones de Listas Vuelos
void nuevoVuelo(NodoVuelo* nueva);
void eliminarVuelo(char vuelo[30]);
void escribirVuelo();
void leerVuelos();
void reporteVuelos(HWND, int);
void printVuelosEnRango(HWND, int, NodoVuelo*, DATE, DATE);
void generarManifiestoPasajeros(NodoBoleto*, int, const char*);
NodoVuelo* binarySearchNumVuelo(NodoVuelo*, int);
NodoVuelo* loopSearchNumVuelo(NodoVuelo*, int);
void SetRegistroVuelos(HWND, int, int, int);
//QuickSort
void swapData(NodoVuelo*, NodoVuelo*);
NodoVuelo* lastNode(NodoVuelo*);
NodoVuelo* partitionNum(NodoVuelo*, NodoVuelo*);
void _quickSortNum(NodoVuelo*, NodoVuelo*);
void quickSortNum(NodoVuelo*);

NodoVuelo* partitionFechaOldToNew(NodoVuelo*, NodoVuelo*);
void _quickSortFechaOldToNew(NodoVuelo*, NodoVuelo*);
void quickSortFechaOldToNew(NodoVuelo*);

NodoVuelo* partitionFechaNewToOld(NodoVuelo*, NodoVuelo*);
void _quickSortFechaNewToOld(NodoVuelo*, NodoVuelo*);
void quickSortFechaNewToOld(NodoVuelo*);
#pragma endregion

#pragma region Funciones de Listas Boletos
void nuevoBoleto(NodoBoleto*);
//void eliminarBoleto(char);
void escribirBoletos();
void leerBoletos();
NodoBoleto* binarySearchNombreBoleto(NodoBoleto*, const char*);
NodoBoleto* loopSearchNombreBoleto(NodoBoleto*, const char*);
#pragma region QuickSort
//Generales
void swapData(NodoBoleto*, NodoBoleto*);
NodoBoleto* lastNode(NodoBoleto*);
//Específicas
NodoBoleto* partitionNumAsiento(NodoBoleto*, NodoBoleto*);
void _quickSortNumAsiento(NodoBoleto*, NodoBoleto*);
void quickSortNumAsiento(NodoBoleto*);

NodoBoleto* partitionNumVuelo(NodoBoleto*, NodoBoleto*);
void _quickSortNumVuelo(NodoBoleto*, NodoBoleto*);
void quickSortNumVuelo(NodoBoleto*);

NodoBoleto* partitionNomPasajero(NodoBoleto*, NodoBoleto*);
void _quickSortNomPasajero(NodoBoleto*, NodoBoleto*);
void quickSortNomPasajero(NodoBoleto*);

void printBoletosDeVueloList(HWND, int, NodoBoleto*, int);
void printList(NodoBoleto*);
#pragma	endregion
#pragma endregion

#pragma region Funciones de Listas Pasajeros (Pacientes)
void nuevoPasajero(NodoPasajero* nuevoPas);
void eliminarPasajero(char NodoPasajero[60]);
void escribirPasajeros();
void leerPasajeros();
void reportePasajeros(); //No es necesario
NodoPasajero* binarySearchNombrePasajero(NodoPasajero*, const char*);
NodoPasajero* loopSearchNombrePasajero(NodoPasajero*, const char*);

void swapData(NodoPasajero* a, NodoPasajero* b);
void heapify(NodoPasajero* head, int n, NodoPasajero* NodoUsuario);
void heapSort(NodoPasajero* head);
#pragma endregion
#pragma endregion

// Puntero - Handler
int WINAPI WinMain(
	HINSTANCE hInstance,  // Dirección de memoria de la App
	HINSTANCE hPreveInstance,  // Instancia previa (null)
	PSTR cmdLine,  // Comandos de línea para la ejecución
	int showCmd  // Metodo de inicialización
	) {
	hInstanceGlobal = hInstance;
	leerUsuarios();
	//Se transforma a un arbol
	iniUsuario = sortedListToBST(iniUsuario);
	leerVuelos();
	leerBoletos();
	leerPasajeros();

	// Asignacion de valores fijos
	#pragma region Valores fijos
	// Nacionalidades
	for (i = 1; i < 5; i++)
	{
		if (ini == nullptr)
		{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
			ini = new nacionalidad;

			strcpy_s(ini->Nacionalidad, "México"); //6am-6pm

			ini->sig = nullptr;
			ini->ant = nullptr;

			aux = ini;
		}
		else
		{
			aux = ini;

			while (aux->sig != nullptr)
			{
				aux = aux->sig;
			}

			aux->sig = new nacionalidad;
			aux->sig->sig = nullptr;
			aux->sig->ant = aux;
			aux = aux->sig;

			if (i == 2)
			{
				strcpy_s(aux->Nacionalidad, "Estados Unidos");
			}
			else if (i == 3)
			{
				strcpy_s(aux->Nacionalidad, "Brasil");
			}
			else
			{
				strcpy_s(aux->Nacionalidad, "Argentina");
			}

			aux = ini;
		}

	}
	// Modelos
	for (i = 1; i < 4; i++)
	{
		if (ini2 == nullptr)
		{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
			ini2 = new modelo;

			strcpy_s(ini2->Modelo, "Bombardier CRJ-900");
			ini2->asientos = 76;
			ini2->asientosT = 67;
			ini2->asientosE = 9;
			ini2->asientosCT = 1200;
			ini2->asientosCE = 2100;
			ini2->asientosN = 8;
			ini2->asientosA = 57;
			ini2->asientosM = 11;

			ini2->sig = nullptr;
			ini2->ant = nullptr;

			aux2 = ini2;
		}
		else
		{
			aux2 = ini2;

			while (aux2->sig != nullptr)
			{
				aux2 = aux2->sig;
			}

			aux2->sig = new modelo;
			aux2->sig->sig = nullptr;
			aux2->sig->ant = aux2;
			aux2 = aux2->sig;

			if (i == 2)
			{
				strcpy_s(aux2->Modelo, "Boeing 737");
				aux2->asientos = 166;
				aux2->asientosT = 150;
				aux2->asientosE = 16;
				aux2->asientosCT = 1500;
				aux2->asientosCE = 3000;
				aux2->asientosN = 17;
				aux2->asientosA = 124;
				aux2->asientosM = 25;
			}
			else
			{
				strcpy_s(aux2->Modelo, "Boeing 777");
				aux2->asientos = 276;
				aux2->asientosT = 152;
				aux2->asientosE = 124;
				aux2->asientosCT = 1800;
				aux2->asientosCE = 4200;
				aux2->asientosN = 28;
				aux2->asientosA = 207;
				aux2->asientosM = 41;
			}

			aux2 = ini2;
		}

	}
	// Lugares
	for (i = 1; i < 9; i++)
	{
		if (ini3 == nullptr)
		{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
			ini3 = new lugar;

			strcpy_s(ini3->Lugar, "México");

			ini3->sig = nullptr;
			ini3->ant = nullptr;

			aux3 = ini3;
		}
		else
		{
			aux3 = ini3;

			while (aux3->sig != nullptr)
			{
				aux3 = aux3->sig;
			}

			aux3->sig = new lugar;
			aux3->sig->sig = nullptr;
			aux3->sig->ant = aux3;
			aux3 = aux3->sig;

			if (i == 2)
			{
				strcpy_s(aux3->Lugar, "Estados Unidos");
			}
			else if (i == 3)
			{
				strcpy_s(aux3->Lugar, "Brasil");
			}
			else if (i == 4)
			{
				strcpy_s(aux3->Lugar, "Argentina");
			}
			else if (i == 5)
			{
				strcpy_s(aux3->Lugar, "México - Ciudad de México");
			}
			else if (i == 6)
			{
				strcpy_s(aux3->Lugar, "México - Nuevo León");
			}
			else if (i == 7)
			{
				strcpy_s(aux3->Lugar, "México - Sonora");
			}
			else if (i == 8)
			{
				strcpy_s(aux3->Lugar, "México - Veracruz");
			}
			else
			{
				strcpy_s(aux3->Lugar, "México - Queretaro");
			}

			aux3 = ini3;
		}

	}
#pragma endregion

	// Puntero al Dialog1
	hDialog1 = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, cDialog1);

	//Mostrar el Dialog
	ShowWindow(hDialog1, showCmd);
	UpdateWindow(hDialog1);  // Opcional

	// Variable para el manejo de Message
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);  // Traduce los eventos de lenguaje máquina a enteros
		DispatchMessage(&msg); // Envía el evento traducido a mi dialogo
	}

	//Se vuelve a transformar a lista
	iniUsuario = BinaryTree2DoubleLinkedList(iniUsuario);
	//quickSort(iniUsuario); //Parece no ser necesario
	escribirUsuarios();
	escribirVuelo();
	escribirBoletos();
	escribirPasajeros();
	//system("pause");
	return 0;
}

#pragma region FuncionesCallBack
// Inicio
BOOL CALLBACK cDialog1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			ifstream archivo("UsuarioCheck.txt");
			string linea;
			getline(archivo, linea);
			archivo.close();

			size_t pos = linea.find(",");
			string usuario = linea.substr(0, pos);
			string contrasena = linea.substr(pos + 1);

			if (!usuario.empty()) {
				SetDlgItemText(hwnd, IDC_EDIT1, usuario.c_str());
			}
			if (!contrasena.empty()) {
				SetDlgItemText(hwnd, IDC_EDIT2, contrasena.c_str());
			}
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDC_BUTTON1: // Registrarse
				{
					EndDialog(hwnd, 0);

					HWND hDialog2 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG2), 0, cDialog2);

					ShowWindow(hDialog2, SW_SHOW);
					UpdateWindow(hDialog2); //Opcional

					break;
				}
				case IDC_BUTTON2: // Iniciar sesion
				{
					BOOL recordar = IsDlgButtonChecked(hwnd, IDC_CHECK1);
					char usuBuscar[30];
					char passwordBuscar[15];

					GetDlgItemText(hwnd, IDC_EDIT1, usuBuscar, sizeof(usuBuscar));
					GetDlgItemText(hwnd, IDC_EDIT2, passwordBuscar, sizeof(passwordBuscar));
					
					DatoUsuario usuarioBuscar;
					strcpy_s(usuarioBuscar.nick, sizeof(usuarioBuscar.nick), usuBuscar);

					auxUsuario3 = searchTree(iniUsuario, &usuarioBuscar);

					if (auxUsuario3 == nullptr)
					{
						MessageBox(NULL, "No se encontró el usuario.", "AVISO", MB_OK | MB_ICONERROR);
					}
					else
					{
						if (strcmp(passwordBuscar, auxUsuario3->dato->password) == 0)
						{
							miUsuario = auxUsuario3;
							inicio = true;
							// Guardar el usuario y la contraseña en un archivo para recordarlo
							if (recordar) {
								ofstream archivo("UsuarioCheck.txt");
								archivo << miUsuario->dato->nick << "," << miUsuario->dato->password;
								archivo.close();
							}

							/*EndDialog(hwnd, 0);
							DialogBox(hInstGlobal, MAKEINTRESOURCE(105), hwnd, procVPrincipal);*/

							EndDialog(hwnd, 0);
							HWND hDialog3 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG3), 0, cDialog3);

							ShowWindow(hDialog3, SW_SHOW);
							UpdateWindow(hDialog3);
						}
						else
							MessageBox(NULL, "Contraseña incorrecta", "AVISO", MB_OK | MB_ICONERROR);
					}
					break;
				}
				case IDC_BUTTON3: // Salir
				{
					int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);

					switch (opc)
					{
						case IDYES:
						{
							DestroyWindow(hwnd);
							PostQuitMessage(0);
						}
						default: break;
					}
					break;
				}
				default: break;
			}
		break;
		}
		default: break;
	}
	return false;  // Un callback siempre retorna falso
}

// Registro
BOOL CALLBACK cDialog2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDC_BUTTON1: // Volver
				{
					if (miUsuario == nullptr)
					{
						EndDialog(hwnd, 0);

						HWND hDialog1 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG1), 0, cDialog1);

						ShowWindow(hDialog1, SW_SHOW);
						UpdateWindow(hDialog1); //Opcional
					}
					else
					{
						EndDialog(hwnd, 0);

						HWND hDialog3 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG3), 0, cDialog3);

						ShowWindow(hDialog3, SW_SHOW);
						UpdateWindow(hDialog3);
					}

					break;
				}
				case IDC_BUTTON2: // Registrarse
				{
					//Condicional para comprobar que no haya controles vacíos
					char nick[30];
					GetDlgItemText(hwnd, IDC_EDIT1, nick, sizeof(nick));
					char nombre[30];
					GetDlgItemText(hwnd, IDC_EDIT2, nombre, sizeof(nombre));
					char apellidoP[30];
					GetDlgItemText(hwnd, IDC_EDIT3, apellidoP, sizeof(apellidoP));
					char apellidoM[30];
					GetDlgItemText(hwnd, IDC_EDIT4, apellidoM, sizeof(apellidoM));
					char email[100];
					GetDlgItemText(hwnd, IDC_EDIT5, email, sizeof(email));
					char password[30];
					GetDlgItemText(hwnd, IDC_EDIT6, password, sizeof(password));

					// Verificar si los controles están vacíos
					if (strlen(nick) == 0 || strlen(nombre) == 0 || strlen(apellidoP) == 0 || strlen(apellidoM) == 0 || strlen(email) == 0 || strlen(password) == 0)
					{
						MessageBox(NULL, "Por favor, rellene todos los campos.", "AVISO", MB_OK | MB_ICONINFORMATION);
						break;
					}
					//Se verifica la edad
					HWND hDia = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
					SYSTEMTIME diaCumple = { 0 }; double dia;
					DateTime_GetSystemtime(hDia, &diaCumple);
					SystemTimeToVariantTime(&diaCumple, &dia);
					int edad = formatoEdad(dia);
					if (edad < 18 || edad > 120)
					{
						MessageBox(NULL, "No se pueden registrar menores de edad.", "AVISO", MB_OK | MB_ICONINFORMATION);
						break;
					}
					
					char usuBuscar[30];
					GetDlgItemText(hwnd, IDC_EDIT1, usuBuscar, sizeof(usuBuscar));

					DatoUsuario dataBuscar;
					strcpy_s(dataBuscar.nick, usuBuscar);

					// Buscar el usuario en el árbol
					NodoUsuario* usuarioExistente = searchTree(iniUsuario, &dataBuscar);

					// Si el usuario ya existe, mostrar un mensaje de error
					if (usuarioExistente != NULL)
					{
						MessageBox(NULL, "El nombre de usuario no esta disponible, pruebe con uno diferente.", "AVISO", MB_OK | MB_ICONINFORMATION);
						break;
					}
					DatoUsuario* data = new DatoUsuario;
					NodoUsuario* temp = new NodoUsuario;
					temp->dato = data;
					GetDlgItemText(hwnd, IDC_EDIT1, temp->dato->nick, sizeof(temp->dato->nick));
					GetDlgItemText(hwnd, IDC_EDIT2, temp->dato->nombre, sizeof(temp->dato->nombre));
					GetDlgItemText(hwnd, IDC_EDIT3, temp->dato->apellidoP, sizeof(temp->dato->apellidoP));
					GetDlgItemText(hwnd, IDC_EDIT4, temp->dato->apellidoM, sizeof(temp->dato->apellidoM));
					GetDlgItemText(hwnd, IDC_EDIT5, temp->dato->email, sizeof(temp->dato->email));
					GetDlgItemText(hwnd, IDC_EDIT6, temp->dato->password, sizeof(temp->dato->password));
						
					//Genero
					if ((IsDlgButtonChecked(hwnd, IDC_RADIO1) == BST_CHECKED))
					{
						temp->dato->genero = 1;
					}
					else
					{
						temp->dato->genero = 0;
					}
					temp->dato->nacimiento = dia;
					strcpy_s(temp->dato->foto, "");

					temp->sig = nullptr;
					temp->ant = nullptr;

					//Registro
					SYSTEMTIME fecha = { 0 };
					GetLocalTime(&fecha);
					SystemTimeToVariantTime(&fecha, &temp->dato->registro);

					//Se revisa si es el primer usuario
					if (iniUsuario == nullptr)
					{
						//Se guarda el nick y la contraseña en un archivo
						ofstream archivo("UsuarioAdmin.txt");
						archivo << temp->dato->nick << "," << temp->dato->password;
						archivo.close();
					}
					//nuevoUsuarioLista(temp);
					insertTree(iniUsuario, temp);
					MessageBox(NULL, "Se ha registrado el usuario con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);

					SetDlgItemText(hwnd, IDC_EDIT1, "");
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");
					SetDlgItemText(hwnd, IDC_EDIT5, "");
					SetDlgItemText(hwnd, IDC_EDIT6, "");

					if (miUsuario == nullptr) //Registro desde la pagina de inicio
					{
						auxUsuario3 = iniUsuario;

						while (auxUsuario3->sig != nullptr && strcmp(usuBuscar, auxUsuario3->dato->nick) != 0)
						{
							auxUsuario3 = auxUsuario3->sig;
						}

						miUsuario = auxUsuario3;
						inicio = true;

						EndDialog(hwnd, 0);

						HWND hDialog3 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG3), 0, cDialog3);

						ShowWindow(hDialog3, SW_SHOW);
						UpdateWindow(hDialog3);
					}
					else //Registro como administrador
					{
						EndDialog(hwnd, 0);

						HWND hDialog3 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG3), 0, cDialog3);

						ShowWindow(hDialog3, SW_SHOW);
						UpdateWindow(hDialog3);
					}

					break;
				}
				case IDC_BUTTON3: // Salir
				{
					int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);

					switch (opc)
					{
						case IDYES:
						{
							DestroyWindow(hwnd);
							PostQuitMessage(0);
						}
						default: break;
					}
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	return false;  // Un callback siempre retorna falso
}

// Perfil
BOOL CALLBACK cDialog3(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			if (miUsuario != nullptr)
			{
				SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nick);
				SetDlgItemText(hwnd, IDC_EDIT2, miUsuario->dato->nombre);
				SetDlgItemText(hwnd, IDC_EDIT3, miUsuario->dato->apellidoP);
				SetDlgItemText(hwnd, IDC_EDIT4, miUsuario->dato->apellidoM);
				SetDlgItemText(hwnd, IDC_EDIT8, miUsuario->dato->email);
				SetDlgItemText(hwnd, IDC_EDIT9, miUsuario->dato->password);

				//Genero
				if (miUsuario->dato->genero == 1)
				{
					SetDlgItemText(hwnd, IDC_EDIT5, "Masculino");
				}
				else
				{
					SetDlgItemText(hwnd, IDC_EDIT5, "Femenino");
				}

				//Edad/Nacimiento
				char cadenaNacimiento[100];
				SYSTEMTIME cumple = { 0 };
				VariantTimeToSystemTime(miUsuario->dato->nacimiento, &cumple);
				formatoFecha(&cumple, cadenaNacimiento);
				SetDlgItemText(hwnd, IDC_EDIT6, cadenaNacimiento);
				SetDlgItemInt(hwnd, IDC_EDIT7, formatoEdad(miUsuario->dato->nacimiento), false);
			}

			if (miUsuario->dato->foto != nullptr)
			{
				strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
			}

			break;
		}
		case WM_COMMAND:
		{
			long opcion = LOWORD(wParam);
			cMenu(hwnd, opcion);

			switch (LOWORD(wParam))
			{
				case IDC_BUTTON1: // Guardar
				{
					//Se guarda el usuario y contraseña en un auxiliar
					NodoUsuario* auxNodo = new NodoUsuario;
					auxNodo->dato = new DatoUsuario;
					strcpy_s(auxNodo->dato->nick, sizeof(auxNodo->dato->nick), miUsuario->dato->nick);
					strcpy_s(auxNodo->dato->password, sizeof(auxNodo->dato->password), miUsuario->dato->password);
					
					GetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nick, sizeof(miUsuario->dato->nick));
					GetDlgItemText(hwnd, IDC_EDIT2, miUsuario->dato->nombre, sizeof(miUsuario->dato->nombre));
					GetDlgItemText(hwnd, IDC_EDIT3, miUsuario->dato->apellidoP, sizeof(miUsuario->dato->apellidoP));
					GetDlgItemText(hwnd, IDC_EDIT4, miUsuario->dato->apellidoM, sizeof(miUsuario->dato->apellidoM));
					GetDlgItemText(hwnd, IDC_EDIT8, miUsuario->dato->email, sizeof(miUsuario->dato->email));
					GetDlgItemText(hwnd, IDC_EDIT9, miUsuario->dato->password, sizeof(miUsuario->dato->password));

					//Si el nick anterior era el del admin, se actualiza el archivo
					if (adminComprobation(auxNodo))
					{
						ofstream archivo("UsuarioAdmin.txt");
						archivo << miUsuario->dato->nick << "," << miUsuario->dato->password;
						archivo.close();
					}

					// Concatenación
					strcpy_s(miUsuario->dato->nombreComp, miUsuario->dato->nombre);
					strcat_s(miUsuario->dato->nombreComp, " ");
					strcat_s(miUsuario->dato->nombreComp, miUsuario->dato->apellidoP);
					strcat_s(miUsuario->dato->nombreComp, " ");
					strcat_s(miUsuario->dato->nombreComp, miUsuario->dato->apellidoM);

					//Genero
					if ((IsDlgButtonChecked(hwnd, IDC_RADIO1) == BST_CHECKED))
					{
						miUsuario->dato->genero = 1;
					}
					else
					{
						miUsuario->dato->genero = 0;
					}

					//Se obtiene la fecha de nacimiento
					HWND hDia = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
					SYSTEMTIME diaCumple = { 0 }; double dia;
					DateTime_GetSystemtime(hDia, &diaCumple);
					SystemTimeToVariantTime(&diaCumple, &dia);
					miUsuario->dato->nacimiento = dia;

					strcpy_s(miUsuario->dato->foto, zFile);
					
					MessageBox(NULL, "Cambios guardados.", "AVISO", MB_OK | MB_ICONINFORMATION);

					//Recarga la pestaña
					EndDialog(hwnd, 0);

					HWND hDialog3 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG3), 0, cDialog3);

					ShowWindow(hDialog3, SW_SHOW);
					UpdateWindow(hDialog3);

					break;
				}
				case IDC_BUTTON2: // Cargar
				{
					OPENFILENAME ofn;

					ZeroMemory(&ofn, sizeof(ofn));

					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = hwnd; //Puntero de la ventana padre
					ofn.lpstrFilter = "ALL\0 * .*\0Bitmaps\0 * .bmp\0";
					ofn.lpstrFile = zFile;
					ofn.lpstrFile[0] = '\0';
					ofn.nMaxFile = sizeof(zFile);
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
					ofn.nFilterIndex = 2;

					if (GetOpenFileName(&ofn) == TRUE)
					{
						HBITMAP bmp; //1
						bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE); //2
						SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 
					}
					break;
				}
				default:
				{
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}
	return false;  // Un callback siempre retorna falso
}

// Lista Usuarios
BOOL CALLBACK cDialog4(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		if (miUsuario != nullptr)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
		}
		if (miUsuario->dato->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		// Recorrer el árbol en preorden y agregar los nombres de usuario al ListBox
		preOrderList(iniUsuario, hwnd);

		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char nombre[30] = { 0 };
				int indice = 0;
				indice = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, indice, (LPARAM)nombre);

				// Buscar el usuario en el árbol
				DatoUsuario data;
				strcpy_s(data.nick, nombre);
				auxUsuario2 = searchTree(iniUsuario, &data);

				SetDlgItemText(hwnd, IDC_EDIT2, auxUsuario2->dato->nick);
				SetDlgItemText(hwnd, IDC_EDIT4, auxUsuario2->dato->nombreComp);

				break;
			}

			default:
			{
				break;
			}

			}

			break;
		}
			case IDC_BUTTON1: // Eliminar
			{
				if (auxUsuario2 == nullptr)
				{
					MessageBox(NULL, "No se ha seleccionado un usuario, seleccione uno de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
				}
				else
				{
					int opc = MessageBox(hwnd, "¿Seguro que desea eliminar este usuario?", "AVISO", MB_YESNO | MB_ICONQUESTION);

					switch (opc)
					{
					case IDYES:
					{
						char NickUsuario[30] = { 0 };
						int indice = 0;
						indice = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
						SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, indice, (LPARAM)NickUsuario);

						if (strcmp(miUsuario->dato->nick, NickUsuario) == 0)
						{
							MessageBox(NULL, "El usuario que inicio sesion será eliminado, se cerrará la sesion.", "AVISO", MB_OK | MB_ICONINFORMATION);

							iniUsuario = deleteTreeNodeByNick(iniUsuario, NickUsuario);
							
							DestroyWindow(hwnd);
							PostQuitMessage(0);
						}
						else
						{
							iniUsuario = deleteTreeNodeByNick(iniUsuario, NickUsuario);

							SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_DELETESTRING, indice, 0);
							SetDlgItemText(hwnd, IDC_EDIT2, "");
							SetDlgItemText(hwnd, IDC_EDIT4, "");

							auxUsuario2 = nullptr;
						}

						break;
					}

					case IDNO:
					{
						SetDlgItemText(hwnd, IDC_EDIT2, "");
						SetDlgItemText(hwnd, IDC_EDIT4, "");

						auxUsuario2 = nullptr;

						break;
					}

					default:
					{
						break;
					}

					}
				}

				break;
			}
			default:
			{
				break;
			}

			}

			break;
		}
		default:
		{
			break;
		}
	}
	return false;  // Un callback siempre retorna falso
}

// Registro Vuelos
BOOL CALLBACK cDialog5(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		if (redirection)
		{
			SetDlgItemInt(hwnd, IDC_EDIT2, auxVuelo2->dato->num, false);
			SetDlgItemText(hwnd, IDC_EDIT3, auxVuelo2->dato->origen);
			SetDlgItemText(hwnd, IDC_EDIT4, auxVuelo2->dato->destino);
			SetDlgItemText(hwnd, IDC_EDIT17, auxVuelo2->dato->modelo);

			char cadenaFecha[100];
			SYSTEMTIME fecha = { 0 };
			VariantTimeToSystemTime(auxVuelo2->dato->fecha, &fecha);

			DateTime_SetSystemtime(GetDlgItem(hwnd, IDC_DATETIMEPICKER1), GDT_VALID, &fecha);

			//Asientos
			/*aux2 = ini2;
			while (aux2->sig != nullptr && strcmp(aux2->Modelo, auxVuelo2->dato->modelo) != 0)
			{
				aux2 = aux2->sig;
			}*/

			SetDlgItemInt(hwnd, IDC_EDIT6, auxVuelo2->dato->asientosT, false);
			SetDlgItemInt(hwnd, IDC_EDIT7, auxVuelo2->dato->asientosCT, false);
			SetDlgItemInt(hwnd, IDC_EDIT8, auxVuelo2->dato->asientosE, false);
			SetDlgItemInt(hwnd, IDC_EDIT9, auxVuelo2->dato->asientosCE, false);

			SetDlgItemInt(hwnd, IDC_EDIT10, auxVuelo2->dato->asientosN, false);
			SetDlgItemInt(hwnd, IDC_EDIT11, auxVuelo2->dato->asientosA, false);
			SetDlgItemInt(hwnd, IDC_EDIT19, auxVuelo2->dato->asientosM, false);

			SetDlgItemInt(hwnd, IDC_EDIT20, auxVuelo2->dato->asientos, false);

			/*redirection = false;*/
		}

		//PANTALLA
		if (miUsuario != nullptr)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
		}
		if (miUsuario->dato->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		aux2 = ini2; // Modelos
		while (aux2->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST6, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux2->Modelo);
			aux2 = aux2->sig;
		}
		if (aux2->sig == nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST6, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux2->Modelo);
			aux2 = aux2->sig;
		}

		aux3 = ini3; // Lugares
		while (aux3->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST2, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux3->Lugar);
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux3->Lugar);
			aux3 = aux3->sig;
		}
		if (aux3->sig == nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST2, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux3->Lugar);
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux3->Lugar);
			aux3 = aux3->sig;
		}

		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_LIST2: // Origen
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char origen[30];
				int indice = 0;

				indice = SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETTEXT, indice, (LPARAM)origen);

				aux3 = ini3;
				while (aux3->sig != nullptr && strcmp(aux3->Lugar, origen) != 0)
				{
					aux3 = aux3->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT3, aux3->Lugar);

				break;
			}

			default:
			{
				break;
			}
			}

			break;
		}
		case IDC_LIST3: // Destino
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char destino[30];
				int indice2 = 0;

				indice2 = SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETTEXT, indice2, (LPARAM)destino);

				aux3 = ini3;
				while (aux3->sig != nullptr && strcmp(aux3->Lugar, destino) != 0)
				{
					aux3 = aux3->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT4, aux3->Lugar);

				break;
			}

			default:
			{
				break;
			}
			}

			break;
		}
		case IDC_LIST6: // Modelo
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char modelo[30];
				int indice3 = 0;

				indice3 = SendDlgItemMessage(hwnd, IDC_LIST6, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST6, LB_GETTEXT, indice3, (LPARAM)modelo);

				aux2 = ini2;
				while (aux2->sig != nullptr && strcmp(aux2->Modelo, modelo) != 0)
				{
					aux2 = aux2->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT17, aux2->Modelo);

				SetDlgItemInt(hwnd, IDC_EDIT6, aux2->asientosT, false);
				SetDlgItemInt(hwnd, IDC_EDIT7, aux2->asientosCT, false);
				SetDlgItemInt(hwnd, IDC_EDIT8, aux2->asientosE, false);
				SetDlgItemInt(hwnd, IDC_EDIT9, aux2->asientosCE, false);

				SetDlgItemInt(hwnd, IDC_EDIT10, aux2->asientosN, false);
				SetDlgItemInt(hwnd, IDC_EDIT11, aux2->asientosA, false);
				SetDlgItemInt(hwnd, IDC_EDIT19, aux2->asientosM, false);

				SetDlgItemInt(hwnd, IDC_EDIT20, aux2->asientos, false);

				break;
			}
			default:
			{
				break;
			}
			}

			break;
		}
		case IDC_BUTTON1: // Número
		{
			if (iniVuelo == nullptr)
			{
				SetDlgItemInt(hwnd, IDC_EDIT2, 1, false);
			}
			else
			{
				NodoVuelo* tempNum = new NodoVuelo;
				DatoVuelo* tempDat = new DatoVuelo;
				tempNum->dato = tempDat;

				auxVuelo3 = iniVuelo;

				while (auxVuelo3->sig != nullptr)
				{
					auxVuelo3 = auxVuelo3->sig;
				}

				SetDlgItemInt(hwnd, IDC_EDIT2, auxVuelo3->dato->num + 1, false);

				auxVuelo3 = iniVuelo;
			}

			break;

		}
		case IDC_BUTTON2: // Guardar
		{
			if (redirection == false)
			{
				//Condicional para asegurar ningun control esté vacío
				char numAsignadoC[10];
				GetDlgItemText(hwnd, IDC_EDIT2, numAsignadoC, sizeof(numAsignadoC));
				char origen[30];
				GetDlgItemText(hwnd, IDC_EDIT3, origen, sizeof(origen));
				char destino[30];
				GetDlgItemText(hwnd, IDC_EDIT4, destino, sizeof(destino));
				char modelo[30];
				GetDlgItemText(hwnd, IDC_EDIT17, modelo, sizeof(modelo));

				// Verificar si los controles están vacíos
				if (strlen(numAsignadoC) == 0 || strlen(origen) == 0 || strlen(destino) == 0 || strlen(modelo) == 0)
				{
					MessageBox(NULL, "Por favor, rellene todos los campos.", "AVISO", MB_OK | MB_ICONINFORMATION);
					break;
				}
				//Condicional para que el vuelo no se haga el mismo día que se creó
				SYSTEMTIME fechaSeleccionada;
				DateTime_GetSystemtime(GetDlgItem(hwnd, IDC_DATETIMEPICKER1), &fechaSeleccionada);
				SYSTEMTIME fechaActual;
				GetSystemTime(&fechaActual);
				DATE dateSeleccionada, dateActual;
				SystemTimeToVariantTime(&fechaSeleccionada, &dateSeleccionada);
				SystemTimeToVariantTime(&fechaActual, &dateActual);

				// Verificar si la fecha seleccionada es la misma que la fecha actual
				if (dateSeleccionada <= dateActual)
				{
					MessageBox(NULL, "La fecha del vuelo no puede ser el día de hoy o anterior.", "AVISO", MB_OK | MB_ICONINFORMATION);
					break;
				}

				int numBuscar;
				char numBuscarC[10];

				GetDlgItemText(hwnd, IDC_EDIT2, numBuscarC, sizeof(numBuscarC));

				numBuscar = atoi(numBuscarC);

				auxVuelo2 = iniVuelo;

				while (auxVuelo2/*->sig*/ != nullptr && strcmp(numBuscarC, auxVuelo2->dato->origen) != 0)
				{
					auxVuelo2 = auxVuelo2->sig;
				}

				if (auxVuelo2/*->sig*/ == nullptr || strcmp(numBuscarC, auxVuelo2->dato->origen) != 0)
				{
					NodoVuelo* temp = new NodoVuelo;
					temp->dato = new DatoVuelo;

					char numAsignadoC[10];
					GetDlgItemText(hwnd, IDC_EDIT2, numAsignadoC, sizeof(numAsignadoC));

					temp->dato->num = atoi(numAsignadoC);

					GetDlgItemText(hwnd, IDC_EDIT3, temp->dato->origen, sizeof(temp->dato->origen));
					GetDlgItemText(hwnd, IDC_EDIT4, temp->dato->destino, sizeof(temp->dato->destino));
					GetDlgItemText(hwnd, IDC_EDIT17, temp->dato->modelo, sizeof(temp->dato->modelo));

					temp->dato->asientosT = aux2->asientosT;
					temp->dato->asientosCT = aux2->asientosCT;
					temp->dato->asientosE = aux2->asientosE;
					temp->dato->asientosCE = aux2->asientosCE;

					temp->dato->asientosN = aux2->asientosN;
					temp->dato->asientosA = aux2->asientosA;
					temp->dato->asientosM = aux2->asientosM;

					temp->dato->asientos = aux2->asientos;

					//Se obtiene la fecha
					HWND hDia = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
					SYSTEMTIME diaCumple = { 0 }; double dia;
					DateTime_GetSystemtime(hDia, &diaCumple);
					SystemTimeToVariantTime(&diaCumple, &dia);

					temp->dato->status = 0;
					temp->dato->fecha = dia;

					SYSTEMTIME fecha = { 0 };
					GetLocalTime(&fecha);
					SystemTimeToVariantTime(&fecha, &temp->dato->registro);

					strcpy_s(temp->dato->usuarioRegistro, miUsuario->dato->nick);

					temp->sig = nullptr;
					temp->ant = nullptr;

					nuevoVuelo(temp);

					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");
					SetDlgItemText(hwnd, IDC_EDIT17, "");
					SetDlgItemText(hwnd, IDC_EDIT6, "");
					SetDlgItemText(hwnd, IDC_EDIT7, "");
					SetDlgItemText(hwnd, IDC_EDIT8, "");
					SetDlgItemText(hwnd, IDC_EDIT9, "");
					SetDlgItemText(hwnd, IDC_EDIT10, "");
					SetDlgItemText(hwnd, IDC_EDIT11, "");
					SetDlgItemText(hwnd, IDC_EDIT19, "");
					SetDlgItemText(hwnd, IDC_EDIT20, "");
					/*SetDlgItemText(hwnd, IDC_EDIT23, "");*/

					EndDialog(hwnd, 0);

					HWND hDialog10 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG10), 0, cDialog10);

					ShowWindow(hDialog10, SW_SHOW);
					UpdateWindow(hDialog10);
				}
				else
				{
					MessageBox(NULL, "El vuelo ya esta registrado.", "AVISO", MB_OK | MB_ICONINFORMATION);
				}
			}
			else
			{
				MessageBox(NULL, "No se puede guardar un vuelo mientras esta editando otro vuelo, para salir del modo edición vuelva a cargar la pestaña.", "AVISO", MB_OK | MB_ICONINFORMATION);
			}

			break;
		}
		case IDC_BUTTON3: // Editar
		{
			if (redirection)
			{
				if (auxVuelo2 == nullptr)
				{
					MessageBox(NULL, "No se ha seleccionado un vuelo, seleccione uno de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
				}
				else
				{
					//Condicional para asegurar ningun control esté vacío
					char origen[30];
					GetDlgItemText(hwnd, IDC_EDIT3, origen, sizeof(origen));
					char destino[30];
					GetDlgItemText(hwnd, IDC_EDIT4, destino, sizeof(destino));

					if (strlen(origen) == 0 || strlen(destino) == 0)
					{
						MessageBox(NULL, "Por favor, rellene todos los campos.", "AVISO", MB_OK | MB_ICONINFORMATION);
						break;
					}

					//Condicional para que el vuelo no se haga el mismo día que se creó
					SYSTEMTIME fechaSeleccionada;
					DateTime_GetSystemtime(GetDlgItem(hwnd, IDC_DATETIMEPICKER1), &fechaSeleccionada);
					SYSTEMTIME fechaActual;
					GetSystemTime(&fechaActual);
					DATE dateSeleccionada, dateActual;
					SystemTimeToVariantTime(&fechaSeleccionada, &dateSeleccionada);
					SystemTimeToVariantTime(&fechaActual, &dateActual);

					// Verificar si la fecha seleccionada es la misma que la fecha actual
					if (dateSeleccionada <= dateActual)
					{
						MessageBox(NULL, "La fecha del vuelo no puede ser el día de hoy o anterior.", "AVISO", MB_OK | MB_ICONINFORMATION);
						break;
					}

					GetDlgItemText(hwnd, IDC_EDIT3, auxVuelo2->dato->origen, sizeof(auxVuelo2->dato->origen));
					GetDlgItemText(hwnd, IDC_EDIT4, auxVuelo2->dato->destino, sizeof(auxVuelo2->dato->destino));

					//Se obtiene la fecha
					HWND hDia = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
					SYSTEMTIME diaCumple = { 0 }; double dia;
					DateTime_GetSystemtime(hDia, &diaCumple);
					SystemTimeToVariantTime(&diaCumple, &dia);
					int edad = formatoEdad(dia);

					auxVuelo2->dato->fecha = dia;

					SYSTEMTIME fecha = { 0 };
					GetLocalTime(&fecha);
					SystemTimeToVariantTime(&fecha, &auxVuelo2->dato->registro);
					MessageBox(NULL, "Cambios guardados.", "AVISO", MB_OK | MB_ICONINFORMATION);

					strcpy_s(auxVuelo2->dato->usuarioRegistro, miUsuario->dato->nick);

					auxVuelo2 = iniVuelo;

					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");
					SetDlgItemText(hwnd, IDC_EDIT17, "");
					SetDlgItemText(hwnd, IDC_EDIT6, "");
					SetDlgItemText(hwnd, IDC_EDIT7, "");
					SetDlgItemText(hwnd, IDC_EDIT8, "");
					SetDlgItemText(hwnd, IDC_EDIT9, "");
					SetDlgItemText(hwnd, IDC_EDIT10, "");
					SetDlgItemText(hwnd, IDC_EDIT11, "");
					SetDlgItemText(hwnd, IDC_EDIT19, "");
					SetDlgItemText(hwnd, IDC_EDIT20, "");

					//Recarga la pestaña
					EndDialog(hwnd, 0);
					HWND hDialog6 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG6), 0, cDialog6);

					ShowWindow(hDialog6, SW_SHOW);
					UpdateWindow(hDialog6); //Opcional
				}

				redirection = false;
			}
			else
			{
				MessageBox(NULL, "No se puede editar un vuelo si no ha seleccionado una de la pestaña ---Lista de Vuelos---.", "AVISO", MB_OK | MB_ICONINFORMATION);
			}

			break;
		}
		default:
			{
				break;
			}
		}

		break;
	}
	default:
		{
			break;
		}
	}

	return false;  // Un callback siempre retorna falso
}

// Lista Vuelos
BOOL CALLBACK cDialog6(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		if (miUsuario != nullptr)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
		}
		if (miUsuario->dato->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		if (auxVuelo2 != nullptr)
		{
			SetDlgItemInt(hwnd, IDC_EDIT2, auxVuelo2->dato->num, NULL);
			SetDlgItemText(hwnd, IDC_EDIT3, auxVuelo2->dato->origen);
			SetDlgItemText(hwnd, IDC_EDIT4, auxVuelo2->dato->destino);

			char cadenaFecha[100];
			SYSTEMTIME fecha = { 0 };
			VariantTimeToSystemTime(auxVuelo2->dato->fecha, &fecha);
			formatoFecha(&fecha, cadenaFecha);
			//sprintf_s(cadenaNacimiento, "%f", miUsuario->dato->nacimiento);
			SetDlgItemText(hwnd, IDC_EDIT6, cadenaFecha);

			switch (auxVuelo2->dato->status)
			{
			case 0:
			{
				SetDlgItemText(hwnd, IDC_EDIT7, "En espera");
				break;
			}
			case 1:
			{
				SetDlgItemText(hwnd, IDC_EDIT7, "Efectuado");
				break;
			}
			case 2:
			{
				SetDlgItemText(hwnd, IDC_EDIT7, "Cancelado");
				break;
			}
			}
		}

		auxVuelo2 = iniVuelo;
		if (iniVuelo != nullptr)
		{
			// Ordenamiento QueckSort Vuelos
			quickSortNum(iniVuelo);

			while (auxVuelo2->sig != nullptr)
			{
				char numStr[200];
				sprintf_s(numStr, sizeof(numStr), "%d", auxVuelo2->dato->num);
				SendDlgItemMessageA(hwnd, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)numStr);
				auxVuelo2 = auxVuelo2->sig;
			}

			if (auxVuelo2->sig == nullptr/* || auxEsp2->ant == nullptr*/)
			{
				char numStr[200];
				sprintf_s(numStr, sizeof(numStr), "%d", auxVuelo2->dato->num);
				SendDlgItemMessageA(hwnd, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)numStr);
				auxVuelo2 = auxVuelo2->sig;
			}
		}
		else
		{
			MessageBox(NULL, "No hay vuelos registrados.", "AVISO", MB_OK | MB_ICONINFORMATION);
		}

		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_LIST2: //Vuelos
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char vueloO[30] = { 0 };
				int indice2 = 0;
				indice2 = SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETTEXT, indice2, (LPARAM)vueloO);
				
				int numVuelo;
				numVuelo = atoi(vueloO);
				auxVuelo2 = iniVuelo;

				while (auxVuelo2->sig != nullptr && auxVuelo2->dato->num != numVuelo)
				{
					auxVuelo2 = auxVuelo2->sig;
				}

				SetDlgItemInt(hwnd, IDC_EDIT2, auxVuelo2->dato->num, NULL);
				SetDlgItemText(hwnd, IDC_EDIT3, auxVuelo2->dato->origen);
				SetDlgItemText(hwnd, IDC_EDIT4, auxVuelo2->dato->destino);

				char cadenaFecha[100];
				SYSTEMTIME fecha = { 0 };
				VariantTimeToSystemTime(auxVuelo2->dato->fecha, &fecha);
				formatoFecha(&fecha, cadenaFecha);
				//sprintf_s(cadenaNacimiento, "%f", miUsuario->dato->nacimiento);
				SetDlgItemText(hwnd, IDC_EDIT6, cadenaFecha);

				switch (auxVuelo2->dato->status)
				{
					case 0:
					{
						SetDlgItemText(hwnd, IDC_EDIT7, "En espera");
						break;
					}
					case 1:
					{
						SetDlgItemText(hwnd, IDC_EDIT7, "Efectuado");
						break;
					}
					case 2:
					{
						SetDlgItemText(hwnd, IDC_EDIT7, "Cancelado");
						break;
					}
				}

				break;
			}

			default:
			{
				break;
			}
			}

			break;
		}
		case IDC_BUTTON1: // Editar
		{
			if (auxVuelo2 == nullptr)
			{
				MessageBox(NULL, "No se ha seleccionado un vuelo, seleccione una de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
				redirection = true;
				EndDialog(hwnd, 0);
				HWND hDialog5 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG5), 0, cDialog5);

				ShowWindow(hDialog5, SW_SHOW);
				UpdateWindow(hDialog5); //Opcional
			}

			break;
		}
		case IDC_BUTTON2: // Cancelar
		{
			if (auxVuelo2 == nullptr)
			{
				MessageBox(NULL, "No se ha seleccionado un vuelo, seleccione uno de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
				int opc = MessageBox(hwnd, "¿Seguro que desea cancelar este vuelo?", "AVISO", MB_YESNO | MB_ICONQUESTION);

				switch (opc)
				{
				case IDYES:
				{
					auxVuelo2->dato->status = 2;
					MessageBox(NULL, "Vuelo cancelado.", "AVISO", MB_OK | MB_ICONINFORMATION);
					auxVuelo2 = nullptr;

					EndDialog(hwnd, 0);
					HWND hDialog6 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG6), 0, cDialog6);
					ShowWindow(hDialog6, SW_SHOW);
					UpdateWindow(hDialog6); //Opcional
					break;
				}

				case IDNO:
				{
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");
					SetDlgItemText(hwnd, IDC_EDIT6, "");
					SetDlgItemText(hwnd, IDC_EDIT7, "");

					auxVuelo2 = nullptr;
					break;
				}

				default:
				{
					break;
				}

				}
			}
			break;
		}
		default:
		{
			break;
		}
		}

		break;
	}
	default:
	{
		break;
	}
	}

	return false;  // Un callback siempre retorna falso
}

// Manifiesto
BOOL CALLBACK cDialog7(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		if (miUsuario != nullptr)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
		}
		if (miUsuario->dato->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		auxVuelo2 = iniVuelo;
		if (iniVuelo != nullptr)
		{
			// Ordenamiento QueckSort Vuelos
			quickSortNum(iniVuelo);

			while (auxVuelo2->sig != nullptr)
			{
				if (auxVuelo2->dato->status = 1)
				{
					SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxVuelo2->dato->origen);
				}
				auxVuelo2 = auxVuelo2->sig;
			}

			if (auxVuelo2->sig == nullptr/* || auxEsp2->ant == nullptr*/)
			{
				if (auxVuelo2->dato->status = 1)
				{
					SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxVuelo2->dato->origen);
				}
				auxVuelo2 = auxVuelo2->sig;
			}
		}
		else
		{
			MessageBox(NULL, "No hay vuelos registrados.", "AVISO", MB_OK | MB_ICONINFORMATION);
		}

		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_LIST3: //Vuelos
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char vueloO[30];
				int indice2 = 0;
				indice2 = SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETTEXT, indice2, (LPARAM)vueloO);

				auxVuelo2 = iniVuelo;

				while (auxVuelo2->sig != nullptr && strcmp(auxVuelo2->dato->origen, vueloO) != 0)
				{
					auxVuelo2 = auxVuelo2->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT2, auxVuelo2->dato->origen);

				break;
			}

			default:
			{
				break;
			}
			}

			break;
		}
		case IDC_BUTTON3: // Seleccionar
		{
			if (auxVuelo2 == nullptr)
			{
				MessageBox(NULL, "No se ha seleccionado un vuelo, seleccione uno de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
				EndDialog(hwnd, 0);

				HWND hDialog8 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG8), 0, cDialog8);

				ShowWindow(hDialog8, SW_SHOW);
				UpdateWindow(hDialog8); //Opcional
			}

			break;
		}

		default:
		{
			break;
		}
		}

		break;
	}

	default:
	{
		break;
	}
	}

	return false;  // Un callback siempre retorna falso
}

// Manifiesto2
BOOL CALLBACK cDialog8(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			if (miUsuario != nullptr)
			{
				SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
			}
			if (miUsuario->dato->foto != nullptr)
			{
				strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
			}
			auxBoleto2 = iniBoleto;
			if (iniBoleto != nullptr)
			{
				// Ordenamiento QueckSort Boleto
				//quickSortNum(iniBoleto);

				//Lista de Boletos
				while (auxBoleto2->sig != nullptr)
				{
					if (auxBoleto2->dato->numVuelo == auxVuelo2->dato->num)
					{
						SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto2->dato->nombreCompPasajero);
					}
					auxBoleto2 = auxBoleto2->sig;
				}

				if (auxBoleto2->sig == nullptr/* || auxEsp2->ant == nullptr*/)
				{
					if (auxBoleto2->dato->numVuelo == auxVuelo2->dato->num)
					{
						SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto2->dato->nombreCompPasajero);
					}
					auxBoleto2 = auxBoleto2->sig;
				}
			}
			else
			{
				MessageBox(NULL, "No hay boletos registrados.", "AVISO", MB_OK | MB_ICONINFORMATION);
			}
			if (auxVuelo2 != nullptr)
			{
				SetDlgItemInt(hwnd, IDC_EDIT2, auxVuelo2->dato->num, false);
				SetDlgItemText(hwnd, IDC_EDIT3, auxVuelo2->dato->origen);
				SetDlgItemText(hwnd, IDC_EDIT4, auxVuelo2->dato->destino);
				SetDlgItemText(hwnd, IDC_EDIT21, auxVuelo2->dato->modelo);

				char cadenaFecha[100];
				SYSTEMTIME fecha = { 0 };
				VariantTimeToSystemTime(auxVuelo2->dato->fecha, &fecha);

				DateTime_SetSystemtime(GetDlgItem(hwnd, IDC_DATETIMEPICKER1), GDT_VALID, &fecha);

				aux2 = ini2;
				while (aux2->sig != nullptr && strcmp(aux2->Modelo, auxVuelo2->dato->modelo) != 0)
				{
					aux2 = aux2->sig;
				}

				char texto[10];
				_itoa_s(aux2->asientosT, texto, 10);
				SetDlgItemText(hwnd, IDC_EDIT6, texto);
				_itoa_s(aux2->asientosCT, texto, 10);
				SetDlgItemText(hwnd, IDC_EDIT7, texto);
				_itoa_s(aux2->asientosE, texto, 10);
				SetDlgItemText(hwnd, IDC_EDIT8, texto);
				_itoa_s(aux2->asientosCE, texto, 10);
				SetDlgItemText(hwnd, IDC_EDIT9, texto);

				_itoa_s(aux2->asientosN, texto, 10);
				SetDlgItemText(hwnd, IDC_EDIT10, texto);
				_itoa_s(aux2->asientosA, texto, 10);
				SetDlgItemText(hwnd, IDC_EDIT11, texto);
				_itoa_s(aux2->asientosM, texto, 10);
				SetDlgItemText(hwnd, IDC_EDIT19, texto);
				_itoa_s(aux2->asientos, texto, 10);
				SetDlgItemText(hwnd, IDC_EDIT20, texto);
				_itoa_s(auxVuelo2->dato->status, texto, 10);
				SetDlgItemText(hwnd, IDC_EDIT27, texto);
			}

			break;
		}
		case WM_COMMAND:
		{
			long opcion = LOWORD(wParam);
			cMenu(hwnd, opcion);

			switch (LOWORD(wParam))
			{
			
			case IDC_BUTTON1: // Reporte
			{
				

				break;
			}
			case IDC_BUTTON2: // Asientos
			{
				int numV = GetDlgItemInt(hwnd, IDC_EDIT2, NULL, NULL);
				quickSortNumAsiento(iniBoleto);
				SendMessage(GetDlgItem(hwnd, IDC_LIST9), LB_RESETCONTENT, 0, 0);

				NodoBoleto* temp = new NodoBoleto;
				temp->dato = new DatoBoleto;
				temp = iniBoleto;

				while (temp->sig != nullptr && temp->dato->numVuelo == numV)
				{
					SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)temp->dato->nombreCompPasajero);
					temp = temp->sig;
				}
				if (temp->sig == nullptr && temp->dato->numVuelo == numV)
				{
					SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)temp->dato->nombreCompPasajero);
				}
				break;
			}
			case IDC_BUTTON3: // Nombres
			{
				int numV = GetDlgItemInt(hwnd, IDC_EDIT2, NULL, NULL);
				quickSortNomPasajero(iniBoleto);
				SendMessage(GetDlgItem(hwnd, IDC_LIST9), LB_RESETCONTENT, 0, 0);

				NodoBoleto* temp = new NodoBoleto;
				temp->dato = new DatoBoleto;
				temp = iniBoleto;

				while (temp->sig != nullptr && temp->dato->numVuelo == numV)
				{
					SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)temp->dato->nombreCompPasajero);
					temp = temp->sig;
				}
				if (temp->sig == nullptr && temp->dato->numVuelo == numV)
				{
					SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)temp->dato->nombreCompPasajero);
				}
				break;
			}
			
			default:
			{
				break;
			}
			}

			break;
		}

		default:
		{
			break;
		}
	}

	return false;  // Un callback siempre retorna falso
}

//Reporte de vuelos
BOOL CALLBACK cDialog9(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		if (miUsuario != nullptr)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
		}
		if (miUsuario->dato->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}
		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		//case IDC_LIST1: // Vuelos
		//{
		//	switch (HIWORD(wParam))
		//	{
		//	case LBN_DBLCLK: //Al dar doble clic en el ListBox 
		//	{
		//		int num;
		//		int indice = 0;
		//		indice = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
		//		SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, indice, (LPARAM)num);
		//		auxVuelo3 = iniVuelo;
		//		while (auxVuelo3->sig != nullptr && auxVuelo3->dato->num == num)
		//		{
		//			auxVuelo3 = auxVuelo3->sig;
		//		}
		//		break;
		//	}
		//	default:
		//	{
		//		break;
		//	}
		//	}
		//	break;
		//}
		case IDC_BUTTON1: // Más recientes
		{
			quickSortFechaNewToOld(iniVuelo);

			SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
			SetRegistroVuelos(hwnd, IDC_LIST1, IDC_DATETIMEPICKER1, IDC_DATETIMEPICKER2);
			break;
		}
		case IDC_BUTTON2: // Más antiguos
		{
			quickSortFechaOldToNew(iniVuelo);

			SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
			SetRegistroVuelos(hwnd, IDC_LIST1, IDC_DATETIMEPICKER1, IDC_DATETIMEPICKER2);
			break;
		}
		case IDC_BUTTON3: // Fechas
		{
			SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
			SetRegistroVuelos(hwnd, IDC_LIST1, IDC_DATETIMEPICKER1, IDC_DATETIMEPICKER2);
			break;
		}
		case IDC_BUTTON4: // Reporte
		{
			if (iniVuelo == nullptr)
			{
				MessageBox(NULL, "No hay vuelos registrados.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
				reporteVuelos(hwnd, IDC_LIST1);
				MessageBox(NULL, "Reporte fue guardado.", "AVISO", MB_OK | MB_ICONEXCLAMATION);
			}

			break;
		}

		default:
		{
			break;
		}
		}

		break;
	}

	default:
	{
		break;
	}
	}

	return false;  // Un callback siempre retorna falso
}

// Registro Pasajeros
BOOL CALLBACK cDialog10(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		if (miUsuario != nullptr)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
		}
		if (miUsuario->dato->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		aux = ini; // Nacionalidades
		while (aux->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux->Nacionalidad);
			aux = aux->sig;
		}
		if (aux->sig == nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux->Nacionalidad);
			aux = aux->sig;
		}

		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_LIST3: // Nacionalidad
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char nacionalidadL[30] = { 0 };
				int indice = 0;

				indice = SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETTEXT, indice, (LPARAM)nacionalidadL);

				aux = ini;
				while (aux->sig != nullptr && strcmp(aux->Nacionalidad, nacionalidadL) != 0)
				{
					aux = aux->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT6, aux->Nacionalidad);

				break;
			}

			default:
			{
				break;
			}
			}

			break;
		}
		case IDC_BUTTON1: // Guardar
		{
			char nombreBuscar[30];
			char apellidoPaternoBuscar[30];
			char apellidoMaternoBuscar[30];
			char pasajeroBuscar[30];

			GetDlgItemText(hwnd, IDC_EDIT2, nombreBuscar, sizeof(nombreBuscar));
			GetDlgItemText(hwnd, IDC_EDIT3, apellidoPaternoBuscar, sizeof(apellidoPaternoBuscar));
			GetDlgItemText(hwnd, IDC_EDIT4, apellidoMaternoBuscar, sizeof(apellidoMaternoBuscar));

			// Concatenación
			strcpy_s(pasajeroBuscar, nombreBuscar);
			strcat_s(pasajeroBuscar, " ");
			strcat_s(pasajeroBuscar, apellidoPaternoBuscar);
			strcat_s(pasajeroBuscar, " ");
			strcat_s(pasajeroBuscar, apellidoMaternoBuscar);

			auxPasajero2 = iniPasajero;

			while (auxPasajero2/*->sig*/ != nullptr && strcmp(pasajeroBuscar, auxPasajero2->dato->nombreComp) != 0)
			{
				auxPasajero2 = auxPasajero2->sig;
			}

			if (auxPasajero2/*->sig*/ == nullptr || strcmp(pasajeroBuscar, auxPasajero2->dato->nombreComp) != 0)
			{
				NodoPasajero* temp = new NodoPasajero;
				temp->dato = new DatoPasajero;

				GetDlgItemText(hwnd, IDC_EDIT2, temp->dato->nombre, sizeof(temp->dato->nombre));
				GetDlgItemText(hwnd, IDC_EDIT3, temp->dato->apellidoP, sizeof(temp->dato->apellidoP));
				GetDlgItemText(hwnd, IDC_EDIT4, temp->dato->apellidoM, sizeof(temp->dato->apellidoM));
				GetDlgItemText(hwnd, IDC_EDIT6, temp->dato->nacionalidad, sizeof(temp->dato->nacionalidad));

				//Genero
				if ((IsDlgButtonChecked(hwnd, IDC_RADIO1) == BST_CHECKED))
				{
					temp->dato->genero = 1;
				}
				else
				{
					temp->dato->genero = 0;
				}

				//Se obtiene la fecha de nacimiento
				HWND hDia = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
				SYSTEMTIME diaCumple = { 0 }; double dia;
				DateTime_GetSystemtime(hDia, &diaCumple);
				SystemTimeToVariantTime(&diaCumple, &dia); 

				temp->dato->nacimiento = dia;

				strcpy_s(temp->dato->usuarioRegistro, miUsuario->dato->nick);

				SYSTEMTIME fecha = { 0 };
				GetLocalTime(&fecha);
				SystemTimeToVariantTime(&fecha, &temp->dato->registro);

				temp->sig = nullptr;
				temp->ant = nullptr;
				nuevoPasajero(temp);

				SetDlgItemText(hwnd, IDC_EDIT2, "");
				SetDlgItemText(hwnd, IDC_EDIT3, "");
				SetDlgItemText(hwnd, IDC_EDIT4, "");
				SetDlgItemText(hwnd, IDC_EDIT5, "");
				SetDlgItemText(hwnd, IDC_EDIT6, "");

				EndDialog(hwnd, 0);

				HWND hDialog10 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG10), 0, cDialog10);

				ShowWindow(hDialog10, SW_SHOW);
				UpdateWindow(hDialog10);
			}
			else
			{
				MessageBox(NULL, "El pasajero ya esta registrado.", "AVISO", MB_OK | MB_ICONINFORMATION);
			}

			break;
		}
		default:
		{
			break;
		}
		}

		break;
	}

	default:
	{
		break;
	}
	}

	return false;  // Un callback siempre retorna falso
}

// Lista Pasajeros
BOOL CALLBACK cDialog11(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			if (miUsuario != nullptr)
			{
				SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
			}
			if (miUsuario->dato->foto != nullptr);
			{
				strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
			}

			aux = ini; // Nacionalidades
			while (aux->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux->Nacionalidad);
				aux = aux->sig;
			}
			if (aux->sig == nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux->Nacionalidad);
				aux = aux->sig;
			}

			//Ordenamiento HeapSort
			heapSort(iniPasajero);

			break;
		}
		case WM_COMMAND:
		{
			long opcion = LOWORD(wParam);
			cMenu(hwnd, opcion);

			switch (LOWORD(wParam))
			{
				case IDC_LIST3: // Nacionalidad
				{
					switch (HIWORD(wParam))
					{
					case LBN_DBLCLK: //Al dar doble clic en el ListBox 
					{
						char nacionalidadL[30] = { 0 };
						int indice = 0;

						indice = SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
						SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETTEXT, indice, (LPARAM)nacionalidadL);

						aux = ini;
						while (aux->sig != nullptr && strcmp(aux->Nacionalidad, nacionalidadL) != 0)
						{
							aux = aux->sig;
						}

						SetDlgItemText(hwnd, IDC_EDIT16, aux->Nacionalidad);

						break;
					}

					default:
					{
						break;
					}
					}

					break;
				}
				case IDC_BUTTON1: // Buscar
				{
					/*char pasajeroBuscar[30];
					GetDlgItemText(hwnd, IDC_EDIT2, pasajeroBuscar, sizeof(pasajeroBuscar));
					
					auxPasajero3 = iniPasajero;
					while (auxPasajero3->sig != nullptr && strcmp(pasajeroBuscar, auxPasajero3->dato->nombreComp) != 0)
					{
						auxPasajero3 = auxPasajero3->sig;
					}*/

					char pasajeroBuscar[30];
					GetDlgItemText(hwnd, IDC_EDIT2, pasajeroBuscar, sizeof(pasajeroBuscar));
					
					auxPasajero3 = binarySearchNombrePasajero(iniPasajero, pasajeroBuscar);

					if (auxPasajero3 != NULL) // (strcmp(pasajeroBuscar, auxPasajero3->dato->nombreComp) == 0)
					{
						SetDlgItemText(hwnd, IDC_EDIT3, auxPasajero3->dato->nombre);
						SetDlgItemText(hwnd, IDC_EDIT4, auxPasajero3->dato->apellidoP);
						SetDlgItemText(hwnd, IDC_EDIT5, auxPasajero3->dato->apellidoM);

						//Genero
						if (auxPasajero3->dato->genero == 1)
						{
							SetDlgItemText(hwnd, IDC_EDIT9, "Masculino");
						}
						else
						{
							SetDlgItemText(hwnd, IDC_EDIT9, "Femenino");
						}

						//Edad/Nacimiento
						char cadenaNacimiento[100];
						SYSTEMTIME cumple = { 0 };
						VariantTimeToSystemTime(auxPasajero->dato->nacimiento, &cumple);
						formatoFecha(&cumple, cadenaNacimiento);
						SetDlgItemText(hwnd, IDC_EDIT10, cadenaNacimiento);
						SetDlgItemInt(hwnd, IDC_EDIT11, formatoEdad(auxPasajero->dato->nacimiento), false);

						SetDlgItemText(hwnd, IDC_EDIT16, auxPasajero3->dato->nacionalidad);
					}
					else
					{
						MessageBox(NULL, "No se ha encontradó a este pasajero.", "AVISO", MB_OK | MB_ICONINFORMATION);
					}

					/*auxPasajero3 = iniPasajero;*/

					break;
				}
				case IDC_BUTTON2: // Editar
				{
					GetDlgItemText(hwnd, IDC_EDIT3, auxPasajero3->dato->nombre, sizeof(auxPasajero3->dato->nombre));
					GetDlgItemText(hwnd, IDC_EDIT4, auxPasajero3->dato->apellidoP, sizeof(auxPasajero3->dato->apellidoP));
					GetDlgItemText(hwnd, IDC_EDIT5, auxPasajero3->dato->apellidoM, sizeof(auxPasajero3->dato->apellidoM));
					GetDlgItemText(hwnd, IDC_EDIT16, auxPasajero3->dato->nacionalidad, sizeof(auxPasajero3->dato->nacionalidad));

					// Concatenación
					strcpy_s(auxPasajero3->dato->nombreComp, auxPasajero3->dato->nombre);
					strcat_s(auxPasajero3->dato->nombreComp, " ");
					strcat_s(auxPasajero3->dato->nombreComp, auxPasajero3->dato->apellidoP);
					strcat_s(auxPasajero3->dato->nombreComp, " ");
					strcat_s(auxPasajero3->dato->nombreComp, auxPasajero3->dato->apellidoM);

					//Genero
					if ((IsDlgButtonChecked(hwnd, IDC_RADIO1) == BST_CHECKED))
					{
						auxPasajero3->dato->genero = 1;
					}
					else
					{
						auxPasajero3->dato->genero = 0;
					}

					//Se obtiene la fecha de nacimiento
					HWND hDia = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
					SYSTEMTIME diaCumple = { 0 }; double dia;
					DateTime_GetSystemtime(hDia, &diaCumple);
					SystemTimeToVariantTime(&diaCumple, &dia);

					auxPasajero3->dato->nacimiento = dia;

					strcpy_s(auxPasajero3->dato->usuarioRegistro, miUsuario->dato->nick);

					SYSTEMTIME fecha = { 0 };
					GetLocalTime(&fecha);
					SystemTimeToVariantTime(&fecha, &auxPasajero3->dato->registro);

					MessageBox(NULL, "Cambios guardados.", "AVISO", MB_OK | MB_ICONINFORMATION);

					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");
					SetDlgItemText(hwnd, IDC_EDIT5, "");
					SetDlgItemText(hwnd, IDC_EDIT9, "");
					SetDlgItemText(hwnd, IDC_EDIT10, "");
					SetDlgItemText(hwnd, IDC_EDIT11, "");
					SetDlgItemText(hwnd, IDC_EDIT16, "");

					//Recarga la pestaña
					EndDialog(hwnd, 0);

					HWND hDialog11 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG11), 0, cDialog11);

					ShowWindow(hDialog11, SW_SHOW);
					UpdateWindow(hDialog11);

					break;
				}
				case IDC_BUTTON3: // Eliminar
				{
					int opc = MessageBox(hwnd, "¿Seguro que desea eliminar este pasajero?", "AVISO", MB_YESNO | MB_ICONQUESTION);

					switch (opc)
					{
					case IDYES:
					{
						char pasajero[30];
						GetDlgItemText(hwnd, IDC_EDIT2, pasajero, sizeof(pasajero));

						auxPasajero3 = iniPasajero;
						while (auxPasajero3->sig != nullptr && strcmp(pasajero, auxPasajero3->dato->nombreComp) != 0)
						{
							auxPasajero3 = auxPasajero3->sig;
						}
						if (/*auxPasajero3->sig == nullptr && */strcmp(pasajero, auxPasajero3->dato->nombreComp) != 0)
						{
							MessageBox(NULL, "No se encontró al pasajero.", "AVISO", MB_OK | MB_ICONINFORMATION);

							SetDlgItemText(hwnd, IDC_EDIT3, "");
							SetDlgItemText(hwnd, IDC_EDIT4, "");
							SetDlgItemText(hwnd, IDC_EDIT5, "");
							SetDlgItemText(hwnd, IDC_EDIT9, "");
							SetDlgItemText(hwnd, IDC_EDIT10, "");
							SetDlgItemText(hwnd, IDC_EDIT11, "");
							SetDlgItemText(hwnd, IDC_EDIT16, "");
						}
						else
						{
							eliminarPasajero(auxPasajero3->dato->nombreComp);

							SetDlgItemText(hwnd, IDC_EDIT3, "");
							SetDlgItemText(hwnd, IDC_EDIT4, "");
							SetDlgItemText(hwnd, IDC_EDIT5, "");
							SetDlgItemText(hwnd, IDC_EDIT9, "");
							SetDlgItemText(hwnd, IDC_EDIT10, "");
							SetDlgItemText(hwnd, IDC_EDIT11, "");
							SetDlgItemText(hwnd, IDC_EDIT16, "");

							auxPasajero3 = nullptr;
						}
						break;
					}

					case IDNO:
					{
						SetDlgItemText(hwnd, IDC_EDIT3, "");
						SetDlgItemText(hwnd, IDC_EDIT4, "");
						SetDlgItemText(hwnd, IDC_EDIT5, "");
						SetDlgItemText(hwnd, IDC_EDIT9, "");
						SetDlgItemText(hwnd, IDC_EDIT10, "");
						SetDlgItemText(hwnd, IDC_EDIT11, "");
						SetDlgItemText(hwnd, IDC_EDIT16, "");

						auxPasajero3 = nullptr;

						break;
					}

					default:
					{
						break;
					}
					}

					break;
				}

				default: break;
			}

			break;
		}

		default: break;
	}

	return false;  // Un callback siempre retorna falso
}

// Registro Boletos
BOOL CALLBACK cDialog12(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			//Pantalla
			if (miUsuario != nullptr)
			{
				SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
			}
			if (miUsuario->dato->foto != nullptr)
			{
				strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
			}
			
			auxVuelo2 = iniVuelo; //Vuelos
			if (iniVuelo != nullptr)
			{
				// Ordenamiento QueckSort Vuelos
				quickSortNum(iniVuelo);

				while (auxVuelo2->sig != nullptr)
				{
					char numStr[200];
					sprintf_s(numStr, sizeof(numStr), "%d", auxVuelo2->dato->num);
					SendDlgItemMessageA(hwnd, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)numStr);
					auxVuelo2 = auxVuelo2->sig;
				}

				if (auxVuelo2->sig == nullptr/* || auxEsp2->ant == nullptr*/)
				{
					char numStr[200];
					sprintf_s(numStr, sizeof(numStr), "%d", auxVuelo2->dato->num);
					SendDlgItemMessageA(hwnd, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)numStr);
					auxVuelo2 = auxVuelo2->sig;
				}
			}
			else
			{
				MessageBox(NULL, "No hay vuelos registrados.", "AVISO", MB_OK | MB_ICONINFORMATION);
			}

			break;
		}
		case WM_COMMAND:
		{
			long opcion = LOWORD(wParam);
			cMenu(hwnd, opcion);

			switch (LOWORD(wParam))
			{
			case IDC_LIST3: //Vuelos
			{
				switch (HIWORD(wParam))
				{
				case LBN_DBLCLK: //Al dar doble clic en el ListBox 
				{
					char vueloO[30] = { 0 };
					int indice2 = 0;
					indice2 = SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
					SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETTEXT, indice2, (LPARAM)vueloO);

					int numVuelo;
					numVuelo = atoi(vueloO);
					auxVuelo2 = iniVuelo;

					while (auxVuelo2->sig != nullptr && auxVuelo2->dato->num != numVuelo)
					{
						auxVuelo2 = auxVuelo2->sig;
					}

					SetDlgItemInt(hwnd, IDC_EDIT2, auxVuelo2->dato->num, NULL);
					SetDlgItemText(hwnd, IDC_EDIT3, auxVuelo2->dato->origen);
					SetDlgItemText(hwnd, IDC_EDIT4, auxVuelo2->dato->destino);

					char cadenaFecha[100];
					SYSTEMTIME fecha = { 0 };
					VariantTimeToSystemTime(auxVuelo2->dato->fecha, &fecha);
					formatoFecha(&fecha, cadenaFecha);
					//sprintf_s(cadenaNacimiento, "%f", miUsuario->dato->nacimiento);
					SetDlgItemText(hwnd, IDC_EDIT5, cadenaFecha);

					break;
				}
				default:
				{
					break;
				}
				}

				break;
			}
			case IDC_BUTTON1: //Buscar
			{
				char pasaBuscar[30];
				GetDlgItemText(hwnd, IDC_EDIT6, pasaBuscar, sizeof(pasaBuscar));
				
				auxPasajero3 = loopSearchNombrePasajero(iniPasajero, pasaBuscar);

				//Edad/Nacimiento
				char cadenaNacimiento[100];
				SYSTEMTIME cumple = { 0 };
				VariantTimeToSystemTime(auxPasajero3->dato->nacimiento, &cumple);
				formatoFecha(&cumple, cadenaNacimiento);
				int edad = formatoEdad(auxPasajero3->dato->nacimiento);

			
				if (auxPasajero3 != nullptr && (strcmp(pasaBuscar, auxPasajero3->dato->nombreComp) == 0))
				{
					if (edad <= 12 && auxVuelo2->dato->asientosN == 0) {
						MessageBox(NULL, "Todos los asientos para niños están ocupados.", "AVISO", MB_OK | MB_ICONINFORMATION);
						break;
					}
					if (edad <= 60 && auxVuelo2->dato->asientosA == 0) {
						MessageBox(NULL, "Todos los asientos para adultos están ocupados.", "AVISO", MB_OK | MB_ICONINFORMATION);
						break;
					}
					if (edad > 60 && auxVuelo2->dato->asientosM == 0) {
						MessageBox(NULL, "Todos los asientos para mayores están ocupados.", "AVISO", MB_OK | MB_ICONINFORMATION);
						break;
					}
					else {
						SetDlgItemText(hwnd, IDC_EDIT7, auxPasajero3->dato->nombreComp);
						//Edad/Nacimiento
						SetDlgItemInt(hwnd, IDC_EDIT8, edad, false);

						if (edad <= 12) {
							SetDlgItemText(hwnd, IDC_EDIT19, "Niño");
							break;
						}
						if (edad <= 60) {
							SetDlgItemText(hwnd, IDC_EDIT19, "Adulto");
							break;
						}
						else {
							SetDlgItemText(hwnd, IDC_EDIT19, "Adulto Mayor");
							break;
						}

					}
				}
				else
				{
					MessageBox(NULL, "No se ha encontradó a este pasajero.", "AVISO", MB_OK | MB_ICONINFORMATION);
				}

				break;
			}
			case IDC_BUTTON3: //Ejecutiva
			{
				if (auxVuelo2->dato->asientosE == 0)
				{
					MessageBox(NULL, "No hay asientos disponibles en la clase ejecutiva.", "AVISO", MB_OK | MB_ICONINFORMATION);
				}
				else
				{
					SetDlgItemText(hwnd, IDC_EDIT10, "Ejecutiva");
				}
				break;
			}
			case IDC_BUTTON4: //Turista
			{
				if (auxVuelo2->dato->asientosT == 0)
				{
					MessageBox(NULL, "No hay asientos disponibles en la clase turista.", "AVISO", MB_OK | MB_ICONINFORMATION);
				}
				else
				{
					SetDlgItemText(hwnd, IDC_EDIT10, "Turista");
				}
				break;
			}
			case IDC_BUTTON5: //Guardar
			{
				int numBoleto = GetDlgItemInt(hwnd, IDC_EDIT9, NULL, NULL);

				if (numBoleto <= auxVuelo2->dato->asientos)
				{
					auxBoleto2 = iniBoleto;
					while (auxBoleto2->sig != nullptr)
					{
						if((auxBoleto2->dato->numVuelo != auxVuelo2->dato->num && auxBoleto2->dato->num != numBoleto))
							auxBoleto2 = auxBoleto2->sig;
					}

					if (auxBoleto2->dato->num == numBoleto)
					{
						MessageBox(NULL, "El número de asiento no esta disponible, seleccione otro.", "AVISO", MB_OK | MB_ICONINFORMATION);
						SetDlgItemText(hwnd, IDC_EDIT19, "");
					}

					if (auxBoleto2->sig == nullptr && auxBoleto2->dato->numVuelo == auxVuelo2->dato->num) {
						if (auxBoleto2->dato->num == numBoleto)
						{
							MessageBox(NULL, "El número de asiento no esta disponible, seleccione otro.", "AVISO", MB_OK | MB_ICONINFORMATION);
							SetDlgItemText(hwnd, IDC_EDIT19, "");
						}
					}
				}

				if (auxBoleto2/*->sig*/ == nullptr || numBoleto != auxBoleto2->dato->num)
				{
					NodoBoleto* temp = new NodoBoleto;
					temp->dato = new DatoBoleto;

					temp->dato->numVuelo = GetDlgItemInt(hwnd, IDC_EDIT2, NULL, NULL);

					//Asientos
					/*auxVuelo2->dato->asientos - 1;*/

					char claseTE[10];
					GetDlgItemText(hwnd, IDC_EDIT10, claseTE, sizeof(claseTE));

					if (strcmp(claseTE, "Ejecutiva") == 0)
					{
						auxVuelo2->dato->asientosE - 1;
					}
					else
					{
						auxVuelo2->dato->asientosT - 1;
					}

					int edad = GetDlgItemInt(hwnd, IDC_EDIT8, NULL, NULL);

					if (edad <= 12)
					{
						auxVuelo2->dato->asientosN - 1;
					}
					else if(edad <= 60)
					{
						auxVuelo2->dato->asientosA - 1;
					}
					else
					{
						auxVuelo2->dato->asientosM - 1;
					}

					GetDlgItemText(hwnd, IDC_EDIT7, temp->dato->nombreCompPasajero, sizeof(temp->dato->nombreCompPasajero));
						
					temp->dato->num = GetDlgItemInt(hwnd, IDC_EDIT9, NULL, NULL);
					char clase[20];
					GetDlgItemText(hwnd, IDC_EDIT10, clase, sizeof(clase));
					if (strcmp(clase, "Turista")) {
						temp->dato->clase = 1;
					}
					else {
						temp->dato->clase = 0;
					}
					SYSTEMTIME fecha = { 0 };
					GetLocalTime(&fecha);
					SystemTimeToVariantTime(&fecha, &temp->dato->registroBoleto);
					temp->dato->registroPase = 0;
					temp->dato->pase = 0;
					temp->dato->status = 0;
						
					strcpy_s(temp->dato->usuarioRegistro, miUsuario->dato->nick);

					temp->sig = nullptr;
					temp->ant = nullptr;

					nuevoBoleto(temp);

					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");
					SetDlgItemText(hwnd, IDC_EDIT5, "");
					SetDlgItemText(hwnd, IDC_EDIT6, "");
					SetDlgItemText(hwnd, IDC_EDIT7, "");
					SetDlgItemText(hwnd, IDC_EDIT8, "");
					SetDlgItemText(hwnd, IDC_EDIT9, "");
					SetDlgItemText(hwnd, IDC_EDIT10, "");
					SetDlgItemText(hwnd, IDC_EDIT11, "");
					EndDialog(hwnd, 0);

					HWND hDialog10 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG10), 0, cDialog10);

					ShowWindow(hDialog10, SW_SHOW);
					UpdateWindow(hDialog10);
				}
				else
				{
					MessageBox(NULL, "El boleto ya esta registrado.", "AVISO", MB_OK | MB_ICONINFORMATION);
				}

				break;
			}
			//case IDC_BUTTON6: //Editar
			//{


			//	break;
			//}

			default: break;
			}

			break;
		}

		default: break;
	}

	return false;  // Un callback siempre retorna falso
}

// Lista Boletos
BOOL CALLBACK cDialog13(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		if (miUsuario != nullptr)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
		}
		if (miUsuario->dato->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}
		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1: // Buscar
		{
			char pasBolBuscar[30];
			GetDlgItemText(hwnd, IDC_EDIT21, pasBolBuscar, sizeof(pasBolBuscar));

			auxBoleto3 = binarySearchNombreBoleto(iniBoleto, pasBolBuscar);

			if (auxBoleto3 != NULL) // (strcmp(pasajeroBuscar, auxPasajero3->dato->nombreComp) == 0)
			{
				auxPasajero3 = binarySearchNombrePasajero(iniPasajero, auxBoleto3->dato->nombreCompPasajero);
				char cadenaNacimiento[100];
				SYSTEMTIME cumple = { 0 };
				VariantTimeToSystemTime(auxPasajero3->dato->nacimiento, &cumple);
				formatoFecha(&cumple, cadenaNacimiento);

				SetDlgItemText(hwnd, IDC_EDIT7, auxPasajero3->dato->nombreComp);
				SetDlgItemInt(hwnd, IDC_EDIT8, formatoEdad(auxPasajero->dato->nacimiento), false);
				SetDlgItemInt(hwnd, IDC_EDIT9, auxBoleto3->dato->num, NULL);
				if (auxBoleto3->dato->clase == 1)
				{
					SetDlgItemText(hwnd, IDC_EDIT10, "Turista");
				}
				else
				{
					SetDlgItemText(hwnd, IDC_EDIT10, "Ejecutiva");
				}
				//Costo dependiendo de la clase				
			}
			else
			{
				MessageBox(NULL, "El pasajero no está en la lista de boletos de este vuelo.", "AVISO", MB_OK | MB_ICONINFORMATION);
			}

			break;
		}
		case IDC_BUTTON2: //
		{


			break;
		}
		case IDC_BUTTON3: //
		{


			break;
		}
		case IDC_BUTTON4: // Editar
		{
			if (auxVuelo2 == nullptr)
			{
				MessageBox(NULL, "No se ha seleccionado un pasajero, seleccione una de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
				redirection = true;
				EndDialog(hwnd, 0);
				HWND hDialog12 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG12), 0, cDialog12);

				ShowWindow(hDialog12, SW_SHOW);
				UpdateWindow(hDialog12); //Opcional
			}

			break;
		}

		default:
		{
			break;
		}
		}

		break;
	}

	default:
	{
		break;
	}

	}

	return false;  // Un callback siempre retorna falso
}

// Pase de Abordar
BOOL CALLBACK cDialog14(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		if (miUsuario != nullptr)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);
		}
		if (miUsuario->dato->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1: // Buscar
		{
			char pasajeroBuscar[30];
			GetDlgItemText(hwnd, IDC_EDIT2, pasajeroBuscar, sizeof(pasajeroBuscar));

			auxPasajero3 = binarySearchNombrePasajero(iniPasajero, pasajeroBuscar);



			break;
		}

		default:
		{
			break;
		}

		}

		break;
	}

	default:
	{
		break;
	}

	}

	return false;  // Un callback siempre retorna falso
}
#pragma endregion

// Menu
bool cMenu(HWND hwnd, long opcion)
{
	switch (opcion)
	{
	case ID_PERFIL: // Perfil
	{
		EndDialog(hwnd, 0);

		HWND hDialog3 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG3), 0, cDialog3);

		ShowWindow(hDialog3, SW_SHOW);
		UpdateWindow(hDialog3); //Opcional

		break;
	}
	case ID_USUARIOS_REGISTRO: // Registro
	{
		EndDialog(hwnd, 0);

		HWND hDialog2 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG2), 0, cDialog2);

		ShowWindow(hDialog2, SW_SHOW);
		UpdateWindow(hDialog2); //Opcional

		break;
	}
	case ID_USUARIOS_LISTA: // Lista Usuarios
	{
		EndDialog(hwnd, 0);

		HWND hDialog4 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG4), 0, cDialog4);

		ShowWindow(hDialog4, SW_SHOW);
		UpdateWindow(hDialog4); //Opcional

		break;
	}
	case ID_VUELOS_REGISTRO: // Registro Vuelos
	{
		redirection = false;

		SetDlgItemText(hwnd, IDC_EDIT2, "");
		SetDlgItemText(hwnd, IDC_EDIT3, "");
		SetDlgItemText(hwnd, IDC_EDIT4, "");
		SetDlgItemText(hwnd, IDC_EDIT5, "");
		SetDlgItemText(hwnd, IDC_EDIT6, "");
		SetDlgItemText(hwnd, IDC_EDIT7, "");
		SetDlgItemText(hwnd, IDC_EDIT8, "");
		SetDlgItemText(hwnd, IDC_EDIT9, "");
		SetDlgItemText(hwnd, IDC_EDIT10, "");
		SetDlgItemText(hwnd, IDC_EDIT11, "");

		EndDialog(hwnd, 0);

		HWND hDialog5 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG5), 0, cDialog5);

		ShowWindow(hDialog5, SW_SHOW);
		UpdateWindow(hDialog5); //Opcional

		break;
	}
	case ID_VUELOS_LISTA: // Lista Vuelos
	{
		EndDialog(hwnd, 0);

		HWND hDialog6 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG6), 0, cDialog6);

		ShowWindow(hDialog6, SW_SHOW);
		UpdateWindow(hDialog6); //Opcional

		break;
	}
	case ID_VUELOS_MANIFIESTO: // Manifiesto
	{
		EndDialog(hwnd, 0);

		HWND hDialog7 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG7), 0, cDialog7);

		ShowWindow(hDialog7, SW_SHOW);
		UpdateWindow(hDialog7); //Opcional

		break;
	}
	case ID_VUELOS_REPOTE: // Reporte Vuelos
	{
		EndDialog(hwnd, 0);
		HWND hDialog9 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG9), 0, cDialog9);
		ShowWindow(hDialog9, SW_SHOW);
		UpdateWindow(hDialog9); //Opcional
		break;
	}
	case ID_PASAJEROS_REGISTRO: // Registro Pasajeros
	{
		EndDialog(hwnd, 0);

		HWND hDialog10 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG10), 0, cDialog10);

		ShowWindow(hDialog10, SW_SHOW);
		UpdateWindow(hDialog10); //Opcional

		break;
	}
	case ID_PASAJEROS_LISTA: // Lista Pasajeros
	{
		EndDialog(hwnd, 0);

		HWND hDialog11 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG11), 0, cDialog11);

		ShowWindow(hDialog11, SW_SHOW);
		UpdateWindow(hDialog11); //Opcional

		break;
	}
	case ID_BOLETOS_REGISTRO: // Registro boletos
	{
		EndDialog(hwnd, 0);

		HWND hDialog12 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG12), 0, cDialog12);

		ShowWindow(hDialog12, SW_SHOW);
		UpdateWindow(hDialog12); //Opcional

		break;
	}
	case ID_BOLETOS_ABORDAJE: // Abordaje boletos
	{
		EndDialog(hwnd, 0);

		HWND hDialog13 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG13), 0, cDialog13);

		ShowWindow(hDialog13, SW_SHOW);
		UpdateWindow(hDialog13); //Opcional

		break;
	}
	case ID_PASES: // Pases
	{
		EndDialog(hwnd, 0);

		HWND hDialog14 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG14), 0, cDialog14);

		ShowWindow(hDialog14, SW_SHOW);
		UpdateWindow(hDialog14); //Opcional

		break;
	}
	case ID_SALIR_INICIO: // Inicio
	{
		int opc = MessageBox(hwnd, "¿Seguro que desea volver al inicio?", "AVISO", MB_YESNO | MB_ICONQUESTION);
		switch (opc)
		{
		case IDYES:
		{
			EndDialog(hwnd, 0);
			HWND hDialog1 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG1), 0, cDialog1);
			ShowWindow(hDialog1, SW_SHOW);
			UpdateWindow(hDialog1); //Opcional
			break;
		}
		default:
		{
			break;
		}
		}
		break;
	}
	case ID_SALIR_CERRAR: // Cerrar
	{
		int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);

		switch (opc)
		{
		case IDYES:
		{
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		}
		default:
		{
			break;
		}

		}
		break;
	}
	default:
	{
		break;
	}
	}
	return true;
}

// Funciones
#pragma region Funciones
//Generales
char* formatoFecha(LPSYSTEMTIME Sys, char* buff) {
	std::string strMessage;
	CString cstrMessage;

	cstrMessage.Format(_T("%d-%02d-%02d %02d:%02d:%02d.%03d"),
		Sys->wYear,
		Sys->wMonth,
		Sys->wDay,
		Sys->wHour,
		Sys->wMinute,
		Sys->wSecond,
		Sys->wMilliseconds);

	strMessage = CT2A(cstrMessage.GetString());
	std::cout << "System time = " << strMessage << std::endl;

	std::ostringstream ossMessage;
	ossMessage
		<< Sys->wYear << "-"
		<< std::setw(2) << std::setfill('0') << Sys->wMonth << "-"
		<< std::setw(2) << std::setfill('0') << Sys->wDay << " "
		<< std::setw(2) << std::setfill('0') << Sys->wHour << ":"
		<< std::setw(2) << std::setfill('0') << Sys->wMinute << ":"
		<< std::setw(2) << std::setfill('0') << Sys->wSecond << "."
		<< std::setw(3) << std::setfill('0') << Sys->wMilliseconds;

	strMessage = ossMessage.str();
	std::cout << "System time = " << strMessage << std::endl;

	sprintf_s(buff,
		100,
		"%d-%02d-%02d %02d:%02d:%02d",
		Sys->wYear,
		Sys->wMonth,
		Sys->wDay,
		Sys->wHour,
		Sys->wMinute,
		Sys->wSecond,
		Sys->wMilliseconds);

	return buff;
}
int formatoEdad(double cumple) {
	SYSTEMTIME SysNow = { 0 };
	SYSTEMTIME Cumple = { 0 };
	double now = 0;
	GetSystemTime(&SysNow);
	VariantTimeToSystemTime(cumple, &Cumple);
	if (SysNow.wYear <= Cumple.wYear) {
		return 0;
	}
	SystemTimeToVariantTime(&SysNow, &now);
	VariantTimeToSystemTime(now - cumple, &SysNow);

	return (SysNow.wYear - 1900);
}
bool adminComprobation(NodoUsuario* miUsu) {
	ifstream archivo("UsuarioAdmin.txt");
	string linea;
	getline(archivo, linea);
	archivo.close();

	size_t pos = linea.find(",");
	string usuario = linea.substr(0, pos);

	if (strcmp(miUsu->dato->nick, usuario.c_str()) == 0)
		return true;
	else
		return false;
}
//Listas de Usuarios
#pragma region Funciones de Listas Usuarios
void nuevoUsuarioLista(NodoUsuario* nuevo)
{
	if (iniUsuario == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniUsuario = new NodoUsuario;
		iniUsuario->dato = new DatoUsuario;

		strcpy_s(iniUsuario->dato->nick, nuevo->dato->nick);
		strcpy_s(iniUsuario->dato->nombre, nuevo->dato->nombre);
		strcpy_s(iniUsuario->dato->apellidoP, nuevo->dato->apellidoP);
		strcpy_s(iniUsuario->dato->apellidoM, nuevo->dato->apellidoM);
		strcpy_s(iniUsuario->dato->email, nuevo->dato->email);
		strcpy_s(iniUsuario->dato->password, nuevo->dato->password);

		// Concatenación
		strcpy_s(iniUsuario->dato->nombreComp, nuevo->dato->nombre);
		strcat_s(iniUsuario->dato->nombreComp, " ");
		strcat_s(iniUsuario->dato->nombreComp, iniUsuario->dato->apellidoP);
		strcat_s(iniUsuario->dato->nombreComp, " ");
		strcat_s(iniUsuario->dato->nombreComp, iniUsuario->dato->apellidoM);

		iniUsuario->dato->nacimiento = nuevo->dato->nacimiento;
		iniUsuario->dato->genero = nuevo->dato->genero;
		strcpy_s(iniUsuario->dato->foto, nuevo->dato->foto);
		iniUsuario->dato->registro = nuevo->dato->registro;

		iniUsuario->sig = nullptr;
		iniUsuario->ant = nullptr;

		auxUsuario2 = auxUsuario;
		auxUsuario3 = auxUsuario;
		auxUsuario = iniUsuario;
	}
	else
	{
		auxUsuario = iniUsuario;
		while (auxUsuario->sig != nullptr)
		{
			auxUsuario = auxUsuario->sig;
		}
		auxUsuario->sig = new NodoUsuario;
		auxUsuario->sig->sig = nullptr;
		auxUsuario->sig->ant = auxUsuario;
		auxUsuario = auxUsuario->sig;
		auxUsuario->dato = new DatoUsuario;

		strcpy_s(auxUsuario->dato->nick, nuevo->dato->nick);
		strcpy_s(auxUsuario->dato->nombre, nuevo->dato->nombre);
		strcpy_s(auxUsuario->dato->apellidoP, nuevo->dato->apellidoP);
		strcpy_s(auxUsuario->dato->apellidoM, nuevo->dato->apellidoM);
		strcpy_s(auxUsuario->dato->email, nuevo->dato->email);
		strcpy_s(auxUsuario->dato->password, nuevo->dato->password);

		// Concatenación
		strcpy_s(auxUsuario->dato->nombreComp, nuevo->dato->nombre);
		strcat_s(auxUsuario->dato->nombreComp, " ");
		strcat_s(auxUsuario->dato->nombreComp, auxUsuario->dato->apellidoP);
		strcat_s(auxUsuario->dato->nombreComp, " ");
		strcat_s(auxUsuario->dato->nombreComp, auxUsuario->dato->apellidoM);

		auxUsuario->dato->nacimiento = nuevo->dato->nacimiento;
		auxUsuario->dato->genero = nuevo->dato->genero;
		strcpy_s(auxUsuario->dato->foto, nuevo->dato->foto);
		auxUsuario->dato->registro = nuevo->dato->registro;

		auxUsuario2 = auxUsuario;
		auxUsuario3 = auxUsuario;
		auxUsuario = iniUsuario;
	}
	//MessageBox(NULL, "Se ha registrado el usuario con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
}
void eliminarUsuarioLista(char nomUsu[30])
{
	NodoUsuario* start;
	auxUsuario = iniUsuario;

	if (auxUsuario == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxUsuario->sig != nullptr && strcmp(auxUsuario->dato->nick, nomUsu) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxUsuario = auxUsuario->sig;
		}
		if (auxUsuario->sig == nullptr && strcmp(auxUsuario->dato->nick, nomUsu) != 0)
		{
			MessageBox(0, "Usuario no encontrado", "AVISO", MB_OK);
		}
		else if (auxUsuario == iniUsuario)
		{	//El nodo es el primero
			if (auxUsuario->sig == nullptr)
			{ //Si es el primero y unico nodo
				//delete auxEsp;		//Eliminamos el primer nodo
				//inicio = nullptr;
				//auxEsp = inicio;
				iniUsuario = nullptr;
				delete auxUsuario;
				auxUsuario = iniUsuario;
				auxUsuario2 = auxUsuario;
				//auxUsu3 = auxUsu;
			}
			else
			{ //Si es el primero y hay mas nodos
				//inicio = auxEsp->sig;	//Cambiamos el puntero 'inicio' al segundo nodo, que ahora es nuestro primer elemento
				//delete auxEsp;			//Eliminamos el primer nodo		
				//auxEsp = inicio;			//Para que auxEsp no quede sin apuntar a nada, la apuntamos al inicio
				//auxEsp->ant = nullptr;
				//inicio = iniEsp->sig;
				//auxEsp->sig->ant = nullptr;
				//delete auxEsp;
				//auxEsp = iniEsp;
				start = iniUsuario->sig;
				auxUsuario->sig->ant = nullptr;
				delete auxUsuario;
				auxUsuario = start;
				auxUsuario->ant = nullptr;
				auxUsuario = iniUsuario;
				auxUsuario2 = auxUsuario;
				//auxUsu3 = auxUsu;
			}
			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);
		}
		else
		{
			if (auxUsuario->sig == nullptr)
			{ //Si el nodo es el último
				auxUsuario->ant->sig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete auxUsuario;
				auxUsuario = iniUsuario;
				auxUsuario2 = auxUsuario;
				//auxUsu3 = auxUsu;
			}
			else
			{ //Si es cualquier nodo que no sea el inicio o el último
				auxUsuario->sig->ant = auxUsuario->ant;
				auxUsuario->ant->sig = auxUsuario->sig;
				delete auxUsuario;
				auxUsuario = iniUsuario;
				auxUsuario2 = auxUsuario;
				//auxUsu3 = auxUsu; //Para que auxEsp no quede sin apuntar a nada, la apuntamos al inicio
			}
			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);
		}
	}
}
void escribirUsuarios() {
	ofstream archivo("Usuarios.bin", ios::binary | ios::out | ios::trunc);
	NodoUsuario* aux = iniUsuario;

	while (aux != nullptr) {
		if (aux->dato != nullptr && aux->dato->nick[0] != '\0') {
			archivo.write(reinterpret_cast<char*>(&aux->dato->type), sizeof(aux->dato->type));
			archivo.write(aux->dato->nick, sizeof(aux->dato->nick));
			archivo.write(aux->dato->nombre, sizeof(aux->dato->nombre));
			archivo.write(aux->dato->apellidoP, sizeof(aux->dato->apellidoP));
			archivo.write(aux->dato->apellidoM, sizeof(aux->dato->apellidoM));
			archivo.write(aux->dato->nombreComp, sizeof(aux->dato->nombreComp));
			archivo.write(aux->dato->password, sizeof(aux->dato->password));
			archivo.write(reinterpret_cast<char*>(&aux->dato->nacimiento), sizeof(aux->dato->nacimiento));
			archivo.write(reinterpret_cast<char*>(&aux->dato->genero), sizeof(aux->dato->genero));
			archivo.write(aux->dato->email, sizeof(aux->dato->email));
			archivo.write(aux->dato->foto, sizeof(aux->dato->foto));
			archivo.write(reinterpret_cast<char*>(&aux->dato->registro), sizeof(aux->dato->registro));
		}
		aux = aux->sig;
	}
	archivo.close();
	// Reiniciamos aux a iniUsuario para asegurar que iniUsuario apunta al inicio de la lista
	aux = iniUsuario;
}
void leerUsuarios() {
	ifstream archivo("Usuarios.bin", ios::binary);

	while (archivo) {
		DatoUsuario* dato = new DatoUsuario;
		archivo.read(reinterpret_cast<char*>(&dato->type), sizeof(dato->type));
		archivo.read(dato->nick, sizeof(dato->nick));
		archivo.read(dato->nombre, sizeof(dato->nombre));
		archivo.read(dato->apellidoP, sizeof(dato->apellidoP));
		archivo.read(dato->apellidoM, sizeof(dato->apellidoM));
		archivo.read(dato->nombreComp, sizeof(dato->nombreComp));
		archivo.read(dato->password, sizeof(dato->password));
		archivo.read(reinterpret_cast<char*>(&dato->nacimiento), sizeof(dato->nacimiento));
		archivo.read(reinterpret_cast<char*>(&dato->genero), sizeof(dato->genero));
		archivo.read(dato->email, sizeof(dato->email));
		archivo.read(dato->foto, sizeof(dato->foto));
		archivo.read(reinterpret_cast<char*>(&dato->registro), sizeof(dato->registro));

		if (archivo) {
			NodoUsuario* nuevo = new NodoUsuario;
			nuevo->dato = dato;
			nuevo->ant = nullptr;
			nuevo->sig = nullptr;
			nuevoUsuarioLista(nuevo);
		}
		else {
			delete dato;
		}
	}
	archivo.close();
	// Reiniciamos aux a iniUsuario para asegurar que iniUsuario apunta al inicio de la lista
	NodoUsuario* aux = iniUsuario;
}
#pragma region QuickSort
//Generales
void swapData(NodoUsuario* a, NodoUsuario* b) {
	DatoUsuario* temp = a->dato;
	a->dato = b->dato;
	b->dato = temp;
}
NodoUsuario* lastNode(NodoUsuario* root) //Función para encontrar el último nodo
{
	while (root && root->sig)
		root = root->sig;
	return root;
}
//Específicas
NodoUsuario* partitionNick(NodoUsuario* l, NodoUsuario* h)
{
	//Se toma el último elemento como pivote
	// x = high (pivote)
	char* x = h->dato->nick;
	// i = low (recorrido)
	NodoUsuario* i = l->ant;
	

	//Acomoda los elmentos menores a la izquierda y mayores a la derecha
	for (NodoUsuario* j = l; j != h; j = j->sig)
	{
		if (_stricmp(j->dato->nick, x) <= 0)
		{
			// Si i = NULL, se convierte en l, si no, se avanza al siguiente nodo
			i = (i == NULL) ? l : i->sig;
			//Se intercambian los numeros
			swapData(i, j);
		}
	}
	//Se hace el mismo proceso con el pivote
	i = (i == NULL) ? l : i->sig;
	swapData(i, h);
	return i;
}
void _quickSortNick(NodoUsuario* l, NodoUsuario* h) // Función recursiva
{
	if (h != NULL && l != h && l != h->sig)
	{
		NodoUsuario* p = partitionNick(l, h);
		_quickSortNick(l, p->ant);
		_quickSortNick(p->sig, h);
	}
}
void quickSortNick(NodoUsuario* head) // Función principal
{
	// Encuentra el último nodo
	NodoUsuario* h = lastNode(head);

	// Manda a llamar la función de QuickSort recursiva
	_quickSortNick(head, h);
}
/*
* void printListNick(NodoUsuario* head)
{
	while (head)
	{
		std::cout << head->dato->nick << "\n";
		head = head->sig;
	}
	std::cout << std::endl;
}
*/
#pragma endregion
#pragma region Arbol
//Conversiones
NodoUsuario* sortedListToBST(NodoUsuario* head) //Función principal
{
	//Se cuenta los nodos de la lista
	int n = countNodes(head);

	//Se crea el arbol
	return sortedListToBSTRecur(&head, n);
}
NodoUsuario* sortedListToBSTRecur(NodoUsuario** head_ref, int n) //Construye el arbol y devuelve la raíz
{
	//head_ref = Puntero al puntero del nodo head de la lista
	//n = Numero de nodos de la lista
		
	// Caso base
	if (n <= 0)
		return NULL;

	//Construye de forma recursiva el subarbol de la izquierda
	NodoUsuario* left = sortedListToBSTRecur(head_ref, n / 2);

	//Ahora head_ref apunta al nodo del medio, por lo que lo tomaremos como la raíz
	NodoUsuario* root = *head_ref;

	//Declaramos el puntero del subarbol de la izquierda 
	root->ant = left;

	/* Change head pointer of Linked List
	for parent recursive calls */
	*head_ref = (*head_ref)->sig;

	//Construye el subarbol izquierdo y lo conecta con la raíz
	//El número de nodos es el (total - subarbol izquierdo - 1)
	root->sig = sortedListToBSTRecur(head_ref, n - n / 2 - 1);

	return root;
}
int countNodes(NodoUsuario* head) //Cuenta los nodos de una lista
{
	int count = 0;
	NodoUsuario* temp = head;
	while (temp)
	{
		temp = temp->sig;
		count++;
	}
	return count;
}
NodoUsuario* BinaryTree2DoubleLinkedList(NodoUsuario* root)
{
	// Caso base
	if (root == NULL)
		return NULL;

	// Nodo estático para mantener el último nodo visitado
	static NodoUsuario* ant = NULL;

	// Convertir el subárbol izquierdo de forma recursiva
	BinaryTree2DoubleLinkedList(root->ant);

	// Ahora convertir este nodo
	if (ant != NULL) {
		root->ant = ant;  // Hacer que el nodo actual sea el siguiente del último nodo visitado
		ant->sig = root;  // Hacer que el último nodo visitado sea el anterior del nodo actual
	}
	else {
		// Si ant es NULL, entonces este nodo es el primer nodo de la lista
		iniUsuario = root;
	}

	ant = root;  // Actualizar el último nodo visitado al nodo actual

	// Convertir el subárbol derecho de forma recursiva
	BinaryTree2DoubleLinkedList(root->sig);

	return iniUsuario;  // Devolver el primer nodo de la lista
}
/*void BinaryTree2DoubleLinkedListDobleNode(NodoUsuario* root, NodoUsuario** head)
{
	//Función recursiva que convierte una arbol a una lista
	//root = Puntero a la raíz del arbol binario
	//head = Puntero a la cabeza de la lista

	// Caso base
	if (root == NULL)
		return;

	//Se inicializa el nodo anteriormente visitado como null
	//Es estático para que sea el igual en todas las llamadas recursivas
	static NodoUsuario* ant = NULL;

	//Se convierte el subarbol izquierdo de forma recursiva
	BinaryTree2DoubleLinkedListDobleNode(root->ant, head);

	// Now convert this node
	if (ant == NULL)
		*head = root;
	else {
		root->ant = ant;
		ant->ant = root;
	}
	ant = root;

	//Se covierte ek subarbol derecho
	BinaryTree2DoubleLinkedListDobleNode(root->sig, head);
}*/
//Operaciones
NodoUsuario* newNode(DatoUsuario* data)
{
	NodoUsuario* new_node = new NodoUsuario;
	new_node->dato = data;
	new_node->ant = new_node->sig = NULL;
	return (new_node);
}
struct NodoUsuario* insertTreeDato(struct NodoUsuario* nodo, DatoUsuario* data)
{
	// Caso Base: Si está vacío, devuelve u nuevo nodo
	if (nodo == NULL)
		return newNode(data);

	//Se usa de forma recursiva para atravesar todo el arbol
	if ((_stricmp(data->nick, nodo->dato->nick) < 0))
		nodo->ant = insertTreeDato(nodo->ant, data);
	else if (_stricmp(data->nick, nodo->dato->nick) > 0)
		nodo->sig = insertTreeDato(nodo->sig, data);

	// Return the (unchanged) node pointer
	return nodo;
}
void insertTree(NodoUsuario*& nodo, NodoUsuario* nuevoNodo)
{
	// Caso Base: Si está vacío, asigna el nuevo nodo
	if (nodo == NULL)
	{
		nodo = nuevoNodo;
		return;
	}

	//Se usa de forma recursiva para atravesar todo el arbol
	if ((_stricmp(nuevoNodo->dato->nick, nodo->dato->nick) < 0))
		insertTree(nodo->ant, nuevoNodo);
	else if (_stricmp(nuevoNodo->dato->nick, nodo->dato->nick) > 0)
		insertTree(nodo->sig, nuevoNodo);
}
struct NodoUsuario* searchTree(struct NodoUsuario* root, DatoUsuario* data) //Busca un nick en el arbol
{
	// Casos Base: raíz es null o el nick está en la raíz
	if (root == NULL || _stricmp(root->dato->nick, data->nick) == 0)
		return root;

	// El nick es más "grande" que el de la raíz
	if (_stricmp(root->dato->nick, data->nick) < 0)
		return searchTree(root->sig, data);

	// El nick es más "pequeño" que el de la raíz
	return searchTree(root->ant, data);
}
NodoUsuario* deleteTreeNodeByNick(NodoUsuario* root, char* nick) //Borra el nodo con el
{
	// Base case
	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the root's key,
	// then it lies in the left subtree
	
	if (_stricmp(nick, root->dato->nick) < 0) {
		root->ant = deleteTreeNodeByNick(root->ant, nick);
		return root;
	}
	// If the key to be deleted is greater than the root's key,
	// then it lies in the right subtree
	else if (_stricmp(nick, root->dato->nick) > 0) {
		root->sig = deleteTreeNodeByNick(root->sig, nick);
		return root;
	}

	// If key is same as root's key, then this is the node to be deleted
	// Node with only one child or no child
	if (root->ant == NULL) { 
		NodoUsuario* temp = root->sig;
		delete root;
		return temp;
	}
	else if (root->sig == NULL) {
		NodoUsuario* temp = root->ant;
		delete root;
		return temp;
	}

	// Node with two children: Get the inorder successor (smallest
	// in the right subtree)
	NodoUsuario* succParent = root;
	NodoUsuario* succ = root->sig;
	while (succ->ant != NULL) {
		succParent = succ;
		succ = succ->ant;
	}

	// Copy the inorder successor's content to this node
	root->dato = succ->dato;

	// Delete the inorder successor
	if (succParent->ant == succ)
		succParent->ant = succ->sig;
	else
		succParent->sig = succ->sig;

	delete succ;
	return root;
}
//Funciones para mostrar el arbol en un ListBox
void preOrderList(NodoUsuario* node, HWND hwnd)
{
	if (node == NULL)
		return;
	SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, (WPARAM)0, (LPARAM)node->dato->nick);
	preOrderList(node->ant, hwnd);
	preOrderList(node->sig, hwnd);
}
void inOrderList(NodoUsuario* root, HWND hwnd)
{
	if (root != NULL) {
		inOrderList(root->ant, hwnd);
		SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, (WPARAM)0, (LPARAM)root->dato->nick);
		inOrderList(root->sig, hwnd);
	}
}
/*
// Funciones para crear y mostrar listas
void push(NodoUsuario** head_ref, DatoUsuario* new_data)
{

NodoUsuario* new_node = new NodoUsuario();
new_node->dato = new_data;
new_node->ant = NULL;
new_node->sig = (*head_ref);
if ((*head_ref) != NULL)
(*head_ref)->ant = new_node;
(*head_ref) = new_node;
}
void printList(NodoUsuario* node)
{
	while (node != NULL)
	{
		std::cout << node->dato << " ";
		node = node->sig;
	}
}
*/
#pragma endregion
#pragma endregion

//Listas de Vuelos
#pragma region Funciones de Listas Vuelos
void nuevoVuelo(NodoVuelo* nuevoV)
{
	if (iniVuelo == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniVuelo = new NodoVuelo;
		iniVuelo->dato = new DatoVuelo;

		strcpy_s(iniVuelo->dato->origen, nuevoV->dato->origen);
		strcpy_s(iniVuelo->dato->destino, nuevoV->dato->destino);
		strcpy_s(iniVuelo->dato->modelo, nuevoV->dato->modelo);

		iniVuelo->dato->num = nuevoV->dato->num;
		iniVuelo->dato->fecha = nuevoV->dato->fecha;
		iniVuelo->dato->status = nuevoV->dato->status;
		iniVuelo->dato->registro = nuevoV->dato->registro;


		iniVuelo->dato->asientosT = nuevoV->dato->asientosT;
		iniVuelo->dato->asientosCT = nuevoV->dato->asientosCT;
		iniVuelo->dato->asientosE = nuevoV->dato->asientosE;
		iniVuelo->dato->asientosCE = nuevoV->dato->asientosCT;

		iniVuelo->dato->asientosN = nuevoV->dato->asientosN;
		iniVuelo->dato->asientosA = nuevoV->dato->asientosA;
		iniVuelo->dato->asientosM = nuevoV->dato->asientosM;

		iniVuelo->dato->asientos = nuevoV->dato->asientos;


		strcpy_s(iniVuelo->dato->usuarioRegistro, nuevoV->dato->usuarioRegistro);

		iniVuelo->sig = nullptr;
		iniVuelo->ant = nullptr;

		auxVuelo2 = auxVuelo;
		auxVuelo3 = auxVuelo;
		auxVuelo = iniVuelo;
	}
	else
	{
		auxVuelo = iniVuelo;

		while (auxVuelo->sig != nullptr)
		{
			auxVuelo = auxVuelo->sig;
		}

		auxVuelo->sig = new NodoVuelo;
		auxVuelo->sig->sig = nullptr;
		auxVuelo->sig->ant = auxVuelo;
		auxVuelo = auxVuelo->sig;
		auxVuelo->dato = new DatoVuelo;

		strcpy_s(auxVuelo->dato->origen, nuevoV->dato->origen);
		strcpy_s(auxVuelo->dato->destino, nuevoV->dato->destino);
		strcpy_s(auxVuelo->dato->modelo, nuevoV->dato->modelo);

		auxVuelo->dato->num = nuevoV->dato->num;
		auxVuelo->dato->fecha = nuevoV->dato->fecha;
		auxVuelo->dato->status = nuevoV->dato->status;
		auxVuelo->dato->registro = nuevoV->dato->registro;


		auxVuelo->dato->asientosT = nuevoV->dato->asientosT;
		auxVuelo->dato->asientosCT = nuevoV->dato->asientosCT;
		auxVuelo->dato->asientosE = nuevoV->dato->asientosE;
		auxVuelo->dato->asientosCE = nuevoV->dato->asientosCT;

		auxVuelo->dato->asientosN = nuevoV->dato->asientosN;
		auxVuelo->dato->asientosA = nuevoV->dato->asientosA;
		auxVuelo->dato->asientosM = nuevoV->dato->asientosM;

		auxVuelo->dato->asientos = nuevoV->dato->asientos;


		strcpy_s(auxVuelo->dato->usuarioRegistro, nuevoV->dato->usuarioRegistro);

		auxVuelo2 = auxVuelo;
		auxVuelo3 = auxVuelo;
		auxVuelo = iniVuelo;
	}
	MessageBox(NULL, "Se ha registrado el vuelo con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
}
void eliminarVuelo(char nomEsp[30])
{
	NodoVuelo* start;
	auxVuelo = iniVuelo;

	if (auxVuelo == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxVuelo->sig != nullptr && strcmp(auxVuelo->dato->origen, nomEsp) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxVuelo = auxVuelo->sig;
		}
		if (auxVuelo->sig == nullptr && strcmp(auxVuelo->dato->origen, nomEsp) != 0)
		{
			MessageBox(0, "Especialidad no encontrada", "AVISO", MB_OK);
		}
		else if (auxVuelo == iniVuelo)
		{	//El nodo es el primero 

			if (auxVuelo->sig == nullptr)
			{ //Si es el primero y unico nodo
				//delete auxEsp;		//Eliminamos el primer nodo
				//inicio = nullptr;
				//auxEsp = inicio;

				iniVuelo = nullptr;
				delete auxVuelo;

				auxVuelo = iniVuelo;
				auxVuelo2 = auxVuelo;
			}
			else
			{ //Si es el primero y hay mas nodos

				//inicio = auxEsp->sig;	//Cambiamos el puntero 'inicio' al segundo nodo, que ahora es nuestro primer elemento
				//delete auxEsp;			//Eliminamos el primer nodo		
				//auxEsp = inicio;			//Para que auxEsp no quede sin apuntar a nada, la apuntamos al inicio
				//auxEsp->ant = nullptr;

				/*inicio = iniEsp->sig;
				auxEsp->sig->ant = nullptr;
				delete auxEsp;
				auxEsp = iniEsp;*/

				start = iniVuelo->sig;
				auxVuelo->sig->ant = nullptr;
				delete auxVuelo;
				auxVuelo = start;
				auxVuelo->ant = nullptr;

				auxVuelo2 = auxVuelo;
				iniVuelo = auxVuelo;
			}

			MessageBox(0, "Especialidad eliminada", "AVISO", MB_OK);
		}
		else
		{

			if (auxVuelo->sig == nullptr)
			{ //Si el nodo es el último
				auxVuelo->ant->sig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete auxVuelo;

				auxVuelo = iniVuelo;
				auxVuelo2 = auxVuelo;
			}
			else
			{ //Si es cualquier nodo que no sea el inicio o el último
				auxVuelo->sig->ant = auxVuelo->ant;
				auxVuelo->ant->sig = auxVuelo->sig;
				delete auxVuelo;

				auxVuelo2 = auxVuelo;
				auxVuelo = iniVuelo; //Para que auxEsp no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "Especialidad eliminada", "AVISO", MB_OK);

		}
	}

}
void escribirVuelo()
{
	auxVuelo = iniVuelo;

	ofstream escribir("Vuelos.bin", ios::binary | ios::out | ios::trunc);

	if (!escribir.is_open())
	{
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (escribir.is_open())
	{
		while (auxVuelo != nullptr)
		{
			if (escribir.bad())
			{
				MessageBox(NULL, "Ocurrió un error durante la escritura", "Error", MB_OK | MB_ICONERROR);

				return;
			}

			escribir.write((char*)auxVuelo->dato, sizeof(DatoVuelo));
			auxVuelo = auxVuelo->sig;
		}

		escribir.close();
	}
}
void leerVuelos()
{
	ifstream leer("Vuelos.bin", ios::binary);

	if (!leer.is_open())
	{
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (leer.is_open())
	{
		NodoVuelo* nuevo = nullptr;

		while (true)
		{
			nuevo = new NodoVuelo;
			nuevo->dato = new DatoVuelo;

			if (!leer.read((char*)nuevo->dato, sizeof(DatoVuelo)))
			{
				delete nuevo->dato;
				delete nuevo;
				break;
			}

			if (iniVuelo == nullptr)
			{
				iniVuelo = nuevo;
				iniVuelo->sig = nullptr;
				iniVuelo->ant = nullptr;
				auxVuelo = iniVuelo;
			}
			else
			{
				auxVuelo->sig = nuevo;
				auxVuelo->sig->ant = auxVuelo;
				auxVuelo = auxVuelo->sig;
				auxVuelo->sig = nullptr;
			}
		}

		leer.close();
	}
}
void reporteVuelos(HWND hwnd, int listBoxId)
{
	ofstream escribir("Reporte de vuelos.txt", ios::out | ios::trunc);
	if (!escribir.is_open()) {
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	// Obtener el número de elementos en el ListBox
	int count = SendMessage(GetDlgItem(hwnd, listBoxId), LB_GETCOUNT, 0, 0);
	if (count == 0) {
		MessageBox(NULL, "No hay vuelos para reportar", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	for (int i = 0; i < count; i++) {
		char text[256];
		// Obtener el texto del elemento
		SendMessage(GetDlgItem(hwnd, listBoxId), LB_GETTEXT, i, (LPARAM)text);
		// Escribir el texto en el archivo
		escribir << text << endl;
	}
	escribir.close();
}
void printVuelosEnRango(HWND hwnd, int List, NodoVuelo* iniVuelos, DATE inicioDate, DATE finDate) {
	for (NodoVuelo* nodo = iniVuelos; nodo != NULL; nodo = nodo->sig) {
		// Comprobar si la fecha del vuelo está dentro del rango
		if (nodo->dato->fecha >= inicioDate && nodo->dato->fecha <= finDate) {
			// Convertir el número de vuelo a una cadena
			char numVueloStr[10];
			sprintf_s(numVueloStr, sizeof(numVueloStr), "%d", nodo->dato->num);

			// Agregar el número de vuelo al ListBox
			SendDlgItemMessage(hwnd, List, LB_ADDSTRING, 0, (LPARAM)numVueloStr);
		}
	}
}
void generarManifiestoPasajeros(NodoBoleto* iniBoletos, int numVuelo, const char* nombreArchivo) {
	// Abrir el archivo de texto para escritura
	FILE* archivo;
	errno_t err = fopen_s(&archivo, nombreArchivo, "w");
	if (err != 0) {
		printf("No se pudo abrir el archivo %s\n", nombreArchivo);
		return;
	}
	for (NodoBoleto* nodo = iniBoletos; nodo != NULL; nodo = nodo->sig) {
		if (nodo->dato->numVuelo == numVuelo && nodo->dato->status == 1) {
			// Se encontró un boleto con el número de vuelo proporcionado y status 1
			NodoPasajero* pasajero = binarySearchNombrePasajero(iniPasajero, nodo->dato->nombreCompPasajero);
			if (pasajero != NULL) {
				// Escribir los datos del pasajero en el archivo			
				int edad = formatoEdad(pasajero->dato->nacimiento);
				char edadStr[4];
				sprintf_s(edadStr, sizeof(edadStr), "%d", edad);
				fprintf(archivo, "Nombre: %s, Edad: %s, Nacionalidad: %s\n",
					pasajero->dato->nombreComp, edadStr, pasajero->dato->nacionalidad);
			}
		}
	}
	// Cerrar el archivo
	fclose(archivo);
}
//Función de búsqueda en la lista por numero de vuelo
NodoVuelo* binarySearchNumVuelo(NodoVuelo* iniVuelos, int numVuelo) {
	NodoVuelo* inicio = iniVuelos;
	NodoVuelo* fin = NULL;
	while (inicio != fin) {
		NodoVuelo* mitad = inicio;
		for (int i = 0; i < numVuelo / 2; i++) {
			mitad = mitad->sig;
		}
		if (mitad->dato->num == numVuelo) {
			return mitad;
		}
		else if (mitad->dato->num < numVuelo) {
			inicio = mitad->sig;
		}
		else {
			fin = mitad;
		}
	}
	return NULL;
}
NodoVuelo* loopSearchNumVuelo(NodoVuelo* iniVuelos, int numVuelo) {
	for (NodoVuelo* nodo = iniVuelos; nodo != NULL; nodo = nodo->sig) {
		if (nodo->dato->num == numVuelo) {
			return nodo;
		}
	}
	return NULL;
}
void SetRegistroVuelos(HWND hwnd, int ListBoxID, int DTP1, int DTP2) {
	auxVuelo3 = iniVuelo; // Vuelos
	auxVuelo3->dato = iniVuelo->dato;
	SYSTEMTIME fecha1 = { 0 }; double fecha1D;
	SYSTEMTIME fecha2 = { 0 }; double fecha2D;
	DateTime_GetSystemtime(GetDlgItem(hwnd, DTP1), &fecha1);
	DateTime_GetSystemtime(GetDlgItem(hwnd, DTP2), &fecha2);
	SystemTimeToVariantTime(&fecha1, &fecha1D);
	SystemTimeToVariantTime(&fecha2, &fecha2D);

	if (iniVuelo != nullptr)
	{
		while (auxVuelo3->sig != nullptr)
		{
			if (auxVuelo3->dato->fecha >= fecha1D && auxVuelo3->dato->fecha <= fecha2D) {
				char cadenaFecha[100];
				SYSTEMTIME fecha = { 0 };
				VariantTimeToSystemTime(auxVuelo3->dato->fecha, &fecha);
				formatoFecha(&fecha, cadenaFecha);

				char vueloInfo[200];
				sprintf_s(vueloInfo, sizeof(vueloInfo), "Número de vuelo: %d, Fecha: %s, Origen: %s, Destino: %s",
					auxVuelo3->dato->num, cadenaFecha, auxVuelo3->dato->origen, auxVuelo3->dato->destino);

				SendDlgItemMessage(hwnd, ListBoxID, LB_ADDSTRING, (WPARAM)0, (LPARAM)vueloInfo);
			}
			auxVuelo3 = auxVuelo3->sig;
		}

		if (auxVuelo3->sig == nullptr && auxVuelo3->dato->fecha >= fecha1D && auxVuelo3->dato->fecha <= fecha2D)
		{
			char cadenaFecha[100];
			SYSTEMTIME fecha = { 0 };
			VariantTimeToSystemTime(auxVuelo3->dato->fecha, &fecha);
			formatoFecha(&fecha, cadenaFecha);

			char vueloInfo[200];
			sprintf_s(vueloInfo, sizeof(vueloInfo), "Número de vuelo: %d, Fecha: %s, Origen: %s, Destino: %s",
				auxVuelo3->dato->num, cadenaFecha, auxVuelo3->dato->origen, auxVuelo3->dato->destino);

			SendDlgItemMessage(hwnd, ListBoxID, LB_ADDSTRING, (WPARAM)0, (LPARAM)vueloInfo);
		}
		auxVuelo3 = auxVuelo3->sig;
	}
	else
	{
		MessageBox(NULL, "No hay vuelos registrados.", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
}

#pragma region QuickSort
//Generales
void swapData(NodoVuelo* a, NodoVuelo* b) {
	DatoVuelo* temp = a->dato;
	a->dato = b->dato;
	b->dato = temp;
}
NodoVuelo* lastNode(NodoVuelo* root) //Función para encontrar el último nodo
{
	while (root && root->sig)
		root = root->sig;
	return root;
}
//Específicas
NodoVuelo* partitionNum(NodoVuelo* l, NodoVuelo* h)
{
	//Se toma el último elemento como pivote
	// x = high (pivote)
	int x = h->dato->num;
	// i = low (recorrido)
	NodoVuelo* i = l->ant;

	//Acomoda los elmentos menores a la izquierda y mayores a la derecha
	for (NodoVuelo* j = l; j != h; j = j->sig)
	{
		if (j->dato->num <= x)
		{
			// Si i = NULL, se convierte en l, si no, se avanza al siguiente nodo
			i = (i == NULL) ? l : i->sig;
			//Se intercambian los numeros
			swapData(i, j);
		}
	}
	//Se hace el mismo proceso con el pivote
	i = (i == NULL) ? l : i->sig;
	swapData(i, h);
	return i;
}
void _quickSortNum(NodoVuelo* l, NodoVuelo* h) // Función recursiva
{
	if (h != NULL && l != h && l != h->sig)
	{
		NodoVuelo* p = partitionNum(l, h);
		_quickSortNum(l, p->ant);
		_quickSortNum(p->sig, h);
	}
}
void quickSortNum(NodoVuelo* head) // Función principal
{
	// Encuentra el último nodo
	NodoVuelo* h = lastNode(head);

	// Manda a llamar la función de QuickSort recursiva
	_quickSortNum(head, h);
}

NodoVuelo* partitionFechaOldToNew(NodoVuelo* l, NodoVuelo* h)
{
	double x = h->dato->fecha;
	NodoVuelo* i = l->ant;

	for (NodoVuelo* j = l; j != h; j = j->sig)
	{
		if (j->dato->fecha <= x)
		{
			i = (i == NULL) ? l : i->sig;
			swapData(i, j);
		}
	}
	i = (i == NULL) ? l : i->sig;
	swapData(i, h);
	return i;
}
void _quickSortFechaOldToNew(NodoVuelo* l, NodoVuelo* h)
{
	if (h != NULL && l != h && l != h->sig)
	{
		NodoVuelo* p = partitionFechaOldToNew(l, h);
		_quickSortFechaOldToNew(l, p->ant);
		_quickSortFechaOldToNew(p->sig, h);
	}
}
void quickSortFechaOldToNew(NodoVuelo* head)
{
	NodoVuelo* h = lastNode(head);
	_quickSortFechaOldToNew(head, h);
}

NodoVuelo* partitionFechaNewToOld(NodoVuelo* l, NodoVuelo* h)
{
	double x = h->dato->fecha;
	NodoVuelo* i = l->ant;

	for (NodoVuelo* j = l; j != h; j = j->sig)
	{
		if (j->dato->fecha >= x)
		{
			i = (i == NULL) ? l : i->sig;
			swapData(i, j);
		}
	}
	i = (i == NULL) ? l : i->sig;
	swapData(i, h);
	return i;
}
void _quickSortFechaNewToOld(NodoVuelo* l, NodoVuelo* h)
{
	if (h != NULL && l != h && l != h->sig)
	{
		NodoVuelo* p = partitionFechaNewToOld(l, h);
		_quickSortFechaNewToOld(l, p->ant);
		_quickSortFechaNewToOld(p->sig, h);
	}
}
void quickSortFechaNewToOld(NodoVuelo* head)
{
	NodoVuelo* h = lastNode(head);
	_quickSortFechaNewToOld(head, h);
}

/*
void printListNum(NodoVuelo* head)
{
	while (head)
	{
		std::cout << head->dato->num << "\n";
		head = head->sig;
	}
	std::cout << std::endl;
}
*/
#pragma endregion
#pragma endregion

//Listas de Boletos
#pragma region Funciones de Listas Boletos
void nuevoBoleto(NodoBoleto* nuevoB)
{
	if (iniBoleto == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniBoleto = new NodoBoleto;
		iniBoleto->dato = new DatoBoleto;

		strcpy_s(iniBoleto->dato->nombreCompPasajero, nuevoB->dato->nombreCompPasajero);
		iniBoleto->dato->num = nuevoB->dato->num;
		iniBoleto->dato->pase = nuevoB->dato->pase;
		iniBoleto->dato->numVuelo = nuevoB->dato->numVuelo;
		iniBoleto->dato->registroBoleto = nuevoB->dato->registroBoleto;
		iniBoleto->dato->registroPase = nuevoB->dato->registroPase;
		iniBoleto->dato->clase = nuevoB->dato->clase;
		iniBoleto->dato->status = nuevoB->dato->status;		
		strcpy_s(iniBoleto->dato->usuarioRegistro, nuevoB->dato->usuarioRegistro);

		iniBoleto->sig = nullptr;
		iniBoleto->ant = nullptr;

		auxBoleto2 = auxBoleto;
		auxBoleto3 = auxBoleto;
		iniBoleto = iniBoleto;
	}
	else
	{
		auxBoleto = iniBoleto;

		while (auxBoleto->sig != nullptr)
		{
			auxBoleto = auxBoleto->sig;
		}

		auxBoleto->sig = new NodoBoleto;
		auxBoleto->sig->sig = nullptr;
		auxBoleto->sig->ant = auxBoleto;
		auxBoleto = auxBoleto->sig;
		auxBoleto->dato = new DatoBoleto;

		strcpy_s(auxBoleto->dato->nombreCompPasajero, nuevoB->dato->nombreCompPasajero);
		auxBoleto->dato->num = nuevoB->dato->num;
		auxBoleto->dato->pase = nuevoB->dato->pase;
		auxBoleto->dato->numVuelo = nuevoB->dato->numVuelo;
		auxBoleto->dato->registroBoleto = nuevoB->dato->registroBoleto;
		auxBoleto->dato->registroPase = nuevoB->dato->registroPase;
		auxBoleto->dato->clase = nuevoB->dato->clase;
		auxBoleto->dato->status = nuevoB->dato->status;
		strcpy_s(auxBoleto->dato->usuarioRegistro, nuevoB->dato->usuarioRegistro);

		auxBoleto2 = auxBoleto;
		auxBoleto3 = auxBoleto;
		auxBoleto = iniBoleto;
	}
	MessageBox(NULL, "Se ha registrado el boleto con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
}
void eliminarBoleto(char pasajeroNom[60])
{
	NodoBoleto* start;
	auxBoleto = iniBoleto;

	if (auxBoleto == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxBoleto->sig != nullptr && strcmp(auxBoleto->dato->nombreCompPasajero, pasajeroNom) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxBoleto = auxBoleto->sig;
		}

		if (auxBoleto->sig == nullptr || strcmp(auxBoleto->dato->nombreCompPasajero, pasajeroNom) != 0)
		{
			MessageBox(0, "Medico no encontrado", "AVISO", MB_OK);
		}
		
		if (auxBoleto == iniBoleto)
		{
			if (iniBoleto->ant != nullptr && iniBoleto->sig != nullptr)
			{
				iniBoleto = iniBoleto->sig;
			}
			else if (iniBoleto->ant == nullptr)
			{
				iniBoleto = iniBoleto->sig;
			}
			else
			{
				iniBoleto = iniBoleto->ant;
			}
		}

		if (auxBoleto == iniBoleto)
		{	//El nodo es el primero 

			if (auxBoleto->sig == nullptr)
			{ //Si es el primero y unico nodo
				//delete auxMed;		//Eliminamos el primer nodo
				//inicio = nullptr;
				//auxMed = inicio;

				iniBoleto = nullptr;
				delete auxBoleto;

				auxBoleto = iniBoleto;
				auxBoleto2 = auxBoleto;
				auxBoleto3 = auxBoleto;
			}
			else
			{ //Si es el primero y hay mas nodos

				//inicio = auxMed->sig;	//Cambiamos el puntero 'inicio' al segundo nodo, que ahora es nuestro primer elemento
				//delete auxMed;			//Eliminamos el primer nodo		
				//auxMed = inicio;			//Para que auxMed no quede sin apuntar a nada, la apuntamos al inicio
				//auxMed->ant = nullptr;

				/*inicio = iniMed->sig;
				auxMed->sig->ant = nullptr;
				delete auxMed;
				auxMed = iniMed;*/

				start = iniBoleto->sig;
				auxBoleto->sig->ant = nullptr;
				delete auxBoleto;
				auxBoleto = start;
				auxBoleto->ant = nullptr;

				auxBoleto2 = auxBoleto;
				auxBoleto3 = auxBoleto;
				iniBoleto = auxBoleto;
			}

			MessageBox(0, "Medico eliminado", "AVISO", MB_OK);
		}
		else
		{

			if (auxBoleto->sig == nullptr)
			{ //Si el nodo es el último
				auxBoleto->ant->sig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete auxBoleto;

				auxBoleto = iniBoleto;
				auxBoleto2 = auxBoleto;
			}
			else
			{ //Si es cualquier nodo que no sea el inicio o el último
				auxBoleto->sig->ant = auxBoleto->ant;
				auxBoleto->ant->sig = auxBoleto->sig;
				delete auxBoleto;

				auxBoleto2 = auxBoleto;
				auxBoleto3 = auxBoleto;
				auxBoleto = iniBoleto; //Para que auxMed no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "Medico eliminado", "AVISO", MB_OK);

		}
	}

}
void escribirBoletos()
{
	auxBoleto = iniBoleto;

	ofstream escribir("Boletos.bin", ios::binary | ios::out | ios::trunc);

	if (!escribir.is_open())
	{
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (escribir.is_open())
	{
		while (auxBoleto != nullptr)
		{
			if (escribir.bad())
			{
				MessageBox(NULL, "Ocurrió un error durante la escritura", "Error", MB_OK | MB_ICONERROR);
				return;
			}

			escribir.write((char*)auxBoleto->dato, sizeof(DatoBoleto));
			auxBoleto = auxBoleto->sig;
		}

		escribir.close();
	}
}
void leerBoletos()
{
	auxBoleto = iniBoleto;

	ifstream leer("Boletos.bin", ios::binary);

	if (!leer.is_open())
	{
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (leer.is_open())
	{
		NodoBoleto* BolLeido = new NodoBoleto;
		BolLeido->dato = new DatoBoleto;

		while (!leer.read((char*)BolLeido->dato, sizeof(DatoBoleto)).eof())
		{
			while (auxBoleto != nullptr && auxBoleto->sig != nullptr)
			{
				auxBoleto = auxBoleto->sig;
			}
			if (auxBoleto == nullptr)
			{
				iniBoleto = BolLeido;
				iniBoleto->sig = nullptr;
				iniBoleto->ant = nullptr;
				auxBoleto = iniBoleto;
			}
			else
			{
				auxBoleto->sig = BolLeido;
				auxBoleto->sig->ant = auxBoleto;
				auxBoleto = auxBoleto->sig;
				auxBoleto->sig = nullptr;
			}

			BolLeido = new NodoBoleto;
			BolLeido->dato = new DatoBoleto;
		}
		leer.close();
		delete BolLeido;
	}
}
NodoBoleto* binarySearchNombreBoleto(NodoBoleto* head, const char* nombrePasajeroComp) {
	NodoBoleto* start = head;
	NodoBoleto* end = NULL;
	do {
		// Encuentra el punto medio
		NodoBoleto* slow = start;
		NodoBoleto* fast = start->sig;
		while (fast != end) {
			fast = fast->sig;
			if (fast != end) {
				slow = slow->sig;
				fast = fast->sig;
			}
		}
		// Comprueba si el nombre del pasajero en el punto medio coincide con el nombre proporcionado
		if (strcmp(slow->dato->nombreCompPasajero, nombrePasajeroComp) == 0) {
			return slow;
		}
		// Si el nombre del pasajero en el punto medio es mayor que el nombre proporcionado, busca en la primera mitad
		else if (strcmp(slow->dato->nombreCompPasajero, nombrePasajeroComp) > 0) {
			end = slow;
		}
		// Si el nombre del pasajero en el punto medio es menor que el nombre proporcionado, busca en la segunda mitad
		else {
			start = slow->sig;
		}
	} while (end == NULL || end != start);
	// No se encontró ningún boleto con el nombre del pasajero proporcionado
	return NULL;
}
NodoBoleto* loopSearchNombreBoleto(NodoBoleto* head, const char* nombrePasajeroComp) {
	NodoBoleto* aux = head;
	while (aux != NULL) {
		if (strcmp(aux->dato->nombreCompPasajero, nombrePasajeroComp) == 0) {
			return aux;
		}
		aux = aux->sig;
	}
	return NULL;

}
#pragma region QuickSort
//Generales
void swapData(NodoBoleto* a, NodoBoleto* b) {
	DatoBoleto* temp = a->dato;
	a->dato = b->dato;
	b->dato = temp;
}
NodoBoleto* lastNode(NodoBoleto* root) {
	while (root && root->sig)
		root = root->sig;
	return root;
}
//Específicas
NodoBoleto* partitionNumAsiento(NodoBoleto* l, NodoBoleto* h) {
	int x = h->dato->num;
	NodoBoleto* i = l->ant;

	for (NodoBoleto* j = l; j != h; j = j->sig) {
		if (j->dato->num <= x) {
			i = (i == NULL) ? l : i->sig;
			swapData(i, j);
		}
	}

	i = (i == NULL) ? l : i->sig;
	swapData(i, h);
	return i;
}
void _quickSortNumAsiento(NodoBoleto* l, NodoBoleto* h) {
	if (h != NULL && l != h && l != h->sig) {
		NodoBoleto* p = partitionNumAsiento(l, h);
		_quickSortNumAsiento(l, p->ant);
		_quickSortNumAsiento(p->sig, h);
	}
}
void quickSortNumAsiento(NodoBoleto* head) {
	NodoBoleto* h = lastNode(head);
	_quickSortNumAsiento(head, h);
}

NodoBoleto* partitionNumVuelo(NodoBoleto* l, NodoBoleto* h) {
	int x = h->dato->numVuelo;
	NodoBoleto* i = l->ant;

	for (NodoBoleto* j = l; j != h; j = j->sig) {
		if (j->dato->numVuelo <= x) {
			i = (i == NULL) ? l : i->sig;
			swapData(i, j);
		}
	}

	i = (i == NULL) ? l : i->sig;
	swapData(i, h);
	return i;
}
void _quickSortNumVuelo(NodoBoleto* l, NodoBoleto* h) {
	if (h != NULL && l != h && l != h->sig) {
		NodoBoleto* p = partitionNumVuelo(l, h);
		_quickSortNumVuelo(l, p->ant);
		_quickSortNumVuelo(p->sig, h);
	}
}
void quickSortNumVuelo(NodoBoleto* head) {
	NodoBoleto* h = lastNode(head);
	_quickSortNumVuelo(head, h);
}

NodoBoleto* partitionNomPasajero(NodoBoleto* l, NodoBoleto* h)
{
	char* x = h->dato->nombreCompPasajero;
	NodoBoleto* i = l->ant;

	for (NodoBoleto* j = l; j != h; j = j->sig)
	{
		if (_stricmp(j->dato->nombreCompPasajero, x) <= 0)
		{
			i = (i == NULL) ? l : i->sig;
			swapData(i, j);
		}
	}
	i = (i == NULL) ? l : i->sig;
	swapData(i, h);
	return i;
}
void _quickSortNomPasajero(NodoBoleto* l, NodoBoleto* h)
{
	if (h != NULL && l != h && l != h->sig)
	{
		NodoBoleto* p = partitionNomPasajero(l, h);
		_quickSortNomPasajero(l, p->ant);
		_quickSortNomPasajero(p->sig, h);
	}
}
void quickSortNomPasajero(NodoBoleto* head)
{
	NodoBoleto* h = lastNode(head);
	_quickSortNomPasajero(head, h);
}

void printBoletosDeVueloList(HWND hwnd, int List, NodoBoleto* iniBoletos, int numVuelo) {
	for (NodoBoleto* nodo = iniBoletos; nodo != NULL; nodo = nodo->sig) {
		if (nodo->dato->numVuelo == numVuelo) {
			// Se encontró un boleto con el número de vuelo proporcionado
			SendDlgItemMessage(hwnd, List, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxVuelo3->dato->origen);
		}
	}
}
void printList(NodoBoleto* head) {
	while (head) {
		std::cout << head->dato->num << "\n";
		head = head->sig;
	}
	std::cout << std::endl;
}
#pragma	endregion
#pragma endregion

//Listas de Pasajeros
#pragma region Funciones de Listas Pasajeros
void nuevoPasajero(NodoPasajero* nuevoPas)
{
	if (iniPasajero == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniPasajero = new NodoPasajero;
		iniPasajero->dato = new DatoPasajero;

		strcpy_s(iniPasajero->dato->nombre, nuevoPas->dato->nombre);
		strcpy_s(iniPasajero->dato->apellidoP, nuevoPas->dato->apellidoP);
		strcpy_s(iniPasajero->dato->apellidoM, nuevoPas->dato->apellidoM);

		// Concatenación
		strcpy_s(iniPasajero->dato->nombreComp, nuevoPas->dato->nombre);
		strcat_s(iniPasajero->dato->nombreComp, " ");
		strcat_s(iniPasajero->dato->nombreComp, iniPasajero->dato->apellidoP);
		strcat_s(iniPasajero->dato->nombreComp, " ");
		strcat_s(iniPasajero->dato->nombreComp, iniPasajero->dato->apellidoM);

		strcpy_s(iniPasajero->dato->nacionalidad, nuevoPas->dato->nacionalidad);

		iniPasajero->dato->genero = nuevoPas->dato->genero;
		iniPasajero->dato->nacimiento = nuevoPas->dato->nacimiento;
		iniPasajero->dato->registro = nuevoPas->dato->registro;
		
		// ::: CAMBIO DE TIPO ::: //
		//strcpy_s(iniPas->fecha, nuevoPas->fecha);
		//strcpy_s(iniPas->genero, nuevoPas->genero);

		// ::: PASADOS ::: //
		//iniPas->telefonoNumP = atoi(iniPas->nacionalidad);
		//strcpy_s(iniPas->ref, nuevoPas->ref);
		//strcpy_s(iniPas->edadChar, nuevoPas->edadChar);
		//iniPas->edadNum = atoi(iniPas->edadChar);
		//strcpy_s(iniPas->pMedicoP, nuevoPas->pMedicoP);

		strcpy_s(iniPasajero->dato->usuarioRegistro, nuevoPas->dato->usuarioRegistro);

		iniPasajero->sig = nullptr;
		iniPasajero->ant = nullptr;

		auxPasajero2 = auxPasajero;
		auxPasajero3 = auxPasajero;
		auxPasajero = iniPasajero;
	}
	else
	{
		auxPasajero = iniPasajero;

		while (auxPasajero->sig != nullptr)
		{
			auxPasajero = auxPasajero->sig;
		}

		auxPasajero->sig = new NodoPasajero;
		auxPasajero->sig->sig = nullptr;
		auxPasajero->sig->ant = auxPasajero;
		auxPasajero = auxPasajero->sig;
		auxPasajero->dato = new DatoPasajero;

		strcpy_s(auxPasajero->dato->nombre, nuevoPas->dato->nombre);
		strcpy_s(auxPasajero->dato->apellidoP, nuevoPas->dato->apellidoP);
		strcpy_s(auxPasajero->dato->apellidoM, nuevoPas->dato->apellidoM);

		// Concatenación
		strcpy_s(auxPasajero->dato->nombreComp, nuevoPas->dato->nombre);
		strcat_s(auxPasajero->dato->nombreComp, " ");
		strcat_s(auxPasajero->dato->nombreComp, auxPasajero->dato->apellidoP);
		strcat_s(auxPasajero->dato->nombreComp, " ");
		strcat_s(auxPasajero->dato->nombreComp, auxPasajero->dato->apellidoM);

		strcpy_s(auxPasajero->dato->nacionalidad, nuevoPas->dato->nacionalidad);

		auxPasajero->dato->genero = nuevoPas->dato->genero;
		auxPasajero->dato->nacimiento = nuevoPas->dato->nacimiento;
		auxPasajero->dato->registro = nuevoPas->dato->registro;

		strcpy_s(auxPasajero->dato->usuarioRegistro, nuevoPas->dato->usuarioRegistro);

		auxPasajero2 = auxPasajero;
		auxPasajero3 = auxPasajero;
		auxPasajero = iniPasajero;
	}

	MessageBox(NULL, "Se ha registrado al pasajero con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
}
void eliminarPasajero(char pasajeroNom[60])
{
	NodoPasajero* start;
	auxPasajero = iniPasajero;

	if (auxPasajero == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxPasajero->sig != nullptr && strcmp(auxPasajero->dato->nombreComp, pasajeroNom) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxPasajero = auxPasajero->sig;
		}

		if (/*auxPasajero->sig == nullptr || */strcmp(auxPasajero->dato->nombreComp, pasajeroNom) != 0)
		{
			MessageBox(0, "Pasajero no encontrado", "AVISO", MB_OK);
		}

		if (auxPasajero == iniPasajero)
		{	//El nodo es el primero 
			if (iniPasajero->ant != nullptr && iniPasajero->sig != nullptr)
			{
				iniPasajero = iniPasajero->sig;
			}
			else if (iniPasajero->ant == nullptr)
			{
				iniPasajero = iniPasajero->sig;
			}
			else
			{
				iniPasajero = iniPasajero->ant;
			}

			if (auxPasajero->sig == nullptr)
			{ //Si es el primero y unico nodo
				//delete auxPas;		//Eliminamos el primer nodo
				//inicio = nullptr;
				//auxPas = inicio;

				iniPasajero = nullptr;
				delete auxPasajero;

				auxPasajero = iniPasajero;
				auxPasajero2 = auxPasajero;
				auxPasajero3 = auxPasajero;
			}
			else
			{ //Si es el primero y hay mas nodos

				//inicio = auxPas->sig;	//Cambiamos el puntero 'inicio' al segundo nodo, que ahora es nuestro primer elemento
				//delete auxPas;			//Eliminamos el primer nodo		
				//auxPas = inicio;			//Para que auxPas no quede sin apuntar a nada, la apuntamos al inicio
				//auxPas->ant = nullptr;

				/*inicio = iniPas->sig;
				auxPas->sig->ant = nullptr;
				delete auxPas;
				auxPas = iniPas;*/

				start = iniPasajero->sig;
				auxPasajero->sig->ant = nullptr;
				delete auxPasajero;
				auxPasajero = start;
				auxPasajero->ant = nullptr;

				auxPasajero2 = auxPasajero;
				auxPasajero3 = auxPasajero;
				iniPasajero = auxPasajero;
			}

			MessageBox(0, "Pasajero eliminado.", "AVISO", MB_OK);
		}
		else
		{

			if (auxPasajero->sig == nullptr)
			{ //Si el nodo es el último
				auxPasajero->ant->sig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete auxPasajero;

				auxPasajero = iniPasajero;
				auxPasajero2 = auxPasajero;
			}
			else
			{ //Si es cualquier nodo que no sea el inicio o el último
				auxPasajero->sig->ant = auxPasajero->ant;
				auxPasajero->ant->sig = auxPasajero->sig;
				delete auxPasajero;

				auxPasajero2 = auxPasajero;
				auxPasajero3 = auxPasajero;
				auxPasajero = iniPasajero; //Para que auxPas no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "Pasajero eliminado.", "AVISO", MB_OK);

		}
	}

}
void escribirPasajeros()
{
	if (iniPasajero == nullptr) {
		MessageBox(NULL, "La lista de pasajeros está vacía", "Advertencia", MB_OK | MB_ICONWARNING);
		return;
	}

	auxPasajero = iniPasajero;

	ofstream escribir("Pasajeros.bin", ios::binary | ios::out | ios::trunc);

	if (!escribir.is_open())
	{
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	while (auxPasajero != nullptr)
	{
		if (escribir.bad())
		{
			MessageBox(NULL, "Ocurrió un error durante la escritura", "Error", MB_OK | MB_ICONERROR);
			return;
		}

		escribir.write((char*)auxPasajero->dato, sizeof(DatoPasajero));
		auxPasajero = auxPasajero->sig;
	}

	escribir.close();
}
void leerPasajeros()
{
	auxPasajero = iniPasajero;

	ifstream leer("Pasajeros.bin", ios::binary);

	if (!leer.is_open())
	{
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (leer.is_open())
	{
		NodoPasajero* pasLeido = new NodoPasajero;
		pasLeido->dato = new DatoPasajero;

		while (!leer.read((char*)pasLeido->dato, sizeof(DatoPasajero)).eof())
		{		
			while (auxPasajero != nullptr && auxPasajero->sig != nullptr)
			{
				auxPasajero = auxPasajero->sig;
			}
			if (auxPasajero == nullptr)
			{
				iniPasajero = pasLeido;
				iniPasajero->sig = nullptr;
				iniPasajero->ant = nullptr;
				auxPasajero = iniPasajero;
			}
			else
			{
				auxPasajero->sig = pasLeido;
				auxPasajero->sig->ant = auxPasajero;
				auxPasajero = auxPasajero->sig;
				auxPasajero->sig = nullptr;
			}

			pasLeido = new NodoPasajero;
			pasLeido->dato = new DatoPasajero;
		}

		leer.close();
		delete pasLeido;
	}
}
void reportePasajeros()
{
	ofstream escribir("Reporte de pasajeros.txt", ios::out | ios::trunc);
	if (!escribir.is_open()) {
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	auxPasajero = iniPasajero;
	if (escribir.is_open())
	{
		while (auxPasajero != nullptr)
		{
			if (escribir.bad()) {
				MessageBox(NULL, "Ocurrió un error durante la escritura", "Error", MB_OK | MB_ICONERROR);
				return;
			}
			escribir.write((char*)auxPasajero, sizeof(NodoPasajero));
			auxPasajero = auxPasajero->sig;
		}

		escribir.close();
	}
	/*auxPas = iniPas;

	if (auxPas == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		ofstream escribir;
		escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 5\\ProgAv\\Proyecto Final\\Segundo Avance\\Segundo Avance\\Segundo Avance\\Usuarios.bin", ios::out | ios::binary | ios::trunc);

		if (escribir.is_open())
		{
			while (auxPas != nullptr)
			{
				escribir.write((char*)auxPas, sizeof(usuario));
				auxPas = auxPas->sig;
			}

			escribir.close();
		}
	}*/
}
NodoPasajero* binarySearchNombrePasajero(NodoPasajero* head, const char* nombrePasajeroComp) {
	NodoPasajero* start = head;
	NodoPasajero* end = NULL;
	if (head == nullptr) {
		MessageBox(NULL, "La lista de pasajeros está vacía", "Advertencia", MB_OK | MB_ICONWARNING);
		return NULL;
	}
	// Comprueba si el nombre del pasajero en el primer nodo coincide con el nombre proporcionado
	if (strcmp(head->dato->nombreComp, nombrePasajeroComp) == 0) {
		return head;
	}

	do {
		// Encuentra el punto medio
		NodoPasajero* slow = start;
		NodoPasajero* fast = start->sig;
		while (fast != end) {
			fast = fast->sig;
			if (fast != end) {
				slow = slow->sig;
				fast = fast->sig;
			}
		}
		// Comprueba si el nombre del pasajero en el punto medio coincide con el nombre proporcionado
		if (strcmp(slow->dato->nombreComp, nombrePasajeroComp) == 0) {
			return slow;
		}
		// Si el nombre del pasajero en el punto medio es mayor que el nombre proporcionado, busca en la primera mitad
		else if (strcmp(slow->dato->nombreComp, nombrePasajeroComp) > 0) {
			end = slow;
		}
		// Si el nombre del pasajero en el punto medio es menor que el nombre proporcionado, busca en la segunda mitad
		else {
			if (slow->sig != NULL)
				start = slow->sig;
			else
				break;
		}
	} while (end == NULL || end != start || start != NULL);
	// No se encontró ningún pasajero con el nombre proporcionado
	return NULL;
}  // Revisar Star
NodoPasajero* loopSearchNombrePasajero(NodoPasajero* head, const char* nombrePasajeroComp) {
	NodoPasajero* current = head;
	while (current != nullptr) {
		if (strcmp(current->dato->nombreComp, nombrePasajeroComp) == 0) {
			return current;
		}
		current = current->sig;
	}
	return NULL;
}

#pragma region HeapSort
void swapData(NodoPasajero* a, NodoPasajero* b) {
	DatoPasajero* temp = a->dato;
	a->dato = b->dato;
	b->dato = temp;
}
void heapify(NodoPasajero* head, int n, NodoPasajero* NodoUsuario) {
	NodoPasajero* smallest = NodoUsuario;
	NodoPasajero* l = (NodoUsuario->sig != nullptr) ? NodoUsuario->sig : nullptr;
	NodoPasajero* r = (NodoUsuario->sig != nullptr && NodoUsuario->sig->sig != nullptr) ? NodoUsuario->sig->sig : nullptr;

	if (l != nullptr && l->dato->num < smallest->dato->num)
		smallest = l;

	if (r != nullptr && r->dato->num < smallest->dato->num)
		smallest = r;

	if (smallest != NodoUsuario) {
		swapData(NodoUsuario, smallest);
		heapify(head, n, smallest);
	}
}
void heapSort(NodoPasajero* head) {
	// Count number of nodes in the list
	int n = 0;
	NodoPasajero* current = head;
	while (current != nullptr) {
		n++;
		current = current->sig;
	}

	// Build heap (rearrange list)
	for (int i = n / 2 - 1; i >= 0; i--) {
		NodoPasajero* current = head;
		for (int j = 0; j < i; j++) {
			current = current->sig;
		}
		heapify(head, n, current);
	}

	// One by one extract an element from heap
	for (int i = n - 1; i >= 0; i--) {
		// Move current root to end
		NodoPasajero* current = head;
		for (int j = 0; j < i; j++) {
			current = current->sig;
		}
		swapData(head, current);

		// call max heapify on the reduced heap
		heapify(head, i, head);
	}
}
/*
void printList(NodoVuelo* head) {
	NodoVuelo* temp = head;
	while (temp != nullptr) {
		cout << temp->dato->num << " ";
		temp = temp->sig;
	}
	cout << "\n";
}
*/
#pragma enregion

#pragma endregion
#pragma endregion
#pragma endregion
