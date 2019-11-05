//
// Created by zahorack on 11/5/19.
//

#include "project_2.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

#include <boost/tuple/tuple.hpp>

#define GNUPLOT_ENABLE_PTY
#include "gnuplot-iostream.h"

#include "Function.h"

namespace examples {
    namespace projectTwo {
        void test()
        {
            cout<<"projectTwo";

            static const Symbolic x("x"), y("y");
            static const Symbolic F = (x - 2)*(x - 2) + (y - x*x)*(y - x*x);

            Function func(F, 2);
        }
    }
}
