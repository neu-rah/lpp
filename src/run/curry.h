/* -*- C++ -*- */
#pragma once
/*Rui Azevedo (neu-rah) ruihfazevedo@gmail.com Oct2019*/
////////////////////////////////////////////////////////////////////////////////
// Currying C++ functions //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "../lpp.h"

namespace rlambda {

  //runtime curry
  //this will turn a C++ funtime function into its a curryed version

  //adapted from: https://gist.github.com/qnighy/496866
  template<typename Func,int cnt>
  struct CurryFunction {
      Func f;
      template<typename... Args>
      inline auto operator()(Args... args) -> decltype(f(args...)) {
          return f(args...);
      }
      template<typename FArg>
      struct Binder {
          Func f;
          FArg farg;
          template<typename... Args>
          inline auto operator()(Args... args) -> decltype(f(farg, args...)) {
              return f(farg, args...);
          }
          inline Binder(const Func& f, const FArg farg) : f(f), farg(farg) {}
      };
      template<typename FArg>
      inline CurryFunction<Binder<FArg>,cnt-1> operator()(FArg farg) {return CurryFunction<Binder<FArg>,cnt-1>(Binder<FArg>(f,farg));}
      template<typename A, typename B, typename... Args>
      void operator()(A a, B b, Args... args) = delete;
      inline CurryFunction(const Func& f) : f(f) {}
  };

  template<typename Func>
  struct CurryFunction<Func,0> {
    Func f;
    template<typename... Args>
    inline auto operator()(Args... args) -> decltype(f(args...)) {
        return f(args...);
    }
    template<typename FArg>
    struct Binder {
        Func f;
        FArg farg;
        template<typename... Args>
        inline auto operator()(Args... args) -> decltype(f(farg, args...)) {
            return f(farg, args...);
        }
        inline Binder(const Func& f, const FArg farg) : f(f), farg(farg) {}
    };
    template<typename FArg>
    inline auto operator()(FArg farg)->decltype(CurryFunction<Binder<FArg>,0>(Binder<FArg>(f,farg))()) {
      CurryFunction<Binder<FArg>,0>(Binder<FArg>(f,farg))();
    }
    template<typename A, typename B, typename... Args>
    void operator()(A a, B b, Args... args) = delete;
    inline CurryFunction(const Func& f) : f(f) {}
  };

  template<typename F>struct FuncInfo{
    using Func=F;
  };
  template<typename R,typename O,typename... OO>
  struct FuncInfo<R(*)(O,OO...)>{
    using Ret=R;
    using Func=R(*)(O,OO...);
    using Args=lambda::List<O,OO...>;
    constexpr static size_t argc=lambda::toInt<lambda::Expr<lambda::Length,Args>>();
  };

  template<typename Func>
  inline CurryFunction<Func,FuncInfo<Func>::argc-1> curry(const Func& f) {
    return CurryFunction<Func,FuncInfo<Func>::argc-1>(f);
  }

};//rλ
