#include <functional>
#include <cmath>
#include <type_traits>

class X{
public:
    double e(double x){
        return x;
    }
    double dx(double x){
        return 1;
    }
};

class Cte{
public:
    Cte(double c):c(c){}
    double e(double v){
        return c;
    }
    double dx(double v){
        return 0;
    }
private:
    double c;
};

template<typename F1, typename F2>
class Multiplica{
public:
    Multiplica(F1 f1, F2 f2): f1(f1), f2(f2){}
    double e(double v){
        return f1.e(v) * f2.e(v);
    }
    double dx(double v){
        return f1.dx(v) * f2.e(v) + f1.e(v)*f2.dx(v);
    }

private:
    F1 f1;
    F2 f2;
};

template<typename T1, typename T2>
Multiplica<T1,T2> operator*(T1 t1, T2 t2){
    return Multiplica<T1,T2>(t1,t2);
}
template<typename T1>
Multiplica<T1,Cte> operator*(T1 t1, double t2){
    return Multiplica<T1,Cte>(t1, Cte(t2));
}
template<typename T2>
Multiplica<Cte,T2> operator*(double t1, T2 t2){
    return Multiplica<Cte,T2>(Cte(t1),t2);
}
template<typename T1>
Multiplica<T1,Cte> operator*(T1 t1, int t2){
    return Multiplica<T1,Cte>(t1, Cte(t2));
}
template<typename T2>
Multiplica<Cte,T2> operator*(int t1, T2 t2){
    return Multiplica<Cte,T2>(Cte(t1),t2);
}

template<typename F1, typename F2>
class Soma{
public:
    Soma(F1 f1, F2 f2): f1(f1), f2(f2){}
    double e(double v){
        return f1.e(v) + f2.e(v);
    }
    double dx(double v){
        return f1.dx(v) + f2.dx(v);
    }

private:
    F1 f1;
    F2 f2;
};

template<typename T1, typename T2>
Soma<T1,T2> operator+(T1 t1, T2 t2){
    return Soma<T1,T2>(t1,t2);
}
template<typename T1>
Soma<T1,Cte> operator+(T1 t1, double t2){
    return Soma<T1,Cte>(t1, Cte(t2));
}
template<typename T2>
Soma<Cte,T2> operator+(double t1, T2 t2){
    return Soma<Cte,T2>(Cte(t1),t2);
}
template<typename T1>
Soma<T1,Cte> operator+(T1 t1, int t2){
    return Soma<T1,Cte>(t1, Cte(t2));
}
template<typename T2>
Soma<Cte,T2> operator+(int t1, T2 t2){
    return Soma<Cte,T2>(Cte(t1),t2);
}

template<typename F1, typename F2>
class Diminui{
public:
    Diminui(F1 f1, F2 f2): f1(f1), f2(f2){}
    double e(double v){
        return f1.e(v) - f2.e(v);
    }
    double dx(double v){
        return f1.dx(v) - f2.dx(v);
    }

private:
    F1 f1;
    F2 f2;
};

template<typename T1, typename T2>
Diminui<T1,T2> operator-(T1 t1, T2 t2){
    return Diminui<T1,T2>(t1,t2);
}
template<typename T1>
Diminui<T1,Cte> operator-(T1 t1, double t2){
    return Diminui<T1,Cte>(t1, Cte(t2));
}
template<typename T2>
Diminui<Cte,T2> operator-(double t1, T2 t2){
    return Diminui<Cte,T2>(Cte(t1),t2);
}
template<typename T1>
Diminui<T1,Cte> operator-(T1 t1, int t2){
    return Diminui<T1,Cte>(t1, Cte(t2));
}
template<typename T2>
Diminui<Cte,T2> operator-(int t1, T2 t2){
    return Diminui<Cte,T2>(Cte(t1),t2);
}
template<typename T1>
Diminui<Cte,T1> operator-(T1 t1){
    return Diminui<Cte,T1>(Cte(0.0),t1);
}

template<typename F1, typename F2>
class Divide{
public:
    Divide(F1 f1, F2 f2): f1(f1), f2(f2){}
    double e(double v){
        return f1.e(v) / f2.e(v);
    }
    double dx(double v){
        return (f1.dx(v) * f2.e(v) - f1.e(v)*f2.dx(v)) / (f2.e(v)*f2.e(v));
    }

private:
    F1 f1;
    F2 f2;
};

template<typename T1, typename T2>
Divide<T1,T2> operator/(T1 t1, T2 t2){
    return Divide<T1,T2>(t1,t2);
}
template<typename T1>
Divide<T1,Cte> operator/(T1 t1, double t2){
    return Divide<T1,Cte>(t1, Cte(t2));
}
template<typename T2>
Divide<Cte,T2> operator/(double t1, T2 t2){
    return Divide<Cte,T2>(Cte(t1),t2);
}
template<typename T1>
Divide<T1,Cte> operator/(T1 t1, int t2){
    return Divide<T1,Cte>(t1, Cte(t2));
}
template<typename T2>
Divide<Cte,T2> operator/(int t1, T2 t2){
    return Divide<Cte,T2>(Cte(t1),t2);
}

template<typename F1>
class Potencia{
public:
    Potencia(F1 f1, int expoente): f1(f1), expoente(expoente){}
    double e(double v){
        return pow(f1.e(v), expoente);
    }
    double dx(double v){
        if(expoente == 1)
            return f1.dx(v);
        return expoente*pow(f1.e(v), expoente - 1)*f1.dx(v);
    }

private:
    F1 f1;
    int expoente;
};

template<typename T1, typename T2>
Potencia<T1> operator->*(T1 t1, T2 t2){
    static_assert( std::is_same_v< int, T2 >, "Operador de potenciação definido apenas para inteiros" );
    return Potencia<T1>(t1, t2);
}

template<typename F1>
class Cosseno{
public:
    Cosseno(F1 f1): f1(f1){}
    double e(double v){
        return cos(f1.e(v));
    }
    double dx(double v){
        return -sin(f1.e(v))*f1.dx(v);
    }

private:
    F1 f1;
};

template<typename T1>
Cosseno<T1> cos(T1 t1){
    return Cosseno<T1>(t1);
}

template<typename F1>
class Seno{
public:
    Seno(F1 f1): f1(f1){}
    double e(double v){
        return sin(f1.e(v));
    }
    double dx(double v){
        return cos(f1.e(v))*f1.dx(v);
    }

private:
    F1 f1;
};

template<typename T1>
Seno<T1> sin(T1 t1){
    return Seno<T1>(t1);
}

template<typename F1>
class Exp{
public:
    Exp(F1 f1): f1(f1){}
    double e(double v){
        return exp(f1.e(v));
    }
    double dx(double v){
        return exp(f1.e(v))*f1.dx(v);
    }

private:
    F1 f1;
};

template<typename T1>
Exp<T1> exp(T1 t1){
    return Exp<T1>(t1);
}

template<typename F1>
class Log{
public:
    Log(F1 f1): f1(f1){}
    double e(double v){
        return log(f1.e(v));
    }
    double dx(double v){
        return (1.0/f1.e(v))*f1.dx(v);
    }

private:
    F1 f1;
};

template<typename T1>
Log<T1> log(T1 t1){
    return Log<T1>(t1);
}



X x;  
