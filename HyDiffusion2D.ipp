/*!
*
* \file   HyDiffusion2D.ipp
* \brief  Template file of HyDiffusion2D class.
*
*/


/*!
*
* \fn HyDiffusion2D<T>::HyDiffusion2D()
* \brief Default constructor
*
*/

template <typename T>
HyDiffusion2D<T>::HyDiffusion2D()
{
}

/*!
*
* \fn HyDiffusion2D<T>::HyDiffusion2D(HyBoundary2D<T> & pBoundary, std::string & pDescription, HyMesh2D<T> & pMesh, long int pTmax)
* \brief Constructor. Initializes the matrix and the vectors
* \param pBoundary Boundary of the domain
* \param pDescription Description of the problem
* \param pMesh Mesh of the domain
* \param pTmax Maximal time
*
*/

template <typename T>
HyDiffusion2D<T>::HyDiffusion2D(  HyDomain<T> & pDomain,
                              HyBoundary<T> & pBoundary,
                              HyMesh2D<T> & pMesh,
                              std::string & pDescription,
                              long int pTmax,
                              unsigned long int pNbTimeStep,
                              double pK
                           ) : HyProblem<T>(pDomain,pBoundary,pMesh,pDescription),aMatrixB((this->aMesh.getNbRectanglesX()+1)*(this->aMesh.getNbRectanglesY()+1),(this->aMesh.getNbRectanglesX()+1)*(this->aMesh.getNbRectanglesY()+1))
{
  aTmax = pTmax;
  if(pNbTimeStep != 0)
    aNbTimeStep = pNbTimeStep;
  else
    std::cerr << "Error in HyDiffusion2D constructor : the number of steps is 0." << std::endl;
  aK = pK;
//  aMatrixB.resize(((this->aMesh.getNbRectanglesX()+1)*(this->aMesh.getNbRectanglesY()+1),(this->aMesh.getNbRectanglesX()+1)*(this->aMesh.getNbRectanglesY()+1)));
  
  
  for(unsigned long int i=0;i<aTmax;++i)
  {
    Eigen::VectorXd lX((this->aMesh.getNbRectanglesX()+1)*(this->aMesh.getNbRectanglesY()+1));
    aEvolution.push_back(lX);
  }
  
//  std::cerr << "KOKO7" << std::endl;
  
  this->aMatrixB.reserve(VectorXi::Constant((this->aMesh.getNbRectanglesX()+1)*(this->aMesh.getNbRectanglesY()+1),5)); // ===NOMBRE DE VOISINS CHANGE EN 3D
//  std::cerr << "KOKO8" << std::endl;
  for(unsigned long int i=0;i<this->aMatrixB.innerSize();++i)
    this->aMatrixB.coeffRef(i,i)=1;
//  std::cerr << "KOKO9" << std::endl;
//  aEvolution = std::vector<Eigen::VectorXd> lVect(aTmax);
//  build();
}

