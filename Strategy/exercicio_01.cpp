#include <iostream>

// Interface - Strategy
class FlyBehavior {
    public:
        virtual void fly() = 0;
};

// Interface - Strategy
class QuackBehavior {
    public:
        virtual void quack() = 0;
};

// Concrete Strategy
class FlyWithWings: public FlyBehavior {
    public:
        void fly(){
            std::cout << "Fly - FlyWithWings" << std::endl;
        }
};

// Concrete Strategy
class FlyNoWay: public FlyBehavior {
    public:
        void fly(){
            std::cout << "Fly - FlyNoWay" << std::endl;
        }
};

// Concrete Strategy
class Quack: public QuackBehavior {
    public:
        void quack(){
            std::cout << "Quack - Quack" << std::endl;
        }
};

// Concrete Strategy
class Squeak: public QuackBehavior {
    public:
        void quack(){
            std::cout << "Quack - Squeak" << std::endl;
        }
};

// Concrete Strategy
class MuteQuack: public QuackBehavior {
    public:
        void quack(){
            std::cout << "Quack - MuteQuack" << std::endl;
        }
};

// Abstract Class - Context
class Duck {
    
    private:

        FlyBehavior* flyBehavior;
        QuackBehavior* quackBehavior;

    public:

        Duck(){
            flyBehavior = nullptr;
            quackBehavior = nullptr;
        }

        ~Duck(){
            if (flyBehavior)
                delete flyBehavior;
            if (quackBehavior)
                delete quackBehavior;
            //std::cout << "Destructor called" << std::endl;
        }

        void swim(){
            std::cout << "swim" << std::endl;
        }

        virtual void display() = 0;
        
        void performQuack(){
            if (quackBehavior)
                quackBehavior->quack();
        }

        void performFly(){
            if (flyBehavior)
                flyBehavior->fly();
        }

        void setFlyBehavior(FlyBehavior* f){
            if (flyBehavior)
                delete flyBehavior;
            flyBehavior = f;
        }

        void setQuackBehavior(QuackBehavior* q){
            if (quackBehavior)
                delete quackBehavior;
            quackBehavior = q;
        }
};

class MallardDuck: public Duck {
    public:
        void display(){
            std::cout << "Display MallardDuck" << std::endl;
        }
};

class RedheadDuck: public Duck {
    public:
        void display(){
            std::cout << "Display RedheadDuck" << std::endl;
        }
};

class RubberDuck: public Duck {
    public:
        void display(){
            std::cout << "Display RubberDuck" << std::endl;
        }
};

class DecoyDuck: public Duck {
    public:
        void display(){
            std::cout << "Display DecoyDuck" << std::endl;
        }
};

int main(){

    MallardDuck mallard;
    mallard.setFlyBehavior(new FlyWithWings());
    mallard.setQuackBehavior(new Quack());

    RedheadDuck red_head;
    red_head.setFlyBehavior(new FlyWithWings());
    red_head.setQuackBehavior(new Quack());
    
    RubberDuck rubber;
    rubber.setFlyBehavior(new FlyNoWay());
    rubber.setQuackBehavior(new Squeak());
    
    DecoyDuck decoy;
    decoy.setFlyBehavior(new FlyNoWay());
    decoy.setQuackBehavior(new MuteQuack());

    Duck* duck_array[] = {&mallard, &red_head, &rubber, &decoy};

    for (Duck* d: duck_array){
        d->display();
        d->performFly();
        d->performQuack();
        std::cout << std::endl;
    }

    return 0;
}