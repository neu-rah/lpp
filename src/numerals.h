/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
#include "logic.h"

namespace lambda {
  //numerals -----------------------------------------------------------------
  template<typename N,typename F>
  using _Succ=typename B::Bind<F>::template Bind<typename N::template Bind<F>/*::App*/>;//::App;
  using Succ=Curry<_Succ,2>;

  template<typename n,typename k>
  using _Add=typename n::template Bind<Succ>::template Bind<k>;
  using Add=Curry<_Add,2>;
  using Mult=B;
  using Pow=T;

  using N0=False;
  using N1=Id;
  using N2=Succ::Bind<N1>;
  using N3=Succ::Bind<N2>;
  using N4=Add::Bind<N2>::Bind<N2>;
  using N5=Add::Bind<N2>::Bind<N3>;

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
  // convert numerals into int using peano numbers
  struct Zero {
    // enum{value=0};
    static constexpr inline int toInt() {return 0;}
    using App=Zero;
  };

  template<typename P>
  struct Peano_Succ {
    // enum{value=P::value+1};
    static constexpr inline int toInt() {return P::toInt()+1;}
    using App=Peano_Succ<P>;
  };
  using Peano=Curry<Peano_Succ,1>;

  template<typename N> int toInt() {return N::template Bind<Peano>::template Bind<Zero>::toInt();}

  ////////////////////////////////////////////////
  // convert size_t into numeral
  template<size_t n,typename R=Zero> struct Numeral:public Numeral<n-1,Succ::Bind<R>> {};
  template<typename R> struct Numeral<0,R>:Succ::Bind<R> {};
};//λ
