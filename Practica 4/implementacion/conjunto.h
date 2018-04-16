/*
 * conjunto.h
 *
 * Copyright  (C) Juan F. Huete
*/

#ifndef __CONJUTO_H
#define __CONJUTO_H
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "crimen.h"

using namespace std;


//! Clase conjunto
/*! Métodos--> conjunto:: conjunto(), insert(), find(),  findIUCR(), findDESCR(), erase(), size(), empty()

 * Tipos--> conjunto::entrada, conjunto::size_type

 * Tipos privados --> conjunto::conjunto_iterator, conjunto::conjunto_const_iterator

 * Descripción

* Un conjunto es un contenedor que permite almacenar en orden creciente un conjunto de elementos no repetidos.  En nuestro caso el conjunto va a tener un subconjunto restringido de métodos (inserción de elementos, consulta de un elemento, etc). Este conjunto "simulará" un conjunto de la stl, con algunas claras diferencias pues, entre otros,  no estará dotado de la capacidad de iterar (recorrer) a través de sus elementos.

* Asociado al conjunto, tendremos el tipo  \code conjunto::entrada \endcode que permite hacer referencia al elemento  almacenado en cada una de las posiciones del conjunto, en nuestro, caso delitos (crimenes). Para esta entrada el requisito es que tenga definidos el operador< y operator=

* Además encontraremos el tipo \code conjunto::size_type \endcode que permite hacer referencia al número de elementos en el conjunto.

  Los tipos privados \code conjunto::conjunto_iterator \endcode y \code conjunto::conjunto_const_iterator \endcode son una abstracción sobre un iterador de la stl
  para poder acceder y recorrer el contenedor ( STL, privado ) del conjunto.

* El número de elementos en el conjunto puede variar dinámicamente; la gestión de la memoria es automática.

 Ejemplo de su uso:
\code
...
conjunto DatosChicago, agresion;
crimen cr;

conjunto.insert(cr);
...
agresion = conjunto.findDESCR("BATTERY");

if (!agresion.empty()){
 cout <<"Tenemos "<< agresion.size() << " agresiones" << endl;
 cout << agresion << endl;
} else "No hay agresiones en el conjunto" << endl;
...
\endcode
 */

class conjunto
{
	public:

		///////////////////////////
		//
		//     Tipos públicos
		//
		///////////////////////////

		/**
			@brief entrada permite hacer referencia al elemento  almacenado en cada una de las posiciones del conjunto.
	   */
		typedef crimen entrada;

		// -------------------------------------------------------------------------------------------

		/**
			@brief size_type numero de elementos en el conjunto.
	   */
		typedef unsigned int size_type;

		// -------------------------------------------------------------------------------------------


	private:

		///////////////////////////
		//
		//     Tipos privados
		//
		///////////////////////////

		// -------------------------------------------------------------------------------------------

		/**
			@brief conjunto_iterator Iterador sobre el contenedor interno del conjunto.
		*/
		typedef vector<conjunto::entrada>::iterator conjunto_iterator;

		// -------------------------------------------------------------------------------------------

		/**
			@brief conjunto_const_iterator Iterador constante sobre el contenedor interno del conjunto.
		*/
		typedef vector<conjunto::entrada>::const_iterator conjunto_const_iterator;

		// vector ORDENADO por crimen.id que almacena los elementos del conjunto
		vector<crimen> vc;

		// -------------------------------------------------------------------------------------------

		pair< conjunto::conjunto_iterator ,bool> binarySearchID( const long int id ) ;

		pair< vector<conjunto::entrada>::const_iterator ,bool> binarySearchID( const long int id ) const;

		// -------------------------------------------------------------------------------------------

		void push_back( const conjunto::entrada & new_entrada );

		//  Declaración del operator<< como método amigo
		friend ostream &  operator << ( ostream & sal, const conjunto & D);

	public:

