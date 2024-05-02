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

using namespace std;

// Estructuras
#pragma region Structs
struct usuario
{
	usuario* ant;
	char nombreUsu[30];
	char nombre[30];
	char apellidoP[30];
	char apellidoM[30];
	char nombreComp[60];
	char clave[30];
	char foto[300];
	usuario* sig;
};

usuario* iniUsu, * auxUsu, * auxUsu2, * auxUsu3, * miUsuario = nullptr;

struct especialidad
{
	especialidad* ant;
	char nombreEsp[30];
	char descripcion[200];
	int claveNum;
	char claveChar[20];
	char nombreUsuE[30];
	especialidad* sig;
};

especialidad* iniEsp, * auxEsp, * auxEsp2, * auxEsp3 = nullptr;

struct medico
{
	medico* ant;
	char nombreMed[30];
	char apellidoPM[30];
	char apellidoMM[30];
	char nombreCompM[60];
	int cedulaNum;
	char cedulaChar[20];
	char especialidad[30];
	int numConsultorioNum;
	char numConsultorioChar[20];
	int hoararioNum;
	char hoararioChar[20];
	int telefonoNum;
	char telefonoChar[20];
	int diasNum;
	char diasChar[30];
	char foto[100];
	char nombreUsuM[30];
	medico* sig;
};

medico* pivote, * iniMed, * auxMed, * auxMed2, * auxMed3 = nullptr;

struct paciente
{
	paciente* ant;
	char nombrePas[30];
	char apellidoPP[30];
	char apellidoMP[30];
	char nombreCompP[60];
	char genero[20];
	int telefonoNumP;
	char telefonoCharP[20];
	char ref[100];
	char fecha[100];
	int edadNum;
	char edadChar[10];
	char pMedicoP[60];
	char nombreUsuP[30];
	paciente* sig;
};

paciente* iniPas, * auxPas, * auxPas2, * auxPas3 = nullptr;


#pragma region Structs Fijos

int i = 0;

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
BOOL CALLBACK cDialog5(HWND, UINT, WPARAM, LPARAM); // Registro Especialidades
BOOL CALLBACK cDialog6(HWND, UINT, WPARAM, LPARAM); // Lista Especialidades
BOOL CALLBACK cDialog7(HWND, UINT, WPARAM, LPARAM); // Registro Medicos
BOOL CALLBACK cDialog8(HWND, UINT, WPARAM, LPARAM); // Lista Medicos
BOOL CALLBACK cDialog9(HWND, UINT, WPARAM, LPARAM); // Reporte Medicos
BOOL CALLBACK cDialog10(HWND, UINT, WPARAM, LPARAM); // Registro Pecientes
BOOL CALLBACK cDialog11(HWND, UINT, WPARAM, LPARAM); // Lista Pacientes
BOOL CALLBACK cDialog12(HWND, UINT, WPARAM, LPARAM); // Reporte Pacientes
BOOL CALLBACK cDialog13(HWND, UINT, WPARAM, LPARAM); // Registro Citas
BOOL CALLBACK cDialog14(HWND, UINT, WPARAM, LPARAM); // Lista Citas
#pragma endregion

//Prototipos
#pragma region Prototipos

#pragma region Funciones de Listas Usuarios
void nuevoUsu(usuario* nuevo);
void eliminarUsu(char nomUsu[30]);
void escribirUsuario();
void leerUsuario();
#pragma endregion

#pragma region Funciones de Listas Especialidades
void nuevaEsp(especialidad* nueva);
void eliminarEsp(char nomEsp[30]);
void escribirEsp();
void leerEsp();
#pragma endregion

#pragma region Funciones de Listas Medicos
void nuevoMed(medico* nuevoMed);
void eliminarMed(char medicoNom[60]);
void escribirMed();
void leerMed();
void reporteMed();
#pragma endregion

#pragma region Funciones de Listas Pacientes
void nuevoPas(paciente* nuevoPas);
void eliminarPas(char paciente[60]);
void escribirPas();
void leerPas();
void reportePas();
#pragma endregion

