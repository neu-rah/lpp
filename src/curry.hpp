
template<typename O,typename... OO>
static inline std::string _Comp<O,OO...>::name() {return Names<O,OO...>::names();}
