/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
namespace lambda {
  struct Cons:V{};

  struct Head:Fst {};
  struct Tail:Snd {};

  struct Nil:Const::Bind<True> {};
  template<typename O>
  struct _Null:Expr<O,Expr<Const,Expr<Const,False>>> {};
  using Null=Curry<_Null,1>;

  //list construction helper
  template<typename... OO> struct List;
  template<typename O,typename... OO> struct List<O,OO...>:Expr<Cons,O,List<OO...>> {};
  template<> struct List<>:Nil {};

  template<typename N>
  using _Drop=Expr<N,Tail>;
  using Drop=Curry<_Drop,1>;
};
