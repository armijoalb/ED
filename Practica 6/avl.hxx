/**
*   Implementación métodos clase AVL.
*   Alberto Armijo Ruiz.
*   2º GII A.
*/

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------------------------------
// Constructores.
//------------------------------------------------------------------------------------------------------

// Constructor por defecto.
template <typename T ,class comparar>
AVL<T,comparar>::AVL()
  :tama(0){}

// Constructor de copia.
template <typename T ,class comparar>
AVL<T,comparar>::AVL( const AVL<T,comparar> & copy_avl )
  :el_avl( copy_avl.el_avl ){
    tama = el_avl.size();
}

//------------------------------------------------------------------------------------------------------
//  Operador de asignación.
//------------------------------------------------------------------------------------------------------
template <typename T ,class comparar>
AVL<T,comparar> & AVL<T,comparar>::operator =( const AVL<T,comparar> & avl_asig ){
  if( this != &avl_asig ){
    el_avl = avl_asig.el_avl;
  }

  return *this;
}

//------------------------------------------------------------------------------------------------------
// Consutores de capacidad.
//------------------------------------------------------------------------------------------------------

// Consultor si está vacío.
template <typename T ,class comparar>
bool AVL<T,comparar>::empty() const{
  return tama == 0;
}

// Consultor tamaño.
template <typename T ,class comparar>
typename AVL<T,comparar>::size_type AVL<T,comparar>::size() const{
  return tama;
}

//------------------------------------------------------------------------------------------------------
// Clase iterator.
//------------------------------------------------------------------------------------------------------

// Constructor.
template <typename T ,class comparar>
AVL<T,comparar>::iterator::iterator(){}

// Constructor de copia con bintree<T>::inorder_iterator.
template <typename T ,class comparar>
AVL<T,comparar>::iterator::iterator(const typename bintree<std::pair<T, altura> >::inorder_iterator & it){
  mi_it = it;
}

// Constructor de copia con AVL<T,comparar>::iterator.
template <typename T ,class comparar>
AVL<T,comparar>::iterator::iterator( const typename AVL<T,comparar>::iterator & it ){
  mi_it = it.mi_it;
}

// Constructor de copia con node.
template <typename T, class comparar>
AVL<T,comparar>::iterator::iterator( typename bintree<T>::node & n)
  :mi_it(n){
}

// Operador *.
template <typename T ,class comparar>
T & AVL<T,comparar>::iterator::operator *(){
  return (*mi_it).first ;
}

// Operador ++ (PreFijo).
template <typename T ,class comparar>
typename AVL<T,comparar>::iterator & AVL<T,comparar>::iterator::operator ++(){
  // Incrementamos el iterator.
  ++mi_it;

  //Devolvemos el objeto incrementado.
  return *this;
}

// Operator ==.
template <typename T, class comparar>
bool AVL<T,comparar>::iterator::operator ==( const typename AVL<T,comparar>::iterator & it ){
  return mi_it == it.mi_it;
}

// Operator !=.
template <typename T, class comparar>
bool AVL<T,comparar>::iterator::operator !=( const typename AVL<T,comparar>::iterator & it ){
  return mi_it != it.mi_it;
}

//------------------------------------------------------------------------------------------------------
// Métodos iterator.
//------------------------------------------------------------------------------------------------------

// Método begin.
template <typename T ,class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::begin(){
  return AVL<T,comparar>::iterator( el_avl.begin_inorder() );
}

// Método end.
template <typename T ,class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::end(){
  return AVL<T,comparar>::iterator( el_avl.end_inorder() );
}

//------------------------------------------------------------------------------------------------------
// Clase const_iterator.
//------------------------------------------------------------------------------------------------------

// Constructor.
template <typename T ,class comparar>
AVL<T,comparar>::const_iterator::const_iterator(){
}

// Constructor de copia con const_inorder_iterator.
template <typename T ,class comparar>
AVL<T,comparar>::const_iterator::const_iterator(const typename bintree<std::pair<T, altura> >::const_inorder_iterator & it){
  mi_it = mi_it;
}

// Constructor de copia con inorder_iterartor.
template <typename T ,class comparar>
AVL<T,comparar>::const_iterator::const_iterator( const typename bintree<std::pair<T, altura> >::inorder_iterator & it){
  mi_it = mi_it;
}

// Constructor de copia con const_iterator.
template <typename T ,class comparar>
AVL<T,comparar>::const_iterator::const_iterator( const typename AVL<T,comparar>::const_iterator &it ){
  mi_it = it.mi_it;
}

