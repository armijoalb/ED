/** @brief fichero de implementacion de la clase conjunto
*/

	///////////////////////////
	//
	//			CONJUNTO
	//
	///////////////////////////

/**
	@brief Constructor primitivo.
*/
conjunto::conjunto(){
}

// -------------------------------------------------------------------------------------------

/**

	@brief Constructor a partir de un vector.

	Ordena el vector pasado como parámetro ( lo modifica ya que es una referencia )
	y lo añade ya ordenado al vector con push_back.

*/
conjunto::conjunto( vector<conjunto::entrada> & v_entrada ){

	*this = v_entrada;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Constructor de copia
	@param[in] d conjunto a copiar
*/
conjunto::conjunto( const conjunto &d ){
	//Copiamos el vector vc del objeto d en el vector de la clase.

	this->vc = d.vc;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Chequea si el conjunto está vacío.
	@return True si size()==0, false en caso contrario.
*/
bool conjunto::empty() const{
	return this->vc.empty();
}

// -------------------------------------------------------------------------------------------

/**
	@brief Número de entradas en el conjunto.
	@post  No se modifica el conjunto.
*/
conjunto::size_type conjunto::size() const{
	return this->vc.size();
}

// -------------------------------------------------------------------------------------------

/**

	@brief Busca una ID mediante búsqueda binaria ( conjunto ordenado por ID ).

	@return Devuelve un par. Si lo ha encontrado el segundo elemento (bool) es true y el primero es un iterador del cojunto::entrada.
	Si el segundo elemento (bool) es false, el primero es la posición (iterator) donde se insertaría dicho elemento.

*/
pair< vector<conjunto::entrada>::const_iterator ,bool> conjunto::binarySearchID( const long int id ) const{
	/*
		Busca un crimen por su ID.

		Si está devuelve un par:
			- Posición del crimen (offset)
			- true

		Si no está devuelve un par:
			- Posición donde iría
			- false
	*/


	// Inicializamos
	vector<conjunto::entrada>::const_iterator ini = vc.begin();
	vector<conjunto::entrada>::const_iterator fin = vc.end() - 1;

	pair< vector<conjunto::entrada>::const_iterator , bool> res( ini, false );

	//iterador half;
	vector<conjunto::entrada>::const_iterator half;


	// Realizamos la búsqueda binaria
	while( ini <= fin && !res.second ){

		half = ini + (fin-ini)/2;

		// Comprobamos si está antes
		if( ( *half ).getID() > id )
			fin = half - 1;

		// Si está después
		else if( ( *half ).getID() < id )
			ini = half + 1;

		// O si lo hemos encontrado
		else{
			res.first = half;
			res.second = true;
		}

	}

	// Si no lo hemos encontrado actualiza la posición
	if( !res.second )
		res.first = ini;

	return res;
}

// -------------------------------------------------------------------------------------------

/**

	@brief Busca una ID mediante búsqueda binaria ( conjunto ordenado por ID ).

	@return Devuelve un par. Si lo ha encontrado el segundo elemento (bool) es true y el primero es un iterador constante cojunto::entrada.
	Si el segundo elemento (bool) es false, el primero es la posición (iterator) donde se insertaría dicho elemento.

*/
pair< conjunto::conjunto_iterator ,bool> conjunto::binarySearchID( const long int id ) {
	/*
		Busca un crimen por su ID.

		Si está devuelve un par:
			- Posición del crimen (offset)
			- true

		Si no está devuelve un par:
			- Posición donde iría
			- false
	*/


	// Inicializamos
	conjunto::conjunto_iterator ini = vc.begin();
	conjunto::conjunto_iterator fin = vc.end() - 1;

	pair< conjunto::conjunto_iterator , bool> res( ini, false );

	conjunto::conjunto_iterator half;


	// Realizamos la búsqueda binaria
	while( ini <= fin && !res.second ){

		half = ini + (fin-ini)/2;

		// Comprobamos si está antes
		if( ( *half ).getID() > id )
			fin = half - 1;

		// Si está después
		else if( ( *half ).getID() < id )
			ini = half + 1;

		// O si lo hemos encontrado
		else{
			res.first = half;
			res.second = true;
		}

	}

	// Si no lo hemos encontrado actualiza la posición
	if( !res.second )
		res.first = ini;

	return res;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Inserta una entrada en el conjunto.
	@param e entrada a insertar.
	@return True si la entrada se ha podido insertar con éxito. False en caso contrario.
	@post 	 Si e no esta en el conjunto, el size() sera incrementado en 1.
*/
bool conjunto::insert( const conjunto::entrada &e ){

	bool aniadido = false;

	// Comprobamos que el vector no esté vacío.
	if ( !empty() ){
		// Busca el elemento
		pair<vector<conjunto::entrada>::iterator, bool> search = binarySearchID( e.getID() );

		// Si no está
		if( search.second == false ){

			// Toma la posición devuelta
			vc.insert( search.first, e );

		}

		aniadido = !search.second ;
	}
	else{
		vc.push_back( e );
		aniadido = true;
	}

	return aniadido;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Busca un crimen en el conjunto.
	@param id identificador del crimen  buscar.
	@return Si existe una entrada en el conjunto, devuelve un par con una copia de la entrada en el conjunto y con el segundo valor a true. Si  no se encuentra devuelve la entrada con la definicion por defecto y false.
	@post No modifica el conjunto.
	\verbatim Uso
	if (C.find(12345).second ==true) cout << "Esta" ;
	else cout << "No esta";
	\endverbatim
*/
pair<conjunto::entrada,bool> conjunto::find( const long int id ) const {
	/*
		Búsqueda binaria de un elemento dentro del conjunto.
	*/

	// Inicio del vector
	vector<conjunto::entrada>::const_iterator inicio = vc.begin();
	pair<conjunto::entrada, bool > out(conjunto::entrada(), false);

	if( !empty() ){
		// Buscamos el elemento
		pair<vector<conjunto::entrada>::const_iterator,bool> search = binarySearchID( id );

		// Si está actualizamos
		if( search.second == true ){
			out.first = *( search.first );
			out.second = search.second;
		}
	}

	return out;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Busca los crimenes con el mismo código IUCR.
	@param iucr identificador del crimen  buscar.
	@return Devuelve un  conjunto con todos los crimenes con el codigo IUCR. Si no existe ninguno devuelve el conjunto vacio.
	@post No modifica el conjunto.
	\verbatim Uso
        vector<crimen> C, A;
        ....
        A = C.findIUCR("0460");
	\endverbatim
*/
conjunto conjunto::findIUCR( const string &iucr ) const {
	conjunto salida;

	conjunto::const_iterator it_busqueda ;

	it_busqueda = this->cbegin();

	for ( ; it_busqueda != this->cend(); it_busqueda++){
		if( (*it_busqueda).getIUCR() == iucr )
			salida.insert( (*it_busqueda) );
	}

	return salida;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Busca los crimenes que contienen una determinada descripción
	@param descr string que representa la descripcion del delito buscar
	@return Devuelve un  conjunto con todos los crimenes  que contengan descr en su descripción. Si no existe ninguno devuelve el conjunto vacio.
	@post No modifica el conjunto.
	\verbatim Uso
        vector<crimen> C, A;
        ....
        A = C.findDESCR("BATTERY");
	\endverbatim
*/
conjunto  conjunto::findDESCR( const string &descr ) const {

	conjunto salida ;

	conjunto::const_iterator it_busqueda = this->cbegin();
	conjunto::const_iterator it_end = this->cend();

	for ( ; it_busqueda != it_end; it_busqueda++){
		if( (*it_busqueda).getDescription().find( descr ) != string::npos )
			salida.insert( (*it_busqueda) );
	}


	return salida;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Borra el delito dado un identificacador.

	Busca la entrada con id en el conjunto  y si la encuentra la borra.

	@param[in] id a borrar.
	@return True si la entrada se ha podido borrar con éxito. False en caso contrario.
	@post Si está en el conjunto, su tamaño se decrementa en 1.
*/
bool conjunto::erase( const long int &id ){

	pair< conjunto::conjunto_iterator, bool > search = binarySearchID( id );

	if( search.second )
		vc.erase( search.first );

	return search.second;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Borra una crimen con identificador dado por e.getID() en el conjunto.


	Busca la entrada con id en el conjunto (o e.getID() en el segundo caso) y si la encuentra la borra.

	@param[in] e con e.getID() que queremos borrar, el resto de los valores no son tenidos en cuenta.
	@return True si la entrada se ha podido borrar con éxito. False en caso contrario.
	@post Si está en el conjunto su tamaño se decrementa en 1.
*/
bool conjunto::erase( const conjunto::entrada &e ){
	bool encontrado = erase( e.getID() );

	return encontrado;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de asignación.
	@param[in] org conjunto  a copiar.
	Crea un conjunto duplicado exacto de org.
*/
conjunto & conjunto::operator=( const conjunto & org ){
	if( this != &org)
		vc = org.vc ;

	return *this ;
}

// -------------------------------------------------------------------------------------------

/*

	@brief Operador de asignación a partir de un vector.

	Ordena el vector pasado como parámetro ( lo modifica ya que es una referencia )
	y lo añade ya ordenado al vector con push_back.

*/
conjunto & conjunto::operator=( vector<conjunto::entrada> & v_entrada ){

	// Inicializamos los iteradores
	vector<conjunto::entrada>::iterator ini = v_entrada.begin();
	vector<conjunto::entrada>::iterator fin = v_entrada.end();

	// Ordenamos - Requiere sobrecarga de <<
	sort( ini, fin );

	// Añadimos ordenados
	
	while( ini != fin ){
		push_back( *ini );

		++ini;
	}

	return *this;
}

// -------------------------------------------------------------------------------------------

/** \invariant

	 IR: rep ==> bool

	\li Para todo i, 0 <= i < vc.size() se cumple
		vc[i].ID > 0;
	\li Para todo i, 0 <= i <= D.dic.size()-1 se cumple
		vc[i].ID< vc[i+1].ID

*/
/**
	@brief Chequea el Invariante de la representación.
	@return True si el invariante es correcto. False en caso contrario
*/
bool conjunto::cheq_rep() const {
	bool correcto = true ;
	conjunto::const_iterator it = this->cbegin();
	conjunto::const_iterator end = this->cend() - 2;


	for( ; it != end && correcto ; it++){
		if ( (*it).getID() >= (*(it + 1)).getID() )
			correcto = false;
	}

	return correcto;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Imprime todas las entradas del conjunto
	@post  No se modifica el conjunto.
*/
ostream & operator<<( ostream &sal, const conjunto &D ){
	conjunto::const_iterator it_salida;

	it_salida = D.cbegin();

	for ( ; it_salida != D.cend() ; it_salida++ ){
		sal << *it_salida << std::endl ;
	}

	sal << std::endl;

	return sal;
}

// -------------------------------------------------------------------------------------------

/*
	@brief Añade un elemento crimen::entrada al final.

	@post El invariante no se debe introducir un elemento que haga que el invariante
	sea falso.

*/
void conjunto::push_back( const conjunto::entrada & new_entrada ){

	// Buscamos el elemento
	pair< conjunto::entrada, bool> search = find( new_entrada.getID() );

	//Si no está lo añadimos
	if( !search.second )
		vc.push_back( new_entrada );

}

// -------------------------------------------------------------------------------------------

	///////////////////////////
	//
	//        iterator
	//
	///////////////////////////


/**
	@brief Constructor por defecto.

	Crea un conjunto::iterator vacío.
*/
conjunto::iterator::iterator(){}

// -------------------------------------------------------------------------------------------

/**
	@brief Constructor a partir de un conjunto::conjunto_iterator ( begin() y end() ).

	Crea un conjunto::iterator copia del conjunto::conjunto_iterator pasado como parámetro.
*/
conjunto::iterator::iterator( const conjunto_iterator & it ){
	iter = it;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Constructor de copia.
*/
conjunto::iterator::iterator( const conjunto::iterator & it ){
	iter = it.iter;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de desrreferencia.

	@return Una referencia al elemento de tipo conjunto::entrada al que apunta el iterador.
*/
conjunto::entrada & conjunto::iterator::operator*() const{

	// Devolvemos el contenido del iterador.
	return *iter;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de pre-incremento.

	@return Una referencia a sí mismo incrementado.
*/
conjunto::iterator & conjunto::iterator::operator++(){

	// Incrementamos
	++iter;

	// Devolvemos el propio objeto una vez incrementado
	return *this;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de post-incremento (iterator++).

	@return Una copia de sí mismo y luego se incrementa.
*/
conjunto::iterator conjunto::iterator::operator++( int ){
	// Post-Increment iterator++

	// Creamos una copia
	conjunto::iterator orig = *this;

	// Incrementamos
	++(*this);

	// Devolvemos la copia
	return orig;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de pre-decremento (--iterator).

	@return Una referencia a sí mismo decrementado.
*/
conjunto::iterator & conjunto::iterator::operator--(){
	// Pre-Increment --iterator

	// Decrementamos
	--iter;

	// Devolvemos el propio objeto una vez incrementado
	return *this;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de post-decremento (iterator--).

	@return Una copia de sí mismo y luego se decrementa.
*/
conjunto::iterator conjunto::iterator::operator--( int ){
	// Post-Increment iterator++

	// Creamos una copia
	conjunto::iterator orig = *this;

	// Incrementamos
	--(*this);

	// Devolvemos la copia
	return orig;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de asignación.

	@return Una referencia a sí mismo para poder encadenar asignaciones.
*/
conjunto::iterator & conjunto::iterator::operator=( const conjunto::iterator & new_it ){

	if( this != &new_it )
		iter = new_it.iter;

	return *this;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de suma.
	@param[in] posiciones que se quiere desplazar el iterador.
	@return Una referencia a sí mismo aumentado posiciones.
*/
conjunto::iterator & conjunto::iterator::operator+( const int  & posiciones ){

	//Incrementamos el iterador iter.
	iter += posiciones;

	// Devolvemos el objeto.
	return *this;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de resta.
	@param[in] posiciones que se quiere desplazar el iterador.
	@return Una referencia a sí mismo decrementado "posiciones".
*/
conjunto::iterator & conjunto::iterator::operator-( const int  & posiciones ){

	//Incrementamos el iterador iter.
	iter -= posiciones;

	// Devolvemos el objeto.
	return *this;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de comparación (igualdad).

	@return true si son iguales o false si no.
*/
bool conjunto::iterator::operator==( const conjunto::iterator & new_it ) const {

	return iter == new_it.iter;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de comparación (desigualdad).

	@return false si son iguales o true si no.
*/
bool conjunto::iterator::operator!=( const conjunto::iterator & new_it ) const {

	return iter != new_it.iter;

}


// -------------------------------------------------------------------------------------------

/**
	@brief Este método permite acceder al primer elemento del conjunto mediante un iterador.

	@return Un conjunto::iterator que apunta al primer elemento del conjunto.
*/
conjunto::iterator conjunto::begin(){ return conjunto::iterator( vc.begin() ); }

// -------------------------------------------------------------------------------------------

/**
	@brief Este método permite acceder al último elemento del conjunto mediante un iterador.

	@return Un conjunto::iterator que apunta al último elemento del conjunto.
*/
conjunto::iterator conjunto::end(){ return conjunto::iterator( vc.end() ); }



   ///////////////////////////
	//
	//      const_iterator
	//
	///////////////////////////



/**
	@brief Constructor por defecto.

	Crea un conjunto::const_iterator vacío.
*/
conjunto::const_iterator::const_iterator(){}

// -------------------------------------------------------------------------------------------

/**
	@brief Constructor a partir de un conjunto::conjunto_iterator ( begin() y end() ).

	Crea un conjunto::const_iterator copia del conjunto::conjunto_iterator pasado como parámetro.
*/
conjunto::const_iterator::const_iterator( const conjunto_iterator & it ){
	iter = it;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Constructor a partir de un conjunto::conjunto_const_iterator ( cbegin() y cend() ).

	Crea un conjunto::const_iterator copia del conjunto::conjunto_const_iterator pasado como parámetro.
*/
conjunto::const_iterator::const_iterator( const conjunto_const_iterator & it ){
	iter = it;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Constructor de copia a partir de un conjunto::iterator.
*/
conjunto::const_iterator::const_iterator( const conjunto::iterator & it ){
	iter = it.iter;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Constructor de copia.
*/
conjunto::const_iterator::const_iterator( const conjunto::const_iterator & it ){
	iter = it.iter;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de desrreferencia.

	@return Una referencia al elemento de tipo conjunto::entrada al que apunta el iterador.
*/
const conjunto::entrada & conjunto::const_iterator::operator*() const {

	// Devolvemos el contenido del iterador
	return *iter;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de pre-incremento (++iterator).

	@return Una referencia a sí mismo incrementado.
*/
conjunto::const_iterator & conjunto::const_iterator::operator++(){

	// Incrementamos
	++iter;

	// Devolvemos el propio objeto una vez incrementado
	return *this;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de post-incremento (iterator++).

	@return Una copia de sí mismo y luego se incrementa.
*/
conjunto::const_iterator conjunto::const_iterator::operator++( int ){

	// Creamos una copia
	conjunto::const_iterator orig = *this;

	// Incrementamos el propio objeto
	++(*this);

	// Devolvemos la copia del original
	return orig;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de pre-decremento (--iterator).

	@return Una referencia a sí mismo decrementado.
*/
conjunto::const_iterator & conjunto::const_iterator::operator--(){

	// Decrementamos
	--iter;

	// Devolvemos el propio objeto una vez incrementado
	return *this;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de post-decremento (iterator--).

	@return Una copia de sí mismo y luego se decrementa.
*/
conjunto::const_iterator conjunto::const_iterator::operator--( int ){

	// Creamos una copia
	conjunto::const_iterator orig = *this;

	// Decrementamos el propio objeto
	--(*this);

	// Devolvemos la copia del original
	return orig;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de suma.
	@param[in] posiciones que se quiere desplazar el iterador.
	@return Una referencia a sí mismo aumentado posiciones.
*/
conjunto::const_iterator & conjunto::const_iterator::operator+( const int  & posiciones ){

	//Incrementamos el iterador iter.
	iter += posiciones;

	// Devolvemos el objeto.
	return *this;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de resta.
	@param[in] posiciones que se quiere desplazar el iterador.
	@return Una referencia a sí mismo decrementado "posiciones".
*/
conjunto::const_iterator & conjunto::const_iterator::operator-( const int  & posiciones ){

	//Incrementamos el iterador iter.
	iter -= posiciones;

	// Devolvemos el objeto.
	return *this;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de asignación (casting a iterator).

	@return Una referencia a sí mismo para poder encadenar asignaciones.
*/
conjunto::const_iterator & conjunto::const_iterator::operator=( const conjunto::iterator & new_it ){

	iter = new_it.iter;

	return *this;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de asignación.

	@return Una referencia a sí mismo para poder encadenar asignaciones.
*/
conjunto::const_iterator & conjunto::const_iterator::operator=( const conjunto::const_iterator & new_it ){

	// Comprobamos que no sea el mismo objeto
	if( this != &new_it )
		iter = new_it.iter;

	return *this;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de comparación (igualdad).

	@return true si son iguales o false si no.
*/
bool conjunto::const_iterator::operator==( const conjunto::const_iterator & new_it ) const {

	return iter == new_it.iter;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de comparación (desigualdad).

	@return false si son iguales o true si no.
*/
bool conjunto::const_iterator::operator!=( const conjunto::const_iterator & new_it ) const{

	return iter != new_it.iter;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Este método permite acceder al primer elemento del conjunto mediante un iterador constante.

	@return Un conjunto::const_iterator que apunta al primer elemento del conjunto.
*/
conjunto::const_iterator conjunto::cbegin() const { return conjunto::const_iterator( vc.cbegin() ); }

// -------------------------------------------------------------------------------------------

/**
	@brief Este método permite acceder al último elemento del conjunto mediante un iterador constante.

	@return Un conjunto::const_iterator que apunta al último elemento del conjunto.
*/
conjunto::const_iterator conjunto::cend() const { return conjunto::const_iterator( vc.cend() ); }

// -------------------------------------------------------------------------------------------



      ///////////////////////////
      //
      //  description_iterator
      //
      ///////////////////////////



/**
   @brief Constructor por defecto.
   Crea un conjunto::description_iterator vacío.
*/
conjunto::description_iterator::description_iterator(){}
// -----------------------------------------------------------------------------

/**
   @brief Constructor de copia.
*/
conjunto::description_iterator::description_iterator(const conjunto::description_iterator &it){
   ini			= it.ini;
   end	 		= it.end;
	current 		= it.current;
}
// -----------------------------------------------------------------------------

/**
@brief Constructor a partir de dos conjunto::iterator ( begin() y end() ).
*/
conjunto::description_iterator::description_iterator( const conjunto::iterator & new_ini,
																		const conjunto::iterator & new_end,
																		const string & new_descrp ){
   end	= new_end;
	descrp = new_descrp;

	// Calcular current_pos
	current = new_ini;

	// Si no contiene la descripción búsca uno que sí
	if( (*current).getDescription().find( descrp ) == string::npos )
		++(*this);

	// Actualizamos la posición de inicio
	ini = current;

}

// -----------------------------------------------------------------------------

/**
   @brief Operador de desreferencia.
   @return Una referencia al elemento de tipo conjunto::entrada al que apunta el iterador.
*/
conjunto::entrada & conjunto::description_iterator::operator*() const{
   return *current;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de pre-incremento (++description_iterator).
   @return Una referencia a sí mismo incrementado.
*/
conjunto::description_iterator &conjunto::description_iterator::operator++(){
   // Incrementamos el iterador hasta que el objeto al que referencia tenga
   // la descripción sobre la que iteramos.

	do{
		++current;
	} while( current != end && (*current).getDescription().find( descrp ) == string::npos );

   return *this;
}

// -----------------------------------------------------------------------------

/**
   @brief Operador de post-incremento (description_iterator++)
   @return Una copia de sí mismo y luego se incrementa.
*/
conjunto::description_iterator conjunto::description_iterator::operator++(int){
   // Creo la copia del objeto.
   conjunto::description_iterator copia = *this;

	++(*this);

   // Devuelvo la copia del original.
   return copia;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de pre-decremento (--description_iterator)
   @return Una referencia a sí mismo decrementado.
*/
conjunto::description_iterator &conjunto::description_iterator::operator--(){
   // Decrementado el iterador mientras la descripción del objeto referenciado
   // sea diferente de descrp y current sea diferente de ini

	do{
		--current;
	}while( current != ini && (*current).getDescription().find( descrp ) != string::npos );

   return *this;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de post-decremento (description_iterator--)
   @return Una copia de sí mismo y luego se decrementa.
*/
conjunto::description_iterator conjunto::description_iterator::operator--(int){
   conjunto::description_iterator copia = *this;

	--(*this);

   return copia;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de asignación.
   @return Una referencia a sí mismo.
*/
conjunto::description_iterator & conjunto::description_iterator::operator=(const conjunto::description_iterator &it){

	// Si no es el mismo objeto
   if(this != &it){
      ini		= it.ini;
      end 		= it.end;
		current	= it.current;
		descrp 	= it.descrp;
   }

   return *this;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de igualdad.
   @return true si son iguales, false si no lo son.
*/
bool conjunto::description_iterator::operator== (const conjunto::description_iterator &it) const{
   return current == it.current;
}

// -----------------------------------------------------------------------------

/**
   @brief Operador de desigualdad.
   @return true si son distintos, false si son iguales.
*/
bool conjunto::description_iterator::operator!= (const conjunto::description_iterator &it) const{
   return current != it.current;
}

// -----------------------------------------------------------------------------

/**
   @brief Método para apuntar al elemento posterior al último elemento del conunto (no pertenece al conjunto).
*/
void conjunto::description_iterator::moveToEnd(){
	current = end;
}

// -----------------------------------------------------------------------------

/**
   @brief Método para obtener un iterador al primer elemento del conjunto cuya descripción contiene la
	cadena pasada como parámetro.
   @return Un conjunto::description_iterator que apunta al primer elemento del conjunto cuya
	descripción contiene la cadena pasada como parámetro.
*/
conjunto::description_iterator conjunto::dbegin(const string & descrp){
   // Creo un conjunto_iterator que apunta al primer elemento del conjunto.

   conjunto::description_iterator first( begin(), end(), descrp );

   // Devuelvo un conjunto::description_iterator.
   return first;
}

// -----------------------------------------------------------------------------

/**
   @brief Método para obtener un iterador al primer elemento del conjunto cuya descripción contiene la
	cadena pasada como parámetro.
   @return Devuelve un conjunto::description_iterator que apunta al primer elemento del conjunto cuya
	descripción contiene la cadena pasada como parámetro.
*/
conjunto::description_iterator conjunto::dend(const string & descrp){
   // Creo un conjunto_iterator que apunta al primer elemento del conjunto.

   conjunto::description_iterator last( begin(), end(), descrp );

	last.moveToEnd();

   // Devuelvo un conjunto::description_iterator.
   return last;
}

// -----------------------------------------------------------------------------


      //////////////////////////////
      //
      // const_description_iterator
      //
      //////////////////////////////


/**
  @brief Constructor por defecto.
  Crea un conjunto::const_description_iterator vacío.
*/
conjunto::const_description_iterator::const_description_iterator(){}
// -----------------------------------------------------------------------------

/**
   @brief Constructor para cdbegin() y cdend().
   Crea un conjunto::const_description_iterator que apunta al primer elemento con desc = descrp.
*/
conjunto::const_description_iterator::const_description_iterator(const conjunto::const_iterator &new_ini, const conjunto::const_iterator &new_end, const string &new_descrp){
   end	 = new_end;
	descrp = new_descrp;

	// Calcular current_pos
	current = new_ini;

	// Si no contiene la descripción búsca uno que sí
	if((*current).getDescription().find(descrp) == string::npos)
		++(*this);

	// Actualizamos la posición de inicio
	ini = current;
}
// -----------------------------------------------------------------------------

/**
   @brief Constructor a partir de dos conjunto::iterator (begin() y end()).
*/
conjunto::const_description_iterator::const_description_iterator(const conjunto::iterator &new_ini, const conjunto::iterator &new_end, const string &new_descrp){
   end	 = new_end;
	descrp = new_descrp;

	// Calcular current_pos
	current = new_ini;

	// Si no contiene la descripción búsca uno que sí
	if((*current).getDescription().find(descrp) == string::npos)
		++(*this);

	// Actualizamos la posición de inicio
	ini = current;
}
// -----------------------------------------------------------------------------

/**
   @brief Constructor de copia desde conjunto::description_iterator
*/
conjunto::const_description_iterator::const_description_iterator(const conjunto::description_iterator &it){
   ini      = it.ini;
   end      = it.end;
   current  = it.current;
}
// -----------------------------------------------------------------------------

/**
   @brief Constructor de copia desde conjunto::const_description_iterator
*/
conjunto::const_description_iterator::const_description_iterator(const conjunto::const_description_iterator &it){
   ini      = it.ini;
   end      = it.end;
   current  = it.current;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de desreferencia.
   @return Una referencia al elemento de tipo conjunto::entrada al que apunta el iterador.
*/
const conjunto::entrada &conjunto::const_description_iterator::operator*() const{
   return *current;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de pre-incremento (conjunto::const_description_iterator).
   @return Una referencia a sí mismo incrementado.
*/
conjunto::const_description_iterator &conjunto::const_description_iterator::operator++(){
   // Incrementamos el iterador hasta que el objeto al que referencia tenga
   // la descripción sobre la que iteramos.
   do{
      ++current;
   } while(current != end && (*current).getDescription().find(descrp) == string::npos);

   return *this;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de post-incremento (conjunto::description_iterator)
   @return Una copia de sí mismo y luego se incrementa.
*/
conjunto::const_description_iterator conjunto::const_description_iterator::operator++ (int){
   // Creo una copia del objeto.
   conjunto::const_description_iterator copia = *this;

	++(*this);

   // Devuelvo el objeto original.
   return copia;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de pre-decremento (conjunto::const_description_iterator)
   @return Una referencia a sí mismo decrementado.
*/
conjunto::const_description_iterator &conjunto::const_description_iterator::operator--(){
   // Decrementado el iterador mientras la descripción del objeto referenciado
   // sea diferente de descrp y current sea diferente de ini
	do{
		--current;
	}while( current != ini && (*current).getDescription().find( descrp ) != string::npos );

   return *this;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de post-decremento (conjunto::const_description_iterator)
   @return Una copia de sí mismo y luego se decrementa.
*/
conjunto::const_description_iterator conjunto::const_description_iterator::operator-- (int){
   // Creo una copia del objeto.
   conjunto::const_description_iterator copia = *this;

   --(*this);

   // Devuelvo una copia del objeto original. x
   return copia;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de asignación.
   @return Una referencia a sí mismo.
*/
conjunto::const_description_iterator & conjunto::const_description_iterator::operator=(const conjunto::const_description_iterator &it){
   // Si no es el mismo objeto, asigno sus datos miembro según los de it.
   if(this != &it){
      ini		= it.ini;
      end 		= it.end;
		current	= it.current;
		descrp 	= it.descrp;
   }

   return *this;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de igualdad.
   @return true si son iguales, false si no lo son.
*/
bool conjunto::const_description_iterator::operator== (const conjunto::const_description_iterator &it) const{
   return current == it.current;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de desigualdad.
   @return true si son distintos, false si son iguales.
*/
bool conjunto::const_description_iterator::operator!= (const conjunto::const_description_iterator &it) const{
   return current != it.current;
}
// -----------------------------------------------------------------------------

/**
   @brief Método para apuntar al elemento posterior al último elemento del conjunto (no pertenece al conjunto).
*/
void conjunto::const_description_iterator::moveToEnd(){
	current = end;
}
// -----------------------------------------------------------------------------

/**
   @brief Método para obtener un iterador al primer elemento del conjunto cuya descripción contiene la
	cadena pasada como parámetro.
   @return Un conjunto::description_iterator que apunta al primer elemento del conjunto cuya
	descripción contiene la cadena pasada como parámetro.
*/
conjunto::const_description_iterator conjunto::cdbegin(const string & descrp) const{
   // Creo un conjunto_iterator que apunta al primer elemento del conjunto.

   conjunto::const_description_iterator first(cbegin(), cend(), descrp);

   // Devuelvo un conjunto::const_description_iterator.
   return first;
}
// -----------------------------------------------------------------------------

/**
   @brief Método para acceder al elemento justo posterior al último elemento
   cuya descripción es igual a descrp.
   @return Un conjunto::const_description_iterator que apunta
   al elemento posterior al último elemento del conjunto cuya descripción es descrp.
*/
conjunto::const_description_iterator conjunto::cdend(const string & descrp) const{
   // Creo un conjunto_iterator que apunta al primer elemento del conjunto.

   conjunto::const_description_iterator last(cbegin(), cend(), descrp);

	last.moveToEnd();

   // Devuelvo un conjunto::description_iterator.
   return last;
}
// -----------------------------------------------------------------------------



      //////////////////////////
      //
      // 	 arrest_iterator
      //
      //////////////////////////



/**
  @brief Constructor por defecto.
  Crea un conjunto::arrest_iterator vacío.
*/
conjunto::arrest_iterator::arrest_iterator(){}

// -------------------------------------------------------------------------------------------

/**
  @brief Constructor para abegin() y aend().
  Crea un conjunto::arrest_iterator que apunta al primer elemento con arrest = true.
*/
conjunto::arrest_iterator::arrest_iterator( const conjunto::iterator & new_ini, const conjunto::iterator & new_end ){

	ini = new_ini;
	end = new_end;

	current = ini;

	if( !(*ini).getArrest() )
		++(*this);

}

// -------------------------------------------------------------------------------------------

/**
  @brief Constructor de copia.
*/
conjunto::arrest_iterator::arrest_iterator ( const conjunto::arrest_iterator & new_it ){

	ini = new_it.ini;
	end = new_it.end;
	current = new_it.current;

}

// -------------------------------------------------------------------------------------------

/**
  @brief Mueve el conjunto::iterator current al final.
*/
void conjunto::arrest_iterator::moveToEnd(){

	current = end;

}

// -------------------------------------------------------------------------------------------

/**
  @brief Operador de desreferencia

	@return Una referencia al elemento de tipo conjunto::entrada con arresto (true) al que apunta el iterador.
*/
conjunto::entrada & conjunto::arrest_iterator::operator*() const{

	return *current;

}

// -------------------------------------------------------------------------------------------

/**
  @brief Operador de pre-incremento.

	@return Una referencia a sí mismo incrementado.
*/
conjunto::arrest_iterator & conjunto::arrest_iterator::operator++(){

	do{

		++current;

	} while( current != end && !(*current).getArrest() );

	return *this;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de post-incremento.

	@return Una copia de sí mismo sin incrementar.
*/
conjunto::arrest_iterator conjunto::arrest_iterator::operator++( int ){

	conjunto::arrest_iterator orig = *this;

	++(*this);

	return orig;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de pre-decremento.

	@return Una referencia a sí mismo decrementado.
*/

conjunto::arrest_iterator & conjunto::arrest_iterator::operator--(){

	do{

		--current;

	} while( current != ini && !(*current).getArrest() );

	return *this;
}


// -------------------------------------------------------------------------------------------

/**
	@brief Operador de post-decremento.

	@return Una copia de sí mismo sin decrementar.
*/

conjunto::arrest_iterator conjunto::arrest_iterator::operator--( int ){

	conjunto::arrest_iterator orig = *this;

	--(*this);

	return orig;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de asignación.

	@return Una referencia a sí mismo para poder encadenar asignaciones.
*/
conjunto::arrest_iterator & conjunto::arrest_iterator::operator=(const conjunto::arrest_iterator & new_it){

   if(this != &new_it){
      ini      = new_it.ini;
      end      = new_it.end;
      current  = new_it.current;
   }

	return *this;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de comparación de igualdad.

	@return true si son iguales o false si no.
*/
bool conjunto::arrest_iterator::operator==( const conjunto::arrest_iterator & new_it ) const{

	return current == new_it.current;

}

// -------------------------------------------------------------------------------------------

/**
	@brief Operador de comparación de desigualdad.

	@return false si son iguales o true si no.
*/
bool conjunto::arrest_iterator::operator!=( const conjunto::arrest_iterator & new_it ) const{

	return current != new_it.current;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Método para obtener un iterador que apunta al primer elemento del conjunto con arrest (true).

	@return Un conjunto::arrest_iterator que apunta al primer elemento del conjunto con arresto.
*/
conjunto::arrest_iterator conjunto::abegin(){

	conjunto::arrest_iterator inicio( begin(), end() );

	return inicio;
}

// -------------------------------------------------------------------------------------------

/**
	@brief Método para obtener un iterador que apunta al siguiente al último elemento del conjunto.

	@return Un conjunto::arrest_iterator que apunta al último elemento del conjunto con arresto.
*/
conjunto::arrest_iterator conjunto::aend(){

	conjunto::arrest_iterator aend( begin(), end() );

	aend.moveToEnd();

	return aend;
}
// -------------------------------------------------------------------------------------------


      ///////////////////////////////
      //
      //    const_arrest_iterator
      //
      ///////////////////////////////


/**
   @brief Constructor por defecto.
   Crea un conjunto::const_arrest_iterator vacío.
*/
conjunto::const_arrest_iterator::const_arrest_iterator(){}
// -------------------------------------------------------------------------------------------

/**
  @brief Constructor para cabegin() y caend().
  Crea un conjunto::const_arrest_iterator que apunta al primer elemento con arrest = true.
*/
conjunto::const_arrest_iterator::const_arrest_iterator(const conjunto::const_iterator & new_ini, const conjunto::const_iterator & new_end){

	ini = new_ini;
	end = new_end;

	current = ini;

	if(!(*ini).getArrest())
		++(*this);

}
// -------------------------------------------------------------------------------------------

/**
  @brief Constructor para cabegin() y caend().
  Crea un conjunto::const_arrest_iterator que apunta al primer elemento con arrest = true.
*/
conjunto::const_arrest_iterator::const_arrest_iterator(const conjunto::iterator & new_ini, const conjunto::iterator & new_end){

	ini = new_ini;
	end = new_end;

	current = ini;

	if(!(*ini).getArrest())
		++(*this);

}
// -------------------------------------------------------------------------------------------

/**
   @brief Constructor de copia desde conjunto::arrest_iterator.
*/
conjunto::const_arrest_iterator::const_arrest_iterator(const conjunto::arrest_iterator & it){
   ini      = it.ini;
   end      = it.end;
   current  = it.current;
}
// -------------------------------------------------------------------------------------------

/**
   @brief Constructor de copia desde conjunto::const_arrest_iterator.
*/
conjunto::const_arrest_iterator::const_arrest_iterator(const conjunto::const_arrest_iterator & it){
   ini      = it.ini;
   end      = it.end;
   current  = it.current;
}
// -----------------------------------------------------------------------------

/**
  @brief Mueve el conjunto::const_iterator current al final.
*/
void conjunto::const_arrest_iterator::moveToEnd(){
	current = end;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de desreferencia.
   @return Una referencia al elemento de tipo conjunto::entrada al que apunta el iterador.
*/
const conjunto::entrada &conjunto::const_arrest_iterator::operator*() const{
   return *current;
}
// -----------------------------------------------------------------------------

/**
  @brief Operador de pre-incremento.
	@return Una referencia a sí mismo incrementado.
*/
conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator++(){

	do{
		++current;
	} while( current != end && !(*current).getArrest() );

	return *this;
}
// -------------------------------------------------------------------------------------------

/**
	@brief Operador de post-incremento.
	@return Una copia de sí mismo sin incrementar.
*/
conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator++( int ){

	conjunto::const_arrest_iterator copia = *this;

	++(*this);

	return copia;
}
// -------------------------------------------------------------------------------------------

/**
	@brief Operador de pre-decremento.
	@return Una referencia a sí mismo decrementado.
*/
conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator--(){

	do{
		--current;
	} while( current != ini && !(*current).getArrest() );

	return *this;
}
// -------------------------------------------------------------------------------------------

/**
	@brief Operador de post-decremento.
	@return Una copia de sí mismo sin decrementar.
*/

conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator--( int ){

	conjunto::const_arrest_iterator copia = *this;

	--(*this);

	return copia;
}
// -------------------------------------------------------------------------------------------

/**
   @brief Operador de asignación.
   @return Una referencia a sí mismo.
*/
conjunto::const_arrest_iterator &conjunto::const_arrest_iterator::operator=(const conjunto::const_arrest_iterator & new_it){
   if(this != &new_it){
      ini      = new_it.ini;
      end      = new_it.end;
      current  = new_it.current;
   }

   return *this;
}
// -------------------------------------------------------------------------------------------

/**
	@brief Operador de comparación de igualdad.
	@return true si son iguales o false si no lo son.
*/
bool conjunto::const_arrest_iterator::operator == (const conjunto::const_arrest_iterator & new_it) const{
   return current == new_it.current;
}
// -----------------------------------------------------------------------------

/**
   @brief Operador de desigualdad.
   @return true si son distintos, false si son iguales.
*/
bool conjunto::const_arrest_iterator::operator!= (const conjunto::const_arrest_iterator &new_it) const{
   return current != new_it.current;
}
// -------------------------------------------------------------------------------------------

/**
	@brief Método para obtener un iterador que apunta al primer elemento del conjunto con arrest (true).

	@return Un conjunto::const_arrest_iterator que apunta al primer elemento del conjunto con arresto.
*/
conjunto::const_arrest_iterator conjunto::cabegin(){

	conjunto::arrest_iterator first(begin(), end());

	return first;
}
// -------------------------------------------------------------------------------------------

/**
	@brief Método para obtener un iterador que apunta al siguiente al último elemento del conjunto.
	@return Un conjunto::const_arrest_iterator que apunta al último elemento del conjunto con arresto.
*/
conjunto::const_arrest_iterator conjunto::caend(){

	conjunto::arrest_iterator last(begin(), end());

	last.moveToEnd();

	return last;
}
