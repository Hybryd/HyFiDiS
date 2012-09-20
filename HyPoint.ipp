
template <typename T>
HyPoint<T>::HyPoint() : aX(0), aY(0), aZ(0),aID(0),aRegular(true),aLocality(-1),aNeigW(NULL),aNeigE(NULL),aNeigN(NULL),aNeigS(NULL),aBoundary(0)
{
}

template <typename T>
HyPoint<T>::HyPoint(T pX, T pY, T pZ=0, unsigned long pID=0, bool pRegular=true): aX(pX), aY(pY), aZ(pZ), aID(pID), aRegular(pRegular)
{
}


template <typename T>
HyPoint<T>::HyPoint(const HyPoint<T> & pP) : aX(pP.aX), aY(pP.aY), aZ(pP.aZ), aID(pP.aID), aRegular(pP.aRegular),aLocality(pP.aLocality),aNeigW(pP.aNeigW),aNeigE(pP.aNeigE),aNeigN(pP.aNeigN),aNeigS(pP.aNeigS),aBoundary(pP.aBoundary)
{
}




template <typename T>
HyPoint<T> operator+(HyPoint<T> const& pA, HyPoint<T> const& pB)
{
  HyPoint<T> res(pA);
  res.setX(pA.getX() + pB.getX());
  res.setY(pA.getY() + pB.getY());
  res.setZ(pA.getZ() + pB.getZ());
  return res;
}


template <typename T>
HyPoint<T> operator/(HyPoint<T> const& pA, double pX)
{
  HyPoint<T> res(pA);
  if(pX != 0)
  {
    res.setX(pA.getX()/pX);
    res.setY(pA.getY()/pX);
    res.setZ(pA.getZ()/pX);
  }
  else
    std::cerr << "ERROR in HyPoint<T> operator/(HyPoint<T> const& pA, double pX) : division by O.";
  return res;
}


template <typename T>
HyPoint<T> & HyPoint<T>::operator=(const HyPoint<T> & pP)
{
  if(&pP != this)
  {
    aX = pP.aX;
    aY = pP.aY;
    aZ = pP.aZ;
    aID = pP.aID;
    aRegular = pP.aRegular;
    aLocality = pP.aLocality;
    aNeigW = pP.aNeigW;
    aNeigE = pP.aNeigE;
    aNeigN = pP.aNeigN;
    aNeigS = pP.aNeigS;
    aBoundary = pP.aBoundary;
  }
  return *this;
}

template <typename T>
bool HyPoint<T>::operator==(const HyPoint<T> & pPoint)
{
	return (aX==pPoint.aX && aY==pPoint.aY && aZ==pPoint.aZ);
}

template <typename T>
bool HyPoint<T>::operator!=(const HyPoint<T> & pPoint)
{
	return (!((*this)==pPoint));
}

template <typename T>
double HyPoint<T>::distance(const HyPoint<T> & pPoint)
{
	return sqrt( (aX-pPoint.aX)*(aX-pPoint.aX) + (aY-pPoint.aY)*(aY-pPoint.aY) + (aZ-pPoint.aZ)*(aZ-pPoint.aZ) );
}

template <typename T>
double HyPoint<T>::sqDistance(const HyPoint<T> & pPoint)
{
	return ( (aX-pPoint.aX)*(aX-pPoint.aX) + (aY-pPoint.aY)*(aY-pPoint.aY) + (aZ-pPoint.aZ)*(aZ-pPoint.aZ) );
}



template <typename T>
std::ostream & operator<<(std::ostream & pOut, HyPoint<T> & pP)
{
  pOut << pP.getX() << " " << pP.getY();
  return pOut;
}



