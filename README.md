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

### Some examples:
```c++
Float::Type phi=1.618;
```
extracting the C++ type `float` with `::Type`

conditional type decision without macros, it not only typecheck, as it also can be encapsulated as a regular C++ type definition.  
This decision is made at compile time, no extra burden on executable.
```c++
using MCU_8BITS=True<>;
using idx_t=MCU_8BITS<Char,Int>::App::Type;
```
or
```c++
using MCU_8BITS=True<>;
using idx_t=if<MCU_8BITS>::Then<Char>::Else<Int>::App::Type;
```

## Curried templates

Lambda functions are C++ templates.

All template/functions can appear with 0 or n elements up to the maximum allowed by the function definition. It is not a syntax error to provide more.

templates with incomplete arguments lists are considered partial applyed lambda functions that can be passed around or complemented with `::Bind`

example:
```c++
True<> //functionl boolean lambda function (with no arguments)
True<Int> //lambda function with one argument bound, awaiting more arguments
True<Int>::Bind<Float> //late binding of second argument
True<Int,Float> //fully satisfied lambda function/c++ template
```

## Functions

#### Id
`Id<o>` identity function

returns given object `o`

#### Flip
`Flip<f,a,b>` call function `f` with swapped arguments `f<b,a>`

#### Const
`Const<o,_>` constant `o` function

when complete (given second argument) it will return the first one `o`

#### Pair
`Pair<a,b,f>` functional data structure

```c++
using X=Pair<Int,Float>;//store "data" (2 types)
using Result=X ReaderFunction;//will call `ReaderFunction<Int,Float>
```

this "data" structure is used to build lists

#### Fst
`Fst<p>` get first element of a pair `p`

#### Snd
`snd<p>` get second element of a pair `p`

### Logic

#### True
`True<a,b>` functional boolean True

returns `a`

#### False
`False<a,b>` functionl boolean False

returns `b`

#### Not
`Not<f>` functional negation (same as `Flip`)

beware that negating relational operators does not negate the equality relation because this is an ealy negation, notg a lete negation as normal booleans.

#### And
`And<a,b>` logical conjunction

#### Or
`Or<a,b>` logical disjunction

#### BEq
`BEq<a,b>` boolean equality.

### Numerals and arithmetic

#### N
`N<size_t>` create a numeral based on a C++ `size_t`

Ex: `N<111>`

#### Succ
`Succ<n>` return the sucessor of the numeral `n`

#### Pred
`Pred<n>` return the predecessor of the numeral `n`

#### Add
`Add<a,b>` add two numerals `a+b`

#### Sub
`Sub<a,b>` subtract two numerals `a-b`

#### Mult
`Mult<a,b>` multiply two numerals `a*b`

#### Pow
`Pow<a,b>` exponential function `a^b`

#### Is0
`Is0<n>` Check if numeral `n` is zero (`N<0>`)

returns a boolean

### Lists

#### Nil
`Nil` empty list

#### Cons
`Cons<h,t>` insert element `h` into `t` list.

#### Head
`Head<l>` return first element of a list

#### Tail
`Tail<l>` return list `l` with first element removed

#### Null
`Null<l>` check if list `l` is empty

#### Drop
`Drop<n,l>` drop `n` elements from list `l`

#### Concat
`Concat<a,b>` concatenate two list into a new one.

#### Length
`Length<l>` get the length of a list

#### Index
`Index<l,n>` get nth element from a list

#### Last
`Last<l>` get last element of a list

#### Init
`Init<l>` get list with last element removed

#### Reverse
`Reverse<L>` get list with elements in reverse order

#### Nats
`Nats` just an infinite list of natural numerals `[1..]`

#### Range
`Range<s,e>` a list of numerals ranging from `s` to `e`

#### Map
`Map<f,l>` map a function `f` over a list

the result is a list where elements are the result of application of function `f` to each element of the original.

`[a,b,..] => [f a,f b,..]`

#### Filter
`Filter<f,l>` filter list elements using function `f`

function `f` should return True for each element that should be included on the result or False otherwise.

#### FoldL
`FoldL<f,i,l>`  fold a list (from left to write) applying function binary `f` to the initial value and repeating the process to the rest of the list with the function result as initial.

#### FoldL
`FoldR<f,i,l>` same as `FoldL` but starting from the last element of the list.


### Adding new functions

function can be added by aliasing expressions

```c++
using Resolution=Pow<N<2>>;
```

here `Resolution` will be a numeral of `2^` to an yet unspecified value.

You can define new functions.

first start by building the final non-curried C++ template to hold your function in lambda namespace.

then use `Curry` template to turn it into a simple type (not template) with a ::Bind member to bind the arguments

eventually use macro `LPP` to import your curried type as a C++ variadic template into the lpp namespace.

```c++
namespace lambda {
  template<typename A,typename B>
  using _MyFunction=
    typename If<SOME_STATIC_CONFIG>
    ::template Then<A>
    ::template Else<Sub<Pow<N<2>,B>,N<1>>>;
  using MyFunction=lambda::Curry<_MyFunction,2>;//define a curried version of the function
};
LPP(MyFunction);//import function as variadic template

//then one can use the function
using x=MyFunction<N<1023>,N<12>>;
```

note: if you need to implement more primitive functions, use struct or class instead of a simple alias.
In that case you must provide an ::App member that will effectively provide the evaluation result.

see the lambda core for examples.

## Syntactic sugar

#### If
`If<condition>::Then<result>::Else<result>` if expression

#### List
`List<...>` build a list with given types

#### Expr
`Expr<...>` build a lambda expression with given expressions

#### ::Bind
`f::Bind<t>` late binding of a parameter `t` to partially applyed function `f`

#### toInt
`toInt<n>()` constexpr function to extract a `size_t` value from a numeral `n`

```c++
cout<< toInt<Length<L1>::App>() <<endl;
```

## More info
[lambda core](./LAMBDA.md)

some more info abot the lambda core powering this idiom.
