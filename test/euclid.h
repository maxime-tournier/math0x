#ifndef MATH0X_TEST_EUCLID_H
#define MATH0X_TEST_EUCLID_H

// TODO includes !

namespace math0x {
	namespace test {

		template<class E>
		void euclid(const euclid::space<E>& space) {

			debug("testing Euclidean space structure for", meta::name<E>());
			debug();
			
			typedef math0x::euclid::dual<E> dual;
			typedef math0x::euclid::field<E> field;

			math0x::lie::group<E> group( space.zero() );
			math0x::lie::group< dual > groupT( (*space).zero() );
			
			E x = test::random( group );
			dual f = test::random( groupT );
			
			field lambda = test::random< field >();
			
			using namespace func;
			
			test::func< line<E> > (x);
			test::func< form<E> > (f);
			test::func< scal<E> > (lambda); 
		
			test::func< sum<E> > ();
			test::func< minus<E> > ();
			test::func< dot<E> > (); 
			test::func< norm2<E> > (); 
			
		}

	}
}


#endif
