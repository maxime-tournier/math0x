#ifndef GROUP_FUNC_ANY_H
#define GROUP_FUNC_ANY_H

#include <group/lie.h>
#include <memory>

namespace func {

  // type erasure class

  // TODO boolean cast, set to zero
  template<class Domain, class Range>
  class any {

    typedef any< lie::algebra<Domain>, lie::algebra<Range> > push_type;
    typedef any< lie::coalgebra<Range>, lie::coalgebra<Domain> > pull_type;
    
    
    struct base {
      virtual ~base() { }

      // TODO rvalue ?
      virtual Range operator()(const Domain& x) const = 0;
      
      virtual push_type push(const Domain& at) const = 0;
      virtual pull_type pull(const Domain& at) const = 0;
      
      // virtual base* copy() const = 0;
    };

    template<class F>
    struct impl : base {
      F value;
      
      static_assert( std::is_same< Domain, func::domain<F> >::value, "bad domain" );
      static_assert( std::is_same< Range, func::range<F> >::value, "bad range" );
      
      impl(const F& value ) : value(value) { }
      impl(F&& value ) : value( std::move(value) ) { }

      Range operator()(const Domain& x) const { return value(x); }
      
      push_type push(const Domain& at) const { return func::push<F>(value, at); }
      pull_type pull(const Domain& at) const { return func::pull<F>(value, at); }
      
      // base* copy() const { return new impl(value); }
    };

    typedef std::unique_ptr<base> ptr_type;
    ptr_type ptr;
    
    const base& get() const { 
      assert( ptr ); 
      return *ptr;
    }

    template<class F>
    static ptr_type make_ptr(F&& f) {
      return ptr_type(  new impl< meta::decay<F> >( std::forward<F>(f) ) );
    }

  public:
    typedef any self;

    // any copy() const {
    //   any res;
    //   res.ptr.reset( ptr ? ptr->copy() : 0 );
    //   return res;
    // }
    
    Range operator()(const Domain& x) const { 
      return get()(x);
    }
    
    any() { }

    template<class F>
    any(F&& f) : ptr( make_ptr( std::forward<F>(f) ) )  {}
    
    any( const any& ) = delete;
    any( any&& ) = default;
    

    any& operator=(const any& ) = delete;
    any& operator=(any&& ) = default;

    template<class F>
    any& operator=(F&& f) {
      ptr = make_ptr( std::forward<F>(f) );
      return *this;
    }
    

    struct push : push_type {
      
      push(const any& of, const Domain& at) 
	: push::self(of.get().push(at)) { }
      
    };

    struct pull : pull_type {
      
      pull(const any& of, const Domain& at) 
	: pull::self(of.get().pull(at)) { }
      
    };


  };

}



#endif