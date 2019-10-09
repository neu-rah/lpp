/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
// access values at typelevel as c++ dependent types

#include <curry.h>

namespace lambda {
  // Static values
  template<typename T,T val>
  struct StaticValue {
    using App=StaticValue<T,val>;
    using Type=T;
    static constexpr inline T value() {return val;}
    static inline constexpr String name() {return String(val);}
    // template<typename X> using Bind=typename X::DEBUG_Bind;
    // template<typename X> using Expr=typename X::DEBUG_Expr;
  };

  template<const char**val>
  struct StaticValue<const char**,val> {
    using App=StaticValue<const char**,val>;
    static constexpr inline const char* value() {return val[0];}
    static inline constexpr String name() {return value();}
    template<typename X> using Bind=typename X::DEBUG_Bind;
    // template<typename X> using Expr=typename X::DEBUG_Expr;
  };

  template<const char**val>
  using StaticText=StaticValue<const char**,val>;

  ///////////////////////////////////////////////////////////////////////////////
  // build curried versions of c++ functions
  template<typename R,typename F,F f,int n, typename... OO>
  struct curry/*:public StaticValue<F,f>*/  {
    template<typename O> using Bind=typename curry<R,F,f,n-1,OO...,O>::App;
    using App=curry<R,F,f,n,OO...>;
    template<typename... EE> struct Expr;
    template<typename E,typename... EE> struct Expr<E,EE...>:Bind<E>::template Expr<EE...>{};
    template<typename E> struct Expr<E>:Bind<E> {};
  };

  template<typename R,typename F,F f,typename... OO>
  struct curry<R,F,f,0,OO...>:public StaticValue<F,f>  {
    using App=curry<R,F,f,0,OO...>;
    static constexpr inline R value() {return f(OO::value()...);}
  };

  template<typename O>
  inline constexpr auto value()->decltype(O::App::value()) {return O::App::value();}
};//λ
