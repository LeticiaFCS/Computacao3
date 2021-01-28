#include<vector>
#include<iostream>

template<int N, typename T>
class Vetor{
public:
    class MeioDoProdutoVetorial{
        public:
            MeioDoProdutoVetorial(const Vetor<N,T> &v): vetor(v.vetor){ }
        private:
            std::vector<T> vetor;
        friend Vetor;
    };
    class Virgula{
        public:
            Virgula(Vetor<N, T> &v): vetor(v){}
            Virgula operator,(T e){
                vetor = e;
                return *this;
            }
        private:
            Vetor<N, T> &vetor;

        friend Vetor;
    };
    Vetor<N,T> operator+(const Vetor<N,T> &oth){
        Vetor<N, T> ret;
        ret.vetor.resize(N);
        for(int i = 0;i < N; i++)
            ret.vetor[i] = vetor[i] + oth.vetor[i];
        return ret;
    }
    Vetor<N,T> operator-(const Vetor<N,T> &oth){
        Vetor<N, T> ret;
        ret.vetor.resize(N);
        for(int i = 0;i < N; i++)
            ret.vetor[i] = vetor[i] - oth.vetor[i];
        return ret;
    }
    T operator*(const Vetor<N,T> &oth){
        T ret = {};
        for(int i = 0;i < N; i++)
            ret += vetor[i] * oth.vetor[i];
        return ret;
    }
    Vetor<N,T> operator*(T e){
        Vetor<N, T> ret;
        ret.vetor.resize(N);
        for(int i = 0;i < N; i++)
            ret.vetor[i] = e * vetor[i];
        return ret;
    }
    MeioDoProdutoVetorial operator*(){
        return MeioDoProdutoVetorial(*this);
    }
    Vetor<N,T> operator*(const MeioDoProdutoVetorial &oth){
        Vetor<N,T> ret;
        ret.vetor.resize(N);      
        if(N == 3){
            ret.vetor[0] = vetor[1]*oth.vetor[2] - vetor[2]*oth.vetor[1];
            ret.vetor[1] = vetor[2]*oth.vetor[0] - vetor[0]*oth.vetor[2];
            ret.vetor[2] = vetor[0]*oth.vetor[1] - vetor[1]*oth.vetor[0];
        }
        return ret;
    }
    Vetor<N,T> operator/(T e){
        Vetor<N, T> ret;
        ret.vetor.resize(N);
        for(int i = 0;i < N; i++)
            ret.vetor[i] = vetor[i] / e;
        return ret;
    }
    void imprime(std::ostream& o) const{
        if(vetor.size() == 0)
            for(int i=0; i<N; i++)
                o<<T()<<' ';
        else
            for(const T& x: vetor)
                o<<x<<' ';
    }
    Vetor<N,T> operator=(const Vetor<N,T> &oth){
        vetor = oth.vetor;
        return *this;
    }

    Virgula operator=(T e){
        vetor.push_back(e); 
        return Virgula(*this);
    }
    
private:
    std::vector<T> vetor;
};

template<int N, typename T>
std::ostream& operator<<(std::ostream& o, const Vetor<N, T> &v){
    v.imprime(o);
    return o;
}

template<int N, typename T>
auto operator*(T e, Vetor<N, T> &v){    
    return v * e;
}
