#include <memory>
#include <string>
#include <map>
#include <functional>
#include <cctype>
#include <algorithm>
#include <type_traits>

class Var { 
public:
    Var( double n ): valor( std::shared_ptr<Undefined>( new Double( n ) ) ) {}
    Var(): valor( new Undefined() ) {}
    Var( int n ): valor( std::shared_ptr<Undefined>( new Int( n ) ) ) {}
    Var( bool n ): valor( std::shared_ptr<Undefined>( new Boolean( n ) ) ) {}
    Var( std::string n ): valor( std::shared_ptr<Undefined>( new String( n ) ) ) {}
    Var( const char* n ): valor( std::shared_ptr<Undefined>( new String( std::string(n) ) ) ) {}
    Var( char n ): valor( std::shared_ptr<Undefined>( new Char( n ) ) ) {}
    
    Var operator = ( bool n ) {
        valor = std::shared_ptr<Undefined>( new Boolean( n ) );
        return (*this);
    }
    Var operator = ( int n ) {
        valor = std::shared_ptr<Undefined>( new Int( n ) );
        return (*this);
    }
    Var operator = ( double n ) {
        valor = std::shared_ptr<Undefined>( new Double( n ) );
        return (*this);
    }
    Var operator = ( std::string n ) {
        valor = std::shared_ptr<Undefined>( new String( n ) );
        return (*this);
    }
    Var operator = ( const char* n ) {
        valor = std::shared_ptr<Undefined>( new String( std::string(n) ) );
        return (*this);
    }
    Var& operator = ( const Var& v ) {
        valor = v.valor;
        return (*this);
    }
    
    Var operator + ( const Var &oth) const {
        return (*valor) + oth.valor;
    }
    Var operator - ( const Var &oth) const {
        return (*valor) - oth.valor;
    }
    Var operator * ( const Var &oth) const {
        return (*valor) * oth.valor;
    }
    Var operator / ( const Var &oth) const {
        return (*valor) / oth.valor;
    }
    Var operator && ( const Var &oth) const {
        return (*valor) && oth.valor;
    }
    Var operator || ( const Var &oth) const {
        return (*valor) || oth.valor;
    }
    Var operator ! () const {
        return !(*valor);
    }
    Var operator < ( const Var &oth ) const{
        return *(valor) < oth.valor;
    }
    Var& operator[] ( const std::string &s) const { 
        return (*valor)[s];
    }
    Var& operator[] ( const char *s) const { 
        return operator[]( std::string(s) );
    }
    Var& operator[] ( const Var &id) const { 
        return (*valor)[id];
    }
    Var operator() (const Var &v) const { 
        return (*valor)(v);
    }
    
    void imprime(std::ostream& o) const {
        valor->imprime(o);
    }

    bool asBool() const{ return valor->asBool(); }
    std::string asString() const { return valor->asString(); }
    bool isNumber(){ return valor->isNumber(); }
    Var forEach( const Var &F ) const{ return (*valor).forEach(F); }

    class Undefined{
    public:
        virtual Var operator < ( const std::shared_ptr<Undefined> oth ) const{ Var v; return v; };
        virtual Var operator ! ( ) const{ return ! Var( (*this).asBool() ); };
        virtual Var operator + ( const std::shared_ptr<Undefined> oth ) const{ Var v; return v; };
        virtual Var operator - ( const std::shared_ptr<Undefined> oth ) const{ Var v; return v; };
        virtual Var operator * ( const std::shared_ptr<Undefined> oth ) const{ Var v; return v; };
        virtual Var operator / ( const std::shared_ptr<Undefined> oth ) const{ Var v; return v; };
        virtual Var operator && ( const std::shared_ptr<Undefined> oth ) const{ Var v; return v; };
        virtual Var operator || ( const std::shared_ptr<Undefined> oth ) const{ Var v; return v; };
        virtual Var& operator[] ( const std::string &s)  { throw Erro("Essa variável não é um objeto"); }
        virtual Var& operator[] ( const Var &id)  { throw Erro("Essa variável não é um array"); }
        virtual void imprime(std::ostream& o) const { o <<"undefined"; }
        virtual Var operator()(const Var &v) const{ throw Erro("Essa variável não pode ser usada como função"); }
        virtual bool asBool() const{ return 0; }
        virtual std::string asString() const { return "undefined"; }
        virtual bool isNumber(){ return false;}
        Var forEach( const Var &F ) const{ Var v; return v; }
        std::ostream& operator<<(std::ostream& o){
            (*this).imprime(o);
            return o;
        }
    };
    
    class Boolean: public Undefined {
    public:
        Boolean( bool val ):_valor(val) {}
        bool valor() const { return _valor; }
        bool asBool() const{ return valor() ;}
        bool isNumber(){ return true; }

