/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
#include "logic.h"

namespace lambda {
  //numerals -----------------------------------------------------------------
  template<typename N,typename F>
  using _Succ=typename B::Bind<F>::template Bind<typename N::template Bind<F>>;
  using Succ=Curry<_Succ,2>;

  template<typename n,typename k>
  using _Add=typename n::template Bind<Succ>::template Bind<k>;
  using Add=Curry<_Add,2>;
  struct Mult:B{};
  struct Pow:T{};

  struct N0:False {};
  struct N1:Id {};
  using N2=Succ::Bind<N1>;
  using N3=Succ::Bind<N2>;
  using N4=Succ::Bind<N3>;
  using N5=Succ::Bind<N4>;
  using N6=Succ::Bind<N5>;
  using N7=Succ::Bind<N6>;
  using N8=Succ::Bind<N7>;
  using N9=Succ::Bind<N8>;

  template<typename N> using _Is0=typename N::template Bind<typename K::template Bind<False>>::template Bind<True>;
  using Is0=Curry<_Is0,1>;

  template<typename P>
  using _Phi=Expr<Pair,Expr<Snd,P>,Expr<Succ,Expr<Snd,P>>>;
  using Phi=Curry<_Phi,1>;

  template<typename N>
  using _Pred=Expr<Fst,Expr<N,Phi,Expr<Pair,N0,N0>>>;
  using Pred=Curry<_Pred,1>;

  template<typename N,typename K>
  using _Sub=Expr<K,Pred,N>;
  using Sub=Curry<_Sub,2>;

  template<typename N,typename K>
  using _LEq=Expr<Is0,Expr<Sub,N,K>>;
  using LEq=Curry<_LEq,2>;

  using GEq=Flip::Bind<LEq>;//this is the functional negation, not the boolean one, it reverses the < signal but not the =
  using GT=Bb::Bind<Not>::Bind<LEq>;

  template<typename N,typename K>
  using _Eq=Expr<And,Expr<LEq,N,K>,Expr<LEq,K,N>>;
  using Eq=Curry<_Eq,2>;

  using LT=Flip::Bind<GT>;

  template<typename N,typename K>
  using _NEq=Expr<Or,Expr<GT,N,K>,Expr<GT,K,N>>;
  using NEq=Curry<_NEq,2>;

  ////////////////////////////////////////////////
  // factorial (do not use over 7)
  template<typename F,typename N>
  using _H=Expr<Is0,N,N1,Expr<Mult,N,Expr<F,Expr<Pred,N>>>>;
  using H=Curry<_H,2>;
  using Fact=Y::Bind<H>;

  ////////////////////////////////////////////////
  // convert numerals into int using peano numbers
  struct Zero {
    // enum{value=0};
    static constexpr inline size_t toInt() {return 0;}
    using App=Zero;
    template<typename X> using Bind=typename X::DEBUG_Bind;
    // template<typename X> using Expr=typename X::DEBUG_Expr;
  };

  template<typename P>
  struct Peano_Succ {
    // enum{value=P::value+1};
    static constexpr inline size_t toInt() {return P::App::toInt()+1;}
    using App=Peano_Succ<P>;
    template<typename X> using Bind=typename X::DEBUG_Bind;
    // template<typename X> using Expr=typename X::DEBUG_Expr;
  };
  using Peano=Curry<Peano_Succ,1>;

  template<typename N> constexpr size_t toInt() {return N::template Bind<Peano>::template Bind<Zero>::App::toInt();}

  ////////////////////////////////////////////////
  // convert size_t into numeral
  template<size_t n,typename R=Zero> struct Numeral:public Numeral<n-1,Succ::Bind<R>> {};
  template<typename R> struct Numeral<0,R>:Succ::Bind<R> {};
};//λ
