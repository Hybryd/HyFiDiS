#ifndef HYPROBLEM_HPP
#define HYPROBLEM_HPP


/*!
* \file   HyProblem.hpp
* \brief  Header file of HyProblem class.
*
*/


#include <iostream>
#include <string>

#include "HyBoundary.hpp"
#include "HyMesh2D.hpp"
#include "HyProblem.hpp"
#include "HyDomain.hpp"


#include <Eigen/Sparse>

using namespace Eigen;

/*!
*
* \class HyProblem
* \brief Defines a physical problem.
*
* The class HyProblem represents a physical problem described by a domain, its boundary, the corresponding PDE and the boundary conditions.
* The numerical solution is obtained by solving the linear system AX = F+G. A represents the matrix (determined by the equation of the problem), X is the unknown vector (the approximate solution), F
*/

template <typename T>
class HyProblem
{
protected:
  /*! The whole rectangular domain that will determine the mesh */
  HyDomain<T>                 & aDomain;
  /*! The boundary of the domain */
  HyBoundary<T>               & aBoundary;
  /*! The mesh for the numerical resolution */
  HyMesh2D<T>                 & aMesh;
  /*! A brief description of the problem */
  std::string                 & aDescription;

	/*	Ax = F+G  */
  /*! The matrix A of the linear problem */
  Eigen::SparseMatrix<T>   aMatrix;
  /*! The unknown solution */
  Eigen::VectorXd               aX;
  /*! The vector containing values of the f function */
  Eigen::VectorXd               aF;
  /*! The vector containing values of the Dirichlet condition */
  Eigen::VectorXd               aG;
  
public:
  HyProblem();
  HyProblem(HyDomain<T> & pDomain, HyBoundary<T> & pBoundary, HyMesh2D<T> & pMesh, std::string & pDescription);
  
  HyBoundary<T>               & getBoundary()     {return aBoundary;}
  std::string                 & getDescription()  {return aDescription;}
  HyDomain<T>                 & getDomain()       {return aDomain;}
  HyMesh2D<T>                 & getMesh()         {return aMesh;}
  Eigen::SparseMatrix<T> & getMatrix()       {return aMatrix;}
  Eigen::VectorXd             & getX()            {return aX;}               // CHANGER VectorXd <- pas forcément des doubles!
  Eigen::VectorXd             & getF()            {return aF;}
  Eigen::VectorXd             & getG()            {return aG;}
  
  void                          setBoundary(HyBoundary<T> & lB) {aBoundary = lB;}
  void                          setX(Eigen::VectorXd pVector) {aX = pVector;}
    
//  void applySolution();
  virtual void build()=0;
  void updateMesh();
  virtual void solve()=0;
//  void projectionOnGamma(HyPoint<T> & pPointIn, HyPoint<T> & pPointOut, double * ph, double * pu); // ph : step, pu, value of g(P) where P is the intersection of [pIn,pOut] and Gamma
  
	
  double g(HyPoint<T> pPoint); // Dirichlet condition
  double g(T pX, T pY, T pZ);
  
  void display(std::ostream & out);
  void displaySolutionGP(std::ostream & out);

  HyProblem<T> & operator=(const HyProblem<T> & pP);
  
};

template <typename T>
std::ostream & operator<<(std::ostream & out, HyProblem<T> pProb);

#include "HyProblem.ipp"

#endif
