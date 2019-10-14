/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
#ifdef ARDUINO
  using Str=String;
#else
  #include <string>
  #include <iostream>
  using Str=std::string;
#endif

namespace lambda {

  template<typename... OO>            struct Count          {static inline constexpr size_t value() {return -1;};};
  template<typename O,typename... OO> struct Count<O,OO...> {static inline constexpr size_t value() {return Count<OO...>::value()+1;};};
  template<>                          struct Count<>        {static inline constexpr size_t value() {return 0;};};

  template<template<typename...> class F,int n, typename... OO>
  struct Name {
    static Str name();
  };

}//λ
