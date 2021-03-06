#ifndef MATH0X_REAL_H
#define MATH0X_REAL_H

#include <math0x/types.h>
#include <math0x/func/id.h>
#include <math0x/euclid.h>

#include <cassert>

// real numbers, as defined in types.h

namespace math0x {

	// euclidean structure
	namespace euclid {

		template<>
		struct traits<RR> {
    
			typedef RR field;
			typedef RR dual;

			traits(const RR& ) { }
			traits() { }
    
			NN dim() const { return 1; }

			RR zero() const { return 0; }

			space<dual> operator*() const { return {}; } 

			field& coord(NN i, RR& x) const { 
				assert( i == 0 );
				meta::noop( i );
				return x; 
			}
			
			const field& coord(NN i, const RR& x) const { 
				assert( i == 0 );
				meta::noop( i );
				return x; 
			}
    
			static constexpr int static_dim = 1;


			class range {
				const RR* data;
			public:
				
				range(const RR& data) : data(&data) { }

				bool empty() const { return !data; }

				void pop() { data = 0; }

				const field& front() const { 
					assert( data );
					return *data; 
				}
				
			};

		};

	}

	// (commutative) lie group structure
	namespace lie {
		
		template<> 
		struct traits<RR> {
    
			typedef RR algebra;
			typedef euclid::dual<algebra> coalgebra;
			
			struct Ad : func::id< RR > {
				Ad(const RR& ) { }
			};

			struct AdT : func::id< RR > {
				AdT(const RR& ) { }
			};
    
			struct exp : func::id<RR> {
				exp(const group<RR>& ) { }
			};

			struct log : func::id<RR> {
				log(const group<RR>& ) { }
			};
    
			RR id() const { return 0; }
			RR inv(const RR& x) const { return -x; }
			RR prod(const RR& x, const RR& y) const { return x + y; }
    
			traits() { }
			traits(const RR& ) { }
    
			euclid::space< algebra > alg() const { return {}; }
    
			algebra bracket(const algebra&, const algebra& ) const { return 0; }
			coalgebra cobracket(const coalgebra&, const coalgebra& ) const { return 0; }
		};

	}

}

#endif
