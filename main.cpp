/// \file   main.cpp
/// \author Hybryd-
///
/// Numerical resolution of PDE using finite difference method



#include <iostream>
#include <fstream>
#include <sstream>



//#include "HyBoundary2D.hpp"
//#include "HyDomain2D.hpp"
//#include "HyMatrix.hpp"
#include "HyMesh2D.hpp"
#include "HyPoint.hpp"
#include "HyPoisson2D.hpp"
#include "HySolver.hpp"
#include "HyDiffusion2D.hpp"
#include "HyPlotter.hpp"

#include "HyCircle.hpp"
#include "HyRectangle.hpp"

int main(int argc, char ** argv)
{

  int     lNbPointsX = 40;
  int     lNbPointsY = 60;
  double  lBLX = 0;
  double  lBLY = 0;
  double  lBLZ = 0;
  double  lURX = 0;
  double  lURY = 0;
  double  lURZ = 0;
  double  lRectBLX = 0;
  double  lRectBLY = 0;
  double  lRectURX = 0;
  double  lRectURY = 0;
  double  lCircX   = 0;
  double  lCircY   = 0;
  double  lRadius = 0;
  HyPoint<double> lCenter,lRectBL, lRectUR;
  
  HyCircle<double>    lCirc;
  HyRectangle<double> lRect;
  
  
  
  if(argc > 2)
  {
    std::fstream input(argv[1],std::ios::in);
//    std::fstream output(argv[2],std::ios::out);
    
    
    if(input)
    {
      std::string line;
      std::string keyword;
      std::string lBoundaryType;
      std::stringstream sline;
      bool read_header = true;
      HyPoint<double> lBL,lUR;
      
      
      ////////////////////////////////////////////////////////////////////
      // Reads the header
      ////////////////////////////////////////////////////////////////////
      
      #if QUIET == 0
        std::cout << std::endl << "Details of the problem:" << std::endl;
      #endif
      while(read_header && getline(input,line))
      {
        if(line != "") // avoids empty lines
        {
          sline.clear();
          sline.str("");
          sline << line;
          sline >> keyword;
          // Parser
          if(keyword[0] == '#')
          {
            if      (keyword == "#NBX")
            {
              sline >> lNbPointsX;
              #if QUIET == 0
                std::cout << " Number of points on X-axis: " << lNbPointsX << std::endl;
              #endif
            }
            else if (keyword == "#NBY")
            {
              sline >> lNbPointsY;
              #if QUIET == 0
                std::cout << " Number of points on Y-axis: " << lNbPointsY << std::endl;
              #endif
            }
            else if (keyword == "#DOMAIN_BOTTOM_LEFT")
            {
              sline >> lBLX >> lBLY >> lBLZ;
              lBL.setX(lBLX);
              lBL.setY(lBLY);
              lBL.setZ(lBLZ);
              #if QUIET == 0
                std::cout << " Bottom-left point: " << lBL << std::endl;
              #endif
            }
            else if (keyword == "#DOMAIN_UPPER_RIGHT")
            {
              sline >> lURX >> lURY >> lURZ;
              lUR.setX(lURX);
              lUR.setY(lURY);
              lUR.setZ(lURZ);
              #if QUIET == 0
                std::cout << " Upper-right point: " << lUR << std::endl;
              #endif
            }
            else if (keyword == "#BOUNDARY")
            {
              sline >> keyword;
              if(keyword == "CIRCLE")
              {
                lBoundaryType = "CIRCLE";
                sline >> lCircX >> lCircY >> lRadius;
                lCenter.setX(lCircX);
                lCenter.setY(lCircY);
                lCirc.setCenter(lCenter);
                lCirc.setRadius(lRadius);
                #if QUIET == 0
                  std::cout << " Type of boundary: Circle (" << lCirc << ")" << std::endl;
                #endif
              }
              else if (keyword == "RECTANGLE")
              {
                lBoundaryType = "RECTANGLE";
                sline >> lRectBLX >> lRectBLY >> lRectURX >> lRectURY;
                lRectBL.setX(lRectBLX);
                lRectBL.setY(lRectBLY);
                lRectUR.setX(lRectURX);
                lRectUR.setY(lRectURY);
                lRect.setBL(lRectBL);
                lRect.setUR(lRectUR);
                #if QUIET == 0
                  std::cout << " Type of boundary: Rectangle (" << lRect << ")" << std::endl;
                #endif
              }
            }
          }
          else
          {
            //
          }
        } // (line != "")
      } // while(read_header && getline(file,line))
    
      
      
      
      HyDomain<double>      lDomain(lBL,lUR);
      HyMesh2D<double>      lMesh(lBL,lUR,lNbPointsX,lNbPointsY);
      std::string           lDescProb="Problem 1";
      HySolver<double>      lSolver;

      std::cout << std::endl;
      
      
      std::cout << "Building the problem..." << std::endl;
      HyDiffusion2D<double> lProb(lDomain,lRect,lMesh,lDescProb,20,20,0.001);
      lProb.buildTheta(0.5);
      lProb.solveTheta();
      
      
      std::cout << "Writing data in files..." << std::endl;
      HyPlotter<double> lPlotter(lMesh,lProb.getEvolution(),argv[2]);
      lPlotter.save("data");
      
//      if(lBoundaryType == "CIRCLE")                 // TRES SALE... A REVOIR
//      {
//        HyPoisson2D<double>   lProb(lDomain,lCirc,lMesh,lDescProb);
//        //lSolver.withBiCGSTAB(lProb);
//        lProb.solve();
//        lProb.applySolution();
//        std::cout << "Writing data in output file..." << std::endl;
//        lProb.displaySolutionGP(output);
//      }
//      else if(lBoundaryType == "RECTANGLE")
//      {
//        HyPoisson2D<double>   lProb(lDomain,lRect,lMesh, lDescProb);
//        lProb.solve();
////        lSolver.withBiCGSTAB(lProb);
//        lProb.applySolution();
//        std::cout << "Writing data in output file..." << std::endl;
//        lProb.displaySolutionGP(output);
//      }

      std::cout << std::endl;

      input.close();
//      output.close();
    } // if(file)
    else
      std::cerr << "Error reading input file" << std::endl;
  }
  else
    std::cerr << "Usage : ./main param files_prefix" << std::endl;
  
  return 0;
}


