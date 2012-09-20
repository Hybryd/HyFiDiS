
template <typename T>
HyCircle<T>::HyCircle() : HyBoundary<T>(), aRadius(1), aCenter(0,0,0)
{
}


template <typename T>
HyCircle<T>::HyCircle(double pRadius, HyPoint<T> & pP) : HyBoundary<T>(), aRadius(pRadius), aCenter(pP)
{
}


template <typename T>
double HyCircle<T>::getBoundary(HyPoint<T> & pPoint)
{
  return HyBoundary<T>::getBoundary(pPoint);
}

template <typename T>
double HyCircle<T>::getBoundary(T pX, T pY, T pZ)
{
//  double res=0;
//  
//  if(pX<0 || pX>20 || pY<0 || pY>10)
//    res=-1;
//  else if((pX==0 || pX==20) && pY>=0 && pY<=10  || (pY==0 || pY==10) && pX>=0 && pX<=20)
//    res=0;
//  else
//    res=1;
//    
//  return res;
//  std::cerr << "DACIRCLE" << std::endl;
  double res = 0;
  double lX = (pX-aCenter.getX())*(pX-aCenter.getX()) + (pY-aCenter.getY())*(pY-aCenter.getY()) + (pZ-aCenter.getZ())*(pZ-aCenter.getZ());
  if (lX < this->aRadius*this->aRadius )
    res = 1;
  else if (lX == this->aRadius*this->aRadius)
    res = 0;
  else
    res = -1;
    
  return res;
  
}

template <typename T>
HyCircle<T> &      HyCircle<T>::operator=(const HyCircle<T> & pC)
{
  if(&pC != this)
  {
    aRadius = pC.getRadius();
    aCenter = pC.getCenter();
  }
  return *this;
}


template <typename T>
std::ostream & operator<<(std::ostream & pOut, HyCircle<T> & pC)
{
  pOut << "Radius : " << pC.getRadius() << ", Center : " << pC.getCenter();
}

