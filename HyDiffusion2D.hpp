#ifndef HYDIFFUSION2D_HPP
#define HYDIFFUSION2D_HPP


/*!
*
* \file   HyDiffusion2D.hpp
* \brief  Header file of HyDiffusion2D class.
*
*/


#include <string>
#include "HyBoundary.hpp"
#include "HyMesh2D.hpp"
#include "HyProblem.hpp"




/*!
*
* \class HyDiffusion2D
* \brief Diffusion equation in 2 dimensions: \f$ \partial_t u - \kappa\Delta u = f \f$
* 
*/

template <typename T>
class HyDiffusion2D : public HyProblem<T>
{
protected:
  /*! The maximal time */
  long int                      aTmax;
  /*! The number of temporal steps*/
  unsigned long int             aNbTimeStep;
  /*! The diffusion coefficient */
  double                        aK;
  /*! The matrix B for the theta method ( A x(n+1) = B x(n) + F + G ) */
  Eigen::SparseMatrix<T>   aMatrixB; 
  /*! The set of all solution for each time step */          
  std::vector<Eigen::VectorXd>  aEvolution;
  
    

public:
  HyDiffusion2D();
  HyDiffusion2D(HyDomain<T> & pDomain, HyBoundary<T> & pBoundary, HyMesh2D<T> & pMesh, std::string & pDescription, long int pTmax, unsigned long int pNbTimeStep=1,double pK = 1);
  
  std::vector<Eigen::VectorXd> getEvolution() const {return aEvolution;}
  
  void build();
  void buildTheta(double pTheta);
  void solve();
  void solveExplicit();
  void solveTheta();
  
  
//  void applySolution(unsigned long int t);
  void displaySolutionGP(std::ostream & out, unsigned long int t);

  double g(HyPoint<T> pPoint); // Dirichlet condition
  double g(T pX, T pY, T pZ);

  double f(HyPoint<T> pPoint);
	double f(T pX, T pY);
  
  double initialCondition(HyPoint<T> pPoint);
  double initialCondition(T pX, T pY);
  

};


template <typename T>
std::ostream & operator<<(std::ostream & out, HyDiffusion2D<T> pProb);

#include "HyDiffusion2D.ipp"

#endif

