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

lambda calculus base [lambda core](./LAMBDA.md)

## lpp

This is an attempt to make lambda more usable... not very practical yet.

 [lambda core](./LPP.md)