        std::string asString() const {
            if(_valor)
                return std::string("true");
            else
                return std::string("false");            
        }
        Var operator ! ( ) const{
            return !_valor;
        };
        Var operator < ( const std::shared_ptr<Undefined> oth ) const {
            auto other = std::dynamic_pointer_cast<Boolean>(oth);
            if(other)
                return _valor < other->valor();
            Var v; return v;
        }
        Var operator && ( const std::shared_ptr<Undefined> oth ) const{
            auto other = std::dynamic_pointer_cast<Boolean>(oth);
            if(other)
                return Var(_valor && other->valor());
            else{
                Var v; return v;
            }
        };
        Var operator || ( const std::shared_ptr<Undefined> oth ) const{
            auto other = std::dynamic_pointer_cast<Boolean>(oth);
            if(other)
                return Var(_valor || other->valor());
            else{
                Var v; return v;
            }
        };
        void imprime(std::ostream& o) const {
            if(_valor)
                o << std::string("true");
            else
                o << std::string("false");
        }
    private:
        bool _valor;
    };
    
    class Int: public Undefined {
    public:
        Int( int val ):_valor(val) {}
        int valor() const { return _valor; }
        bool isNumber(){ return true;}
        bool asBool() const{ return (bool) valor() ;}
        std::string asString() const { return std::to_string(valor()) ;}
        Var operator < ( const std::shared_ptr<Undefined> oth ) const {
            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor < otherInt->valor();

            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor < otherDouble->valor();

            auto otherChar = std::dynamic_pointer_cast<Char>(oth);
            if(otherChar)
                return _valor < otherChar->valor();
            
            Var v; return v;
        }
        Var operator + ( const std::shared_ptr<Undefined> oth ) const{
            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor + otherInt->valor();

            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor + otherDouble->valor();

            Var v;
            return v;
        };
        Var operator - ( const std::shared_ptr<Undefined> oth ) const{
            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor - otherInt->valor();

            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor - otherDouble->valor();

            Var v;
            return v;
        };
        Var operator * ( const std::shared_ptr<Undefined> oth ) const{
            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor * otherInt->valor();

            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor * otherDouble->valor();

            Var v;
            return v;
        };
        Var operator / ( const std::shared_ptr<Undefined> oth ) const{
            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor / otherInt->valor();

            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor / otherDouble->valor();

            Var v;
            return v;
        };
        void imprime(std::ostream& o) const {
            o << _valor;
        }
    private:
        int _valor;
    };

    class Double: public Undefined {
    public:
        Double( double val ):_valor(val) {}
        double valor() const { return _valor; }
        bool isNumber(){ return true;}
        bool asBool() const{ return (bool) valor() ;}
        std::string asString() const { return std::to_string(valor()) ;}
        Var operator < ( const std::shared_ptr<Undefined> oth ) const {
            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor < otherDouble->valor();

            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor < otherInt->valor();
            
            auto otherChar = std::dynamic_pointer_cast<Char>(oth);
            if(otherChar)
                return _valor < otherChar->valor();
            
            Var v; return v;
        }
        Var operator + ( const std::shared_ptr<Undefined> oth ) const{
            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor + otherDouble->valor();

            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor + otherInt->valor();

            Var v; return v;
        };
        Var operator - ( const std::shared_ptr<Undefined> oth ) const{
            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor - otherDouble->valor();

            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor - otherInt->valor();

            Var v; return v;
        };
        Var operator * ( const std::shared_ptr<Undefined> oth ) const{
            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor * otherDouble->valor();

            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor * otherInt->valor();

            Var v; return v;
        };
        Var operator / ( const std::shared_ptr<Undefined> oth ) const{
            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor / otherDouble->valor();

            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor / otherInt->valor();

            Var v; return v;
        };
        void imprime(std::ostream& o) const {
            o << _valor;
        }
    private:
        double _valor;
    };
    
    class Char: public Undefined {
    public:
        Char( char val ) : _valor(val) {}
        char valor() const { return _valor; }
        bool asBool() const{ return (bool) valor() ;}
        std::string asString() const { return std::string(1, valor()) ;}
        Var operator < ( const std::shared_ptr<Undefined> oth ) const {
            auto otherChar = std::dynamic_pointer_cast<Char>(oth);
            if(otherChar)
                return _valor < otherChar->valor();
            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor < otherInt->valor();
            auto otherDouble = std::dynamic_pointer_cast<Double>(oth);
            if(otherDouble)
                return _valor < otherDouble->valor();
            auto otherString = std::dynamic_pointer_cast<String>(oth);
            if(otherString)
                return std::string(1, _valor) < otherString->valor();
            Var v; return v;
        }
        Var operator + ( const std::shared_ptr<Undefined> oth ) const{
            auto otherChar = std::dynamic_pointer_cast<Char>(oth);
            if(otherChar)
                return std::string(1, _valor) + std::string(1, otherChar->valor());
            auto otherInt = std::dynamic_pointer_cast<Int>(oth);
            if(otherInt)
                return _valor + otherInt->valor();
            auto otherString = std::dynamic_pointer_cast<String>(oth);
            if(otherString)
                return _valor + otherString->valor();
            Var v; return v;
        };
        void imprime(std::ostream& o) const {
            o << _valor;
        }
        bool isNumber(){ return isdigit(_valor);}
    private:
        char _valor; 
    };
    
