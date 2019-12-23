#include <iostream>
using namespace std;

#include <r-lambda.h>//runtime lambda core
using namespace rlambda;

int main(int argc, char **argv) {
  cout<<_id<int>(2019)<<endl;
  cout<<_true<const char*>("Yes")("No")<<endl;
  cout<<_false<const char*>("Yes")("No")<<endl;
  //the flip of true is false
  cout<<_flip<decltype(_true<const char*>),const char*,const char*>(_true<const char*>)("Yes")("No")<<endl;
  return 0;
}
