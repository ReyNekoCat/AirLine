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

struct DatoUsuario;
struct NodoUsuario;

struct DatoVuelo;
struct NodoVuelo;

struct DatoBoleto;
struct NodoBoleto;

struct DatoPasajero;
struct NodoPasajero;

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
	char nombrePasajero[30];
	char apellidoPPasajero[30];
	char apellidoMPasajero[30];
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
boleto* pivote, * iniBoleto, * auxBoleto, * auxBoleto2, * auxBoleto3 = nullptr;

struct pasajero
{
	DatoBoleto* dato;
	NodoBoleto* ant;
	NodoBoleto* sig;
};
NodoBoleto* pivote, * iniBoleto, * auxBoleto, * auxBoleto2, * auxBoleto3 = nullptr;

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
#pragma endregion

#pragma region Funciones de Listas Vuelos (Especialidades)
void nuevoVuelo(NodoVuelo* nueva);
void eliminarVuelo(char vuelo[30]);
void escribirVuelo();
void leerVuelos();
void reporteVuelos(); //Antes Boletos/Medicos
//QuickSort
void swapData(NodoVuelo*, NodoVuelo*);
NodoVuelo* lastNode(NodoVuelo*);
NodoVuelo* partitionNum(NodoVuelo*, NodoVuelo*);
void _quickSortNum(NodoVuelo*, NodoVuelo*);
void quickSortNum(NodoVuelo*);
//void printList(NodoVuelo*);

void preOrderList(NodoUsuario*, HWND);
void inOrderList(NodoUsuario*, HWND);
void reporteVuelos();
#pragma endregion

#pragma region Funciones de Listas Boletos (Medicos)
void nuevoBoleto(NodoBoleto* nuevoMed);
void eliminarBoleto(char medicoNom[60]);
void escribirBoletos();
void leerBoletos();

void swapData(NodoBoleto*, NodoBoleto*);
NodoBoleto* lastNode(NodoBoleto*);

NodoBoleto* partitionNumVuelo(NodoBoleto*, NodoBoleto*);
void _quickSortNumAsiento(NodoBoleto*, NodoBoleto*);
void quickSortNumAsiento(NodoBoleto*);
//void printListAsiento(NodoBoleto*);
#pragma endregion

#pragma region Funciones de Listas Pasajeros (Pacientes)
void nuevoPasajero(NodoPasajero* nuevoPas);
void eliminarPasajero(char NodoPasajero[60]);
void escribirPasajeros();
void leerPasajeros();
void reportePasajeros(); //No es necesario

