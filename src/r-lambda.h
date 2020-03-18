/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Oct2019*/
////////////////////////////////////////////////////////////////////////////////
// runtime lambda abstractions /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// #include "run/curry.h"
// #include "run/types.h"
// using namespace lambda;
#include "lpp.h"
using namespace lpp;

#include "run/curry.h"

namespace rlambda {
  //identity
  template<typename O> O _rI(O o){return o;}
  template<typename O> constexpr auto rI=RCurry<decltype(_rI<O>),_rI<O>,O>();
  //self application
  template<typename O> O _rM(O o){return o(o);}
  template<typename O> constexpr auto rM=RCurry<decltype(_rM<O>),_rM<O>,O>();
  //functional true
  template<typename O> O _rK(O o,O){return o;}
  template<typename O> constexpr auto rK=RCurry<decltype(_rK<O>),_rK<O>,O,O>();
  //functional false
  template<typename O>
  auto rKI=rK<O>(rKI<O>);
  //flip/functional negation
  template<typename F,typename A,typename B>
  auto _rC(F f,A a,B b)->decltype(f(b)(a)) {return f(b)(a);}
  template<typename F,typename A,typename B>
  constexpr auto rC=RCurry<decltype(_rC<F,A,B>),_rC<F,A,B>,F,A,B>();
  //function composition
  template<typename F,typename G,typename O>
  auto _rB(F f,G g,O o)->decltype(f(g(o))) {return f(g(o));}
  template<typename F,typename G,typename O>
  constexpr auto rB=RCurry<decltype(_rB<F,G,O>),_rB<F,G,O>,F,G,O>();
  //
  template<typename A,typename B, typename F>
  auto _rV(A a,B b,F f)->decltype(f(a,b)) {return f(a,b);}
  template<typename A,typename B, typename F>
  constexpr auto rV=RCurry<decltype(_rV<A,B,F>),_rV<A,B,F>,A,B,F>();
  
};//rλ