/*!
*
* \fn void HyDiffusion2D<T>::build()
* \brief Fills the matrix A and the vectors F and G
*
*/
template <typename T>
void HyDiffusion2D<T>::build()
{

  unsigned long int lIndex = 0;
  unsigned long int lNeigW, lNeigE, lNeigN, lNeigS;
  double            lBound;
  bool              lIsOnBoundary=false;
  
  double            lDt = (this->aTmax)/(this->aNbTimeStep);
  double            lAlpha = (this->aK*lDt)/(this->aMesh.getHX()*this->aMesh.getHY());
//  std::cerr << "ALPHA : " << lAlpha << std::endl;
  
  
//  // First, check if each point is inside the domain Omega, on the boundary Gamma, or ouside the domain. And update neighbourhood.
//  for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
//  {
//    for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
//    {
//      
//      lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;
//      
////      std::cerr << "Point : (" << lIndex << ", " << this->aMesh[i][j].getLocality() << "," << this->aMesh[i][j].getBoundary() << ") : " << this->aMesh[i][j] << std::endl; 
//      lBound = this->aBoundary.getBoundary(this->aMesh[i][j]);
//      
//      
//      if(lBound > 0)
//        this->aMesh[i][j].setLocality(1);
//      else if (lBound == 0)
//        this->aMesh[i][j].setLocality(0);
//      else
//        this->aMesh[i][j].setLocality(-1);
//      
//      if(j!=0)
//        this->aMesh[i][j].setNeigS(&(this->aMesh[i][j-1]));
//      if(j!=this->aMesh.getNbRectanglesY())
//        this->aMesh[i][j].setNeigN(&(this->aMesh[i][j+1]));
//      if(i!=0)
//        this->aMesh[i][j].setNeigW(&(this->aMesh[i-1][j]));
//      if(i!=this->aMesh.getNbRectanglesX())
//        this->aMesh[i][j].setNeigE(&(this->aMesh[i+1][j]));
//    }
//  }  
  HyProblem<T>::updateMesh();
  
  for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
  {
    for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
    {
      lNeigW = 0;
      lNeigE = 0;
      lNeigN = 0;
      lNeigS = 0;


      // Index of the Xij in the matrix and vector
      lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;

      // Set if the point is in the domain omega and has at least one neigbour outside
      lIsOnBoundary=false;
      if(this->aMesh[i][j].getLocality()==-1)
      {
        this->aMesh[i][j].setBoundary(false);
      }
      else if(this->aMesh[i][j].getLocality()==1)
      {
        if(this->aMesh[i][j].getNeigW() != NULL)
          lIsOnBoundary |= (this->aMesh[i][j].getNeigW()->getLocality() == -1);
        if(this->aMesh[i][j].getNeigE() != NULL)
          lIsOnBoundary |= (this->aMesh[i][j].getNeigE()->getLocality() == -1);
        if(this->aMesh[i][j].getNeigN() != NULL)
          lIsOnBoundary |= (this->aMesh[i][j].getNeigN()->getLocality() == -1);
        if(this->aMesh[i][j].getNeigS() != NULL)
          lIsOnBoundary |= (this->aMesh[i][j].getNeigS()->getLocality() == -1);
        this->aMesh[i][j].setBoundary(lIsOnBoundary);
//        std::cout << this->aMesh[i][j] << " : " << this->aMesh[i][j].getBoundary() << std::endl;
      }
      else if(this->aMesh[i][j].getLocality()==0)
        this->aMesh[i][j].setBoundary(true);
      
      

      
      // If the point is inside the domain (not in the boundary)
			if(this->aMesh[i][j].getLocality() == 1)
      {
//        std::cerr << this->aMesh[i][j] << " 1" << std::endl;      
      
        // Filling F
        this->aF(lIndex) = f(this->aMesh[i][j])*lDt;
        this->aMatrix.coeffRef(lIndex,lIndex)=-4*lAlpha;

        
        // Indexes of the neighbours
        // -J-
        // Bottom
        if(j==0)
        {
          lNeigN=(j+1)*(this->aMesh.getNbRectanglesX()+1) + i;
        }
//        
        // Top
        else if(j==this->aMesh.getNbRectanglesY())
        {
          lNeigS=(j-1)*(this->aMesh.getNbRectanglesX()+1) + i;
        }

        // Middle
        else
        {
          lNeigN=(j+1)*(this->aMesh.getNbRectanglesX()+1) + i;
          lNeigS=(j-1)*(this->aMesh.getNbRectanglesX()+1) + i;
        }

        // -I-
        // Left
        if(i==0)
        {
          lNeigE=j*(this->aMesh.getNbRectanglesX()+1) + i + 1;
        }

        // Right
        else if(i==this->aMesh.getNbRectanglesX())
        {
          lNeigW=j*(this->aMesh.getNbRectanglesX()+1) + i-1;
        }

        // Middle
        else
        {
          lNeigE=j*(this->aMesh.getNbRectanglesX()+1) + i + 1;
          lNeigW=j*(this->aMesh.getNbRectanglesX()+1) + i - 1;
        }
        
        // Check the neighbours
        if(this->aMesh[i][j].getNeigW() != NULL)
        {
//            std::cerr << " NeigW : " << *(this->aMesh[i][j].getNeigW()) << std::endl;
          // If the neighbour is not inside the domain Omega
          if(this->aMesh[i][j].getNeigW()->getLocality()<=0)
          {
            this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigW()))*lAlpha;
          }
          else
          {
            this->aMatrix.coeffRef(lIndex,lNeigW)=1*lAlpha;
          }
        }
        if(this->aMesh[i][j].getNeigE() != NULL)
        {
//            std::cerr << " NeigE : " << *(this->aMesh[i][j].getNeigE()) << std::endl;
          // If the neighbour is not inside the domain Omega
          if(this->aMesh[i][j].getNeigE()->getLocality()<=0)
          {
//            this->aG[lIndex] += -g(*(this->aMesh[i][j].getNeigE()));
            this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigE()))*lAlpha;
          }
          else
          {
            this->aMatrix.coeffRef(lIndex,lNeigE)=1*lAlpha;
          }
        }
        
        if(this->aMesh[i][j].getNeigN() != NULL)
        {
//            std::cerr << " NeigN : " << *(this->aMesh[i][j].getNeigN()) << std::endl;
          // If the neighbour is not inside the domain Omega
          if(this->aMesh[i][j].getNeigN()->getLocality()<=0)
          { 
            this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigN()))*lAlpha;
          }
          else
          {
            this->aMatrix.coeffRef(lIndex,lNeigN)=1*lAlpha;
          }
        }
        if(this->aMesh[i][j].getNeigS() != NULL)
        {
//            std::cerr << " NeigS : " << *(this->aMesh[i][j].getNeigS()) << std::endl;
          // If the neighbour is not inside the domain Omega
          if(this->aMesh[i][j].getNeigS()->getLocality()<=0)
          {
            this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigS()))*lAlpha;
          }
          else
          {
            this->aMatrix.coeffRef(lIndex,lNeigS)=1*lAlpha;
          }
        }
      } //  if(this->aBoundary.getBoundary(this->aMesh[i][j])>0)
      
      // if the point is on the boundary
      else if (this->aMesh[i][j].getBoundary()) 
      {
//        this->aMatrix.diagRowColumn(lIndex); // Imposer plutot dirichlet sur la solution tout à la fin
        this->aG(lIndex) += g(this->aMesh[i][j])*lAlpha;
//        std::cerr << this->aMesh[i][j] << " 1" << std::endl;
      }

    } // for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i))
  } // for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
}



