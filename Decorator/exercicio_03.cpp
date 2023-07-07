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

        SIZE getSize(){
            return size;
        }

        void setSize(SIZE size){
            this->size = size;
        }

        virtual std::string getDescription() = 0;
        
        virtual double cost() = 0;
};

// Componente Concreto - Base para os decorators agregarem funcionalidades
class DummyComponent: public Beverage {
    public:

        DummyComponent(){
            description = "";
        }

        double cost(){
            return 0;
        }

        std::string getDescription(){
            return description;
        }
};

// Classe Abstrata - Decorator
class Decorator: public Beverage {
    public:
        Beverage* beverage;
        virtual std::string getDescription() = 0;
};

// Decorator Concreto
class HouseBlend: public Decorator {
    public:

        HouseBlend(Beverage* beverage){
            this->beverage = beverage;
            description = "House Blend Coffee";
            size = S;
        }

        ~HouseBlend(){
            if (beverage)
                delete beverage;
        }

        double cost(){
            return size*0.89 + beverage->cost();
        }

        std::string getDescription(){
            return sizeToString(size) + " " + description + " " + beverage->getDescription();
        }
};

// Decorator Concreto
class DarkRoast: public Decorator {
    public:

        DarkRoast(Beverage* beverage){
            this->beverage = beverage;
            description = "Dark Roast Coffee";
            size = S;
        }

        ~DarkRoast(){
            if (beverage)
                delete beverage;
        }

        double cost(){
            return size*0.99 + beverage->cost();
        }

        std::string getDescription(){
            return sizeToString(size) + " " + description + " " + beverage->getDescription();
        }
};

// Decorator Concreto
class Espresso: public Decorator {
    public:

        Espresso(Beverage* beverage){
            this->beverage = beverage;
            description = "Espresso";
            size = S;
        }
        
        ~Espresso(){
            if (beverage)
                delete beverage;
        }

        double cost(){
            return size*1.99 + beverage->cost();
        }

        std::string getDescription(){
            return sizeToString(size) + " " + description + " " + beverage->getDescription();
        }
};

// Decorator Concreto
class Decaf: public Decorator {
    public:

        Decaf(Beverage* beverage){
            this->beverage = beverage;
            description = "Decaf";
            size = S;
        }

        ~Decaf(){
            if (beverage)
                delete beverage;
        }

        double cost(){
            return size*1.05 + beverage->cost();
        }

        std::string getDescription(){
            return sizeToString(size) + " " + description + " " + beverage->getDescription();
        }
};

// Decorator Concreto
class Milk: public Decorator {
    public:

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
class Mocha: public Decorator {
    public:

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
class Soy: public Decorator {
    public:

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
class Whip: public Decorator {
    public:

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

    Beverage* beverage = new DummyComponent();
    beverage = new Espresso(beverage);
    beverage = new Espresso(beverage);
    beverage->setSize(L);
    std::cout << beverage->getDescription() << " - $" << beverage->cost() << std::endl;

    Beverage* beverage2 = new DummyComponent();
    beverage2 = new DarkRoast(beverage2);
    beverage2->setSize(L);
    beverage2 = new Mocha(beverage2);
    beverage2->setSize(L);
    beverage2 = new Mocha(beverage2);
    beverage2->setSize(S);
    beverage2 = new Whip(beverage2);
    beverage2->setSize(M);
    std::cout << beverage2->getDescription() << " - $" << beverage2->cost() << std::endl;

    Beverage* beverage3 = new DummyComponent();
    beverage3 = new HouseBlend(beverage3);
    beverage3->setSize(L);
    beverage3 = new Soy(beverage3);
    beverage3 = new Mocha(beverage3);
    beverage3 = new Whip(beverage3);
    beverage3 = new DarkRoast(beverage3);
    beverage3->setSize(M);
    std::cout << beverage3->getDescription() << " - $" << beverage3->cost() << std::endl;
    
    return 0;
}