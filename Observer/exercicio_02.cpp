#include <iostream>
#include <string>
#include <list>

// Interface
class Observer {
    public:
        virtual void update() = 0;
};

// Interface
class Subject {

    protected:

        std::list<Observer*>* observers;

    public:

        virtual void attach(Observer* o) = 0;
        virtual void detach(Observer* o) = 0;
        virtual void notify() = 0;
};

// Classe auxiliar para representar dados de um produto de uma loja
class Produto {

    public:

        unsigned int id;
        std::string nome;
        float preco;

        Produto(unsigned int id, std::string nome, float preco){
            this->id = id;
            this->nome = nome;
            this->preco = preco;
        }

};

// Concrete Subject
class Loja: public Subject {
    
    public:

        std::list<Produto*> produtos;

        std::string nome;

        Loja(){
            observers = new std::list<Observer*>;   
        }

        Loja(std::string nome){
            this->nome = nome;
            observers = new std::list<Observer*>;
        }

        ~Loja(){
            if (observers)
                delete observers;
            
            for (std::list<Produto*>::iterator it=produtos.begin(); it != produtos.end(); it++)
                delete *it;
        }

        /*
            Métodos provenientes de Subject
        */
        void attach(Observer* o){
            observers->push_back(o);
        }

        void detach(Observer* o){
            observers->remove(o);
        }
        
        void notify(){
            /*
                Para a notificação dos concrete observers, optou-se pelo protocolo pull model,
                sendo o concrete observer responsável por buscar os dados atualizados posteriormente.
            */
            for (std::list<Observer*>::iterator it=observers->begin(); it != observers->end(); it++)
                (*it)->update();
        }

        /*
            Métodos para mudar o estado da loja (adição e atualização de produtos)

            Obs. Sempre que a lista de produtos é modificada, adiciona-se/movimenta-se
            o produto modificado para o final da lista. Dessa forma, um concret observer
            recupera o produto atualizado com base na sua posição.

            Optou-se por essa situação apenas para simplificar o código. Em um caso real,
            uma opção melhor deve ser escolhida, uma vez que o mecanismo em questão não
            é suficientemente robusto para uma aplicação real.
        */
        void adicionarProduto(unsigned int id, std::string nome, float preco){
            Produto* p = new Produto(id, nome, preco);
            produtos.push_back(p);
            notify();
        }
        
        void alterarPrecoProduto(unsigned int id, float novo_preco){
            for (std::list<Produto*>::iterator it=produtos.begin(); it != produtos.end(); it++){
                if ((*it)->id == id){
                    (*it)->preco = novo_preco;
                    produtos.splice(produtos.end(), produtos, it);
                }
            }
            notify();
        }

        /*
        Apenas uma ideia de método para remoção de produtos
        void removerProduto(unsigned int id){
            for (std::list<Produto*>::iterator it=produtos.begin(); it != produtos.end(); it++){
                if ((*it)->id == id)
                    produtos.remove(*it);
            }
        }
        */
        
        void listarProdutos(){
            for (std::list<Produto*>::iterator it=produtos.begin(); it != produtos.end(); it++){
                std::cout << "Id: " << (*it)->id << std::endl;
                std::cout << "Nome: " << (*it)->nome << std::endl;
                std::cout << "Preco: " << (*it)->preco << std::endl;
                std::cout << "-----------------------------" << std::endl;
            }
        }

        /* 
            Método para pegar a atualização de estado do Concrete Subject, isto é,
            o produto que foi atualizado/adicionado.
        */
        const Produto* getProdutoAtualizado(){
            return produtos.back();
        }

};

class Usuario {
    
    public:

        std::string login;

        Usuario(std::string login){
            this->login = login;
        }

        void receberNotificacaoProduto(std::string nome_loja, std::string nome_produto, float preco_produto){
            std::cout << "Usuario: " << login << std::endl;
            std::cout << "Recebida uma notificação da loja <<" << nome_loja << ">>" << std::endl;
            std::cout << "Confira o produto atualizado abaixo!" << std::endl;
            std::cout << "Produto: " << nome_produto << std::endl;
            std::cout << "Preco: " << preco_produto << std::endl;
            std::cout << "- - - - - - - - - - - - -" << std::endl;
        }
};

class Notificador: public Observer {
    
    private:

        Loja* loja_referencia;
        std::list<Usuario*> usuarios;

    public:

        Notificador(Loja* loja_referencia){
            this->loja_referencia = loja_referencia;
            this->loja_referencia->attach(this);
        }

        ~Notificador(){
            for (std::list<Usuario*>::iterator it=usuarios.begin(); it != usuarios.end(); it++)
                usuarios.remove(*it);
            
            if (loja_referencia)
                loja_referencia->detach(this);
        }

        void update(){
            const Produto* p = loja_referencia->getProdutoAtualizado();
            for (std::list<Usuario*>::iterator it=usuarios.begin(); it != usuarios.end(); it++)
                (*it)->receberNotificacaoProduto(loja_referencia->nome, p->nome, p->preco);
        }

        void setLojaReferencia(Loja* nova_loja){
            loja_referencia = nova_loja;
        }

        void registrarUsuario(Usuario* u){
            usuarios.push_back(u);
        }

        void removerUsuario(Usuario* u){
            usuarios.remove(u);
        }
};

int main(){

    Usuario* user1 = new Usuario("login1");
    Usuario* user2 = new Usuario("login2");
    Usuario* user3 = new Usuario("login3");

    Loja* loja1 = new Loja("Loja A");
    Loja* loja2 = new Loja("Loja B");

    // Essas alterações não devem ser notificadas, pois não existe um concrete observer para esse concrete subject
    loja1->adicionarProduto(0, "Produto-01", 1.0);
    loja1->alterarPrecoProduto(0, 1.5);

    Notificador* notificador_loja1 = new Notificador(loja1);
    Notificador* notificador_loja2 = new Notificador(loja2);

    notificador_loja1->registrarUsuario(user1);
    notificador_loja1->registrarUsuario(user2);
    notificador_loja1->registrarUsuario(user3);
    
    // Essas modificações devem ser notificadas aos 3 usuários
    loja1->adicionarProduto(1, "Produto-02", 2.0);
    loja1->adicionarProduto(2, "Produto-03", 3.0);
    loja1->alterarPrecoProduto(2, 3.5);

    notificador_loja2->registrarUsuario(user1);
    
    // Essas modificações devem ser noticiadas apenas ao usuário 1
    loja2->adicionarProduto(3, "Produto-04", 4.0);
    loja2->adicionarProduto(4, "Produto-05", 5.0);

    notificador_loja2->registrarUsuario(user2);
    loja2->alterarPrecoProduto(4, 5.5);
    
    delete loja1;
    delete loja2;
    
    delete user1;
    delete user2;
    delete user3;
    

    return 0;
}