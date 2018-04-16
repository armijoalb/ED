/* 
 * crimen.hxx
 * 
 * Implementación de la clase crimen.
 *
 * 2015 
 *
 */



	//////////////////////////
	//
	//        CRIMEN
	//
	//////////////////////////



/*!
	@brief Constructor por defecto.

	Crea un objeto crimen vacío. Por defecto se inicializa el ID
	en 0, el cual no cumple el invariante de la representación.
	Los strings son vacíos ( "" ), latitud y longitud valen 0
	y false el arresto o si es doméstico.
*/
crimen::crimen()
	
	// Lista de inicialización a valores por defecto.
	:ID(1), case_number(""), date(), iucr(""), primary_type(""),
	 description(""), location_description(""), arrest(false),
	 domestic(false), latitude(0), longitude(0)

{}

//-----------------------------------------------------------------------------
	
/*!
	@brief Constructor de copia.

	Crea una copia en memoria del objeto crimen pasado como parámetro.

	@param x Objeto tipo crimen del que se quiere realizar la copia.

*/
crimen::crimen( const crimen & x )
	
	// Lista de inicialización a partir del parámetro x
	:ID( x.getID() ), case_number( x.getCaseNumber() ), date( x.getDate() ),
	 iucr( x.getIUCR() ), primary_type( x.getPrimaryType() ), 
	 description( x.getDescription() ), location_description( x.getLocationDescription() ), 
	 arrest( x.getArrest() ), domestic( x.getDomestic() ), 
	 latitude( x.getLatitude() ), longitude( x.getLongitude() )

{}

//-----------------------------------------------------------------------------

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
crimen::crimen(	long int id, 						// ID del caso
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
)

	// Lista de inicialización a valores por defecto.
	:ID( id ), case_number( cas_num ), date( dat ), iucr( iu ), primary_type( prim_type ),
	 description( desc ), location_description( loc_des ), arrest( arr ),
	 domestic( dom ), latitude( lat ), longitude( lon )

{}

//-----------------------------------------------------------------------------

/**

	@brief Constructor de inicialización a partir de una cadena (string).

	Toma una cadena (string) cuyo formato es:

	"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
	FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"

	Y crea el objeto crimen a partir de dichos datos.

	\pre { El ID debe de ser mayor que 0 ( ID > 0 ). }

	@param data Objeto string a analizar.
*/
crimen::crimen( const string & data ){
	/*
		Inicializa el objeto crimen a partir de un objeto string cuyo formato es:
		
		"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
		FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"
		
	*/
	setFromString( data );
	
}

//-----------------------------------------------------------------------------

/*!
	@brief Comprueba que el invariante es correcto.

	Comprueba que el invariante de la representación del objeto crimen
	sea correcto, es decir, ID > 0.

	@return true si es correcto, false si no.
*/
bool crimen::cheq_rep(){
	return ID > 0;
}


		/////////////////////////
		//
		//     MODIFICADORES
		//
		/////////////////////////


/*!
	@brief Establece el ID del crimen.

	\pre { El ID debe de ser mayor que 0 ( ID > 0 ). }

	@param id Número entero que representa el ID.
*/
void crimen::setID( long int id ){
	ID = id;
}

//-----------------------------------------------------------------------------

/*!
	@brief Establece el número del crimen.

	@param case_num Entero mayor que cero que contiene el ID.
*/
void crimen::setCaseNumber( const string & case_num ){
	case_number = case_num;
}

//-----------------------------------------------------------------------------

/*!
	@brief Establece la fecha del crimen.

	@param dat Objeto tipo fecha para almacenar la fecha del crimen.
*/
void crimen::setDate( const fecha & dat ){
	date = dat;
}

//-----------------------------------------------------------------------------

/*!
	@brief Establece el IUCR del crimen.

	Establece el IUCR del crimen. Es una cadena de texto según Illinois Uniform Crime Reporting.

	@param iucr_dat Cadena de texto que contiene el IUCR del crimen.
*/
void crimen::setIUCR( const string & iucr_dat ){
	iucr = iucr_dat;
}

//-----------------------------------------------------------------------------

