/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Oct2019*/
////////////////////////////////////////////////////////////////////////////////
// Currying C++ functions //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// #include "../compile/curry.h"
// #include "../compile/numerals.h"
// #include "../compile/dependent.h"
// #include "../compile/list.h"
// using namespace lambda;

#include "../lpp.h"
using namespace lpp;

namespace rlambda {

  template<int need,typename P,typename O,typename... OO> struct RC;
  template<int need,typename P,typename B> struct _RC;

  template<typename F,F& f,typename O,typename... OO>
  struct _RCurry {
    using This=_RCurry<F,f,O,OO...>;
    using Want=O;
    using Need=Length<List<O,OO...>>;
    static constexpr int need=toInt<Need>();

    template<typename R>
    _RC<R::need-1,This,R> operator()(R& r)
      {return _RC<need-1,This,R>(*this,r);}

    RC<need-1,This,OO...> operator()(O o) {return RC<need-1,This,OO...>(*this,o);}

    auto app(O o,OO... oo)->decltype(f(o,oo...)) {return f(o,oo...);}
  };

  template<typename F,F& f,typename O>
  struct _RCurry<F,f,O> {
    using This=_RCurry<F,f,O>;
    using Want=O;
    using Need=Length<List<O>>;
    static constexpr int need=1;
    auto operator()(O o)->decltype(f(o)) {return f(o);}
    template<typename R>
    _RC<need-1,This,R> operator()(R& r)
      {return _RC<need-1,This,R>(*this,r);}
  };

  template<int need,typename P,typename O,typename... OO>
  struct RC {
    using This=RC<need,P,O,OO...>;
    using Want=O;
    P prev;
    using Bound=typename P::Want;
    Bound bound;
    inline RC(P p,Bound o):prev(p),bound(o) {}

    RC<need-1,This,OO...> operator()(O o) {return RC<need-1,This,OO...>(*this,o);}

    template<typename R>
    _RC<R::need,This,R> operator()(R r)
      {return _RC<R::need,This,R>(*this,r);}

    template<typename... Args>
    auto app(Args... args)->decltype(prev.app(bound)) {return prev.app(bound,args...);}
  };

  template<typename P,typename O>
  struct RC<1,P,O> {
    using This=RC<1,P,O>;
    P prev;
    using Bound=typename P::Want;
    Bound bound;
    inline RC(P& p,Bound o):prev(p),bound(o) {}

    auto operator()(O o)
      ->decltype(prev.app(bound,o))
      {return prev.app(bound,o);}

    template<typename R>
    _RC<R::need,This,R> operator()(R r)
      {return _RC<1,This,R>(*this,r);}
  };

  template<int need,typename P,typename B>
  struct _RC {
    using This=_RC<need,P,B>;
    P prev;
    using Bound=B;
    Bound bound;
    using Want=typename B::Want;

    inline _RC(P& p,Bound o):prev(p),bound(o) {}

    auto operator()(Want o)->decltype(prev(o)) {return prev(o);}

    template<typename R>
    auto operator()(R& r)->decltype(_RC<R::need,This,R>(*this,r))
      {return _RC<R::need,This,R>(*this,r);}
  };

  template<typename P,typename B>
  struct _RC<1,P,B> {
    using This=RC<1,P,B>;
    P prev;
    using Bound=B;
    Bound bound;
    using Want=typename B::Want;

    inline _RC(P& p,Bound o):prev(p),bound(o) {}

    auto operator()(Want o)->decltype(prev(o)) {return prev(o);}

    template<typename R>
    auto operator()(R& r)->decltype(_RC<R::need,This,R>(*this,r))
      {return _RC<1,This,R>(*this,r);}
  };
};//rλ
