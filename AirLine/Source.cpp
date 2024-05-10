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
	char vuelo[50];
	int num;
	int clase;
	int pase;
	int estado;
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
	//char genero[20];
	//char fecha[100];
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
//Lugares

//Avion
//Modelos
//Asientos (Para cada rango)
//Clase
//Precios
//RangoNiños
//RangoAdultos

struct consultorio
{
	consultorio* ant;
	char num[10];
	consultorio* sig;
};
consultorio* ini, * aux = nullptr;

struct horario
{
	horario* ant;
	char hor[30];
	horario* sig;
};
horario* ini2, * aux2 = nullptr;

struct dias
{
	dias* ant;
	char dia[30];
	dias* sig;
};
dias* ini3, * aux3 = nullptr;

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

#pragma region Funciones de Listas Usuarios
void nuevoUsuario(NodoUsuario* nuevo);
void eliminarUsuario(char nomUsu[30]);
void escribirUsuarios();
void leerUsuarios();
#pragma endregion

#pragma region Funciones de Listas Vuelos (Especialidades)
void nuevoVuelo(NodoVuelo* nueva);
void eliminarVuelo(char vuelo[30]);
void escribirVuelo();
void leerVuelos();
void reporteVuelos(); //Antes Boletos/Medicos
#pragma endregion

#pragma region Funciones de Listas Boletos (Medicos)
void nuevoBoleto(NodoBoleto* nuevoMed);
void eliminarBoleto(char medicoNom[60]);
void escribirBoletos();
void leerBoletos();
#pragma endregion

#pragma region Funciones de Listas Pasajeros (Pacientes)
void nuevoPasajero(NodoPasajero* nuevoPas);
void eliminarPasajero(char NodoPasajero[60]);
void escribirPasajeros();
void leerPasajeros();
void reportePasajeros(); //No es necesario
#pragma endregion

