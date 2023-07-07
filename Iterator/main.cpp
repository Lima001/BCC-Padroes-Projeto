#include <iostream>
#include "listaDupla.h"

int main(){

    ListaDupla<int>* lista = new ListaDupla<int>;

    for (int i=0; i<=5; i++)
        lista->inserirFim(i);

    for (int i=5; i>=0; i--)
        lista->inserirInicio(i);

    std::cout << "Tamanho: " << lista->size() << " - Vazio: " << lista->isEmpty() << std::endl;

    Iterator<int>* it = lista->iterator();

    while (it->hasNext())
        std::cout << it->nextIndex() << " - " << it->next() << std::endl;

    std::cout << std::endl;
    it->last();

    while (it->hasPrevious())
        std::cout << it->previousIndex() << " - " << it->previous() << std::endl;

    lista->clear();
    std::cout << "Tamanho: " << lista->size() << " - Vazio: " << lista->isEmpty() << std::endl;
    
    it->first();
    while (it->hasNext())
        std::cout << it->nextIndex() << " - " << it->next() << std::endl;

    delete lista;

    return 0;
}