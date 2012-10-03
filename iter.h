#ifndef MATH0X_ITER_H
#define MATH0X_ITER_H

#include <math0x/types.h>
#include <math0x/comma.h>

namespace math0x {

	// control structure for iterative algorithms
	struct iter {

		// iterations bound
		NN bound;
    
		// (positive) precision threshold
		RR epsilon;			

		iter(NN bound = 0, RR epsilon = -1.0) 
			: bound(bound), epsilon(epsilon) { }
    
		// performs iteration with given function object. @f may or may
		// not return current precision. returns actual iteration
		// performed and last precision.
		template<class F>
		iter operator()(F&& f) const {

			NN i = 0;
			RR eps = 0;
			
			for(i = 0; i < bound; ++i) {
				eps = ( std::forward<F>(f)(), on_void<RR>(0.0) ).value; 
	
				if( eps <= epsilon ) break;
			}
      
			return iter(i, eps);
		}

	};

}


#endif
