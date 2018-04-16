/*! Implementacion  de la clase conjunto

*/

/** @todo implementar la funcion
*/

conjunto::conjunto(){
  lo que se tenga que poner
}

conjunto::iterator conjunto::begin() const{
conjunto::iterator sal;
	sal.itv = vc.begin();
        return sal;
}


conjunto::iterator conjunto::end() const{
conjunto::iterator sal;
	sal.itv = vc.end();
        return sal;
}
/** @brief constructor defecto iterator
*/
conjunto::iterator::iterator(){

}

/** @brief constructor copia iterator
*/
conjunto::iterator::iterator(const conjunto::iterator & i)
  itv = i.itv;
}


