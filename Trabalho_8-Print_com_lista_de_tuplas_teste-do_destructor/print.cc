#include <iostream>




class AbstractPair{
public:
    virtual void imprime(std::ostream& o) const = 0;
    virtual AbstractPair * clone() const = 0;
    virtual ~AbstractPair(){}
    
};

template<typename A, typename B>
class PairImpl: public AbstractPair{
public:
    PairImpl(const A &a, const B &b): a(a), b(b){}
    PairImpl(const PairImpl<A,B> &oth): a(oth.a), b(oth.b){}
    PairImpl(PairImpl<A,B> &&oth): a(oth.a), b(oth.b){}
    PairImpl<A, B> operator =(const PairImpl<A,B> &oth){
        a = oth.a;
        b = oth.b;
        return (*this);
    }
    PairImpl<A, B> operator =(PairImpl<A,B> &&oth){
        a = oth.a;
        b = oth.b;
        return (*this);
    }
    AbstractPair * clone() const{
        return new PairImpl(*this);
    }
    void imprime(std::ostream& o) const {
        o << a << " = " << b << "\n";
    }
private:
    A a;
    B b;
};
class Pair {
public:
    template <typename A, typename B>
    Pair(A a, B b): p(new PairImpl<A,B>(a, b)){}
    Pair(const Pair &o): p(o.p->clone()){}
    Pair(Pair &&o): p(o.p){
        o.p = nullptr;
    }
    Pair operator=(const Pair &o){
        p = o.p->clone();
        return (*this);
    }
    Pair operator=(Pair &&o){
        p = o.p;
        o.p = nullptr;
        return (*this);
    }
    void imprime(std::ostream& o) const  {
        p->imprime(o);
    }
    ~Pair(){
        delete p;
    } 
private:
    AbstractPair *p;
};
void print( std::ostream& o, std::initializer_list<Pair> lista ) {
    for(auto it = lista.begin(); it != lista.end(); it++)
        (*it).imprime(o);
}