		///////////////////////////
		//
		//        CONJUNTO
		//
		///////////////////////////


		conjunto( );
		conjunto( vector<conjunto::entrada> & v_entrada );
		conjunto (const conjunto & d);

		pair<conjunto::entrada,bool> find( const long int id ) const;

		conjunto  findIUCR( const string & iucr) const;

		conjunto  findDESCR( const string & descr) const;

		bool insert( const conjunto::entrada & e);

		bool erase(const long int & id);

		bool erase(const  conjunto::entrada & e);

		conjunto & operator=( const conjunto & org);
		conjunto & operator=( vector<conjunto::entrada> & v_entrada );

		size_type size() const ;

		bool empty() const;

	  	bool cheq_rep( ) const;


		///////////////////////////
		//
		//       ITERADORES
		//
		///////////////////////////

      //! Clase iterator
		/**

			Clase iterator ( conjunto::iterator )

			Iterador sobre las entradas del conjunto.

			Métodos: conjunto::iterator:: iterator(), operator*(), operator++(), operator++(int), operator--(), operator--(int), operator=(), operator==(), operator!=()

			Uso:

			Se puede acceder a la primera entrada del conjunto:

			\code conjunto::iterator it = (obj_conjunto).cbegin() \endcode

			Y también al siguiente al último elemento ( no pertenece al conjunto ):

			\code conjunto::iterator it = (obj_conjunto).cend() \endcode

			También tenemos un constructor por defecto y constructor de copia, así como el operador de asignación ( = ).

			Podemos avanzar con el operador ++ ( post/pre incremento ) y compararlos  ==, !=.

		*/
		class iterator {

			private:
				// Clase amiga para poder acceder al contenedor.
				friend class conjunto;

				// Iterador sobre el contenedor del conjunto.
				conjunto_iterator iter;

				// Constructores para begin() y end().
				iterator( const conjunto_iterator & it );

			public:

				// Constructor por defecto
				iterator();

				// Constructor de copia
				iterator( const conjunto::iterator & it );

				// Operadores
				conjunto::entrada & operator*() const;
				conjunto::iterator & operator++();
				conjunto::iterator operator++(int);
				conjunto::iterator & operator--();
				conjunto::iterator operator--(int);
				conjunto::iterator & operator=( const conjunto::iterator & new_it );
				conjunto::iterator & operator + (const int & posiciones);
				conjunto::iterator & operator - (const int & posiciones);
				bool operator==( const conjunto::iterator & new_it ) const;
				bool operator!=( const conjunto::iterator & new_it ) const;

		};

      //! Clase const iterator
		/**

			Clase const_iterator ( conjunto::const_iterator )

			Iterador sobre las entradas del conjunto.

			Métodos: conjunto::const_iterator:: const_iterator(), operator*(), operator++(), operator++(int), operator--(), operator--(int), operator=(), operator==(), operator!=()

			Uso:

			Se puede acceder a la primera entrada del conjunto:

			\code conjunto::const_iterator it = (obj_conjunto).cbegin() \endcode

			Y también al siguiente al último elemento ( no pertenece al conjunto ):

			\code conjunto::const_iterator it = (obj_conjunto).cend() \endcode

			También tenemos un constructor por defecto y constructor de copia, así como el operador de asignación ( = ).

			Podemos avanzar con el operador ++ ( post/pre incremento ) y compararlos  ==, !=.

			Además los iteradores constantes pueden ser copiados o asignados ( casting ) a partir de un iterador ( conjunto::iterator ).

		*/
		class const_iterator {

			private:
				// Clase amiga para poder acceder al contenedor.
				friend class conjunto;

				// Iterador sobre el contenedor del conjunto.
				conjunto_const_iterator iter;

				// Constructores para begin(), cbegin(), end() y cend().
				const_iterator( const conjunto_iterator & it );
				const_iterator( const conjunto_const_iterator & it );

			public:

				// Constructor por defecto
				const_iterator();

