/*
 * crimen.h
 *
 * Copyright  (C) Juan F. Huete
*/
#ifndef __CRIMEN_H
#define __CRIMEN_H

#include <string>
#include <iostream>
#include <vector>
#include "fecha.h"

using namespace std;

//! Clase crimen, asociada a la definición de un crimen.
/*!
	\b Constructores

	crimen::crimen()

	\b Consultores

	crimen::getID(), getCaseNumber(), getDate(), getIUCR(),
	getPrimaryType(), getDescription(), getLocationDescription(),
	getArrest(), getDomestic(), getLatitude(), getLongitude()


	\b Modificadores

	crimen::setID(), setCaseNumber(), setDate(), setIUCR(),
	setPrimaryType(), setDescription(), setLocationDescription(),
	setArrest(), setDomestic(), setLatitude(), setLongitude()


	<b> Sobrecarga de operadores </b>

	crimen::operator=(), operator==(), operator!=(), operator<(),
	operator<=(), operator>(), operator>=(), operator<<()


 * \b Descripción

 * Contiene toda la información asociada a un crimen.

 * <b>Requiere C++11 ( Flag: -std=c++0x )</b>

 * El ID por defecto es 1.

 * Los atributos de un objeto crimen son:


 * \li ID : Número ( mayor que 0 ) que identifica el caso ( es único ).
 *	\li Número del caso
 *	\li Fecha
 *	\li IUCR
 *	\li Tipo de crimen
 *	\li Descripción
 *	\li Localización ( descripción )
 *	\li Ha habido arrestos
 *	\li Es doméstico
 *	\li Latitud / Longitud


	\invariant

* El invariante de la representación del crimen es su ID de forma que:

	\verbatim

	IR: rep ==> bool

	 Para todo crimen:
			ID > 0
	\endverbatim


	<b> Sobrecarga de operadores </b>

	Están sobrecargados los operadores de comparación y el de la salida estándar ( << ).
	El criterio de comparación es el ID, que al ser único y un entero es fácil determinar
	cuál es menor y por tanto sucedió antes cronológicamente.


 * <b> Ejemplo de uso: </b>
 \code

 // Crea un objeto crimen vacío.
 crimen input_crimen, output_crimen;

 // Creamos los parámetros.
 long int id = ... ;
 ...

 // Rellenamos los datos.
 input_crimen.setID( id )
 ...

 // Ahora podemos copiarlo
 output_crimen = input_crimen;
 crimen otro_crimen( output_crimen );

 // O también obtener datos.
 cout << otro_crimen.getCaseNumber();

 // Podemos mostrar un crimen por la salida estándar
 cout << input_crimen << otro_crimen;

 // O compararlos entre sí
 if( input_crimen < otro_crimen )
 	cout << "El primer crimen fue: " << input_crimen << endl;

 \endcode

*/

class crimen {
	public:


		/*****************************************************************/
		//
		// 	CONSTRUCTORES


		/*!
			@brief Constructor por defecto.

			Crea un objeto crimen vacío. Por defecto se inicializa el ID
			en 0, el cual no cumple el invariante de la representación.
			Los strings son vacíos ( "" ), latitud y longitud valen 0
			y false el arresto o si es doméstico.
		*/
		crimen();

		/*!
			@brief Constructor de copia.

			Crea una copia en memoria del objeto crimen pasado como parámetro.

			@param x Objeto tipo crimen del que se quiere realizar la copia.

		*/
		crimen( const crimen & x );

		/*!
			@brief Constructor de inicialización.

			Construye un objeto crimen y lo rellena con los parámetros.

			\pre { El ID debe de ser mayor que 0 ( ID > 0 ). }

			@param id Entero mayor que cero que contiene el ID.
			@param cas_num Cadena del número del caso.
			@param dat Fecha del delito.
			@param iu IUCR.
			@param prim_type Tipo de delito.
			@param desc Descripción.
			@param loc_des Descripción de la localización.
			@param arr Booleano para saber si ha habido arrestos.
			@param dom Booleano para saber si es doméstico.
			@param lat Latitud.
			@param lon Longitud.
		*/
		crimen(	long int id, 						// ID del caso
					const string & cas_num,			// Nº del caso
					const fecha & dat,				// Fecha del caso
					const string & iu,				// IUCR
					const string & prim_type,		// Tipo primario del caso
					const string & desc,				// Descripción
					const string & loc_des,			// Localización ( string )
					bool arr,							// Ha habido arrestos
					bool dom,							// Es un caso doméstico
					double lat,							// Latitud
					double lon							// Longitud
		);

