# <λ++>
#### type-level lambda for C++

[![Build Status](https://travis-ci.org/neu-rah/lpp.svg?branch=master)](https://travis-ci.org/neu-rah/lpp)

**this is an experimental project. so, please share your thoughts**

lambda calculus for C++ types, this is pure compile time, so data here are C++ types

inspired by the excellent videos of @glebec (https://youtu.be/3VQ382QG-y4) (thank you!)

```c++
Float::Type phi=1.618;
```

```c++
using MCU_8BITS=True;
using idx_t=MCU_BITS::Bind<As<uint8_t>>::Bind<Int>::Type;
//alternative syntax:
using sz_t=Expr<MCU_8BITS,As<uint8_t>,Int>::Type;
```

## A language to manipulate types

### Partial application

Using a _curry_ template that can turn any c++ template of types into a curryed version adding ::Bind member types, this also reduces the original template to a single type, making it possible to compose and combine them again in new operations.

Just because non-curryed version are so easy to write in C++, but we absolutely need them currying.

### lambda 'standard' terms
|name|lambda|description|
|--- |--- |--- |
|I |_λx.x_ |Identity|
|M |_λf.ff_|Self application|
|K |_λab.a_|first = functional boolean True|
|KI |_λba.a_|second = functional boolean false|
|C |_λfab.fba_|flip = functional negation|
|B |_λfgo.f(g o)_|function composition|
|V |_λabf.fab_|pair = functional data structure|

### Functions

Id - identity

Flip - swap 2 arguments of a given function

Pair - (static) data constructor, holds a pair of 2 types

Fst - get the first of a pair

Snd - get the second of a pair

### Types

provides a c++ primitive type wrapper

**As<**_type_**>**

extract with `::Type`

### use C++ dependent types

**Value<**_type_**,**_value_**>**

extract with `::Value`

### Logic

implemented operators And, Or, Not, booleans and BEq (boolean equality)

### Numerals

N0..N5 for convenience

**Succ<**_numeral_**>** get the successor or a numeral

**Pred<**_numeral_**>** get the predecessor of a numeral

**Is0<**_numeral_**>** check if numeral is zero

#### Peano

using Peano numbers to convert Numeral to constexpr values

**toInt<**_type_**>**() a convenience to print numerals

numerals will yield the corresponding value

#### Arithmetic

Add, Sub, Mul, Pow

#### Relational operators

Eq, LEq, GEq, LT, GT, NEq
