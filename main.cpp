
#include <group/euclid.h>
#include <group/real.h>

#include <group/tuple.h>
#include <group/tuple/stream.h>

#include <group/log.h>


struct taiste {
  
  template<int I>
  void operator()() const {
    log(I);
  };
  
};



int main(int, char** ) {

  euclid::space<RR> E;

  RR x = E.zero();
  RR z = E.sum(E.minus(x), x);

  typedef tuple::repeat<RR, 2> pair_type;
  
  euclid::space<pair_type> Pair;

  pair_type pair = Pair.zero();
  
  typedef std::tuple< pair_type, pair_type > double_pair_type;
  euclid::space<double_pair_type> DPair;

  double_pair_type dpair = DPair.zero();
  
  DPair.coord(2, dpair) = 1;
  log( dpair );

  return z == E.zero();
}
