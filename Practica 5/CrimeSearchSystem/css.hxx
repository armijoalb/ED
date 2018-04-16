/*
 * Implementación métodos de la clase CSS.
 *
 * Alberto Armijo Ruiz.
 * 2º GII A.
 *
*/

#include <fstream>

/**
  @brief Constructor por defecto.
*/
CSS::CSS(){}


/**
  @brief Crea un nuevo CSS a partir de el nombre de un archivo.
  @param nombreDB nombre del archivo que contiene los datos del conjunto.
*/
void CSS::load( string nombreDB ){
  ifstream fe;
  string cadena;

  // Abrimos el fichero.
  fe.open(nombreDB.c_str(), ifstream::in);

  // Comprobamos que no ha habido fallo para poder cargarlo.
  if( !fe.fail() ){
    getline(fe,cadena,'\n'); //leo la cabecera del fichero

    while( !fe.eof() ){
      getline(fe,cadena,'\n');

      Crimen aux = cadena;

      insert( aux );
    }
  }
}


/**
  @brief Inserta un nuevo Crimen en el conjunto.
  @param x nuevo crimen a insertar.
  @pre el crimen no está dentro del conjunto antes de insertarse.
*/
void CSS::insert( const Crimen & x ){
  ID id = x.getID();
  IUCR iucr = x.getIUCR();
  Termino descr = x.getDescription();
  Longitud lon = x.getLongitude();
  Latitud lat = x.getLatitude();

  // ******************************************************************************************************** //

  // Insertamos el crimen en baseDatos.
  baseDatos.insert(std::pair<ID, Crimen>(id, x) );

  // ******************************************************************************************************** //

  // Insertamos en el multimap.
  DateAccess.insert(std::pair<Date, map<ID, Crimen>::iterator>(x.getDate(), baseDatos.find(id) ) );

  // ******************************************************************************************************** //

  // Insertamos en IUCRAccess.
  // Comprobamos si no está.
  if( IUCRAccess.find( iucr ) == IUCRAccess.end()){
    set<ID> s_iucr;
    s_iucr.insert(id);
    IUCRAccess.insert(std::pair<IUCR, set<ID> >(iucr, s_iucr) );
  }
  else{
    // Añadimos el id al set.
    IUCRAccess[iucr].insert( id );
  }

  // ******************************************************************************************************** //

  // Insertamos en index.
  // Comprobamos si no está.

  Termino term;
  int ini = 0;
  // Calculamos el primer espacio.
  int fin = descr.find_first_of( ' ', ini);

  while( ini < fin ){
    term = descr.substr( ini, (fin-ini) );

    if( index.find( term ) == index.end() ){
      set<ID> s_term;
      s_term.insert(id);
      index.insert(std::pair<Termino, set<ID> >(term, s_term) );
    }
    else{
      // Añadimos el id al set.
      index[term].insert( id );
    }

    // Calculamos el siguiente.
    ini = fin + 1;
    fin = descr.find_first_of( ' ', ini);
  }

  // Añadimos la última palabra de la descripción.
  term = descr.substr( ini, (fin-ini) );
  if( index.find( term ) == index.end() ){
    set<ID> s_term;
    s_term.insert(id);
    index.insert(std::pair<Termino, set<ID> >(term, s_term) );
  }
  else{
    // Añadimos el id al set.
    index[term].insert( id );
  }

  // ******************************************************************************************************** //

  // Insertamos en el posicionesGeo.
  // Comprobamos si la longitud ya está.
  if( posicionesGeo.find( lon ) == posicionesGeo.end() ){
    multimap<Latitud, ID> multim;
    multim.insert(std::pair<Latitud, ID>( lat, id) );
    posicionesGeo.insert(std::pair<Longitud, multimap<Latitud, ID> >( lon, multim ) );
  }
  else{
    // Añadimos al multimap.
    posicionesGeo[lon].insert(std::pair<Latitud, ID>( lat, id ) );
  }

  // ******************************************************************************************************** //
}

