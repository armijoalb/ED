/**
   @brief Fichero de implementacion de la clase fecha
*/
      //////////////////////////
      //
      //         FECHA
      //
      //////////////////////////


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
fecha::fecha(){
  sec = 0;
  min = 0;
  hour = 0;
  day = 1;
  mon = 1;
  year = 2000;
  apm = false;
}
//-----------------------------------------------------------------------------

/**
   @brief Constructor de copia.
   @param f fecha de la que copiar al objeto que se crea.
*/
fecha::fecha (const fecha & f){
   mon   = f.mon;
   day   = f.day;
   year  = f.year;
   hour  = f.hour;
   min   = f.min;
   sec   = f.sec;
   apm   = f.apm;
}
//-----------------------------------------------------------------------------

   /**
      @brief Constructor desde string.
      @param s string del que leer la fecha.
      @pre Formato "mm/dd/aaaa hh:mm:ss AM-PM"
   */
fecha::fecha (const string & s) {
   stof(s);
}
//-----------------------------------------------------------------------------

/**
   @brief Operador de asignación desde fecha.
   Crea una fecha duplicada exacta de f.
   @param f fecha a copiar.
*/
fecha & fecha::operator=(const fecha & f) {
   if (this != &f){
      year  = f.year;
      mon   = f.mon;
      day   = f.day;
      hour  = f.hour;
      min   = f.min;
      sec   = f.sec;
      apm   = f.apm;
   }
   return *this;
}
//-----------------------------------------------------------------------------

/**
   @brief Operador de asignación desde string.
   Asignar una fecha a un objeto fecha a partir de un string.
   @param s string del que copiar la fecha.
   @pre Formato "mm/dd/aaaa hh:mm:ss AM-PM".
*/
fecha & fecha::operator=(const string & s){
   stof(s);
   return *this;
}
//-----------------------------------------------------------------------------

/**
   @brief Operador "menor que".
   Comprueba si la fecha f es menor que la actual.
   @param f fecha con la que comparar la actual.
   @return True si la fecha actual es menor que f, false en otro caso.
*/
bool fecha::operator<(const fecha & f) const{

  bool menor = false;
  if (year        < f.year) menor = true;
  else if (mon    < f.mon)  menor = true;
  else if (day    < f.day)  menor = true;
  else if (hour   < f.hour) menor = true;
  else if (min    < f.min)  menor = true;
  else if (sec    < f.sec)  menor = true;
  else if (apm    < f.apm)  menor = true;

  return menor;
}
//-----------------------------------------------------------------------------

/**
   @brief Operador "mayor que"
   Comprueba si la fecha f es mayor que la actual.
   @param f fecha con la que comparar la actual.
   @return True si la fecha actual es mayor que f, false en otro caso.
*/
bool fecha::operator>(const fecha & f) const{

   bool mayor = false;
   if (year        > f.year) mayor = true;
   else if (mon    > f.mon)  mayor = true;
   else if (day    > f.day)  mayor = true;
   else if (hour   > f.hour) mayor = true;
   else if (min    > f.min)  mayor = true;
   else if (sec    > f.sec)  mayor = true;
   else if (apm    > f.apm)  mayor = true;

   return mayor;
}
//-----------------------------------------------------------------------------

/**
   @brief Operador "menor o igual que"
   Comprueba si la fecha f es menor o igual que la actual.
   @param f fecha con la que comparar la actual.
   @return True si la fecha actual es menor o igual que f, false en otro caso.
*/
bool fecha::operator<=(const fecha & f)const{

   bool menor_eq = false;
   if (year        <= f.year) menor_eq = true;
   else if (mon    <= f.mon)  menor_eq = true;
   else if (day    <= f.day)  menor_eq = true;
   else if (hour   <= f.hour) menor_eq = true;
   else if (min    <= f.min)  menor_eq = true;
   else if (sec    <= f.sec)  menor_eq = true;
   else if (apm    <= f.apm)  menor_eq = true;

   return menor_eq;
}
//-----------------------------------------------------------------------------

/**
   @brief Operador "mayor o igual que"
   Comprueba si la fecha f es mayor o igual que la actual.
   @param f fecha con la que comparar la actual.
   @return True si la fecha actual es mayor o igual que f, false en otro caso.
*/
bool fecha::operator>=(const fecha & f) const{

   bool mayor_eq = false;
   if (year        >= f.year) mayor_eq = true;
   else if (mon    >= f.mon)  mayor_eq = true;
   else if (day    >= f.day)  mayor_eq = true;
   else if (hour   >= f.hour) mayor_eq = true;
   else if (min    >= f.min)  mayor_eq = true;
   else if (sec    >= f.sec)  mayor_eq = true;
   else if (apm    >= f.apm)  mayor_eq = true;

   return mayor_eq;
}
//-----------------------------------------------------------------------------

