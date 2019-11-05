//
// Created by zahorack on 11/5/19.
//

#include "Point.h"

void Point::operator=(Symbolic sym) {
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

void Point::operator=(Point point) {
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
