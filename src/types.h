/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Aug2019*/
////////////////////////////////////////////////////////////////////////////////
//Native type wraper ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
namespace lambda {
  template<typename O> struct As {
    template<typename> using Bind=As<O>;
    using App=As<O>;
    using Type=O;
  };
  //wraping C++ types
  using Char=As<char>;
  using Int=As<int>;
  using Float=As<float>;
  using String=As<const char*>;
};//λ
