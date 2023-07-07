#include <iostream>

// Interface - Strategy
class DefinirValorComportamento {
    public:
        virtual float definirValor(char localizao, float espaco, int comodos) = 0;
};

// Concrete Strategy
class DefinirValorComEdificacao: public DefinirValorComportamento {
    public:
        float definirValor(char localizacao, float espaco, int comodos){
            float val_regiao;
            
            switch (localizacao) {
                case 'A':
                    val_regiao = 3000;
                    break;
                case 'B':
                    val_regiao = 1000;
                    break;
                case 'C':
                    val_regiao = 500;
                    break;
                default:
                    val_regiao = 0;
                    break;
            }
            return  (espaco * val_regiao) + (comodos * 1000);
        }
};

// Concrete Strategy
class DefinirValorSemEdificacao: public DefinirValorComportamento {
    public:
        float definirValor(char localizacao, float espaco, int comodos){
            float val_regiao;
            
            switch (localizacao) {
                case 'A':
                    val_regiao = 1500;
                    break;
                case 'B':
                    val_regiao = 750;
                    break;
                case 'C':
                    val_regiao = 200;
                    break;
                default:
                    val_regiao = 0;
                    break;
            }
            return (espaco * val_regiao);
        }
};

// Abstract Class - Context
class Imovel {
    
    private:
    
        char localizacao;
        float espaco;
        int comodos;
        DefinirValorComportamento* definir_valor;
    
    public:
    
        Imovel(char loc, float esp, int com){
            localizacao = loc;
            espaco = esp;
            comodos = com;
            definir_valor = nullptr;
        }

        ~Imovel(){
            if (definir_valor)
                delete definir_valor;
        }

        void setDefinirValor(DefinirValorComportamento* d){
            if (definir_valor)
                delete definir_valor;
            definir_valor = d;
        }

        float performDefinirValor(){
            if (definir_valor)
                return definir_valor->definirValor(localizacao, espaco, comodos);
            return 0;
        }

        int getComodos(){
            return comodos;
        }

        void setComodos(int novo_comodos){
            comodos = novo_comodos;
        }

        float getEspaco(){
            return espaco;
        }

        void setEspaco(float novo_espaco){
            espaco = novo_espaco;
        }

        char getLocalizacao(){
            return localizacao;
        }

        void setLocalizacao(char nova_localizacao){
            localizacao = nova_localizacao;
        }

        virtual void print() = 0;

};

class Casa: public Imovel {
    public:

        Casa(char loc, float esp, int com):
            Imovel(loc, esp, com){
        }

        void print(){
            std::cout << "Casa" << std::endl;
        }
};

class Apartamento: public Imovel {
    public:

        Apartamento(char loc, float esp, int com):
            Imovel(loc, esp, com){
        }

        void print(){
            std::cout << "Apartamento" << std::endl;
        }
};

class Terreno: public Imovel {
    public:

        Terreno(char loc, float esp, int com):
            Imovel(loc, esp, com){
        }

        void print(){
            std::cout << "Terreno" << std::endl;
        }
};

int main(){

    Casa c1 = Casa('A', 120, 7);
    c1.setDefinirValor(new DefinirValorComEdificacao());

    Casa c2 = Casa('B', 85, 5);
    c2.setDefinirValor(new DefinirValorComEdificacao());

    Apartamento a1 = Apartamento('C', 55, 5);
    a1.setDefinirValor(new DefinirValorComEdificacao());

    Terreno t1 = Terreno('A', 1000, 0);
    t1.setDefinirValor(new DefinirValorSemEdificacao());

    Imovel* lista_imoveis[] = {&c1, &c2, &a1, &t1};
    
    for (Imovel* i: lista_imoveis){
        i->print();
        std::cout << "IPTU - R$ " << i->performDefinirValor() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}