/**
   @brief Operador "igual que".
   Compara la fecha f con la actual.
   @param f fecha con la que va a comparar la actual.
   @return True si son iguales, false en otro caso.
*/
bool fecha::operator==(const fecha & f) const{

   bool iguales = true;
   if (year       != f.year)  iguales = false;
   else if (mon   != f.mon)   iguales = false;
   else if (day   != f.day)   iguales = false;
   else if (hour  != f.hour ) iguales = false;
   else if (min   != f.min )  iguales = false;
   else if (sec   != f.sec )  iguales = false;
   else if (apm   != f.apm )  iguales = false;

   return iguales;
}
//-----------------------------------------------------------------------------

/**@brief Operador "distinto que".
Comprueba si la fecha f es distinta de f.
@param f fecha con la que va a comparar la actual.
@return True si son distintas, false en otro caso.
*/
bool fecha::operator!=(const fecha & f)const{

   bool distintos = false;
   if (year       != f.year)  distintos = true;
   else if (mon   != f.mon)   distintos = true;
   else if (day   != f.day)   distintos = true;
   else if (hour  != f.hour ) distintos = true;
   else if (min   != f.min )  distintos = true;
   else if (sec   != f.sec )  distintos = true;
   else if (apm   != f.apm )  distintos = true;

   return distintos;
}
//-----------------------------------------------------------------------------

/**
   @brief Comprobador del invariante de representación
   @return True si todos los parámetros son corrector, false en otro caso.
*/
bool fecha::check_inv (){
   bool ok = true;
   if(year  < 2000   ||
      mon   < 1      || mon   > 12 ||
      day   < 1      || day   > 31 ||
      hour  < 0      || hour  > 23 ||
      min   < 0      || min   > 59 ||
      sec   < 0      || sec   > 59  ) ok = false;

   return ok;
}
//-----------------------------------------------------------------------------

/**
   @brief Convertir la fecha a string.
   @return Un string con una fecha en el formato "mm/dd/aaaa hh:mm:ss AM-PM"
*/
string fecha::toString() const{
   string fecha;
   string tarde;
   const string   sep_date  = "/",
                  sep_time  = ":",
                  space     = " ";

   if (apm) tarde = "PM";
   else tarde = "AM";

   if (mon < 10) fecha = to_string(0) + to_string(mon);
   else fecha = to_string(mon);
   fecha += sep_date;

   if (day < 10) fecha += to_string(0) + to_string(day);
   else fecha += to_string(day);
   fecha += sep_date;

   fecha += to_string(year) + space;

   if (hour < 10) fecha += to_string(0) + to_string(hour);
   else fecha += to_string(hour);
   fecha += sep_time;

   if (min < 10) fecha += to_string(0) + to_string(min);
   else fecha += to_string(min);
   fecha += sep_time;

   if (sec < 10) fecha += to_string(0) + to_string(sec);
   else fecha += to_string(sec);
   fecha += space;

   fecha += tarde;

   return fecha;
}
//-----------------------------------------------------------------------------

/**
   @brief Dado un string
   transformar los valores a enteros y almacenarlos.
   @param s cadena de la que leer la fecha
   @pre Formato "mm/dd/aaaa hh:mm:ss AM"
*/

// Leer cada variable desde un string y tansformarlas a enteros para almacenarlas
/*
Leer de la cadena X valores (length)
Transformarlos a enteros y almacenarlo en el valor que representen (mon, day, year...)
Avanzar X posiciones (salto)
*/
void fecha::stof(const string &s){
   string tmp;
   int       ini     = 0;
   const int length  = 2, //Tam subcadena
             salto   = 3; //Tam subcadena + caracter a omitir
   /*
   El tamaño de la subcadena siempre es de 2
   excepto para year (tam = 4, salto = 5)
   */
   mon = toInteger(s, ini, length);

   ini += salto;
   day = toInteger(s, ini, length);

   ini += salto;
   year = toInteger(s, ini, 4);

   ini += 5;
   hour = toInteger(s, ini, length);

   ini += salto;
   min = toInteger(s, ini, length);

   ini += salto;
   sec = toInteger(s, ini, length);

   ini += salto;
   tmp = s.substr(ini, length);
   if(tmp == "PM")
      apm = true;
   else
      apm = false;
}
//-----------------------------------------------------------------------------

/**
   @brief Dado un string, obtiene una subcadena
   y la devuelve como entero.
   @param s cadena completa.
   @param i comienzo de la subcadena.
   @param l longitud de la subcadena.
   @return Una subcadena convertida a entero.
*/
int fecha::toInteger(const string &s, const int i, const int l) {
   string tmp;
   int final;
   tmp = s.substr(i, l);
   final = stoi(tmp);
   return final;
}
//-----------------------------------------------------------------------------

/**
   @brief Imprime fecha con el formato  mm/dd/aaaa hh:mm:ss.
   @param os Objeto "Output Stream", flujo de salida.
   @param f Objeto fecha
   @return os, devuelve el propio flujo para poder concatenarlo.
*/
ostream& operator<< ( ostream& os, const fecha & f){

   os << f.toString();

      return os;
}
