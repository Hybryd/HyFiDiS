#ifndef HYPOISSON2D_HPP
#define HYPOISSON2D_HPP


/*!
* \file   HyPoisson2D.hpp
* \brief  Header file of HyPoisson2D class.
*
*/


#include <string>
#include "HyBoundary.hpp"
//#include "HyMatrix.hpp"
#include "HyMesh2D.hpp"
#include "HyProblem.hpp"
//#include "HySetPoints.hpp"
//#include "HyVector.hpp"




/*!
*
* \class HyPoisson2D
* \brief Poisson equation in 2 dimensions: \f$ \Delta u = f \f$
*
* 
*/

template <typename T>
class HyPoisson2D : public HyProblem<T>
{
protected:

public:
  HyPoisson2D();
  HyPoisson2D(HyDomain<T> & pDomain, HyBoundary<T> & pBoundary, HyMesh2D<T> & pMesh, std::string & pDescription );
  void build();
  void solve();

  double g(HyPoint<T> pPoint); // Dirichlet condition
  double g(T pX, T pY, T pZ);

  double f(HyPoint<T> pPoint);
	double f(T pX, T pY);
  
  
  
};

template <typename T>
std::ostream & operator<<(std::ostream & out, HyPoisson2D<T> pProb);

#include "HyPoisson2D.ipp"

#endif
