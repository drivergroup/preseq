/*    Copyright (C) 2011 University of Southern California and
 *                       Andrew D. Smith and Timothy Daley
 *
 *    Authors: Andrew D. Smith and Timothy Daley
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONTINUED_FRACTION_HPP
#define CONTINUED_FRACTION_HPP

#include <fstream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <complex>
#include <cassert>

struct ContinuedFraction {
  // Constructor
  ContinuedFraction(const std::vector<double> &coeffs,
		    const size_t in_lower, const size_t in_upper) :
    lower_offset(in_lower), upper_offset(in_upper), ps_coeffs(coeffs) {}
  
  // Evaluators
  double
  operator()(const double val, const size_t depth);
  
  double 
  complex_deriv(const double val, const size_t depth);
  
  size_t lower_offset;
  size_t upper_offset;
  std::vector<double> ps_coeffs;
  std::vector<double> cf_coeffs;
  std::vector<double> offset_coeffs;
};

class ContinuedFractionApproximation {
public:
  static const size_t MINIMUM_ALLOWED_DEGREE = 6;
  
  // Constructor
  ContinuedFractionApproximation(const ContinuedFraction &cf_instance, 
				 const size_t max_terms) :
    cont_frac_estimate(cf_instance), depth(max_terms) {
    compute_cf_coeffs();
  }
  
  // Mutators
  void compute_cf_coeffs();
  
  void
  set_depth(const size_t max_terms) {
    depth = max_terms;
    assert(depth >= MINIMUM_ALLOWED_DEGREE);
  }
  
  size_t get_depth() const {return depth;} 
  
  double
  locate_local_max(const double lower_limit, const double upper_limit,
		   const double step_size, const double upper_bound,
		   const double deriv_upper_bound);
  
  ContinuedFraction cont_frac_estimate;
private:
  size_t depth;
  
  double locate_zero_cf_deriv(const double val, const double prev_val);
};

#endif
