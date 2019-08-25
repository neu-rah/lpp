/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
#include "lambda.h"

namespace lambda {
  //logic -----------------------------------------
  struct True:K {};
  struct False:KI{};
  struct Not:C{};

  template<typename P,typename Q> using _And=typename P::template Bind<Q>::template Bind<P>::App;
  struct And:Curry<_And,2> {};

  struct Or:M {};

  template<typename P,typename Q> using _BEq=typename P::template Bind<Q>::template Bind<Not::Bind<Q>>::App;
  using BEq=Curry<_BEq,2>;

  template<typename O,typename F> using _T=typename F::template Bind<O>;
  using T=Curry<_T,2>;
};
