			
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
   Y	Sí		5       Ingreso al sistema por usuario y contraseña, *recordar usuario.
   Z	No		5		Registro de Usuarios
   Y	Sí		10		Registro de Vuelos
   Y	Sí		10		Registro de Pasajeros
   X	Sí		10		Compra de boletos
   X	Sí		5		Pases de abordar
   X 	Sí		10		Cancelación/Confirmación de Vuelos
   X	No		10		Cancelación de boletos comprados
   X	Sí		10		Manifiesto
   Y	No		10		Reporte de Vuelos
   X	Sí		10		Uso apropiado de métodos de ordenamiento y búsqueda binaria en listas ligadas.
   Y	Sí		5		Guardado de información en archivos binarios.
*/	
				/// :::: DESCRIPCIONES DEL PROYECTO :::: ///

////// ::: MENÚ PRINCIPAL ::: //
/*	- Las opciones para los usuarios serán: Vuelos, pasajeros, cancelaciones, pases de abordar, manifiesto y reporte de vuelos.
	X La opción de la gestión de usuarios solo estará disponible para el usuario administrador.                                 
*/
////// ::: USUARIOS ::: //
/*	X El usuario administrador, puede ser uno solo, y el dato de ese usuario y contraseña debe estar guardado en un archivo texto.
	X Para poder ingresar a la aplicación se debe contar con usuarios registrados, los cuales debe agregar un usuario administrador.	
		X Se requiere ser usuario registrado para ingresar a la aplicación
	X Se debe habilitar un checkbox para que se permita recordar el último usuario que ingresó a la aplicación.
	X Solo se deben permitir registro de usuarios mayores a 18 años.
	X El nombre de usuario y su fotografía se deben mostrar en todas las pantallas del proyecto.
	X Al registrar a cada usuario se debe guardar la fecha y hora del registro.
	- Los datos de los usuarios son:
		▪ Nombre de usuario
		▪ Correo electrónico
		▪ Contraseña
		▪ Nombre completo
		▪ Fecha de Nacimiento
		▪ Género
		▪ Fotografía
*/
////// ::: VUELOS ::: //
/*
	- Se requiere tener un sistema que administre los vuelos programados y las listas de pasajeros de cada vuelo.
	- Se debe tener una pantalla para el registro de los vuelos.
	- Se deben de programar los vuelos:
		X Un vuelo va desde un origen a un destino
		X A una fecha y hora concreta
		X Solo es posible programar vuelos hasta los próximos 6 meses
		X Tiene # de vuelo que se debe generar automáticamente
		X En qué tipo de avión
		X La cantidad de asientos disponibles
		X En clase turista o en clase ejecutiva
		X Precio en cada clase
	X Por cada vuelo, solo se pueden admitir a un 10% pasajeros menores de 12 años, y un 15% de pasajeros mayores de 60 años.
		X Estos porcentajes pueden cambiar por cada vuelo.
	X Se debe guardar usuario, fecha y hora del registro de cada vuelo.
	X Los vuelos también pueden ser cancelados antes de la fecha y hora de la realización del vuelo
		X Se debe de contar con una pantalla o esta misma donde se confirme la realización de cada vuelo y la cantidad de pasajeros que abordaron.
*/	
////// ::: PASAJEROS ::: //
/*	-Se debe tener una pantalla para registrar a los pasajeros.
	X De los pasajeros es necesario guardar sus datos generales completos, como: 
		X Nombre completo
		X Fecha de nacimiento
		X Género
		X Nacionalidad.
	X Se debe guardar usuario, fecha y hora del registro de cada pasajero.
*/
////// ::: BOLETOS ::: //
/*	X Los pasajeros pueden comprar boletos para los vuelos futuros
	X Se deben de cuidar las validaciones que hay en la compra de boletos, como:
		X Cantidad de asientos disponibles
		X Boletos para menores de edad o tercera edad
		X Clase turista o clase ejecutiva.
	X Se debe indicar cuál es la forma de pago de cada boleto
		- Tarjeta de crédito,
		- Débito
		- Transferencia
		- etc.
	X Un mismo pasajero no puede tener dos o más boletos en el mismo vuelo. (solo uno)
	X Los pasajeros tienen hasta 10 días antes de la realización del vuelo para cancelar su compra.
		X La cantidad de días para hacer una cancelación también se configura por vuelo.
*/
////// ::: PASES DE ABORDAR ::: //
/*	-Se debe tener una pantalla para obtener el pase de abordar, que es la confirmación de que un pasajero va a tomar el vuelo.
	X Si un pasajero no obtiene su pase de abordar, no puede hacer uso del vuelo.
	X Se debe guardar fecha y hora en la que se obtiene el pase de abordar.
*/
////// ::: MANIFIESTO ::: //
/*	- Se debe tener una pantalla donde se muestren todos los vuelos realizados
		X Se debe elegir uno y se deben mostrar la lista de pasajeros que realizaron el vuelo.
	X Se debe tener la opción de ordenar por número de asiento (ordenamientos)
		- O de ordenar por apellidos y nombre de los pasajeros 
	X En la parte superior del manifiesto deben de venir los datos del vuelo 
		X Además de mostrar al lado la lista de pasajeros.
	- Los datos del manifiesto deben de incluir:
		X Nombre completo del pasajero
		X Edad
		X Nacionalidad.
	X Se debe mostrar en pantalla y luego con un botón generar un archivo texto con el reporte.
*/
////// ::: REPORTE DE VUELOS ::: //
/*	X Se debe tener una pantalla donde se le defina un rango de fechas y que muestre todos los vuelos en esas fechas.
		X Se mostrará un listado con la lista de vuelos en el rango de fechas seleccionado
		X Número de vuelo, hora, origen y destino, ordenado por número de vuelo.
	X Se debe mostrar en pantalla y luego con un botón generar un archivo texto con el reporte.
*/
////// ::: ESTRUCTURAS DE DATOS ::: //
/*	- Se debe utilizar listas doblemente ligadas para el manejo de la información.
	Y Todas las entidades se deben de guardar en archivos binarios.
	Y Se deben de utilizar al menos los métodos de ordenamiento HeapSort y QuickSort, en la entidad que elija el alumno.
		- Vuelos y Pasajeros
	Y La entidad de usuarios debe de ser gestionada con un árbol binario.
	X Para las búsquedas de información, se debe de utilizar el método de búsqueda binaria.
*/
////// ::: REGISTRO ::: //
/*	- Registro de alguna entidad se refiere a altas, bajas y cambios.
	X Cuando se realicen cambios se deben de mostrar los datos anteriores
		X Además de capturar los nuevos.
	X Todas las entidades deben guardar la clave del usuario que está registrando los datos.
	X Los nombres completos tanto de usuarios y pasajeros se deben de guardar de forma separada como:
		- Nombre(s)
		- Apellido paterno
		- Apellido materno
*/
////// ::: SALIR ::: //
/*	- Una de las opciones disponibles en el sistema debe ser salir del mismo
	X En ese momento se deben de guardar los datos de las estructuras en memoria como:
		X Árboles binarios
		X Listas doblemente ligadas
	X Se deben guardar como archivos binarios.
*/
////// ::: OPCIONES ADICIONALES ::: // (NO hacerlo a priori)
/*	Queda a criterio del alumno manejar opciones adicionales para enriquecer el proyecto, como:
	- Ciudades
	- Pilotos
	- Tipos de avión
	- etc.
*/