// Constructor de copia con iterator.
template <typename T ,class comparar>
AVL<T,comparar>::const_iterator::const_iterator( const typename AVL<T,comparar>::iterator & it){
  mi_it = it.mi_it;
}

// Operador *.
template <typename T ,class comparar>
const T & AVL<T,comparar>::const_iterator::operator *() const{
  return (*mi_it).first ;
}

// Operador ++ (Pre-Fijo).
template <typename T ,class comparar>
typename AVL<T,comparar>::const_iterator & AVL<T,comparar>::const_iterator::operator ++(){
  // Incrementamos el iterator.
  ++mi_it;

  //Devolvemos el objeto incrementado.
  return *this;
}

// Operator ==.
template <typename T, class comparar>
bool AVL<T,comparar>::const_iterator::operator ==( const typename AVL<T,comparar>::const_iterator & it ) const{
  return mi_it == it.mi_it;
}

// Operator !=.
template <typename T, class comparar>
bool AVL<T,comparar>::const_iterator::operator !=( const typename AVL<T,comparar>::const_iterator & it ) const{
  return mi_it == it.mi_it;
}

//------------------------------------------------------------------------------------------------------
// Métodos const_iterator.
//------------------------------------------------------------------------------------------------------

// Método cbegin().
template <typename T ,class comparar>
typename AVL<T,comparar>::const_iterator AVL<T,comparar>::cbegin() const{
  return AVL<T,comparar>::const_iterator( el_avl.begin_inorder() );
}

// Método cend().
template <typename T ,class comparar>
typename AVL<T,comparar>::const_iterator AVL<T,comparar>::cend() const{
  return AVL<T,comparar>::const_iterator( el_avl.end_inorder() );
}

//------------------------------------------------------------------------------------------------------
//  Clase reverse_iterator.
//------------------------------------------------------------------------------------------------------

// Constructor por defecto.
template <typename T ,class comparar>
AVL<T,comparar>::reverse_iterator::reverse_iterator(){
}

// Constructor de copia con reverse_iterator.
template <typename T ,class comparar>
AVL<T,comparar>::reverse_iterator::reverse_iterator( const AVL<T,comparar>::reverse_iterator & it){
  mi_r_it = it.mi_r_it;
}

// Constructor de copia con inorder_iterator.
template <typename T ,class comparar>
AVL<T,comparar>::reverse_iterator::reverse_iterator(const typename bintree<std::pair<T, altura> >::inorder_iterator & it){
  mi_r_it = it;
}

// Operador *.
template <typename T ,class comparar>
T & AVL<T,comparar>::reverse_iterator::operator * (){
  return (*mi_r_it).first ;
}

// Operador ++ (Pre-Fijo.)
template <typename T ,class comparar>
typename AVL<T,comparar>::reverse_iterator & AVL<T,comparar>::reverse_iterator::operator ++(){
  // Incrementamos el objeto. Lo que en el inorder_iterator sería decrementar.
  --mi_r_it;

  // Devolvemos el objeto incrementado.
  return *this;
}

// Operator ==.
template <typename T, class comparar>
bool AVL<T,comparar>::reverse_iterator::operator ==( const typename AVL<T,comparar>::reverse_iterator & it ){
  return mi_r_it == it.mi_r_it;
}

// Operator !=.
template <typename T, class comparar>
bool AVL<T,comparar>::reverse_iterator::operator !=( const typename AVL<T,comparar>::reverse_iterator & it){
  return mi_r_it != it.mi_r_it;
}

//------------------------------------------------------------------------------------------------------
//  Métodos reverse_iterator.
//------------------------------------------------------------------------------------------------------

// Método rbegin().
template <typename T ,class comparar>
typename AVL<T,comparar>::reverse_iterator AVL<T,comparar>::rbegin(){
  return AVL<T,comparar>::reverse_iterator( el_avl.begin_reverse() );
}

// Método rend().
template <typename T ,class comparar>
typename AVL<T,comparar>::reverse_iterator AVL<T,comparar>::rend(){
  return AVL<T,comparar>::reverse_iterator( el_avl.end_reverse() );
}

//------------------------------------------------------------------------------------------------------
//  Clase const_reverse_iterator.
//------------------------------------------------------------------------------------------------------

// Constructor por defecto.
template <typename T ,class comparar>
AVL<T,comparar>::const_reverse_iterator::const_reverse_iterator(){}

// Constructor de copia con const_reverse_iterator.
template <typename T ,class comparar>
AVL<T,comparar>::const_reverse_iterator::const_reverse_iterator( const AVL<T,comparar>::const_reverse_iterator & it ){
  mi_r_it = it.mi_r_it;
}

