class PilhaInt{
    public:
        PilhaInt(int tamanho = 10): tamanho(tamanho){
            atual = 0;
            tab = (int*) malloc(tamanho * sizeof(int));
            for(int i=0; i<tamanho; i++)
                tab[i] = 0;
        }
        PilhaInt(PilhaInt &o): atual(o.atual), tamanho(o.tamanho) {
            tab = (int*) malloc(tamanho * sizeof(int));
            for(int i = 0; i < atual; i++)
                tab[i] = o.tab[i];
        }
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
            tab = (int*) realloc(tab, n * sizeof(int));
            tamanho = n;
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
        ~PilhaInt(){
            free(tab);
        }
    private:
        int *tab;
        int atual;
        int tamanho;
};