/*!
	@brief Establece el tipo primario del crimen.


	@param p_type Cadena de texto que representa el tipo de crimen.

*/
void crimen::setPrimaryType( const string & p_type){
	primary_type = p_type;
}

//-----------------------------------------------------------------------------

/*!
	@brief Establece una descripción para el crimen.

	@param des Cadena de texto (string) con la descripción del crimen.

*/
void crimen::setDescription( const string & des ){
	description = des;
}

//-----------------------------------------------------------------------------
	
/*!
	@brief Establece la descripción del lugar aproximado.

	@param loc_des Cadena de texto (string) con la descripción del lugar del crimen.
*/
void crimen::setLocationDescription( const string & loc_des ){
	location_description = loc_des;
}

//-----------------------------------------------------------------------------
	
/*!
	@brief Establece si ha habido arrestos.

	@param arr Variable booleana para determinar si ha habido arrestos.
*/
void crimen::setArrest( bool arr ){
	arrest = arr;
}

//-----------------------------------------------------------------------------

/*!
	@brief Establece si el crimen ha sido doméstico.

	@param dom Variable booleana para determinar si el crimen es doméstico.
*/
void crimen::setDomestic( bool dom ){
	domestic = dom;
}

//-----------------------------------------------------------------------------

/*!
	@brief Establece la Latitud del crimen.

	@param lat Coordenada con la latitud (double).
*/
void crimen::setLatitude( double lat ){
	latitude = lat;
}

//-----------------------------------------------------------------------------

/*!
	@brief Establece la Longitud del crimen.

	@param lon Coordenada con la longitud (double).
*/
void crimen::setLongitude( double lon ){
	longitude = lon;
}

//-----------------------------------------------------------------------------

/**

	@brief Modifica los atributos del objeto crimen a partir de una cadena (string).

	Asigna los atributos del objeto crimen a partir de un objeto string cuyo formato es:

	"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
	FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"

	Y crea el objeto crimen a partir de dichos datos.

	@param data Objeto string a analizar.
*/
void crimen::setFromString( const string & data ){
	/*
			
		Analiza la cadena e introduce cada elemento en un vector de string para poder acceder
		fácilmente a ellos.
		
		Otra froma sería suprimir el vector y comprobar dentro del while con un if else para
		cada caso.
		
		No utiliza iteradores ya que el método find_first_of() está implementado con size_t.
		
	*/
	const int ID_POS = 0;
	const int CASE_NUM_POS = 1;
	const int DATE_POS = 2;
	const int IUCR_POS = 4;
	const int PRIM_T_POS = 5;
	const int DESC_POS = 6;
	const int LOC_DES_POS = 7;
	const int ARREST_POS = 8;
	const int DOM_POS = 9;
	const int LAT_POS = 19;
	const int LON_POS = 20;
	
	const int NUM_PARAM = 21;
	
	int inicio = 0;
	int fin = 0;
	
	vector<string> data_parsed;
	
	// Calculamos la primera coma
	fin = data.find_first_of(',', inicio);
	
	// Recorremos la cadena
	while( inicio < fin ){
		
		data_parsed.push_back( data.substr( inicio, (fin-inicio) ) );
		
		inicio = fin + 1;
		fin = data.find_first_of(',', inicio );
		
	}
	
	// Añadimos el último
	data_parsed.push_back( data.substr( inicio, (data.size()-inicio) ) );
	
	// Asignamos los elementos si hay suficientes datos
	if( data_parsed.size() >= NUM_PARAM ){
		
		// Convertimos a entero el ID
		ID = stoi( data_parsed[ ID_POS ] ); 							
		case_number = data_parsed[ CASE_NUM_POS ];
		date = data_parsed[ DATE_POS ];								
		iucr = data_parsed[ IUCR_POS ];
		primary_type = data_parsed[ PRIM_T_POS ];					
		description = data_parsed[ DESC_POS ];
		location_description = data_parsed[ LOC_DES_POS ];
		
		// Comprobamos si son 'true' o 'false'
		if( *(data_parsed[ ARREST_POS ].cbegin()) == 't' )
			arrest = true;
		else
			arrest = false;
		
		if( *(data_parsed[ DOM_POS ].cbegin()) == 't' )
			domestic = true;
		else
			domestic = false;
		
		// Convertimos a 'double'
		latitude = stod( data_parsed[ LAT_POS ] );
		longitude = stod( data_parsed[ LON_POS ] );
	}
	
}


		/////////////////////////
		//
		//     CONSULTORES
		//
		/////////////////////////

