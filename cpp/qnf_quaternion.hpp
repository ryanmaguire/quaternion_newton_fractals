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
 *      Provides routines for generating Newton fractals with quaternions.    *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2024/01/25                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef QNF_QUATERNION_HPP
#define QNF_QUATERNION_HPP

/*  sqrt function found here. Used for computing norms.                       */
#include <cmath>

/*  Namespace for the project. "Quaternion Newton Fractal."                   */
namespace qnf {

    /*  Struct for working with quaternions.                                  */
    struct quaternion {
        /*  Contiguous array for the four components of a quaternion.         */
        double dat[4];

        /*  Empty constructor. Set the quaternion to the origin.              */
        quaternion(void)
        {
            dat[0] = 0.0;
            dat[1] = 0.0;
            dat[2] = 0.0;
            dat[3] = 0.0;
        }

        /*  Constructor from four real numbers, the individual components.    */
        quaternion(double a, double x, double y, double z)
        {
            dat[0] = a;
            dat[1] = x;
            dat[2] = y;
            dat[3] = z;
        }

        /*  Quaternion addition, which is vector addition in R^4.             */
        inline quaternion operator + (const quaternion &q) const
        {
            const double a = dat[0] + q.dat[0];
            const double x = dat[1] + q.dat[1];
            const double y = dat[2] + q.dat[2];
            const double z = dat[3] + q.dat[3];
            return quaternion(a, x, y, z);
        }

        /*  Quaternion addition, storing the result in the left-hand side.    */
        inline quaternion & operator += (const quaternion &q)
        {
            dat[0] += q.dat[0];
            dat[1] += q.dat[1];
            dat[2] += q.dat[2];
            dat[3] += q.dat[3];
            return *this;
        }

        /*  Quaternion subtraction, which is vector subtraction in R^4.       */
        inline quaternion operator - (const quaternion &q) const
        {
            const double a = dat[0] - q.dat[0];
            const double x = dat[1] - q.dat[1];
            const double y = dat[2] - q.dat[2];
            const double z = dat[3] - q.dat[3];
            return quaternion(a, x, y, z);
        }

        /*  Quaternion subtraction, storing the result in the left-hand side. */
        inline quaternion & operator -= (const quaternion &q)
        {
            dat[0] -= q.dat[0];
            dat[1] -= q.dat[1];
            dat[2] -= q.dat[2];
            dat[3] -= q.dat[3];
            return *this;
        }

        /*  Addition with a real number. Adds to the real part.               */
        inline quaternion operator + (double a) const
        {
            return quaternion(dat[0] + a, dat[1], dat[2], dat[3]);
        }

        /*  Addition with a real number storing the result in *this.          */
        inline quaternion & operator += (double a)
        {
            dat[0] += a;
            return *this;
        }

        /*  Subtraction with a real number. Subtracts from the real part.     */
        inline quaternion operator - (double a) const
        {
            return quaternion(dat[0] - a, dat[1], dat[2], dat[3]);
        }

        /*  Subtraction with a real number storing the result in *this.       */
        inline quaternion & operator -= (double a)
        {
            dat[0] -= a;
            return *this;
        }

        /*  Scalar multiplication, which is computed component-wise.          */
        inline quaternion operator * (double a) const
        {
            return quaternion(a*dat[0], a*dat[1], a*dat[2], a*dat[3]);
        }

        /*  Scalar multiplication, storing the result in *this.               */
        inline quaternion & operator *= (double a)
        {
            dat[0] *= a;
            dat[1] *= a;
            dat[2] *= a;
            dat[3] *= a;
            return *this;
        }

        /*  Division by a scalar. Performed component-wise.                   */
        inline quaternion operator / (double r) const
        {
            const double factor = 1.0 / r;
            const double a = dat[0] * factor;
            const double x = dat[1] * factor;
            const double y = dat[2] * factor;
            const double z = dat[3] * factor;
            return quaternion(a, x, y, z);
        }

