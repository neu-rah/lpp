#include <iostream>
using namespace std;

#include <r-lambda.h>//runtime lambda core
using namespace rlambda;

int _d(int x){return x<<1;}
auto d=_RCurry<decltype(_d),_d,int>();

int _m(int x,int y){return x*y;}
auto m=_RCurry<decltype(_m),_m,int,int>();

int main(int argc, char **argv) {
  cout<<d(2)<<endl;
  cout<<m(2)(3)<<endl;
  // auto dm=decltype(d)::Bind<decltype(m),m,int>(2);
  auto x=d(d);
  d(m);
  cout<<x(2)<<endl;
  // cout<<m(d)(2)(3)<<endl;
  return 0;
}
