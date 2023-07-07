#include <iostream>
#include <stdlib.h>

// <<Interface>>
class State {
    public:
        virtual void inserirMoeda() = 0;
        virtual void ejetarMoeda() = 0;
        virtual void virarManivela() = 0;
        virtual void entregar() = 0;
};

// Declaração da estrutura da classe - Implementação dos métodos realizada em momento posterior
class MaquinaBolinhas {
    private:
        State* esgotado;
        State* semCredito;
        State* comCredito;
        State* vendido;
        State* vencedor;
        
        State* estadoAtual;
        int countBolinhas;

    public:
        MaquinaBolinhas();
        MaquinaBolinhas(int nBolinhas);
        ~MaquinaBolinhas();
        void inserirMoeda();
        void ejetarMoeda();
        void virarManivela();
        void setEstado(State* estado);
        void setCountBolinhas(int n);
        int getCountBolinhas();
        State* getEstadoVendido();
        State* getEstadoVencedor();
        State* getEstadoEsgotado();
        State* getEstadoComCredito();
        State* getEstadoSemCredito();
};

/*
    Implementação dos Estados Concretos
*/
class SemCredito: public State {
    private:
        MaquinaBolinhas* m;

    public:
        SemCredito(MaquinaBolinhas* m){
            this->m = m;    
        }

        ~SemCredito(){
            m = nullptr;
        }

        void inserirMoeda(){
            std::cout << "Moeda inserida com sucesso!" << std::endl;
            m->setEstado(m->getEstadoComCredito());
        }

        void ejetarMoeda(){
            std::cout << "Nenhuma moeda foi inserida - Impossível realizar ação" << std::endl;
        }

        void virarManivela(){
            std::cout << "Alavanca acionada, porém falta inserir moeda" << std::endl;
        }

        void entregar(){
            std::cout << "Impossível entregar prêmio" << std::endl;
        }
};

class ComCredito: public State {
    private:
        MaquinaBolinhas* m;

    public:
        ComCredito(MaquinaBolinhas* m){
            this->m = m;    
        }

        ~ComCredito(){
            m = nullptr;
        }

        void inserirMoeda(){
            std::cout << "Uma moeda já foi anteriormente inserida - Impossível inserir nova moeda" << std::endl;
        }

        void ejetarMoeda(){
            std::cout << "Moeda ejetada com sucesso!" << std::endl;
            m->setEstado(m->getEstadoSemCredito());
        }

        void virarManivela(){
            std::cout << "Manivela acionada com sucesso!" << std::endl;
            
            if (rand()%10 +1 == 1 && m->getCountBolinhas() >= 2)
                m->setEstado(m->getEstadoVencedor());
            else
                m->setEstado(m->getEstadoVendido());
        }

        void entregar(){
            std::cout << "Nenhuma bolinha foi entregue ainda" << std::endl;
        }
};

class Esgotado: public State {
    private:
        MaquinaBolinhas* m;

    public:
        Esgotado(MaquinaBolinhas* m){
            this->m = m;    
        }

        ~Esgotado(){
            m = nullptr;
        }

        void inserirMoeda(){
            std::cout << "A máquina está vazia - Impossível realizar ação" << std::endl;
        }

        void ejetarMoeda(){
            std::cout << "Nenhuma moeda inserida - Impossível realizar ação" << std::endl;
        }

        void virarManivela(){
            std::cout << "A máquina está vazia - Impossível realizar ação" << std::endl;
        }

        void entregar(){
            std::cout << "Nenhuma bolinha fornecida - Impossível realizar ação" << std::endl;
        }
};

class Vendido: public State {
    private:
        MaquinaBolinhas* m;

    public:
        Vendido(MaquinaBolinhas* m){
            this->m = m;    
        }

        ~Vendido(){
            m = nullptr;
        }

        void inserirMoeda(){
            std::cout << "Aguarde - Máquina processando venda anterior" << std::endl;
        }

        void ejetarMoeda(){
            std::cout << "Alavanca já foi acionada - Impossível realizar ação" << std::endl;
        }

        void virarManivela(){
            std::cout << "Acionar a manivela novamente não resultará em mais uma bolinha" << std::endl;
        }

        void entregar(){
            std::cout << "Pegue a sua bolinha!" << std::endl;
            
            if (m->getCountBolinhas() > 1)
                m->setEstado(m->getEstadoSemCredito());
            else
                m->setEstado(m->getEstadoEsgotado());
            
            m->setCountBolinhas(m->getCountBolinhas()-1);
        }
};

class Vencedor: public State {
    private:
        MaquinaBolinhas* m;

