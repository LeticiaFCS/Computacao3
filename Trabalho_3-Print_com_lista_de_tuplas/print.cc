#include <iostream>
class AbstractPair{
public:
    virtual void imprime(std::ostream& o) = 0;
};

template<typename A, typename B>
class PairImpl: public AbstractPair{
public:
    PairImpl(A a, B b): a(a), b(b){}
    PairImpl(const PairImpl<A,B> &oth): a(oth.a), b(oth.b){}
    void imprime(std::ostream& o){
        o << a << " = " << b << "\n";
    }
private:
    A a;
    B b;
};

class Pair {
public:
  template <typename A, typename B>
  Pair( A a, B b ) {
      p = new PairImpl<A,B>(a, b);
  }
  template <typename A, typename B>
  Pair(const Pair &o){
      p = new PairImpl<A,B>(o);
  }
  void imprime(std::ostream& o){
        p->imprime(o);
    }
private:
    AbstractPair *p;
};
void print( std::ostream& o, std::initializer_list<Pair> lista ) {
    for(Pair p: lista) 
        p.imprime(o); 
}