/**
  @brief Elimina un Crimen del conjunto.
  @param id ID del Crimen que queremos borrar.
  @return True si el crimen se ha podido borrar, false si no.
*/
bool CSS::erase( ID id ){
  bool borrado = true;

  // Comprobamos que el id está en el conjunto.
  if( baseDatos.find( id ) != baseDatos.end() ){
    // ******************************************************************************************************** //
    //Borramos la entrada en DateAccess con el id.
    DateAccess.erase( baseDatos[id].getDate() );

    // ******************************************************************************************************** //

    // Borramos el id del set de IUCRAccess.
    IUCRAccess[ baseDatos[id].getIUCR() ].erase( id );

    // ******************************************************************************************************** //

    // Borramos el id del set de index.
    Termino descr = baseDatos[id].getDescription();
    Termino term;
    int ini = 0;
    int fin = descr.find_first_of( ' ', ini);

    while( ini < fin ){
      term = descr.substr( ini, (fin-ini) );

      index[ term ].erase( id );

      // Borramos la entrada en el unordered_map si el set está vacío.
      if( index[term].size() == 0 )
        index.erase( term );

      ini = fin + 1;
      fin = descr.find_first_of( ' ', ini );
    }

    // Borramos el último término de la descripción.
    term = descr.substr( ini, (fin-ini) );
    index[ term ].erase( id );

    // Borramos la entrada en el unordered_map si el set está vacío.
    if( index[term].size() == 0 )
      index.erase( term );


    // ******************************************************************************************************** //


    // Borramos la entrada del multimap con el id.
    posicionesGeo[ baseDatos[id].getLongitude() ].erase( baseDatos[id].getLatitude() );

    // Borramos la entrada del map si la entrada en baseDatos[id].getLongitude está vacía.
    if( posicionesGeo[ baseDatos[id].getLongitude() ].size() == 0)
      posicionesGeo.erase( baseDatos[id].getLongitude() );

    // ******************************************************************************************************** //

    // Borramos el id de la base de datos.
    baseDatos.erase( id );

    // ******************************************************************************************************** //
  }
  else{
    borrado = false;
  }

  return borrado;
}

/**
  @brief Busca un Crimen en el conjunto.
  @param id ID del conjunto que buscamos.
  @return Un iterator de la clase CSS si lo encuentra, si no lo encuentra, el iterator apunta a baseDatos.end().
*/
CSS::iterator CSS::find_ID( const ID id ){
  // Buscamos el elemento en la base de datos.
  CSS::iterator it( baseDatos.find( id ) );

  // Devolvemos el elemento.
  return it;
}

/**
  @bried Modifica el valor de arrest en el Crimen especificado.
  @param id ID del Crimen que buscamos, value nuevo valor del atributo arrest del Crimen.
*/
void CSS::setArrest( const ID id , bool value ){
  // Comprobamos que el elemento esté en la base de datos.
  if( baseDatos.find( id ) != baseDatos.end() ){
    baseDatos[id].setArrest( value );
  }
}

/**
  @brief Busca y inserta en una lista todos los IDs de Crimenes que están dentro de las coordenadas.
  @param x1 Longitud inicio, y1 Latitud inicio, x2 Longitud fin, y2 Latitud fin.
  @return Una lista con los IDs de Crimenes que entran dentro de las coordenas.
  @pre x1 < x2 y y1 < y2.
*/
list<ID> CSS::inArea( Longitud x1, Latitud y1, Longitud x2, Latitud y2 ){
  // Lista en la que metemos los id.
  list<ID> salida;

  // Calculamos los extremos de la longitud recorrida.
  map<Longitud, multimap<Latitud, ID> >::iterator ini_longitud = posicionesGeo.find(x1);
  map<Longitud, multimap<Latitud, ID> >::iterator fin_longitud = posicionesGeo.find(x2)++;

  // Recorremos los elementos del map que se encuentren entre los extremos [x1,x2].
  for( ; ini_longitud != fin_longitud ; ini_longitud++){
    multimap<Latitud, ID>::iterator ini_latitud = ini_longitud->second.begin();
    multimap<Latitud, ID>::iterator fin_latitud = ini_longitud->second.end();

    // Recorremos el multimap de cada una de las longitudes.
    for( ; ini_latitud != fin_latitud ; ini_latitud ++){
      // Añadimos a la lista un id nuevo si su latitud se encuentra dentro del intervalo [y1,y2]
      if( ini_latitud->first >= y1 && ini_latitud->first <= y2 ){
        salida.push_back( ini_latitud->second );
      }
    }
  }

  return salida;
}

// --------------------------------------------------------------------------------------------------
// Métodos consulta libre.
// --------------------------------------------------------------------------------------------------

