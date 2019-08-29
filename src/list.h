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

  // LAST := Y (λgx. NULL x NIL (NULL (CDR x) (CAR x) (g (CDR x))))
  template<typename F,typename X>
  using _Last=Expr<Null,X,Nil,Expr<Null,Expr<Tail,X>,Expr<Head,X>,Expr<F,Expr<Tail,X>>>>;
  using Last=Expr<Y,Curry<_Last,2>>;

  //TRUNCATE := Y (λgx. NULL x NIL (NULL (CDR x) NIL (PAIR (CAR x) (g (CDR x)))))
  //here renamed to `Onot` as the haskell function
  template<typename F,typename X>
  using _Init=Expr<Null,X,Nil,Expr<Null,Expr<Tail,X>,Nil,Expr<Pair,Expr<Head,X>,Expr<F,Expr<Tail,X>>>>>;
  using Init=Expr<Y,Curry<_Init,2>>;

  // REVERSE := Y (λgal. NULL l a (g (PAIR (CAR l) a) (CDR l))) NIL
  template<typename F,typename A,typename L>
  using _Reverse=Expr<Null,L,A,Expr<F,Expr<Pair,Expr<Head,L>,A>,Expr<Tail,L>>>;
  using Reverse=Expr<Y,Curry<_Reverse,3>,Nil>;

  //infinit list of numerals starting at N
  template<typename F,typename N>
  using _Nats=Expr<Pair,N,Expr<F,Expr<Succ,N>>>;
  using NatsN=Expr<Y,Curry<_Nats,2>>;

  //numerals infinite list staring at 1
  struct Nats:NatsN::Bind<N1> {};

  //take n elements of a list in reverse order
  template<typename F,typename To,typename N,typename From>
  using _TakeR=
    typename If<Expr<Is0,N>>
    ::template Then<To>
    ::template Else<
      typename If<Expr<Null,From>>
      ::template Then<Nil>
      ::template Else<
        Expr<
          F,
          Expr<Pair,Expr<Head,From>,To>,
          Expr<Pred,N>,
          Expr<Tail,From>
        >
      >
    >;
  using TakeR=Expr<Y,Curry<_TakeR,4>,Nil>;

  //take n elements from a list
  template<typename N,typename O>
  using _Take=Expr<Reverse,Expr<TakeR,N,O>>;
  using Take=Curry<_Take,2>;

  template<typename S,typename E>
  using _Range=Expr<Take,Expr<Sub,E,S>,NatsN::Bind<S>>;
  using Range=Curry<_Range,2>;

  // MAP f x — maps each element of the list x through f:
  // MAP := Y (λgfx. NULL x NIL (PAIR (f (CAR x)) (g f (CDR x))))
  template<typename G,typename F, typename O>
  using _Map=
    typename If<Expr<Null,O>>
    ::template Then<Nil>
    ::template Else<
      Expr<
        Pair,
        Expr<F,Expr<Head,O>>,
        Expr<G,F,Expr<Tail,O>>
      >
    >;
  using Map=Expr<Y,Curry<_Map,3>>;

  // FILTER f x — evaluates to a list of all e in the list x for which f e is TRUE (assuming that f returns only TRUE or FALSE for all elements of x):
  // FILTER := Y (λgfx.
  //   NULL x
  //   NIL
  //  (f (CAR x) (PAIR (CAR x)) I (g f (CDR x)))
  // )
  template<typename G,typename F, typename O>
  using _Filter=
    typename If<Expr<Null,O>>
    ::template Then<Nil>
    ::template Else<
      Expr<
        F,
        Expr<Head,O>,
        Expr<
          Pair,
          Expr<Head,O>
        >,
        I,
        Expr<G,F,Expr<Tail,O>>
      >
    >;
  using Filter=Expr<Y,Curry<_Filter,3>>;

};
