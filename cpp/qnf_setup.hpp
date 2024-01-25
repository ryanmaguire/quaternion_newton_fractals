/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of quaternion_newton_fractals.                          *
 *                                                                            *
 *  quaternion_newton_fractals is free software: you can redistribute it      *
 *  and/or modify it under the terms of the GNU General Public License as     *
 *  published by the Free Software Foundation, either version 3 of the        *
 *  License, or (at your option) any later version.                           *
 *                                                                            *
 *  quaternion_newton_fractals is distributed in the hope that it will be     *
 *  useful but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with quaternion_newton_fractals.  If not, see                       *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the basic setup parameters for the images.                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2024/01/25                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef QNF_SETUP_HPP
#define QNF_SETUP_HPP

/*  Namespace for the project. "Quaternion Newton Fractal."                   */
namespace qnf {

    /*  Another namespace to avoid name conflicts with these constants.       */
    namespace setup {

        /*  The starting and ending widths and heights for the image.         */
        static const double start = -3.0;
        static const double end = 3.0;

        /*  Number of pixels in the x and y axes.                             */
        static const unsigned int xsize = 1024U;
        static const unsigned int ysize = 1024U;

        /*  Factor used for converting from pixels to points in space.        */
        static const double pxfact = 5.8651026392961877E-03;
        static const double pyfact = 5.8651026392961877E-03;

        /*  Maximum number of iterations allowed in Newton's method.          */
        static const unsigned int max_iters = 32U;
    }
    /*  End of "setup" namespace.                                             */
}
/*  End of "qnf" namespace.                                                   */

#endif
/*  End of include guard.                                                     */