/**
  @brief Calcula un map con los pesos de los IDs.
  @param m mapa que contiene los IDs y su peso, t_i set de IDs de cada una de las entradas de index.
*/
void CSS::unionPeso( map<ID, float> & m, const set<ID> & t_i ){

  // Recorremos el set.
  for( set<ID>::iterator it = t_i.begin() ; it != t_i.end() ; it ++){
    // Comprobamos si el elemento ya se encuentra en el mapa.
    if( m.find( *it ) != m.end() ){
      // Incrementamos el valor del segundo parámetro en 1.0
      m[*it] += 1.0;
    }
    else{
      // Añadimos un nuevo ID al mapa.
      m.insert( std::pair<ID, float>( *it, 1.0) );
    }
  }

}

/**
  @brief Consulta libre por una lista de terminos.
  @param q lista de Terminos que buscamos, k número de elementos que tendrá el vector de salida.
  @return Un vector de pares con ID y su peso.
*/
vector<pair<ID,float> > CSS::Query( list<string> & q, int k){
  // Contenedor que devolvemos.
  vector<pair<ID,float> >salida;

  // Metemos los elementos de la lista en un mapa.
  map<ID, float> aux;

  for(  list<string>::iterator it_lista = q.begin(); it_lista != q.end() ; it_lista++){
    unionPeso(aux, index.find( *it_lista )->second );
  }


  // Metemos los elementos en la priority_queue.
  priority_queue< pair<ID, float>, vector<pair<ID, float> >, my_comp > cola_prioridad;
  map<ID, float>::iterator it_aux = aux.begin();

  // Primero, metemos los k primeros elementos.
  for( int i = 0 ; i < k ; i++){
    cola_prioridad.push( std::pair<ID, float>( it_aux->first, it_aux->second ) );
    it_aux ++;
  }

  // Ahora, metemos los k mejores.
  my_comp comparar;

  for( ; it_aux != aux.end() ; it_aux++){
    if( comparar( *it_aux, cola_prioridad.top() ) ){
      // Quitamos el elemento del tope.
      cola_prioridad.pop();
      // Metemos el nuevo elemento.
      cola_prioridad.push( std::pair<ID, float>( it_aux->first, it_aux->second ) );
    }
  }

  // Finalmente, metemos los elementos en el vector.
  while( !cola_prioridad.empty() ){
    salida.push_back( cola_prioridad.top() );
    cola_prioridad.pop();
  }

  // Devolvemos el vector.
  return salida;
}


// --------------------------------------------------------------------------------------------------
// Clase my_comp. Functor para comprar elementos de un pair de float.
// --------------------------------------------------------------------------------------------------

/**
  @brief Sobrecarga del operador ().
  @param lhs primer par, rhs segundo par.
  @return True si el float de lhs es mayor que el de rhs, false si no lo es.
*/
bool CSS::my_comp::operator () (const std::pair<ID, float> & lhs, const std::pair<ID, float> & rhs ) const{
  return (lhs.second) > (rhs.second);
}


// --------------------------------------------------------------------------------------------------
// Clase iterator.
// --------------------------------------------------------------------------------------------------

/**
  @brief Constructor por defecto.
*/
CSS::iterator::iterator(){
}

/**
  @brief Constructor de copia.
  @param iter iterador a baseDatos.
*/
CSS::iterator::iterator(  const map<ID, Crimen>::iterator & iter ){
  it = iter ;
}

/**
  @brief Sobrecarga del operador *.
  @return Una referencia a un par de ID, Crimen.
*/
pair<const ID, Crimen> & CSS::iterator::operator *(){

  // Devolvemos el contenido del iterador.
  return *it;
}

/**
  @brief Operador de pre-incremento.
  @return Una referencia a el objeto incrementado.
*/
CSS::iterator & CSS::iterator::operator ++(){
  // Incrementamos
  it++;

  return *this;
}

/**
  @brief Operador de post-incremento.
  @return Una copia de sí mismo, después se incrementa.
*/
CSS::iterator CSS::iterator::operator++( int ){
  // Hacemos una copia.
  CSS::iterator orig = *this;

  // Incrementamos.
  ++(*this);

  // Devolvemos la copia.
  return orig;
}