//#pragma region Funciones de Arbol Medico
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
	leerUsuario();
	leerEsp();
	leerMed();
	leerPas();

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
	if (iniMed != nullptr)
	{
		auxMed3 = iniMed;
		float i = 0;

		while (auxMed3->sig != nullptr)
		{
			i++;
			auxMed3 = auxMed3->sig;
		}

		i++;
		i = i / 2;
		auxMed3 = iniMed;

		for (float i2 = 0; i2 < i; i2++)
		{
			auxMed3 = auxMed3->sig;
		}

		pivote = auxMed3;
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


	escribirUsuario();
	escribirEsp();
	escribirMed();
	escribirPas();
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
			char claveBuscar[15];

			GetDlgItemText(hwnd, IDC_EDIT1, usuBuscar, sizeof(usuBuscar));
			GetDlgItemText(hwnd, IDC_EDIT2, claveBuscar, sizeof(claveBuscar));

			auxUsu3 = iniUsu;

			if (iniUsu == nullptr)
			{
				MessageBox(NULL, "No hay usuarios registrados", "AVISO", MB_OK | MB_ICONERROR);
			}
			else {
				while (auxUsu3->sig != nullptr && strcmp(usuBuscar, auxUsu3->nombreUsu) != 0)
				{
					auxUsu3 = auxUsu3->sig;
				}
				if (auxUsu3->sig == nullptr && strcmp(usuBuscar, auxUsu3->nombreUsu) != 0)
				{
					MessageBox(NULL, "No se encontró el usuario.", "AVISO", MB_OK | MB_ICONERROR);
				}
				else
				{
					if (strcmp(claveBuscar, auxUsu3->clave) == 0)
					{
						miUsuario = auxUsu3;
						inicio = true;

						/*EndDialog(hwnd, 0);
						DialogBox(hInstGlobal, MAKEINTRESOURCE(105), hwnd, procVPrincipal);*/

						EndDialog(hwnd, 0);

						HWND hDialog3 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG3), 0, cDialog3);

						ShowWindow(hDialog3, SW_SHOW);
						UpdateWindow(hDialog3);
					}
					else
					{
						MessageBox(NULL, "Contraseña incorrecta", "AVISO", MB_OK | MB_ICONERROR);
					}

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
	default:
	{
		break;
	}

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

			auxUsu3 = iniUsu;

			while (auxUsu3/*->sig*/ != nullptr && strcmp(usuBuscar, auxUsu3->nombreUsu) != 0)
			{
				auxUsu3 = auxUsu3->sig;
			}
			if (auxUsu3/*->sig*/ == nullptr || strcmp(usuBuscar, auxUsu3->nombreUsu) != 0)
			{
				usuario* temp = new usuario;

				GetDlgItemText(hwnd, IDC_EDIT1, temp->nombreUsu, sizeof(temp->nombreUsu));
				GetDlgItemText(hwnd, IDC_EDIT2, temp->nombre, sizeof(temp->nombre));
				GetDlgItemText(hwnd, IDC_EDIT3, temp->apellidoP, sizeof(temp->apellidoP));
				GetDlgItemText(hwnd, IDC_EDIT4, temp->apellidoM, sizeof(temp->apellidoM));
				/*GetDlgItemText(hwnd, IDC_EDIT5, temp->clave, sizeof(temp->clave));*/
				/*GetDlgItemText(hwnd, IDC_EDIT6, temp->clave, sizeof(temp->clave));*/
				GetDlgItemText(hwnd, IDC_EDIT7, temp->clave, sizeof(temp->clave));

				strcpy_s(temp->foto, "");

				nuevoUsu(temp);

				SetDlgItemText(hwnd, IDC_EDIT1, "");
				SetDlgItemText(hwnd, IDC_EDIT2, "");
				SetDlgItemText(hwnd, IDC_EDIT3, "");
				SetDlgItemText(hwnd, IDC_EDIT4, "");
				SetDlgItemText(hwnd, IDC_EDIT5, "");
				SetDlgItemText(hwnd, IDC_EDIT6, "");
				SetDlgItemText(hwnd, IDC_EDIT7, "");

				auxUsu3 = iniUsu;

				while (auxUsu3->sig != nullptr && strcmp(usuBuscar, auxUsu3->nombreUsu) != 0)
				{
					auxUsu3 = auxUsu3->sig;
				}

				inicio = true;

				if (miUsuario == nullptr)
				{
					miUsuario = auxUsu3;

					EndDialog(hwnd, 0);

					HWND hDialog3 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG3), 0, cDialog3);

					ShowWindow(hDialog3, SW_SHOW);
					UpdateWindow(hDialog3);
				}
				else
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

		break;
	}
	default:
	{
		break;
	}

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
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreUsu);
			SetDlgItemText(hwnd, IDC_EDIT2, miUsuario->nombre);
			SetDlgItemText(hwnd, IDC_EDIT3, miUsuario->apellidoP);
			SetDlgItemText(hwnd, IDC_EDIT4, miUsuario->apellidoM);
			SetDlgItemText(hwnd, IDC_EDIT7, miUsuario->clave);
		}
		if (/*strcmp(miUsuario->foto, "") == 0 ||*/ miUsuario->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->foto, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE); //2
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
			strcpy_s(miUsuario->foto, zFile);

			GetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreUsu, sizeof(miUsuario->nombreUsu));
			GetDlgItemText(hwnd, IDC_EDIT2, miUsuario->nombre, sizeof(miUsuario->nombre));
			GetDlgItemText(hwnd, IDC_EDIT3, miUsuario->apellidoP, sizeof(miUsuario->apellidoP));
			GetDlgItemText(hwnd, IDC_EDIT4, miUsuario->apellidoM, sizeof(miUsuario->apellidoM));
			GetDlgItemText(hwnd, IDC_EDIT7, miUsuario->clave, sizeof(miUsuario->clave));

			// Concatenación
			strcpy_s(miUsuario->nombreComp, miUsuario->nombre);
			strcat_s(miUsuario->nombreComp, " ");
			strcat_s(miUsuario->nombreComp, miUsuario->apellidoP);
			strcat_s(miUsuario->nombreComp, " ");
			strcat_s(miUsuario->nombreComp, miUsuario->apellidoM);

			
			strcpy_s(miUsuario->foto, zFile);

			MessageBox(NULL, "Cambios guardados.", "AVISO", MB_OK | MB_ICONINFORMATION);

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
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreComp);
		}
		if (miUsuario->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		auxUsu2 = iniUsu;

		while (auxUsu2->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxUsu2->nombreUsu);
			auxUsu2 = auxUsu2->sig;
		}

		if (auxUsu2->sig == nullptr/* || auxUsu2->ant == nullptr*/)
		{
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxUsu2->nombreUsu);
			auxUsu2 = auxUsu2->sig;
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

				auxUsu2 = iniUsu;

				while (auxUsu2->sig != nullptr && strcmp(auxUsu2->nombreUsu, nombre) != 0)
				{
					auxUsu2 = auxUsu2->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT2, auxUsu2->nombreUsu);
				SetDlgItemText(hwnd, IDC_EDIT4, auxUsu2->nombreComp);

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
			if (auxUsu2 == nullptr)
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
					char usuario[30] = { 0 };
					int indice = 0;
					indice = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
					SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, indice, (LPARAM)usuario);

					if (strcmp(miUsuario->nombreUsu, usuario) == 0)
					{
						MessageBox(NULL, "El usuario que inicio sesion será eliminado, se cerrará la sesion.", "AVISO", MB_OK | MB_ICONINFORMATION);

						eliminarUsu(usuario);

						DestroyWindow(hwnd);
						PostQuitMessage(0);
					}
					else
					{
						eliminarUsu(usuario);

						SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_DELETESTRING, indice, 0);
						SetDlgItemText(hwnd, IDC_EDIT2, "");
						SetDlgItemText(hwnd, IDC_EDIT4, "");

						auxUsu2 = nullptr;
					}

					break;
				}

				case IDNO:
				{
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");

					auxUsu2 = nullptr;

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
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreComp);
		}
		if (miUsuario->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
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
			if (iniEsp == nullptr)
			{
				SetDlgItemText(hwnd, IDC_EDIT3, "1");
			}
			else
			{
				especialidad* tempNum = new especialidad;
				auxEsp3 = iniEsp;

				while (auxEsp3->sig != nullptr)
				{
					auxEsp3 = auxEsp3->sig;
				}

				/*auxEsp3 = auxEsp3->ant;*/

				tempNum->claveNum = auxEsp3->claveNum;

				tempNum->claveNum = tempNum->claveNum + 1;

				_itoa_s(tempNum->claveNum, tempNum->claveChar, 10);

				SetDlgItemText(hwnd, IDC_EDIT3, tempNum->claveChar);
			}

			break;
			
		}
		case IDC_BUTTON2: // Guardar
		{
			char espBuscar[30];

			GetDlgItemText(hwnd, IDC_EDIT1, espBuscar, sizeof(espBuscar));

			auxEsp2 = iniEsp;

			while (auxEsp2/*->sig*/ != nullptr && strcmp(espBuscar, auxEsp2->nombreEsp) != 0)
			{
				auxEsp2 = auxEsp2->sig;
			}

			if (auxEsp2/*->sig*/ == nullptr || strcmp(espBuscar, auxEsp2->nombreEsp) != 0)
			{
				especialidad* temp = new especialidad;

				GetDlgItemText(hwnd, IDC_EDIT2, temp->nombreEsp, sizeof(temp->nombreEsp));
				GetDlgItemText(hwnd, IDC_EDIT3, temp->claveChar, sizeof(temp->claveChar));
				GetDlgItemText(hwnd, IDC_EDIT4, temp->descripcion, sizeof(temp->descripcion));

				strcpy_s(temp->nombreUsuE, miUsuario->nombreUsu);

				nuevaEsp(temp);

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
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreComp);
		}
		if (miUsuario->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		auxEsp2 = iniEsp;

		if (iniEsp != nullptr)
		{
			while (auxEsp2->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxEsp2->nombreEsp);
				auxEsp2 = auxEsp2->sig;
			}

			if (auxEsp2->sig == nullptr/* || auxEsp2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST2, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxEsp2->nombreEsp);
				auxEsp2 = auxEsp2->sig;
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

				auxEsp2 = iniEsp;

				while (auxEsp2->sig != nullptr && strcmp(auxEsp2->nombreEsp, nombreEspC) != 0)
				{
					auxEsp2 = auxEsp2->sig;
				}

				SetDlgItemText(hwnd, IDC_EDIT2, auxEsp2->nombreEsp);
				SetDlgItemText(hwnd, IDC_EDIT3, auxEsp2->claveChar);
				SetDlgItemText(hwnd, IDC_EDIT4, auxEsp2->descripcion);

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
			if (auxEsp2 == nullptr)
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
			if (auxEsp2 == nullptr)
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

					eliminarEsp(especialidad);

					SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_DELETESTRING, indice2, 0);
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");*/

					auxEsp2 = nullptr;

					break;
				}

				case IDNO:
				{
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");

					auxEsp2 = nullptr;

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
			if (auxEsp2 == nullptr)
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

					auxEsp2 = nullptr;

					break;
				}

				case IDNO:
				{
					SetDlgItemText(hwnd, IDC_EDIT2, "");
					SetDlgItemText(hwnd, IDC_EDIT3, "");
					SetDlgItemText(hwnd, IDC_EDIT4, "");

					auxEsp2 = nullptr;

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

			//while (auxEsp3->sig != nullptr)
			//{
			//	auxEsp3 = auxEsp3->sig;
			//}

			//tempNum->claveNum = auxEsp3->claveNum;

			//tempNum->claveNum = tempNum->claveNum + 1;

			//_itoa_s(tempNum->claveNum, tempNum->claveChar, 10);

			//SetDlgItemText(hwnd, IDC_EDIT3, tempNum->claveChar);

			///*especialidad* tempNum = new especialidad;
			//auxEsp3 = auxEsp2;

			//tempNum->claveNum = auxEsp3->claveNum;

			//tempNum->claveNum = tempNum->claveNum + 1;

			//_itoa_s(tempNum->claveNum, tempNum->claveChar, 10);

			//SetDlgItemText(hwnd, IDC_EDIT3, tempNum->claveChar);*/

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
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreComp);
		}
		if (miUsuario->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
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

		auxEsp3 = iniEsp; // Especialidades

		if (iniEsp != nullptr)
		{
			while (auxEsp3->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxEsp3->nombreEsp);
				auxEsp3 = auxEsp3->sig;
			}

			if (auxEsp3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST9, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxEsp3->nombreEsp);
				auxEsp3 = auxEsp3->sig;
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

				auxEsp3 = iniEsp;

				while (auxEsp3->sig != nullptr && strcmp(auxEsp3->nombreEsp, num5) != 0)
				{
					auxEsp3 = auxEsp3->sig;

				}

				SetDlgItemText(hwnd, IDC_EDIT17, auxEsp3->nombreEsp);

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

			auxMed2 = pivote;

			// Campos
			medico* temp = new medico;

			GetDlgItemText(hwnd, IDC_EDIT2, temp->nombreMed, sizeof(temp->nombreMed));
			GetDlgItemText(hwnd, IDC_EDIT3, temp->apellidoPM, sizeof(temp->apellidoPM));
			GetDlgItemText(hwnd, IDC_EDIT4, temp->apellidoMM, sizeof(temp->apellidoMM));
			GetDlgItemText(hwnd, IDC_EDIT5, temp->cedulaChar, sizeof(temp->cedulaChar));
			GetDlgItemText(hwnd, IDC_EDIT8, temp->telefonoChar, sizeof(temp->telefonoChar));
			GetDlgItemText(hwnd, IDC_EDIT14, temp->numConsultorioChar, sizeof(temp->numConsultorioChar));
			GetDlgItemText(hwnd, IDC_EDIT15, temp->hoararioChar, sizeof(temp->hoararioChar));
			GetDlgItemText(hwnd, IDC_EDIT16, temp->diasChar, sizeof(temp->diasChar));
			GetDlgItemText(hwnd, IDC_EDIT17, temp->especialidad, sizeof(temp->especialidad));
			strcpy_s(temp->foto, zFile);

			if (strcmp(temp->foto, "") != 0 &
				strcmp(temp->nombreMed, "") != 0 &
				strcmp(temp->apellidoPM, "") != 0 &
				strcmp(temp->apellidoMM, "") != 0 &
				strcmp(temp->cedulaChar, "") != 0 &
				strcmp(temp->telefonoChar, "") != 0 &
				strcmp(temp->numConsultorioChar, "") != 0 &
				strcmp(temp->hoararioChar, "") != 0 &
				strcmp(temp->diasChar, "") != 0 &
				strcmp(temp->especialidad, "") != 0)
			{
				while (auxMed2/*->sig*/ != nullptr && strcmp(medBuscar, auxMed2->cedulaChar) != 0)
				{
					auxMed2 = auxMed2->sig;
				}

				if (auxMed2/*->sig*/ == nullptr || strcmp(medBuscar, auxMed2->cedulaChar) != 0)
				{
					/*medico* temp = new medico;*/

					GetDlgItemText(hwnd, IDC_EDIT2, temp->nombreMed, sizeof(temp->nombreMed));
					GetDlgItemText(hwnd, IDC_EDIT3, temp->apellidoPM, sizeof(temp->apellidoPM));
					GetDlgItemText(hwnd, IDC_EDIT4, temp->apellidoMM, sizeof(temp->apellidoMM));
					GetDlgItemText(hwnd, IDC_EDIT5, temp->cedulaChar, sizeof(temp->cedulaChar));
					GetDlgItemText(hwnd, IDC_EDIT8, temp->telefonoChar, sizeof(temp->telefonoChar));
					GetDlgItemText(hwnd, IDC_EDIT14, temp->numConsultorioChar, sizeof(temp->numConsultorioChar));
					GetDlgItemText(hwnd, IDC_EDIT15, temp->hoararioChar, sizeof(temp->hoararioChar));
					GetDlgItemText(hwnd, IDC_EDIT16, temp->diasChar, sizeof(temp->diasChar));
					GetDlgItemText(hwnd, IDC_EDIT17, temp->especialidad, sizeof(temp->especialidad));

					// Horario

					if (strcmp(temp->hoararioChar, "6am - 6pm") == 0)
					{
						temp->hoararioNum = 1;
					}
					else if (strcmp(temp->hoararioChar, "6pm - 12am") == 0)
					{
						temp->hoararioNum = 2;
					}
					else if (strcmp(temp->hoararioChar, "6am - 3pm") == 0)
					{
						temp->hoararioNum = 3;
					}
					else
					{
						temp->hoararioNum = 4;
					}

					// Días

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

					strcpy_s(temp->foto, zFile);
					strcpy_s(temp->nombreUsuM, miUsuario->nombreUsu);

					nuevoMed(temp);

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
				else
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
			if (auxEsp2 == nullptr)
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
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreComp);
		}
		if (miUsuario->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		auxMed3 = iniMed; // Medicos

		while (auxMed3->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxMed3->nombreCompM/*nombreCompM*/);
			auxMed3 = auxMed3->sig;
		}

		if (auxMed3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
		{
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxMed3->nombreCompM/*nombreCompM*/);
			auxMed3 = auxMed3->sig;
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

		auxEsp3 = iniEsp; // Especialidades

		if (iniEsp != nullptr)
		{
			while (auxEsp3->sig != nullptr)
			{
				SendDlgItemMessage(hwnd, IDC_LIST10, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxEsp3->nombreEsp);
				auxEsp3 = auxEsp3->sig;
			}

			if (auxEsp3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
			{
				SendDlgItemMessage(hwnd, IDC_LIST10, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxEsp3->nombreEsp);
				auxEsp3 = auxEsp3->sig;
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

				auxEsp3 = iniEsp;

				while (auxEsp3->sig != nullptr && strcmp(auxEsp3->nombreEsp, num5) != 0)
				{
					auxEsp3 = auxEsp3->sig;

				}

				SetDlgItemText(hwnd, IDC_EDIT18, auxEsp3->nombreEsp);

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

				auxMed3 = iniMed;

				while (auxMed3->sig != nullptr && strcmp(auxMed3->nombreCompM, num) != 0)
				{
					auxMed3 = auxMed3->sig;

				}

				SetDlgItemText(hwnd, IDC_EDIT2, auxMed3->nombreMed);
				SetDlgItemText(hwnd, IDC_EDIT3, auxMed3->apellidoPM);
				SetDlgItemText(hwnd, IDC_EDIT4, auxMed3->apellidoMM);

				SetDlgItemText(hwnd, IDC_EDIT5, auxMed3->cedulaChar);
				SetDlgItemText(hwnd, IDC_EDIT18, auxMed3->especialidad);

				SetDlgItemText(hwnd, IDC_EDIT8, auxMed3->telefonoChar);

				SetDlgItemText(hwnd, IDC_EDIT17, auxMed3->numConsultorioChar);
				SetDlgItemText(hwnd, IDC_EDIT15, auxMed3->hoararioChar);
				SetDlgItemText(hwnd, IDC_EDIT16, auxMed3->diasChar);

				strcpy_s(zFile, auxMed3->foto); //Inicializar zfile con la dirección de memoria del puntero foto

				HBITMAP bmp; //1
				bmp = (HBITMAP)LoadImage(NULL, auxMed3->foto, IMAGE_BITMAP, 120, 120, LR_LOADFROMFILE); //2
				SendDlgItemMessage(hwnd, IDC_BMP2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3 

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
			GetDlgItemText(hwnd, IDC_EDIT2, auxMed3->nombreMed, sizeof(auxMed3->nombreMed));
			GetDlgItemText(hwnd, IDC_EDIT3, auxMed3->apellidoPM, sizeof(auxMed3->apellidoPM));
			GetDlgItemText(hwnd, IDC_EDIT4, auxMed3->apellidoPM, sizeof(auxMed3->apellidoPM));

			GetDlgItemText(hwnd, IDC_EDIT5, auxMed3->cedulaChar, sizeof(auxMed3->cedulaChar));
			auxMed3->cedulaNum = atoi(auxMed3->cedulaChar);
			GetDlgItemText(hwnd, IDC_EDIT18, auxMed3->especialidad, sizeof(auxMed3->especialidad));
			
			GetDlgItemText(hwnd, IDC_EDIT8, auxMed3->telefonoChar, sizeof(auxMed3->telefonoChar));
			auxMed3->telefonoNum = atoi(auxMed3->telefonoChar);

			GetDlgItemText(hwnd, IDC_EDIT17, auxMed3->numConsultorioChar, sizeof(auxMed3->numConsultorioChar));
			auxMed3->numConsultorioNum = atoi(auxMed3->numConsultorioChar);
			GetDlgItemText(hwnd, IDC_EDIT15, auxMed3->hoararioChar, sizeof(auxMed3->hoararioChar));
			// Horario

			if (strcmp(auxMed3->hoararioChar, "6am - 6pm") == 0)
			{
				auxMed3->hoararioNum = 1;
			}
			else if (strcmp(auxMed3->hoararioChar, "6pm - 12am") == 0)
			{
				auxMed3->hoararioNum = 2;
			}
			else if (strcmp(auxMed3->hoararioChar, "6am - 3pm") == 0)
			{
				auxMed3->hoararioNum = 3;
			}
			else
			{
				auxMed3->hoararioNum = 4;
			}
			GetDlgItemText(hwnd, IDC_EDIT16, auxMed3->diasChar, sizeof(auxMed3->diasChar));
			// Días

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

			// Concatenación
			strcpy_s(auxMed3->nombreCompM, auxMed3->nombreMed);
			strcat_s(auxMed3->nombreCompM, " ");
			strcat_s(auxMed3->nombreCompM, auxMed3->apellidoPM);
			strcat_s(auxMed3->nombreCompM, " ");
			strcat_s(auxMed3->nombreCompM, auxMed3->apellidoPM);

			strcpy_s(auxMed3->foto,zFile);

			MessageBox(NULL, "Cambios guardados.", "AVISO", MB_OK | MB_ICONINFORMATION);

			break;
		}
		case IDC_BUTTON2: // Eliminar
		{
			if (auxMed3 == nullptr)
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

					eliminarMed(medico);

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

					auxMed3 = nullptr;

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

					auxMed3 = nullptr;

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
	default:
	{
		break;
	}

	}

	return false;  // Un callback siempre retorna falso
}

// Reporte Medicos
//BOOL CALLBACK cDialog9(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_INITDIALOG:
//	{
//		if (miUsuario != nullptr)
//		{
//			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreComp);
//		}
//
//
//		auxMed3 = iniMed; // Medicos
//
//		while (auxMed3->sig != nullptr)
//		{
//			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxMed3->nombreCompM/*nombreCompM*/);
//			auxMed3 = auxMed3->sig;
//		}
//
//		if (auxMed3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
//		{
//			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxMed3->nombreCompM/*nombreCompM*/);
//			auxMed3 = auxMed3->sig;
//		}
//
//		break;
//	}
//	case WM_COMMAND:
//	{
//		long opcion = LOWORD(wParam);
//		cMenu(hwnd, opcion);
//
//		switch (LOWORD(wParam))
//		{
//		case IDC_BUTTON1: // Generar
//		{
//			if (iniMed == nullptr)
//			{
//				MessageBox(NULL, "No hay medicos registrados.", "AVISO", MB_OK | MB_ICONERROR);
//			}
//			else
//			{
//				reporteMed();
//				MessageBox(NULL, "Reporte fue guardado en C:-Users-hp-Documents-UANL-Universidad 7-ED-Proyecto_Clinica-Proyecto_Clinica.", "AVISO", MB_OK | MB_ICONERROR);
//			}
//
//			break;
//		}
//		default:
//		{
//			break;
//		}
//
//		}
//
//		break;
//	}
//	default:
//	{
//		break;
//	}
//
//	}
//
//	return false;  // Un callback siempre retorna falso
//}

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

		auxMed3 = iniMed; // Medicos

		while (auxMed3->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxMed3->nombreCompM/*nombreCompM*/);
			auxMed3 = auxMed3->sig;
		}

		if (auxMed3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
		{
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxMed3->nombreCompM/*nombreCompM*/);
			auxMed3 = auxMed3->sig;
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

				auxMed3 = iniMed;

				while (auxMed3->sig != nullptr && strcmp(auxMed3->nombreCompM, num) != 0)
				{
					auxMed3 = auxMed3->sig;

				}

				SetDlgItemText(hwnd, IDC_EDIT8, auxMed3->nombreCompM);

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
			/*GetDlgItemText(hwnd, IDC_DATETIMEPICKER1, fecha, sizeof(fecha));*/

			char pasBuscar[60];

			GetDlgItemText(hwnd, IDC_EDIT2, pasBuscar, sizeof(pasBuscar));

			auxPas2 = iniPas;

			while (auxPas2/*->sig*/ != nullptr && strcmp(pasBuscar, auxPas2->nombreCompP) != 0)
			{
				auxPas2 = auxPas2->sig;
			}

			if (auxPas2/*->sig*/ == nullptr || strcmp(pasBuscar, auxPas2->nombreCompP) != 0)
			{
				paciente* temp = new paciente;

				GetDlgItemText(hwnd, IDC_EDIT2, temp->nombrePas, sizeof(temp->nombrePas));
				GetDlgItemText(hwnd, IDC_EDIT3, temp->apellidoPP, sizeof(temp->apellidoPP));
				GetDlgItemText(hwnd, IDC_EDIT4, temp->apellidoMP, sizeof(temp->apellidoMP));

				// Genero

				if (IsDlgButtonChecked(hwnd, IDC_RADIO1))
				{
					strcpy_s(temp->genero, "Masculino");
				}
				else
				{
					strcpy_s(temp->genero, "Femenino");
				}

				GetDlgItemText(hwnd, IDC_EDIT5, temp->telefonoCharP, sizeof(temp->telefonoCharP));
				GetDlgItemText(hwnd, IDC_EDIT6, temp->ref, sizeof(temp->ref));
				GetDlgItemText(hwnd, IDC_DATETIMEPICKER1, temp->fecha, sizeof(temp->fecha));
				GetDlgItemText(hwnd, IDC_EDIT7, temp->edadChar, sizeof(temp->edadChar));
				GetDlgItemText(hwnd, IDC_EDIT8, temp->pMedicoP, sizeof(temp->pMedicoP));

				strcpy_s(temp->nombreUsuP, miUsuario->nombreUsu);

				nuevoPas(temp);

				SetDlgItemText(hwnd, IDC_EDIT2, "");
				SetDlgItemText(hwnd, IDC_EDIT3, "");
				SetDlgItemText(hwnd, IDC_EDIT4, "");
				SetDlgItemText(hwnd, IDC_EDIT5, "");
				SetDlgItemText(hwnd, IDC_EDIT8, "");

				EndDialog(hwnd, 0);

				HWND hDialog10 = CreateDialog(hInstanceGlobal, MAKEINTRESOURCE(IDD_DIALOG10), 0, cDialog10);

				ShowWindow(hDialog10, SW_SHOW);
				UpdateWindow(hDialog10);
			}
			else
			{
				MessageBox(NULL, "Es posible que este paciente ya este registrado.", "AVISO", MB_OK | MB_ICONINFORMATION);
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
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreComp);
		}
		if (miUsuario->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
			SendDlgItemMessage(hwnd, IDC_BMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp); //3
		}

		auxMed3 = iniMed; // Medicos

		while (auxMed3->sig != nullptr)
		{
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxMed3->nombreCompM/*nombreCompM*/);
			auxMed3 = auxMed3->sig;
		}

		if (auxMed3->sig == nullptr/* || auxUsu2->ant == nullptr*/)
		{
			SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxMed3->nombreCompM/*nombreCompM*/);
			auxMed3 = auxMed3->sig;
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

// Registro Boletos
BOOL CALLBACK cDialog12(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

		//auxPas3 = iniPas;

		//while (auxPas3->sig != nullptr)
		//{
		//	SendDlgItemMessage(hwnd, IDC_LIST3, LB_ADDSTRING, (WPARAM)0, (LPARAM)auxPas3->nombreCompP/*nombreCompM*/);
		//	auxPas3 = auxPas3->sig;
		//}

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
			if (iniPas == nullptr)
			{
				MessageBox(NULL, "No hay pacientes registrados.", "AVISO", MB_OK | MB_ICONERROR);
			}
			else
			{
				reportePas();
				MessageBox(NULL, "Reporte fue guardado en C:-Users-hp-Documents-UANL-Universidad 7-ED-Proyecto_Clinica-Proyecto_Clinica.", "AVISO", MB_OK | MB_ICONEXCLAMATION);
			}

			break;

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

// Lista Boletos
BOOL CALLBACK cDialog13(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
			SetDlgItemText(hwnd, IDC_EDIT1, miUsuario->nombreComp);
		}
		if (miUsuario->foto != nullptr)
		{
			strcpy_s(zFile, miUsuario->foto); //Inicializar zfile con la dirección de memoria del puntero foto

			HBITMAP bmp; //1
			bmp = (HBITMAP)LoadImage(NULL, miUsuario->foto, IMAGE_BITMAP, 70, 70, LR_LOADFROMFILE); //2
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
#pragma region funciones

//Funciones de Listas de Usuarios
#pragma region Funciones de Listas Usuarios

void nuevoUsu(usuario* nuevo)
{
	if (iniUsu == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniUsu = new usuario;

		strcpy_s(iniUsu->nombreUsu, nuevo->nombreUsu);
		strcpy_s(iniUsu->nombre, nuevo->nombre);
		strcpy_s(iniUsu->apellidoP, nuevo->apellidoP);
		strcpy_s(iniUsu->apellidoM, nuevo->apellidoM);
		strcpy_s(iniUsu->clave, nuevo->clave);

		// Concatenación
		strcpy_s(iniUsu->nombreComp, nuevo->nombre);
		strcat_s(iniUsu->nombreComp, " ");
		strcat_s(iniUsu->nombreComp, iniUsu->apellidoP);
		strcat_s(iniUsu->nombreComp, " ");
		strcat_s(iniUsu->nombreComp, iniUsu->apellidoM);

		strcpy_s(iniUsu->foto, nuevo->foto);

		iniUsu->sig = nullptr;
		iniUsu->ant = nullptr;

		auxUsu2 = auxUsu;
		auxUsu3 = auxUsu;
		auxUsu = iniUsu;
	}
	else
	{
		auxUsu = iniUsu;

		while (auxUsu->sig != nullptr)
		{
			auxUsu = auxUsu->sig;
		}

		auxUsu->sig = new usuario;
		auxUsu->sig->sig = nullptr;
		auxUsu->sig->ant = auxUsu;
		auxUsu = auxUsu->sig;

		strcpy_s(auxUsu->nombreUsu, nuevo->nombreUsu);
		strcpy_s(auxUsu->nombre, nuevo->nombre);
		strcpy_s(auxUsu->apellidoP, nuevo->apellidoP);
		strcpy_s(auxUsu->apellidoM, nuevo->apellidoM);
		strcpy_s(auxUsu->clave, nuevo->clave);

		// Concatenación
		strcpy_s(auxUsu->nombreComp, nuevo->nombre);
		strcat_s(auxUsu->nombreComp, " ");
		strcat_s(auxUsu->nombreComp, auxUsu->apellidoP);
		strcat_s(auxUsu->nombreComp, " ");
		strcat_s(auxUsu->nombreComp, auxUsu->apellidoM);

		strcpy_s(auxUsu->foto, nuevo->foto);

		auxUsu2 = auxUsu;
		auxUsu3 = auxUsu;
		auxUsu = iniUsu;
	}

	MessageBox(NULL, "Se ha registrado el usuario con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
}

void eliminarUsu(char nomUsu[30])
{
	usuario* start;
	auxUsu = iniUsu;

	if (auxUsu == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxUsu->sig != nullptr && strcmp(auxUsu->nombreUsu, nomUsu) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxUsu = auxUsu->sig;
		}
		if (auxUsu->sig == nullptr && strcmp(auxUsu->nombreUsu, nomUsu) != 0)
		{
			MessageBox(0, "Usuario no encontrado", "AVISO", MB_OK);
		}
		else if (auxUsu == iniUsu)
		{	//El nodo es el primero 

			if (auxUsu->sig == nullptr)
			{ //Si es el primero y unico nodo
				//delete auxEsp;		//Eliminamos el primer nodo
				//inicio = nullptr;
				//auxEsp = inicio;

				iniUsu = nullptr;
				delete auxUsu;

				auxUsu = iniUsu;
				auxUsu2 = auxUsu;
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

				start = iniUsu->sig;
				auxUsu->sig->ant = nullptr;
				delete auxUsu;
				auxUsu = start;
				auxUsu->ant = nullptr;

				auxUsu = iniUsu;
				auxUsu2 = auxUsu;
				/*auxUsu3 = auxUsu;*/
			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);
		}
		else
		{

			if (auxUsu->sig == nullptr)
			{ //Si el nodo es el último
				auxUsu->ant->sig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete auxUsu;

				auxUsu = iniUsu;
				auxUsu2 = auxUsu;
				/*auxUsu3 = auxUsu;*/
			}
			else
			{ //Si es cualquier nodo que no sea el inicio o el último
				auxUsu->sig->ant = auxUsu->ant;
				auxUsu->ant->sig = auxUsu->sig;
				delete auxUsu;

				auxUsu = iniUsu;
				auxUsu2 = auxUsu;
				/*auxUsu3 = auxUsu;*/ //Para que auxEsp no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "Usuario eliminado", "AVISO", MB_OK);

		}
	}

}

void escribirUsuario()
{
	auxUsu = iniUsu;

	ofstream escribir("Info de Usuarios.bin", ios::binary | ios::out | ios::trunc);
	//escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\Usuarios.txt", ios::out | ios::trunc);

	if (escribir.is_open())
	{
		while (auxUsu != nullptr)
		{
			escribir.write((char*)auxUsu, sizeof(usuario));
			auxUsu = auxUsu->sig;
		}

		escribir.close();
	}

	/*auxUsu = iniUsu;

	if (auxUsu == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		ofstream escribir;
		escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 5\\ProgAv\\Proyecto Final\\Segundo Avance\\Segundo Avance\\Segundo Avance\\Usuarios.bin", ios::out | ios::binary | ios::trunc);

		if (escribir.is_open())
		{
			while (auxUsu != nullptr)
			{
				escribir.write((char*)auxUsu, sizeof(usuario));
				auxUsu = auxUsu->sig;
			}

			escribir.close();
		}
	}*/
}

void leerUsuario()
{
	auxUsu = iniUsu;

	ifstream leer("Info de Usuarios.bin", ios::binary);
	//leer.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\Usuarios.txt", ios::in);

	if (leer.is_open())
	{
		usuario* usuLeido = new usuario;

		while (!leer.read((char*)usuLeido, sizeof(usuario)).eof())
		{

			while (auxUsu != nullptr && auxUsu->sig != nullptr)
			{
				auxUsu = auxUsu->sig;
			}
			if (auxUsu == nullptr)
			{
				iniUsu = usuLeido;
				iniUsu->sig = nullptr;
				iniUsu->ant = nullptr;
				auxUsu = iniUsu;
			}
			else
			{
				auxUsu->sig = usuLeido;
				auxUsu->sig->ant = auxUsu;
				auxUsu = auxUsu->sig;
				auxUsu->sig = nullptr;
				/*auxUsu->sig = usuLeido;
				auxUsu->ant = auxUsu;
				auxUsu = auxUsu->sig;
				auxUsu->sig = nullptr;*/
			}

			usuLeido = new usuario;
		}

		leer.close();
		delete usuLeido;
	}
}

#pragma endregion

//Funciones de Listas de Especialidades
#pragma region Funciones de Listas Especialidades

void nuevaEsp(especialidad* nueva)
{
	if (iniEsp == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniEsp = new especialidad;

		strcpy_s(iniEsp->nombreEsp, nueva->nombreEsp);
		strcpy_s(iniEsp->descripcion, nueva->descripcion);

		strcpy_s(iniEsp->claveChar, nueva->claveChar);
		iniEsp->claveNum = atoi(iniEsp->claveChar);

		strcpy_s(iniEsp->nombreUsuE, nueva->nombreUsuE);

		iniEsp->sig = nullptr;
		iniEsp->ant = nullptr;

		auxEsp2 = auxEsp;
		auxEsp3 = auxEsp;
		auxEsp = iniEsp;
	}
	else
	{
		auxEsp = iniEsp;

		while (auxEsp->sig != nullptr)
		{
			auxEsp = auxEsp->sig;
		}

		auxEsp->sig = new especialidad;
		auxEsp->sig->sig = nullptr;
		auxEsp->sig->ant = auxEsp;
		auxEsp = auxEsp->sig;

		strcpy_s(auxEsp->nombreEsp, nueva->nombreEsp);
		strcpy_s(auxEsp->descripcion, nueva->descripcion);

		strcpy_s(auxEsp->claveChar, nueva->claveChar);
		auxEsp->claveNum = atoi(auxEsp->claveChar);

		strcpy_s(auxEsp->nombreUsuE, nueva->nombreUsuE);

		auxEsp2 = auxEsp;
		auxEsp3 = auxEsp;
		auxEsp = iniEsp;
	}

	MessageBox(NULL, "Se ha registrado la especialidad con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
}

void eliminarEsp(char nomEsp[30])
{
	especialidad* start;
	auxEsp = iniEsp;

	if (auxEsp == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxEsp->sig != nullptr && strcmp(auxEsp->nombreEsp, nomEsp) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxEsp = auxEsp->sig;
		}
		if (auxEsp->sig == nullptr && strcmp(auxEsp->nombreEsp, nomEsp) != 0)
		{
			MessageBox(0, "Especialidad no encontrada", "AVISO", MB_OK);
		}
		else if (auxEsp == iniEsp)
		{	//El nodo es el primero 

			if (auxEsp->sig == nullptr)
			{ //Si es el primero y unico nodo
				//delete auxEsp;		//Eliminamos el primer nodo
				//inicio = nullptr;
				//auxEsp = inicio;

				iniEsp = nullptr;
				delete auxEsp;

				auxEsp = iniEsp;
				auxEsp2 = auxEsp;
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

				start = iniEsp->sig;
				auxEsp->sig->ant = nullptr;
				delete auxEsp;
				auxEsp = start;
				auxEsp->ant = nullptr;

				auxEsp2 = auxEsp;
				iniEsp = auxEsp;
			}

			MessageBox(0, "Especialidad eliminada", "AVISO", MB_OK);
		}
		else
		{

			if (auxEsp->sig == nullptr)
			{ //Si el nodo es el último
				auxEsp->ant->sig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete auxEsp;

				auxEsp = iniEsp;
				auxEsp2 = auxEsp;
			}
			else
			{ //Si es cualquier nodo que no sea el inicio o el último
				auxEsp->sig->ant = auxEsp->ant;
				auxEsp->ant->sig = auxEsp->sig;
				delete auxEsp;

				auxEsp2 = auxEsp;
				auxEsp = iniEsp; //Para que auxEsp no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "Especialidad eliminada", "AVISO", MB_OK);

		}
	}

}

void escribirEsp()
{
	auxEsp = iniEsp;

	ofstream escribir;
	escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\Especialidades.bin", ios::out | ios::binary | ios::trunc);

	if (escribir.is_open())
	{
		while (auxEsp != nullptr)
		{
			escribir.write((char*)auxEsp, sizeof(especialidad));
			auxEsp = auxEsp->sig;
		}

		escribir.close();
	}

	/*auxEsp = iniEsp;

	if (auxEsp == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		ofstream escribir;
		escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 5\\ProgAv\\Proyecto Final\\Segundo Avance\\Segundo Avance\\Segundo Avance\\Usuarios.bin", ios::out | ios::binary | ios::trunc);

		if (escribir.is_open())
		{
			while (auxEsp != nullptr)
			{
				escribir.write((char*)auxEsp, sizeof(usuario));
				auxEsp = auxEsp->sig;
			}

			escribir.close();
		}
	}*/
}

void leerEsp()
{
	auxEsp = iniEsp;

	ifstream leer;
	leer.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\Especialidades.bin", ios::in | ios::binary);

	if (leer.is_open())
	{
		especialidad* espLeida = new especialidad;

		while (!leer.read((char*)espLeida, sizeof(especialidad)).eof())
		{

			while (auxEsp != nullptr && auxEsp->sig != nullptr)
			{
				auxEsp = auxEsp->sig;
			}
			if (auxEsp == nullptr)
			{
				iniEsp = espLeida;
				iniEsp->sig = nullptr;
				iniEsp->ant = nullptr;
				auxEsp = iniEsp;
			}
			else
			{
				auxEsp->sig = espLeida;
				auxEsp->sig->ant = auxEsp;
				auxEsp = auxEsp->sig;
				auxEsp->sig = nullptr;
				/*auxEsp->sig = espLeida;
				auxEsp->ant = auxEsp;
				auxEsp = auxEsp->sig;
				auxEsp->sig = nullptr;*/
			}

			espLeida = new especialidad;
		}

		leer.close();
		delete espLeida;
	}
}

#pragma endregion

//Funciones de Listas de Medicos
#pragma region Funciones de Listas Medicos

void nuevoMed(medico* nuevoMed)
{
	if (pivote == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		pivote = new medico;

		strcpy_s(pivote->nombreMed, nuevoMed->nombreMed);
		strcpy_s(pivote->apellidoPM, nuevoMed->apellidoPM);
		strcpy_s(pivote->apellidoMM, nuevoMed->apellidoMM);

		// Concatenación
		strcpy_s(pivote->nombreCompM, nuevoMed->nombreMed);
		strcat_s(pivote->nombreCompM, " ");
		strcat_s(pivote->nombreCompM, pivote->apellidoPM);
		strcat_s(pivote->nombreCompM, " ");
		strcat_s(pivote->nombreCompM, pivote->apellidoMM);

		strcpy_s(pivote->cedulaChar, nuevoMed->cedulaChar);
		pivote->cedulaNum = atoi(pivote->cedulaChar);
		strcpy_s(pivote->numConsultorioChar, nuevoMed->numConsultorioChar);
		pivote->numConsultorioNum = atoi(pivote->numConsultorioChar);
		strcpy_s(pivote->telefonoChar, nuevoMed->telefonoChar);
		pivote->telefonoNum = atoi(pivote->telefonoChar);

		strcpy_s(pivote->hoararioChar, nuevoMed->hoararioChar);
		pivote->hoararioNum = nuevoMed->hoararioNum;
		strcpy_s(pivote->diasChar, nuevoMed->diasChar);
		pivote->diasNum = nuevoMed->diasNum;

		strcpy_s(pivote->especialidad, nuevoMed->especialidad);

		strcpy_s(pivote->foto, nuevoMed->foto);

		strcpy_s(pivote->nombreUsuM, nuevoMed->nombreUsuM);

		pivote->sig = nullptr;
		pivote->ant = nullptr;

		auxMed = pivote;
		auxMed2 = auxMed;
		auxMed3 = auxMed;
		iniMed = pivote;
	}
	else
	{
		auxMed = pivote;
		nuevoMed->cedulaNum = atoi(nuevoMed->cedulaChar);

		/*if (nuevoMed->cedulaNum == auxMed->cedulaNum)
		{
			auxMed2 = auxMed->ant;
			auxMed->ant = new medico;
			auxMed->ant->ant = auxMed2;
			auxMed->ant->sig = auxMed;
			auxMed = auxMed->ant;
			auxMed2->sig = auxMed;
		}
		else */if (nuevoMed->cedulaNum > auxMed->cedulaNum)
		{
			while (auxMed->sig != nullptr && nuevoMed->cedulaNum > auxMed->cedulaNum)
			{
				auxMed = auxMed->sig;
			}

			if (auxMed->ant != nullptr && auxMed->sig != nullptr)
			{

				/*if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				{
					auxMed2 = auxMed->ant;
					auxMed->ant = new medico;
					auxMed->ant->ant = auxMed2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxMed2->sig = auxMed;
				}
				else */if (nuevoMed->cedulaNum > auxMed->cedulaNum)
				{
					auxMed2 = auxMed->sig;
					auxMed->sig = new medico;
					auxMed->sig->sig = auxMed2;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
					auxMed2->ant = auxMed;
				}
				else
				{
					auxMed2 = auxMed->ant;
					auxMed->ant = new medico;
					auxMed->ant->ant = auxMed2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxMed2->sig = auxMed;
				}
			}
			else
			{
				/*if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				{
					auxMed2 = auxMed->ant;
					auxMed->ant = new medico;
					auxMed->ant->ant = auxMed2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxMed2->sig = auxMed;
				}
				else */if (nuevoMed->cedulaNum > auxMed->cedulaNum)
				{
					auxMed->sig = new medico;
					auxMed->sig->sig = nullptr;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
				}
				else
				{
					auxMed2 = auxMed->ant;
					auxMed->ant = new medico;
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

				/*if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				{
					auxMed2 = auxMed->ant;
					auxMed->ant = new medico;
					auxMed->ant->ant = auxMed2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxMed2->sig = auxMed;
				}
				else */if (nuevoMed->cedulaNum < auxMed->cedulaNum)
				{
					auxMed2 = auxMed->ant;
					auxMed->ant = new medico;
					auxMed->ant->ant = auxMed2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxMed2->sig = auxMed;
				}
				else
				{
					auxMed2 = auxMed->sig;
					auxMed->sig = new medico;
					auxMed->sig->sig = auxMed2;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
					auxMed2->ant = auxMed;
				}
			}
			else
			{
				/*if (nuevoMed->cedulaNum == auxMed->cedulaNum)
				{
					auxMed2 = auxMed->ant;
					auxMed->ant = new medico;
					auxMed->ant->ant = auxMed2;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
					auxMed2->sig = auxMed;
				}
				else */if (nuevoMed->cedulaNum < auxMed->cedulaNum)
				{
					auxMed->ant = new medico;
					auxMed->ant->ant = nullptr;
					auxMed->ant->sig = auxMed;
					auxMed = auxMed->ant;
				}
				else
				{
					auxMed2 = auxMed->sig;
					auxMed->sig = new medico;
					auxMed->sig->sig = auxMed2;
					auxMed->sig->ant = auxMed;
					auxMed = auxMed->sig;
					auxMed2->ant = auxMed;
				}
			}
			
		}

		strcpy_s(auxMed->nombreMed, nuevoMed->nombreMed);
		strcpy_s(auxMed->apellidoPM, nuevoMed->apellidoPM);
		strcpy_s(auxMed->apellidoMM, nuevoMed->apellidoMM);

		// Concatenación
		strcpy_s(auxMed->nombreCompM, nuevoMed->nombreMed);
		strcat_s(auxMed->nombreCompM, " ");
		strcat_s(auxMed->nombreCompM, auxMed->apellidoPM);
		strcat_s(auxMed->nombreCompM, " ");
		strcat_s(auxMed->nombreCompM, auxMed->apellidoMM);

		strcpy_s(auxMed->cedulaChar, nuevoMed->cedulaChar);
		auxMed->cedulaNum = atoi(auxMed->cedulaChar);
		strcpy_s(auxMed->numConsultorioChar, nuevoMed->numConsultorioChar);
		auxMed->numConsultorioNum = atoi(auxMed->numConsultorioChar);
		strcpy_s(auxMed->telefonoChar, nuevoMed->telefonoChar);
		auxMed->telefonoNum = atoi(auxMed->telefonoChar);

		strcpy_s(auxMed->hoararioChar, nuevoMed->hoararioChar);
		auxMed->hoararioNum = nuevoMed->hoararioNum;
		strcpy_s(auxMed->diasChar, nuevoMed->diasChar);
		auxMed->diasNum = nuevoMed->diasNum;

		strcpy_s(auxMed->especialidad, nuevoMed->especialidad);

		strcpy_s(auxMed->foto, nuevoMed->foto);

		strcpy_s(auxMed->nombreUsuM, nuevoMed->nombreUsuM);

		while (auxMed->ant != nullptr)
		{
			auxMed = auxMed->ant;
		}

		iniMed = auxMed;

		auxMed = pivote;
		auxMed2 = auxMed;
		auxMed3 = auxMed;
	}

	MessageBox(NULL, "Se ha registrado al medico con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
}

void eliminarMed(char medicoNom[60])
{
	medico* start;
	auxMed = iniMed;

	if (auxMed == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxMed->sig != nullptr && strcmp(auxMed->nombreCompM, medicoNom) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxMed = auxMed->sig;
		}

		if (auxMed->sig == nullptr || strcmp(auxMed->nombreCompM, medicoNom) != 0)
		{
			MessageBox(0, "Medico no encontrado", "AVISO", MB_OK);
		}
		
		if (auxMed == pivote)
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

		if (auxMed == iniMed)
		{	//El nodo es el primero 

			if (auxMed->sig == nullptr)
			{ //Si es el primero y unico nodo
				//delete auxMed;		//Eliminamos el primer nodo
				//inicio = nullptr;
				//auxMed = inicio;

				iniMed = nullptr;
				delete auxMed;

				auxMed = iniMed;
				auxMed2 = auxMed;
				auxMed3 = auxMed;
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

				start = iniMed->sig;
				auxMed->sig->ant = nullptr;
				delete auxMed;
				auxMed = start;
				auxMed->ant = nullptr;

				auxMed2 = auxMed;
				auxMed3 = auxMed;
				iniMed = auxMed;
			}

			MessageBox(0, "Medico eliminado", "AVISO", MB_OK);
		}
		else
		{

			if (auxMed->sig == nullptr)
			{ //Si el nodo es el último
				auxMed->ant->sig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete auxMed;

				auxMed = iniMed;
				auxMed2 = auxMed;
			}
			else
			{ //Si es cualquier nodo que no sea el inicio o el último
				auxMed->sig->ant = auxMed->ant;
				auxMed->ant->sig = auxMed->sig;
				delete auxMed;

				auxMed2 = auxMed;
				auxMed3 = auxMed;
				auxMed = iniMed; //Para que auxMed no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "Medico eliminado", "AVISO", MB_OK);

		}
	}

}

void escribirMed()
{
	auxMed = iniMed;

	ofstream escribir;
	escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\Medicos.bin", ios::out | ios::binary | ios::trunc);

	if (escribir.is_open())
	{
		while (auxMed != nullptr)
		{
			escribir.write((char*)auxMed, sizeof(medico));
			auxMed = auxMed->sig;
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

void leerMed()
{
	auxMed = iniMed;

	ifstream leer;
	leer.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\Medicos.bin", ios::in | ios::binary);

	if (leer.is_open())
	{
		medico* medLeido = new medico;

		while (!leer.read((char*)medLeido, sizeof(medico)).eof())
		{

			while (auxMed != nullptr && auxMed->sig != nullptr)
			{
				auxMed = auxMed->sig;
			}
			if (auxMed == nullptr)
			{
				iniMed = medLeido;
				iniMed->sig = nullptr;
				iniMed->ant = nullptr;
				auxMed = iniMed;
			}
			else
			{
				auxMed->sig = medLeido;
				auxMed->sig->ant = auxMed;
				auxMed = auxMed->sig;
				auxMed->sig = nullptr;
				/*auxMed->sig = espLeida;
				auxMed->ant = auxMed;
				auxMed = auxMed->sig;
				auxMed->sig = nullptr;*/
			}

			medLeido = new medico;
		}

		leer.close();
		delete medLeido;
	}
}

void reporteMed()
{
	auxMed = iniMed;

	ofstream escribir;
	escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\Medicos.txt", ios::out| ios::trunc);

	if (escribir.is_open())
	{
		while (auxMed != nullptr)
		{
			escribir.write((char*)auxMed, sizeof(medico));
			auxMed = auxMed->sig;
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

#pragma endregion

//Funciones de Listas de Pacientes
#pragma region Funciones de Listas Pacientes

void nuevoPas(paciente* nuevoPas)
{
	if (iniPas == nullptr)
	{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
		iniPas = new paciente;

		strcpy_s(iniPas->nombrePas, nuevoPas->nombrePas);
		strcpy_s(iniPas->apellidoPP, nuevoPas->apellidoPP);
		strcpy_s(iniPas->apellidoMP, nuevoPas->apellidoMP);

		// Concatenación
		strcpy_s(iniPas->nombreCompP, nuevoPas->nombrePas);
		strcat_s(iniPas->nombreCompP, " ");
		strcat_s(iniPas->nombreCompP, iniPas->apellidoPP);
		strcat_s(iniPas->nombreCompP, " ");
		strcat_s(iniPas->nombreCompP, iniPas->apellidoMP);

		strcpy_s(iniPas->genero, nuevoPas->genero);

		strcpy_s(iniPas->telefonoCharP, nuevoPas->telefonoCharP);
		iniPas->telefonoNumP = atoi(iniPas->telefonoCharP);

		strcpy_s(iniPas->ref, nuevoPas->ref);
		strcpy_s(iniPas->fecha, nuevoPas->fecha);

		strcpy_s(iniPas->edadChar, nuevoPas->edadChar);
		iniPas->edadNum = atoi(iniPas->edadChar);

		strcpy_s(iniPas->pMedicoP, nuevoPas->pMedicoP);

		strcpy_s(iniPas->nombreUsuP, nuevoPas->nombreUsuP);

		iniPas->sig = nullptr;
		iniPas->ant = nullptr;

		auxPas = iniPas;
		auxPas2 = auxPas;
		auxPas3 = auxPas;
	}
	else
	{
		auxPas = iniPas;

		strcpy_s(nuevoPas->nombreCompP, nuevoPas->nombrePas);
		strcat_s(nuevoPas->nombreCompP, " ");
		strcat_s(nuevoPas->nombreCompP, nuevoPas->apellidoPP);
		strcat_s(nuevoPas->nombreCompP, " ");
		strcat_s(nuevoPas->nombreCompP, nuevoPas->apellidoMP);

		/*if (nuevoPas->cedulaNum == auxPas->cedulaNum)
		{
			auxPas2 = auxPas->ant;
			auxPas->ant = new medico;
			auxPas->ant->ant = auxPas2;
			auxPas->ant->sig = auxPas;
			auxPas = auxPas->ant;
			auxPas2->sig = auxPas;
		}
		else */if (strcmp(nuevoPas->nombreCompP, auxPas->nombreCompP) > 0)
		{
			while (auxPas->sig != nullptr && strcmp(nuevoPas->nombreCompP, auxPas->nombreCompP) > 0)
			{
				auxPas = auxPas->sig;
			}

			if (auxPas->ant != nullptr && auxPas->sig != nullptr)
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
				else */if (strcmp(nuevoPas->nombreCompP, auxPas->nombreCompP) > 0)
				{
					auxPas2 = auxPas->sig;
					auxPas->sig = new paciente;
					auxPas->sig->sig = auxPas2;
					auxPas->sig->ant = auxPas;
					auxPas = auxPas->sig;
					auxPas2->ant = auxPas;
				}
				else
				{
					auxPas2 = auxPas->ant;
					auxPas->ant = new paciente;
					auxPas->ant->ant = auxPas2;
					auxPas->ant->sig = auxPas;
					auxPas = auxPas->ant;
					auxPas2->sig = auxPas;
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
				else */if (strcmp(nuevoPas->nombreCompP, auxPas->nombreCompP) > 0)
				{
					auxPas->sig = new paciente;
					auxPas->sig->sig = nullptr;
					auxPas->sig->ant = auxPas;
					auxPas = auxPas->sig;
				}
				else
				{
					auxPas2 = auxPas->ant;
					auxPas->ant = new paciente;
					auxPas->ant->ant = auxPas2;
					auxPas->ant->sig = auxPas;
					auxPas = auxPas->ant;
					auxPas2->sig = auxPas;
				}
			}
		}
		else
		{
			while (auxPas->ant != nullptr && strcmp(nuevoPas->nombreCompP, auxPas->nombreCompP) < 0)
			{
				auxPas = auxPas->ant;
			}

			if (auxPas->ant != nullptr && auxPas->sig != nullptr)
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
				else */if (strcmp(nuevoPas->nombreCompP, auxPas->nombreCompP) < 0)
				{
					auxPas2 = auxPas->ant;
					auxPas->ant = new paciente;
					auxPas->ant->ant = auxPas2;
					auxPas->ant->sig = auxPas;
					auxPas = auxPas->ant;
					auxPas2->sig = auxPas;
				}
				else
				{
					auxPas2 = auxPas->sig;
					auxPas->sig = new paciente;
					auxPas->sig->sig = auxPas2;
					auxPas->sig->ant = auxPas;
					auxPas = auxPas->sig;
					auxPas2->ant = auxPas;
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
				else */if (strcmp(nuevoPas->nombrePas, auxPas->nombrePas) < 0)
				{
					auxPas->ant = new paciente;
					auxPas->ant->ant = nullptr;
					auxPas->ant->sig = auxPas;
					auxPas = auxPas->ant;
				}
				else
				{
					auxPas2 = auxPas->sig;
					auxPas->sig = new paciente;
					auxPas->sig->sig = auxPas2;
					auxPas->sig->ant = auxPas;
					auxPas = auxPas->sig;
					auxPas2->ant = auxPas;
				}
			}

		}

		strcpy_s(auxPas->nombrePas, nuevoPas->nombrePas);
		strcpy_s(auxPas->apellidoPP, nuevoPas->apellidoPP);
		strcpy_s(auxPas->apellidoMP, nuevoPas->apellidoMP);

		// Concatenación
		strcpy_s(auxPas->nombreCompP, auxPas->nombrePas);
		strcat_s(auxPas->nombreCompP, " ");
		strcat_s(auxPas->nombreCompP, auxPas->apellidoPP);
		strcat_s(auxPas->nombreCompP, " ");
		strcat_s(auxPas->nombreCompP, auxPas->apellidoMP);

		strcpy_s(auxPas->genero, nuevoPas->genero);

		strcpy_s(auxPas->telefonoCharP, nuevoPas->telefonoCharP);
		auxPas->telefonoNumP = atoi(auxPas->telefonoCharP);

		strcpy_s(auxPas->ref, nuevoPas->ref);
		strcpy_s(auxPas->fecha, nuevoPas->fecha);

		strcpy_s(auxPas->edadChar, nuevoPas->edadChar);
		auxPas->edadNum = atoi(auxPas->edadChar);

		strcpy_s(auxPas->pMedicoP, nuevoPas->pMedicoP);

		strcpy_s(auxPas->nombreUsuP, nuevoPas->nombreUsuP);

		while (auxPas->ant != nullptr)
		{
			auxPas = auxPas->ant;
		}

		iniPas = auxPas;

		auxPas = iniPas;
		auxPas2 = auxPas;
		auxPas3 = auxPas;
	}

	MessageBox(NULL, "Se ha registrado al paciente con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
}

void eliminarPas(char pacienteNom[60])
{
	paciente* start;
	auxPas = iniPas;

	if (auxPas == nullptr)
	{
		MessageBox(0, "La lista esta vacia.", "AVISO", MB_OK);
	}
	else
	{
		while (auxPas->sig != nullptr && strcmp(auxPas->nombreCompP, pacienteNom) != 0)
		{ //Nos movemos en el arreglo para buscar el usuario

			auxPas = auxPas->sig;
		}

		if (auxPas->sig == nullptr || strcmp(auxPas->nombreCompP, pacienteNom) != 0)
		{
			MessageBox(0, "paciente no encontrado", "AVISO", MB_OK);
		}

		if (auxPas == iniPas)
		{	//El nodo es el primero 
			if (iniPas->ant != nullptr && iniPas->sig != nullptr)
			{
				iniPas = iniPas->sig;
			}
			else if (iniPas->ant == nullptr)
			{
				iniPas = iniPas->sig;
			}
			else
			{
				iniPas = iniPas->ant;
			}

			if (auxPas->sig == nullptr)
			{ //Si es el primero y unico nodo
				//delete auxPas;		//Eliminamos el primer nodo
				//inicio = nullptr;
				//auxPas = inicio;

				iniPas = nullptr;
				delete auxPas;

				auxPas = iniPas;
				auxPas2 = auxPas;
				auxPas3 = auxPas;
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

				start = iniPas->sig;
				auxPas->sig->ant = nullptr;
				delete auxPas;
				auxPas = start;
				auxPas->ant = nullptr;

				auxPas2 = auxPas;
				auxPas3 = auxPas;
				iniPas = auxPas;
			}

			MessageBox(0, "paciente eliminado", "AVISO", MB_OK);
		}
		else
		{

			if (auxPas->sig == nullptr)
			{ //Si el nodo es el último
				auxPas->ant->sig = nullptr;	//Antes de eliminar, el penultumo nodo, su puntero siguiente, lo igualamos a nullptr
				delete auxPas;

				auxPas = iniPas;
				auxPas2 = auxPas;
			}
			else
			{ //Si es cualquier nodo que no sea el inicio o el último
				auxPas->sig->ant = auxPas->ant;
				auxPas->ant->sig = auxPas->sig;
				delete auxPas;

				auxPas2 = auxPas;
				auxPas3 = auxPas;
				auxPas = iniPas; //Para que auxPas no quede sin apuntar a nada, la apuntamos al inicio
			}

			MessageBox(0, "paciente eliminado", "AVISO", MB_OK);

		}
	}

}

void escribirPas()
{
	auxPas = iniPas;

	ofstream escribir;
	escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\Pacientes.bin", ios::out | ios::binary | ios::trunc);

	if (escribir.is_open())
	{
		while (auxPas != nullptr)
		{
			escribir.write((char*)auxPas, sizeof(paciente));
			auxPas = auxPas->sig;
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

void leerPas()
{
	auxPas = iniPas;

	ifstream leer;
	leer.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\Pacientes.bin", ios::in | ios::binary);

	if (leer.is_open())
	{
		paciente* pasLeido = new paciente;

		while (!leer.read((char*)pasLeido, sizeof(paciente)).eof())
		{

			while (auxPas != nullptr && auxPas->sig != nullptr)
			{
				auxPas = auxPas->sig;
			}
			if (auxPas == nullptr)
			{
				iniPas = pasLeido;
				iniPas->sig = nullptr;
				iniPas->ant = nullptr;
				auxPas = iniPas;
			}
			else
			{
				auxPas->sig = pasLeido;
				auxPas->sig->ant = auxPas;
				auxPas = auxPas->sig;
				auxPas->sig = nullptr;
				/*auxPas->sig = espLeida;
				auxPas->ant = auxPas;
				auxPas = auxPas->sig;
				auxPas->sig = nullptr;*/
			}

			pasLeido = new paciente;
		}

		leer.close();
		delete pasLeido;
	}
}

void reportePas()
{
	auxPas = iniPas;

	ofstream escribir;
	escribir.open("C:\\Users\\hp\\Documents\\UANL\\Universidad 7\\ED\\Proyecto_Clinica\\Proyecto_Clinica\\PacientesReporte.txt", ios::out | ios::trunc);

	if (escribir.is_open())
	{
		while (auxPas != nullptr)
		{
			escribir.write((char*)auxPas, sizeof(paciente));
			auxPas = auxPas->sig;
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

#pragma endregion

#pragma region Funciones de Arbol Medicos

//medico* crearNodo(medico* nuevoMed)
//{
//	medico* nodo = new medico;
//
//	//strcpy_s(nodo->nombreMed, nuevoMed->nombreMed);
//	//strcpy_s(nodo->apellidoPM, nuevoMed->apellidoPM);
//	//strcpy_s(nodo->apellidoMM, nuevoMed->apellidoMM);
//
//	//// Concatenación
//	//strcpy_s(nodo->nombreCompM, nuevoMed->nombreMed);
//	//strcat_s(nodo->nombreCompM, " ");
//	//strcat_s(nodo->nombreCompM, nodo->apellidoPM);
//	//strcat_s(nodo->nombreCompM, " ");
//	//strcat_s(nodo->nombreCompM, nodo->apellidoMM);
//
//	//strcpy_s(nodo->cedulaChar, nuevoMed->cedulaChar);
//	//nodo->cedulaNum = atoi(nodo->cedulaChar);
//	//strcpy_s(nodo->numConsultorioChar, nuevoMed->numConsultorioChar);
//	//nodo->numConsultorioNum = atoi(nodo->numConsultorioChar);
//	//strcpy_s(nodo->hoararioChar, nuevoMed->hoararioChar);
//	//nodo->hoararioNum = atoi(nodo->hoararioChar);
//	//strcpy_s(nodo->telefonoChar, nuevoMed->telefonoChar);
//	//nodo->telefonoNum = atoi(nodo->telefonoChar);
//
//	//strcpy_s(nodo->foto, nuevoMed->foto);
//
//	//nodo->lun = nuevoMed->lun;
//	//nodo->mar = nuevoMed->mar;
//	//nodo->mie = nuevoMed->mie;
//	//nodo->jue = nuevoMed->jue;
//	//nodo->vie = nuevoMed->vie;
//	//nodo->sab = nuevoMed->sab;
//
//	//strcpy_s(nodo->nombreUsuM, nuevoMed->nombreUsuM);
//
//	/*nodo->der = nullptr;*/
//	/*nodo->izq = nullptr;*/
//
//
//	return nodo;
//}
//
//void nuevoMed(medico*& pivote, medico* nuevoMed2)
//{
//
//
//	//nuevoMed2->cedulaNum = atoi(nuevoMed2->cedulaChar);
//
//	//if (pivote == nullptr)
//	//{ //Si 'inicio->sig es igual a nullptr, o sea, apunta a nada, la lista esta vacia
//	//	medico *nuevoNodo = crearNodo(nuevoMed2);
//	//	pivote = nuevoNodo;
//
//	//	/*auxMed = pivote;
//	//	auxMed2 = auxMed;
//	//	auxMed3 = auxMed;*/
//	//}
//	//else
//	//{
//	//	int valorRaiz = pivote->cedulaNum;
//
//	//	if (nuevoMed2->cedulaNum < valorRaiz)
//	//	{
//	//		nuevoMed(pivote->izq, nuevoMed2);
//	//	}
//	//	else if (nuevoMed2->cedulaNum > valorRaiz)
//	//	{
//	//		nuevoMed(pivote->der, nuevoMed2);
//	//	}
//
//	//	/*auxMed2 = auxMed;
//	//	auxMed3 = auxMed;
//	//	auxMed = pivote;*/
//	//}
//
//	MessageBox(NULL, "Se ha registrado el médico con éxito.", "AVISO", MB_OK | MB_ICONINFORMATION);
//	/*int opc = MessageBox(hwnd, (LPCWSTR)L"¿Seguro que desea eliminar este usuario?", (LPCWSTR)L"AVISO", MB_YESNO | MB_ICONQUESTION);*/
//}
//
//bool buscarMed(medico *pivote, medico* busqueda)
//{
//	busqueda->cedulaNum = atoi(busqueda->cedulaChar);
//
//	if (pivote == nullptr) // No hay registros
//	{
//		return false;
//	}
//	else if (pivote->cedulaNum == busqueda->cedulaNum) // Las variables son iguales
//	{
//		return true;
//	}
//	else if (busqueda->cedulaNum < pivote->cedulaNum) // La variable es menor
//	{
//		return buscarMed(pivote->izq, busqueda);
//		/*cout << pivote->cedulaChar;*/
//		/*if (pivote->izq == nullptr)
//		{
//			return false;
//		}*/
//	}
//	else if (busqueda->cedulaNum > pivote->cedulaNum) // La variable es mayor
//	{
//		return buscarMed(pivote->der, busqueda);
//		/*cout << pivote->cedulaChar;*/
//		/*if (pivote->der == nullptr)
//		{
//			return false;
//		}*/
//	}
//	else // La variable no existe
//	{
//		return false;
//	}
//}

#pragma endregion