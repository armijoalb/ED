/**
  Contenedor árbol binario (bintree).
  Implementación.
  Alberto Armijo Ruiz.
  2º A GII.
*/

// -----------------------------------------------------------------------------------------------------
// Clase node.
// -----------------------------------------------------------------------------------------------------

//********************************************************
// Constructor.
//********************************************************
template <typename T>
bintree<T>::node::node()
:padre(NULL), izquierda(NULL), derecha(NULL), etiqueta(5){
}

//********************************************************
// Constructor de copia.
//********************************************************
template <typename T>
bintree<T>::node::node( const typename bintree<T>::node &n ){
  etiqueta  = n.etiqueta;
  padre     = n.padre;
  izquierda = n.izquierda;
  derecha   = n.derecha;
}

//********************************************************
// Operador de asignación.
//********************************************************
template <typename T>
typename bintree<T>::node & bintree<T>::node::operator = ( const typename bintree<T>::node &n ){
  if( this != n ){
    etiqueta = *n;
    *padre     = n.parent();
    *izquierda = n.left();
    *derecha   = n.right();
  }

  return *this;
}

//********************************************************
// Consultor null.
//********************************************************
template <typename T>
bool bintree<T>::node::null() const{
  return this == NULL; //??
}
//********************************************************
// Consultor esHoja.
//********************************************************
template <typename T>
bool bintree<T>::node::esHoja() const{
  return ( right()->null() && left()->null() );
}

//********************************************************
// Consultor esInterno.
//********************************************************
template <typename T>
bool bintree<T>::node::esInterno() const{
  return ( !(left()->null() ) || !( right()->null() )  );
}

//********************************************************
// Consultor padre.
//********************************************************
template <typename T>
typename bintree<T>::node * bintree<T>::node::parent() const {
  return parent;
}

//********************************************************
// Consultor hijo izquierda.
//********************************************************
template <typename T>
typename bintree<T>::node * bintree<T>::node::left() const {
  return izquierda;
}

//********************************************************
// Consultor hijo derecha.
//********************************************************
template <typename T>
typename bintree<T>::node * bintree<T>::node::right() const{
  return derecha;
}

//********************************************************
// Operador *-
//********************************************************

template <typename T>
T & bintree<T>::node::operator * (){
  return etiqueta;
}

//********************************************************
// Comparador igualdad.
//********************************************************
template <typename T>
bool bintree<T>::node::operator == ( const typename bintree<T>::node &n ) const {
  return ( etiqueta == n.etiqueta && padre == n.padre && izquierda == n.izquierda && derecha == n.derecha );
}

//********************************************************
// Comparador desigualdad.
//********************************************************
template <typename T>
bool bintree<T>::node::operator != ( const typename bintree<T>::node &n ) const {
  return ( etiqueta != n.etiqueta || padre != n.padre || izquierda != n.izquierda || derecha != n.derecha );
}

// -----------------------------------------------------------------------------------------------------
// Clase bintree.
// -----------------------------------------------------------------------------------------------------

//********************************************************
// Constructor.
//********************************************************
template <typename T>
bintree<T>::bintree(){
  raiz = NULL;
  num_nodos = 0;
}

//********************************************************
// Constructor de copia.
//********************************************************
template <typename T>
bintree<T>::bintree( const bintree<T> & A ){
  num_nodos = A.num_nodos;
  /*
  // Recorremos todo el árbol en pre_orden insertando los elementos.
  std::vector<bintree<T>::node const *> quedan;

  bintree<T>::node const * actual = A.root();
  while( !actual->null() ){

  }
*/
}

//********************************************************
// Destructor.
//********************************************************
template <typename T>
bintree<T>::~bintree(){ // modificar.
  delete raiz;
  num_nodos = 0;
}

//********************************************************
// Consultor número de nodos.
//********************************************************
template <typename T>
size_type bintree<T>::size() const{
  return num_nodos;
}


//********************************************************
// Consultor raíz.
//********************************************************
template <typename T>
typename bintree<T>::node * bintree<T>::root() const{
  return raiz;
}

//********************************************************
// Consultor null.
//********************************************************
template <typename T>
bool bintree<T>::null() const{
    return raiz->null();
}

//********************************************************
// Método insert.
//********************************************************
template <typename T>
void bintree<T>::insert( node *& root, T & x ){
    if( raiz->null() ){
      raiz = new node;
      raiz->etiqueta = x;
    }
    else{
      if( raiz->etiqueta < x ){
        insert( raiz->derecha, x );
      }
      else{
        insert( raiz->izquierda, x );
      }
    }
}
