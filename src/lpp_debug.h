/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
#ifdef LPP_DEBUG
  #include <string>
  #include "lambda.h"
  #include <iostream>

  namespace lambda {
    template<typename O> Str trace() {return O::name();}
    template<> Str trace<Char>() {return "Char";}
    template<> Str trace<Int>() {return "Int";}
    template<> Str trace<Float>() {return "Float";}
    template<> Str trace<String>() {return "String";}

    template<> Str trace<I>() {return "I";}
    template<> Str trace<M>() {return "M";}
    template<> Str trace<K>() {return "K";}
    template<> Str trace<KI>() {return "KI";}
    template<> Str trace<C>() {return "C";}
    template<> Str trace<B>() {return "B";}
    template<> Str trace<V>() {return "V";}
    template<> Str trace<Bb>() {return "Bb";}
    template<> Str trace<Y>() {return "Y";}
    template<> Str trace<Id>() {return "Id";}
    template<> Str trace<Flip>() {return "Flip";}
    template<> Str trace<Pair>() {return "Pair";}
    template<> Str trace<Fst>() {return "Fst";}
    template<> Str trace<Snd>() {return "Snd";}

    template<> Str trace<True>() {return "True";}
    template<> Str trace<False>() {return "False";}
    template<> Str trace<Not>() {return "Not";}
    template<> Str trace<And>() {return "And";}
    template<> Str trace<Or>() {return "Or";}
    template<> Str trace<BEq>() {return "BEq";}
    template<> Str trace<T>() {return "T";}
    template<> Str trace<Const>() {return "Const";}

    template<> Str trace<Succ>() {return "Succ";}
    template<> Str trace<Add>() {return "Add";}
    template<> Str trace<Mult>() {return "Mult";}
    template<> Str trace<Pow>() {return "Pow";}
    template<> Str trace<N0>() {return "N0";}
    template<> Str trace<N1>() {return "N1";}
    template<> Str trace<N2>() {return "N2";}
    template<> Str trace<N3>() {return "N3";}
    template<> Str trace<N4>() {return "N4";}
    template<> Str trace<N5>() {return "N5";}
    template<> Str trace<N6>() {return "N6";}
    template<> Str trace<N7>() {return "N7";}
    template<> Str trace<N8>() {return "N8";}
    template<> Str trace<N9>() {return "N9";}
    template<> Str trace<Is0>() {return "Is0";}
    template<> Str trace<Phi>() {return "Phi";}
    template<> Str trace<Pred>() {return "Pred";}
    template<> Str trace<Sub>() {return "Sub";}
    template<> Str trace<Zero>() {return "Zero";}

    template<> Str trace<Cons>() {return "Cons";}
    template<> Str trace<Nil>() {return "Nil";}
    template<> Str trace<Head>() {return "Head";}
    template<> Str trace<Tail>() {return "Tail";}
    template<> Str trace<Null>() {return "Null";}
    template<> Str trace<Drop>() {return "Drop";}
    template<> Str trace<Concat>() {return "Concat";}
    template<> Str trace<Length>() {return "Length";}
    template<> Str trace<Index>() {return "Index";}
    template<> Str trace<Last>() {return "Last";}
    template<> Str trace<Init>() {return "Init";}
    template<> Str trace<Reverse>() {return "Reverse";}
    template<> Str trace<NatsN>() {return "NatsN";}
    template<> Str trace<Nats>() {return "Nats";}
    template<> Str trace<TakeR>() {return "TakeR";}
    template<> Str trace<Take>() {return "Take";}
    template<> Str trace<Range>() {return "Range";}
    template<> Str trace<Map>() {return "Map";}
    template<> Str trace<Filter>() {return "Filter";}
    template<> Str trace<FoldL>() {return "FoldL";}
    template<> Str trace<FoldR>() {return "FoldR";}

    // template<> Str trace<>() {return "";}

    template<typename... OO>            struct Names          {static inline Str names() {return "";};};
    template<typename O,typename... OO> struct Names<O,OO...> {static inline Str names() {return trace<O>()+"->"+Names<OO...>::names();};};
    template<typename O>                struct Names<O>       {static inline Str names() {return trace<O>();};};
    template<>                          struct Names<>        {static inline Str names() {return "";};};

    template<typename O>
    void Show() {
      std::cout<<trace<O>()<<" => "<<trace<typename O::App>()<<std::endl;
    }

  }//λ
#endif