		/**

			@brief Constructor de inicialización a partir de una cadena (string).

			Toma una cadena (string) cuyo formato es:

			"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
			FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"

			Y crea el objeto crimen a partir de dichos datos.

			\pre { El ID debe de ser mayor que 0 ( ID > 0 ). }

			@param data Objeto string a analizar.
		*/

		crimen( const string & data );

		/*!
			@brief Comprueba que el invariante es correcto.

			Comprueba que el invariante de la representación del objeto crimen
			sea correcto, es decir, ID > 0.

			@return true si es correcto, false si no.
		*/
		bool cheq_rep();

		/*****************************************************************/
		//
		// 	MODIFICADORES


		/*!
			@brief Establece el ID del crimen.

			\pre { El ID debe de ser mayor que 0 ( ID > 0 ). }

			@param id Número entero que representa el ID.
		*/
		void setID( long int id );

		/*!
			@brief Establece el número del crimen.

			@param case_num Entero mayor que cero que contiene el ID.
		*/
		void setCaseNumber( const string & case_num );

		/*!
			@brief Establece la fecha del crimen.

			@param dat Objeto tipo fecha para almacenar la fecha del crimen.
		*/
		void setDate( const fecha & dat );

		/*!
			@brief Establece el IUCR del crimen.

			Establece el IUCR del crimen. Es una cadena de texto según Illinois Uniform Crime Reporting.

			@param iucr_dat Cadena de texto que contiene el IUCR del crimen.
		*/
		void setIUCR( const string & iucr_dat );

		/*!
			@brief Establece el tipo primario del crimen.


			@param p_type Cadena de texto que representa el tipo de crimen.

		*/
		void setPrimaryType( const string & p_type);

		/*!
			@brief Establece una descripción para el crimen.

			@param des Cadena de texto (string) con la descripción del crimen.

		*/
		void setDescription( const string & des );

		/*!
			@brief Establece la descripción del lugar aproximado.

			@param loc_des Cadena de texto (string) con la descripción del lugar del crimen.
		*/
		void setLocationDescription( const string & loc_des );

		/*!
			@brief Establece si ha habido arrestos.

			@param arr Variable booleana para determinar si ha habido arrestos.
		*/
		void setArrest( bool arr );

		/*!
			@brief Establece si el crimen ha sido doméstico.

			@param dom Variable booleana para determinar si el crimen es doméstico.
		*/
		void setDomestic( bool dom );

		/*!
			@brief Establece la Latitud del crimen.

			@param lat Coordenada con la latitud (double).
		*/
		void setLatitude( double lat );

		/*!
			@brief Establece la Longitud del crimen.

			@param lon Coordenada con la longitud (double).
		*/
		void setLongitude( double lon );

		/**

			@brief Modifica los atributos del objeto crimen a partir de una cadena (string).

			Toma una cadena (string) cuyo formato es:

			"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
			FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"

			Y crea el objeto crimen a partir de dichos datos.

			@param data Objeto string a analizar.
		*/

		void setFromString( const string & data );

		/*****************************************************************/
		//
		// 	CONSULTORES


		/*!
			@brief Devuelve el ID del crimen.

			@return Número del ID ( > 0 ) (long int).
		*/
		long int getID() const;

		/*!
			@brief Devuelve el número del crimen.

			@return Número del crimen (long int).
		*/
		const string & getCaseNumber() const;

		/*!
			@brief Devuelve la fecha del crimen.

			@return Referencia constante a la fecha del crimen (fecha).
		*/
		const fecha & getDate() const;

		/*!
			@brief Devuelve la cadena IUCR del crimen.

			@return Referencia constante a la cadena de texto que contiene el IUCR (string).
		*/
		const string & getIUCR() const;

		/*!
			@brief Devuelve el tipo (primario) de crimen.

			@return Referencia constante a la cadena de texto que contiene el tipo de crimen (stirng).
		*/
		const string & getPrimaryType() const;

		/*!
			@brief Devuelve la descripción del crimen.

			@return Referencia constante a la descripción del crimen (string).
		*/
		const string & getDescription() const;

		/*!
			@brief Devuelve la descripción del lugar del crimen.

			@return Referencia constante que contiene la descripción del lugar (string).
		*/
		const string & getLocationDescription() const;

