#include <iostream>
#include <string.h>

enum SIZE {   
    S = 1, 
    M = 2, 
    L = 3
};

std::string sizeToString(SIZE size){
    if (size == 1)
        return "Small";
    else if (size == 2)
        return "Medium";
    else
        return "Large";
}

// Classe Abstrata - Componente
class Beverage {
    public:
        std::string description;
        SIZE size;

        Beverage(){
            description = "Unknown Beverage";
            size = S;
        }

        virtual std::string getDescription(){
            return sizeToString(size) + " " + description;
        }

        SIZE getSize(){
            return size;
        }

        void setSize(SIZE size){
            this->size = size;
        }

        virtual double cost() = 0;
};

// Componente Concreto
class HouseBlend: public Beverage {
    public:

        HouseBlend(){
            description = "House Blend Coffee";
            size = S;
        }

        double cost(){
            return size*0.89;
        }
};

// Componente Concreto
class DarkRoast: public Beverage {
    public:

        DarkRoast(){
            description = "Dark Roast Coffee";
            size = S;
        }

        double cost(){
            return size*0.99;
        }
};

// Componente Concreto
class Espresso: public Beverage {
    public:

        Espresso(){
            description = "Espresso";
            size = S;
        }

        double cost(){
            return size*1.99;
        }
};

// Componente Concreto
class Decaf: public Beverage {
    public:

        Decaf(){
            description = "Decaf";
            size = S;
        }

        double cost(){
            return size*1.05;
        }
};

// Classe Abstrata - Decorator
class CondimentDecorator: public Beverage {
    public:
        virtual std::string getDescription() = 0;
};

// Decorator Concreto
class Milk: public CondimentDecorator {
    public:
        Beverage* beverage;

        Milk(Beverage* beverage){
            this->beverage = beverage;
        }

        ~Milk(){
            if (beverage)
                delete beverage;
        }

        double cost(){
            return size*0.05 + beverage->cost();
        }

        std::string getDescription(){
            return (beverage->getDescription() + ", " + sizeToString(size) + " Milk");
        }
};

// Decorator Concreto
class Mocha: public CondimentDecorator {
    public:
        Beverage* beverage;

        Mocha(Beverage* beverage){
            this->beverage = beverage;
        }

        ~Mocha(){
            if (beverage)
                delete beverage;
        }

        double cost(){
            return (size+2)*0.05  + beverage->cost();
        }

        std::string getDescription(){
            return (beverage->getDescription() + ", " + sizeToString(size) + " Mocha");
        }
};

// Decorator Concreto
class Soy: public CondimentDecorator {
    public:
        Beverage* beverage;

        Soy(Beverage* beverage){
            this->beverage = beverage;
        }

        ~Soy(){
            if (beverage)
                delete beverage;
        }

        double cost(){
            return (size+1)*0.05 + beverage->cost();
        }

        std::string getDescription(){
            return (beverage->getDescription() + ", " + sizeToString(size) + " Soy");
        }
};

// Decorator Concreto
class Whip: public CondimentDecorator {
    public:
        Beverage* beverage;

        Whip(Beverage* beverage){
            this->beverage = beverage;
        }

        ~Whip(){
            if (beverage)
                delete beverage;
        }

        double cost(){
            return (size+2)*0.05 + beverage->cost();
        }

        std::string getDescription(){
            return (beverage->getDescription() + ", " + sizeToString(size) + " Whip");
        }
};

int main(){

    Beverage* beverage = new Espresso();
    beverage->setSize(L);
    std::cout << beverage->getDescription() << " - $" << beverage->cost() << std::endl;

    Beverage* beverage2 = new DarkRoast();
    beverage2->setSize(L);
    beverage2 = new Mocha(beverage2);
    beverage2->setSize(L);
    beverage2 = new Mocha(beverage2);
    beverage2->setSize(S);
    beverage2 = new Whip(beverage2);
    beverage2->setSize(M);
    std::cout << beverage2->getDescription() << " - $" << beverage2->cost() << std::endl;

    Beverage* beverage3 = new HouseBlend();
    beverage3->setSize(L);
    beverage3 = new Soy(beverage3);
    beverage3 = new Mocha(beverage3);
    beverage3 = new Whip(beverage3);
    std::cout << beverage3->getDescription() << " - $" << beverage3->cost() << std::endl;

    return 0;
}