#ifndef VARIABLES_HPP
#define VARIABLES_HPP

/*!
* \file   Variables.hpp
* \brief  List of all macros and parameters
*
* \param DISPLAY_MESH_GRID_STYLE  If the value is 1, displays the mesh like a grid in the terminal, with dots at each node.
* \param DISPLAY_WHOLE_MESH       If the value is 1, displays the whole mesh (as a set of points). If 0, it only displays the domain defined by the HyBoundary. It avoids displaying useless points outside the interesting domain.
* \param HY_EPSILON               Arbitrary precision, used in the code of this library only.
* \param HY_PI                    Approximation of the most beautiful number of all the universe.
* \param QUIET                    If the value is 1, does not display any additionnal information like details of the problem or of the computation.
*
*/


#define DISPLAY_MESH_GRID_STYLE 1
#define DISPLAY_WHOLE_MESH      0
#define HY_EPSILON              0.000001
#define HY_PI                   3.1415926535
#define QUIET                   0



#endif