        /*  Division by a scalar. Performed component-wise.                   */
        inline quaternion & operator /= (double r)
        {
            const double factor = 1.0 / r;
            dat[0] *= factor;
            dat[1] *= factor;
            dat[2] *= factor;
            dat[3] *= factor;
            return *this;
        }

        /*  Quaternion multiplication. Requires 16 real multiplications. I do *
         *  not know if this can be improved. Other libraries (Boost in C++,  *
         *  quaternion in C) also use 16 multiplications, so perhaps not.     */
         inline quaternion operator * (const quaternion &q) const
         {
                /*  The real part of the product.                             */
                const double a = dat[0]*q.dat[0] - dat[1]*q.dat[1] -
                                 dat[2]*q.dat[2] - dat[3]*q.dat[3];

                /*  The "i", or first imaginary, part of the product.         */
                const double x = dat[0]*q.dat[1] + dat[1]*q.dat[0] +
                                 dat[2]*q.dat[3] - dat[3]*q.dat[2];

                /*  The "j", or second imaginary, part of the product.        */
                const double y = dat[0]*q.dat[2] - dat[1]*q.dat[3] +
                                 dat[2]*q.dat[0] + dat[3]*q.dat[1];

                /*  The "k", or third imaginary, part of the product.         */
                const double z = dat[0]*q.dat[3] + dat[1]*q.dat[2] -
                                 dat[2]*q.dat[1] + dat[3]*q.dat[0];

                return quaternion(a, x, y, z);
         }

        /*  Multiplication where the product is stored in the left-hand side. */
        inline quaternion & operator *= (const quaternion &q)
        {
            /*  Avoid overwriting data. Copy the components of *this.         */
            const double a = dat[0];
            const double x = dat[1];
            const double y = dat[2];
            const double z = dat[3];

            /*  Perform the quaternion product and store the result in *this. */
            dat[0] = a*q.dat[0] - x*q.dat[1] - y*q.dat[2] - z*q.dat[3];
            dat[1] = a*q.dat[1] + x*q.dat[0] + y*q.dat[3] - z*q.dat[2];
            dat[2] = a*q.dat[2] - x*q.dat[3] + y*q.dat[0] + z*q.dat[1];
            dat[3] = a*q.dat[3] + x*q.dat[2] - y*q.dat[1] + z*q.dat[0];

            return *this;
        }

        /*  The square of the Euclidean norm (R^4 norm) of a quaternion.      */
        inline double norm_sq(void) const
        {
            return dat[0]*dat[0]+dat[1]*dat[1]+dat[2]*dat[2]+dat[3]*dat[3];
        }

        /*  The Euclidean norm (R^4 norm) of a quaternion.                    */
        inline double norm(void) const
        {
            return std::sqrt(this->norm_sq());
        }

        /*  Computes the square of a quaternion. Saves on redundant           *
         *  multiplications due to cancellations.                             */
        inline quaternion square(void) const
        {
            const double a = dat[0]*dat[0] - dat[1]*dat[1] -
                             dat[2]*dat[2] - dat[3]*dat[3];
            const double x = 2.0*dat[0]*dat[1];
            const double y = 2.0*dat[0]*dat[2];
            const double z = 2.0*dat[0]*dat[3];
            return quaternion(a, x, y, z);
        }

        /*  Comptutes the square and stores it in the input.                  */
        inline void square_self(void)
        {
            const double a = dat[0];
            const double two_a = 2.0*a;
            dat[0] = a*a - dat[1]*dat[1] - dat[2]*dat[2] - dat[3]*dat[3];
            dat[1] *= two_a;
            dat[2] *= two_a;
            dat[3] *= two_a;
        }