#pragma region Funciones de Arbol Boletos (Medicos)
//medico *crearNodo(medico* nuevoMed);
//void nuevoMed(medico*& pivote, medico* nuevoMed);
//bool buscarMed(medico *pivote, medico* busqueda);
//#pragma endregion

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
	leerVuelos();
	leerBoletos();
	leerPasajeros();

	// Asignacion de valores fijos
	#pragma region Valores fijos

	// Consultorios
	for (i = 1; i < 5; i++)
	{
		if (ini == nullptr)
		{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
			ini = new consultorio;

			strcpy_s(ini->num, "1");

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

			aux->sig = new consultorio;
			aux->sig->sig = nullptr;
			aux->sig->ant = aux;
			aux = aux->sig;

			if (i == 2)
			{
				strcpy_s(aux->num, "2");
			}
			else if (i == 3)
			{
				strcpy_s(aux->num, "3");
			}
			else
			{
				strcpy_s(aux->num, "4");
			}

			aux = ini;
		}

	}
	// Horarios
	for (i = 1; i < 5; i++)
	{
		if (ini2 == nullptr)
		{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
			ini2 = new horario;

			strcpy_s(ini2->hor, "6am - 6pm"); //6am-6pm

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

			aux2->sig = new horario;
			aux2->sig->sig = nullptr;
			aux2->sig->ant = aux2;
			aux2 = aux2->sig;

			if (i == 2)
			{
				strcpy_s(aux2->hor, "6pm - 12am"); // 6pm-12pm
			}
			else if (i == 3)
			{
				strcpy_s(aux2->hor, "6am - 3pm"); // 6pm-3pm
			}
			else
			{
				strcpy_s(aux2->hor, "3pm - 12am"); // 3pm-12am
			}

			aux2 = ini2;
		}

	}
	// Días
	for (i = 1; i < 5; i++)
	{
		if (ini3 == nullptr)
		{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
			ini3 = new dias;

			strcpy_s(ini3->dia, "Lunes - Viernes (M)");

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

			aux3->sig = new dias;
			aux3->sig->sig = nullptr;
			aux3->sig->ant = aux3;
			aux3 = aux3->sig;

			if (i == 2)
			{
				strcpy_s(aux3->dia, "Lunes - Viernes (N)");
			}
			else if (i == 3)
			{
				strcpy_s(aux3->dia, "Sabado (M)");
			}
			else
			{
				strcpy_s(aux3->dia, "Sabado (N)");
			}

			aux3 = ini3;
		}

	}

	// Pivotes
	if (iniBoleto != nullptr)
	{
		auxBoleto3 = iniBoleto;
		float i = 0;

		while (auxBoleto3->sig != nullptr)
		{
			i++;
			auxBoleto3 = auxBoleto3->sig;
		}

		i++;
		i = i / 2;
		auxBoleto3 = iniBoleto;

		for (float i2 = 0; i2 < i; i2++)
		{
			auxBoleto3 = auxBoleto3->sig;
		}

		pivote = auxBoleto3;
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
					char usuBuscar[30];
					char passwordBuscar[15];

					GetDlgItemText(hwnd, IDC_EDIT1, usuBuscar, sizeof(usuBuscar));
					GetDlgItemText(hwnd, IDC_EDIT2, passwordBuscar, sizeof(passwordBuscar));

					auxUsuario3 = iniUsuario;

					if (iniUsuario == nullptr)
					{
						MessageBox(NULL, "No hay usuarios registrados", "AVISO", MB_OK | MB_ICONERROR);
					}
					else {
						while (auxUsuario3->sig != nullptr && strcmp(usuBuscar, auxUsuario3->dato->nick) != 0)
							auxUsuario3 = auxUsuario3->sig;

						if (auxUsuario3->sig == nullptr && strcmp(usuBuscar, auxUsuario3->dato->nick) != 0)
							MessageBox(NULL, "No se encontró el usuario.", "AVISO", MB_OK | MB_ICONERROR);
						else
						{
							if (strcmp(passwordBuscar, auxUsuario3->dato->password) == 0)
							{
								miUsuario = auxUsuario3;
								inicio = true;

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
	//case WM_CLOSE:  //Cerrar ventana
	//{
	//	DestroyWindow(hwnd);
	//	break;
	//}
	//case WM_DESTROY:
	//{
	//	PostQuitMessage(1);  //Sólo se usa para cerrar la ventana principal
	//	break;
	//}
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

					auxUsuario3 = iniUsuario;

					while (auxUsuario3/*->sig*/ != nullptr && strcmp(usuBuscar, auxUsuario3->dato->nick) != 0)
					{
						auxUsuario3 = auxUsuario3->sig;
					}
					if (auxUsuario3/*->sig*/ == nullptr || strcmp(usuBuscar, auxUsuario3->dato->nick) != 0)
					{
						NodoUsuario* temp = new NodoUsuario;
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

						nuevoUsuario(temp);

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

					}
					else
					{
						MessageBox(NULL, "El nombre de usuario no esta disponible, pruebe con uno diferente.", "AVISO", MB_OK | MB_ICONINFORMATION);
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
				sprintf_s(cadenaNacimiento, "%f", miUsuario->dato->nacimiento);
				SetDlgItemText(hwnd, IDC_EDIT6, cadenaNacimiento);
				sprintf_s(cadenaNacimiento, "%f", miUsuario->dato->nacimiento);
				SetDlgItemText(hwnd, IDC_EDIT7, cadenaNacimiento);
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
					GetDlgItemText(hwnd, IDC_EDIT1, miUsuario->dato->nick, sizeof(miUsuario->dato->nick));
					GetDlgItemText(hwnd, IDC_EDIT2, miUsuario->dato->nombre, sizeof(miUsuario->dato->nombre));
					GetDlgItemText(hwnd, IDC_EDIT3, miUsuario->dato->apellidoP, sizeof(miUsuario->dato->apellidoP));
					GetDlgItemText(hwnd, IDC_EDIT4, miUsuario->dato->apellidoM, sizeof(miUsuario->dato->apellidoM));
					GetDlgItemText(hwnd, IDC_EDIT8, miUsuario->dato->email, sizeof(miUsuario->dato->email));
					GetDlgItemText(hwnd, IDC_EDIT9, miUsuario->dato->password, sizeof(miUsuario->dato->password));

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
					break;

					//Recarga la pestaña
					EndDialog(hwnd, 0);

					HWND hDialog3 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG3), 0, cDialog3);

					ShowWindow(hDialog3, SW_SHOW);
					UpdateWindow(hDialog3);
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
				default: break;
			}
			break;
		}
		default: break;
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

			auxUsuario2 = iniUsuario;
				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
			}

			auxUsuario2 = iniUsuario;

			while (auxUsuario2->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxUsuario2->dato->nick);
				auxUsuario2 = auxUsuario2->sig;
			}

			if (auxUsuario2->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxUsuario2->dato->nick);
				auxUsuario2 = auxUsuario2->sig;
			}

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

					auxUsuario2 = iniUsuario;

					while (auxUsuario2->sig != nullptr && strcmp(auxUsuario2->dato->nick, nombre) != 0)
					{
						auxUsuario2 = auxUsuario2->sig;
					}

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
						char NodoUsuario[30] = { 0 };
						int indice = 0;
						indice = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
						SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, indice, (LPARAM)NodoUsuario);

						if (strcmp(miUsuario->dato->nick, NodoUsuario) == 0)
						{
							MessageBox(NULL, "El usuario que inicio sesion será eliminado, se cerrará la sesion.", "AVISO", MB_OK | MB_ICONINFORMATION);

							eliminarUsuario(NodoUsuario);

							DestroyWindow(hwnd);
							PostQuitMessage(0);
						}
						else
						{
							eliminarUsuario(NodoUsuario);

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

		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1: // Número
		{
			if (iniVuelo == nullptr)
			{
				SetDlgItemText(hwnd, IDC_EDIT3, "1");
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

				/*auxEsp3 = auxEsp3->ant;*/

				tempNum->dato->num = auxVuelo3->dato->num;

				tempNum->dato->num = tempNum->dato->num + 1;

				// ::: ANTERIOR ::: // 
				//_itoa_s(tempNum->num, tempNum->claveChar, 10);
				//SetDlgItemText(hwnd, IDC_EDIT3, tempNum->claveChar);
			}

			break;
			
		}
		case IDC_BUTTON2: // Guardar
		{
			char espBuscar[30];

			GetDlgItemText(hwnd, IDC_EDIT1, espBuscar, sizeof(espBuscar));

			auxVuelo2 = iniVuelo;

			while (auxVuelo2/*->sig*/ != nullptr && strcmp(espBuscar, auxVuelo2->dato->origen) != 0)
			{
				auxVuelo2 = auxVuelo2->sig;
			}

			if (auxVuelo2/*->sig*/ == nullptr || strcmp(espBuscar, auxVuelo2->dato->origen) != 0)
			{
				NodoVuelo* temp = new NodoVuelo;

				GetDlgItemText(hwnd, IDC_EDIT2, temp->dato->origen, sizeof(temp->dato->origen));
				GetDlgItemText(hwnd, IDC_EDIT4, temp->dato->destino, sizeof(temp->dato->destino));
				//GetDlgItemText(hwnd, IDC_EDIT3, temp->claveChar, sizeof(temp->claveChar));
				strcpy_s(temp->dato->usuarioRegistro, miUsuario->dato->nick);
				nuevoVuelo(temp);
				SetDlgItemText(hwnd, IDC_EDIT2, "");
				SetDlgItemText(hwnd, IDC_EDIT3, "");
				SetDlgItemText(hwnd, IDC_EDIT4, "");

				EndDialog(hwnd, 0);

				HWND hDialog5 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG5), 0, cDialog5);

				ShowWindow(hDialog5, SW_SHOW);
				UpdateWindow(hDialog5);
			}
			else
			{
				MessageBox(NULL, "La especialidad ya esta registrada.", "AVISO", MB_OK | MB_ICONINFORMATION);
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
			MessageBox(NULL, "No hay especialidades registradas.", "AVISO", MB_OK | MB_ICONINFORMATION);
		}
		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_LIST2:
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char nombreEspC[30] = { 0 };
				int indice2 = 0;
				indice2 = SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETTEXT, indice2, (LPARAM)nombreEspC);

				auxVuelo2 = iniVuelo;

				while (auxVuelo2->sig != nullptr && strcmp(auxVuelo2->dato->origen, nombreEspC) != 0)
				{
					auxVuelo2 = auxVuelo2->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT2, auxVuelo2->dato->origen);
				SetDlgItemText(hwnd, IDC_EDIT4, auxVuelo2->dato->destino);
				//SetDlgItemText(hwnd, IDC_EDIT3, auxEsp2->claveChar);
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
				MessageBox(NULL, "No se ha seleccionado una especialidad, seleccione una de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
				int opc = MessageBox(hwnd, "¿Seguro que desea cancelar este vuelo?", "AVISO", MB_YESNO | MB_ICONQUESTION);

				switch (opc)
				{
				case IDYES:
				{
					/*char especialidad[30] = { 0 };
					int indice2 = 0;
					indice2 = SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETCURSEL, 0, 0);
					SendDlgItemMessage(hwnd, IDC_LIST2, LB_GETTEXT, indice2, (LPARAM)especialidad);

					GetDlgItemText(hwnd, IDC_EDIT2, auxVuelo2->origen, sizeof(auxVuelo2->origen));
					GetDlgItemText(hwnd, IDC_EDIT4, auxVuelo2->destino, sizeof(auxVuelo2->destino));
					//GetDlgItemText(hwnd, IDC_EDIT3, auxEsp2->claveChar, sizeof(auxEsp2->claveChar));
					//auxEsp2->num = atoi(auxEsp2->claveChar);
					MessageBox(NULL, "Cambios guardados.", "AVISO", MB_OK | MB_ICONINFORMATION);
					eliminarEsp(especialidad);

					SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_DELETESTRING, indice2, 0);
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");*/

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
				MessageBox(NULL, "No se ha seleccionado una especialidad, seleccione una de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
				int opc = MessageBox(hwnd, "¿Seguro que desea confirmar este vuelo?", "AVISO", MB_YESNO | MB_ICONQUESTION);

				switch (opc)
				{
				case IDYES:
				{
					/*
					eliminarEsp(especialidad);
					SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_DELETESTRING, indice2, 0);
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");

					auxVuelo2 = nullptr;
					auxVuelo = nullptr;	
					*/
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
			//especialidad* tempNum = new especialidad;
			//auxEsp3 = iniEsp;

			break;
		}
		/*
		case IDC_BUTTON: // Clave
		{
			Vuelo* tempNum = new Vuelo;
			auxVuelo3 = iniVuelo;
			//while (auxEsp3->sig != nullptr)
			//{
			//	auxEsp3 = auxEsp3->sig;
			//}

			while (auxVuelo3->sig != nullptr)
			{
				auxVuelo3 = auxVuelo3->sig;
			}
			//tempNum->claveNum = auxEsp3->claveNum;

			tempNum->num = auxVuelo3->num;
			tempNum->num = tempNum->num + 1;
			//tempNum->claveNum = tempNum->claveNum + 1;

			// ::: ANTERIOR 
			//_itoa_s(tempNum->num, tempNum->claveChar, 10);
			//SetDlgItemText(hwnd, IDC_EDIT3, tempNum->claveChar);
			//_itoa_s(tempNum->claveNum, tempNum->claveChar, 10);

			/*especialidad* tempNum = new especialidad;
			auxEsp3 = auxEsp2;
			//SetDlgItemText(hwnd, IDC_EDIT3, tempNum->claveChar);

			///*especialidad* tempNum = new especialidad;
			//auxEsp3 = auxEsp2;

			//tempNum->claveNum = auxEsp3->claveNum;

			//tempNum->claveNum = tempNum->claveNum + 1;

			//_itoa_s(tempNum->claveNum, tempNum->claveChar, 10);

			//SetDlgItemText(hwnd, IDC_EDIT3, tempNum->claveChar);

		break;
		}
		*/
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

		aux = ini; // Consultorios

		while (aux->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST6, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux->num);
			aux = aux->sig;
		}

		if (aux->sig == nullptr/* || auxUsu2->ant == nullptr*/)
		{
			SendDlgItemMessage(hwnd, IDC_LIST6, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux->num);
			aux = aux->sig;
		}

		aux2 = ini2; // Horarios

		while (aux2->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST7, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux2->hor);
			aux2 = aux2->sig;
		}

		if (aux2->sig == nullptr/* || auxUsu2->ant == nullptr*/)
		{
			SendDlgItemMessage(hwnd, IDC_LIST7, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux2->hor);
			aux2 = aux2->sig;
		}

		aux3 = ini3; // Días

		while (aux3->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST8, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux3->dia);
			aux3 = aux3->sig;
		}

		if (aux3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
		{
			SendDlgItemMessage(hwnd, IDC_LIST8, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux3->dia);
			aux3 = aux3->sig;
		}

		auxVuelo3 = iniVuelo; // Especialidades

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
			MessageBox(NULL, "No hay especialidades registradas.", "AVISO", MB_OK | MB_ICONINFORMATION);
		}

		//auxMed = pivote;

		//strcpy_s(zFile, auxMed->foto); //Inicializar zfile con la dirección de memoria del puntero foto

		//HBITMAP bmp; //1
		//bmp = (HBITMAP)LoadImage(NULL, auxMed->foto, IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE); //2
		//SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 

		break;
	}
	case WM_COMMAND:
	{
		long opcion = LOWORD(wParam);
		cMenu(hwnd, opcion);

		switch (LOWORD(wParam))
		{
		case IDC_LIST6: // Consultorio
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char num2[30] = { 0 };
				int indice2 = 0;
				indice2 = SendDlgItemMessage(hwnd, IDC_LIST6, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST6, LB_GETTEXT, indice2, (LPARAM)num2);

				aux = ini;

				while (aux->sig != nullptr && strcmp(aux->num, num2) != 0)
				{
					aux = aux->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT14, aux->num);

				break;
			}

			default:
			{
				break;
			}

			}

			break;
		}
		case IDC_LIST7: // Horario
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char num3[30] = { 0 };
				int indice3 = 0;
				indice3 = SendDlgItemMessage(hwnd, IDC_LIST7, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST7, LB_GETTEXT, indice3, (LPARAM)num3);

				aux2 = ini2;

				while (aux2->sig != nullptr && strcmp(aux2->hor, num3) != 0)
				{
					aux2 = aux2->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT15, aux2->hor);

				break;
			}

			default:
			{
				break;
			}

			}

			break;
		}
		case IDC_LIST8: // Día
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char num4[30] = { 0 };
				int indice4 = 0;
				indice4 = SendDlgItemMessage(hwnd, IDC_LIST8, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST8, LB_GETTEXT, indice4, (LPARAM)num4);

				aux3 = ini3;

				while (aux3->sig != nullptr && strcmp(aux3->dia, num4) != 0)
				{
					aux3 = aux3->sig;

				}

				SetDlgItemText(hwnd, IDC_EDIT16, aux3->dia);

				break;
			}

			default:
			{
				break;
			}

			}

			break;
		}
		case IDC_LIST9: // Especialidades
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK: //Al dar doble clic en el ListBox 
			{
				char num5[30] = { 0 };
				int indice5 = 0;
				indice5 = SendDlgItemMessage(hwnd, IDC_LIST9, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST9, LB_GETTEXT, indice5, (LPARAM)num5);

				auxVuelo3 = iniVuelo;

				while (auxVuelo3->sig != nullptr && strcmp(auxVuelo3->dato->origen, num5) != 0)
				{
					auxVuelo3 = auxVuelo3->sig;

				}

				SetDlgItemText(hwnd, IDC_EDIT17, auxVuelo3->dato->origen);

				break;
			}

			default:
			{
				break;
			}

			}

			break;
		}
		case IDC_BUTTON1: // Cargar
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
				bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 
			}

			break;
		}
		case IDC_BUTTON2: // Guardar
		{
			char medBuscar[20];

			GetDlgItemText(hwnd, IDC_EDIT5, medBuscar, sizeof(medBuscar));

			auxBoleto2 = pivote;

			// Campos
			NodoBoleto* temp = new NodoBoleto;

			GetDlgItemText(hwnd, IDC_EDIT2, temp->dato->nombrePasajero, sizeof(temp->dato->nombrePasajero));
			GetDlgItemText(hwnd, IDC_EDIT3, temp->dato->apellidoPPasajero, sizeof(temp->dato->apellidoPPasajero));
			GetDlgItemText(hwnd, IDC_EDIT4, temp->dato->apellidoMPasajero, sizeof(temp->dato->apellidoMPasajero));
			//GetDlgItemText(hwnd, IDC_EDIT5, temp->cedulaChar, sizeof(temp->cedulaChar));
			//GetDlgItemText(hwnd, IDC_EDIT8, temp->telefonoChar, sizeof(temp->telefonoChar));
			//GetDlgItemText(hwnd, IDC_EDIT14, temp->numConsultorioChar, sizeof(temp->numConsultorioChar));
			//GetDlgItemText(hwnd, IDC_EDIT15, temp->hoararioChar, sizeof(temp->hoararioChar));
			//GetDlgItemText(hwnd, IDC_EDIT16, temp->diasChar, sizeof(temp->diasChar));
			GetDlgItemText(hwnd, IDC_EDIT17, temp->dato->vuelo, sizeof(temp->dato->vuelo));
			//strcpy_s(temp->foto, zFile);

			if (//strcmp(temp->foto, "") != 0 &
				strcmp(temp->dato->nombrePasajero, "") != 0 &
				strcmp(temp->dato->apellidoPPasajero, "") != 0 &
				strcmp(temp->dato->apellidoMPasajero, "") != 0 &
				//strcmp(temp->cedulaChar, "") != 0 &
				//strcmp(temp->telefonoChar, "") != 0 &
				//strcmp(temp->numConsultorioChar, "") != 0 &
				//strcmp(temp->hoararioChar, "") != 0 &
				//strcmp(temp->diasChar, "") != 0 &
				strcmp(temp->dato->vuelo, "") != 0)
			{
				//while (auxMed2/*->sig*/ != nullptr && strcmp(medBuscar, auxMed2->cedulaChar) != 0)
				{
					auxBoleto2 = auxBoleto2->sig;
				}

				//if (auxMed2/*->sig*/ == nullptr || strcmp(medBuscar, auxMed2->cedulaChar) != 0)
				{
					/*medico* temp = new medico;*/

					GetDlgItemText(hwnd, IDC_EDIT2, temp->dato->nombrePasajero, sizeof(temp->dato->nombrePasajero));
					GetDlgItemText(hwnd, IDC_EDIT3, temp->dato->apellidoPPasajero, sizeof(temp->dato->apellidoPPasajero));
					GetDlgItemText(hwnd, IDC_EDIT4, temp->dato->apellidoMPasajero, sizeof(temp->dato->apellidoMPasajero));
					//GetDlgItemText(hwnd, IDC_EDIT5, temp->cedulaChar, sizeof(temp->cedulaChar));
					//GetDlgItemText(hwnd, IDC_EDIT8, temp->telefonoChar, sizeof(temp->telefonoChar));
					//GetDlgItemText(hwnd, IDC_EDIT14, temp->numConsultorioChar, sizeof(temp->numConsultorioChar));
					//GetDlgItemText(hwnd, IDC_EDIT15, temp->hoararioChar, sizeof(temp->hoararioChar));
					//GetDlgItemText(hwnd, IDC_EDIT16, temp->diasChar, sizeof(temp->diasChar));
					GetDlgItemText(hwnd, IDC_EDIT17, temp->dato->vuelo, sizeof(temp->dato->vuelo));

					// Horario
					/*
					* if (strcmp(temp->hoararioChar, "6am - 6pm") == 0)
					{
						temp->pase = 1;
					}
					else if (strcmp(temp->hoararioChar, "6pm - 12am") == 0)
					{
						temp->pase = 2;
					}
					else if (strcmp(temp->hoararioChar, "6am - 3pm") == 0)
					{
						temp->pase = 3;
					}
					else
					{
						temp->pase = 4;
					}
					*/
					

					// Días
					/*
					if (strcmp(temp->diasChar, "Lunes - Viernes (M)") == 0)
					{
						temp->diasNum = 1;
					}
					else if (strcmp(temp->diasChar, "Lunes - Viernes (N)") == 0)
					{
						temp->diasNum = 2;
					}
					else if (strcmp(temp->diasChar, "Sabado (M)") == 0)
					{
						temp->diasNum = 3;
					}
					else
					{
						temp->diasNum = 4;
					}
					*/
					
					//strcpy_s(temp->foto, zFile);
					strcpy_s(temp->dato->usuarioRegistro, miUsuario->dato->nick);

					nuevoBoleto(temp);

					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");
					SetDlgItemText(hwnd, IDC_EDIT5, "");
					SetDlgItemText(hwnd, IDC_EDIT8, "");

					SetDlgItemText(hwnd, IDC_EDIT14, "");
					SetDlgItemText(hwnd, IDC_EDIT15, "");
					SetDlgItemText(hwnd, IDC_EDIT16, "");
					SetDlgItemText(hwnd, IDC_EDIT17, "");

					EndDialog(hwnd, 0);

					HWND hDialog7 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG7), 0, cDialog7);

					ShowWindow(hDialog7, SW_SHOW);
					UpdateWindow(hDialog7);
				}
				//else
				{
					MessageBox(NULL, "Es posible que este medico ya este registrado.", "AVISO", MB_OK | MB_ICONEXCLAMATION);
				}
			}
			else
			{
				MessageBox(NULL, "Todos los campos son abligatorios.", "AVISO", MB_OK | MB_ICONEXCLAMATION);
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
			auxBoleto3 = iniBoleto; // Medicos

			while (auxBoleto3->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto3->dato->nombreCompPasajero/*nombreCompM*/);
				auxBoleto3 = auxBoleto3->sig;
			}
			if (auxBoleto3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto3->dato->nombreCompPasajero/*nombreCompM*/);
				auxBoleto3 = auxBoleto3->sig;
			}
			aux = ini; // Consultorios

			while (aux->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST6, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux->num);
				aux = aux->sig;
			}
			if (aux->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST6, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux->num);
				aux = aux->sig;
			}
			aux2 = ini2; // Horarios

			while (aux2->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST7, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux2->hor);
				aux2 = aux2->sig;
			}

			if (aux2->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST7, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux2->hor);
				aux2 = aux2->sig;
			}

			aux3 = ini3; // Días

			while (aux3->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST8, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux3->dia);
				aux3 = aux3->sig;
			}

			if (aux3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST8, LB_ADDSTRING, (WPARAM)0, (LPARAM)aux3->dia);
				aux3 = aux3->sig;
			}

			auxVuelo3 = iniVuelo; // Especialidades

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
				MessageBox(NULL, "No hay especialidades registradas.", "AVISO", MB_OK | MB_ICONINFORMATION);
			}

			break;
		}
		case WM_COMMAND:
		{
			long opcion = LOWORD(wParam);
			cMenu(hwnd, opcion);

			switch (LOWORD(wParam))
			{
			case IDC_LIST6: // Consultorio
			{
				switch (HIWORD(wParam))
				{
				case LBN_DBLCLK: //Al dar doble clic en el ListBox 
				{
					char num2[30] = { 0 };
					int indice2 = 0;
					indice2 = SendDlgItemMessage(hwnd, IDC_LIST6, LB_GETCURSEL, 0, 0);
					SendDlgItemMessage(hwnd, IDC_LIST6, LB_GETTEXT, indice2, (LPARAM)num2);

					aux = ini;

					while (aux->sig != nullptr && strcmp(aux->num, num2) != 0)
					{
						aux = aux->sig;
					}

					SetDlgItemText(hwnd, IDC_EDIT17, aux->num);

					break;
				}

				default:
				{
					break;
				}

				}

				break;
			}
			case IDC_LIST7: // Horario
			{
				switch (HIWORD(wParam))
				{
				case LBN_DBLCLK: //Al dar doble clic en el ListBox 
				{
					char num3[30] = { 0 };
					int indice3 = 0;
					indice3 = SendDlgItemMessage(hwnd, IDC_LIST7, LB_GETCURSEL, 0, 0);
					SendDlgItemMessage(hwnd, IDC_LIST7, LB_GETTEXT, indice3, (LPARAM)num3);

					aux2 = ini2;

					while (aux2->sig != nullptr && strcmp(aux2->hor, num3) != 0)
					{
						aux2 = aux2->sig;
					}

					SetDlgItemText(hwnd, IDC_EDIT15, aux2->hor);

					break;
				}

				default:
				{
					break;
				}

				}

				break;
			}
			case IDC_LIST8: // Día
			{
				switch (HIWORD(wParam))
				{
				case LBN_DBLCLK: //Al dar doble clic en el ListBox 
				{
					char num4[30] = { 0 };
					int indice4 = 0;
					indice4 = SendDlgItemMessage(hwnd, IDC_LIST8, LB_GETCURSEL, 0, 0);
					SendDlgItemMessage(hwnd, IDC_LIST8, LB_GETTEXT, indice4, (LPARAM)num4);

					aux3 = ini3;

					while (aux3->sig != nullptr && strcmp(aux3->dia, num4) != 0)
					{
						aux3 = aux3->sig;

					}

					SetDlgItemText(hwnd, IDC_EDIT16, aux3->dia);

					break;
				}

				default:
				{
					break;
				}

				}

				break;
			}
			case IDC_LIST10: // Especialidades
			{
				switch (HIWORD(wParam))
				{
				case LBN_DBLCLK: //Al dar doble clic en el ListBox 
				{
					char num5[30] = { 0 };
					int indice5 = 0;
					indice5 = SendDlgItemMessage(hwnd, IDC_LIST10, LB_GETCURSEL, 0, 0);
					SendDlgItemMessage(hwnd, IDC_LIST10, LB_GETTEXT, indice5, (LPARAM)num5);

					auxVuelo3 = iniVuelo;

					while (auxVuelo3->sig != nullptr && strcmp(auxVuelo3->dato->origen, num5) != 0)
					{
						auxVuelo3 = auxVuelo3->sig;

					}

					SetDlgItemText(hwnd, IDC_EDIT18, auxVuelo3->dato->origen);

					break;
				}

				default:
				{
					break;
				}

				}

				break;
			}
			case IDC_LIST3: // Medicos
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

					while (auxBoleto3->sig != nullptr && strcmp(auxBoleto3->dato->nombreCompPasajero, num) != 0)
					{
						auxBoleto3 = auxBoleto3->sig;

					}

					SetDlgItemText(hwnd, IDC_EDIT2, auxBoleto3->dato->nombrePasajero);
					SetDlgItemText(hwnd, IDC_EDIT3, auxBoleto3->dato->apellidoPPasajero);
					SetDlgItemText(hwnd, IDC_EDIT4, auxBoleto3->dato->apellidoMPasajero);

					//SetDlgItemText(hwnd, IDC_EDIT5, auxMed3->cedulaChar);
					SetDlgItemText(hwnd, IDC_EDIT18, auxBoleto3->dato->vuelo);

					//SetDlgItemText(hwnd, IDC_EDIT8, auxMed3->telefonoChar);

					//SetDlgItemText(hwnd, IDC_EDIT17, auxMed3->numConsultorioChar);
					//SetDlgItemText(hwnd, IDC_EDIT15, auxMed3->hoararioChar);
					//SetDlgItemText(hwnd, IDC_EDIT16, auxMed3->diasChar);

					//strcpy_s(zFile, auxMed3->foto); //Inicializar zfile con la dirección de memoria del puntero foto

					HBITMAP bmp; //1
					//bmp = (HBITMAP)LoadImage(NULL, auxMed3->foto, IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE); //2
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
			case IDC_BUTTON1: // Editar
			{
				GetDlgItemText(hwnd, IDC_EDIT2, auxBoleto3->dato->nombrePasajero, sizeof(auxBoleto3->dato->nombrePasajero));
				GetDlgItemText(hwnd, IDC_EDIT3, auxBoleto3->dato->apellidoPPasajero, sizeof(auxBoleto3->dato->apellidoPPasajero));
				GetDlgItemText(hwnd, IDC_EDIT4, auxBoleto3->dato->apellidoPPasajero, sizeof(auxBoleto3->dato->apellidoPPasajero));

				//GetDlgItemText(hwnd, IDC_EDIT5, auxMed3->cedulaChar, sizeof(auxMed3->cedulaChar));
				//auxMed3->cedulaNum = atoi(auxMed3->cedulaChar);
				GetDlgItemText(hwnd, IDC_EDIT18, auxBoleto3->dato->vuelo, sizeof(auxBoleto3->dato->vuelo));
			
				//GetDlgItemText(hwnd, IDC_EDIT8, auxMed3->telefonoChar, sizeof(auxMed3->telefonoChar));
				//auxMed3->estado = atoi(auxMed3->telefonoChar);

				//GetDlgItemText(hwnd, IDC_EDIT17, auxMed3->numConsultorioChar, sizeof(auxMed3->numConsultorioChar));
				//auxMed3->clase = atoi(auxMed3->numConsultorioChar);
				//GetDlgItemText(hwnd, IDC_EDIT15, auxMed3->hoararioChar, sizeof(auxMed3->hoararioChar));
				// Horario
				/*
				* if (strcmp(auxMed3->hoararioChar, "6am - 6pm") == 0)
				{
					auxMed3->pase = 1;
				}
				else if (strcmp(auxMed3->hoararioChar, "6pm - 12am") == 0)
				{
					auxMed3->pase = 2;
				}
				else if (strcmp(auxMed3->hoararioChar, "6am - 3pm") == 0)
				{
					auxMed3->pase = 3;
				}
				else
				{
					auxMed3->pase = 4;
				}
				GetDlgItemText(hwnd, IDC_EDIT16, auxMed3->diasChar, sizeof(auxMed3->diasChar));
				*/
			
				// Días
				/*
				if (strcmp(auxMed3->diasChar, "Lunes - Viernes (M)") == 0)
				{
					auxMed3->diasNum = 1;
				}
				else if (strcmp(auxMed3->diasChar, "Lunes - Viernes (N)") == 0)
				{
					auxMed3->diasNum = 2;
				}
				else if (strcmp(auxMed3->diasChar, "Sabado (M)") == 0)
				{
					auxMed3->diasNum = 3;
				}
				else
				{
					auxMed3->diasNum = 4;
				}
				*/

				// Concatenación
				strcpy_s(auxBoleto3->dato->nombreCompPasajero, auxBoleto3->dato->nombrePasajero);
				strcat_s(auxBoleto3->dato->nombreCompPasajero, " ");
				strcat_s(auxBoleto3->dato->nombreCompPasajero, auxBoleto3->dato->apellidoPPasajero);
				strcat_s(auxBoleto3->dato->nombreCompPasajero, " ");
				strcat_s(auxBoleto3->dato->nombreCompPasajero, auxBoleto3->dato->apellidoPPasajero);

				//strcpy_s(auxMed3->foto,zFile);

				MessageBox(NULL, "Cambios guardados.", "AVISO", MB_OK | MB_ICONINFORMATION);

				break;
			}
			case IDC_BUTTON2: // Eliminar
			{
				if (auxBoleto3 == nullptr)
				{
					MessageBox(NULL, "No se ha seleccionado a un medico, seleccione uno de la lista con doble click.", "AVISO", MB_OK | MB_ICONERROR);
				}
				else
				{
					int opc = MessageBox(hwnd, "¿Seguro que desea eliminar a este medico?", "AVISO", MB_YESNO | MB_ICONQUESTION);

					switch (opc)
					{
					case IDYES:
					{
						char medico[60] = { 0 };
						int indiceE = 0;
						indiceE = SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
						SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETTEXT, indiceE, (LPARAM)medico);

						eliminarBoleto(medico);

						SendMessage(GetDlgItem(hwnd, IDC_LIST3), LB_DELETESTRING, indiceE, 0);

						SetDlgItemText(hwnd, IDC_EDIT2, "");
						SetDlgItemText(hwnd, IDC_EDIT3, "");
						SetDlgItemText(hwnd, IDC_EDIT4, "");

						SetDlgItemText(hwnd, IDC_EDIT5, "");
						SetDlgItemText(hwnd, IDC_EDIT18, "");

						SetDlgItemText(hwnd, IDC_EDIT8, "");

						SetDlgItemText(hwnd, IDC_EDIT17, "");
						SetDlgItemText(hwnd, IDC_EDIT15, "");
						SetDlgItemText(hwnd, IDC_EDIT16, "");

						auxBoleto3 = nullptr;

						break;
					}

					case IDNO:
					{
						SetDlgItemText(hwnd, IDC_EDIT2, "");
						SetDlgItemText(hwnd, IDC_EDIT3, "");
						SetDlgItemText(hwnd, IDC_EDIT4, "");

						SetDlgItemText(hwnd, IDC_EDIT5, "");
						SetDlgItemText(hwnd, IDC_EDIT18, "");

						SetDlgItemText(hwnd, IDC_EDIT8, "");

						SetDlgItemText(hwnd, IDC_EDIT17, "");
						SetDlgItemText(hwnd, IDC_EDIT15, "");
						SetDlgItemText(hwnd, IDC_EDIT16, "");

						auxBoleto3 = nullptr;

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
			case IDC_BUTTON3: // Cargar
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
					bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE); //2
					SendDlgItemMessage(hwnd, /*IDC_BMP2*/1056, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 
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
		default: break;

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
			if (miUsuario->dato->foto != nullptr);
			{
				strcpy_s(zFile, miUsuario->dato->foto); //Inicializar zfile con la dirección de memoria del puntero foto

				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, miUsuario->dato->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
			}
			auxBoleto3 = iniBoleto; // Medicos

			while (auxBoleto3->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto3->dato->nombreCompPasajero/*nombreCompM*/);
				auxBoleto3 = auxBoleto3->sig;
			}
			if (auxBoleto3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto3->dato->nombreCompPasajero/*nombreCompM*/);
				auxBoleto3 = auxBoleto3->sig;
			}

			//FECHA
			SYSTEMTIME fechaHoy;
			ZeroMemory(&fechaHoy, sizeof(fechaHoy));
			GetLocalTime(&fechaHoy);

			char fechaCompleta[30] = { 0 };
			char fechaChar[5] = { 0 };

			sprintf_s(fechaChar, "%d", fechaHoy.wYear);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, "/");

			sprintf_s(fechaChar, "%d", fechaHoy.wMonth);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, "/");

			sprintf_s(fechaChar, "%d", fechaHoy.wDay);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, "/");

			sprintf_s(fechaChar, "%d", fechaHoy.wHour);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, ":");

			sprintf_s(fechaChar, "%d", fechaHoy.wMinute);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, ":");

			sprintf_s(fechaChar, "%d", fechaHoy.wSecond);

			strcat_s(fechaCompleta, fechaChar);

			/*strcpy_s(aux->fechaCompleta, fechaCompleta);*/

			/*SetWindowText(GetDlgItem(hwnd, IDC_EDIT35), fechaCompleta);*/

			break;
		}
		case WM_COMMAND:
		{
			long opcion = LOWORD(wParam);
			cMenu(hwnd, opcion);

			switch (LOWORD(wParam))
			{
				case IDC_LIST3: // Medicos
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

							while (auxBoleto3->sig != nullptr && strcmp(auxBoleto3->dato->nombreCompPasajero, num) != 0)
							{
								auxBoleto3 = auxBoleto3->sig;

							}
							SetDlgItemText(hwnd, IDC_EDIT8, auxBoleto3->dato->nombreCompPasajero);
							break;
						}
						default: break;
					}
					break;
				}
				case IDC_BUTTON1: // Guardar
				{
					/*GetDlgItemText(hwnd, IDC_DATETIMEPICKER1, fecha, sizeof(fecha));*/

					char pasBuscar[60];

					GetDlgItemText(hwnd, IDC_EDIT2, pasBuscar, sizeof(pasBuscar));

					auxPasajero2 = iniPasajero;

					while (auxPasajero2/*->sig*/ != nullptr && strcmp(pasBuscar, auxPasajero2->dato->nombreComp) != 0)
					{
						auxPasajero2 = auxPasajero2->sig;
					}

					if (auxPasajero2/*->sig*/ == nullptr || strcmp(pasBuscar, auxPasajero2->dato->nombreComp) != 0)
					{
						NodoPasajero* temp = new NodoPasajero;

						GetDlgItemText(hwnd, IDC_EDIT2, temp->dato->nombre, sizeof(temp->dato->nombre));
						GetDlgItemText(hwnd, IDC_EDIT3, temp->dato->apellidoP, sizeof(temp->dato->apellidoP));
						GetDlgItemText(hwnd, IDC_EDIT4, temp->dato->apellidoM, sizeof(temp->dato->apellidoM));

						// Genero 
						if (IsDlgButtonChecked(hwnd, IDC_RADIO1))
						{
							//strcpy_s(temp->genero, "Masculino");
						}
						else
						{
							//strcpy_s(temp->genero, "Femenino");
						}

						GetDlgItemText(hwnd, IDC_EDIT5, temp->dato->nacionalidad, sizeof(temp->dato->nacionalidad));
						//GetDlgItemText(hwnd, IDC_DATETIMEPICKER1, temp->fecha, sizeof(temp->fecha));

						// ::: PASADOS ::: //
						//GetDlgItemText(hwnd, IDC_EDIT6, temp->ref, sizeof(temp->ref));				
						//GetDlgItemText(hwnd, IDC_EDIT7, temp->edadChar, sizeof(temp->edadChar));
						//GetDlgItemText(hwnd, IDC_EDIT8, temp->pMedicoP, sizeof(temp->pMedicoP));

						strcpy_s(temp->dato->usuarioRegistro, miUsuario->dato->nick);

						nuevoPasajero(temp);

						SetDlgItemText(hwnd, IDC_EDIT2, "");
						SetDlgItemText(hwnd, IDC_EDIT3, "");
						SetDlgItemText(hwnd, IDC_EDIT4, "");
						SetDlgItemText(hwnd, IDC_EDIT5, "");
						SetDlgItemText(hwnd, IDC_EDIT8, "");

						EndDialog(hwnd, 0);

						HWND hDialog10 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG10), 0, cDialog10);

						ShowWindow(hDialog10, SW_SHOW);
						UpdateWindow(hDialog10);
					}else
						MessageBox(NULL, "Es posible que este paciente ya este registrado.", "AVISO", MB_OK | MB_ICONINFORMATION);
					break;
				}
				default: break;
			}
		}
	return false;  // Un callback siempre retorna falso
	}
}