// Constructor de copia con const_inorder_iterator.
template <typename T ,class comparar>
AVL<T,comparar>::const_reverse_iterator::const_reverse_iterator(
  const typename bintree<std::pair<T, altura> >::const_inorder_iterator & it){
  mi_r_it = it;
}

// Operador *.
template <typename T ,class comparar>
const T & AVL<T,comparar>::const_reverse_iterator::operator *() const{
  return (*mi_r_it).first;
}

// Operador ++ (Pre-fijo).
template <typename T ,class comparar>
typename AVL<T,comparar>::const_reverse_iterator & AVL<T,comparar>::const_reverse_iterator::operator ++( ){
  // Incrementamos el objeto. Lo que en el const_inorder_iterator es decrementar.
  --mi_r_it;

  // Devolvemos el objeto implementado.
  return *this;
}

// Operator ==.
template <typename T, class comparar>
bool AVL<T,comparar>::const_reverse_iterator::operator ==( const typename AVL<T,comparar>::const_reverse_iterator & it ) const{
  return mi_r_it == it.mi_r_it;
}

// Operator !=.
template <typename T, class comparar>
bool AVL<T, comparar>::const_reverse_iterator::operator !=( const typename AVL<T,comparar>::const_reverse_iterator & it ) const{
  return mi_r_it != it.mi_r_it;
}

//------------------------------------------------------------------------------------------------------
//  Métodos const_reverse_iterator.
//------------------------------------------------------------------------------------------------------

// Método crbegin().
template <typename T ,class comparar>
typename AVL<T,comparar>::const_reverse_iterator AVL<T,comparar>::crbegin(){
  return const_reverse_iterator( el_avl.begin_reverse() );
}

// Método crend().
template <typename T ,class comparar>
typename AVL<T,comparar>::const_reverse_iterator AVL<T,comparar>::crend(){
  return const_reverse_iterator( el_avl.end_reverse() );
}

//------------------------------------------------------------------------------------------------------
//  Modificadores.
//------------------------------------------------------------------------------------------------------

// Método clear.
template <typename T ,class comparar>
void AVL<T,comparar>::clear(){
  // Limpiamos el árbol.
  el_avl.clear();
  // Ponemos tama a 0.
  tama = 0;
}

// Método insert.
template <typename T, class comparar>
std::pair<typename AVL<T,comparar>::iterator, bool> AVL<T,comparar>::insert(const T & e){
  typename bintree<std::pair<T, typename AVL<T,comparar>::altura > >::node nodo, nodo_padre, insertado;
  std::pair<T, typename AVL<T,comparar>::altura > etiqueta(e,0);

  bool encontrado = find( e, nodo, nodo_padre );

  typename bintree<std::pair<T, typename AVL<T,comparar>::altura> >::node entrada( etiqueta );

  if( !encontrado ){
    if( nodo_padre.null() ){ // El árbol está vacío.
      el_avl.setRoot( entrada );
      insertado = el_avl.root();
    }
    else{
      if( cmp(e,  (*nodo_padre).first) ){
        el_avl.insert_left(nodo_padre, etiqueta);
        insertado = nodo_padre.left();
      }
      else{
        el_avl.insert_right(nodo_padre, etiqueta);
        insertado = nodo_padre.right();
      }
    }
    // Incrementamos tama.
    tama++;
    typename bintree<std::pair<T, typename AVL<T,comparar>::altura> >::node n;
    n = insertado;
    // Nos movemos desde el nodo que hemos incrementado hasta la raíz,
    // y si su altura es igual que la del nodo hijo, incrementamos en una la altura del nodo padre.
    while( !n.parent().null() ){
      n = n.parent();
      (*n).second = h( n );
    }

    n = insertado;

    // Chequear balanceo.
    balancear_arbol( n );
  }
  else{
    insertado = nodo;
  }


  return std::pair< typename AVL<T,comparar>::iterator, bool>(typename AVL<T,comparar>::iterator(insertado), !encontrado);
}

