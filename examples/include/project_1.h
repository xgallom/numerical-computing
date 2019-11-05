//
// Created by zahorack on 10/29/19.
//
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

#ifndef OPM_PROJECT_1_H
#define OPM_PROJECT_1_H

namespace examples {
    namespace projectOne {

        void NewtonRaphson();
        void LevenbergMarquardt();
    }
}
#endif //OPM_PROJECT_1_H
