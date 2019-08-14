/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
// lambda abstractions /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "curry.h"

////////////////////////////////////////////////////////////////////////////////
// some standard terms -----------------------------------------------
template <typename O> using _I=O;
using I=Curry<_I,1>;

template <typename F> using _M=typename F::template Bind<F>::App;
using M=Curry<_M,1>;

template<typename O,typename> using _K=O;
using K=Curry<_K,2>;

using KI=K::Bind<I>;

template<typename F,typename A,typename B> using _C=typename F::template Bind<B>::template Bind<A>::App;
using C=Curry<_C,3>;

template<typename F,typename G,typename O> using _B=typename F::template Bind<typename G::template Bind<O>>::App;
using B=Curry<_B,3>;

template<typename A,typename B, typename F>
using _V=typename F::template Bind<A>::template Bind<B>::App;
using V=Curry<_V,3>;

// template<typename F,typename G,typename A,typename B>
// using _Bb=Expr<F,Expr<G,A,B>>;
// using Bb=Curry<_Bb,4>;

using Bb=Expr<B,B,B>;

////////////////////////////////////////////////////////////////////////////////
//base  functions --------------------------------
using Id=I;
using Flip=C;
using Pair=V;

template<typename P>
using _Fst=typename P::template Bind<K>;
using Fst=Curry<_Fst,1>;

template<typename P>
using _Snd=typename P::template Bind<KI>;
using Snd=Curry<_Snd,1>;
