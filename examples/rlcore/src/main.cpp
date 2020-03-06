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
  cout<<RI<rAs>()(2)<<endl;
  cout<<RI<RI<rAs>>()()(2);
  return 0;
}
