/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Oct2019*/
////////////////////////////////////////////////////////////////////////////////
// runtime lambda abstractions /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "run/curry.h"
namespace rlambda {

  template<typename O> inline O __id(O i) {return i;}
  template<typename O> auto _id=curry(&__id<O>);

  template<typename O> inline O __true(O o,O) {return o;}
  template<typename O> auto _true=curry(&__true<O>);

  template<typename O> inline O __false(O,O o) {return o;}
  template<typename O> auto _false=curry(&__false<O>);

  template<typename F>
  using Ret=typename FuncInfo<F>::Ret;

  template<typename F,typename A,typename B>
  auto __flip(F f,A a,B b)->decltype(f(b)(a)) {return f(b)(a);}
  template<typename F,typename A,typename B>
  auto _flip=curry(&__flip<F,A,B>);

};//rλ
