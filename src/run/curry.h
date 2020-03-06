/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Oct2019*/
////////////////////////////////////////////////////////////////////////////////
// Currying C++ functions //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "../lpp.h"

namespace rlambda {

  // template<typename F>
  // struct Info {};

  template<typename R,typename... OO>
  struct Info {using App=R;};

  // template<typename F>
  template<typename R,typename... OO>
  Info<R,OO...> info(R(*f)(OO...)) {return Info<R,OO...>();}

  template<typename P,typename O,typename... OO> struct RC;

  template<typename F,F& f,typename O,typename... OO>
  struct RCurry {
    using This=RCurry<F,f,O,OO...>;
    O o;
    using App=typename decltype(info(f))::App;
    RC<This,OO...> operator()(O _o) {o=_o;return RC<This,OO...>(*this);}
    auto app(OO... oo)->decltype(f(o,oo...)) {return f(o,oo...);}
  };

  template<typename F,F& f,typename O>
  struct RCurry<F,f,O> {
    using App=typename decltype(info(f))::App;
    auto operator()(O o)->decltype(f(o)) {return f(o);}
  };

  template<typename P,typename O,typename... OO>
  struct RC {
    using This=RC<P,O,OO...>;
    O o;
    P prev;
    RC(P p):prev(p) {}
    RC<This,OO...> operator()(O _o) {o=_o;return RC<This,OO...>(*this);}

    auto app()->decltype(prev.app(o)) {return prev.app(o);}
  };

  template<typename P,typename O>
  struct RC<P,O> {
    using This=RC<P,O>;
    P prev;
    RC(P p):prev(p) {}
    auto operator()(O o)->decltype(prev.app(o)) {return prev.app(o);}
  };

};//rλ
