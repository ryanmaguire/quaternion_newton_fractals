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
 *      Renders a gif of Newton fractals for 2-dimensional subspaces of       *
 *      the quaternions.                                                      *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2024/01/25                                                        *
 ******************************************************************************/
#include "qnf.hpp"
#include <cstdio>
#include <cstdlib>
#include <cmath>

static inline qnf::quaternion func(const qnf::quaternion &q)
{
    return q.cube() - 1.0;
}

static inline qnf::quaternion newton(const qnf::quaternion &q)
{
    qnf::quaternion num = q.cube()*2.0 + 1.0;
    qnf::quaternion den = q.square() * 3.0;
    return num / den;
}

int main(void)
{
    const unsigned int n_frames = 100U;
    char name[20];
    unsigned int frame;
    const double angle_step = TWO_PI / static_cast<double>(n_frames);
    const double eps = 1.0E-8;
    const double eps_sq = 1.0E-16;
    double angle = 0.0;

    for (frame = 0U; frame < n_frames; ++frame)
    {
        const double cos_ang = std::cos(angle);
        const double sin_ang = std::sin(angle);
        const qnf::quaternion one = qnf::quaternion(1.0, 0.0, 0.0, 0.0);
        const qnf::quaternion u0 = qnf::quaternion(cos_ang, sin_ang, 0.0, 0.0);
        const qnf::quaternion u1 = qnf::quaternion(0.0, 0.0, cos_ang, sin_ang);
        unsigned int x, y, iters;
        qnf::color c;
        std::sprintf(name, "fractal_%03u.ppm", frame);
        qnf::ppm PPM = qnf::ppm(name);
        PPM.init();

        for (y = 0U; y < qnf::setup::ysize; ++y)
        {
            const double a0 = qnf::setup::start + qnf::setup::pyfact * y;

            for (x = 0U; x < qnf::setup::xsize; ++x)
            {
                const double a1 = qnf::setup::start + qnf::setup::pxfact*x;
                qnf::quaternion q = u0*a0 + u1*a1;
                qnf::quaternion p = func(q);

                for (iters = 0U; iters < qnf::setup::max_iters; ++iters)
                {
                    if (p.norm_sq() < eps_sq)
                        break;

                    q = newton(q);
                    p = func(q);
                }

                if (p.norm_sq() > eps_sq)
                    c = qnf::colors::black();

                else if (qnf::dist(q, one) < eps)
                    c = qnf::colors::white() * 0.5;
                else
                {
                    const double rho_sq = q.dat[1]*q.dat[1] + q.dat[2]*q.dat[2];
                    const double rho = std::sqrt(rho_sq);
                    const double phi = std::atan2(q.dat[3], rho);
                    const double theta = std::atan2(q.dat[2], q.dat[1]);
                    c = qnf::sphere_color(phi, theta);
                }

                c.write(PPM);
            }
        }

        PPM.close();
        std::printf("Current Frame: %3u  Total: %u\n", frame + 1U, n_frames);

        angle += angle_step;
    }

    std::system("ffmpeg -i fractal_%03d.ppm fractal.gif");
    std::system("rm -f *.ppm");
}