        /*  Cubes a quaternion, saving on many redundant multiplications.     */
        inline quaternion cube(void) const
        {
            const double rsq = dat[0]*dat[0];
            const double vsq = dat[1]*dat[1] + dat[2]*dat[2] + dat[3]*dat[3];
            const double factor = 3.0*rsq - vsq;
            const double a = (rsq - 3.0*vsq) * dat[0];
            const double x = factor * dat[1];
            const double y = factor * dat[2];
            const double z = factor * dat[3];
            return quaternion(a, x, y, z);
        }

        /*  Cubes a quaternion and stores the result in *this.                */
        inline void cube_self(void)
        {
            const double rsq = dat[0]*dat[0];
            const double vsq = dat[1]*dat[1] + dat[2]*dat[2] + dat[3]*dat[3];
            const double factor = 3.0*rsq - vsq;
            dat[0] *= (rsq - 3.0*vsq);
            dat[1] *= factor;
            dat[2] *= factor;
            dat[3] *= factor;
        }

        /*  Computes the quaternion conjugate, which negates imaginary parts. */
        inline quaternion conjugate(void) const
        {
            return quaternion(dat[0], -dat[1], -dat[2], -dat[3]);
        }

        /*  Conjugates *this and stores the result in *this.                  */
        inline void conjugate_self(void)
        {
            dat[1] = -dat[1];
            dat[2] = -dat[2];
            dat[3] = -dat[3];
        }

        inline quaternion reciprocal(void) const
        {
            const double factor = 1.0 / this->norm_sq();
            const double a = factor * dat[0];
            const double x = -factor * dat[1];
            const double y = -factor * dat[2];
            const double z = -factor * dat[3];
            return quaternion(a, x, y, z);
        }

        inline void reciprocate(void)
        {
            const double factor = 1.0 / this->norm_sq();
            const double neg_factor = -factor;
            dat[0] *= factor;
            dat[1] *= neg_factor;
            dat[2] *= neg_factor;
            dat[3] *= neg_factor;
        }

        /*  Quaternion division. Requires 16 real multiplications.            */
         inline quaternion operator / (const quaternion &q) const
         {
                /*  The real part of the product.                             */
                const double a = dat[0]*q.dat[0] + dat[1]*q.dat[1] +
                                 dat[2]*q.dat[2] + dat[3]*q.dat[3];

                /*  The "i", or first imaginary, part of the product.         */
                const double x = -dat[0]*q.dat[1] + dat[1]*q.dat[0] -
                                  dat[2]*q.dat[3] + dat[3]*q.dat[2];

                /*  The "j", or second imaginary, part of the product.        */
                const double y = -dat[0]*q.dat[2] + dat[1]*q.dat[3] +
                                  dat[2]*q.dat[0] - dat[3]*q.dat[1];

                /*  The "k", or third imaginary, part of the product.         */
                const double z = -dat[0]*q.dat[3] - dat[1]*q.dat[2] +
                                  dat[2]*q.dat[1] + dat[3]*q.dat[0];

                const double factor = 1.0 / q.norm_sq();
                return quaternion(a*factor, x*factor, y*factor, z*factor);
         }

        /*  Normalizes *this to unit magnitude.                               */
        inline quaternion normalize(void) const
        {
            const double factor = 1.0 / this->norm();
            const double a = dat[0] * factor;
            const double x = dat[1] * factor;
            const double y = dat[2] * factor;
            const double z = dat[3] * factor;
            return quaternion(a, x, y, z);
        }
    };
    /*  End of quaternion struct.                                             */

    /*  Quaternion metric induced by the quaternion norm.                     */
    inline double dist(const quaternion &q, const quaternion &p)
    {
        const double da = q.dat[0] - p.dat[0];
        const double dx = q.dat[1] - p.dat[1];
        const double dy = q.dat[2] - p.dat[2];
        const double dz = q.dat[3] - p.dat[3];
        return std::sqrt(da*da + dx*dx + dy*dy + dz*dz);
    }
}
/*  End of namespace "qnf".                                                   */

#endif
/*  End of include guard.                                                     */
