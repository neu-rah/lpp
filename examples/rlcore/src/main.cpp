#include <iostream>
using namespace std;

#include <r-lambda.h>//runtime lambda core
using namespace rlambda;

/*
RCurry (runtime curry)
turns regular c++ functions into curry versions
a c++ function that accepts lets say 2 arguments `a`,`b` and return `c`
is then turned into a function that accepts one argument a,
and return a second function that accepts `b` and returns `c` (considering the previous `a`)

*/

// template<typename F,F& f> struct Func {};

//(constexpr => they are known at compile time)------------------------
//turn a template function into a curried one
template<typename I>
inline I _id(I i) {return i;}
template<typename I>
constexpr auto id=RCurry<decltype(_id<I>),_id,I>();

//regular function with single param
int _d(int x){return x<<1;}
constexpr auto d=RCurry<decltype(_d),_d,int>();
// constexpr auto d=typename decltype(fun(_d))::template curried<decltype(_d),_d>;

//regular function with multiple param
int _m(int x,int y){return x*y;}
constexpr auto m=RCurry<decltype(_m),_m,int,int>();

template<typename O> O __true(O o,O) {return o;}
template<typename O> auto _true=RCurry<decltype(__true<O>),__true<O>,O,O>();
template<typename O> O __false(O,O o) {return o;}
template<typename O> auto _false=RCurry<decltype(__false<O>),__false<O>,O,O>();

/*
evaluation order
right-most function requiring arguments have priority
*/
int main(int argc, char **argv) {
  cout<<"d(2):"<<d(2)<<endl;
  cout<<"m(2)(3):"<<m(2)(3)<<endl;
  auto x=d(d);
  cout<<"x(2):"<<x(2)<<endl;
  cout<<"id<int>(d)(1967:"<<id<int>(d)(1967)<<endl;
  cout<<"m(d)(5)(3):"<<m(d)(5)(3)<<endl;
  cout<<"d(m)(2)(3):"<<d(m)(2)(3)<<endl;
  cout<<"m(5)(d)(3):"<<m(5)(d)(3)<<endl;
  cout<<"d(m)(10)(2):"<<d(m)(10)(2)<<endl;
  cout<<"d(m(10))(2):"<<d(m(10))(2)<<endl;//same as above
  cout<<"d(m)(5)(m)(3)(2):"<<d(m)(5)(m)(3)(2)<<endl;
  cout<<_true<const char*>("Ok")("Fail")<<endl;
  cout<<_false<const char*>("Fail")("Ok")<<endl;
  return 0;
}