// Lista Pasajeros
BOOL CALLBACK cDialog11(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
			auxBoleto3 = iniBoleto; // Medicos

			while (auxBoleto3->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto3->dato->nombreCompPasajero/*nombreCompM*/);
				auxBoleto3 = auxBoleto3->sig;
			}
			if (auxBoleto3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxBoleto3->dato->nombreCompPasajero/*nombreCompM*/);
				auxBoleto3 = auxBoleto3->sig;
			}

			//FECHA
			SYSTEMTIME fechaHoy;
			ZeroMemory(&fechaHoy, sizeof(fechaHoy));
			GetLocalTime(&fechaHoy);

			char fechaCompleta[30] = { 0 };
			char fechaChar[5] = { 0 };

			sprintf_s(fechaChar, "%d", fechaHoy.wYear);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, "/");

			sprintf_s(fechaChar, "%d", fechaHoy.wMonth);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, "/");

			sprintf_s(fechaChar, "%d", fechaHoy.wDay);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, "/");

			sprintf_s(fechaChar, "%d", fechaHoy.wHour);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, ":");

			sprintf_s(fechaChar, "%d", fechaHoy.wMinute);

			strcat_s(fechaCompleta, fechaChar);
			strcat_s(fechaCompleta, ":");

			sprintf_s(fechaChar, "%d", fechaHoy.wSecond);

			strcat_s(fechaCompleta, fechaChar);

			/*strcpy_s(aux->fechaCompleta, fechaCompleta);*/
			/*SetWindowText(GetDlgItem(hwnd, IDC_EDIT35), fechaCompleta);*/
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


					break;
				}
				case IDC_BUTTON2: // Editar
				{


					break;
				}
				case IDC_BUTTON3: // Eliminar
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
			//auxPas3 = iniPas;

			while (auxPasajero3->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxPasajero3->dato->nombreComp/*nombreCompM*/);
				auxPasajero3 = auxPasajero3->sig;
			}
			//while (auxPas3->sig != nullptr)
			//{
			//	SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxPas3->nombreCompP/*nombreCompM*/);
			//	auxPas3 = auxPas3->sig;
			//}

			if (auxBoleto3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxPasajero3->dato->nombreComp/*nombreCompM*/);
				auxPasajero3 = auxPasajero3->sig;
			}
			//if (auxMed3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			//{
			//	SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxPas3->nombreCompP/*nombreCompM*/);
			//	auxPas3 = auxPas3->sig;
			//}
			break;
		}
		case WM_COMMAND:
		{
			long opcion = LOWORD(wParam);
			cMenu(hwnd, opcion);

			switch (LOWORD(wParam))
			{
				case IDC_BUTTON1: // generar
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
		case IDC_BUTTON3: // Generar Hora
		{


			break;
		}
		case IDC_BUTTON4: // Guardar
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
	case ID_VUELOS_REGISTRO: // Registro Especialidades
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
		int opc = MessageBox(hwnd, "¿Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
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
//Genéricas
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
char* formatoEdad(LPSYSTEMTIME Sys, char* buff) {

	std::string strMessage;
	CString cstrMessage;

	cstrMessage.Format(_T("%d"), Sys->wYear);

	strMessage = CT2A(cstrMessage.GetString());
	std::cout << "System time = " << strMessage << std::endl;

	std::ostringstream ossMessage;
	ossMessage << Sys->wYear;

	strMessage = ossMessage.str();
	std::cout << "System time = " << strMessage << std::endl;

	sprintf_s(buff, 100, "%d", Sys->wYear);
	return buff;
}

//Listas de Usuarios
#pragma region Funciones de Listas Usuarios
void nuevoUsuario(NodoUsuario* nuevo)
{
	if (iniUsuario == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniUsuario = new NodoUsuario;

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

		auxUsuario2 = auxUsuario;
		auxUsuario3 = auxUsuario;
		auxUsuario = iniUsuario;
	}

	MessageBox(NULL, "Se ha registrado el usuario con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
}
void eliminarUsuario(char nomUsu[30])
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
				/*auxUsu3 = auxUsu;*/
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

				start = iniUsuario->sig;
				auxUsuario->sig->ant = nullptr;
				delete auxUsuario;
				auxUsuario = start;
				auxUsuario->ant = nullptr;

				auxUsuario = iniUsuario;
				auxUsuario2 = auxUsuario;
				/*auxUsu3 = auxUsu;*/
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
				/*auxUsu3 = auxUsu;*/
			}
			else
			{ //Si es cualquier nodo que no sea el inicio o el último
				auxUsuario->sig->ant = auxUsuario->ant;
				auxUsuario->ant->sig = auxUsuario->sig;
				delete auxUsuario;

				auxUsuario = iniUsuario;
				auxUsuario2 = auxUsuario;
				/*auxUsu3 = auxUsu;*/ //Para que auxEsp no quede sin apuntar a nada, la apuntamos al inicio
			}
			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);
		}
	}
}
void escribirUsuarios()
{
	auxUsuario = iniUsuario;

	ofstream escribir;
	escribir.open("Usuarios.bin", ios::out | ios::binary | ios::trunc);
	
	if (!escribir.is_open())
	{
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (escribir.is_open())
	{
		while (auxUsuario != nullptr)
		{
			if (escribir.bad())
			{
				MessageBox(NULL, "Ocurrió un error durante la escritura", "Error", MB_OK | MB_ICONERROR);
				return;
			}

			escribir.write((char*)auxUsuario, sizeof(NodoUsuario));
			auxUsuario = auxUsuario->sig;
		}

		escribir.close();
	}
}
void leerUsuarios()
{
	auxUsuario = iniUsuario;

	ifstream leer;
	leer.open("Usuarios.bin", ios::in | ios::binary);


	if (!leer.is_open())
	{
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (leer.is_open())
	{
		NodoUsuario* usuLeido = new NodoUsuario;

		while (!leer.read((char*)usuLeido, sizeof(NodoUsuario)).eof())
		{
			while (auxUsuario != nullptr && auxUsuario->sig != nullptr)
			{
				auxUsuario = auxUsuario->sig;
			}
			if (auxUsuario == nullptr)
			{
				iniUsuario = usuLeido;
				iniUsuario->sig = nullptr;
				iniUsuario->ant = nullptr;
				auxUsuario = iniUsuario;
			}
			else
			{
				auxUsuario->sig = usuLeido;
				auxUsuario->sig->ant = auxUsuario;
				auxUsuario = auxUsuario->sig;
				auxUsuario->sig = nullptr;
			}

			usuLeido = new NodoUsuario;
		}

		leer.close();
		delete usuLeido;
	}
}
#pragma region QuickSort
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
NodoUsuario* partition(NodoUsuario* l, NodoUsuario* h)
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
void _quickSort(NodoUsuario* l, NodoUsuario* h) // Función recursiva
{
	if (h != NULL && l != h && l != h->sig)
	{
		NodoUsuario* p = partition(l, h);
		_quickSort(l, p->ant);
		_quickSort(p->sig, h);
	}
}
void quickSort(NodoUsuario* head) // Función principal
{
	// Encuentra el último nodo
	NodoUsuario* h = lastNode(head);

	// Manda a llamar la función de QuickSort recursiva
	_quickSort(head, h);
}
void printList(NodoUsuario* head)
{
	while (head)
	{
		std::cout << head->dato->nick << "\n";
		head = head->sig;
	}
	std::cout << std::endl;
}
#pragma endregion
#pragma region Arbol
//Declaraciones de funciones
int countNodes(NodoUsuario* head);
NodoUsuario* sortedListToBSTRecur(NodoUsuario** head_ref, int n);
//Coonversiones
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
void BinaryTree2DoubleLinkedList(NodoUsuario* root, NodoUsuario** head)
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
	BinaryTree2DoubleLinkedList(root->ant, head);

	// Now convert this node
	if (ant == NULL)
		*head = root;
	else {
		root->ant = ant;
		ant->ant = root;
	}
	ant = root;

	//Se covierte ek subarbol derecho
	BinaryTree2DoubleLinkedList(root->sig, head);
}
//Operaciones
NodoUsuario* newNode(DatoUsuario* data)
{
	NodoUsuario* new_node = new NodoUsuario;
	new_node->dato = data;
	new_node->ant = new_node->sig = NULL;
	return (new_node);
}
struct NodoUsuario* insertTree(struct NodoUsuario* nodo, DatoUsuario* data)
{
	// Caso Base: Si está vacío, devuelve u nuevo nodo
	if (nodo == NULL)
		return newNode(data);

	//Se usa de forma recursiva para atravesar todo el arbol
	if ((_stricmp(data->nick, nodo->dato->nick) < 0))
		nodo->ant = insertTree(nodo->ant, data);
	else if (_stricmp(data->nick, nodo->dato->nick) > 0)
		nodo->sig = insertTree(nodo->sig, data);

	// Return the (unchanged) node pointer
	return nodo;
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
/*
//Imprime el arbol en preorden
void preOrder(NodoUsuario* node)
{
	if (node == NULL)
		return;
	std::cout << node->dato << " ";
	preOrder(node->ant);
	preOrder(node->sig);
}
//Imprime en inorden
void inorder(NodoUsuario* root)
{
	if (root != NULL) {
		inorder(root->ant);
		printf("%d ", root->dato->nick);
		inorder(root->sig);
	}
}
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
{
	if (iniVuelo == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniVuelo = new NodoVuelo;

		strcpy_s(iniVuelo->dato->origen, nueva->dato->origen);
		strcpy_s(iniVuelo->dato->destino, nueva->dato->destino);

		// ::: ANTERIOR ::: //
		//strcpy_s(iniEsp->claveChar, nueva->claveChar);
		//iniEsp->num = atoi(iniEsp->claveChar);

		strcpy_s(iniVuelo->dato->usuarioRegistro, nueva->dato->usuarioRegistro);

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

		strcpy_s(auxVuelo->dato->origen, nueva->dato->origen);
		strcpy_s(auxVuelo->dato->destino, nueva->dato->destino);

		// ::: ANTERIOR ::: //
		//strcpy_s(auxEsp->claveChar, nueva->claveChar);
		//auxEsp->num = atoi(auxEsp->claveChar);

		strcpy_s(auxVuelo->dato->usuarioRegistro, nueva->dato->usuarioRegistro);

		auxVuelo2 = auxVuelo;
		auxVuelo3 = auxVuelo;
		auxVuelo = iniVuelo;
	}

	MessageBox(NULL, "Se ha registrado la especialidad con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
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

			escribir.write((char*)auxVuelo, sizeof(NodoVuelo));
			auxVuelo = auxVuelo->sig;
		}

		escribir.close();
	}
}
void leerVuelos()
{
	auxVuelo = iniVuelo;

	ifstream leer("Vuelos.bin", ios::binary);

	if (!leer.is_open())
	{
		MessageBox(NULL, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (leer.is_open())
	{
		NodoVuelo* espLeida = new NodoVuelo;

		while (!leer.read((char*)espLeida, sizeof(NodoVuelo)).eof())
		{
			while (auxVuelo != nullptr && auxVuelo->sig != nullptr)
			{
				auxVuelo = auxVuelo->sig;
			}
			if (auxVuelo == nullptr)
			{
				iniVuelo = espLeida;
				iniVuelo->sig = nullptr;
				iniVuelo->ant = nullptr;
				auxVuelo = iniVuelo;
			}
			else
			{
				auxVuelo->sig = espLeida;
				auxVuelo->sig->ant = auxVuelo;
				auxVuelo = auxVuelo->sig;
				auxVuelo->sig = nullptr;
			}

			espLeida = new NodoVuelo;
		}

		leer.close();
		delete espLeida;
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
#pragma region QuickSort
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
NodoVuelo* partition(NodoVuelo* l, NodoVuelo* h)
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
void _quickSort(NodoVuelo* l, NodoVuelo* h) // Función recursiva
{
	if (h != NULL && l != h && l != h->sig)
	{
		NodoVuelo* p = partition(l, h);
		_quickSort(l, p->ant);
		_quickSort(p->sig, h);
	}
}
void quickSort(NodoVuelo* head) // Función principal
{
	// Encuentra el último nodo
	NodoVuelo* h = lastNode(head);

	// Manda a llamar la función de QuickSort recursiva
	_quickSort(head, h);
}
void printList(NodoVuelo* head)
{
	while (head)
	{
		std::cout << head->dato->num << "\n";
		head = head->sig;
	}
	std::cout << std::endl;
}
#pragma endregion
#pragma endregion

//Listas de Boletos (Medicos)
#pragma region Funciones de Listas Boletos (Medicos)
void nuevoBoleto(NodoBoleto* nuevoMed)
{
	if (pivote == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		pivote = new NodoBoleto;

		strcpy_s(pivote->dato->nombrePasajero, nuevoMed->dato->nombrePasajero);
		strcpy_s(pivote->dato->apellidoPPasajero, nuevoMed->dato->apellidoPPasajero);
		strcpy_s(pivote->dato->apellidoMPasajero, nuevoMed->dato->apellidoMPasajero);

		// Concatenación
		strcpy_s(pivote->dato->nombreCompPasajero, nuevoMed->dato->nombrePasajero);
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
		pivote->dato->pase = nuevoMed->dato->pase;
		//strcpy_s(pivote->diasChar, nuevoMed->diasChar);
		//pivote->diasNum = nuevoMed->diasNum;

		strcpy_s(pivote->dato->vuelo, nuevoMed->dato->vuelo);

		//strcpy_s(pivote->foto, nuevoMed->foto);

		strcpy_s(pivote->dato->usuarioRegistro, nuevoMed->dato->usuarioRegistro);

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
		//	auxMed2 = auxMed->ant;
		//	auxMed->ant = new medico;
		//	auxMed->ant->ant = auxMed2;
		//	auxMed->ant->sig = auxMed;
		//	auxMed = auxMed->ant;
		//	auxMed2->sig = auxMed;
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
				//	auxMed2 = auxMed->ant;
				//	auxMed->ant = new medico;
				//	auxMed->ant->ant = auxMed2;
				//	auxMed->ant->sig = auxMed;
				//	auxMed = auxMed->ant;
				//	auxMed2->sig = auxMed;
				//}
				//else
				if (nuevoMed->cedulaNum > auxMed->cedulaNum)
				{
					auxMed2 = auxMed->sig;
					auxMed->sig = new boleto;
					auxMed->sig->sig = auxMed2;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
					auxMed2->ant = auxMed;
				}
				else
				{
					auxMed2 = auxMed->ant;
					auxMed->ant = new boleto;
					auxMed->ant->ant = auxMed2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxMed2->sig = auxMed;
				}
			}
			else
			{
				//if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				//{
				//	auxMed2 = auxMed->ant;
				//	auxMed->ant = new medico;
				//	auxMed->ant->ant = auxMed2;
				//	auxMed->ant->sig = auxMed;
				//	auxMed = auxMed->ant;
				//	auxMed2->sig = auxMed;
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
					auxMed2 = auxMed->ant;
					auxMed->ant = new boleto;
					auxMed->ant->ant = auxMed2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxMed2->sig = auxMed;
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
				//	auxMed2 = auxMed->ant;
				//	auxMed->ant = new medico;
				//	auxMed->ant->ant = auxMed2;
				//	auxMed->ant->sig = auxMed;
				//	auxMed = auxMed->ant;
				//	auxMed2->sig = auxMed;
				//}
				//else 
				if (nuevoMed->cedulaNum < auxMed->cedulaNum)
				{
					auxMed2 = auxMed->ant;
					auxMed->ant = new boleto;
					auxMed->ant->ant = auxMed2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxMed2->sig = auxMed;
				}
				else
				{
					auxMed2 = auxMed->sig;
					auxMed->sig = new boleto;
					auxMed->sig->sig = auxMed2;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
					auxMed2->ant = auxMed;
				}
			}
			else
			{
				//if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				//{
				//	auxMed2 = auxMed->ant;
				//	auxMed->ant = new medico;
				//	auxMed->ant->ant = auxMed2;
				//	auxMed->ant->sig = auxMed;
				//	auxMed = auxMed->ant;
				//	auxMed2->sig = auxMed;
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
					auxMed2 = auxMed->sig;
					auxMed->sig = new boleto;
					auxMed->sig->sig = auxMed2;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
					auxMed2->ant = auxMed;
				}
			}

		}
		*/


		strcpy_s(auxBoleto->dato->nombrePasajero, nuevoMed->dato->nombrePasajero);
		strcpy_s(auxBoleto->dato->apellidoPPasajero, nuevoMed->dato->apellidoPPasajero);
		strcpy_s(auxBoleto->dato->apellidoMPasajero, nuevoMed->dato->apellidoMPasajero);

		// Concatenación
		strcpy_s(auxBoleto->dato->nombreCompPasajero, nuevoMed->dato->nombrePasajero);
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
		auxBoleto->dato->pase = nuevoMed->dato->pase;
		//strcpy_s(auxMed->diasChar, nuevoMed->diasChar);
		//auxMed->diasNum = nuevoMed->diasNum;

		strcpy_s(auxBoleto->dato->vuelo, nuevoMed->dato->vuelo);

		//strcpy_s(auxMed->foto, nuevoMed->foto);

		strcpy_s(auxBoleto->dato->usuarioRegistro, nuevoMed->dato->usuarioRegistro);

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
void eliminarBoleto(char medicoNom[60])
{
	NodoBoleto* start;
	auxBoleto = iniBoleto;

	if (auxBoleto == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxBoleto->sig != nullptr && strcmp(auxBoleto->dato->nombreCompPasajero, medicoNom) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxBoleto = auxBoleto->sig;
		}

		if (auxBoleto->sig == nullptr || strcmp(auxBoleto->dato->nombreCompPasajero, medicoNom) != 0)
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

			escribir.write((char*)auxBoleto, sizeof(NodoBoleto));
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

		

		strcpy_s(iniPasajero->dato->nacionalidad, nuevoPas->dato->nacionalidad);
		
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

		auxPasajero = iniPasajero;
		auxPasajero2 = auxPasajero;
		auxPasajero3 = auxPasajero;
	}
	else
	{
		auxPasajero = iniPasajero;

		strcpy_s(nuevoPas->dato->nombreComp, nuevoPas->dato->nombre);
		strcat_s(nuevoPas->dato->nombreComp, " ");
		strcat_s(nuevoPas->dato->nombreComp, nuevoPas->dato->apellidoP);
		strcat_s(nuevoPas->dato->nombreComp, " ");
		strcat_s(nuevoPas->dato->nombreComp, nuevoPas->dato->apellidoM);

		/*if (nuevoPas->cedulaNum == auxPas->cedulaNum)
		{
			auxPas2 = auxPas->ant;
			auxPas->ant = new medico;
			auxPas->ant->ant = auxPas2;
			auxPas->ant->sig = auxPas;
			auxPas = auxPas->ant;
			auxPas2->sig = auxPas;
		}
		else */if (strcmp(nuevoPas->dato->nombreComp, auxPasajero->dato->nombreComp) > 0)
		{
			while (auxPasajero->sig != nullptr && strcmp(nuevoPas->dato->nombreComp, auxPasajero->dato->nombreComp) > 0)
			{
				auxPasajero = auxPasajero->sig;
			}

			if (auxPasajero->ant != nullptr && auxPasajero->sig != nullptr)
			{

				/*if (nuevoPas->cedulaNum == auxPas->cedulaNum)
				{
					auxPas2 = auxPas->ant;
					auxPas->ant = new medico;
					auxPas->ant->ant = auxPas2;
					auxPas->ant->sig = auxPas;
					auxPas = auxPas->ant;
					auxPas2->sig = auxPas;
				}
				else */if (strcmp(nuevoPas->dato->nombreComp, auxPasajero->dato->nombreComp) > 0)
				{
					auxPasajero2 = auxPasajero->sig;
					auxPasajero->sig = new NodoPasajero;
					auxPasajero->sig->sig = auxPasajero2;
					auxPasajero->sig->ant = auxPasajero;
					auxPasajero = auxPasajero->sig;
					auxPasajero2->ant = auxPasajero;
				}
				else
				{
					auxPasajero2 = auxPasajero->ant;
					auxPasajero->ant = new NodoPasajero;
					auxPasajero->ant->ant = auxPasajero2;
					auxPasajero->ant->sig = auxPasajero;
					auxPasajero = auxPasajero->ant;
					auxPasajero2->sig = auxPasajero;
				}
			}
			else
			{
				/*if (nuevoPas->cedulaNum == auxPas->cedulaNum)
				{
					auxPas2 = auxPas->ant;
					auxPas->ant = new medico;
					auxPas->ant->ant = auxPas2;
					auxPas->ant->sig = auxPas;
					auxPas = auxPas->ant;
					auxPas2->sig = auxPas;
				}
				else */if (strcmp(nuevoPas->dato->nombreComp, auxPasajero->dato->nombreComp) > 0)
				{
					auxPasajero->sig = new NodoPasajero;
					auxPasajero->sig->sig = nullptr;
					auxPasajero->sig->ant = auxPasajero;
					auxPasajero = auxPasajero->sig;
				}
				else
				{
					auxPasajero2 = auxPasajero->ant;
					auxPasajero->ant = new NodoPasajero;
					auxPasajero->ant->ant = auxPasajero2;
					auxPasajero->ant->sig = auxPasajero;
					auxPasajero = auxPasajero->ant;
					auxPasajero2->sig = auxPasajero;
				}
			}
		}
		else
		{
			while (auxPasajero->ant != nullptr && strcmp(nuevoPas->dato->nombreComp, auxPasajero->dato->nombreComp) < 0)
			{
				auxPasajero = auxPasajero->ant;
			}

			if (auxPasajero->ant != nullptr && auxPasajero->sig != nullptr)
			{

				/*if (nuevoPas->cedulaNum == auxPas->cedulaNum)
				{
					auxPas2 = auxPas->ant;
					auxPas->ant = new medico;
					auxPas->ant->ant = auxPas2;
					auxPas->ant->sig = auxPas;
					auxPas = auxPas->ant;
					auxPas2->sig = auxPas;
				}
				else */if (strcmp(nuevoPas->dato->nombreComp, auxPasajero->dato->nombreComp) < 0)
				{
					auxPasajero2 = auxPasajero->ant;
					auxPasajero->ant = new NodoPasajero;
					auxPasajero->ant->ant = auxPasajero2;
					auxPasajero->ant->sig = auxPasajero;
					auxPasajero = auxPasajero->ant;
					auxPasajero2->sig = auxPasajero;
				}
				else
				{
					auxPasajero2 = auxPasajero->sig;
					auxPasajero->sig = new NodoPasajero;
					auxPasajero->sig->sig = auxPasajero2;
					auxPasajero->sig->ant = auxPasajero;
					auxPasajero = auxPasajero->sig;
					auxPasajero2->ant = auxPasajero;
				}
			}
			else
			{
				/*if (nuevoPas->cedulaNum == auxPas->cedulaNum)
				{
					auxPas2 = auxPas->ant;
					auxPas->ant = new medico;
					auxPas->ant->ant = auxPas2;
					auxPas->ant->sig = auxPas;
					auxPas = auxPas->ant;
					auxPas2->sig = auxPas;
				}
				else */if (strcmp(nuevoPas->dato->nombre, auxPasajero->dato->nombre) < 0)
				{
					auxPasajero->ant = new NodoPasajero;
					auxPasajero->ant->ant = nullptr;
					auxPasajero->ant->sig = auxPasajero;
					auxPasajero = auxPasajero->ant;
				}
				else
				{
					auxPasajero2 = auxPasajero->sig;
					auxPasajero->sig = new NodoPasajero;
					auxPasajero->sig->sig = auxPasajero2;
					auxPasajero->sig->ant = auxPasajero;
					auxPasajero = auxPasajero->sig;
					auxPasajero2->ant = auxPasajero;
				}
			}

		}

		strcpy_s(auxPasajero->dato->nombre, nuevoPas->dato->nombre);
		strcpy_s(auxPasajero->dato->apellidoP, nuevoPas->dato->apellidoP);
		strcpy_s(auxPasajero->dato->apellidoM, nuevoPas->dato->apellidoM);

		// Concatenación
		strcpy_s(auxPasajero->dato->nombreComp, auxPasajero->dato->nombre);
		strcat_s(auxPasajero->dato->nombreComp, " ");
		strcat_s(auxPasajero->dato->nombreComp, auxPasajero->dato->apellidoP);
		strcat_s(auxPasajero->dato->nombreComp, " ");
		strcat_s(auxPasajero->dato->nombreComp, auxPasajero->dato->apellidoM);

		

		strcpy_s(auxPasajero->dato->nacionalidad, nuevoPas->dato->nacionalidad);
		

		// ::: CAMBIO DE TIPO ::: //
		//strcpy_s(auxPas->fecha, nuevoPas->fecha);
		//strcpy_s(auxPas->genero, nuevoPas->genero);

		// ::: PASADOS ::: //
		//auxPas->telefonoNumP = atoi(auxPas->nacionalidad);
		//strcpy_s(auxPas->edadChar, nuevoPas->edadChar);
		//auxPas->edadNum = atoi(auxPas->edadChar);
		//strcpy_s(auxPas->ref, nuevoPas->ref);
		//strcpy_s(auxPas->pMedicoP, nuevoPas->pMedicoP);

		strcpy_s(auxPasajero->dato->usuarioRegistro, nuevoPas->dato->usuarioRegistro);

		while (auxPasajero->ant != nullptr)
		{
			auxPasajero = auxPasajero->ant;
		}

		iniPasajero = auxPasajero;

		auxPasajero = iniPasajero;
		auxPasajero2 = auxPasajero;
		auxPasajero3 = auxPasajero;
	}

	MessageBox(NULL, "Se ha registrado al paciente con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
}
void eliminarPasajero(char pacienteNom[60])
{
	NodoPasajero* start;
	auxPasajero = iniPasajero;

	if (auxPasajero == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxPasajero->sig != nullptr && strcmp(auxPasajero->dato->nombreComp, pacienteNom) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxPasajero = auxPasajero->sig;
		}

		if (auxPasajero->sig == nullptr || strcmp(auxPasajero->dato->nombreComp, pacienteNom) != 0)
		{
			MessageBox(0, "paciente no encontrado", "AVISO", MB_OK);
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

			MessageBox(0, "paciente eliminado", "AVISO", MB_OK);
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

			MessageBox(0, "paciente eliminado", "AVISO", MB_OK);

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

		escribir.write((char*)auxPasajero, sizeof(NodoPasajero));
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
#pragma region HeapSort
/*
void swapData(NodoVuelo* a, NodoVuelo* b) {
	DatoVuelo* temp = a->dato;
	a->dato = b->dato;
	b->dato = temp;
}
*/
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