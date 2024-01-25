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
 *  Date:   2024/01/25                                                        *
 ******************************************************************************/

/* Include guard to prevent including this file twice.                        */
#ifndef QNF_COLOR_HPP
#define QNF_COLOR_HPP

/*  Multiples of pi defined here. Used for the color wheel routine.           */
#include "qnf_pi.hpp"

/*  Struct for working with PPM files found here.                             */
#include "qnf_ppm.hpp"

/*  File data type found here.                                                */
#include <cstdio>

/*  Namespace for the project. "Quaternion Newton Fractal."                   */
namespace qnf {

    /*  Simple struct for working with colors in a PPM file.                  */
    struct color {

        /*  A color is given by its RGB values.                               */
        unsigned char red, green, blue;

        /*  Empty constructor.                                                */
        color(void);

        /**********************************************************************
         *  Constructor:                                                      *
         *      qnf::color                                                    *
         *  Purpose:                                                          *
         *      Creates a color struct from three unsigned values.            *
         *  Arguments:                                                        *
         *      r (unsigned char):                                            *
         *          The red component of the color.                           *
         *      g (unsigned char):                                            *
         *          The green component of the color.                         *
         *      b (unsigned char):                                            *
         *          The blue component of the color.                          *
         *  Outputs:                                                          *
         *      c (qnf::color):                                               *
         *          The color (r, g, b) in 24-bit RGB color space.            *
         **********************************************************************/
        color(unsigned char r, unsigned char g, unsigned char b);

        /**********************************************************************
         *  Method:                                                           *
         *      qnf::write                                                    *
         *  Purpose:                                                          *
         *      Writes a color to a FILE.                                     *
         *  Arguments:                                                        *
         *      fp (FILE *):                                                  *
         *          A pointer to a file, the file the color is written to.    *
         *  Outputs:                                                          *
         *      None (void).                                                  *
         **********************************************************************/
        inline void write(FILE *fp) const;

        /**********************************************************************
         *  Method:                                                           *
         *      qnf::write                                                    *
         *  Purpose:                                                          *
         *      Writes a color to a PPM file.                                 *
         *  Arguments:                                                        *
         *      PPM (qnf::ppm &):                                             *
         *          A reference to a PPM file that has been initialized.      *
         *  Outputs:                                                          *
         *      None (void).                                                  *
         **********************************************************************/
        inline void write(qnf::ppm &PPM) const;

        /**********************************************************************
         *  Operator:                                                         *
         *      *                                                             *
         *  Purpose:                                                          *
         *      Scales the intensity of a color by a real number.             *
         *  Arguments:                                                        *
         *      t (double):                                                   *
         *          A real number, usually between 0 an 1.                    *
         *  Outputs:                                                          *
         *      tc (qnf::color).                                              *
         *          The color *this* with each color channel scaled by t.     *
         **********************************************************************/
        inline color operator * (double t) const;

        /**********************************************************************
         *  Operator:                                                         *
         *      *=                                                            *
         *  Purpose:                                                          *
         *      Scales the intensity of a color by a real number.             *
         *  Arguments:                                                        *
         *      t (double):                                                   *
         *          A real number, usually between 0 an 1.                    *
         *  Outputs:                                                          *
         *      None (void).                                                  *
         **********************************************************************/
        inline void operator *= (double t);

        /**********************************************************************
         *  Operator:                                                         *
         *      +                                                             *
         *  Purpose:                                                          *
         *      Mixes two colors together by averaging over their components. *
         *  Arguments:                                                        *
         *      c (const qnf::color &c):                                      *
         *          A color.                                                  *
         *  Outputs:                                                          *
         *      mix (qnf::color).                                             *
         *          The average of the color c and *this*.                    *
         **********************************************************************/
        inline color operator + (const qnf::color &c) const;

        /**********************************************************************
         *  Operator:                                                         *
         *      +=                                                            *
         *  Purpose:                                                          *
         *      Mixes two colors together by averaging over their components. *
         *  Arguments:                                                        *
         *      c (const qnf::color &c):                                      *
         *          A color.                                                  *
         *  Outputs:                                                          *
         *      None (void).                                                  *
         **********************************************************************/
        inline void operator += (const qnf::color &c);
    };

    /*  Empty constructor, just return.                                       */
    color::color(void)
    {
        return;
    }

    /**************************************************************************
     *  Constructor:                                                          *
     *      qnf::color                                                        *
     *  Purpose:                                                              *
     *      Creates a color struct from three unsigned values.                *
     *  Arguments:                                                            *
     *      r (unsigned char):                                                *
     *          The red component of the color.                               *
     *      g (unsigned char):                                                *
     *          The green component of the color.                             *
     *      b (unsigned char):                                                *
     *          The blue component of the color.                              *
     *  Outputs:                                                              *
     *      c (qnf::color):                                                   *
     *          The color (r, g, b) in 24-bit RGB color space.                *
     **************************************************************************/
    color::color(unsigned char r, unsigned char g, unsigned char b)
    {
        red = r;
        green = g;
        blue = b;
    }

