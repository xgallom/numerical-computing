//
// Created by zahorack on 10/29/19.
//
#include "project_1.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

#include <boost/tuple/tuple.hpp>
#include <symbolic/symbolic.h>

#define GNUPLOT_ENABLE_PTY
#include "gnuplot-iostream.h"
#include "symbolicc++.h"

/*
%   Subject:    Optimalisation of processes in mechatronics
%   Project:    Gradeint optimalisation methods
%   Author:     Bc. Oliver Hollý

%   Task: Find minimum of purpose function: f(x1,x2) = (x1 - 2)^2 + (x2 - x1^2)^2
%       a.) By Nelder and Mead method (length of the edge of the starting complex = 2.5, accuracy = 0.05)
%       b.) By Newton and Raphson method
%       c.) Bz Levenberg Marquardt method
%       Consider following:
%           <> alfa = 8, c = 4
%           <> sarting point [1.5, 5], termination condition in b.), c.)
%           <> accuracy = d = g1^2 + g2^2 <= 0.001, when[g1, g2] = gradient(f).
*/

struct Point {
    double x;
    double y;
    Symbolic matrix;

    void operator=(Symbolic sym) {
        if(sym.columns() == 2) {
            matrix = sym;
            x = static_cast<double>(matrix.column(0));
            y = static_cast<double>(matrix.column(1));
        }
        else if(sym.rows() == 2) {
            matrix = sym.transpose();
            x = static_cast<double>(matrix.column(0));
            y = static_cast<double>(matrix.column(1));
        }
    }

    void operator=(Point point) {
        if(point.matrix.columns() == 2) {
            matrix = point.matrix;
            x = static_cast<double>(matrix.column(0));
            y = static_cast<double>(matrix.column(1));
        }
        else if(point.matrix.rows() == 2) {
            matrix = point.matrix.transpose();
            x = static_cast<double>(matrix.column(0));
            y = static_cast<double>(matrix.column(1));
        }

    }
};

struct Gradient {
    Symbolic dx;
    Symbolic dy;
    Symbolic matrix;
};

struct Hessian {
    Symbolic h11;
    Symbolic h12;
    Symbolic h21;
    Symbolic h22;
    Symbolic matrix;
};

namespace examples {
    namespace projectOne {

        static const float Precision   = 0.001;
        static const float MaxCycleIterations = 50;
        static const Symbolic StartPointX(1.5), StartPointY(5.0);
        const Point StartPoint = {
                .x = 1.5,
                .y = 5,
                .matrix = (StartPointX, StartPointY),
        };

        static const Symbolic x("x"), y("y");
        static const Symbolic F = (x - 2)*(x - 2) + (y - x*x)*(y - x*x);


        static Symbolic getFuncValue(Symbolic func, Point at)
        {
            Symbolic result = func.subst(x == at.x);
            result = result.subst(y == at.y);

            return result;
        }

        static Gradient getGradient(Symbolic func)
        {
            Gradient g;
            g.dx = df(func,x);
            g.dy = df(func,y);

            Symbolic GradientMatrix = ((g.dx), (g.dy));
            g.matrix = GradientMatrix;

            //cout<<"getGradient: "<<g.dx<<"  "<<g.dy<<"\n";
            return g;
        }

        static Gradient getGradientValue(Symbolic func, Point at)
        {
            Gradient g = getGradient(func);
            g.dx = getFuncValue(g.dx, at);
            g.dy = getFuncValue(g.dy, at);

            Symbolic GradientMatrix = (g.dx, g.dy);
            g.matrix = GradientMatrix;

            //cout<<"getGradientValue: "<<g.dx<<"  "<<g.dy<<"\n";
            return g;
        }

        static Hessian getHessian(Symbolic func)
        {
            Hessian hessian;
            hessian.h11 = getGradient(getGradient(F).dx).dx;
            hessian.h12 = getGradient(getGradient(F).dx).dy;
            hessian.h21 = getGradient(getGradient(F).dy).dx;
            hessian.h22 = getGradient(getGradient(F).dy).dy;

            Symbolic HessianMatrix("HessianMatrix", 2,2);
            HessianMatrix = ((hessian.h11, hessian.h12), (hessian.h21, hessian.h22));
            hessian.matrix = HessianMatrix;

            //cout<<"getHessian: \n"<<hessian.h11<<"  "<<hessian.h12<<"\n"<<hessian.h21<<"  "<<hessian.h22<<"\n";
            return hessian;
        }

