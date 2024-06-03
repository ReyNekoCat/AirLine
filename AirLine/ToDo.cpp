			
		   //// ::::: LISTA DE REQUISITOS Y PENDIENTES ::::: ////
// X = Pendiente / Y = En proceso / Z = Completado / - = Info / ? = Duda //

////// ::: ENTREGA 1 ::: //
/*	 /	Req. / Puntos / Info. /
	Z	Si		10      Diseño de un documento en Word con el modelo de datos y código en C++.
	Z	No		10		Definición de cuántas listas ligadas se utilizarán en todo el proyecto y estructura de cada nodo.
	Z	Si		10		Definición de árboles binarios
	Z	Si		5		Algoritmo Quicksort aplicado a la lista.
	X	Si		5		Algoritmo Heapsort aplicado a la lista.
	Z	No		15		Algoritmo de manipulación de información de cada lista ligada y árbol binario.
	Z	Si		10		Funciones para manejo de archivos, un archivo por cada lista ligada.
	Z	Si		25		Diseño de pantallas del proyecto en WinAPI con C++.
	Z	Si		10		Utilización de clases para la estructura de datos y métodos.
*/
////// ::: ENTREGA 2 ::: //
/*	 /	Req. / Puntos / Info. /
   Z	Sí		5       Ingreso al sistema por usuario y contraseña, *recordar usuario.
   Z	No		5		Registro de Usuarios
   Z	Sí		10		Registro de Vuelos
   Z	Sí		10		Registro de Pasajeros
   Z	Sí		10		Compra de boletos
   X	Sí		5		Pases de abordar
   Z 	Sí		10		Cancelación/Confirmación de Vuelos
   X	No		10		Cancelación de boletos comprados
   Z	Sí		10		Manifiesto
   Z	No		10		Reporte de Vuelos
   Z	Sí		10		Uso apropiado de métodos de ordenamiento y búsqueda binaria en listas ligadas.
   Z	Sí		5		Guardado de información en archivos binarios.
*/	
				/// :::: DESCRIPCIONES DEL PROYECTO :::: ///