		/*!
			@brief Devuelve si ha habido algún arresto en el crimen.

			@return true si ha habido algún arresto, false si no.
		*/
		bool getArrest() const;

		/*!
			@brief Devuelve si el crimen es doméstico.

			@return true si el caso es doméstico, false si no.
		*/
		bool getDomestic() const;

		/*!
			@brief Devuelve la latitud del lugar del crimen.

			@return Latitud (double).
		*/
		double getLatitude() const;

		/*!
			@brief Devuelve la longitud del lugar del crimen.

			@return Longitud (double).
		*/
		double getLongitude() const;


		/*****************************************************************/
		//
		// 	SOBRECARGA


		/*!

			@brief Sobrecarga del operador de asignación ( = ) a partir de un objeto crimen.

			@param c Objeto crimen a copiar.
			@return Referencia a sí mismo (crimen).
		*/
		crimen & operator=(const crimen & c);

		/**

			@brief Sobrecarga del operador de asignación ( = ) a partir de una cadena (string).

			Toma una cadena (string) cuyo formato es:

			"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
			FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"

			Y crea el objeto crimen a partir de dichos datos.

			@param data Objeto string a analizar.
			@return Referencia a sí mismo (crimen).

		*/

		crimen & operator=( const string & data );

		/*!
			@brief Sobrecarga del operador de igualdad (==).

			@param c Objeto crimen con el se quiere comparar.
			@return true si son iguales, false si no.
		*/
		bool operator==(const crimen & c) const;

		/*!
			@brief Sobrecarga del operador de desigualdad ( != ).

			@param c Objeto crimen con el que se quiere comparar.
			@return true si son diferentes, false si no.
		*/
		bool operator!=(const crimen & c) const;

		/*!
			@brief Sobrecarga del operador de comparación menor ( < ).

			Compara si un crimen está antes según su ID ( y por tanto se habrá
			producido antes cronológicamente ).

			@param c Objeto crimen con el que se quiere comparar.
			@return true si es menor que c, false si no.
		*/
		bool operator<(const crimen & c) const;

		/*!
			@brief Sobrecarga del operador de comparación menor igual ( <= ).

			Compara si un crimen está antes según su ID ( y por tanto se habrá
			producido antes cronológicamente ) o si es el mismo.

			@param c Objeto crimen con el que se quiere comparar.
			@return true si es menor ( o igual ) que c, false si no.
		*/
		bool operator<=(const crimen & c) const;

		/*!
			@brief Sobrecarga del operador de comparación mayor ( > ).

			Compara si un crimen está después según su ID ( y por tanto se habrá
			producido posteriormente cronológicamente ).

			@param c Objeto crimen con el que se quiere comparar.
			@return true si es mayor que c, false si no.
		*/
		bool operator>(const crimen & c) const;

		/*!
			@brief Sobrecarga del operador de comparación mayor igual ( >= ).

			Compara si un crimen está después según su ID ( y por tanto se habrá
			producido posteriormente cronológicamente ) o si es igual.

			@param c Objeto crimen con el que se quiere comparar.
			@return true si es mayor ( o igual ) que c, false si no.
		*/
		bool operator>=(const crimen & c) const;

	private:

		friend ostream & operator<< ( ostream & os, const crimen & c );

		//Atributos
		long int ID; 							// ID del caso
		string case_number;					// Nº del caso
		fecha date;								// Fecha del caso
		string iucr;							// IUCR - Código del tipo del delito según Illinois Uniform Crime Reporting
		string primary_type;					// Tipo primario del caso
		string description;					// Descripción
		string location_description;		// Localización ( string )
		bool arrest;							// Ha habido arrestos
		bool domestic;							// Es un caso doméstico
		double latitude;						// Latitud
		double longitude;						// Longitud
};

	/*!
			@brief Sobrecarga del operador << de la biblioteca iostream.

			Muestra por pantalla los atributos del crimen:
			- ID
			- Número del caso
			- Fecha
			- IUCR
			- Tipo de crimen
			- Descripción
			- Localización ( descripción )
			- Ha habido arrestos
			- Es doméstico
			- Latitud / Longitud

			@param os Objeto "Output Stream", flujo de salida.
			@param c Objeto crimen a mostrar por la salida estándar.
			@return os, devuelve el propio flujo para poder concatenarlo.
	*/
	ostream & operator<< ( ostream & os, const crimen & c );


#include "crimen.hxx"
#endif