    class String: public Undefined {
    public:
        String( std::string val ) : _valor(val) {}
        std::string valor() const { return _valor; }
        std::string asString() const { return valor();}
        bool asBool() const{ return _valor.size() ;}
        Var operator < ( const std::shared_ptr<Undefined> oth ) const {
            auto otherString = std::dynamic_pointer_cast<String>(oth);
            if(otherString)
                return _valor < otherString->valor();
            auto otherChar = std::dynamic_pointer_cast<Char>(oth);
            if(otherChar)
                return _valor < std::string(1, otherChar->valor());
            Var v; return v;
        }
        Var operator + ( const std::shared_ptr<Undefined> oth ) const{
            auto otherString = std::dynamic_pointer_cast<String>(oth);
            if(otherString)
                return Var(_valor + otherString->valor());
            auto otherChar = std::dynamic_pointer_cast<Char>(oth);
            if(otherChar)
                return Var(_valor + std::string(1, otherChar->valor()));
            Var v; return v;
        };
        void imprime(std::ostream& o) const {
            o << _valor;
        }
        bool isNumber(){ 
            std::string valorTrim = _valor;
            
            std::reverse(valorTrim.begin(), valorTrim.end());
            while(valorTrim.size() && (valorTrim.back() == ' ' || valorTrim.back()  == '\n'))
                valorTrim.pop_back();
            
            std::reverse(valorTrim.begin(), valorTrim.end());
            while(valorTrim.size() && (valorTrim.back() == ' ' || valorTrim.back()  == '\n'))
                valorTrim.pop_back();
            
            for(char c: valorTrim)
                if(!isdigit(c))
                    return false;
            return true;
        }
    private:
        std::string _valor; 
    };
    
    class Object: public Undefined{
    public:
        Var& operator[] ( const std::string &s)  { 
            return objects[s];
        }
        void imprime(std::ostream& o) const { o <<"object"; }
        std::string asString() const { return "object"; }
        bool asBool() const{ return 1; }
    protected:
        std::map<std::string, Var> objects;
    };
    Var( Object *o): valor( std::shared_ptr<Undefined>( o ) ) {}
    Var operator = ( Object *o ) {
        valor = std::shared_ptr<Undefined>( o );
        return (*this);
    }

    class Array: public Object{
    public:
        Var& operator[] ( const Var &id)  { 
            return objects[id.asString()];
        }
        Var forEach( const Var &F ) const{
            for(auto const e:objects)
                F(e.second);
            Var v;
            return v;
        }
        
        void imprime(std::ostream& o) const { o <<"array"; }
        std::string asString() const { return "array"; }
    };
    Var( Array *o): valor( std::shared_ptr<Undefined>( o ) ) {}
    Var operator = ( Array *o ) {
        valor = std::shared_ptr<Undefined>( o );
        return (*this);
    }
    
    
    template<typename F>
    class Function: public Undefined{
    public:
        Function( F _f) : f(_f){ }
        Var operator()(const Var &v) const{
            auto ret = std::invoke_result< decltype( f ), Var >;
            if(std::is_same< void, ret >::value){
                Var v;
                return v;
            }
            return f(v);
        }
        Var operator()(Var v) const{
            return f(v);
        }
        void imprime(std::ostream& o) const { o <<"function"; }
        bool asBool() const{ return 1; }
        std::string asString() const { return "function"; }
    private:
        F f;
    };
    
    template<typename F>
    Var(F f): valor( std::shared_ptr<Function<F>>( new Function(f) ) ) {}
    
    template<typename F>
    Var operator = ( F f ) {
        valor = std::shared_ptr<Undefined>( new Function(f) );
        return (*this);
    }
    

    class Erro {
    public:
        Erro( std::string msg ): msg(msg) {}
    
        std::string operator()() const {
            return msg;
        }
    
    private:
        std::string msg;
    };

private:
    std::shared_ptr<Undefined> valor;
};


Var::Object * newObject(){
    return new Var::Object;
}
Var::Array * newArray(){
    return new Var::Array;
}

Var operator > ( const Var& a, const Var& b ) { return b < a; }
Var operator != ( const Var& a, const Var& b ) { return (a<b) || (b<a); }
Var operator == ( const Var& a, const Var& b ) { return !(a!=b); }
Var operator <= ( const Var& a, const Var& b ) { return !(b<a); }
Var operator >= ( const Var& a, const Var& b ) { return !(a<b); }

template<typename T>
Var operator == ( T a, const Var& b ) { return Var(a)==b; }
template<typename T>
Var operator + ( T a, const Var& b ) { return Var(a)+b; }
template<typename T>
Var operator - ( T a, const Var& b ) { return Var(a)-b; }
template<typename T>
Var operator * ( T a, const Var& b ) { return Var(a)*b; }
template<typename T>
Var operator / ( T a, const Var& b ) { return Var(a)/b; }
template<typename T>
Var operator && ( T a, const Var& b ) { return Var(a)&&b; }
template<typename T>
Var operator || ( T a, const Var& b ) { return Var(a)||b; }

std::ostream& operator<<(std::ostream& o, const Var &v){
    v.imprime(o);
    return o;
}
