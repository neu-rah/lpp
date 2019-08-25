#include "base.h"
#include "lpp_debug.h"
#include <string>

using namespace lambda;

template<template<typename...> class F,int n, typename... OO>
std::string Name<F,n,OO...>::name() {
  std::string res=trace<Curry<F,n+Count<OO...>::value()>>();
  res+="("+Names<OO...>::names();
  if (n) res+=" {+"+std::to_string(n)+"}";
  return res+")";
}
