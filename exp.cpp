/*
 * @file exp.cpp
 *
 * @authors: Ivo Filot
 * @authors: Bart Zijlstra
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cmath>    // std::exp
#include <limits>   // numeric_limits
#include <stdio.h>  // printf

 /*
  * @fn m_exp
  *
  * Calculate exponent of x using MacLaurin series
  * See: http://www.songho.ca/math/taylor/taylor_exp.html
  *
  * Notes: * m_exp is used to differentiate it from std::exp()
  *        * The MacLaurin series has poor convergence, std::exp() is way more efficient
  *
  * @param x exponent
  *
  * @return exponent of x; i.e. exp(x)
  */
 double m_exp(double x) {
     static const double prec = std::numeric_limits<double>::epsilon();

     auto result    = 1.0;    // final answer
     auto square    = 1.0;    // variable to hold current term
     auto factorial = 1.0;    // variable to hold current term
     auto term      = 1.0;    // variable to hold current term
     auto i         = 1;      // counter

     // perform MacLaurin expansion
     while(std::abs(term / result) > prec) {   // terminate when the last term could not be handled due to machine precision
         square *= x;
         factorial *= i;
         term = square / factorial;
         result+=term;
         i++;
     }

     return result;
 }

/*
 * @fn main
 *
 * Main loop: print a table of homebrew exp function versus the libm exponent
 *            function.
 */
int main() {
    // produce table of exponents
    printf("  x   |    m_exp(x)    |  std::exp(x)  |      diff      |\n");
    printf("------+----------------+---------------+----------------+\n");
    for(double x = -10; x < 20; x+= 1.0) {
        printf("%4.0f  |  %8.6e  |  %8.6e | %+8.7e | \n", x, m_exp(x), std::exp(x), (m_exp(x) - std::exp(x)) / std::exp(x));
    }

    return 0;
}

