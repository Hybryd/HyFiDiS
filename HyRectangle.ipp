
template <typename T>
HyRectangle<T>::HyRectangle() : HyBoundary<T>(), aBL(0,0,0), aUR(0,0,0)
{
}


template <typename T>
HyRectangle<T>::HyRectangle(HyPoint<T> & pBL, HyPoint<T> & pUR) : HyBoundary<T>(), aBL(pBL), aUR(pUR)
{
  if(!(pBL.getX() < pUR.getX() && pBL.getY() < pUR.getY()))
    std::cerr << "ERROR in HyRectangle<T>::HyRectangle(HyPoint<T> & pBL, HyPoint<T> & pUR) : HyBoundary<T>() : Check the points.";
}


template <typename T>
double HyRectangle<T>::getBoundary(HyPoint<T> & pPoint)
{
  return HyBoundary<T>::getBoundary(pPoint);
}


template <typename T>
double HyRectangle<T>::getBoundary(T pX, T pY, T pZ)
{
  double res = 0;
  
  if(pX > this->aBL.getX() && pX < this->aUR.getX() && pY > this->aBL.getY() && pY < this->aUR.getY())
    res = 1;
  else if(pX < this->aBL.getX() || pX > this->aUR.getX() || pY < this->aBL.getY() || pY > this->aUR.getY())
    res = -1;
  else
    res = 0;
    
  return res;
  
}



template <typename T>
std::ostream & operator<<(std::ostream & pOut, HyRectangle<T> & pC)
{
  pOut << pC.getBL() << " --> " << pC.getUR();
}

