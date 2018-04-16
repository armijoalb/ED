/** @brief fichero de implementacion de la clase conjunto
*/


//Constructor por defecto.
conjunto::conjunto(){
}

//Constructor de copia.
conjunto::conjunto( const conjunto &d ){
	//Copiamos el vector vc del objeto d en el vector de la clase.

	this->vc = d.vc;
}

//Método para comprobar si el conjunto está vacío.
bool conjunto::empty() const{
	return this->vc.empty();
}

//Método para conocer el tamaño del conjunto.
conjunto::size_type conjunto::size() const{
	return this->vc.size();
}

// Búsqueda binaria
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
	vector<conjunto::entrada>::const_iterator ini = vc.cbegin();
	vector<conjunto::entrada>::const_iterator fin = vc.cend() - 1;

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
	//if( !res.second )
	//	res.first = ini;

	return res;
}

pair< vector<conjunto::entrada>::iterator ,bool> conjunto::binarySearchID( const long int id ) {
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
	vector<conjunto::entrada>::iterator ini = vc.begin();
	vector<conjunto::entrada>::iterator fin = vc.end() - 1 ;

	pair< vector<conjunto::entrada>::iterator , bool> res( ini, false );

	vector<conjunto::entrada>::iterator half;


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

//Método para introducir una nueva entrada en el conjunto.
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
	
}

//Método para buscar un id dentro del conjunto.
pair<conjunto::entrada,bool> conjunto::find( const long int id ) const {
	/*
		Búsqueda binaria de un elemento dentro del conjunto.
	*/
	
	// Inicio del vector
	vector<conjunto::entrada>::const_iterator inicio = vc.cbegin();
	pair<conjunto::entrada, bool > out(conjunto::entrada(), false);
	
	// Buscamos el elemento
	pair<vector<conjunto::entrada>::const_iterator,bool> search = binarySearchID( id );
	
	// Si está actualizamos
	if( search.second == true ){
		out.first = *( search.first );
		out.second = search.second;
	}
	
	return out;
}

//Método para construir un conjunto con las entradas que tengan mismo IUCR.
//Devuelve conjunto vacío si no existe ninguna entrada con igual IUCR.
conjunto conjunto::findIUCR( const string &iucr ) const {
	conjunto salida;
	std::vector<conjunto::entrada>::const_iterator it_busqueda ;

	it_busqueda = this->vc.begin();

	for ( ; it_busqueda != this->vc.end(); it_busqueda++){
		if( (*it_busqueda).getIUCR() == iucr )
			salida.insert( (*it_busqueda) );
	}

	return salida;
}


//Método para construir un conjunto con las entradas con misma descripcion.
//Devuelve conjunto vacío si no hay ninguna entrada con esa descripcion.
conjunto  conjunto::findDESCR( const string &descr ) const {
	conjunto salida ;
	std::vector<conjunto::entrada>::const_iterator it_busqueda ;

	it_busqueda = this->vc.begin();

	for ( ; it_busqueda != this->vc.end(); it_busqueda++){
		if( (*it_busqueda).getDescription() == descr )
			salida.insert( (*it_busqueda) );
	}


	return salida;
}

//Método para borra una entrada, buscada por su ID.
bool conjunto::erase( const long int &id ){
	std::vector<conjunto::entrada>::iterator it_borrar;
	bool encontrado = false;
	it_borrar = this->vc.begin();

	while( it_borrar != this->vc.end() && !encontrado ){
		if( (*it_borrar).getID() == id ){
			this->vc.erase( it_borrar );
			encontrado = true;
		}
		else
			it_borrar ++ ;
	}

	return encontrado;
}

//Igual que el método anterior, cambiando el parámetro dado por una entrada.
//Buscamos con entrada.getID().
bool conjunto::erase( const conjunto::entrada &e ){
	bool encontrado = this->erase( e.getID() );

	return encontrado;
}

//Sobrecarga de la asignacion.
conjunto & conjunto::operator = ( const conjunto & org ){
	if( this != &org)
		this->vc = org.vc ;

	return *this ;
}

//Método para comprobar si el invariante es correcto.
bool conjunto::cheq_rep() const {
	bool correcto = true ;
	std::vector<conjunto::entrada>::const_iterator it = vc.begin();
	std::vector<conjunto::entrada>::const_iterator end = vc.end() - 1;

	for( ; it != end && correcto ; it++){
		if ( (*it).getID() >= (*(it+1)).getID() )
			correcto = false;
	}

	return correcto;
}

//Sobrecarga de la salida
ostream & operator << ( ostream &sal, const conjunto &D ){
	std::vector<conjunto::entrada>::const_iterator it_salida;

	it_salida = D.vc.begin();

	for ( ; it_salida != D.vc.end() ; it_salida++ ){
		sal << *it_salida << std::endl ;
	}

	sal << std::endl;

	return sal;
}