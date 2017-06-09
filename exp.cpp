/*
 * @file exp.cpp
 *
 * @author: Ivo Filot
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
 * @fn factorial
 *
 * Calculate factorial using a recursion formula ( n! = n * (n-1)! )
 *
 * @param x number to get factorial from
 *
 * @return factorial of x
 */
double factorial(double x) {
    if(x > 1) {
        return x * factorial(x - 1);
    } else {    // 0! and 1! equal unity
        return 1;
    }
}

/*
 * @fn ipow
 *
 * Integer-raised exponentiation based on squaring
 * See: https://en.wikipedia.org/wiki/Exponentiation_by_squaring
 *
 * x^n = x * (x^2) ^ ( (n-1) / 2 ); if n is odd
 *     =     (x^2) ^ ( n / 2 )    ; if n is even
 *
 * @param base Base value
 * @param exp  Exponent value
 *
 * @return base^exp
 */
double ipow(double base, unsigned int exp) {
    double result = 1;
    while(exp) {
        if(exp & 1) {       // check whether exp is odd, if so, multiple result by base
            result *= base; 
        }

        // this part is executed every time

        exp >>= 1;          // shift-right the exp (divide by two ignoring the LSB)
        base *= base;       // square the base number
    }

    return result;
}

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

    double result = 1.0;    // final answer
    double term = 1.0;      // variable to hold current term
    unsigned int i = 1;     // counter

    // perform MacLaurin expansion
    while(std::abs(term / result) > prec) {   // terminate when the last term could not be handled due to machine precision
        term = ipow(x, i) / factorial(i);
        result += term;
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

