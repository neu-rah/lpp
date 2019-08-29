/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/

#include "numerals.h"
#include "dependent.h"
#include "list.h"
#include "base.hpp"

#define LPP(x) LPP_TT struct x:lambda::Expr<lambda::x,OO...>{}; template<> struct x<>:lambda::x {};
#define LPP_TT template<typename... OO>

namespace lpp {
  //import lambda native type wrappers
  using Char=lambda::Char;
  using Int=lambda::Int;
  using Float=lambda::Float;
  using String=lambda::String;
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

  template<size_t n> struct N:Succ<N<n-1>> {};
  template<> struct N<0>:lambda::N0 {};

  //some utilities (for debug mostly)
  template<typename N>
  auto toInt=lambda::toInt<N>;
};
