///
/// \file HyMesh1D.hpp
/// \date 2010
///
/// Header of HyMesh1D class. Represents a cartesian 1D mesh.
///

#ifndef HYMESH1D_HPP
#define HYMESH1D_HPP

#include <iostream>
#include <vector>
#include "HyMesh.hpp"
#include "Variables.hpp"


template <typename T>
class HyMesh1D : public HyMesh<T>
{
protected:
  std::vector<HyPoint<T> >                aMesh;
  unsigned long                           aNbRectanglesX;
  double                                  ahX;

public:
  HyMesh1D();
  HyMesh1D(HyPoint<T> & pBL, HyPoint<T> & pUR, unsigned long pNbRectanglesX);
  HyMesh1D(HyMesh1D<T> & pMesh);

  std::vector< HyPoint<T> >   getMesh()               {return aMesh;}
  unsigned long               getNbRectanglesX()      {return aNbRectanglesX;}
  double        getHX()                               {return ahX;            }
  unsigned long size()                                {return aMesh.size();  }
  HyPoint<T> & operator[](unsigned long i);
  
  void  display() {std::cout << "";}
  
};

template <typename T>
std::ostream & operator<<(std::ostream & out, HyMesh1D<T> & pM);

#include "HyMesh1D.ipp"

#endif
