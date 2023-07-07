#include <iostream>
#include <string.h>

// Classe Abstrata - Componente
class Beverage {
    public:
        std::string description;

        Beverage(){
            description = "Unknown Beverage";
        }

        virtual std::string getDescription(){
            return description;
        }

        virtual double cost() = 0;
};

// Componente Concreto
class HouseBlend: public Beverage {
    public:

        HouseBlend(){
            description = "House Blend Coffee";
        }

        double cost(){
            return 0.89;
        }
};

// Componente Concreto
class DarkRoast: public Beverage {
    public:

        DarkRoast(){
            description = "Dark Roast Coffee";
        }

        double cost(){
            return 0.99;
        }
};

// Componente Concreto
class Espresso: public Beverage {
    public:

        Espresso(){
            description = "Espresso";
        }

        double cost(){
            return 1.99;
        }
};

// Componente Concreto
class Decaf: public Beverage {
    public:

        Decaf(){
            description = "Decaf";
        }

        double cost(){
            return 1.05;
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
            return 0.10 + beverage->cost();
        }

        std::string getDescription(){
            return (beverage->getDescription() + ", Milk");
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
            return 0.20 + beverage->cost();
        }

        std::string getDescription(){
            return (beverage->getDescription() + ", Mocha");
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
            return 0.15 + beverage->cost();
        }

        std::string getDescription(){
            return (beverage->getDescription() + ", Soy");
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
            return 0.10 + beverage->cost();
        }

        std::string getDescription(){
            return (beverage->getDescription() + ", Whip");
        }
};

int main(){

    Beverage* beverage = new Espresso();
    std::cout << beverage->getDescription() << " - $" << beverage->cost() << std::endl;

    Beverage* beverage2 = new DarkRoast();
    beverage2 = new Mocha(beverage2);
    beverage2 = new Mocha(beverage2);
    beverage2 = new Whip(beverage2);
    std::cout << beverage2->getDescription() << " - $" << beverage2->cost() << std::endl;

    Beverage* beverage3 = new HouseBlend();
    beverage3 = new Soy(beverage3);
    beverage3 = new Mocha(beverage3);
    beverage3 = new Whip(beverage3);
    std::cout << beverage3->getDescription() << " - $" << beverage3->cost() << std::endl;

    return 0;
}