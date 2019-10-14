#include "base.h"
#ifdef LPP_DEBUG
  #include "lpp_debug.h"
  #include <string>

  namespace lambda {
    template<template<typename...> class F,int n, typename... OO>
    Str Name<F,n,OO...>::name() {
      Str res="("+trace<Curry<F,n+Count<OO...>::value()>>();
      res+="::"+Names<OO...>::names();
      #ifdef ARDUINO
        if (n) res+="->{+"+Str(n)+"}";
      #else
        if (n) res+="->{+"+std::to_string(n)+"}";
      #endif
      return res+")";
    }
  };
#endif