////// ::: MENÚ PRINCIPAL ::: //
/*	- Las opciones para los usuarios serán: Vuelos, pasajeros, cancelaciones, pases de abordar, manifiesto y reporte de vuelos.
	? La opción de la gestión de usuarios solo estará disponible para el usuario administrador.                                 
*/
////// ::: USUARIOS ::: // COMPLETADO //
/*	Z El usuario administrador, puede ser uno solo, y el dato de ese usuario y contraseña debe estar guardado en un archivo texto.
	Z Para poder ingresar a la aplicación se debe contar con usuarios registrados, los cuales debe agregar un usuario administrador.	
		Z Se requiere ser usuario registrado para ingresar a la aplicación
	Z Se debe habilitar un checkbox para que se permita recordar el último usuario que ingresó a la aplicación.
	Z Solo se deben permitir registro de usuarios mayores a 18 años.
	Z El nombre de usuario y su fotografía se deben mostrar en todas las pantallas del proyecto.
	Z Al registrar a cada usuario se debe guardar la fecha y hora del registro. (Ver donde se va a mostrar)
	- Los datos de los usuarios son:
		▪ Nombre de usuario
		▪ Correo electrónico
		▪ Contraseña
		▪ Nombre completo
		▪ Fecha de Nacimiento
		▪ Género
		▪ Fotografía
*/
////// ::: VUELOS ::: // X - Validaciones menores //
/*
	- Se requiere tener un sistema que administre los vuelos programados y las listas de pasajeros de cada vuelo.
	- Se debe tener una pantalla para el registro de los vuelos.
	- Se deben de programar los vuelos:
		Z Un vuelo va desde un origen a un destino
		Z A una fecha y hora concreta
		X Solo es posible programar vuelos hasta los próximos 6 meses
		Z Tiene # de vuelo que se debe generar automáticamente
		Z En qué tipo de avión
		Z La cantidad de asientos disponibles
		Z En clase turista o en clase ejecutiva
		Z Precio en cada clase
	Z Por cada vuelo, solo se pueden admitir a un 10% pasajeros menores de 12 años, y un 15% de pasajeros mayores de 60 años.
		X Estos porcentajes pueden cambiar por cada vuelo.
	Z Se debe guardar usuario, fecha y hora del registro de cada vuelo.
	Z Los vuelos también pueden ser cancelados antes de la fecha y hora de la realización del vuelo
		Y Se debe de contar con una pantalla o esta misma donde se confirme la realización de cada vuelo y la cantidad de pasajeros que abordaron.
*/	
////// ::: PASAJEROS ::: // COMPLETADO //
/*	-Se debe tener una pantalla para registrar a los pasajeros.
	Z De los pasajeros es necesario guardar sus datos generales completos, como: 
		Z Nombre completo
		Z Fecha de nacimiento
		Z Género
		Z Nacionalidad.
	Z Se debe guardar usuario, fecha y hora del registro de cada pasajero.
*/
//////	::: BOLETOS ::: // X - Forma de pago y cancelaciones //
/*	Z Los pasajeros pueden comprar boletos para los vuelos futuros
	Z Se deben de cuidar las validaciones que hay en la compra de boletos, como:
		Z Cantidad de asientos disponibles
		Z Boletos para menores de edad o tercera edad
		Z Clase turista o clase ejecutiva.
	X Se debe indicar cuál es la forma de pago de cada boleto
		- Tarjeta de crédito,
		- Débito
		- Transferencia
		- etc.
	Z Un mismo pasajero no puede tener dos o más boletos en el mismo vuelo. (solo uno)
	X Los pasajeros tienen hasta 10 días antes de la realización del vuelo para cancelar su compra.
		X La cantidad de días para hacer una cancelación también se configura por vuelo.
*/
////// ::: PASES DE ABORDAR ::: // WIP //
/*	-Se debe tener una pantalla para obtener el pase de abordar, que es la confirmación de que un pasajero va a tomar el vuelo.
	X Si un pasajero no obtiene su pase de abordar, no puede hacer uso del vuelo.
	X Se debe guardar fecha y hora en la que se obtiene el pase de abordar.
*/
////// ::: MANIFIESTO ::: // COMPLETADO //
/*	- Se debe tener una pantalla donde se muestren todos los vuelos realizados
		Z Se debe elegir uno y se deben mostrar la lista de pasajeros que realizaron el vuelo.
	Z Se debe tener la opción de ordenar por número de asiento (ordenamientos)
		- O de ordenar por apellidos y nombre de los pasajeros
	Z En la parte superior del manifiesto deben de venir los datos del vuelo 
		Z Además de mostrar al lado la lista de pasajeros.
	- Los datos del manifiesto deben de incluir:
		Z Nombre completo del pasajero
		Z Edad
		Z Nacionalidad.
	Z Se debe mostrar en pantalla y luego con un botón generar un archivo texto con el reporte.
*/
////// ::: REPORTE DE VUELOS ::: // COMPLETADO //
/*	Z Se debe tener una pantalla donde se le defina un rango de fechas y que muestre todos los vuelos en esas fechas.
		Z Se mostrará un listado con la lista de vuelos en el rango de fechas seleccionado
		Z Número de vuelo, hora, origen y destino, ordenado por número de vuelo.
	Z Se debe mostrar en pantalla y luego con un botón generar un archivo texto con el reporte.
*/
////// ::: ESTRUCTURAS DE DATOS ::: // COMPLETADO //
/*	- Se debe utilizar listas doblemente ligadas para el manejo de la información.
	Z Todas las entidades se deben de guardar en archivos binarios.
	Z Se deben de utilizar al menos los métodos de ordenamiento HeapSort y QuickSort, en la entidad que elija el alumno.
		- Vuelos y Pasajeros
	Z La entidad de usuarios debe de ser gestionada con un árbol binario.
	Z Para las búsquedas de información, se debe de utilizar el método de búsqueda binaria.
*/
////// ::: REGISTRO ::: // COMPLETADO //
/*	- Registro de alguna entidad se refiere a altas, bajas y cambios.
	Z Cuando se realicen cambios se deben de mostrar los datos anteriores
		Z Además de capturar los nuevos.
	Z Todas las entidades deben guardar la clave del usuario que está registrando los datos.
	Z Los nombres completos tanto de usuarios y pasajeros se deben de guardar de forma separada como:
		- Nombre(s)
		- Apellido paterno
		- Apellido materno
*/
//////	::: SALIR :::	// COMPLETADO //
/*	- Una de las opciones disponibles en el sistema debe ser salir del mismo
	Z En ese momento se deben de guardar los datos de las estructuras en memoria como:
		Z Árboles binarios
		Z Listas doblemente ligadas
	Z Se deben guardar como archivos binarios.
*/
////// ::: OPCIONES ADICIONALES ::: // NO //
/*	Queda a criterio del alumno manejar opciones adicionales para enriquecer el proyecto, como:
	- Ciudades
	- Pilotos
	- Tipos de avión
	- etc.
*/