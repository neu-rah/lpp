#include <iostream>
using namespace std;

#include <r-lambda.h>//runtime lambda core
using namespace rlambda;

template<typename I>
inline I _id(I i) {return i;}

template<typename I>
auto id=_RCurry<decltype(_id<I>),_id,I>();

int _d(int x){return x<<1;}
auto d=_RCurry<decltype(_d),_d,int>();

int _m(int x,int y){return x*y;}
auto m=_RCurry<decltype(_m),_m,int,int>();

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