/*!
*
* \fn void HyDiffusion2D<T>::build(double pTheta)
* \brief Fills the matrix A according to the theta method, and the vectors F and G
*
*/
template <typename T>
void HyDiffusion2D<T>::buildTheta(double pTheta)
{
  if(0< pTheta && pTheta <= 1)
  {
    unsigned long int lIndex = 0;
    unsigned long int lNeigW, lNeigE, lNeigN, lNeigS;
    double            lBound;
    bool              lIsOnBoundary=false;
    
    double            lDt = (this->aTmax)/(this->aNbTimeStep);
    double            lAlpha = (this->aK*lDt)/(this->aMesh.getHX()*this->aMesh.getHY());
    
    HyProblem<T>::updateMesh();
    
    for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
    {
      for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
      {
        lNeigW = 0;
        lNeigE = 0;
        lNeigN = 0;
        lNeigS = 0;

//        std::cerr << "KOKO2" << std::endl;
        // Index of the Xij in the matrix and vector
        lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;

        // Set if the point is in the domain omega and has at least one neigbour outside
        lIsOnBoundary=false;
        if(this->aMesh[i][j].getLocality()==-1)
        {
          this->aMesh[i][j].setBoundary(false);
        }
        else if(this->aMesh[i][j].getLocality()==1)
        {
          if(this->aMesh[i][j].getNeigW() != NULL)
            lIsOnBoundary |= (this->aMesh[i][j].getNeigW()->getLocality() == -1);
          if(this->aMesh[i][j].getNeigE() != NULL)
            lIsOnBoundary |= (this->aMesh[i][j].getNeigE()->getLocality() == -1);
          if(this->aMesh[i][j].getNeigN() != NULL)
            lIsOnBoundary |= (this->aMesh[i][j].getNeigN()->getLocality() == -1);
          if(this->aMesh[i][j].getNeigS() != NULL)
            lIsOnBoundary |= (this->aMesh[i][j].getNeigS()->getLocality() == -1);
          this->aMesh[i][j].setBoundary(lIsOnBoundary);
        }
        else if(this->aMesh[i][j].getLocality()==0)
          this->aMesh[i][j].setBoundary(true);
        
        

        
        // If the point is inside the domain (not in the boundary)
			  if(this->aMesh[i][j].getLocality() == 1)
        {
        
          // Filling F
          this->aF(lIndex) = f(this->aMesh[i][j])*lDt;
          
          this->aMatrix.coeffRef(lIndex,lIndex)    =1+4*lAlpha*pTheta;
          this->aMatrixB.coeffRef(lIndex,lIndex)  =1-4*lAlpha*(1-pTheta);

          
          // Indexes of the neighbours
          // -J-
          // Bottom
          if(j==0)
          {
            lNeigN=(j+1)*(this->aMesh.getNbRectanglesX()+1) + i;
          }
  //        
          // Top
          else if(j==this->aMesh.getNbRectanglesY())
          {
            lNeigS=(j-1)*(this->aMesh.getNbRectanglesX()+1) + i;
          }

          // Middle
          else
          {
            lNeigN=(j+1)*(this->aMesh.getNbRectanglesX()+1) + i;
            lNeigS=(j-1)*(this->aMesh.getNbRectanglesX()+1) + i;
          }

          // -I-
          // Left
          if(i==0)
          {
            lNeigE=j*(this->aMesh.getNbRectanglesX()+1) + i + 1;
          }

          // Right
          else if(i==this->aMesh.getNbRectanglesX())
          {
            lNeigW=j*(this->aMesh.getNbRectanglesX()+1) + i-1;
          }

          // Middle
          else
          {
            lNeigE=j*(this->aMesh.getNbRectanglesX()+1) + i + 1;
            lNeigW=j*(this->aMesh.getNbRectanglesX()+1) + i - 1;
          }
          
          // Check the neighbours
          if(this->aMesh[i][j].getNeigW() != NULL)
          {
  //            std::cerr << " NeigW : " << *(this->aMesh[i][j].getNeigW()) << std::endl;
            // If the neighbour is not inside the domain Omega
            if(this->aMesh[i][j].getNeigW()->getLocality()<=0)
            {
  //            this->aG[lIndex] += -g(*(this->aMesh[i][j].getNeigW()));
              this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigW()))*lAlpha; // VALUES OF aG MUST BE SET IN SOLVETHETA
            }
            else
            {
  //            this->aMatrix[lIndex][lNeigW]=1;
              this->aMatrix.coeffRef(lIndex,lNeigW)=1*lAlpha*pTheta;
              this->aMatrixB.coeffRef(lIndex,lNeigW)=lAlpha*(1-pTheta);
            }
          }
          if(this->aMesh[i][j].getNeigE() != NULL)
          {
  //            std::cerr << " NeigE : " << *(this->aMesh[i][j].getNeigE()) << std::endl;
            // If the neighbour is not inside the domain Omega
            if(this->aMesh[i][j].getNeigE()->getLocality()<=0)
            {
  //            this->aG[lIndex] += -g(*(this->aMesh[i][j].getNeigE()));
              this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigE()))*lAlpha;
            }
            else
            {
              this->aMatrix.coeffRef(lIndex,lNeigE)=1*lAlpha*pTheta;
              this->aMatrixB.coeffRef(lIndex,lNeigE)=lAlpha*(1-pTheta);;
            }
          }
          
          if(this->aMesh[i][j].getNeigN() != NULL)
          {
  //            std::cerr << " NeigN : " << *(this->aMesh[i][j].getNeigN()) << std::endl;
            // If the neighbour is not inside the domain Omega
            if(this->aMesh[i][j].getNeigN()->getLocality()<=0)
            { 
              this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigN()))*lAlpha;
            }
            else
            {
              this->aMatrix.coeffRef(lIndex,lNeigN)=1*lAlpha*pTheta;
              this->aMatrixB.coeffRef(lIndex,lNeigN)=lAlpha*(1-pTheta);;
            }
          }
          if(this->aMesh[i][j].getNeigS() != NULL)
          {
  //            std::cerr << " NeigS : " << *(this->aMesh[i][j].getNeigS()) << std::endl;
            // If the neighbour is not inside the domain Omega
            if(this->aMesh[i][j].getNeigS()->getLocality()<=0)
            {
              this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigS()))*lAlpha;
            }
            else
            {
              this->aMatrix.coeffRef(lIndex,lNeigS)=1*lAlpha*pTheta;
              this->aMatrixB.coeffRef(lIndex,lNeigS)=lAlpha*(1-pTheta);;
            }
          }
        } //  if(this->aBoundary.getBoundary(this->aMesh[i][j])>0)
        
        // if the point is on the boundary
        else if (this->aMesh[i][j].getBoundary()) 
        {
  //        this->aMatrix.diagRowColumn(lIndex); // Imposer plutot dirichlet sur la solution tout à la fin
          this->aG(lIndex) += g(this->aMesh[i][j])*lAlpha;
  //        std::cerr << this->aMesh[i][j] << " 1" << std::endl;
        }

      } // for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i))
    } // for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
  }
  else
    std::cerr << "ERROR in void HyDiffusion2D<T>::build(double pTheta) : theta is not between 0 (excluded) and 1 (included)." << std::endl;
}







