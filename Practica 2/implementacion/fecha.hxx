/** @brief Fichero de implementacion de la clase fecha

*/

// Constructor por defecto
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

// Constructor de copia
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

// Constructor desde string
fecha::fecha (const string & s) {
   stof(s);
}
//-----------------------------------------------------------------------------

// Sobrecarga del operador "=" para fecha = fecha
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

//Sobrecarga del operador "=" para fecha = string
fecha & fecha::operator=(const string & s){
   stof(s);
   return *this;
}
//-----------------------------------------------------------------------------

//Devolver fecha como string en el formato mm/dd/aaaa hh:mm:aa AM
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

// Sobrecarga del operador ==
bool fecha::operator==(const fecha & f) const{

   bool iguales = false;
   if (year       == f.year)  iguales = true;
   else if (mon   == f.mon)   iguales = true;
   else if (day   == f.day)   iguales = true;
   else if (hour  == f.hour ) iguales = true;
   else if (min   == f.min )  iguales = true;
   else if (sec   == f.sec )  iguales = true;
   else if (apm   == f.apm )  iguales = true;

   return iguales;
}
//-----------------------------------------------------------------------------

// Sobrecarga del operador <
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

// Sobrecarga del operador >
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

// Sobrecarga del operador <=
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

// Sobrecarga del operador >=
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

// Sobrecarga del operador !=
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

// Implementación del comprobante del invariante de representación
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

// Devolver como entero una subcadena de una cadena s
int fecha::toInteger(const string &s, const int i, const int l) {
   string tmp;
   int final;
   tmp = s.substr(i, l);
   final = stoi(tmp);
   return final;
}
//-----------------------------------------------------------------------------

// Sobrecarga del operador <<
ostream& operator<< ( ostream& os, const fecha & f){

   os << f.toString();

      return os;
}