    /**************************************************************************
     *  Method:                                                               *
     *      qnf::write                                                        *
     *  Purpose:                                                              *
     *      Writes a color to a FILE.                                         *
     *  Arguments:                                                            *
     *      fp (FILE *):                                                      *
     *          A pointer to a file, the file the color is written to.        *
     *  Outputs:                                                              *
     *      None (void).                                                      *
     **************************************************************************/
    inline void color::write(FILE *fp) const
    {
        std::fputc(int(red), fp);
        std::fputc(int(green), fp);
        std::fputc(int(blue), fp);
    }

    /**************************************************************************
     *  Method:                                                               *
     *      qnf::write                                                        *
     *  Purpose:                                                              *
     *      Writes a color to a PPM file.                                     *
     *  Arguments:                                                            *
     *      PPM (qnf::ppm &):                                                 *
     *          A reference to a PPM file that has been initialized.          *
     *  Outputs:                                                              *
     *      None (void).                                                      *
     **************************************************************************/
    inline void color::write(qnf::ppm &PPM) const
    {
        write(PPM.fp);
    }

    /**************************************************************************
     *  Operator:                                                             *
     *      *                                                                 *
     *  Purpose:                                                              *
     *      Scales the intensity of a color by a real number.                 *
     *  Arguments:                                                            *
     *      t (double):                                                       *
     *          A real number, usually between 0 an 1.                        *
     *  Outputs:                                                              *
     *      tc (qnf::color).                                                  *
     *          The color *this* with each color channel scaled by t.         *
     *  Method:                                                               *
     *      Scale each color channel by t and then cast to unsigned char.     *
     *  Notes:                                                                *
     *      No checks for overflow are performed. Large or negative values of *
     *      t may yield unexpected results.                                   *
     **************************************************************************/
    inline color color::operator * (double t) const
    {
        const unsigned char r = static_cast<unsigned char>(t*red);
        const unsigned char g = static_cast<unsigned char>(t*green);
        const unsigned char b = static_cast<unsigned char>(t*blue);
        return color(r, g, b);
    }

    /**************************************************************************
     *  Operator:                                                             *
     *      *=                                                                *
     *  Purpose:                                                              *
     *      Scales the intensity of a color by a real number.                 *
     *  Arguments:                                                            *
     *      t (double):                                                       *
     *          A real number, usually between 0 an 1.                        *
     *  Outputs:                                                              *
     *      None (void).                                                      *
     *  Method:                                                               *
     *      Scale each color channel by t and then cast to unsigned char. The *
     *      end result is then stored in *this*.                              *
     *  Notes:                                                                *
     *      No checks for overflow are performed. Large or negative values of *
     *      t may yield unexpected results.                                   *
     **************************************************************************/
    inline void color::operator *= (double t)
    {
        red = static_cast<unsigned char>(t*red);
        green = static_cast<unsigned char>(t*green);
        blue = static_cast<unsigned char>(t*blue);
    }

    /**************************************************************************
     *  Operator:                                                             *
     *      +                                                                 *
     *  Purpose:                                                              *
     *      Mixes two colors together by averaging over their components.     *
     *  Arguments:                                                            *
     *      c (const qnf::color &c):                                          *
     *          A color.                                                      *
     *  Outputs:                                                              *
     *      mix (qnf::color).                                                 *
     *          The average of the color c and *this*.                        *
     *  Method:                                                               *
     *      Cast each channel to double to avoid overflow. Then average       *
     *      the values together and cast back to unsigned char.               *
     **************************************************************************/
    inline color color::operator + (const qnf::color &c) const
    {
        /*  Cast the values to doubles and take the average, component-wise.  */
        const double x = 0.5 * (double(red) + double(c.red));
        const double y = 0.5 * (double(green) + double(c.green));
        const double z = 0.5 * (double(blue) + double(c.blue));

        /*  Cast the double back to unsigned char's and return.               */
        const unsigned char r = static_cast<unsigned char>(x);
        const unsigned char g = static_cast<unsigned char>(y);
        const unsigned char b = static_cast<unsigned char>(z);
        return color(r, g, b);
    }

