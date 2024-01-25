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
 *      Provides a struct for using colors.                                   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/02/28                                                        *
 ******************************************************************************/

/* Include guard to prevent including this file twice.                        */
#ifndef QNF_PPM_HPP
#define QNF_PPM_HPP

/*  Basic constants for the setup of the experiments given here.              */
#include "qnf_setup.hpp"

/*  File data type found here.                                                */
#include <cstdio>

/*  Namespace for the project. "Quaternion Newton Fractal."                   */
namespace qnf {

    /*  Struct for working with PPM files.                                    */
    struct ppm {

        /*  The "data" of the PPM is just a FILE pointer.                     */
        FILE *fp;

        /*  Constructor from a name, the name of the file.                    */
        ppm(const char *name);

        /*  Method for initializing the PPM using arbitrary values.           */
        inline void init(unsigned int x, unsigned int y, int type);

        /*  Method for initializing the PPM using the values in "setup".      */
        inline void init(void);

        /*  Method for closing the file pointer for the PPM.                  */
        inline void close(void);
    };

    /**************************************************************************
     *  Constructor:                                                          *
     *      ppm                                                               *
     *  Purpose:                                                              *
     *      Creates a PPM file with a given file name.                        *
     *  Arguments:                                                            *
     *      name (const char *):                                              *
     *          The file name of the output PPM (ex. "fractal.ppm").          *
     *  Outputs:                                                              *
     *      PPM (qnf::ppm):                                                   *
     *          A PPM struct whose FILE pointer points to a ppm file that has *
     *          been given write permissions.                                 *
     *  Notes:                                                                *
     *      fopen returns NULL on failure. This function will print a warning *
     *      if fopen fails. It is the callers responsibility to inspect the   *
     *      FILE pointer before trying to use it.                             *
     **************************************************************************/
    ppm::ppm(const char *name)
    {
        fp = std::fopen(name, "w");

        /*  Warn the caller is fopen failed.                                  */
        if (!fp)
            std::puts("ERROR: fopen failed and returned NULL.");
    }

    /**************************************************************************
     *  Method:                                                               *
     *      init                                                              *
     *  Purpose:                                                              *
     *      Print the preamble to the PPM file. A PPM file wants Pn followed  *
     *      by three numbers. P6 means we're encoding an RGB image in binary  *
     *      format. The first two numbers are the number of pixels in the x   *
     *      and y axes. The last number is the size of our color spectrum,    *
     *      which is 255.                                                     *
     *  Arguments:                                                            *
     *      x (unsigned int):                                                 *
     *          The number of pixels in the x axis.                           *
     *      y (unsigned int):                                                 *
     *          The number of pixels in the y axis.                           *
     *      type (int):                                                       *
     *          The type of the PPM, options are 1 through 6.                 *
     *  Outputs:                                                              *
     *      None (void).                                                      *
     **************************************************************************/
    inline void ppm::init(unsigned int x, unsigned int y, int type)
    {
        switch (type)
        {
            case 1:
                std::fprintf(fp, "P1\n%u %u\n255\n", x, y);
                return;
            case 2:
                std::fprintf(fp, "P2\n%u %u\n255\n", x, y);
                return;
            case 3:
                std::fprintf(fp, "P3\n%u %u\n255\n", x, y);
                return;
            case 4:
                std::fprintf(fp, "P4\n%u %u\n255\n", x, y);
                return;
            case 5:
                std::fprintf(fp, "P5\n%u %u\n255\n", x, y);
                return;
            default:
                std::fprintf(fp, "P6\n%u %u\n255\n", x, y);
        }
    }


    /**************************************************************************
     *  Method:                                                               *
     *      init                                                              *
     *  Purpose:                                                              *
     *      Initialize a PPM using the values in "setup".                     *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Outputs:                                                              *
     *      None (void).                                                      *
     *  Method:                                                               *
     *      Pass the default parameters to the other init function.           *
     **************************************************************************/
    inline void ppm::init(void)
    {
        init(qnf::setup::xsize, qnf::setup::ysize, 6);
    }

    /**************************************************************************
     *  Function:                                                             *
     *      close                                                             *
     *  Purpose:                                                              *
     *      Closes the file pointer in a PPM struct.                          *
     *  Arguments:                                                            *
     *      None (void).                                                      *
     *  Outputs:                                                              *
     *      None (void).                                                      *
     **************************************************************************/
    inline void ppm::close(void)
    {
        /*  Ensure the pointer is not NULL before trying to close it.         */
        if (!fp)
            return;

        std::fclose(fp);
    }
}
/*  End of namespace qnf.                                                     */

#endif
/*  End of include guard.                                                     */