    public:
        Vencedor(MaquinaBolinhas* m){
            this->m = m;    
        }

        ~Vencedor(){
            m = nullptr;
        }

        void inserirMoeda(){
            std::cout << "Aguarde - Máquina processando venda anterior" << std::endl;
        }

        void ejetarMoeda(){
            std::cout << "Alavanca já foi acionada - Impossível realizar ação" << std::endl;
        }

        void virarManivela(){
            std::cout << "Acionar a manivela novamente não resultará em mais uma bolinha" << std::endl;
        }

        void entregar(){
            std::cout << "Vencedor! Pegue duas bolinhas!" << std::endl;
            
            if (m->getCountBolinhas() > 2)
                m->setEstado(m->getEstadoSemCredito());
            else
                m->setEstado(m->getEstadoEsgotado());
            
            m->setCountBolinhas(m->getCountBolinhas()-2);
        }
};

/*
    Implementação dos métodos da classe MaquinaBolinhas
*/
MaquinaBolinhas::MaquinaBolinhas(){
    esgotado = nullptr;
    semCredito =nullptr;
    comCredito = nullptr;
    vendido = nullptr;
    vencedor = nullptr;
    countBolinhas = 0;
}

MaquinaBolinhas::MaquinaBolinhas(int nBolinhas){
    countBolinhas = nBolinhas;
    esgotado = new Esgotado(this);
    semCredito = new SemCredito(this);
    comCredito = new ComCredito(this);
    vendido = new Vendido(this);
    vencedor = new Vencedor(this);

    if (countBolinhas > 0)
        estadoAtual = semCredito;
    else
        estadoAtual = esgotado;
}

MaquinaBolinhas::~MaquinaBolinhas(){
    estadoAtual = nullptr;
    delete esgotado;
    delete semCredito;
    delete comCredito;
    delete vencedor;
    delete vendido;
}

void MaquinaBolinhas::inserirMoeda(){
    estadoAtual->inserirMoeda();
}

void MaquinaBolinhas::ejetarMoeda(){
    estadoAtual->ejetarMoeda();
}

void MaquinaBolinhas::virarManivela(){
    estadoAtual->virarManivela();
    estadoAtual->entregar();
}

void MaquinaBolinhas::setEstado(State* estado){
    estadoAtual = estado;
}

void MaquinaBolinhas::setCountBolinhas(int n){
    countBolinhas = n;
}

int MaquinaBolinhas::getCountBolinhas(){
    return countBolinhas;
}

State* MaquinaBolinhas::getEstadoVendido(){
    return vendido;
}

State* MaquinaBolinhas::getEstadoVencedor(){
    return vencedor;
}

State* MaquinaBolinhas::getEstadoEsgotado(){
    return esgotado;
}

State* MaquinaBolinhas::getEstadoComCredito(){
    return comCredito;
}

State* MaquinaBolinhas::getEstadoSemCredito(){
    return semCredito;
}

// Classe para testar Maquina de Bolinhas implementada
class TesteMaquina {
    private:
        MaquinaBolinhas m = MaquinaBolinhas(10);
    
    public:
        void main(){
            int op, countBolinhas;
            bool executar = true;
            
            while (executar){
                printMenu();

                std::cout << "Digite a sua opção: ";
                std::cin >> op;

                switch (op){

                    case 0:
                        executar = false;
                        break;
                    case 1:
                        m.inserirMoeda();
                        break;
                    case 2:
                        m.virarManivela();
                        break;
                    case 3:
                        m.ejetarMoeda();
                        break;
                    case 4:
                        std::cout << "Digite a quantidade de bolinhas a serem adicionadas: ";
                        std::cin >> countBolinhas;
                        m.setCountBolinhas(m.getCountBolinhas()+countBolinhas);
                        break;
                    default:
                        std::cout << "Opção inválida, tente novamente!" << std::endl;
                        break;
                };

                if (!executar)
                    break;
            }
        }

        void printMenu(){
            std::cout << "-------------------------" << std::endl;
            std::cout << "Quantidade de bolinhas disponíveis: " << m.getCountBolinhas() << std::endl;
            std::cout << "Opções:" << std::endl;
            std::cout << "0 - Sair" << std::endl;
            std::cout << "1 - Inserir Moeda" << std::endl;
            std::cout << "2 - Virar Manivela" << std::endl;
            std::cout << "3 - Ejetar Moeda" << std::endl;
            std::cout << "4 - Adicionar bolinhas na máquina" << std::endl;
            std::cout << "-------------------------" << std::endl;
        }
};

int main(){
    TesteMaquina tm;
    tm.main();
    return 0;
}