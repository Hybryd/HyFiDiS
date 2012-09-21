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
* \brief Stokes flow equation in 2 dimensions: \f$ -\eta \Delta \emph{u} + \nabla p = \emph{f}\f$  in \f$\Omega\f$, \f$ div(\emph{u}) = 0\f$ in \f$\Omega\f$, \f$\emph{u}=\emph{g}\f$ in \f$\partial\Omega\f$.
* 
*/

template <typename T>
class HyStokes2D : public HyProblem<T>
{
protected:
  

public:
  HyStokes2D();

};


template <typename T>
std::ostream & operator<<(std::ostream & out, HyStokes2D<T> pProb);

#include "HyStokes2D.ipp"

#endif
