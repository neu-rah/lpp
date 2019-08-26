/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
// lambda abstractions /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "curry.h"

namespace lambda {
  ////////////////////////////////////////////////////////////////////////////////
  // some standard terms -----------------------------------------------
  template <typename O> using _I=O;
  using I=Curry<_I,1>;

  template <typename F> using _M=typename F::template Bind<F>;
  using M=Curry<_M,1>;

  template<typename O,typename> using _K=O;
  using K=Curry<_K,2>;

  using KI=K::Bind<I>;

  template<typename F,typename A,typename B> using _C=typename F::template Bind<B>::template Bind<A>;
  using C=Curry<_C,3>;

  template<typename F,typename G,typename O> using _B=typename F::template Bind<typename G::template Bind<O>>;
  using B=Curry<_B,3>;

  template<typename A,typename B, typename F>
  using _V=typename F::template Bind<A>::template Bind<B>;
  using V=Curry<_V,3>;

  using Bb=Expr<B,B,B>;

  template<typename F,typename X>
  using ___Y=typename F::template Bind<typename X::template Bind<X>>;
  using __Y=Curry<___Y,2>;
  template<typename F>
  using _Y=typename __Y::Bind<F>::template Bind<typename __Y::template Bind<F>>;
  using Y=Curry<_Y,1>;

  ////////////////////////////////////////////////////////////////////////////////
  //base  functions --------------------------------
  struct Id:I{};
  struct Flip:C{};
  struct Pair:V{};

  template<typename P>
  using _Fst=typename P::template Bind<K>;
  using Fst=Curry<_Fst,1>;

  template<typename P>
  using _Snd=typename P::template Bind<KI>;
  using Snd=Curry<_Snd,1>;
};//λ
