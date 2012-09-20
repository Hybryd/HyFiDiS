/// \file   HyPoisson2D.ipp
/// \brief  Template file of HyPoisson2D class.

///
/// \fn HyPoisson2D<T>::HyPoisson2D()
/// \brief Default constructor
///
template <typename T>
HyPoisson2D<T>::HyPoisson2D()
{
}

///
/// \fn HyPoisson2D<T>::HyPoisson2D(HyBoundary2D<T> & pBoundary, std::string & pDescription, HyMesh2D<T> & pMesh)
/// \brief Constructor. Initializes the matrix and the vectors
/// \param pBoundary Boundary of the domain
/// \param pDescription Description of the problem
/// \param pMesh Mesh of the domain
///
template <typename T>
HyPoisson2D<T>::HyPoisson2D(  HyDomain<T> & pDomain,
                              HyBoundary<T> & pBoundary,
                              HyMesh2D<T> & pMesh,
                              std::string & pDescription
                           ) : HyProblem<T>(pDomain,pBoundary,pMesh,pDescription)
{
  build();
}




///
/// \fn void HyPoisson2D<T>::build()
/// \brief Fills the matrix A and the vectors F and G
///
template <typename T>
void HyPoisson2D<T>::build()
{

  unsigned long int lIndex = 0;
  unsigned long int lNeigW, lNeigE, lNeigN, lNeigS;
  double            lBound;
  bool              lIsOnBoundary=false;
  
  
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
      
      

//      std::cerr << "Point : (" << lIndex << ", " << this->aMesh[i][j].getLocality() << "," << this->aMesh[i][j].getBoundary() << ") : " << this->aMesh[i][j] << std::endl;      
      
      // If the point is inside the domain (not in the boundary)
			if(this->aMesh[i][j].getLocality() == 1)
      {
//        std::cerr << this->aMesh[i][j] << " 1" << std::endl;      
      
        // Filling F
        this->aF(lIndex) = f(this->aMesh[i][j]);
        this->aMatrix.coeffRef(lIndex,lIndex)=-4;
//        this->aF[lIndex] = f(this->aMesh[i][j]);
//        this->aMatrix[lIndex][lIndex]=-4;
        
        
        // Indexes of the neighbours
        // -J-
        // Bottom
        if(j==0)
        {
//          lExistsS = false;
//          if(this->aMesh[i][j].getLocality() != this->aMesh[i][j+1].getLocality())
//          	lOutS = true;
//////          std::cout << "  (j==0) " << std::endl;
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
            this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigW()));
          }
          else
          {
//            this->aMatrix[lIndex][lNeigW]=1;
            this->aMatrix.coeffRef(lIndex,lNeigW)=1;
          }
        }
        if(this->aMesh[i][j].getNeigE() != NULL)
        {
//            std::cerr << " NeigE : " << *(this->aMesh[i][j].getNeigE()) << std::endl;
          // If the neighbour is not inside the domain Omega
          if(this->aMesh[i][j].getNeigE()->getLocality()<=0)
          {
//            this->aG[lIndex] += -g(*(this->aMesh[i][j].getNeigE()));
            this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigE()));
          }
          else
          {
            this->aMatrix.coeffRef(lIndex,lNeigE)=1;
          }
        }
        
        if(this->aMesh[i][j].getNeigN() != NULL)
        {
//            std::cerr << " NeigN : " << *(this->aMesh[i][j].getNeigN()) << std::endl;
          // If the neighbour is not inside the domain Omega
          if(this->aMesh[i][j].getNeigN()->getLocality()<=0)
          { 
            this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigN()));
          }
          else
          {
            this->aMatrix.coeffRef(lIndex,lNeigN)=1;
          }
        }
        if(this->aMesh[i][j].getNeigS() != NULL)
        {
//            std::cerr << " NeigS : " << *(this->aMesh[i][j].getNeigS()) << std::endl;
          // If the neighbour is not inside the domain Omega
          if(this->aMesh[i][j].getNeigS()->getLocality()<=0)
          {
            this->aG(lIndex) += -g(*(this->aMesh[i][j].getNeigS()));
          }
          else
          {
            this->aMatrix.coeffRef(lIndex,lNeigS)=1;
          }
        }
      } //  if(this->aBoundary.getBoundary(this->aMesh[i][j])>0)
      
      // if the point is on the boundary
      else if (this->aMesh[i][j].getBoundary()) 
      {
//        this->aMatrix.diagRowColumn(lIndex); // Imposer plutot dirichlet sur la solution tout à la fin
        this->aG(lIndex) += g(this->aMesh[i][j]);
//        std::cerr << this->aMesh[i][j] << " 1" << std::endl;
      }

    } // for(unsigned int i=0;i<=this->aMesh.getNbRectanglesX();++i))
  } // for(unsigned int j=0;j<=this->aMesh.getNbRectanglesY();++j)
}