// Método erase.
template <typename T, class comparar>
void AVL<T,comparar>::erase( typename AVL<T,comparar>::iterator & it ){
  typename bintree<std::pair<T, typename AVL<T,comparar>::altura > >::node nodo, nodo_padre;
  bintree<std::pair<T, typename AVL<T,comparar>::altura> > aux;
  bool encontrado = find( (*it) , nodo, nodo_padre );

  if( encontrado ){
    if( nodo.right().null() && nodo.left().null() ){//Es hoja.
      if( nodo_padre.null() ){
        // Es la raíz.
        clear();
      }
      else{
        // No es la raíz.
        if( nodo_padre.left() == nodo ){
          el_avl.prune_left(nodo_padre, aux);
        }
        else{
          el_avl.prune_right(nodo_padre, aux);
        }

        aux.clear();
      }
    }
    else if( nodo.right().null() || nodo.left().null() ){ // Tiene un hijo.
      if( !nodo.left().null() )
        el_avl.prune_left(nodo, aux);
      else
        el_avl.prune_right(nodo, aux);

      if( nodo_padre.null() )
        el_avl = aux;
      else if( nodo_padre.left() == nodo )
        el_avl.insert_left( nodo_padre, aux);
      else
        el_avl.insert_right( nodo_padre, aux);
    }
    else{ // Tiene dos hijos.
      typename bintree<std::pair<T, typename AVL<T,comparar>::altura> >::node pred;

      // Calculamos el nodo más a la izquierda. (Predecesor.)
      pred = nodo.left();
      while( !pred.right().null() )
        pred = pred.right();

      std::pair<T, typename AVL<T,comparar>::altura> valor_pred( *pred );
      typename bintree<std::pair<T, typename AVL<T,comparar>::altura> >::node nodo_a_borrar = nodo;
      typename AVL<T,comparar>::iterator it( pred );
      erase(it);

      *nodo_a_borrar = valor_pred;
    }
  }
  tama --;
  typename bintree<std::pair<T, typename AVL<T,comparar>::altura> >::node n;
  n = nodo;
  // Nos movemos desde el nodo que hemos incrementado hasta la raíz,
  // y si su altura es igual que la del nodo hijo, incrementamos en una la altura del nodo padre.
  while( !n.parent().null() ){
    n = n.parent();
    (*n).second = h( n );
  }

  n = nodo;

  balancear_arbol(nodo_padre);
}

// Método swap.
template <typename T, class comparar>
void AVL<T, comparar>::swap( AVL<T, comparar> & dest ){
  el_avl.swap( dest.el_avl );
}

//------------------------------------------------------------------------------------------------------
//  Operaciones.
//------------------------------------------------------------------------------------------------------

// Método find booleano.
template <typename T, class comparar>
bool AVL<T,comparar>::find(const T & e, typename bintree<std::pair<T,altura> >::node &n,
   typename bintree<std::pair<T,altura> >::node &padre) const{
  bool encontrado = false;
  n = el_avl.root();

  while( !n.null() && !encontrado ){
    if( (*n).first == e ){
      encontrado = true;
    }
    else{
      padre = n;

      // Comprobamos si la etiqueta es mayor.
      if( cmp(e , (*n).first) )
        n = n.left(); // Debe estar a la izquierda de n.
      else
        n = n.right(); // Debe estar a la derecha de n.

    }
  }

  return encontrado;
}

// Método find con iterator.
template <typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::find( const T & e ){
  bool enc;
  typename bintree<std::pair<T, typename AVL<T,comparar>::altura> >::node nodo, nodo_padre;

  enc = find( e, nodo, nodo_padre);

  if( enc )
    return typename AVL<T,comparar>::iterator(nodo);
  else
    return end();
}

// Método upper_bound.
template <typename T, class comparar>
typename AVL<T, comparar>::iterator AVL<T, comparar>::upper_bound( const T & e ){
  typename AVL<T, comparar>::iterator ini, it;

  ini = begin();


  int count = el_avl.size() ;
  int step;
  while( count > 0 ){
    step = count / 2;
    it = ini;
    for( int i = 0; i < step ; i++){
      ++it;
    }

    if( !cmp(e, (*it) ) ){
      ini = ++it;
      count -= step+1;
    }
    else{
      count = step;
    }
  }

  return ini;
}

// Método lower_bound.
template <typename T, class comparar>
typename AVL<T, comparar>::iterator AVL<T, comparar>::lower_bound( const T & e ){
  typename AVL<T, comparar>::iterator ini, it;

  ini = begin();

  int count = tama ;

  int step;
  while( count > 0 ){
    step = count / 2;

    it = ini;
    for( int i = 0; i < step ; i++){
      ++it;
    }

    if( cmp(e, (*it) ) ){
      ini = ++it;
      count -= step+1;
    }
    else{
      count = step;
    }
  }

  return ini;
}

