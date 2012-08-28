#ifndef GROUP_FUNC_MINUS_H
#define GROUP_FUNC_MINUS_H

#include <group/euclid.h>

namespace func {

  template<class E>
  struct minus {
    typedef minus self;
    
    euclid::space<E> space;

    E operator()(const E& x) const {
      return space.minus(x);
    }

    
    struct push : minus {
      
      push(const minus& of, const E& ) : push::self(of) { }
    
    };
    
    struct pull : minus< euclid::dual<E> > {
      
      pull(const minus& of, const E& ) : pull::self{ *of.space } {  }
      
    };
    
  };
  
  
}


#endif
