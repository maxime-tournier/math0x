#ifndef MATH0X_FUNC_SCAL_H
#define MATH0X_FUNC_SCAL_H

#include <math0x/euclid.h>

namespace math0x { 
	namespace func {

		template<class E>
		struct scal {
			typedef scal base;
    
			euclid::field<E> lambda;
			euclid::space<E> space;
    
			scal( const euclid::field<E>& lambda,
			      const euclid::space<E>& space = {} ) 
				: lambda( lambda ),
				  space( space ) 
			{
      
			}

    
			E operator()(const E& x) const { return space.scal(lambda, x); }
    
			struct push;
			struct pull;    
		};

  
		template<class E>
		struct scal<E>::push : scal { 
			push(const scal& of, const E& ) : push::base(of) { }
		};


		template<class E>
		struct scal<E>::pull : scal< euclid::dual<E> > { 
			pull(const scal& of, const E& ) : pull::base(of.lambda, *of.space) { }
		};


	template<class E>
	scal<E> make_scal(const euclid::field<E>& lambda, const euclid::space<E>& space) { return {lambda, space}; }
	
	}
}

#endif