/////
///// \fn void HyPoisson2D<T>::projectionOnGamma(HyPoint<T> & pPointIn, HyPoint<T> & pPointOut, double * ph, double * pu)
///// \brief Finds the intersection between [pPointIn,pPointOut] and the boundary
///// \param pPointIn The point in OmegaIn
///// \param pPointOut The point in OmegaOut
///// \param ph Will be the value of the partial h (between 0 and 1)
///// \param pu Will be the value of g in the projection point
/////
//template <typename T>
//void HyPoisson2D<T>::projectionOnGamma(HyPoint<T> & pPointIn, HyPoint<T> & pPointOut, double * ph, double * pu)
//{
//	// Check if pIn is in Omega and pOut out of Omega
//	if(this->aBoundary.getBoundary(pPointIn) > 0 && this->aBoundary.getBoundary(pPointOut) <= 0)
//	{
//		double lIn,lOut,lMid;
//		// if pIn and pOut have the same ordonate
//		if(pPointIn.getY() == pPointOut.getY())
//		{
//			double lY		= pPointIn.getY();
//			lIn					= pPointIn.getX();
//			lOut				= pPointOut.getX();
//			lMid				= (lIn+lOut)/2;

//			while(fabs(lIn-lOut) > EPSILON)
//			{
//				if(this->aBoundary.getBoundary(lMid,lY) > 0) // P is in Omega
//					lIn = lMid;
//				else
//					lOut = lMid;
//				lMid = (lIn+lOut)/2;
//			}
//			
//			std::cout << "ph : " << *ph << std::endl;
//			*ph = this->aMesh.getH()*(fabs(lMid-pPointIn.getX())/fabs(pPointOut.getX()-pPointIn.getX()));
//			std::cout << "ph : " << *ph << std::endl;
//			*pu = g(lMid,lY);
//		}
//		// if pIn and pOut have the same abscissa
//		else
//		{
//			double lX		= pPointIn.getX();
//			lIn					= pPointIn.getY();
//			lOut				= pPointOut.getY();
//			lMid				= (lIn+lOut)/2;
//			
//			while(fabs(lIn-lOut) > EPSILON)
//			{
//				if(this->aBoundary.getBoundary(lX,lMid) > 0) // P is in Omega
//					lIn = lMid;
//				else
//					lOut = lMid;
//				lMid = (lIn+lOut)/2;
//			}
//			
//			std::cout << "ph : " << *ph << std::endl;
//			*ph = this->aMesh.getH()*(fabs(lMid-pPointIn.getY())/fabs(pPointOut.getY()-pPointIn.getY()));
//			std::cout << "ph : " << *ph << std::endl;
//			*pu = g(lX,lMid);
//		}
//	}
//	else
//	{
//		std::cerr << "ERROR in projectionOnGamma(HyPoint<T> pIn, HyPoint<T> pOut, double * ph, double * pu) : " << std::endl;
//		std::cerr << " pIn = " << pPointIn << "(" << this->aBoundary.getBoundary(pPointIn) << ")     pOut = " << pPointOut << "(" << this->aBoundary.getBoundary(pPointOut) << ")" << std::endl;
//    std::cerr << "   pIn is not in Omega or pOut is not out of Omega" << std::endl;
//	}
//}