void swapData(NodoPasajero* a, NodoPasajero* b);
void heapify(NodoPasajero* head, int n, NodoPasajero* NodoUsuario);
void heapSort(NodoPasajero* head);
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
				strcpy_s(ini2->Modelo, "Boeing 737");
				ini2->asientos = 166;
				ini2->asientosT = 150;
				ini2->asientosE = 16;
				ini2->asientosCT = 1500;
				ini2->asientosCE = 3000;
				ini2->asientosN = 17;
				ini2->asientosA = 124;
				ini2->asientosM = 25;
			}
			else
			{
				strcpy_s(ini2->Modelo, "Boeing 777");
				ini2->asientos = 276;
				ini2->asientosT = 152;
				ini2->asientosE = 124;
				ini2->asientosCT = 1800;
				ini2->asientosCE = 4200;
				ini2->asientosN = 28;
				ini2->asientosA = 207;
				ini2->asientosM = 41;
			}

			/*else if (i == 3)
			{
				strcpy_s(aux2->Modelo, "Brasil");
			}*/

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
				strcpy_s(ini3->Lugar, "Estados Unidos");
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
				strcpy_s(ini3->Lugar, "México - Queretaro");
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
					if (IDC_RADIO1 == BST_CHECKED)
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
				//sprintf_s(cadenaNacimiento, "%f", miUsuario->dato->nacimiento);
				SetDlgItemText(hwnd, IDC_EDIT6, cadenaNacimiento);
				
				//sprintf_s(cadenaNacimiento, "%f", miUsuario->dato->nacimiento);
				//SetDlgItemText(hwnd, IDC_EDIT7, cadenaNacimiento);
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
					if (IDC_RADIO1 == BST_CHECKED)
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
				SetDlgItemText(hwnd, IDC_EDIT2, "1");
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

				int num;
				char numC[10];
				num = auxVuelo3->num + 1;

				_itoa_s(num, numC, 10);
				SetDlgItemText(hwnd, IDC_EDIT2, numC);

				auxVuelo3 = iniVuelo;

			}

			break;
			
		}
		case IDC_BUTTON2: // Guardar
		{
			int numBuscar;
			char numBuscarC[10];

			GetDlgItemText(hwnd, IDC_EDIT2, numBuscarC, sizeof(numBuscarC));

			numBuscar = atoi(numBuscarC);

			auxVuelo2 = iniVuelo;

			while (auxVuelo2/*->sig*/ != nullptr && strcmp(espBuscar, auxVuelo2->dato->origen) != 0)
			{
				auxVuelo2 = auxVuelo2->sig;
			}

			if (auxVuelo2/*->sig*/ == nullptr || strcmp(espBuscar, auxVuelo2->dato->origen) != 0)
			{
				NodoVuelo* temp = new NodoVuelo;

				char numAsignadoC[10];
				GetDlgItemText(hwnd, IDC_EDIT2, numAsignadoC, sizeof(numAsignadoC));
				temp->num = atoi(numAsignadoC);

				GetDlgItemText(hwnd, IDC_EDIT3, temp->origen, sizeof(temp->origen));
				GetDlgItemText(hwnd, IDC_EDIT4, temp->destino, sizeof(temp->destino));
				GetDlgItemText(hwnd, IDC_EDIT17, temp->modelo, sizeof(temp->modelo));

				//Se obtiene la fecha
				HWND hDia = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
				SYSTEMTIME diaCumple = { 0 }; double dia;
				DateTime_GetSystemtime(hDia, &diaCumple);
				SystemTimeToVariantTime(&diaCumple, &dia);

				temp->status = 0;

				temp->fecha = dia;

				strcpy_s(temp->usuarioRegistro, miUsuario->nick);

				temp->registro = 0.0;

				GetDlgItemText(hwnd, IDC_EDIT2, temp->dato->origen, sizeof(temp->dato->origen));
				GetDlgItemText(hwnd, IDC_EDIT4, temp->dato->destino, sizeof(temp->dato->destino));
				//GetDlgItemText(hwnd, IDC_EDIT3, temp->claveChar, sizeof(temp->claveChar));
				strcpy_s(temp->dato->usuarioRegistro, miUsuario->dato->nick);
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
				SetDlgItemText(hwnd, IDC_EDIT23, "");

				EndDialog(hwnd, 0);

				HWND hDialog10 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG10), 0, cDialog10);

				ShowWindow(hDialog10, SW_SHOW);
				UpdateWindow(hDialog10);
			}
			else
			{
				MessageBox(NULL, "El vuelo ya esta registrado.", "AVISO", MB_OK | MB_ICONINFORMATION);
			}

			break;
		}
		case IDC_BUTTON3: // Editar
		{


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
		auxVuelo2 = iniVuelo;
		if (iniVuelo != nullptr)
		{
			while (auxVuelo2->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxVuelo2->dato->origen);
				auxVuelo2 = auxVuelo2->sig;
			}

			if (auxVuelo2->sig == nullptr/* || auxEsp2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxVuelo2->dato->origen);
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
				char vueloO[30];
				int indice2 = 0;
				indice2 = SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETTEXT, indice2, (LPARAM)vueloO);

				auxVuelo2 = iniVuelo;

				while (auxVuelo2->sig != nullptr && strcmp(auxVuelo2->origen, vueloO) != 0)
				{
					auxVuelo2 = auxVuelo2->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT2, auxVuelo2->num);
				SetDlgItemText(hwnd, IDC_EDIT3, auxVuelo2->origen);
				SetDlgItemText(hwnd, IDC_EDIT4, auxVuelo2->destino);
				SetDlgItemText(hwnd, IDC_EDIT6, auxVuelo2->fecha);
				SetDlgItemText(hwnd, IDC_EDIT7, auxVuelo2->status);

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
				MessageBox(NULL, "No se ha seleccionado una especialidad, seleccione una de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
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
					

					auxVuelo2 = nullptr;

					break;
				}

				case IDNO:
				{
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");

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
		case IDC_BUTTON3: // Confirmar
		{
			if (auxVuelo2 == nullptr)
			{
				MessageBox(NULL, "No se ha seleccionado un vuelo, seleccione uno de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
				int opc = MessageBox(hwnd, "¿Seguro que desea confirmar este vuelo?", "AVISO", MB_YESNO | MB_ICONQUESTION);

				switch (opc)
				{
				case IDYES:
				{
					
					auxVuelo2 = nullptr;
					auxVuelo = nullptr;	
					
					break;
				}
					


				case IDNO:
				{
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");

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

		auxVuelo3 = iniVuelo; // Vuelos
		if (iniVuelo != nullptr)
		{
			while (auxVuelo3->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxVuelo3->dato->origen);
				auxVuelo3 = auxVuelo3->sig;
			}

			if (auxVuelo3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxVuelo3->dato->origen);
				auxVuelo3 = auxVuelo3->sig;
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
		case IDC_BUTTON1: // Nombre
		{
			

			break;
		}
		case IDC_BUTTON2: // Asiento
		{
			

			break;
		}
		case IDC_BUTTON3: // Seleccionar
		{
			if (auxVuelo3 == nullptr)
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

			auxBoleto3 = iniBoleto; // Boletos
			if (iniBoleto != nullptr)
			{
				while (auxBoleto3->sig != nullptr)
				{
					SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto3->nombreCompPasajero/*nombreCompM*/);
					auxBoleto3 = auxBoleto3->sig;
				}
				if (auxBoleto3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
				{
					SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto3->nombreCompPasajero/*nombreCompM*/);
					auxBoleto3 = auxBoleto3->sig;
				}
			}

			auxVuelo3 = iniVuelo; // Vuelos
			if (iniVuelo != nullptr)
			{
				while (auxVuelo3->sig != nullptr)
				{
					SendDlgItemMessage(hwnd, IDC_LIST10, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxVuelo3->dato->origen);
					auxVuelo3 = auxVuelo3->sig;
				}

				if (auxVuelo3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
				{
					SendDlgItemMessage(hwnd, IDC_LIST10, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxVuelo3->dato->origen);
					auxVuelo3 = auxVuelo3->sig;
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
			case IDC_LIST3: // Boletos
			{
				switch (HIWORD(wParam))
				{
				case LBN_DBLCLK: //Al dar doble clic en el ListBox 
				{
					char num[60] = { 0 };
					int indice = 0;
					indice = SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
					SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETTEXT, indice, (LPARAM)num);

					auxBoleto3 = iniBoleto;

					while (auxBoleto3->sig != nullptr && strcmp(auxBoleto3->nombreCompPasajero, num) != 0)
					{
						auxBoleto3 = auxBoleto3->sig;

					}

					SetDlgItemText(hwnd, IDC_EDIT2, auxBoleto3->nombrePasajero);
					SetDlgItemText(hwnd, IDC_EDIT3, auxBoleto3->apellidoPPasajero);
					SetDlgItemText(hwnd, IDC_EDIT4, auxBoleto3->apellidoMPasajero);

					//SetDlgItemText(hwnd, IDC_EDIT5, auxBoleto3->cedulaChar);
					SetDlgItemText(hwnd, IDC_EDIT18, auxBoleto3->vuelo);

					//SetDlgItemText(hwnd, IDC_EDIT8, auxBoleto3->telefonoChar);

					//SetDlgItemText(hwnd, IDC_EDIT17, auxBoleto3->numConsultorioChar);
					//SetDlgItemText(hwnd, IDC_EDIT15, auxBoleto3->hoararioChar);
					//SetDlgItemText(hwnd, IDC_EDIT16, auxBoleto3->diasChar);

					//strcpy_s(zFile, auxBoleto3->foto); //Inicializar zfile con la dirección de memoria del puntero foto

					HBITMAP bmp; //1
					//bmp = (HBITMAP)LoadImage(NULL, auxBoleto3->foto, IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE); //2
					//SendDlgItemMessage(hwnd, IDC_BMP2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 

					break;
				}
				default:
				{
					break;
				}
				}

				break;
			}
			case IDC_BUTTON1: // Numero
			{
				

				break;
			}
			case IDC_BUTTON2: // Asientos
			{
				

				break;
			}
			case IDC_BUTTON3: // Nombres
			{
				

				break;
			}
			case IDC_BUTTON4: // Reporte
			{
				if (iniPasajero == nullptr)
				{
					MessageBox(NULL, "No hay pacientes registrados.", "AVISO", MB_OK | MB_ICONERROR);
				}
				else
				{
					reportePasajeros();
					MessageBox(NULL, "Reporte fue guardado en C:-Users-hp-Documents-UANL-Universidad 7-ED-Proyecto_Clinica-Proyecto_Clinica.", "AVISO", MB_OK | MB_ICONEXCLAMATION);
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


// Registro Pasajeros
BOOL CALLBACK cDialog10(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		if (miUsuario != nullptr)
		{
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreComp);
		}
		if (miUsuario->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
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

			while (auxPasajero2/*->sig*/ != nullptr && strcmp(pasajeroBuscar, auxPasajero2->nombreComp) != 0)
			{
				auxPasajero2 = auxPasajero2->sig;
			}

			if (auxPasajero2/*->sig*/ == nullptr || strcmp(pasajeroBuscar, auxPasajero2->nombreComp) != 0)
			{
				pasajero* temp = new pasajero;

				GetDlgItemText(hwnd, IDC_EDIT2, temp->nombre, sizeof(temp->nombre));
				GetDlgItemText(hwnd, IDC_EDIT3, temp->apellidoP, sizeof(temp->apellidoP));
				GetDlgItemText(hwnd, IDC_EDIT4, temp->apellidoM, sizeof(temp->apellidoM));
				GetDlgItemText(hwnd, IDC_EDIT6, temp->nacionalidad, sizeof(temp->nacionalidad));

				//Genero
				if (IDC_RADIO1 == BST_CHECKED)
				{
					temp->genero = 1;
				}
				else
				{
					temp->genero = 0;
				}

				//Se obtiene la fecha de nacimiento
				HWND hDia = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
				SYSTEMTIME diaCumple = { 0 }; double dia;
				DateTime_GetSystemtime(hDia, &diaCumple);
				SystemTimeToVariantTime(&diaCumple, &dia);

				temp->nacimiento = dia;

				strcpy_s(temp->usuarioRegistro, miUsuario->nick);

				temp->registro = 0.0;

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
					char pasajeroBuscar[30];
					GetDlgItemText(hwnd, IDC_EDIT2, pasajeroBuscar, sizeof(pasajeroBuscar));
					
					auxPasajero3 = iniPasajero;
					while (auxPasajero3->sig != nullptr && strcmp(pasajeroBuscar, auxPasajero3->nombreComp) != 0)
					{
						auxPasajero3 = auxPasajero3->sig;
					}

					if (strcmp(pasajeroBuscar, auxPasajero3->nombreComp) == 0)
					{
						SetDlgItemText(hwnd, IDC_EDIT3, auxPasajero3->nombre);
						SetDlgItemText(hwnd, IDC_EDIT4, auxPasajero3->apellidoP);
						SetDlgItemText(hwnd, IDC_EDIT5, auxPasajero3->apellidoM);

						//Genero
						if (auxPasajero3->genero == 1)
						{
							SetDlgItemText(hwnd, IDC_EDIT9, "Masculino");
						}
						else
						{
							SetDlgItemText(hwnd, IDC_EDIT9, "Femenino");
						}

						//Edad/Nacimiento
						char cadenaNacimiento[100];
						sprintf_s(cadenaNacimiento, "%f", auxPasajero3->nacimiento);
						SetDlgItemText(hwnd, IDC_EDIT10, cadenaNacimiento);
						sprintf_s(cadenaNacimiento, "%f", auxPasajero3->nacimiento);
						SetDlgItemText(hwnd, IDC_EDIT11, cadenaNacimiento);

						SetDlgItemText(hwnd, IDC_EDIT16, auxPasajero3->nacionalidad);
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
					GetDlgItemText(hwnd, IDC_EDIT3, auxPasajero3->nombre, sizeof(auxPasajero3->nombre));
					GetDlgItemText(hwnd, IDC_EDIT4, auxPasajero3->apellidoP, sizeof(auxPasajero3->apellidoP));
					GetDlgItemText(hwnd, IDC_EDIT5, auxPasajero3->apellidoM, sizeof(auxPasajero3->apellidoM));
					GetDlgItemText(hwnd, IDC_EDIT16, auxPasajero3->nacionalidad, sizeof(auxPasajero3->nacionalidad));

					// Concatenación
					strcpy_s(auxPasajero3->nombreComp, auxPasajero3->nombre);
					strcat_s(auxPasajero3->nombreComp, " ");
					strcat_s(auxPasajero3->nombreComp, auxPasajero3->apellidoP);
					strcat_s(auxPasajero3->nombreComp, " ");
					strcat_s(auxPasajero3->nombreComp, auxPasajero3->apellidoM);

					//Genero
					if (IDC_RADIO1 == BST_CHECKED)
					{
						auxPasajero3->genero = 1;
					}
					else
					{
						auxPasajero3->genero = 0;
					}

					//Se obtiene la fecha de nacimiento
					HWND hDia = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
					SYSTEMTIME diaCumple = { 0 }; double dia;
					DateTime_GetSystemtime(hDia, &diaCumple);
					SystemTimeToVariantTime(&diaCumple, &dia);

					auxPasajero3->nacimiento = dia;

					strcpy_s(auxPasajero3->usuarioRegistro, miUsuario->nick);

					auxPasajero3->registro = 0.0;

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
						while (auxPasajero3->sig != nullptr && strcmp(pasajero, auxPasajero3->nombreComp) != 0)
						{
							auxPasajero3 = auxPasajero3->sig;
						}
						if (/*auxPasajero3->sig == nullptr && */strcmp(pasajero, auxPasajero3->nombreComp) != 0)
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
							eliminarPasajero(auxPasajero3->nombreComp);

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
			if (miUsuario != nullptr)
				SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nombreComp);

			if (miUsuario->dato->foto != nullptr)
			{
				strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
			}

			auxPasajero3 = iniPasajero;
			if (iniPasajero != nullptr)
			{
				while (auxPasajero3->sig != nullptr)
				{
					SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxPasajero3->nombreComp/*nombreCompM*/);
					auxPasajero3 = auxPasajero3->sig;
				}
				if (auxBoleto3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
				{
					SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxPasajero3->nombreComp/*nombreCompM*/);
					auxPasajero3 = auxPasajero3->sig;
				}
			}

			break;
		}
		case WM_COMMAND:
		{
			long opcion = LOWORD(wParam);
			cMenu(hwnd, opcion);

			switch (LOWORD(wParam))
			{
				case IDC_BUTTON1:
				{
					

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
		case IDC_BUTTON3: //
		{


			break;
		}
		case IDC_BUTTON4: //
		{


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
		case IDC_BUTTON6: // Buscar
		{


			break;
		}
		case IDC_BUTTON3: // Generar hora
		{


			break;
		}
		case IDC_BUTTON4: // Editar
		{


			break;
		}
		case IDC_BUTTON5: // Elimiar
		{


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
	//case ---: // Lista Medicos
	//{
	//	EndDialog(hwnd, 0);
	//	HWND hDialog8 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG8), 0, cDialog8);
	//	ShowWindow(hDialog8, SW_SHOW);
	//	UpdateWindow(hDialog8); //Opcional
	//	break;
	//}
	//case ---: // Reporte Medicos
	//{
	//	EndDialog(hwnd, 0);
	//	HWND hDialog9 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG9), 0, cDialog9);
	//	ShowWindow(hDialog9, SW_SHOW);
	//	UpdateWindow(hDialog9); //Opcional
	//	break;
	//}
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
	double now = 0;
	GetSystemTime(&SysNow);
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
		DatoUsuario* data = new DatoUsuario;
		iniUsuario->dato = data;

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

		DatoUsuario* data = new DatoUsuario;
		auxUsuario->dato = data;

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
	DatoUsuario* dato;

	while (archivo) {
		dato = new DatoUsuario;
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

//Listas de Vuelos (Especialidades)
#pragma region Funciones de Listas Vuelos (Especialidades)
void nuevoVuelo(NodoVuelo* nueva)
//Listas de Vuelos
#pragma region Funciones de Listas Vuelos
void nuevoVuelo(Vuelo* nuevoV)
{
	if (iniVuelo == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniVuelo = new NodoVuelo;

		strcpy_s(iniVuelo->dato->origen, nueva->dato->origen);
		strcpy_s(iniVuelo->dato->destino, nueva->dato->destino);
		strcpy_s(iniVuelo->origen, nuevoV->origen);
		strcpy_s(iniVuelo->destino, nuevoV->destino);
		strcpy_s(iniVuelo->modelo, nuevoV->modelo);

		iniVuelo->num = nuevoV->num;
		iniVuelo->fecha = nuevoV->fecha;
		iniVuelo->status = nuevoV->status;
		iniVuelo->registro = nuevoV->registro;

		strcpy_s(iniVuelo->usuarioRegistro, nuevoV->usuarioRegistro);

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

		strcpy_s(auxVuelo->origen, nuevoV->origen);
		strcpy_s(auxVuelo->destino, nuevoV->destino);
		strcpy_s(auxVuelo->modelo, nuevoV->modelo);

		auxVuelo->num = nuevoV->num;
		auxVuelo->fecha = nuevoV->fecha;
		auxVuelo->status = nuevoV->status;
		auxVuelo->registro = nuevoV->registro;

		strcpy_s(auxVuelo->usuarioRegistro, nuevoV->usuarioRegistro);

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
void reporteVuelos()
{
	ofstream escribir("Reporte de vuelos.txt", ios::out | ios::trunc);
	if (!escribir.is_open()) {
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	auxBoleto = iniBoleto;
	if (escribir.is_open())
	{
		while (auxBoleto != nullptr)
		{
			if (escribir.bad()) {
				MessageBox(NULL, "Ocurrió un error durante la escritura", "Error", MB_OK | MB_ICONERROR);
				return;
			}
			escribir.write((char*)auxBoleto, sizeof(NodoBoleto));
			auxBoleto = auxBoleto->sig;
		}
		escribir.close();
	}
	/*auxMed = iniMed;

	if (auxMed == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		ofstream escribir;
		escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 5\\ProgAv\\Proyecto Final\\Segundo Avance\\Segundo Avance\\Segundo Avance\\Usuarios.bin", ios::out | ios::binary | ios::trunc);

		if (escribir.is_open())
		{
			while (auxMed != nullptr)
			{
				escribir.write((char*)auxMed, sizeof(usuario));
				auxMed = auxMed->sig;
			}

			escribir.close();
		}
	}*/
}
void printVuelosEnRango(HWND hwnd, int List, NodoVuelo* iniVuelos, DATE inicioDate, DATE finDate) {
	for (NodoVuelo* nodo = iniVuelos; nodo != NULL; nodo = nodo->sig) {
		// Comprobar si la fecha del vuelo está dentro del rango
		if (nodo->dato->fecha >= inicioDate && nodo->dato->fecha <= finDate) {
			// Convertir el número de vuelo a una cadena
			char numVueloStr[10];
			sprintf(numVueloStr, "%d", nodo->dato->num);

			// Agregar el número de vuelo al ListBox
			SendDlgItemMessage(hwnd, List, LB_ADDSTRING, 0, (LPARAM)numVueloStr);
		}
	}
}
void generarManifiestoPasajeros(NodoBoleto* iniBoletos, int numVuelo, const char* nombreArchivo) {
	// Abrir el archivo de texto para escritura
	FILE* archivo = fopen(nombreArchivo, "w");
	if (archivo == NULL) {
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
				sprintf(edadStr, "%d", edad);
				fprintf(archivo, "Nombre: %s, Edad: %s, Nacionalidad: %s\n",
					pasajero->dato->nombreComp, edadStr, pasajero->dato->nacionalidad);
			}
		}
	}
	// Cerrar el archivo
	fclose(archivo);
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

//Listas de Boletos (Medicos)
#pragma region Funciones de Listas Boletos (Medicos)
void nuevoBoleto(NodoBoleto* nuevoBoleto)
{
	if (pivote == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		pivote = new NodoBoleto;

		strcpy_s(pivote->dato->nombrePasajero, nuevoBoleto->dato->nombrePasajero);
		strcpy_s(pivote->dato->apellidoPPasajero, nuevoBoleto->dato->apellidoPPasajero);
		strcpy_s(pivote->dato->apellidoMPasajero, nuevoBoleto->dato->apellidoMPasajero);

		// Concatenación
		strcpy_s(pivote->dato->nombreCompPasajero, nuevoBoleto->dato->nombrePasajero);
		strcat_s(pivote->dato->nombreCompPasajero, " ");
		strcat_s(pivote->dato->nombreCompPasajero, pivote->dato->apellidoPPasajero);
		strcat_s(pivote->dato->nombreCompPasajero, " ");
		strcat_s(pivote->dato->nombreCompPasajero, pivote->dato->apellidoMPasajero);

		//strcpy_s(pivote->cedulaChar, nuevoMed->cedulaChar);
		//pivote->cedulaNum = atoi(pivote->cedulaChar);
		//strcpy_s(pivote->numConsultorioChar, nuevoMed->numConsultorioChar);
		//pivote->clase = atoi(pivote->numConsultorioChar);
		//strcpy_s(pivote->telefonoChar, nuevoMed->telefonoChar);
		//pivote->estado = atoi(pivote->telefonoChar);

		//strcpy_s(pivote->hoararioChar, nuevoMed->hoararioChar);
		pivote->dato->pase = nuevoBoleto->dato->pase;
		//strcpy_s(pivote->diasChar, nuevoMed->diasChar);
		//pivote->diasNum = nuevoMed->diasNum;

		pivote->dato->numVuelo = nuevoBoleto->dato->numVuelo;

		//strcpy_s(pivote->foto, nuevoMed->foto);

		strcpy_s(pivote->dato->usuarioRegistro, nuevoBoleto->dato->usuarioRegistro);

		pivote->sig = nullptr;
		pivote->ant = nullptr;

		auxBoleto = pivote;
		auxBoleto2 = auxBoleto;
		auxBoleto3 = auxBoleto;
		iniBoleto = pivote;
	}
	else
	{
		// ::: ANTERIOR ::: //
		/*
		 		auxMed = pivote;	
		nuevoMed->cedulaNum = atoi(nuevoMed->cedulaChar);

		//if (nuevoMed->cedulaNum == auxMed->cedulaNum)
		//{
		//	auxBoleto2 = auxMed->ant;
		//	auxMed->ant = new medico;
		//	auxMed->ant->ant = auxBoleto2;
		//	auxMed->ant->sig = auxMed;
		//	auxMed = auxMed->ant;
		//	auxBoleto2->sig = auxMed;
		//}
		//else 
		if (nuevoMed->cedulaNum > auxMed->cedulaNum)
		{
			while (auxMed->sig != nullptr && nuevoMed->cedulaNum > auxMed->cedulaNum)
			{
				auxMed = auxMed->sig;
			}

			if (auxMed->ant != nullptr && auxMed->sig != nullptr)
			{

				//if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				//{
				//	auxBoleto2 = auxMed->ant;
				//	auxMed->ant = new medico;
				//	auxMed->ant->ant = auxBoleto2;
				//	auxMed->ant->sig = auxMed;
				//	auxMed = auxMed->ant;
				//	auxBoleto2->sig = auxMed;
				//}
				//else
				if (nuevoMed->cedulaNum > auxMed->cedulaNum)
				{
					auxBoleto2 = auxMed->sig;
					auxMed->sig = new boleto;
					auxMed->sig->sig = auxBoleto2;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
					auxBoleto2->ant = auxMed;
				}
				else
				{
					auxBoleto2 = auxMed->ant;
					auxMed->ant = new boleto;
					auxMed->ant->ant = auxBoleto2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxBoleto2->sig = auxMed;
				}
			}
			else
			{
				//if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				//{
				//	auxBoleto2 = auxMed->ant;
				//	auxMed->ant = new medico;
				//	auxMed->ant->ant = auxBoleto2;
				//	auxMed->ant->sig = auxMed;
				//	auxMed = auxMed->ant;
				//	auxBoleto2->sig = auxMed;
				//}
				//else
				if (nuevoMed->cedulaNum > auxMed->cedulaNum)
				{
					auxMed->sig = new boleto;
					auxMed->sig->sig = nullptr;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
				}
				else
				{
					auxBoleto2 = auxMed->ant;
					auxMed->ant = new boleto;
					auxMed->ant->ant = auxBoleto2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxBoleto2->sig = auxMed;
				}
			}
		}
		else
		{
			while (auxMed->ant != nullptr && nuevoMed->cedulaNum < auxMed->cedulaNum)
			{
				auxMed = auxMed->ant;
			}

			if (auxMed->ant != nullptr && auxMed->sig != nullptr)
			{

				//if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				//{
				//	auxBoleto2 = auxMed->ant;
				//	auxMed->ant = new medico;
				//	auxMed->ant->ant = auxBoleto2;
				//	auxMed->ant->sig = auxMed;
				//	auxMed = auxMed->ant;
				//	auxBoleto2->sig = auxMed;
				//}
				//else 
				if (nuevoMed->cedulaNum < auxMed->cedulaNum)
				{
					auxBoleto2 = auxMed->ant;
					auxMed->ant = new boleto;
					auxMed->ant->ant = auxBoleto2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxBoleto2->sig = auxMed;
				}
				else
				{
					auxBoleto2 = auxMed->sig;
					auxMed->sig = new boleto;
					auxMed->sig->sig = auxBoleto2;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
					auxBoleto2->ant = auxMed;
				}
			}
			else
			{
				//if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				//{
				//	auxBoleto2 = auxMed->ant;
				//	auxMed->ant = new medico;
				//	auxMed->ant->ant = auxBoleto2;
				//	auxMed->ant->sig = auxMed;
				//	auxMed = auxMed->ant;
				//	auxBoleto2->sig = auxMed;
				//}
				//else 
				if (nuevoMed->cedulaNum < auxMed->cedulaNum)
				{
					auxMed->ant = new boleto;
					auxMed->ant->ant = nullptr;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
				}
				else
				{
					auxBoleto2 = auxMed->sig;
					auxMed->sig = new boleto;
					auxMed->sig->sig = auxBoleto2;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
					auxBoleto2->ant = auxMed;
				}
			}

		}
		*/


		strcpy_s(auxBoleto->dato->nombrePasajero, nuevoBoleto->dato->nombrePasajero);
		strcpy_s(auxBoleto->dato->apellidoPPasajero, nuevoBoleto->dato->apellidoPPasajero);
		strcpy_s(auxBoleto->dato->apellidoMPasajero, nuevoBoleto->dato->apellidoMPasajero);

		// Concatenación
		strcpy_s(auxBoleto->dato->nombreCompPasajero, nuevoBoleto->dato->nombrePasajero);
		strcat_s(auxBoleto->dato->nombreCompPasajero, " ");
		strcat_s(auxBoleto->dato->nombreCompPasajero, auxBoleto->dato->apellidoPPasajero);
		strcat_s(auxBoleto->dato->nombreCompPasajero, " ");
		strcat_s(auxBoleto->dato->nombreCompPasajero, auxBoleto->dato->apellidoMPasajero);

		//strcpy_s(auxMed->cedulaChar, nuevoMed->cedulaChar);
		//auxMed->cedulaNum = atoi(auxMed->cedulaChar);
		//strcpy_s(auxMed->numConsultorioChar, nuevoMed->numConsultorioChar);
		//auxMed->clase = atoi(auxMed->numConsultorioChar);
		//strcpy_s(auxMed->telefonoChar, nuevoMed->telefonoChar);
		//auxMed->estado = atoi(auxMed->telefonoChar);

		//strcpy_s(auxMed->hoararioChar, nuevoMed->hoararioChar);
		auxBoleto->dato->pase = nuevoBoleto->dato->pase;
		//strcpy_s(auxMed->diasChar, nuevoMed->diasChar);
		//auxMed->diasNum = nuevoMed->diasNum;

		auxBoleto->dato->numVuelo = nuevoBoleto->dato->numVuelo;

		//strcpy_s(auxMed->foto, nuevoMed->foto);

		strcpy_s(auxBoleto->dato->usuarioRegistro, nuevoBoleto->dato->usuarioRegistro);

		while (auxBoleto->ant != nullptr)
		{
			auxBoleto = auxBoleto->ant;
		}

		iniBoleto = auxBoleto;

		auxBoleto = pivote;
		auxBoleto2 = auxBoleto;
		auxBoleto3 = auxBoleto;
	}

	MessageBox(NULL, "Se ha registrado al medico con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
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
		
		if (auxBoleto == pivote)
		{
			if (pivote->ant != nullptr && pivote->sig != nullptr)
			{
				pivote = pivote->sig;
			}
			else if (pivote->ant == nullptr)
			{
				pivote = pivote->sig;
			}
			else
			{
				pivote = pivote->ant;
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
		NodoBoleto* medLeido = new NodoBoleto;

		while (!leer.read((char*)medLeido, sizeof(NodoBoleto)).eof())
		{
			while (auxBoleto != nullptr && auxBoleto->sig != nullptr)
			{
				auxBoleto = auxBoleto->sig;
			}
			if (auxBoleto == nullptr)
			{
				iniBoleto = medLeido;
				iniBoleto->sig = nullptr;
				iniBoleto->ant = nullptr;
				auxBoleto = iniBoleto;
			}
			else
			{
				auxBoleto->sig = medLeido;
				auxBoleto->sig->ant = auxBoleto;
				auxBoleto = auxBoleto->sig;
				auxBoleto->sig = nullptr;
			}

			medLeido = new NodoBoleto;
		}

		leer.close();
		delete medLeido;
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

//Listas de Pasajeros (Pacientes)
#pragma region Funciones de Listas Pasajeros (Pacientes)
void nuevoPasajero(NodoPasajero* nuevoPas)
{
	if (iniPasajero == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniPasajero = new NodoPasajero;

		strcpy_s(iniPasajero->dato->nombre, nuevoPas->dato->nombre);
		strcpy_s(iniPasajero->dato->apellidoP, nuevoPas->dato->apellidoP);
		strcpy_s(iniPasajero->dato->apellidoM, nuevoPas->dato->apellidoM);

		// Concatenación
		strcpy_s(iniPasajero->dato->nombreComp, nuevoPas->dato->nombre);
		strcat_s(iniPasajero->dato->nombreComp, " ");
		strcat_s(iniPasajero->dato->nombreComp, iniPasajero->dato->apellidoP);
		strcat_s(iniPasajero->dato->nombreComp, " ");
		strcat_s(iniPasajero->dato->nombreComp, iniPasajero->dato->apellidoM);

		strcpy_s(iniPasajero->nacionalidad, nuevoPas->nacionalidad);

		iniPasajero->genero = nuevoPas->genero;
		iniPasajero->nacimiento = nuevoPas->nacimiento;
		iniPasajero->registro = nuevoPas->registro;
		
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

		auxPasajero->sig = new pasajero;
		auxPasajero->sig->sig = nullptr;
		auxPasajero->sig->ant = auxPasajero;
		auxPasajero = auxPasajero->sig;

		strcpy_s(auxPasajero->dato->nombre, nuevoPas->dato->nombre);
		strcpy_s(auxPasajero->dato->apellidoP, nuevoPas->dato->apellidoP);
		strcpy_s(auxPasajero->dato->apellidoM, nuevoPas->dato->apellidoM);

		// Concatenación
		strcpy_s(auxPasajero->nombreComp, nuevoPas->nombre);
		strcat_s(auxPasajero->nombreComp, " ");
		strcat_s(auxPasajero->nombreComp, auxPasajero->apellidoP);
		strcat_s(auxPasajero->nombreComp, " ");
		strcat_s(auxPasajero->nombreComp, auxPasajero->apellidoM);

		strcpy_s(auxPasajero->nacionalidad, nuevoPas->nacionalidad);

		auxPasajero->genero = nuevoPas->genero;
		auxPasajero->nacimiento = nuevoPas->nacimiento;
		auxPasajero->registro = nuevoPas->registro;

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
		while (auxPasajero->sig != nullptr && strcmp(auxPasajero->nombreComp, pasajeroNom) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxPasajero = auxPasajero->sig;
		}

		if (/*auxPasajero->sig == nullptr || */strcmp(auxPasajero->nombreComp, pasajeroNom) != 0)
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

		while (!leer.read((char*)pasLeido, sizeof(NodoPasajero)).eof())
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
			start = slow->sig;
		}
	} while (end == NULL || end != start);
	// No se encontró ningún pasajero con el nombre proporcionado
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