//
// Created by zahorack on 11/5/19.
//

#include "Function.h"

Function::Function(const Symbolic f, int n):
    m_function(f),
    m_dimension(n)
{}

Symbolic Function::value()
{
    return m_function;
}
Function::~Function()
{

}
Symbolic Function::value(Point)
{
	return Symbolic();
}
Symbolic Function::gradient()
{
	return Symbolic();
}
Symbolic Function::gradient(Point)
{
	return Symbolic();
}
Symbolic Function::hessian()
{
	return Symbolic();
}
Symbolic Function::hessian(Point)
{
	return Symbolic();
}