    /**************************************************************************
     *  Operator:                                                             *
     *      +=                                                                *
     *  Purpose:                                                              *
     *      Mixes two colors together by averaging over their components.     *
     *  Arguments:                                                            *
     *      c (const qnf::color &c):                                          *
     *          A color.                                                      *
     *  Outputs:                                                              *
     *      None (void).                                                      *
     *  Method:                                                               *
     *      Average over each channel and store the result in *this*.         *
     **************************************************************************/
    inline void color::operator += (const qnf::color &c)
    {
        /*  Cast the values to doubles and take the average, component-wise.  */
        const double x = 0.5 * (double(red) + double(c.red));
        const double y = 0.5 * (double(green) + double(c.green));
        const double z = 0.5 * (double(blue) + double(c.blue));

        /*  Cast the double back to unsigned char's and return.               */
        red = static_cast<unsigned char>(x);
        green = static_cast<unsigned char>(y);
        blue = static_cast<unsigned char>(z);
    }

    /*  Constant colors that are worth having.                                */
    namespace colors {
        inline color white(void)
        {
            return color(0xFFU, 0xFFU, 0xFFU);
        }

        inline color black(void)
        {
            return color(0x00U, 0x00U, 0x00U);
        }

        inline color red(void)
        {
            return color(0xFFU, 0x00U, 0x00U);
        }

        inline color green(void)
        {
            return color(0x00U, 0xFFU, 0x00U);
        }

        inline color blue(void)
        {
            return color(0x00U, 0x00U, 0xFFU);
        }

        inline color yellow(void)
        {
            return color(0xFFU, 0xFFU, 0x00U);
        }
    }
    /*  End of namespace "colors".                                            */

    inline color color_wheel(double angle)
    {
        /*  There are 1535 possible colors given by the gradient. This scale  *
         *  factor helps normalize the angle.                                 */
        const double gradient_factor = 1535 / TWO_PI;

        /*  Scale the angle from (-pi, pi) to (0, 1023).                      */
        double val = (angle + ONE_PI) * gradient_factor;

        /*  Lastly, a color for the output.                                   */
        color out;

        /*  Values outside the legal range (angle < -pi). Return blue.        */
        if (val < 0.0)
            return colors::blue();

        /*  For 0 <= val < 256 transition from blue to cyan.                  */
        else if (val < 256.0)
        {
            out.red = 0x00U;
            out.green = static_cast<unsigned char>(val);
            out.blue = 0xFFU;
        }

        /*  For 256 <= val < 512 transition from cyan to green.               */
        else if (val < 512.0)
        {
            /*  Shift val back to the range (0, 256).                         */
            val -= 256.0;

            /*  Transition from cyan to green.                                */
            out.red = 0x00U;
            out.green = 0xFFU;
            out.blue = static_cast<unsigned char>(256.0 - val);
        }

        /*  For 512 <= val < 768 transition from green to yellow.             */
        else if (val < 768.0)
        {
            /*  Shift val back to the range (0, 256).                         */
            val -= 512.0;

            /*  Transition from green to yellow.                              */
            out.red = static_cast<unsigned char>(val);
            out.green = 0xFFU;
            out.blue = 0x00U;
        }

        /*  For 768 <= val < 1024 transition from yellow to red.              */
        else if (val < 1024.0)
        {
            /*  Shift val back to the range (0, 256).                         */
            val -= 768.0;

            /*  Transition from yellow to red.                                */
            out.red = 0xFFU;
            out.green = static_cast<unsigned char>(256.0 - val);
            out.blue = 0x00U;
        }

        /*  For 1024 <= val < 1280 transition from red to magenta.            */
        else if (val < 1280.0)
        {
            /*  Shift val back to the range (0, 256).                         */
            val -= 1024.0;

            /*  Gradient from red to magenta.                                 */
            out.red = 0xFFU;
            out.green = 0x00U;
            out.blue = static_cast<unsigned char>(val);
        }

        /*  Finally transition from magenta back to blue.                     */
        else if (val < 1536.0)
        {
            /*  Shift val back to the range (0, 256).                         */
            val -= 1280.0;

            /*  Transition from magenta to blue.                              */
            out.red = static_cast<unsigned char>(256.0 - val);
            out.green = 0x00U;
            out.blue = 0xFFU;
        }

        /*  Values outside the legal range (angle > +pi). Return blue.        */
        else
            return colors::blue();

        return out;
    }

    inline double clamp(double x)
    {
        if (x < 0.0)
            return 0.0;

        if (x > 255.0)
            return 255.0;

        return x;
    }

    inline color saturate(const color &c, double val)
    {
        const double r = clamp(c.red + 255.0*val);
        const double g = clamp(c.green + 255.0*val);
        const double b = clamp(c.blue + 255.0*val);

        const unsigned char red = static_cast<unsigned char>(r);
        const unsigned char green = static_cast<unsigned char>(g);
        const unsigned char blue = static_cast<unsigned char>(b);
        return color(red, green, blue);
    }

    inline color sphere_color(double phi, double theta)
    {
        const double s = (phi + HALF_PI) / HALF_PI - 1.0;
        color c = color_wheel(theta);
        return saturate(c, s);
    }
}
/*  End of "qnf" namespace.                                                   */

#endif
/*  End of include guard.                                                     */
