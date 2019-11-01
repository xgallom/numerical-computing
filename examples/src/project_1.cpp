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
        static const float alfa= 8;
        static const float c   = 4;

        static const Symbolic StartPointX(1.5), StartPointY(5.0);
        Point StartPoint = {
                .x = 1.5,
                .y = 5,
                .matrix = (StartPointX, StartPointY),
        };

        static Symbolic x("x"), y("y");
        static Symbolic F;

        static void init() {
            F = (x - 2)*(x - 2) + (y - x*x)*(y - x*x);
        }

        static Symbolic getFuncValue(Symbolic func, Point at)
        {
            Symbolic result = func.subst(x == at.x);
            result = result.subst(y == at.y);

            //cout<<"getFuncValue: "<<result<<"\n";
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


        void NewtonRaphson() {
            init();
//            getFuncValue(F, StartPoint);
//            getGradient(F);
//            getGradientValue(F, StartPoint);
//            getHessian(F);
//            getHessianValue(F, StartPoint);

            for(int iterator = 0; iterator <= 2; iterator++) {
                cout<<"Iteration: "<<iterator<<"\n";

                Symbolic f = getFuncValue(F, StartPoint);
                Gradient g = getGradientValue(F, StartPoint);

                Hessian H = getHessianValue(F, StartPoint);

                Point xnew;
                xnew.matrix = StartPoint.matrix.transpose() - (H.matrix.inverse()) * g.matrix.transpose();
                xnew.x = static_cast<double>(xnew.matrix.row(0));
                xnew.y = static_cast<double>(xnew.matrix.row(1));


                Symbolic fnew = getFuncValue(F, xnew);
                Gradient gnew = getGradientValue(F, xnew);

                double dx = static_cast<double>(gnew.dx);
                double dy = static_cast<double>(gnew.dy);

                if((dx*dx + dy*dy) > Precision) {
                    StartPoint.x = xnew.x;
                    StartPoint.y = xnew.y;
                    StartPoint.matrix = xnew.matrix.transpose();
                }
                else {
                    cout << "Newton and Raphson method reach solution with accuracy and terminated in " << iterator
                         << ". iteration \n\n";
                    cout << "Locally minimum of function have been found at [" << xnew.x << " " << xnew.y << "]\n\n";
                    break;
                }
            }
        }
    }
}