//template <typename T>
//double HyPoisson2D<T>::g(T pX, T pY, T pZ)
//{

//  return 0;
//}

template <typename T>
void HyPoisson2D<T>::solve()
{
  #if QUIET == 0
    std::cout << "Solving using BiCGSTAB method...";
  #endif
  BiCGSTAB<SparseMatrix<T> > lSolver(this->getMatrix());
  this->setX(lSolver.solve(this->getF() + this->getG()));
  #if QUIET == 0
    switch (lSolver.info())
    {
      case 0:
        std::cout << " OK." << std::endl;
        std::cout << " Number of iterations: " << lSolver.iterations() << std::endl;
        std::cout << " Estimated error:      " << lSolver.error()      << std::endl;
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
    
    }
    
  #endif
}


template <typename T>
double HyPoisson2D<T>::g(HyPoint<T> pPoint)
{
	return g(pPoint.getX(),pPoint.getY(),pPoint.getZ());
}


///
/// \fn double HyProblem<T>::g(T pX, T pY)
/// \brief The Dirichlet condition on the boundary
/// \param pX, pY, pZ The coordinates of evaluation
/// \return The value of the Dirichlet condition on the point (pX,pY,pZ)
///
template <typename T>
double HyPoisson2D<T>::g(T pX, T pY, T pZ)
{
  double res=0;
//  if(pX == 20 && pY >= 0 && pY <= 10)
//    res = 100;
//  else if(pX == 0 && pY >= 0 && pY <= 10)
//    res = 30;
//  else
//    res = 60;
//  res = pX + pY;
  
//  if(pY==0 && pX>=0 && pX <=20)
//    res = -50*sin(PI*pX/20);
//  if(pY==10 && pX>=0 && pX <=20)
//    res = -100*sin(PI*pX/10);
//    
//  if(pX==0 && pY>=0 && pY <=10)
//    res = 400*sin(PI*pY/10);
//  if(pX==20 && pY>=0 && pY <=10)
//    res = 100*sin(PI*pY/2.5);
//  
  
////  if(pY==0 && pX>=0 && pX <=10)
////    res = 500*pX;
////  if(pY==0 && pX>=10 && pX <=20)
////    res = 500*(20-pX);
////  if(pY==10 && pX>=0 && pX <=10)
////    res = res = 500*pX;//0;//-100*sin(PI*pX/10);
////  if(pY==10 && pX>=10 && pX <=20)  
////    res = 500*(20-pX);
////    
////    
////  if(pX==0 && pY>=0 && pY <=10)
////    res = 0;//400*sin(PI*pY/10);
////  if(pX==20 && pY>=0 && pY <=10)
////    res = 0;//100*sin(PI*pY/2.5);
  res = pX*pY;
	return res;
}





/*												  				  */
/*	f, 2nd part of Poisson's equation */
/*  																  */
///
/// \fn double HyPoisson2D<T>::f(HyPoint<T> pPoint)
/// \brief The function f
/// \param pPoint The point of evaluation
/// \return The value of f(pPoint)
///
template <typename T>
double HyPoisson2D<T>::f(HyPoint<T> pPoint)
{
	return f(pPoint.getX(),pPoint.getY());
}


///
/// \fn double HyPoisson2D<T>::f(T pX, T pY)
/// \brief The function f
/// \param pX,pY The coordinate of evaluation
/// \return The value of f(pX,pY)
///
template <typename T>
double HyPoisson2D<T>::f(T pX, T pY)
{
	return 0;
}





