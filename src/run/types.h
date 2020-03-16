/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
//Native type/value wraper ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "../compile/types.h"
using namespace lambda;

namespace rlambda {

  template<typename O>
  struct rAs:lambda::As<O> {
    O o;
    inline rAs(O o):o(o) {}
    inline O operator()() const {return o;}
    inline operator O() const {return o;}
    using Type=O;
    using Res=O;
  };

  //wraping C++ types/values
  using rChar=rAs<char>;
  using rInt=rAs<int>;
  using rFloat=rAs<float>;
  using rStr=rAs<const char*>;
};//λ
