#ifndef MATH0X_FUNC_GET_H
#define MATH0X_FUNC_GET_H

#include <math0x/types.h>
#include <math0x/lie.h>
#include <math0x/tuple.h>
#include <math0x/func/part.h>

namespace math0x {

	namespace func {
    
		// get the ith element from a tuple
		template<class ... Args, int I>
		struct get<std::tuple<Args...>, I> {

			static_assert( I >= 0, "tuple index must be positive" );
			
			typedef get base;
      
			typedef std::tuple<Args...> domain;
			typedef math0x::tuple::element<I, domain> range;


			const range& operator()(const domain& x) const {
				return std::get<I>(x);
			}

			range operator()(domain&& x) const {
				return std::move( std::get<I>(x) );
			}
      
      
			struct push : get<lie::algebra<domain>, I > {
				push(const get&, const domain& ) { }
			};


			struct pull : partial<lie::coalgebra<domain>, I> {
				pull(const get&, const domain& at)
					: pull::base( lie::group<domain>(at).coalg().zero() ) { 
					
				}
			};
      
		};

	}
}



#endif
