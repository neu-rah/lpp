/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
// Currying C++ templates //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template<template<typename...> class F,int n=-1, typename... OO>
struct Curry {
  template<typename O> using Bind=typename Curry<F,(n>0)?n-1:n,OO...,O>::App;
  using App=Curry<F,n,OO...>;
  template<typename... EE> struct Expr;
  template<typename E,typename... EE> struct Expr<E,EE...>:Bind<E>::template Expr<EE...>{};
  template<typename E> struct Expr<E>:Bind<E> {};
};

template<template<typename...> class F, typename O,typename... OO>
struct Curry<F,-1,O,OO...> {
  template<typename P> using Bind=typename Curry<F,-1,OO...,P>::App;
  using App=typename F<O,OO...>::App;
  template<typename... EE> struct Expr;
  template<typename E,typename... EE> struct Expr<E,EE...>:Bind<E>::template Expr<EE...>{};
  template<typename E> struct Expr<E>:Bind<E> {};
};

template<template<typename...> class F, typename O,typename... OO>
struct Curry<F,0,O,OO...> {
  using App=typename F<O,OO...>::App;
  // template<typename X> using Bind=typename X::DEBUG;
  template<typename X> using Expr=typename X::DEBUG_Expr;
};

//////////////////////////////////////////////
// get long bind sequences easier to write
template<typename O,typename... OO> using Expr=typename O::template Expr<OO...>;
