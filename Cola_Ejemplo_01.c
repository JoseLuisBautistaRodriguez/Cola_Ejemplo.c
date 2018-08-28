#include <stdio.h>
#include <stdlib.h>
						
#define TIPO_DE_DATO 10			// Determina el tamannio del array unidimencional que se generara por cada pieza en cola ( Evaluar el tipo de datos a ingresar)
#define NUMERO_MX_DE_DATOS 50	// Determina el numero maximo de piezas que existiran en la cola (Ello depende del SO a usar y Arquitectura del mismo)
	
	/*
		EL tamannio de memoria asignada al ejecutarse el programa en su punto maximo sera:

		TMM = (NUMERO_MX_DE_DATOS) * [(tipo de dato a usar en DatosIngresados)(TIPO_DE_DATO) + (tamannio de un puntero)] 

		TMM estara dado en bytes; los valores dependen de la arquitectura del sistema. 
	*/

typedef struct nodoBase 
{
	unsigned char DatosIngresados[TIPO_DE_DATO];
	struct nodoBase *siguienteDato ;
}TipoNodo;

typedef TipoNodo *ApuntadorANodo;
typedef TipoNodo *PrimerDato;
typedef TipoNodo *UltimoDato;

/*Crea una pieza de TipoNodo de manera dinamica y le asigna los valores del arreglo*/
char IngresarDato( ApuntadorANodo *PrimerDato, ApuntadorANodo *UltimoDato, unsigned char *AP_Arreglo ) 
{
	unsigned char contador = 0;

	if ( !*PrimerDato ) // En el primer ingreso de un array se ejecuta lo siguiente:
	{
		ApuntadorANodo nuevoNodo;									// se crea un nodo de paso.(apuntador) 
		nuevoNodo = ( ApuntadorANodo )malloc(sizeof(TipoNodo));		// Se asigna un espacio en memoria de Tipo NodoBase
		for (; contador < TIPO_DE_DATO ; contador++ ) nuevoNodo -> DatosIngresados[contador] = *(AP_Arreglo + contador ); // se asignan los datos del arreglo

		nuevoNodo -> siguienteDato = NULL ;							// Se asigna un null al valor siguiente. 
		*PrimerDato = nuevoNodo;									// Se da un espacio al Nodo de paso como el primer elemento en la cola
		*UltimoDato = nuevoNodo;									// Se da un espacio al Nodo de paso como el primer elemento en la cola

	}else /* Si ya existe un elemento en la cola, se ejecuta lo siguiente:*/
	{
		ApuntadorANodo nuevoNodo;									// se crea un nodo de paso.(apuntador) 
		nuevoNodo = ( ApuntadorANodo )malloc(sizeof(TipoNodo));		// Se asigna un espacio en memoria de Tipo NodoBase

		for (; contador < TIPO_DE_DATO ; contador++ ) nuevoNodo -> DatosIngresados[contador] = *(AP_Arreglo + contador ); // se asignan los datos del arreglo
		nuevoNodo -> siguienteDato = NULL ;							// Se asigna un null al valor siguiente.

		if (*UltimoDato) (*UltimoDato)-> siguienteDato = nuevoNodo; // Asigna la ultima posicion al puntero anterio el nodo actual
		*UltimoDato = nuevoNodo;									// Modifica la pila para indicar que ahora es el ultimo array ingresado
	}
	return 1 ;
}

/* Crea un archivo a partir de los elementos en la pila existentes*/
char ImprimirValores(ApuntadorANodo *PrimerDato, ApuntadorANodo *UltimoDato, unsigned int numeroDeElementos)
{
	unsigned int i = 0, j = 0; 	// Contadores
	FILE *archivo;				
	archivo = fopen(/*("%s", extencionDeArchivo)*/ "EjemploActivo.txt" , "w" );
	/*
		Si el archivo a imprimir tendra nombres que cambien acorde a la ejecucion del programa, quitar el comentario dentro de la funcion fopen
		asignando el nombre en "%s" (o una variable) con su extencion, en extencionDeArchivo, tomando en cuenta que la variacion del nombre y extencion
		del archivo estan dentro del array extencionDeArchivo. 
	*/

	/* El siguiente for anidado imprime dentro del archivo los datos de la cola existentes, tambien elimina los valores tomando como referencia 
		la variable numeroDeElementos, si se quiere agregar saltos de linea dentro del documento a imprimir, esta es la zona indicada, ya sea antes del o
		despues del for anidado.
	*/

	for (; i < numeroDeElementos ; i++) 
	{	
		ApuntadorANodo nodoDePaso;
		nodoDePaso = *PrimerDato;
		if ( !nodoDePaso ) // si ya no hay eleementos dentro de la pila, cierra el archivo y termina la funcion.
		{
			fclose(archivo);
			return 0 ;
		} 
		*PrimerDato = nodoDePaso -> siguienteDato;
		
		for ( j = 0 ;j<TIPO_DE_DATO;j++) fprintf( archivo ,"%c", nodoDePaso ->DatosIngresados[j] );
		
		if(!*PrimerDato)*UltimoDato = NULL; // reasigna el apuntador del elemento anterior 
		free(nodoDePaso); // Elimina el nodo de la pila
	}

	fclose(archivo); 
	return 1 ;
}

int main()
{	
	ApuntadorANodo PrimerDato = NULL , UltimoDato = NULL ;  // Asigna valores nulos para la Pila, aún no existe.  
	unsigned int ValorDePaso = 0 ;							/* Es el valor de control, se recomieda que sea menor a TMM
															 	Si este valor es reasignado a 0, puede ser llamado n veces
															 	dentro del programa, pero es necesario modificar el nombre 
															 	de salida del archivo, para evitar una sobre escritura en 
															 	el txt ya realizado.  
															*/			

	unsigned char arregloEjemplo[10] = "DATOS A";	/* Cadena de ingreso de ejemplo, este arrray puede ser sustituido por la entrada
														ya evaludada o parametrizada del gpio, si el tipo de dato cambia, modificar 
														el de la estructura y evaluar tamannio para el TMM. 
	*/

	for ( ;ValorDePaso < NUMERO_MX_DE_DATOS ; ) ValorDePaso += (unsigned int)IngresarDato( &PrimerDato, &UltimoDato,  arregloEjemplo);
		/*
			Este for realiza la asignacion para n valores de entrada; n < NUMERO_MX_DE_DATOS, la asignacion sera constante hasta el limite marcado,
			esto puedde ser modificado con la libreria time.h, asignando un tiempo limite < TMM o una funcion recursiva que contemple el cambio de 
			nombre del archivo para evitar su sobre escriura. El valor de paso se usa de control para el numero de datos a imprimir dentro del docu-
			mento impreso. 
		*/
	ValorDePaso = ImprimirValores( &PrimerDato, &UltimoDato, ValorDePaso); /* Al mandar llamar esta funcion, si el valor en ValorDePaso == 0, no 
																				se realizo la impresion de los datos, si ValorDePaso == 1, la impresion 
																				se realizo con exito.
																			*/
	return 0 ;
}
