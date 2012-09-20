#include "HyPoint.hpp"

template <typename T>
HyMesh1D<T>::HyMesh1D()
{
}



template <typename T>
HyMesh1D<T>::HyMesh1D(HyPoint<T> & pBL, HyPoint<T> & pUR, unsigned long pNbRectanglesX) : aNbRectanglesX(pNbRectanglesX)
{
  unsigned long int lCpt=0;
  if(pNbRectanglesX > 0 && pBL.getX() < pUR.getX())
  {
    ahX = (pUR.getX() - pBL.getX())/pNbRectanglesX;
    for(unsigned long int j=0; j<= aNbRectanglesY;++j)
    {
      HyPoint<T> lPoint(i*ahX,0,0,lCpt);
      aMesh[i].push_back(lPoint);
      ++lCpt;
    }
  }
  else
  {
    std::cerr << "ERROR in HyMesh1D<T>::HyMesh1D(HyPoint<T> & pBL, HyPoint<T> & pUR, unsigned long pNbRectanglesX) : " << std::endl; 
    std::cerr << "   Check the points defining the Mesh" << std::endl;
  }
}

template <typename T>
HyMesh1D<T>::HyMesh1D( HyMesh1D<T> & pMesh) : aNbRectanglesX(pMesh.aNbRectanglesX),
                                              ahX(pMesh.ahX)
{
  for(unsigned long int i=0; i<=aNbRectanglesX;++i)
  {
    aMesh[i].push_back(pMesh[i]);
  }
}


template <typename T>
HyPoint<T> HyMesh1D<T>::operator[](unsigned long i)
{
  if(i>=0 && i<aMesh.size())
    return aMesh[i];
  else
    std::cerr << "ERROR in HyMesh1D<T>::operator[](unsigned long i) : " << std::endl;
    std::cerr << "   Check the index" << std::endl;
}


template <typename T>
std::ostream & operator<<(std::ostream & out, HyMesh1D<T> & pM)
{
  #if DISPLAY_MESH_GRID_STYLE == 1
    for(unsigned long int j=0; j< pM.size(); ++j)
      out << ".  ";
    out << std::endl;
    for(unsigned long int i=0; i< pM.size();++i)
    {
      if(i>=10)
        out << i << " ";
      else
        out << i << "  ";
    }
  #else
    for(unsigned long int i=0; i< pM.size();++i)
      out << pM[i] << std::endl;
    out << std::endl;
  #endif
  return out;
}
