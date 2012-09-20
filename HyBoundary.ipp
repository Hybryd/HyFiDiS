/*!
*
* \file   HyBoundary.ipp
* \brief  Template file of HyBoundary class.
*
*/

/*!
*
* \fn HyBoundary<T>::HyBoundary()
* \brief Default constructor of HyBoundary.
*
*/

template <typename T>
HyBoundary<T>::HyBoundary()
{
}

/*!
*
* \fn HyBoundary<T>::HyBoundary(std::string pDescription)
* \brief Constructor of HyBoundary.
* \param pDescription Brief description of the boundary.
*
*/

template <typename T>
HyBoundary<T>::HyBoundary(std::string pDescription) : aDescription(pDescription)
{
}



/*!
*
* \fn double HyBoundary<T>::getBoundary(HyPoint<T> & pPoint)
* \brief Definition of the boundary. Positive inside the domain, 0 on the boundary, negative outside.
* \param pPoint The point to evalutate.
*
*/
template <typename T>
double HyBoundary<T>::getBoundary(HyPoint<T> & pPoint)
{
  return this->getBoundary(pPoint.getX(),pPoint.getY(),pPoint.getZ());
}

/*!
*
* \fn HyBoundary<T> & HyBoundary<T>::operator=(const HyBoundary<T> & pB)
* \brief operator=
* \param pB The HyBoundary to copy.
*
*/
template <typename T>
HyBoundary<T> & HyBoundary<T>::operator=(const HyBoundary<T> & pB)
{
  if(&pB != this)
    aDescription = pB.getDescription();
  
  return *this;
}

/*!
*
* \fn std::ostream & operator<<(std::ostream & out, HyBoundary<T> pBound)
* \brief operator<<
* \param out The ostream to write in.
* \param pBound The HyBoundary to display.
*/
template <typename T>
std::ostream & operator<<(std::ostream & out, HyBoundary<T> pBound)
{
  out << pBound.getDescription();
  return out;
}




