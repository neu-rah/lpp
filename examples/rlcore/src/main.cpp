#include <iostream>
using namespace std;

#include <r-lambda.h>//runtime lambda core
using namespace rlambda;

int _d(int x){return x<<1;}
RCurry<decltype(_d),_d,int> d;

int _m(int a,int b) {return a*b;}
RCurry<decltype(_m),_m,int,int> m;

template<typename O>
O _div(O a,O b) {return a/b;}
template<typename O>
RCurry<decltype(_div<O>),_div<O>,O,O> rat;


int main(int argc, char **argv) {
  cout<<rI<decltype(d)>(d)(rInt(2))<<endl;
  cout<<rI<decltype(m)>(m)(rInt(5))(3)<<endl;
  cout<<rI<decltype(rI<int>)>(rI<int>)(rInt(8))<<endl;
  cout<<rI<decltype(rI<rInt>)>(rI<rInt>)(10)<<endl;
  // cout<<rM<decltype(rI<rI<int>>)>(rI<int>)(11)<<endl;
  return 0;
}
