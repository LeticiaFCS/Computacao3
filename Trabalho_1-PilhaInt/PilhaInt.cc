class PilhaInt{
    public:
        PilhaInt(){
            atual = 0;
            for(int i = 0; i < MAX_PILHA; i++)
                tab[i] = 0;
        }
        void empilha(int valor){
            tab[atual++] = valor;
        }
        int desempilha(){
            return tab[--atual];
        }
        void print(std::ostream& o) {
            o<<"[ ";
            if(atual != 0)
                o<<tab[0];
            for(int i = 1; i < atual; i++)
                o<<", "<<tab[i];
            o<<" ]";
        }
        const PilhaInt& operator=(const PilhaInt& o){
            atual = o.atual;
            for(int i = 0; i < atual; i++)
                tab[i] = o.tab[i];
            return *this;
        }
        PilhaInt& operator << (int valor){
            empilha(valor);
            return *this;
        }
    private:
        static const int MAX_PILHA = 10; 
        int tab[MAX_PILHA];
        int atual;
};
