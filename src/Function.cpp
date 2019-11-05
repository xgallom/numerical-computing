//
// Created by zahorack on 11/5/19.
//

#include "include/Function.h"


Function::Function(const Symbolic f, int n):
    m_function(f),
    m_dimension(n)
{}


Symbolic Function::value()
{
    return m_function;
}