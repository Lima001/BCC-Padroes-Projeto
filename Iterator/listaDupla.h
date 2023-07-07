#ifndef LISTA_DUPLA_INTEIROS_H
#define LISTA_DUPLA_INTEIROS_H

#include "iterator.h"

template <typename T>
class NoListaDupla;

template <typename T>
class ListaDupla;

template <typename T>
class ListaDuplaIterator: public Iterator<T> {
    private:
        ListaDupla<T>* iterable;
        NoListaDupla<T>* cursor;
        int index;
    
    public:

        ListaDuplaIterator(ListaDupla<T>* lista){
            iterable = lista;
            cursor = iterable->getHead();
            
            if (!iterable->isEmpty())
                index = 0;
            else 
                index = std::numeric_limits<int>::min();
        };

        void first(){
            cursor = iterable->getHead();
            if (!iterable->isEmpty())
                index = 0;
            else
                index = std::numeric_limits<int>::min();
        }

        void last(){
            cursor = iterable->getTail();
            if (!iterable->isEmpty())
                index = iterable->size()-1;
            else
                index = std::numeric_limits<int>::min();
        }

        bool hasNext(){
            return (cursor != nullptr);
        }

        bool hasPrevious(){
            return (cursor != nullptr);
        }

        T next(){
            assert(this->hasNext());
            T info = cursor->getInfo();
            cursor = cursor->getProx();
            index++;
            return info;
        }

        T previous(){
            assert(this->hasPrevious());
            T info = cursor->getInfo();
            cursor = cursor->getAnterior();
            index--;
            return info;
        }

        int nextIndex(){
            if (cursor == iterable->getTail())
                return iterable->size()-1;
            return index+1;
        }

        int previousIndex(){
            if (cursor == iterable->getHead())
                return -1;
            return index-1;
        } 
};

template <typename T>
class NoListaDupla {
    private:
        T info;
        NoListaDupla<T>* ant;
        NoListaDupla<T>* prox;

    public:

        NoListaDupla(){
            ant = nullptr;
            prox = nullptr;
        }

        ~NoListaDupla(){
            ant = nullptr;
            prox = nullptr;
        }

        void setInfo(T info){
            this->info = info;
        }

        T getInfo(){
            return info;
        }

        void setProx(NoListaDupla<T>* prox){
            this->prox = prox;
        }

        NoListaDupla<T>* getProx(){
            return prox;
        }

        void setAnterior(NoListaDupla<T>* ant){
            this->ant = ant;
        }

        NoListaDupla<T>* getAnterior(){
            return ant;
        }
};

template <typename T>
class ListaDupla: public Iterable<T> {
    private:
        NoListaDupla<T>* head;
        NoListaDupla<T>* tail;
    
    public:
        
        ListaDupla(){
            head = nullptr;
            tail = nullptr;
        }

        ~ListaDupla(){
            NoListaDupla<T>* tmp = nullptr;
            while (head){
                tmp = head->getProx();
                delete head;
                head = tmp;
            }
        }

        void inserirInicio(T info){
            NoListaDupla<T>* no = new NoListaDupla<T>();
            no->setInfo(info);
            
            if (!head){
                head = no;
                tail = no;
            }
            else {
                NoListaDupla<T>* tmp = head;
                head = no;
                no->setProx(tmp);
                tmp->setAnterior(no);
            }
        }
        
        void inserirFim(T info){
            NoListaDupla<T>* no = new NoListaDupla<T>();
            no->setInfo(info);
            
            if (!tail){
                head = no;
                tail = no;
            }
            else {
                NoListaDupla<T>* tmp = tail;
                tail = no;
                no->setAnterior(tmp);
                tmp->setProx(no);
            }
        }
        
        bool isEmpty(){
            return (head == nullptr);
        }
        
        void clear(){
            NoListaDupla<T>* tmp = nullptr;
            while (head){
                tmp = head->getProx();
                delete head;
                head = tmp;
            }
            tail = nullptr;
        }
        
        int size(){
            NoListaDupla<T>* tmp = head;
            int i = 0;

            while (tmp){
                i++;
                tmp = tmp->getProx();
            }

            return i;
        }
        
        ListaDuplaIterator<T>* iterator(){
            ListaDuplaIterator<T>* i = new ListaDuplaIterator<T>(this);
            return i;
        }
        
        NoListaDupla<T>* getHead(){
            return head;
        }

        NoListaDupla<T>* getTail(){
            return tail;
        }
};

#endif