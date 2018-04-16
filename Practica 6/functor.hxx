/**
* Implementación functor.
* Alberto Armijo Ruiz.
* 2 º GII A.
*/

template <typename T>
bool compare<T>::operator() (const T & a, const T & b )const{
  return a < b;
}