				// Constructores de copia
				const_iterator( const conjunto::iterator & it );
				const_iterator( const conjunto::const_iterator & it );

				// Operadores
				const conjunto::entrada & operator*() const;
				conjunto::const_iterator & operator++();
				conjunto::const_iterator operator++(int);
				conjunto::const_iterator & operator--();
				conjunto::const_iterator operator--(int);
				conjunto::const_iterator & operator=( const conjunto::iterator & new_it );
				conjunto::const_iterator & operator=( const conjunto::const_iterator & new_it );
				conjunto::const_iterator & operator +( const int & posiciones );
				conjunto::const_iterator & operator -( const int & posiciones );
				bool operator==( const conjunto::const_iterator & new_it ) const;
				bool operator!=( const conjunto::const_iterator & new_it ) const;

		};

		///////////////////////////
		//
		//   description_iterator
		//
		///////////////////////////

      //! Clase description iterator

		/**
         Clase description_iterator (conjunto::description_iterator)
         Iterador sobre las entradas del conjunto en cuya descripción hay una coincidencia con "descrp"

         Métodos:
         conjunto::description_iterator:: description_iterator(), operator*(), operator++(), operator++(int), operator--(), operator--(int), operator=(), operator==(), operator!=()

         Uso:
         Se puede acceder a la primera entrada del conjunto cuya descripción tiene una coincidencia con "descrp":
         \code conjunto::description_iterator diter = (obj_conjunto).dbegin() \endcode
         Y también al siguiente al último elemento (no pertenece al conjunto):
         \code conjunto::description_iterator diter = (obj_conjunto).dend() \endcode

         También tenemos un constructor por defecto y constructor de copia, así como el operador de asignación =.
         Podemos avanzar con el operador ++ ( post/pre incremento ), retroceder con el operador -- (post/pre decremento), compararlos  ==, !=
         y obtener una expresión equivalente al valor contenido en el elemento al que apunta el iterador *.
		*/
      class description_iterator{
         private:
            // Clase amiga para poder acceder al contenedor.
            friend class conjunto;

				// Iteradores para indicar el inicio y el final.
            conjunto::iterator ini;
				conjunto::iterator end;

				// Iterador sobre el contenedor del conjunto.
				conjunto::iterator current;

            // Descripción de los crímenes sobre los que vamos a iterar.
            string descrp;

            // Constructores para dbegin() y dend().
            description_iterator( const conjunto::iterator & new_ini, const conjunto::iterator & new_end, const string &new_descrp );

				void moveToEnd();

         public:
            // Constructor por defecto.
            description_iterator();

            // Constructor de copia.
            description_iterator(const conjunto::description_iterator &it);

            // Sobrecarga de operadores.
            conjunto::entrada & operator*() const;
            conjunto::description_iterator operator++ (int);
            conjunto::description_iterator & operator++ ();
            conjunto::description_iterator operator-- (int);
            conjunto::description_iterator & operator-- ();
            conjunto::description_iterator & operator= (const conjunto::description_iterator &it);
            bool operator== (const conjunto::description_iterator &it) const;
            bool operator!= (const conjunto::description_iterator &it) const;

      };

      //! Clase const description iterator
      /**
			Clase const_description_iterator (conjunto::const_description_iterator)
			Iterador sobre las entradas del conjunto.

			Métodos:
         conjunto::const_description_iterator:: const_description_iterator(), operator*(), operator++(), operator++(int), operator--(), operator--(int), operator=(), operator==(), operator!=()

         Uso:
         Se puede acceder a la primera entrada del conjunto cuya descripción tiene una coincidencia con "descrp":
         \code conjunto::const_description_iterator cditer = (obj_conjunto).cdbegin() \endcode
         Y también al siguiente al último elemento (no pertenece al conjunto):
         \code conjunto::const_description_iterator cditer = (obj_conjunto).dend() \endcode

         También tenemos un constructor por defecto y constructor de copia, así como el operador de asignación =.
         Podemos avanzar con el operador ++ ( post/pre incremento ), retroceder con el operador -- (post/pre decremento), compararlos  ==, !=
         y obtener una expresión equivalente al valor contenido en el elemento al que apunta el iterador *.

			Además, los iteradores constantes pueden ser copiados o asignados (casting) a partir de un iterador (conjunto::description_iterator).
		*/
      class const_description_iterator{
         private:
            // Clase amiga para poder acceder al contenedor.
            friend class conjunto;