/**
  @brief Operador de post-decremento.
  @return Una copia de sí mismo, después se decrementa.
*/
CSS::iterator CSS::iterator::operator --( int ){
  // Hacemos una copia.
  CSS::iterator orig = *this;

  // Decrementamos.
  --(*this);

  // Devolvemos la copia.
  return orig;
}

/**
  @brief Operador de pre-decremento.
  @return Una referencia al objeto decrementado.
*/
CSS::iterator & CSS::iterator::operator --(){
  // Decrementamos.
  it--;

  return *this;
}


/**
  @brief Método que permite acceder al primer elemento de baseDatos.
  @return Un CSS::iterator apuntando a el primer elemento de baseDatos.
*/
CSS::iterator CSS::begin(){
  return CSS::iterator( baseDatos.begin() );
}

/**
  @brief Método que permite acceder al último elemento de baseDatos.
  @return Un CSS::iterator apuntando a el último elemento de baseDatos.
*/
CSS::iterator CSS::end(){
  return CSS::iterator( baseDatos.end() );
}


/**
  @brief Operador de desigualdad.
  @return True si no son iguales, false si lo son.
*/
bool CSS::iterator::operator != ( const CSS::iterator & iter ){
  return it != iter.it;
}

/**
  @brief Operador de igualdad.
  @return True si son iguales, false si no.
*/
bool CSS::iterator::operator == ( const CSS::iterator & iter ){
  return it == iter.it;
}

// --------------------------------------------------------------------------------------------------
// Clase Date_iterator.
// --------------------------------------------------------------------------------------------------

/**
  @brief Constructor por defecto.
*/
CSS::Date_iterator::Date_iterator(){
}

/**
  @brief Contructor de copia.
  @param iter iterador de DateAccess.
*/
CSS::Date_iterator::Date_iterator( const multimap<Date, map<ID, Crimen>::iterator >::iterator & iter){
  it_mm = iter;
}

/**
  @brief Sobrecarga del operador *.
  @return Una referencia a un par de ID, Crimen.
*/
pair<const ID, Crimen> & CSS::Date_iterator::operator * (){

  //Devolvemos el iterador del segundo argumento.
  return (*(*it_mm).second );
}

/**
  @brief Operador de pre-incremento.
  @return Una referencia a el objeto incrementado.
*/
CSS::Date_iterator & CSS::Date_iterator::operator ++(){
  // Incrementamos.
  it_mm ++;

  return *this;
}

/**
  @brief Operador de pre-decremeto.
  @return Una referencia a el objeto decrementado.
*/
CSS::Date_iterator & CSS::Date_iterator::operator --(){
  // Decrementamos.
  it_mm--;

  return *this;
}

/**
  @brief Operador de post-incremento.
  @return Una copia de sí mismo, después se incrementa.
*/
CSS::Date_iterator CSS::Date_iterator::operator ++ (int){
  // Creamos una copia.
  CSS::Date_iterator orig = *this;

  // Incrementamos.
  ++(*this);

  // Devolvemos la copia.
  return orig;
}

/**
  @brief Operador de post-decremento.
  @return Una copia de sí mismo, después se decrementa.
*/
CSS::Date_iterator CSS::Date_iterator::operator --( int ){
  // Creamos una copia.
  CSS::Date_iterator orig = *this;

  // Decrementamos.
  --(*this);

  // Devolvemos la copia.
  return orig;
}

/**
  @brief Operador de igualdad.
  @return True si son iguales, false si no.
*/
bool CSS::Date_iterator::operator ==( const Date_iterator & iter){
  return it_mm == iter.it_mm;
}

/**
  @brief Operador de desigualdad.
  @return True si no son iguales, false si lo son.
*/
bool CSS::Date_iterator::operator !=( const Date_iterator & iter){
  return it_mm != iter.it_mm;
}

/**
  @brief Método que permite acceder al primer elemento de DateAccess.
  @return Un CSS::iterator apuntando a el primer elemento de DateAccess.
*/
CSS::Date_iterator CSS::dbegin(){
  return CSS::Date_iterator( DateAccess.begin() );
}

/**
  @brief Método que permite acceder al último elemento de DateAccess.
  @return Un CSS::iterator apuntando a el último elemento de DateAccess.
*/
CSS::Date_iterator CSS::dend(){
  return CSS::Date_iterator( DateAccess.end() );
}

