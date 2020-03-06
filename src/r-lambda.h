/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Oct2019*/
////////////////////////////////////////////////////////////////////////////////
// runtime lambda abstractions /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "run/curry.h"
#include "run/types.h"
using namespace lambda;

namespace rlambda {

  template<template<typename> class T>
  struct RI {
    template<typename O>
    using Res=typename T<O>::Type;

    template<typename O>
    Res<O> operator()(O o){return T<O>(o);}
  };

  // // function ref, should be template or normal param? probably both versions
  // template <typename F,F& f,typename O>
  // auto _rM(O o)->decltype(f(f)(o)) {return f(f)(o);}
  // template <typename F,F& f,typename O>
  // RCurry<decltype(_rM<F,f,O>),_rM<F,f,O>,O> rM;
  //
  // template<typename O,typename>
  // O _rK(O o) {return o;}
  // template<typename O,typename P>
  // RCurry<decltype(_rK<O,P>),_rK<O,P>,O,P> rK;
  //
  // template<typename O,typename P>
  // auto rKI=rK<rI<O>,P>(rI<O>);
  //
  // template<typename F,F& f,typename A,typename B>
  // auto _rC(A a,B b)->decltype(f(b)(a)) {return f(b)(a);}


};//rλ
