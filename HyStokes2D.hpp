#ifndef HYSTOKES2D_HPP
#define HYSTOKES2D_HPP


/*!
*
* \file   HyStokes2D.hpp
* \brief  Header file of HyStokes2D class.
*
*/


#include <string>
#include "HyBoundary.hpp"
#include "HyMesh2D.hpp"
#include "HyProblem.hpp"




/*!
*
* \class HyStokes2D
* \brief Stokes flow equation in 2 dimensions: \f$ -\nu \Delta \emph{u} + \nabla p = \emph{f}\f$  in \f$\Omega\f$, \f$ div(\emph{u}) = 0\f$ in \f$\Omega\f$, \f$\emph{u}=\emph{g}\f$ in \f$\partial\Omega\f$.
* 
*/

template <typename T>
class HyStokes2D : public HyProblem<T>
{
protected:
  double aNu;
  Eigen::VectorXd               aP;
  Eigen::SparseMatrix<T>   aMatrixA;
  Eigen::SparseMatrix<T>   aMatrixB;

public:
  HyStokes2D();
  HyStokes2D(HyDomain<T> & pDomain, HyBoundary<T> & pBoundary, HyMesh2D<T> & pMesh, std::string & pDescription );

  void build();
  void solve();

  double g(HyPoint<T> pPoint); // Dirichlet condition
  double g(T pX, T pY, T pZ);

  double f(HyPoint<T> pPoint);
	double f(T pX, T pY);

};


template <typename T>
std::ostream & operator<<(std::ostream & out, HyStokes2D<T> pProb);

#include "HyStokes2D.ipp"

#endif