        static Hessian getHessianValue(Symbolic func, Point at)
        {
            Hessian hessian = getHessian(func);
            hessian.h11 = getFuncValue(hessian.h11, at);
            hessian.h12 = getFuncValue(hessian.h12, at);
            hessian.h21 = getFuncValue(hessian.h21, at);
            hessian.h22 = getFuncValue(hessian.h22, at);

            Symbolic HessianMatrix("HessianMatrix", 2,2);
            HessianMatrix = ((hessian.h11, hessian.h12), (hessian.h21, hessian.h22));
            hessian.matrix = HessianMatrix;

            //cout<<"getHessianValue: \n"<<hessian.h11<<"  "<<hessian.h12<<"\n"<<hessian.h21<<"  "<<hessian.h22<<"\n";
            return hessian;
        }

        static double toDouble(Symbolic sym)
        {
            return static_cast<double>(sym);
        }


        void NewtonRaphson() {

            Point point = StartPoint;

            for(int iterator = 0; iterator <= MaxCycleIterations; iterator++) {
                cout<<"Iteration: "<<iterator<<"\n";

                Symbolic f = getFuncValue(F, point);
                Gradient g = getGradientValue(F, point);
                Hessian H = getHessianValue(F, point);

                Point newpoint;
                newpoint = point.matrix.transpose() - (H.matrix.inverse()) * g.matrix.transpose();

                Symbolic fnew = getFuncValue(F, newpoint);
                Gradient gnew = getGradientValue(F, newpoint);

                double dx = toDouble(gnew.dx), dy = toDouble(gnew.dy);

                if((dx*dx + dy*dy) > Precision) {
                    point = newpoint;
                }
                else {
                    cout << "Newton and Raphson method reach solution with accuracy and terminated in " << iterator
                         << ". iteration \n\n";
                    cout << "Locally minimum of function have been found at [" << newpoint.x << " " << newpoint.y << "]\n\n";
                    break;
                }
            }
        }

        void LevenbergMarquardt()
        {
            float alfa= 8;
            float c   = 4;
            Point point = StartPoint;

            for(int iterator = 0; iterator <= MaxCycleIterations; iterator++) {
                cout<<"Iteration: "<<iterator<<"\n";

                Symbolic f = getFuncValue(F, point);
                Gradient g = getGradientValue(F, point);
                Hessian H = getHessianValue(F, point);

                Symbolic eye = ((static_cast<Symbolic>(alfa),    0),
                                (   0, static_cast<Symbolic>(alfa)));

                Point newpoint;
                newpoint = point.matrix.transpose() - (H.matrix + eye).inverse() * g.matrix.transpose();

                Symbolic fnew = getFuncValue(F, newpoint);
                Gradient gnew = getGradientValue(F, newpoint);

                if(toDouble(fnew) < toDouble(f)) {
                    alfa = alfa/c;

                    if ((toDouble(gnew.dx)*toDouble(gnew.dx) + toDouble(gnew.dy)*toDouble(gnew.dy)) > Precision) {
                        point = newpoint;
                    } else {
                        cout << "Levenberg Marquardt method reach solution with accuracy and terminated in " << iterator
                             << ". iteration \n\n";
                        cout << "Locally minimum of function have been found at [" << newpoint.x << " " << newpoint.y
                             << "]\n\n";
                        break;
                    }
                }
                else {
                    alfa = alfa/c;
                }
            }
        }

        static void visualisations() {
            std::string funkcia = "((x - 2)*(x - 2) + (y - x*x)*(y - x*x))";
            Gnuplot gp("gnuplot -persist");

            gp<<("set xrange [-5:5]\n");
            gp<<("set yrange [-5:5]\n");
            gp<<("set pm3d at b\n");
            gp<<("set ticslevel 0.8\n");
            gp<<("set isosample 40,40\n");
            gp<<("set cntrparam levels 15\n");
            gp<<("set samples 20\n");
            gp<<("set isosamples 21\n");
            gp<<("set view 60, 30, 0.85, 1.1\n");
            gp<<("set key at screen 1.0, 0.9\n");
            gp<<("set style textbox opaque noborder margins 0.5, 0.5\n");
            gp<<("set cntrparam levels incr -10,1,10\n");
            gp<<("set contour\n");

            gp<<("splot ");
            gp<<((funkcia));
            gp<<("\n");
        }

    }
}