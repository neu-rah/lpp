#include <iostream>
using namespace std;

#include <lpp.h>
#include <lpp_debug.h>
using namespace lpp;

//creating dependent types to use as lambda expressions
const char* yes="Yes";using Yes=StaticText<&yes>;
const char* no="No";using No=StaticText<&no>;

class myClass1 {};
class myClass2 {};

//add a zero to naturals
using Nz=Cons<N<0>,Nats<>>;

int main() {
  //debug print (not always possible due to laziness and infinite structures)
  cout<<"debug print lambda expression:"<<lambda::trace<True<Int,Float>>()<<endl;

  //extracting a value from a dependent type lambda
  cout<<"print lambda dependent type (char*): "<<value<Yes>()<<endl;

  //creating and extracting a dependent value
  cout<<"int dependent value: "<<value<StaticValue<int,2019>>()<<endl;

  //creating a lambda numeral and extracting a `size_t` from it
  cout<<"numeral toInt: "<<toInt<N<123>>()<<endl;

  //wraping user type to use as lambda expression and extracting it as type of x
  True<As<myClass1>,As<myClass2>>::App::Type x;

  //creating a lambda numeral and extracting a `size_t` from it
  cout<<"list head: [0,1,..] -> ";
  cout<<toInt<Head<Nz>>()<<endl;

  cout<<"head (drop 10 [0,1,..]) -> ";
  cout<<toInt<
    Head<
      Drop<
        N<10>,
        Nz
      >
    >
  >()<<endl;

  cout<<"head (drop 10 (Map (Mult 2) [0,1,..])) -> ";
  cout<<toInt<
    Head<
      Drop<
        N<10>,
        Map<Mult<N<2>>,Nz>
      >
    >
  >()<<endl;

  return 0;
}
