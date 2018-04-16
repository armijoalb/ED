/* 
 * crimen.hxx
 * 
 * Implementación de la clase crimen.
 *
 * 2015 
 *
 */

	
//-----------------------------------------------------------------------------
//
// 	CONSTRUCTORES


// Constructor por defecto.
crimen::crimen()
	
	// Lista de inicialización a valores por defecto.
	:ID(1), case_number(""), date(), iucr(""), primary_type(""),
	 description(""), location_description(""), arrest(false),
	 domestic(false), latitude(0), longitude(0)

{}

//-----------------------------------------------------------------------------
	
// Constructor de copia
crimen::crimen( const crimen & x )
	
	// Lista de inicialización a partir del parámetro x
	:ID( x.getID() ), case_number( x.getCaseNumber() ), date( x.getDate() ),
	 iucr( x.getIUCR() ), primary_type( x.getPrimaryType() ), 
	 description( x.getDescription() ), location_description( x.getLocationDescription() ), 
	 arrest( x.getArrest() ), domestic( x.getDomestic() ), 
	 latitude( x.getLatitude() ), longitude( x.getLongitude() )

{}

//-----------------------------------------------------------------------------

// Constructor de inicialización
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

// Constructor de inicialización
crimen::crimen( const string & data ){
	/*
		Inicializa el objeto crimen a partir de un objeto string cuyo formato es:
		
		"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
		FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"
		
	*/
	setFromString( data );
	
}

//-----------------------------------------------------------------------------

// Comprobante del invariante de la representación 
bool crimen::cheq_rep(){
	return ID > 0;
}


//-----------------------------------------------------------------------------
//
// 	MODIFICADORES


// Prec: id > 0
void crimen::setID( long int id ){
	ID = id;
}
	
void crimen::setCaseNumber( const string & case_num ){
	case_number = case_num;
}
	
void crimen::setDate( const fecha & dat ){
	date = dat;
}
	
void crimen::setIUCR( const string & iucr_dat ){
	iucr = iucr_dat;
}
	
void crimen::setPrimaryType( const string & p_type){
	primary_type = p_type;
}	

void crimen::setDescription( const string & des ){
	description = des;
}
	
void crimen::setLocationDescription( const string & loc_des ){
	location_description = loc_des;
}
	
void crimen::setArrest( bool arr ){
	arrest = arr;
}
	
void crimen::setDomestic( bool dom ){
	domestic = dom;
}

void crimen::setLatitude( double lat ){
	latitude = lat;
}

void crimen::setLongitude( double lon ){
	longitude = lon;
}

//-----------------------------------------------------------------------------

// Constructor de inicialización
void crimen::setFromString( const string & data ){
	/*
		Asigna los atributos del objeto crimen a partir de un objeto string cuyo formato es:
		
		"ID,Case Number,Date,Block,IUCR,Primary Type,Description,Location Description,Arrest,Domestic,Beat,District,Ward,Community Area,
		FBI Code,X Coordinate,Y Coordinate,Year,Updated On,Latitude,Longitude,Location"
		
		
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

//-----------------------------------------------------------------------------
//
// 	CONSULTORES


long int crimen::getID() const{
	return ID;
}
		
const string & crimen::getCaseNumber() const{
	return case_number;
}
	
const fecha & crimen::getDate() const{
	return date;
}

const string & crimen::getIUCR() const{
	return iucr;
}
		
const string & crimen::getPrimaryType() const{
	return primary_type;
}

const string & crimen::getDescription() const{
	return description;
}
		
const string & crimen::getLocationDescription() const{
	return location_description;
}

bool crimen::getArrest() const{
	return arrest;
}
	
bool crimen::getDomestic() const{
	return domestic;
}
		
double crimen::getLatitude() const{
	return latitude;
}
	
double crimen::getLongitude() const{
	return longitude;
}


//-----------------------------------------------------------------------------
//
// 	SOBRECARGA


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

// Asignación a partir de un string
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

bool crimen::operator==(const crimen & c) const {
	return ID == c.ID;
}

bool crimen::operator!=(const crimen & c) const{
	return ID != c.ID;
}

bool crimen::operator<(const crimen & c) const{
	return ID < c.ID;
}	

bool crimen::operator<=(const crimen & c) const{
	return ID <= c.ID;
}

bool crimen::operator>(const crimen & c) const{
	return ID > c.ID;
}

bool crimen::operator>=(const crimen & c) const{
	return ID >= c.ID;
}

//-----------------------------------------------------------------------------

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