//template <typename T>
//void HyDiffusion2D<T>::applySolution(unsigned long int t)
//{
//  std::cerr << "APPLY SOLUTION" << std::endl;
//  unsigned int lIndex = 0;
//  for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
//  {
//    for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
//    {
//      lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;
//      
//      if(this->aMesh[i][j].getLocality()==1)
//        this->aMesh[i][j].setZ(this->aEvolution[t](lIndex));
//      else if(this->aMesh[i][j].getLocality()==-1)
//        this->aMesh[i][j].setZ(0);
//      
//      if(this->aMesh[i][j].getBoundary())
//      {
//        this->aMesh[i][j].setZ(this->aG(lIndex));
////        std::cerr << aMesh[i][j] << " " << aG(lIndex) << std::endl;
//      }  
////        std::cerr << aMesh[i][j] << " " << aG(lIndex) << std::endl;
//    }
//  }
//}


/*!
*
* \fn void HyDiffusion2D<T>::displaySolutionGP(std::ostream & out, unsigned long int t)
* \brief Display the solution for gnuplot, using the pattern "X Y VALUE" (to display in 3D)
* \param out The ostream to write in
* \param t The time of evolution
*
*/

template <typename T>
void HyDiffusion2D<T>::displaySolutionGP(std::ostream & out, unsigned long int t)
{
//  std::cerr << "displaySolutionGP" << std::endl;
  unsigned int lIndex=0;
  for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
  {
    for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
    {
      lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;
      #if DISPLAY_WHOLE_MESH == 0
        if (this->aMesh[i][j].getLocality() == 1)
          out << this->aMesh[i][j] << " " << this->aEvolution[t](lIndex) << std::endl;
      #else
        out << this->aMesh[i][j] << " " << this->aEvolution[t](lIndex) << std::endl;
      #endif
    }
  }
  out << std::endl;
}


