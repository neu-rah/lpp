/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
// Currying C++ templates //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include "base.h"
namespace lambda {
  template<template<typename...> class F,int n, typename... OO>
  struct Curry {
    using This=Curry<F,n,OO...>;
    template<typename O> using Bind=Curry<F,(n>0)?n-1:n,OO...,O>;
    using App=This;
    template<typename... EE> struct Expr;
    template<typename E,typename... EE> struct Expr<E,EE...>:Bind<E>::template Expr<EE...> {};
    template<typename E> struct Expr<E>:Bind<E> {};
    static inline constexpr std::string name() {return Name<F,n,OO...>::name();}
  };

  // template<template<typename...> class F,int n, typename... OO>
  // struct Curry<F,n,n,OO...> {};

  // template<template<typename...> class F, typename O,typename... OO>
  // struct Curry<F,-1,O,OO...> {
  //   template<typename P> using Bind=Curry<F,-1,OO...,P>;
  //   using App=typename F<O,OO...>::App;
  //   template<typename... EE> struct Expr;
  //   template<typename E,typename... EE> struct Expr<E,EE...>:Bind<E>::template Expr<EE...>::App {};
  //   template<typename E> struct Expr<E>:Bind<E>::App {};
  // };

  template<template<typename...> class F, typename... OO>
  struct Curry<F,0,OO...> {
    using App=typename F<OO...>::App;
    template<typename X> using Bind=typename App::template Bind<X>;
    // template<typename X> using Bind=typename X::DEBUG_Bind;
    // template<typename X> using Expr=typename X::DEBUG_Expr;
    template<typename... EE> struct Expr;
    template<typename E,typename... EE> struct Expr<E,EE...>:Bind<E>::template Expr<EE...> {};
    template<typename E> struct Expr<E>:Bind<E> {};
    static inline constexpr std::string name() {return Name<F,0,OO...>::name();}
  };

  //////////////////////////////////////////////
  // get long bind sequences easier to write
  template<typename O,typename... OO> using Expr=typename O::App::template Expr<OO...>;

  //point-free composition helper
  template<typename O,typename P,typename... OO> struct Comp:O::template Bind<Comp<P,OO...>> {};
  template<typename O,typename P> struct Comp<O,P>:O::template Bind<P> {};
};//λ