            // Iteradores para indicar el principio y el final.
            conjunto::const_iterator ini;
            conjunto::const_iterator end;

            // Iterador sobre el contenedor del conjunto.
            conjunto::const_iterator current;


            // Descripción de los crímenes sobre los que vamos a iterar.
            string descrp;

            // Constructores para cdbegin() cdend().
            const_description_iterator(const conjunto::const_iterator &new_ini, const conjunto::const_iterator &new_end, const string &new_descrp);
            const_description_iterator(const conjunto::iterator &new_ini, const conjunto::iterator &new_end, const string &new_descrp);

            // Método para mover current a fin.
            void moveToEnd();
         public:
            // Constructor por defecto.
            const_description_iterator();

            // Constructores de copia.
            const_description_iterator(const conjunto::description_iterator &it);
            const_description_iterator(const conjunto::const_description_iterator &it);

            // Sobrecarga de operadores.
            const conjunto::entrada & operator*() const;
            conjunto::const_description_iterator operator++ (int);
            conjunto::const_description_iterator & operator++ ();
            conjunto::const_description_iterator operator-- (int);
            conjunto::const_description_iterator & operator-- ();
            conjunto::const_description_iterator & operator= (const conjunto::const_description_iterator &it);
            bool operator== (const conjunto::const_description_iterator &it) const;
            bool operator!= (const conjunto::const_description_iterator &it) const;
      };

      //! Clase arrest iterator
		/**
			Clase arrest_iterator ( conjunto::arrest_iterator )

			Iterador sobre las entradas del conjunto en cuyo crimen ha habido un arresto.

			Métodos: conjunto::arrest_iterator:: arrest_iterator(), operator*(), operator++(), operator++(int), operator--(), operator--(int), operator=(), operator==(), operator!=()

			Uso:

			Acceso al primer crimen del conjunto con arresto:

			\code conjunto::arrest_iterator it = (obj_conjunto).abegin() \endcode

			Acceso al último crimen del conjunto con arresto:
			\code conjunto::arrest_iterator it = (obj_conjunto).aend() \endcode

         También tenemos un constructor por defecto y constructor de copia, así como el operador de asignación =.
         Podemos avanzar con el operador ++ ( post/pre incremento ), retroceder con el operador -- (post/pre decremento), compararlos  ==, !=
         y obtener una expresión equivalente al valor contenido en el elemento al que apunta el iterador *.
		*/
      class arrest_iterator{

			private:
				// Clase amiga para poder acceder al contenedor.
				friend class conjunto;

            // Iteradores para indicar el principio y el final.
            conjunto::iterator ini;
            conjunto::iterator end;

            // Iterador sobre el contenedor del conjunto.
            conjunto::iterator current;

				// Mover al último elemento
				void moveToEnd();

				// Constructor para abegin() y aend()
				arrest_iterator( const conjunto::iterator & new_ini, const conjunto::iterator & new_end );

			public:
				// Constructor por defecto
				arrest_iterator();

				// Constructor de copia
				arrest_iterator( const conjunto::arrest_iterator & new_it );

				// Operadores
				conjunto::entrada & operator*() const;
				conjunto::arrest_iterator & operator++();
				conjunto::arrest_iterator operator++(int);
				conjunto::arrest_iterator & operator--();
				conjunto::arrest_iterator operator--(int);
				conjunto::arrest_iterator & operator=( const conjunto::arrest_iterator & new_it );
				bool operator==( const conjunto::arrest_iterator & new_it ) const;
				bool operator!=( const conjunto::arrest_iterator & new_it ) const;
      };

