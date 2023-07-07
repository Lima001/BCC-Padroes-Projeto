#include <iostream>
#include <string.h>

// Interface para arquivos de aúdio
class FormatoAudio {
    public:
        virtual void abrir(std::string caminho) = 0;
        virtual void reproduzir() = 0;
        virtual void parar() = 0;
};

// Implementação do arquivo do tipo mp3 com base na interface para arquivos de áudio
class ArquivoMP3: public FormatoAudio {
    public:
        void abrir(std::string caminho){
            std::cout << "Abrindo arquivo mp3 localizado em " << caminho << std::endl;
        }

        void reproduzir(){
            std::cout << "Reproduzindo arquivo mp3" << std::endl;
        }

        void parar(){
            std::cout << "Parando reprodução de arquivo mp3" << std::endl;
        }
};

// Implementação do arquivo do tipo wav com base na interface para arquivos de áudio
class ArquivoWAV: public FormatoAudio {
    public:
        void abrir(std::string caminho){
            std::cout << "Abrindo arquivo wav localizado em " << caminho << std::endl;
        }

        void reproduzir(){
            std::cout << "Reproduzindo arquivo wav" << std::endl;
        }

        void parar(){
            std::cout << "Parando reprodução de arquivo wav" << std::endl;
        }
};

// Implementação da classe para arquivos wma (não pode ser alterada)
class WmaPlay {
    private:
        /* 
            Obs. Adicionei esses atributos apenas para deixar a execução de
            métodos mais 'agradável' - setFile() configura path; play() exibe
            o indíce e o arquivo que está tocando, etc.

            Essa alteração não está relacionada com adaptações para o uso da classe
            em relação ao problema dado - para isso segue implementando o padrão
            adapter, conforme estipulado.
        */
        std::string path;
        int index;

    public:
        void setFile(std::string path){
            this->path = path;
            std::cout << "File path has been set to " << path << std::endl;
        }

        void open(){
            std::cout << "Opening audio file located at " << path << std::endl;
        } 

        void setLocation(int index){
            this->index = index;
            std::cout << "Location has been set to  " << index << std::endl;
        }

        void play(){
            std::cout << "Playing file " << path << " at location " << index << std::endl;
        }

        void stop(){
            std::cout << "Stopping audio playing" << std::endl;
        }
};

// Implementação do adaptador de WmaPlay para FormatoAudio
class WmaPlayAdapter: public FormatoAudio {
    private:
        WmaPlay* wmaPlay;
    
    public:
        
        WmaPlayAdapter(WmaPlay* wmaPlay){
            this->wmaPlay = wmaPlay;
        }

        ~WmaPlayAdapter(){
            if (wmaPlay)
                wmaPlay = nullptr;
        }

        void abrir(std::string caminho){
            // Por padrão, sempre configura-se o índice para o inicial - 0
            wmaPlay->setFile(caminho);
            wmaPlay->setLocation(0);
            wmaPlay->open();
        }

        void reproduzir(){
            wmaPlay->play();
        }
        
        void parar(){
            wmaPlay->stop();
        }
};

// Classe para execução de método main
class AudioPlayer {
    public:
        void main(){
            // Criação dos objetos para arquivos de aúdio
            ArquivoMP3* arquivoMp3 = new ArquivoMP3();
            ArquivoWAV* arquivoWav = new ArquivoWAV();
            WmaPlay* arquivoWma = new WmaPlay();

            // Instaciando um adaptador para WMA
            WmaPlayAdapter* adaptadorArquivoWma = new WmaPlayAdapter(arquivoWma);

            // Criação de duas listas auxiliares para facilitar execução de testes posteriormente
            std::string listaCaminhos[] = {
                "caminho_arquivo.mp3",
                "caminho_arquivo.wav",
                "caminho_arquivo.wma"
            };

            // Observe como aqui utilizamos o objeto adaptado
            FormatoAudio* listaArquivosAudio[] = {
                arquivoMp3,
                arquivoWav,
                adaptadorArquivoWma
            };

            // Chamada dos métodos para todos os arquivos
            for (int i=0; i<3; i++){
                listaArquivosAudio[i]->abrir(listaCaminhos[i]);
                listaArquivosAudio[i]->reproduzir();
                listaArquivosAudio[i]->parar();
                std::cout << std::endl;
            }

            delete arquivoMp3;
            delete arquivoWav;
            delete adaptadorArquivoWma;
            delete arquivoWma;
        }
};

// Execução do teste criado
int main(){
    AudioPlayer ap;
    ap.main();
}