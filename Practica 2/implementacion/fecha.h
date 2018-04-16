/*
 * fecha.h
 *
 * Copyright  (C) Juan F. Huete
*/

#ifndef __FECHA_H
#define __FECHA_H

#include <string>
#include <iostream>

using namespace std;

//! Clase fecha.
/*!
 * \b Constructores
 * fecha::fecha ()

 * \b Sobrecarga de operadores
 * fecha::operator=(), operator==(), operator<(), operator<=(),
 * operator>(), operator>=(), operator!=(), operator<<()

 * \b Modificadores de tipo
 * fecha::toInteger(), stof(), toString().

 * \b Comprobante
 * fecha::check_inv()

 * \b Descripción

 * Contiene toda la información asociada a una fecha con el formato  "mm/dd/aaaa hh:mm:ss AM-PM".
 * Se usará el formato de 12 horas, referenciando la mañana o la tarde con AM o PM.

 * Es necesario compilar con C++11, para ello, se añade la opción -std=c++0x a g++.

 * <b> Función de abstracción </b>

 * Cada unidad temporal de la fecha se instancia en un entero , teniendo:
 * \verbatim
     mes      = mon
     día      = day
     año      = year
     hora     = hour
     minuto   = min
     segundo  = sec
  \endverbatim
 *    El periodo del día (AM o PM) se instancia en un booleano booleano

 * \invariant
 * 1 <=  mon   <= 12
 * 1 <=  day   <= 31
 * year >= 2000
 * 0 <= hour   <= 12
 * 0 <= min    <= 59
 * 0 <= sec    <= 59

 * <b> Ejemplo de uso </b>
 *
 * Crear objeto:
 * \code
 * fecha a;
 * fecha b("mm/dd/aaaa hh:mm:ss AM");
 * fecha c(b);
 * \endcode

 * La sobrecarga del operador = nos permite:
 * \code
 * a = "mm/dd/aaaa hh:mm:ss AM";
 * c = a;
 * \endcode

 * Podemos comparar dos fechas:
 * \code
 * bool t = a > b || a == c;

 * bool g = c <= b || b != a;
 * \endcode

 * Y podemos mostrar una fecha por pantalla:
 * \code
 * cout << a;
 * \endcode

*/
class fecha {

public:

   /**@brief Constructor por defecto.
   \verbatim
   mon   = 1
   day   = 1
   year  = 2000
   hour  = 0
   min   = 0
   sec   = 0
   apm   = false
   \endverbatim
   */
   fecha ();

   /**@brief Constructor desde string.
   @param s string del que leer la fecha.
   @pre Formato "mm/dd/aaaa hh:mm:ss AM-PM"
   */
   fecha (const string & s);

   /**@brief Constructor de copia.
   @param f fecha de la que copiar al objeto que se crea.
   */
   fecha (const fecha & f);

   /**@brief Operador de asignación.
   Crea una fecha duplicada exacta de f.
   @param f fecha a copiar.
   */
   fecha & operator=(const fecha & f);

   /**@brief Operador de asignación.
   Asignar una fecha a un objeto fecha a partir de un string.
   @param s string del que copiar la fecha.
   @pre Formato "mm/dd/aaaa hh:mm:ss AM-PM".
   */
   fecha & operator=(const string & s);

   /**@brief Convertir la fecha a string.
   @return Un string con una fecha en el formato "mm/dd/aaaa hh:mm:ss AM-PM"
   */
   string toString() const;

   /**@brief Operador "igual que".
   Compara la fecha f con la actual.
   @param f fecha con la que va a comparar la actual.
   @return True si son iguales, false en otro caso.
   */
   bool operator==(const fecha & f) const;

   /**@brief Operador "menor que".
   Comprueba si la fecha f es menor que la actual.
   @param f fecha con la que comparar la actual.
   @return True si la fecha actual es menor que f, false en otro caso.
   */
   bool operator<(const fecha & f)const;

   /**@brief Operador "mayor que"
   Comprueba si la fecha f es mayor que la actual.
   @param f fecha con la que comparar la actual.
   @return True si la fecha actual es mayor que f, false en otro caso.
   */
   bool operator>(const fecha & f) const;

   /**@brief Operador "menor o igual que"
   Comprueba si la fecha f es menor o igual que la actual.
   @param f fecha con la que comparar la actual.
   @return True si la fecha actual es menor o igual que f, false en otro caso.
   */
   bool operator<=(const fecha & f)const;

   /**@brief Operador "mayor o igual que"
   Comprueba si la fecha f es mayor o igual que la actual.
   @param f fecha con la que comparar la actual.
   @return True si la fecha actual es mayor o igual que f, false en otro caso.
   */
   bool operator>=(const fecha & f) const;

   /**@brief Operador "distinto que".
   Comprueba si la fecha f es distinta de f.
   @param f fecha con la que va a comparar la actual.
   @return True si son distintas, false en otro caso.
   */
   bool operator!=(const fecha & f)const;

   /**@brief Comprobador del invariante de representación
   @return True si todos los parámetros son corrector, false en otro caso.
   */
   bool check_inv ();
private:

   /**@brief Segundos
   */
   int  sec;

   /**@brief Minutos
   */
   int  min;

   /**@brief Horas
   */
   int  hour;

   /**@brief Día del mes
   */
   int  day;

   /**@brief Mes
   */
   int  mon;

   /**@brief Año
   */
   int  year;

   /**@brief AM/PM
   @post AM = false, PM = true
   */
   bool apm;

   /**@brief Dado un string, obtiene una subcadena
   y la devuelve como entero.
   @param s cadena completa.
   @param i comienzo de la subcadena.
   @param l longitud de la subcadena.
   @return Una subcadena convertida a entero.
   */
   int toInteger(const string &s, const int i, const int l);

   /**@brief Dado un string
   transformar los valores a enteros y almacenarlos.
   @param s cadena de la que leer la fecha
   @pre Formato "mm/dd/aaaa hh:mm:ss AM"
   */
   void stof(const string &s);

   /* @brief Imprime fecha con el formato  mm/dd/aaaa hh:mm:ss.
   @param os Objeto "Output Stream", flujo de salida.
   @param f Objeto fecha
   @return os, devuelve el propio flujo para poder concatenarlo.
   */
   friend  ostream& operator<< ( ostream& os, const fecha & f);
};

   ostream& operator<< ( ostream& os, const fecha & f);

#include "fecha.hxx" // Incluimos la implementacion.


#endif