      //! Clase const arrest iterator
		/**
         Clase const_arrest_iterator ( conjunto::const_arrest_iterator )

         Iterador constante sobre las entradas del conjunto en cuyo crimen haya habido un arresto.

         Métodos: conjunto::const_arrest_iterator::const_arrest_iterator(), operator*(), operator++(), operator++(int), operator--(), operator--(int), operator=(), operator==(), operator!=()

         Uso:

         Acceso al primer crimen del conjunto con arresto:

         \code conjunto::const_arrest_iterator it = (obj_conjunto).cabegin() \endcode

         Acceso al último crimen del conjunto con arresto:
         \code conjunto::const_arrest_iterator it = (obj_conjunto).caend() \endcode

         También tenemos un constructor por defecto y constructor de copia, así como el operador de asignación =.
         Podemos avanzar con el operador ++ ( post/pre incremento ), retroceder con el operador -- (post/pre decremento), compararlos  ==, !=
         y obtener una expresión equivalente al valor contenido en el elemento al que apunta el iterador *.

			Además, los iteradores constantes pueden ser copiados o asignados (casting) a partir de un iterador (conjunto::arrest_iterator).
		*/
				class const_arrest_iterator{

					private:
						// Clase amiga para poder acceder al contenedor.
						friend class conjunto;

                  // Iteradores para indicar el principio y el final.
                  conjunto::const_iterator ini;
                  conjunto::const_iterator end;

                  // Iterador sobre el contenedor del conjunto.
                  conjunto::const_iterator current;

                  // Constructores para cabegin() caend().
                  const_arrest_iterator(const conjunto::const_iterator &new_ini, const conjunto::const_iterator &new_end);
                  const_arrest_iterator(const conjunto::iterator &new_ini, const conjunto::iterator &new_end);

                  // Método para mover current a fin.
                  void moveToEnd();
					public:
						// Constructor por defecto
						const_arrest_iterator();

						// Constructor de copia
						const_arrest_iterator( const conjunto::arrest_iterator & it );
                  const_arrest_iterator( const conjunto::const_arrest_iterator & it );

						// Operadores
						const conjunto::entrada & operator*() const;
						conjunto::const_arrest_iterator & operator++();
						conjunto::const_arrest_iterator operator++(int);
						conjunto::const_arrest_iterator & operator--();
						conjunto::const_arrest_iterator operator--(int);
						conjunto::const_arrest_iterator & operator=(const conjunto::const_arrest_iterator & new_it);
						bool operator==(const conjunto::const_arrest_iterator & new_it) const;
						bool operator!=(const conjunto::const_arrest_iterator & new_it) const;
				};


      // Métodos iterator
		conjunto::iterator begin();
		conjunto::iterator end();

		// Métodos const_iterator
		conjunto::const_iterator cbegin() const;
		conjunto::const_iterator cend() const;

      // Métodos description_iterator
      conjunto::description_iterator dbegin(const string & descrp);
      conjunto::description_iterator dend(const string & descrp);

      // Métodos const_description_iterator
      conjunto::const_description_iterator cdbegin(const string & descrp) const;
      conjunto::const_description_iterator cdend(const string & descrp) const;

      // Métodos arrest_iterator
      conjunto::arrest_iterator abegin();
		conjunto::arrest_iterator aend();

      // Métodos const_arrest_iterator
      conjunto::const_arrest_iterator cabegin();
		conjunto::const_arrest_iterator caend();

};


ostream &  operator<<( ostream & sal, const conjunto & D);


	///////////////////////////
	//
	//     IMPLEMENTACIÓN
	//
	///////////////////////////

#include "conjunto.hxx"

#endif
