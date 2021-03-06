/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/

#include "compile/numerals.h"
#include "compile/dependent.h"
#include "compile/list.h"
#include "compile/base.hpp"

// template<typename O>
// struct Lambda {
// };

#define LPP(x) LPP_TT struct x:lambda::Expr<lambda::x,OO...>{}; template<> struct x<>:lambda::x {};

#define LPP_TT template<typename... OO>

namespace lpp {
  //import lambda native type wrappers
  using Char=lambda::Char;
  using Int=lambda::Int;
  using Float=lambda::Float;
  using String=lambda::String;
  template<typename O>
  using As=lambda::As<O>;
  template<typename O>
  inline constexpr auto value()->decltype(O::App::value()) {return O::App::value();}
  template<typename R,typename F,F f,int n, typename... OO>
  using curry=lambda::curry<R,F,f,n,OO...>;
  //import type wrappers
  template<typename T,T val> using StaticValue=lambda::StaticValue<T,val>;
  template<const char**val> using StaticText=lambda::StaticText<val>;
  //impoort syntactic sugar
  template<typename condition> using If=lambda::If<condition>;
  template<typename... OO> using List=lambda::List<OO...>;
  //import some lambda functions as C++ variadic templates
  template<typename O,typename... OO> using Expr=lambda::Expr<O,OO...>;
  LPP(Id);
  LPP(Flip);
  LPP(Pair);
  LPP(Const);
  LPP(Fst);
  LPP(Snd);

  LPP(True);
  LPP(False);
  LPP(Not);
  LPP(And);
  LPP(Or);
  LPP(BEq);

  LPP(Succ);
  LPP(Pred);
  LPP(Add);
  LPP(Sub);
  LPP(Mult);
  LPP(Pow);
  LPP(Is0);

  LPP(Nil);
  LPP(Cons);
  LPP(Head);
  LPP(Tail);
  LPP(Null);
  LPP(Drop);
  LPP(Concat);
  LPP(Length);
  LPP(Index);
  LPP(Last);
  LPP(Init);
  LPP(Reverse);
  LPP(Nats);
  LPP(Range);
  LPP(Map);
  LPP(Filter);
  LPP(FoldL);
  LPP(FoldR);
  LPP(Zip);

  template<size_t n> struct N:Succ<N<n-1>> {};
  template<> struct N<0>:lambda::N0 {};

  template<typename N>
  inline constexpr size_t toInt() {return lambda::toInt<N>();};
};
