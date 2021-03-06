/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Oct2019*/
////////////////////////////////////////////////////////////////////////////////
// Currying C++ functions //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "../lpp.h"
using namespace lpp;

namespace rlambda {

  template<int n,typename P,typename O,typename... OO> struct RC;
  template<int n,typename P,typename B> struct _RC;

  template<typename F,F& f,typename O,typename... OO>
  struct RCurry {
    using This=RCurry<F,f,O,OO...>;
    using Want=O;
    static constexpr int miss=toInt<Length<List<O,OO...>>>();

    template<typename R>
    _RC<R::miss,This,R> operator()(const R& r) const
      {return _RC<R::miss,This,R>(*this,r);}

    // template<typename R,R& r>
    // _RC<R::miss,This,R> operator()() const
    //   {return _RC<R::miss,This,R>(*this,r);}

    RC<miss-1,This,OO...> operator()(O o) const {return RC<miss-1,This,OO...>(*this,o);}

    auto app(O o,OO... oo) const ->decltype(f(o,oo...)) {return f(o,oo...);}
    auto app(O o) const ->decltype(operator()(o)) {return operator()(o);}
  };

  template<typename F,F& f,typename O>
  struct RCurry<F,f,O> {
    using This=RCurry<F,f,O>;
    using Want=O;
    static constexpr int miss=1;

    auto operator()(O o) const ->decltype(f(o)) {return f(o);}

    template<typename R,R r>
    _RC<R::miss,This,R> operator()() const
      {return _RC<R::miss,This,R>(*this,r);}

    template<typename R>
    _RC<R::miss,This,R> operator()(const R& r) const
      {return _RC<R::miss,This,R>(*this,r);}

    auto app(O o) const ->decltype(operator()(o)) {return operator()(o);}
  };

  template<int n,typename P,typename O,typename... OO>
  struct RC {
    static constexpr int miss=n;
    using This=RC<miss,P,O,OO...>;
    using Want=O;
    using Bound=typename P::Want;
    const P prev;
    const Bound bound;
    inline RC(const P p,const Bound o):prev(p),bound(o) {}

    RC<miss-1,This,OO...> operator()(O o) const {return RC<miss-1,This,OO...>(*this,o);}

    template<typename R>
    _RC<R::miss,This,R> operator()(const R& r) const
      {return _RC<R::miss,This,R>(*this,r);}

    template<typename... Args>
    auto app(Args... args) const ->decltype(prev.app(bound,args...)) {return prev.app(bound,args...);}
  };

  template<typename P,typename O>
  struct RC<1,P,O> {
    static constexpr int miss=1;
    using This=RC<1,P,O>;
    using Want=O;
    using Bound=typename P::Want;
    const P prev;
    const Bound bound;
    inline RC(const P& p,const Bound o):prev(p),bound(o) {}

    auto operator()(const O o) const
      ->decltype(prev.app(bound,o))
      {return prev.app(bound,o);}

    template<typename R>
    _RC<R::miss,This,R> operator()(const R& r) const
      {return _RC<R::miss,This,R>(*this,r);}

    auto app(O o) const ->decltype(prev.app(bound,o)) {return prev.app(bound,o);}
  };

  template<int n,typename P,typename B>
  struct _RC {
    static constexpr int miss=n;
    using This=_RC<miss,P,B>;
    using Bound=B;
    const P prev;
    const Bound bound;
    using Want=typename B::Want;

    inline _RC(const P& p,const Bound o):prev(p),bound(o) {}

    template<typename=void>
    auto operator()(Want o) const
      ->decltype(_RC<miss-1,This,decltype(bound(o))>(*this,bound(o)))
      {return    _RC<miss-1,This,decltype(bound(o))>(*this,bound(o));}

    auto app(Want o) const ->decltype(prev(o)) {return prev(o);}

    template<typename R>
    auto operator()(const R& r) const
      ->decltype(_RC<R::miss,This,R>(*this,r))
      {return    _RC<R::miss,This,R>(*this,r);}
  };

  template<typename P,typename B>
  struct _RC<1,P,B> {
    using This=_RC<1,P,B>;
    using Bound=B;
    const P prev;
    const Bound bound;
    using Want=typename B::Want;

    inline _RC(const P& p,const Bound o):prev(p),bound(o) {}

    auto operator()(Want o) const
      ->decltype(prev.app(bound(o)))
      {return prev.app(bound(o));}

    template<typename R>
    auto operator()(const R& r)->decltype(_RC<R::miss,This,R>(*this,r)) const
      {return _RC<R::miss,This,R>(*this,r);}

    auto app(Want o) const ->decltype(prev.app(bound(o))) {return prev.app(bound(o));}
  };


};//rλ