/*!
	@brief Devuelve el ID del crimen.

	@return Número del ID ( > 0 ) (long int).
*/
long int crimen::getID() const{
	return ID;
}

//-----------------------------------------------------------------------------

/*!
	@brief Devuelve el número del crimen.

	@return Número del crimen (long int).
*/
const string & crimen::getCaseNumber() const{
	return case_number;
}

//-----------------------------------------------------------------------------

/*!
	@brief Devuelve la fecha del crimen.

	@return Referencia constante a la fecha del crimen (fecha).
*/
const fecha & crimen::getDate() const{
	return date;
}

//-----------------------------------------------------------------------------

/*!
	@brief Devuelve la cadena IUCR del crimen.

	@return Referencia constante a la cadena de texto que contiene el IUCR (string).
*/
const string & crimen::getIUCR() const{
	return iucr;
}

//-----------------------------------------------------------------------------

/*!
	@brief Devuelve el tipo (primario) de crimen.

	@return Referencia constante a la cadena de texto que contiene el tipo de crimen (stirng).
*/
const string & crimen::getPrimaryType() const{
	return primary_type;
}

//-----------------------------------------------------------------------------

/*!
	@brief Devuelve la descripción del crimen.

	@return Referencia constante a la descripción del crimen (string).
*/
const string & crimen::getDescription() const{
	return description;
}

//-----------------------------------------------------------------------------

/*!
	@brief Devuelve la descripción del lugar del crimen.

	@return Referencia constante que contiene la descripción del lugar (string).
*/
const string & crimen::getLocationDescription() const{
	return location_description;
}

//-----------------------------------------------------------------------------

/*!
	@brief Devuelve si ha habido algún arresto en el crimen.

	@return true si ha habido algún arresto, false si no.
*/
bool crimen::getArrest() const{
	return arrest;
}

//-----------------------------------------------------------------------------
	
/*!
	@brief Devuelve si el crimen es doméstico.

	@return true si el caso es doméstico, false si no.
*/
bool crimen::getDomestic() const{
	return domestic;
}

//-----------------------------------------------------------------------------

/*!
	@brief Devuelve la latitud del lugar del crimen.

	@return Latitud (double).
*/
double crimen::getLatitude() const{
	return latitude;
}

//-----------------------------------------------------------------------------

/*!
	@brief Devuelve la longitud del lugar del crimen.

	@return Longitud (double).
*/
double crimen::getLongitude() const{
	return longitude;
}


		/////////////////////////
		//
		//      Sobrecarga
		//
		/////////////////////////


/**

	@brief Sobrecarga del operador de asignación ( = ) a partir de un objeto crimen.

	@param c Objeto crimen a copiar.
	@return Referencia a sí mismo (crimen).
*/
crimen & crimen::operator=(const crimen & c){
	/*
		Sobrecarga del operador de asignación.
	*/
	
	// Comprueba si es el mismo objeto
	if( this != &c ){
		
		// Actualiza los atributos
		ID 						= c.ID;
		case_number 			= c.case_number;
		date 						= c.date;
		iucr 						= c.iucr;
		primary_type 			= c.primary_type;
		description 			= c.description;
		location_description = c.location_description;
		arrest 					= c.arrest;
		domestic 				= c.domestic;
		latitude 				= c.latitude;
		longitude 				= c.longitude;
		
	}
	
	// Se devuelve a sí mismo
	return *this;
}

//-----------------------------------------------------------------------------