//------------------------------------------------------------------------------------------------------
//  Otras Operaciones.
//------------------------------------------------------------------------------------------------------
template <typename T, class comparar>
int AVL<T, comparar>::balanceo( const typename bintree<std::pair<T, typename AVL<T,comparar>::altura> >::node & n){
  typename bintree<std::pair<T, typename AVL<T, comparar>::altura> >::node izq, der;
  izq = n.left();
  der = n.right();

  return h( izq ) - h( der );
}

// Rotación simple a la izquierda.
template <typename T, class comparar>
void AVL<T,comparar>::rsi( typename bintree< std::pair<T, typename AVL<T,comparar>::altura> >::node & n ){
  bintree<std::pair<T, typename AVL<T,comparar>::altura> > aux, aux2;

  if( !n.right().left().null() ){
    el_avl.prune_left( n.right(), aux2 );
  }

  el_avl.prune_right( n, aux);


  el_avl.insert_right(n,  aux2);

  if( n.parent().null() ){
    // Es la raíz.
    aux2.assign_subtree(el_avl, n);
  }
  else{
    if( n.parent().right() == n ){
      el_avl.prune_right(n.parent(), aux2);
    }
    else{
      el_avl.prune_left(n.parent(), aux2);
    }
  }

  aux.insert_left(aux.root(), aux2);
  el_avl.assign_subtree(aux, aux.root() );

}

// Rotación simple a la derecha.
template <typename T, class comparar>
void AVL<T,comparar>::rsd( typename bintree< std::pair<T, typename AVL<T, comparar>::altura> >::node & n ){
  bintree<std::pair<T, typename AVL<T,comparar>::altura> > aux, aux2;

  if( !n.left().right().null() ){
    el_avl.prune_right( n.left(), aux2 );
  }

  el_avl.prune_left( n, aux);


  el_avl.insert_left(n,  aux2);

  if( n.parent().null() ){
    // Es la raíz.
    aux2.assign_subtree(el_avl, n);
  }
  else{
    if( n.parent().right() == n ){
      el_avl.prune_right(n.parent(), aux2);
    }
    else{
      el_avl.prune_left(n.parent(), aux2);
    }
  }

  aux.insert_right(aux.root(), aux2);
  el_avl.assign_subtree(aux, aux.root() );

}

// Rotación doble a la izquierda.
template <typename T, class comparar>
void AVL<T,comparar>::rdi( typename bintree< std::pair<T, typename AVL<T,comparar>::altura> >::node & n){
  typename bintree< std::pair<T, typename AVL<T, comparar>::altura> >::node aux = n.right();
  rsd( aux );
  rsi(n);
}

// Rotación doble a la derecha.
template <typename T, class comparar>
void AVL<T,comparar>::rdd( typename bintree< std::pair<T, typename AVL<T,comparar>::altura> >::node & n ){
  typename bintree< std::pair<T, typename AVL<T, comparar>::altura> >::node aux = n.left();
  rsi( aux );
  rsd(n);
}

// Altura.
template <typename T, class comparar>
typename AVL<T,comparar>::altura AVL<T,comparar>::h(
            typename bintree< std::pair<T, typename AVL<T,comparar>::altura> >::node & n){
    if( n.null() )
      return -1;

    typename bintree< std::pair<T, typename AVL<T, comparar>::altura> >::node r, l;
    l = n.left();
    r = n.right();

    return 1 + std::max( h( l ), h( r ) );
}

template <typename T, class comparar>
typename AVL<T, comparar>::altura AVL<T,comparar>::h(
    typename bintree< std::pair<T, typename AVL<T, comparar>::altura> >::const_node & n )const{

    if( n.null() )
      return -1;

    typename bintree< std::pair<T, typename AVL<T, comparar>::altura> >::const_node r, l;
    l = n.left();
    r = n.right();

    return 1 + std::max( h( l ) , h( r ) );
}

// Método balancear árbol.
template <typename T, class comparar>
void AVL<T, comparar>::balancear_arbol( typename bintree<std::pair<T, typename AVL<T, comparar>::altura> >::node & n){
  // Vamos subiendo hasta la raíz, y si encontramos que un nodo tiene un balanceo >= 2 o <= -2
  // balanceamos el árbol.
  bool balanceado = false;
  while( ! n.parent().null() && ! balanceado ){
    if( balanceo(n) >= 2 || balanceo(n) <= -2 ){
      // Calculamos donde está el desequilibrio.
      if(( *n.left().left() ).second > 0 )
        rsd(n);
      else if( (*n.left().right() ).second > 0 )
        rdd(n);
      else if( (*n.right().left() ).second > 0 )
        rdi(n);
      else
        rsi(n);

      balanceado = true;
    }
    else{
      // Subimos por el árbol.
      n = n.parent();
    }
  }

}