/**
  @brief Devuelve la cota inferior de una fecha.
  @param fecha fecha cuya cota inferior queremos saber.
  @return Un CSS::Date_iterator apuntando a la cota inferior, dend() si no hay cota inferior.
*/
CSS::Date_iterator CSS::lower_bound( Date fecha ){
  return CSS::Date_iterator( DateAccess.lower_bound( fecha ) );
}

/**
  @brief Devuelve la cota superior de una fecha.
  @param fecha fecha cuya cota superior queremos saber.
  @return Un CSS::Date_iterator apuntando a la cota superior, dend() si no hay cota superior.
*/
CSS::Date_iterator CSS::upper_bound( Date fecha ){
  return CSS::Date_iterator( DateAccess.upper_bound( fecha ) );
}

// --------------------------------------------------------------------------------------------------
// Clase IUCR_iterator.
// --------------------------------------------------------------------------------------------------

/**
  @brief Constructor por defecto.
  @param p referencia a la clase CSS.
*/
CSS::IUCR_iterator::IUCR_iterator(CSS & p)
:parent(p){
}

/**
  @brief Constructor de copia.
  @param iter_m iterador a IUCRAccess , p referencia a la clase CSS.
*/
CSS::IUCR_iterator::IUCR_iterator( const map<IUCR, set<ID> >::iterator & iter_m, CSS & p)
:parent(p){
  it_m = iter_m;
  it_s = (*iter_m).second.begin();
}

/**
  @brief Sobrecarga del operador *.
  @return Una referencia a un par de ID, Crimen.
*/
pair<const ID, Crimen> & CSS::IUCR_iterator::operator * (){
   return *(parent.baseDatos.find( *it_s ) );
}

/**
  @brief Operador de pre-incremento.
  @return Una referencia a el objeto incrementado.
*/
CSS::IUCR_iterator & CSS::IUCR_iterator::operator ++ (){
  if( it_s != parent.IUCRAccess[(*it_m).first ].end() ){
    it_s ++;
  }
  else{
    it_m ++;
    it_s = (*it_m).second.begin();
  }

  return *this;
}

/**
  @brief Operador de pre-decremeto.
  @return Una referencia a el objeto decrementado.
*/
CSS::IUCR_iterator & CSS::IUCR_iterator::operator -- (){
  if( it_s == parent.IUCRAccess[(*it_m).first].begin() ){
    it_m --;
  }
  else{
    it_s --;
  }

  return *this;
}

/**
  @brief Operador de igualdad.
  @return True si son iguales, false si no.
*/
bool CSS::IUCR_iterator::operator ==( const IUCR_iterator & iter ){
  return it_m == iter.it_m && it_s == iter.it_s;
}

/**
  @brief Operador de desigualdad.
  @return True si no son iguales, false si lo son.
*/
bool CSS::IUCR_iterator::operator !=( const IUCR_iterator & iter){
  return it_m != iter.it_m && it_s != iter.it_s;
}

/**
  @brief Método que permite acceder al primer elemento de IUCRAccess.
  @return Un CSS::iterator apuntando a el primer elemento de IUCRAccess.
*/
CSS::IUCR_iterator CSS::ibegin(){
  return CSS::IUCR_iterator( IUCRAccess.begin(), *this  );
}

/**
  @brief Método que permite acceder al último elemento de IUCRAccess.
  @return Un CSS::iterator apuntando a el último elemento de IUCRAccess.
*/
CSS::IUCR_iterator CSS::iend(){
  return CSS::IUCR_iterator( IUCRAccess.end(), *this );
}
/**
  @brief Devuelve la cota superior de un iucr
  @param iucr iucr cuya cota superior queremos saber.
  @return Un IUCR_iterator apuntando a la cota superior, iend() si no hay cota superior.
*/
CSS::IUCR_iterator CSS::upper_bound( IUCR iucr ){
  return CSS::IUCR_iterator( IUCRAccess.upper_bound( iucr ), *this );
}
/**
  @brief Devuelve la cota inferior de un iucr
  @param iucr iucr cuya cota inferior queremos saber.
  @return Un IUCR_iterator apuntando a la cota inferior, iend() si no hay cota inferior.
*/
CSS::IUCR_iterator CSS::lower_bound( IUCR iucr ){
  return CSS::IUCR_iterator( IUCRAccess.lower_bound( iucr ), *this );
}
