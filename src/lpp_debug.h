/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
#include <string>
#include "base.h"
#include "types.h"
#include "lambda.h"
#include "curry.h"
#include "logic.h"

namespace lambda {
  template<typename O> std::string trace() {return O::name();}
  template<> std::string trace<Char>() {return "Char";}
  template<> std::string trace<Int>() {return "Int";}
  template<> std::string trace<Float>() {return "Float";}
  template<> std::string trace<String>() {return "String";}

  template<> std::string trace<I>() {return "I";}
  template<> std::string trace<M>() {return "M";}
  template<> std::string trace<K>() {return "K";}
  template<> std::string trace<KI>() {return "KI";}
  template<> std::string trace<C>() {return "C";}
  template<> std::string trace<B>() {return "B";}
  template<> std::string trace<V>() {return "V";}
  template<> std::string trace<Bb>() {return "Bb";}
  template<> std::string trace<Id>() {return "Id";}
  template<> std::string trace<Flip>() {return "Flip";}
  template<> std::string trace<Pair>() {return "Pair";}
  template<> std::string trace<Fst>() {return "Fst";}
  template<> std::string trace<Snd>() {return "Snd";}

  template<> std::string trace<True>() {return "True";}
  template<> std::string trace<False>() {return "False";}
  template<> std::string trace<Not>() {return "Not";}
  template<> std::string trace<And>() {return "And";}
  template<> std::string trace<Or>() {return "Or";}
  template<> std::string trace<BEq>() {return "BEq";}
  template<> std::string trace<T>() {return "T";}
  template<> std::string trace<Const>() {return "Const";}

  template<> std::string trace<Succ>() {return "Succ";}
  template<> std::string trace<Add>() {return "Add";}
  template<> std::string trace<Mult>() {return "Mult";}
  template<> std::string trace<Pow>() {return "Pow";}
  template<> std::string trace<N0>() {return "N0";}
  template<> std::string trace<N1>() {return "N1";}
  template<> std::string trace<N2>() {return "N2";}
  template<> std::string trace<N3>() {return "N3";}
  template<> std::string trace<N4>() {return "N4";}
  template<> std::string trace<N5>() {return "N5";}
  template<> std::string trace<Is0>() {return "Is0";}
  template<> std::string trace<Phi>() {return "Phi";}
  template<> std::string trace<Pred>() {return "Pred";}
  template<> std::string trace<Sub>() {return "Sub";}
  template<> std::string trace<Zero>() {return "Zero";}

  // template<> std::string trace<>() {return "";}

  template<typename... OO>            struct Names          {static inline std::string names() {return "";};};
  template<typename O,typename... OO> struct Names<O,OO...> {static inline std::string names() {return trace<O>()+","+Names<OO...>::names();};};
  template<typename O>                struct Names<O>       {static inline std::string names() {return trace<O>();};};
  template<>                          struct Names<>        {static inline std::string names() {return "";};};

  template<typename O>
  void Show() {
    cout<<trace<O>()<<" => "<<trace<typename O::App>()<<endl;
  }
}//λ
