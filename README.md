# <λ++>
#### turing-complete idiom to express types in C++

[![Build Status](https://travis-ci.com/neu-rah/lpp.svg?branch=master)](https://travis-ci.org/neu-rah/lpp)
[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.me/ruihfazevedo)
[![License: MIT](https://img.shields.io/github/license/neu-rah/lpp)](https://spdx.org/licenses/MIT.html)

Based on lambda calculus, therefor using functional paradigm on top of modern C++ metaprogramming. Expressions on this idiom are metaprogramming and evaluate at compile time, yelding C++ types as a result.  

inspired by the excellent videos of @glebec (https://youtu.be/3VQ382QG-y4) (thank you!)

### Scope  
This idiom uses lambda calculus as its background on a close cope with c++ templates.
It only operates at compile time.  
Results in β normal form translate to C++ types (native or user defined).  
So this expressions can only be used in replacement of C++ types.  
A layer to provide `constexpr` values is available through dependent types.
It is therefor a turing-complete idiom to decide types at compile time.
Types have to be extracted after expression evaluation (::App) to yeld valid C++ types.
Using Lazyness, static immutable "data" (here expressed as c++ types) and partial application.

## lambda base

lambda calculus base [lambda core doc.](./LAMBDA.md)

## lpp

This is an attempt to make lambda more usable.

 `Head<List>` looks much better that `Expr<Head,L2>::App`

[LPP doc.](./LPP.md)

## r-lambda

RCurry (runtime curry)
turns regular c++ functions into curry versions.

A C++ function that accepts lets say 2 arguments `a` and `b`, and returns `c` is then turned into a function that accepts one argument `a` and return a second function that accepts `b` and returns `c` (considering the previous `a`).

_curry is the only part implemented, and still testing. No lambda calculus yet_

```c++
auto f=RCurry<decltype(_f),_f,int,int>();
```

Thus the call of `_f(a,b)` can now be `f(a)(b)`

**evaluation order**  
right-most function requiring arguments have priority

```c++
#include <iostream>
using namespace std;

#include <r-lambda.h>//runtime lambda core
using namespace rlambda;

template<typename I>
inline I _id(I i) {return i;}//original
template<typename I>
auto id=RCurry<decltype(_id<I>),_id,I>();//curry version

int _d(int x){return x<<1;}//original
auto d=RCurry<decltype(_d),_d,int>();//curry version

int _m(int x,int y){return x*y;}//original
auto m=RCurry<decltype(_m),_m,int,int>();//curry version

int main(int argc, char **argv) {
  cout<<d(2)<<endl;
  cout<<m(2)(3)<<endl;
  auto x=d(d);
  cout<<x(2)<<endl;
  cout<<id<int>(d)(1967)<<endl;
  cout<<m(d)(5)(3)<<endl;
  cout<<d(m)(2)(3)<<endl;
  cout<<m(5)(d)(3)<<endl;
  cout<<d(m)(10)(2)<<endl;
  cout<<d(m(10))(2)<<endl;//same as above
  cout<<d(m)(5)(m)(3)(2)<<endl;
  return 0;
}
```
