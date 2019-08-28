#include <iostream>
#include <utility>
#include <type_traits>
using namespace std;

#include <lpp.h>
#include <lpp_debug.h>
using namespace lambda;

const char* ok="Ok";using Ok=StaticText<&ok>;
const char* fail="Fail";using Fail=StaticText<&fail>;
const char* yes="Yes";using Yes=StaticText<&yes>;
const char* no="No";using No=StaticText<&no>;
const char* true_text="true";using trueText=StaticText<&true_text>;
const char* false_text="false";using falseText=StaticText<&false_text>;

inline int _test(int a,int b) {return a*b;}
using test=curry<int,decltype(&_test),_test,2>;

int main() {
  //debug output
  cout<<trace<Ok>()<<endl;//type string
  Show<Expr<N1,Not,True,Yes,No>>();//cout type => type::App

  //numerals, selecting a type
  cout<<(0!=(N0::Bind<Not>::Bind<True>::Bind<Float>::Bind<Int>::App::Type)0.618?"Ok":"Fail")<<": Zero numeral"<<endl;
  cout<<(0==(Succ::Bind<N4>::Bind<Not>::Bind<True>::Bind<Float>::Bind<Int>::App::Type)0.618?"Ok":"Fail")<<": Succ N4"<<endl;

  cout<<Expr<N0,Not,True,Ok,Fail>::App::value()<<": N0 Not True"<<endl;
  cout<<Expr<N1,Not,True,Fail,Ok>::App::value()<<": N1 Not True"<<endl;
  cout<<Expr<N2,Not,True,Ok,Fail>::App::value()<<": N2 Not True"<<endl;
  cout<<Expr<N3,Not,True,Fail,Ok>::App::value()<<": N3 Not True"<<endl;
  cout<<Expr<N4,Not,True,Ok,Fail>::App::value()<<": N4 Not True"<<endl;
  cout<<Expr<N5,Not,True,Fail,Ok>::App::value()<<": N5 Not True"<<endl;

  // cout<<N3::Bind<Peano>::Bind<Zero>::toInt()<<endl;
  cout
    <<toInt<N0>()<<","
    <<toInt<N1>()<<","
    <<toInt<N2>()<<","
    <<toInt<N3>()<<","
    <<toInt<N4>()<<endl;
  cout<<"5+4="<<toInt< Add::Bind<N5>::Bind<N4> >()<<endl;
  cout<<"5*4="<<toInt< Mult::Bind<N5>::Bind<N4> >()<<endl;
  cout<<"3*4="<<toInt< Expr<Mult,N3,N4> >()<<endl;
  cout<<"3^5="<<toInt< Expr<Pow,N3,N5> >()<<endl;

  // //checking usage of static values
  cout<<"int value 111:"<<StaticValue<int,111>::value()<<endl;
  cout<<"Is0 N0 "<<Is0::Bind<N0>::Bind<Yes>::Bind<No>::App::value()<<endl;
  cout<<"Is0 N1 "<<Is0::Bind<N1>::Bind<Yes>::Bind<No>::App::value()<<endl;
  cout<<"Is0 N2 "<<Is0::Bind<N2>::Bind<Yes>::Bind<No>::App::value()<<endl;
  cout<<"Is0 "<<toInt<Pow::Bind<N4>::Bind<N3>::App>()<<" "<<Is0::Bind<Pow::Bind<N4>::Bind<N3>>::Bind<Yes>::Bind<No>::App::value()<<endl;

  // //use curried c++ functions, c++ functions can now be lambda expressions
  cout<<"call c++ function test(3,5) "<<test::Bind<StaticValue<int,3>>::Bind<StaticValue<int,5>>::value()<<endl;
  cout<<"call c++ function Expr<test,3,5> "<<Expr<test,StaticValue<int,3>,StaticValue<int,5>>::value()<<endl;

  // //pairs, `fst` and `snd`
  using P=V::Bind<N1>::Bind<N2>;
  cout<<"Pair (1,2):"<<"("<<toInt<Fst::Bind<P>::App>()<<","<<toInt<Snd::Bind<P>::App>()<<")"<<endl;
  cout<<endl;
  cout<<"arithmetic-----------------------"<<endl;
  cout<<"5-3="<<toInt<Expr<Sub,N5,N3>>()<<endl;
  cout<<endl;
  cout<<"relational operators-----------"<<endl;
  cout<<"5<=3? "<<Expr<LEq,N5,N3,Yes,No>::App::value()<<endl;
  cout<<"3<=5? "<<Expr<LEq,N3,N5,Yes,No>::App::value()<<endl;
  cout<<"2<=2? "<<Expr<LEq,N2,N2,Yes,No>::App::value()<<endl;
  cout<<endl;
  cout<<"5>=3? "<<Expr<GEq,N5,N3,Yes,No>::App::value()<<endl;
  cout<<"3>=5? "<<Expr<GEq,N3,N5,Yes,No>::App::value()<<endl;
  cout<<"2>=2? "<<Expr<GEq,N2,N2,Yes,No>::App::value()<<endl;
  cout<<endl;
  cout<<"5>3? "<<Expr<GT,N5,N3,Yes,No>::App::value()<<endl;
  cout<<"3>5? "<<Expr<GT,N3,N5,Yes,No>::App::value()<<endl;
  cout<<"2>2? "<<Expr<GT,N2,N2,Yes,No>::App::value()<<endl;
  cout<<endl;
  cout<<"5<3? "<<Expr<LT,N5,N3,Yes,No>::App::value()<<endl;
  cout<<"3<5? "<<Expr<LT,N3,N5,Yes,No>::App::value()<<endl;
  cout<<"2<2? "<<Expr<LT,N2,N2,Yes,No>::App::value()<<endl;
  cout<<endl;
  cout<<"1=2? "<<Expr<Eq,N1,N2,Yes,No>::App::value()<<endl;
  cout<<"2=2? "<<Expr<Eq,N2,N2,Yes,No>::App::value()<<endl;
  cout<<endl;
  cout<<"1!=2? "<<Expr<NEq,N1,N2,Yes,No>::App::value()<<endl;
  cout<<"2!=2? "<<Expr<NEq,N2,N2,Yes,No>::App::value()<<endl;
  cout<<endl;

  cout<<endl<<"Lists-----------------------"<<endl;
  using L1=List<String,Float,Int>;
  cout<<"L1:[String,Float,Int]"<<endl;
  cout<<"Null L1: ";Show<Expr<Expr<Null,L1>,Yes,No>>();
  cout<<"Null(Tail L1): ";Show<Expr<Expr<Null,Expr<Tail,L1>>,Yes,No>>();
  cout<<"Null(Tail (Tail L1)): ";Show<Expr<Expr<Null,Expr<Tail,Expr<Tail,L1>>>,Yes,No>>();
  cout<<"Null(Tail.Tail.Tail L1)): ";Show<Expr<Expr<Null,Expr<Tail,Expr<Tail,Expr<Tail,L1>>>>,Yes,No>>();
  cout<<endl;

  using BFL=Expr<Y,Expr<Cons,Char>>;//dont print this!
  // Show<BFL>(); -> segmentation fault (stack iverflow)
  cout<<"Lazy: Head(Drop(3*5) [Char..]) : ";Show<Expr<Head,Expr<Drop,Expr<Mult,N3,N5>,BFL>>>();
  cout<<endl;

  //factorial (lazy Y)
  cout<<"5!="<<toInt<Fact::Bind<N5>::App>()<<endl;

  //more list operations
  using A=List<Float,Int>;
  using B=List<I,M,K,KI,C,B,V,Bb,Y,Id>;
  using L2=Expr<Concat,B,A>::App;
  cout<<"length L2: "<<toInt<Expr<Length,L2>::App>()<<endl;
  cout<<"Index 5 L2: "<<trace<Expr<Index,L2,N5>::App>()<<endl;
  cout<<"Lat L2: "<<trace<Expr<Last,L2>::App>()<<endl;
  cout<<"Length$Init L2: "<<toInt<Expr<Length,Init::Bind<L2>>::App>()<<endl;
  cout<<"Head(Reverse L2): "<<trace<Expr<Head,Expr<Reverse,L2>>::App>()<<endl;
  cout<<endl;

  cout<<"Nats: ["<<toInt<Expr<Head,Nats>>()<<", "<<toInt<Expr<Head,Expr<Tail,Nats>>>()<<",..]"<<endl;
  cout<<"Head(Drop(3*5) Nats): "<<toInt<Expr<Head,Expr<Drop::Bind<Expr<Mult,N3,N5>>,Nats>>::App>()<<endl;
  cout<<"Length(TakeR 5 Nats): "<<toInt<Expr<Length,Expr<TakeR,N5,Nats>>::App>()<<endl;
  cout<<"Length(Take 5 Nats): "<<toInt<Expr<Length,Expr<Take,N5,Nats>>::App>()<<endl;
  cout<<"Head(TakeR 3 Nats): "<<toInt<Expr<Head,Expr<TakeR,N3,Nats>>::App>()<<endl;

  cout<<"----------------------------------------------------------------------------------------------------"<<endl;
  cout<<"all this happened at compile time, the only code generated was the code to print this report.. ejoy!"<<endl;
  return true;
}
