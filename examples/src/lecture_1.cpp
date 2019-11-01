//
// Created by zahorack on 10/15/19.
//
#include "lecture_1.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
//#include <string.h>

#include <boost/tuple/tuple.hpp>
// This must be defined before the first time that "gnuplot-iostream.h" is included.
#define GNUPLOT_ENABLE_PTY
#include "gnuplot-iostream.h"
#include "symbolicc++.h"


namespace examples {

    template <typename T>
    static void fillBuffer(T *buff, T min, T step, int size) {
        T value = min;

        for(int i = 0; i < size; i++) {
            buff[i] = value;
            value += step;
        }
    }

    namespace lectureOne {

        /*  Ste dopravný inžinier a máte na starosť údržbu povrchu úseku diaľnice. Dopravu treba
            presmerovať do jedného pruhu a treba navrhnúť rýchlostný limit, ktorý minimalizuje
            dopravné zápchy. */

        void taskOne() {

            std::cout << "Hello world";
            double CarLength = 2.5,
                    gravity = 9.81,
                    ReactionTime = 0.33,
                    AdhesionCoef = 0.8;

            std::map<double, double> data;

            for (double j = 0; j < 12; j += 0.5) {

                double safe_distance = j / (CarLength + (j * j / (2 * AdhesionCoef * gravity) + ReactionTime * j));

                data[j] = safe_distance;
            }
            //// -persist option makes the window not disappear when your program exits
            Gnuplot gp("gnuplot -persist");
            // NOTE: we can use map here because the X values are intended to be
            // sorted.  If this was not the case, vector<pair<double,double>> could be
            // used instead.

            gp << "set xrange [0:12]\nset yrange [0:1]\n";
            gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
            gp.send(data);

        }


        /*
            Vykreslite graf funkcie f(u, v) =(u-3)*v+3)^2 + ((u^2-3)*v -3)^2 v3D priestore
            a jeho vrstevnice – contour, nájdite na grafe lokálne minimá
            a maximá, resp. stacionárne body.
         */
        void taskTwo() {
            std::string funkcia = "(((x-3)*y+3)*((x-3)*y+3) + ((x*x - 3)*y -3)*((x*x - 3)*y -3))";

            Gnuplot gp("gnuplot -persist");

            Symbolic x("x"), y("y");
            Symbolic Fuv;

            Fuv = (((x-3)*y+3)*((x-3)*y+3) + ((x*x - 3)*y -3)*((x*x - 3)*y -3));
            cout<<Fuv<<endl;

//            const int Size = 10;
//            int x[Size];
//            int y[Size];
//            int z[Size];
//            fillBuffer<int>(x, -4,1, Size);
//            fillBuffer<int>(y, -4,1, Size);
//
//            for(int i = 0; i < Size; i++) {
//                z[i] = ((x[i]-3)*y[i]+3)^2 + ((x[i]^2 - 3)*y[i] -3)^2;
//                printf("%d\n", z[i]);
//            }


//            gp<<("a = 0.9\n");
//            gp<<("f(x) = a * sin(x)\n");
//            gp<<("g(x) = a * cos(x)\n");
//            gp<<("plot f(x) title 'sin(x)' with lines linestyle 1, g(x) notitle with lines linestyle 2\n");

            gp<<("set xrange [-2:2]\n");
            gp<<("set yrange [-2:2]\n");
            gp<<("set pm3d at b\n");
            gp<<("set ticslevel 0.8\n");
            gp<<("set isosample 40,40\n");

            gp<<("splot ");
            gp<<((funkcia));
            gp<<("\n");
        }

        void taskThree()
        {
            Gnuplot gp("gnuplot -persist");

            Symbolic x("x");
            Symbolic y("y");
            Symbolic F;


            F = integrate(x + 1, x);
            F = (x + 2 + y);
            cout<<df(F,x);

            cout<<"\n\nResult:";
            cout<<F.subst(x == 5);

            gp<<("splot ");
            gp<<(F);
            gp<<("\n");


//            cout << integrate(x + 1, x);     // => 1/2*x^(2)+x
//            Symbolic y("y");
//            cout << df(y, x);              // => 0
//            cout << df(y[x], x);           // => df(y[x],x)
//            cout << df(exp(cos(y[x])), x); // => -sin(y[x])*df(y[x],x)*e^cos(y[x])

//            gp<<("a = 0.9\n");
//            gp<<("f(x) = a * sin(x)\n");
//            gp<<("g(x) = a * cos(x)\n");
//            gp<<("plot f(x) title 'sin(x)' with lines linestyle 1, g(x) notitle with lines linestyle 2\n");

//            Symbolic alpha("alpha");
//            Symbolic X, XI, dX, result;
//
//            X = ( ( cos(alpha), sin(alpha) ),
//                    (-sin(alpha), cos(alpha) ) );
//
//            cout << X << endl;
//
//            XI = X[alpha == -alpha]; cout << XI << endl;
//            dX = df(X, alpha);       cout << dX << endl;
//
//            result = XI * dX;        cout << result << endl;
//            result = result[(cos(alpha)^2) == 1 - (sin(alpha)^2)];
//            cout << result << endl;
        }
    }
}




