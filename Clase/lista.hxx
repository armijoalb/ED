// -----------------------------------------------------------------------------
// Implementación list.
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
template < typename T >
list<T>::list(){
  tama = 0;
  cub = new node;
  cub->sig = cub->ant = cub;
}

// -----------------------------------------------------------------------------
template < typename T >
unsigned int list<T>::size(){
  return tama;
}

// -----------------------------------------------------------------------------
template < typename T >
bool list<T>::empty(){
  return tama == 0;
}

// -----------------------------------------------------------------------------
template < typename T >
T & list<T>::back() {
  return cub->ant->info;
}

// -----------------------------------------------------------------------------
template < typename T >
const T & list<T>::back() const{
  return cub->ant->info;
}

// -----------------------------------------------------------------------------
template < typename T >
void list<T>::push_back(const T dato){
  node *aux = new node;
  aux->info = dato;
  aux->ant = cub->ant;
  aux->sig = cub;
  aux->ant->sig = aux;
  cub->ant = aux;
  tama ++;
}

// -----------------------------------------------------------------------------
template < typename T >
void list<T>::pop_back(){
  node *aux = new node;
  aux = cub->ant;

  cub->ant = cub->ant->ant;
  aux->ant->sig = cub;

  delete aux;
  tama --;
}

// -----------------------------------------------------------------------------
template < typename T >
void list<T>::clear(){
  node * aux = new node;
  while( cub->sig != cub ){
    aux = cub->sig;
    cub->sig = aux->sig;
    delete aux;
  }
  cub->ant = cub;
  tama = 0;
}

// -----------------------------------------------------------------------------
template < typename T >
list<T>::~list(){
  clear();
  delete cub;
}

// -----------------------------------------------------------------------------
template < typename T >
void list<T>::remove( const T & dato ){
  node *aux = new node;
  node *a_borrar = new node;
  aux = cub->sig;

  while( aux != cub ){

    if( aux->info == dato ){
      a_borrar = aux;
      a_borrar->sig->ant = a_borrar->ant;
      a_borrar->ant->sig = a_borrar->sig;
      delete a_borrar;
      tama --;
    }

    aux = aux->sig;
  }
}

// -----------------------------------------------------------------------------------

// clase iterator.

// -----------------------------------------------------------------------------------

template < typename T >
typename list<T>::iterator list<T>::begin(){
  typename list<T>::iterator sal;

  sal.ptr_nodo = cub->sig;

  return sal;
}

// -----------------------------------------------------------------------------------
template < typename T >
typename list<T>::iterator list<T>::end(){
  typename list<T>::iterator sal;

  sal.ptr_nodo = cub->ant;

  return sal;
}

// -----------------------------------------------------------------------------------
template < typename T >
typename list<T>::iterator::iterator()
  :ptr_nodo = 0{}

// ------------------------------------------------------------------------------------
template < typename T >
typename list<T>::iterator::iterator( const typename list<T>::iterator & it ){
  ptr_nodo = it.ptr_nodo;
}

// ------------------------------------------------------------------------------------
template < typename T >
typename list<T>::iterator & typename list<T>::iterator::operator ++(){
  ptr_nodo = ptr_nodo->sig;

  return *this;
}

// ------------------------------------------------------------------------------------
template < typename T >
bool typename list<T>::iterator::operator == ( const typename list<T>::iterator it ) const {
  return ptr_nodo == it.ptr_nodo ;
}

// ---------------------------------------------------------------------------------------
template < typename T >
typename list<T>::iterator list<T>::insert( typename list<T>::iterator pos, const T & x ){
  typename list<T>::iterator sal;

  sal.ptr_nodo       = new nodo ;
  sal.ptr_nodo->info = x;

  sal.ptr_nodo->ant      = pos.ptr_nodo->ant;
  sal.ptr_nodo->ant->sig = sal.ptr_nodo ;
  sal.ptr_nodo->sig      = pos.ptr_nodo ;
  pos.ptr_nodo->ant      = sal.ptr_nodo ;

  tama ++;
  return sal;
}

// -----------------------------------------------------------------------------------------
template < typename T >
void list<T>::insert( typename list<T>::iterator it, unsigned int n, const T & x ){
  typename list<T>::iterator aux(it);

  for( i = 0; i < n ; i++ )
    insert( aux, x );

}

// ------------------------------------------------------------------------------------------
template < typename T >           // Template de la clase.
template < class InputIterator >  // Template de la función, específica de la función.
void list<T>::insert( typename list<T>::iterator it, InputIterator ini, InputIterator fin ){
  // Insertamos los elementos.
  while( ini != fin ){
    insert( it, *ini );
    ++ini;
  }
}

// -----------------------------------------------------------------------------------------
