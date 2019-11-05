//
// Created by zahorack on 11/5/19.
//

#ifndef NUMERICAL_COMPUTING_POINT_H
#define NUMERICAL_COMPUTING_POINT_H

#include "symbolicc++.h"

class Point {

public:
    double x;
    double y;
    Symbolic matrix;


    void operator=(Symbolic);
    void operator=(Point);
};

#endif //NUMERICAL_COMPUTING_POINT_H
