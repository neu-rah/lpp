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

  template<typename G,typename A, typename B>
  using _Concat=
    typename If<Expr<Null,A>>
    ::template Then<B>
    ::template Else<
      Expr<Pair,
        Expr<Head,A>,
        Expr<G,Expr<Tail,A>,B>
      >
    >;
  using Concat=Expr<Y,Curry<_Concat,3>>;

  template<typename F,typename Cnt,typename X>
  using _Length=Expr<Null,X,Cnt,Expr<F,Expr<Succ,Cnt>,Expr<Tail,X>>>;
  using Length=Expr<Y,Curry<_Length,3>,N0>;

  template<typename X,typename N>
  using _Index=Expr<Head,Expr<N,Tail,X>>;
  using Index=Curry<_Index,2>;

};
