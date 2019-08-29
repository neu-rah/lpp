# <λ++>
#### type-level lazy untyped lambda for C++

this is pure compile time, so data here are C++ types

inspired by the excellent videos of @glebec (https://youtu.be/3VQ382QG-y4) (thank you!)

**Scope**  
This idiom uses lambda calculus as its background on a close cope with c++ templates.
It only operates at compile time.  
Results is normal form translate to C++ types (native or user defined).  
So this expressions can only be used in replacement of C++ types.  
A layer to provide `constexpr` values is provide through dependent types.
It is therefor a turing-complete idiom to decide types at compile time.

**Some examples:**  
```c++
Float::Type phi=1.618;
```
```c++
using MCU_8BITS=True;
using idx_t=MCU_BITS::Bind<As<uint8_t>>::Bind<Int>::App::Type;
//alternative syntax:
using sz_t=Expr<MCU_8BITS,As<uint8_t>,Int>::App::Type;
//syntactic sugar
using port_t=If<MCU_8BITS>::Then<Char>::Else<Int>::App::Type;
```

## A language to manipulate types

### Partial application

Using a _curry_ template that can turn any c++ template of types into a curryed version, adding ::Bind member types. This also reduces the original template to a single type, making it possible to compose and combine them again in new operations.

Just because non-curryed version are so easy to write in C++, but we absolutely need them currying.

Function application is **Lazy**.

### lambda 'standard' terms (combinators)
|name|lambda|description|
|--- |--- |--- |
|I |_λx.x_ |Identity|
|M |_λf.ff_|Self application|
|K |_λab.a_|first = functional boolean True|
|KI |_λba.a_|second = functional boolean false|
|C |_λfab.fba_|flip = functional negation|
|B |_λfgo.f(g o)_|function composition|
|V |_λabf.fab_|pair = functional data structure|
|V |_λabf.fab_|pair = functional data structure|
|Y |_λf.(λo.f(o o)) (λo.f(o o))_ |Recursion|

### Functions

`Id o` - identity

`Flip f a b` - swap 2 arguments of a given function _`f a b -> f b a`_

`Pair a b f` - data constructor, holds a pair of 2 types to deliver them later to the reader function `f` _`(Pair a b) f -> f a b`_

`Fst p` - get the first of a pair `p`

`Snd p` - get the second of a pair `p`

### Types

provides a c++ primitive type wrapper

**As<** _type_ **>**

extract with `::Type`

### use C++ dependent types

**StaticValue<** _type_ **,** _value_ **>**

extract with `::value()` static function

note: _can only host `constexpr` values_

**StaticText<** _pointer to some static text_ **>**  
a specialization for handling strings as dependent types in C++11

#### C++ constexpr functions
**curry<** _«return type»_, _«func. type»_, _«func. ptr»_, _«nr of arguments»_, _[«bounded arguments type list...»]_ **>**

_(**this is an experimental feature** expect heavy changes)_.

transform a C++ constexpr returning function into a lambda curried function that can be used as a lambda term.

```c++
//define
inline int _test(int a,int b) {return a*b;}
using test=curry<int,decltype(&_test),_test,2>;

//use
cout<<"call c++ function test(3,5) "<<test::Bind<StaticValue<int,3>>::Bind<StaticValue<int,5>>::value()<<endl;
cout<<"call c++ function Expr<test,3,5> "<<Expr<test,StaticValue<int,3>,StaticValue<int,5>>::value()<<endl;
```

### Logic

implemented operators `And`, `Or`, `Not`, `BEq` (boolean equality) along with functional boolean versions `True` and `False`

### Numerals

`N0` .. `N9` for convenience

`Succ n` get the successor of numeral `n`

`Pred n` get the predecessor of numeral `n`

`Is0 n` check if numeral `n` is zero

#### Peano

using Peano numbers to convert Numeral to constexpr values

**toInt<** _type_ **>**() a convenience to print numerals

numerals will yield the corresponding value

#### Arithmetic (with numerals)

`Add a b` a+b

`Sub a b` a-b

`Mul a b` a*b

`Pow b e` b^e

`Fact n` n!

#### Relational operators (for numerals)

`Eq`, `LEq`, `GEq`, `LT`, `GT`, `NEq`

#### Lists

`Nil` empty list.

`Cons h t` use `o` as list `t` head

`Head l` get list `l` first element (fails compilation if empty).

`Tail l` get list `l` tail, yields empty list when empty.

`Null l` check if `l` is empty.

`Drop n l` drops first `n` (as numeral) elements from the list `l`

`Concat a b` join to lists

`Length l` length of a list

`Index l i` get liost element by index/composition

`Last l` get last element of list or Nil

`Init l` list without last element

`Reverse` reverse a finite list

`NatsN n` numerals infinite list starting at `n`

`Nats` numerals infinite list starting at `N1`

`TakeR n l` take n elements of a list in reverse order

`Take n l` take n elements of a list

`Range s e` list of numerals from `s` to `e`

`Map f l` map a function `f` over list `l`

`Filter f l` filter a list `l` with function `f`

`FoldL f n l` fold left a list `l` using 'binary' function `f` starting with `n`

`FoldL f n l` right fold a list `l` using 'binary' function `f` starting with `n`

**List<** _elements[,..]_ **>**  
utility to construct lists as:
```c++
using L1=List<A,B,C>;
using same_as_L1=Const::Bind<A>::Bind<Const::Bind<B>::Bind<Const::Bind<C>::Bind<Nil>>>;
using or_this_way=Expr<Cons,A,Expr<Cons,B,Expr<Cons,C,Nil>>>;
```

### The <λ++> core

<script src="https://gist.github.com/neu-rah/ad35d9c41c75c5eece704dfcf033fb62.js"></script>

### References

Lambda Calculus  
http://www.allisons.org/ll/FP/Lambda/

Collected Lambda Calculus Functions  
https://jwodder.freeshell.org/lambda.html

Lambda Calculus Examples  
http://users.monash.edu/~lloyd/tildeFP/Lambda/Examples/

Lazy or Eager? Order of Evaluation in Lambda Calculus and OCaml - The Always Learning Marty  
https://thealmarty.com/2018/09/03/lazy-or-eager-order-of-evaluation-in-lambda-calculus-and-ocaml/

Lambda the Ultimate | Programming Languages Weblog  
http://lambda-the-ultimate.org/

lists.lam  
http://languagemachine.sourceforge.net/lists.html

Lambda calculus definition  
https://en.wikipedia.org/wiki/Lambda_calculus_definition

Fixed-point combinator  
https://en.wikipedia.org/wiki/Fixed-point_combinator