/*!
*
* \fn void HyDiffusion2D<T>::solve()
* \brief Solve the problem using the explicit method by default
*
*/

template <typename T>
void HyDiffusion2D<T>::solve()
{
  this->solveExplicit();
}



/*!
*
* \fn void HyDiffusion2D<T>::solveExplicit()
* \brief Solve the problem using the explicit method
*
*/

template <typename T>
void HyDiffusion2D<T>::solveExplicit()
{
  unsigned long int lIndex = 0;
  
  // Fill aEvolution with the initial condition
  for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
  {
    for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
    {
      lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;
      aEvolution[0](lIndex) = initialCondition(this->aMesh[i][j]);
    }
  }
  
  for(unsigned long int t=1;t<aTmax;++t)
  {
    this->aEvolution[t] = this->aEvolution[t-1] + this->aMatrix*this->aEvolution[t-1];
  }
  
  
//  
//  #if QUIET == 0
//    switch (lSolver.info())
//    {
//      case 0:
//        std::cout << " OK." << std::endl;
//        std::cout << " Number of iterations: " << lSolver.iterations() << std::endl;
//        std::cout << " Estimated error:      " << lSolver.error()      << std::endl;
//      break;
//      
//      case 1:
//        std::cout << " ERROR: The provided data did not satisfy the prerequisites." << std::endl;
//      break;
//      
//      case 2:
//        std::cout << " ERROR: Iterative procedure did not converge." << std::endl;
//      break;
//      
//      case 3:
//        std::cout << " ERROR: The inputs are invalid, or the algorithm has been improperly called. When assertions are enabled, such errors trigger an assert." << std::endl;
//      break;
//    
//    }
//    
//  #endif

}

