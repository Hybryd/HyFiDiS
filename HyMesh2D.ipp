#include "HyPoint.hpp"

template <typename T>
HyMesh2D<T>::HyMesh2D()
{
}

template <typename T>
std::vector< HyPoint<T> > & HyMesh2D<T>::operator[](unsigned long i)
{
  if(i>=0 && i<aMesh.size())
    return aMesh[i];
  else
    std::cerr << "ERROR in HyMesh2D<T>::operator[](unsigned long i) : " << std::endl;
    std::cerr << "   Check the index" << std::endl;
}


template <typename T>
HyMesh2D<T>::HyMesh2D(HyPoint<T> & pBL, HyPoint<T> & pUR, unsigned long pNbRectanglesX, unsigned long pNbRectanglesY) : aNbRectanglesX(pNbRectanglesX),aNbRectanglesY(pNbRectanglesY)
{
  unsigned long int lCpt=0;
  if(pNbRectanglesX > 0 && pNbRectanglesY > 0 && pBL.getX() < pUR.getX() && pBL.getY() < pUR.getY() )
  {
    ahX = (pUR.getX() - pBL.getX())/pNbRectanglesX;
//    aNbRectanglesY = (unsigned long int)((pUR.getY() - pBL.getY() + 1)/ah);
    ahY = (pUR.getY() - pBL.getY())/pNbRectanglesY;
//    std::cout << "h = " << ah << std::endl;
    for(unsigned long int i=0; i<= pNbRectanglesX;++i)
    {
      std::vector<HyPoint<T> > v;
      aMesh.push_back(v);
      for(unsigned long int j=0; j<= aNbRectanglesY;++j)
      {
        HyPoint<T> lPoint(i*ahX,j*ahY,0,lCpt);
        aMesh[i].push_back(lPoint);
        ++lCpt;
      }
    }
  }
  else
  {
    std::cerr << "ERROR in HyMesh2D<T>::HyMesh2D(HyPoint<T> & pBL, HyPoint<T> & pUR, unsigned long pNbRectanglesX, unsigned long pNbRectanglesY) : " << std::endl; 
    std::cerr << "   Check the points defining the Mesh" << std::endl;
  }
}

template <typename T>
HyMesh2D<T>::HyMesh2D( HyMesh2D<T> & pMesh) : aNbRectanglesX(pMesh.aNbRectanglesX),
                                              aNbRectanglesY(pMesh.aNbRectanglesY),
                                              ahX(pMesh.ahX),
                                              ahY(pMesh.ahY)
{
  for(unsigned long int i=0; i<=aNbRectanglesX;++i)
  {
    std::vector<HyPoint<T> > v;
    aMesh.push_back(v);
    for(unsigned long int j=0; j<= aNbRectanglesY;++j)
    {
      aMesh[i].push_back(pMesh[i][j]);
    }
  }
}


template <typename T>
std::ostream & operator<<(std::ostream & out, HyMesh2D<T> & pM)
{
  #if DISPLAY_MESH_GRID_STYLE == 1
  for(long int j=pM.getMesh()[0].size()-1; j>=0; --j)
  {
    if(j>=10)
      out << j << " ";
    else
      out << j << "  ";
    for(unsigned long int i=0; i< pM.size();++i)
    {
      out << ".  ";
    }
    out << std::endl;
  }
  out << "   ";
  for(unsigned long int i=0; i< pM.size();++i)
  {
    if(i>=10)
      out << i << " ";
    else
      out << i << "  ";
  }
  
  #else
  
  for(long int j=pM.getMesh()[0].size()-1; j>=0; --j)
  {
    for(unsigned long int i=0; i< pM.size();++i)
    {
      #if DISPLAY_WHOLE_MESH == 0
        if (pM[i][j].getLocality() == 1)
          out << pM[i][j] << std::endl;
      #else
        out << pM[i][j] << std::endl;
      #endif
      out << " ";
    }
    #if DISPLAY_GNUPLOT == 0
    out << std::endl;
    #endif
  }
  #endif
  return out;
}