/**

	@brief Sobrecarga del operador de asignación ( = ) a partir de una cadena (string).

	Toma una cadena (string) cuyo formato es:

	"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
	FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"

	Y crea el objeto crimen a partir de dichos datos.

	@param data Objeto string a analizar.
	@return Referencia a sí mismo (crimen).

*/
crimen & crimen::operator=( const string & data ){
	/*
		Asigna los atributos del objeto crimen a partir de un objeto string cuyo formato es:
		
		"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
		FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"
		
	*/
	
	setFromString( data );
	
	return *this;
}

//-----------------------------------------------------------------------------

/*
	Sobrecarga de los operadores de comparación.
	
	El criterio de comparación es el ID del delito,
	ya que al ser un entero ( mayor que cero ) y emitirse
	de forma consecutiva, podemos saber cuál va antes.

*/

//-----------------------------------------------------------------------------

/**
	@brief Sobrecarga del operador de igualdad (==).

	@param c Objeto crimen con el se quiere comparar.
	@return true si son iguales, false si no.
*/
bool crimen::operator==(const crimen & c) const {
	return ID == c.ID;
}

//-----------------------------------------------------------------------------

/**
	@brief Sobrecarga del operador de desigualdad ( != ).

	@param c Objeto crimen con el que se quiere comparar.
	@return true si son diferentes, false si no.
*/
bool crimen::operator!=(const crimen & c) const{
	return ID != c.ID;
}

//-----------------------------------------------------------------------------

/**
	@brief Sobrecarga del operador de comparación menor ( < ).

	Compara si un crimen está antes según su ID ( y por tanto se habrá
	producido antes cronológicamente ).

	@param c Objeto crimen con el que se quiere comparar.
	@return true si es menor que c, false si no.
*/
bool crimen::operator<(const crimen & c) const{
	return ID < c.ID;
}

//-----------------------------------------------------------------------------

/**
	@brief Sobrecarga del operador de comparación menor igual ( <= ).

	Compara si un crimen está antes según su ID ( y por tanto se habrá
	producido antes cronológicamente ) o si es el mismo.

	@param c Objeto crimen con el que se quiere comparar.
	@return true si es menor ( o igual ) que c, false si no.
*/
bool crimen::operator<=(const crimen & c) const{
	return ID <= c.ID;
}

//-----------------------------------------------------------------------------

/**
	@brief Sobrecarga del operador de comparación mayor ( > ).

	Compara si un crimen está después según su ID ( y por tanto se habrá
	producido posteriormente cronológicamente ).

	@param c Objeto crimen con el que se quiere comparar.
	@return true si es mayor que c, false si no.
*/
bool crimen::operator>(const crimen & c) const{
	return ID > c.ID;
}

//-----------------------------------------------------------------------------

/*!
	@brief Sobrecarga del operador de comparación mayor igual ( >= ).

	Compara si un crimen está después según su ID ( y por tanto se habrá
	producido posteriormente cronológicamente ) o si es igual.

	@param c Objeto crimen con el que se quiere comparar.
	@return true si es mayor ( o igual ) que c, false si no.
*/
bool crimen::operator>=(const crimen & c) const{
	return ID >= c.ID;
}

//-----------------------------------------------------------------------------

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
ostream & operator<< ( ostream & os, const crimen & c ){
	/*
		Sobrecarga del operador << para mostrar
		un delito / crimen por la salida estándar.
	*/
	
	cout << "Crimen" << endl;
	cout << "ID: " << c.ID << endl;
	cout << "Numero de caso: " << c.case_number << endl;
	cout << "Fecha: " << c.date << endl;
	cout << "IUCR: " << c.iucr << endl;
	cout << "Tipo de delito: " << c.primary_type << endl;
	cout << "Descripcion: " << c.description << endl;
	cout << "Localización ( descripcion ): " << c.location_description << endl;
	
	// Damos formato a los booleanos
	cout << "Hay arrestos: ";
	if( c.arrest )
		cout << "Si";
	else
		cout << "No";
	cout << endl;
	
	cout << "Es domestico: ";
	if( c.domestic )
		cout << "Si";
	else
		cout << "No";
	cout << endl;
	
	cout << "Latitud: " << c.latitude << endl;
	cout << "Longitud: " << c.longitude << endl;
	
	return os;
}

//-----------------------------------------------------------------------------