/*!
*
* \fn void HyDiffusion2D<T>::solveImplicit()
* \brief Solve the problem using the implicit method
*
*/
template <typename T>
void HyDiffusion2D<T>::solveTheta()
{
  unsigned long int lIndex = 0;
  
  // Fill aEvolution with the initial condition
  for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
  {
    for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i)
    {
      lIndex=j*(this->aMesh.getNbRectanglesX()+1) + i;
      aEvolution[0](lIndex) = initialCondition(this->aMesh[i][j]);
    }
  }

  #if QUIET == 0
    std::cout << "Solving using BiCGSTAB method..." << std::endl;
  #endif
  BiCGSTAB<SparseMatrix<T> > lSolver(this->getMatrix());
  
  for(unsigned long int t=1;t<this->aNbTimeStep;++t)
  {
    
    this->aEvolution[t] = lSolver.solve(this->aMatrixB * this->aEvolution[t-1] + this->aF + this->aG);
    #if QUIET == 0
      std::cout << " Step " << t << "...";
      switch (lSolver.info())
      {
        case 0:
          std::cout << " OK. (Number of iterations: " << lSolver.iterations() << ", Estimated error: " << lSolver.error() << ")" << std::endl;
        break;
        
        case 1:
          std::cout << " ERROR: The provided data did not satisfy the prerequisites." << std::endl;
        break;
        
        case 2:
          std::cout << " ERROR: Iterative procedure did not converge." << std::endl;
        break;
        
        case 3:
          std::cout << " ERROR: The inputs are invalid, or the algorithm has been improperly called. When assertions are enabled, such errors trigger an assert." << std::endl;
        break;
        
        default:
          std::cout << "???" << std::endl;
        break;
      }
    #endif
  }

}

/*!
*
* \fn double HyDiffusion2D<T>::g(HyPoint<T> pPoint)
* \brief Dirichlet condition
* \param pPoint The point to evaluate
* \return The value of the Dirichlet condition for the given point
*
*/
template <typename T>
double HyDiffusion2D<T>::g(HyPoint<T> pPoint)
{
	return g(pPoint.getX(),pPoint.getY(),pPoint.getZ());
}


/*!
*
* \fn double HyDiffusion2D<T>::g(T pX, T pY, T pZ)
* \brief Dirichlet condition
* \param pX, pY, pZ The coordinates of evaluation
* \return The value of the Dirichlet condition for the given point (pX,pY,pZ)
*
*/
template <typename T>
double HyDiffusion2D<T>::g(T pX, T pY, T pZ)
{
  double res=0;
	return res;
}

/*!
*
* \fn double HyDiffusion2D<T>::f(HyPoint<T> pPoint)
* \brief The function f of the Diffusion equation
* \param pPoint The point of evaluation
* \return The value of f(pPoint)
*
*/
template <typename T>
double HyDiffusion2D<T>::f(HyPoint<T> pPoint)
{
	return f(pPoint.getX(),pPoint.getY());
}


/*!
*
* \fn double HyDiffusion2D<T>::f(T pX, T pY)
* \brief The function f of the Diffusion equation
* \param pX,pY The coordinate of evaluation
* \return The value of f(pX,pY)
*
*/
template <typename T>
double HyDiffusion2D<T>::f(T pX, T pY)
{
	return 0;
}


/*!
*
* \fn double HyDiffusion2D<T>::initialCondition(HyPoint<T> pPoint)
* \brief The initial condition
* \param pPoint The point of evaluation
* \return The value of f(pPoint)
*
*/
template <typename T>
double HyDiffusion2D<T>::initialCondition(HyPoint<T> pPoint)
{
  return initialCondition(pPoint.getX(),pPoint.getY());
}



/*!
*
* \fn double HyDiffusion2D<T>::initialCondition(T pX, T pY)
* \brief The initial condition
* \param pX,pY The coordinate of evaluation
* \return The value of f(pX,pY)
*
*/
template <typename T>
double HyDiffusion2D<T>::initialCondition(T pX, T pY)
{
  double res=0;
  res = 1.5*exp(-((pX-10)*(pX-10) + (pY-10)*(pY-10)));
  return res;
}







