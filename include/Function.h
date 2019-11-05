//
// Created by zahorack on 11/5/19.
//

#ifndef NUMERICAL_COMPUTING_FUNCTION_H
#define NUMERICAL_COMPUTING_FUNCTION_H

#include <symbolic/symbolic.h>
#include "symbolicc++.h"
#include "Point.h"

class Function {
    Symbolic m_function;
    int m_dimension;
public:
    Function(const Symbolic f, int n);
    ~Function();


    Symbolic value();
    Symbolic value(Point);

    Symbolic gradient();
    Symbolic gradient(Point);

    Symbolic hessian();
    Symbolic hessian(Point);

};

#endif //NUMERICAL_COMPUTING_FUNCTION_H
