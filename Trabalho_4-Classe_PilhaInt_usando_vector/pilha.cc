class PilhaInt{
    public:
        PilhaInt(int tamanho = 10): tab(tamanho), atual(0), tamanho(tamanho){}
        PilhaInt(PilhaInt &o): tab(o.tab), atual(o.atual), tamanho(o.tamanho) {}
        const PilhaInt& operator=(PilhaInt &o){
            while(atual > o.atual)
                desempilha();
            redimensiona(o.capacidade());
            atual = o.atual;
            for(int i = 0; i < atual; i++)
                tab[i] = o.tab[i];
            return *this;
        }
        
        int capacidade() const {
            return tamanho;
        }
        void redimensiona(int n){
            while(n < atual)
                desempilha();
            tamanho = n;
            tab.resize(n);
        }
        void empilha(int valor){
            if(atual >= capacidade())
                redimensiona(2 * capacidade());
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
        
        PilhaInt& operator << (int valor){
            empilha(valor);
            return *this;
        }
    private:
        std::vector<int> tab;
        int atual;
        int tamanho;
};