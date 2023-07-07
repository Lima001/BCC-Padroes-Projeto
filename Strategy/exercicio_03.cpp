#include <iostream>

// Interface - Strategy
class MovimentarComportamento {
    public:
        virtual void movimentar() = 0;
};

// Concrete Strategy
class MovimentarComMotor: public MovimentarComportamento {
    public:
        void movimentar(){
            std::cout << "Movimentando com Motor!" << std::endl;
        }
};

// Concrete Strategy
class MovimentarComRemo: public MovimentarComportamento {
    public:
        void movimentar(){
            std::cout << "Movimentando com Remo!" << std::endl;
        }
};

// Concrete Strategy
class MovimentarComVela: public MovimentarComportamento {
    public:
        void movimentar(){
            std::cout << "Movimentando à Vela!" << std::endl;
        }
};

// Abstract Class - Context
class Barco {

    private:
        MovimentarComportamento* movimentarComportamento; 

    public:
        
        Barco(){
            movimentarComportamento = nullptr;
        }

        ~Barco(){
            if (movimentarComportamento)
                delete movimentarComportamento;
        }

        void setMovimentarComportamento(MovimentarComportamento* m){
            if (movimentarComportamento)
                delete movimentarComportamento;
            movimentarComportamento = m;
        }

        void performarMovimentar(){
            if (movimentarComportamento)
                movimentarComportamento->movimentar();
        }

        virtual void print() = 0;

};

class Bateira: public Barco {
    void print(){
        std::cout << "Bateira" << std::endl;
    }
};

class Iate: public Barco {
    void print(){
        std::cout << "Iate" << std::endl;
    }
};

class Canoa: public Barco {
    void print(){
        std::cout << "Canoa" << std::endl;
    }
};

class Jangada: public Barco {
    void print(){
        std::cout << "Jangada" << std::endl;
    }
};

class BarcoVela: public Barco {
    void print(){
        std::cout << "Barco a Vela" << std::endl;
    }
};

int main(){

    Bateira b1;
    b1.setMovimentarComportamento(new MovimentarComMotor());

    Iate b2;
    b2.setMovimentarComportamento(new MovimentarComMotor());
    
    Canoa b3;
    b3.setMovimentarComportamento(new MovimentarComRemo());

    Jangada b4;
    b4.setMovimentarComportamento(new MovimentarComRemo());

    BarcoVela b5;
    b5.setMovimentarComportamento(new MovimentarComVela());

    Barco* lista_barcos[] = {&b1, &b2, &b3, &b4, &b5};

    for (Barco* b: lista_barcos){
        b->print();
        b->performarMovimentar();
        std::cout << std::endl;
    }

    return 0;
}