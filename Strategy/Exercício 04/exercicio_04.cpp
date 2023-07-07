#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

// Interface - Strategy
class EdgeDetectionBehavior {
    public:
        virtual void detectEdge(cv::Mat* inputArray, cv::Mat* outputArray) = 0;
};

// Concrete Strategy
class SobelEdgeDetection: public EdgeDetectionBehavior {
    public:
        void detectEdge(cv::Mat* inputArray, cv::Mat* outputArray){
            cv::Mat bluredImage;
            cv::GaussianBlur(*inputArray, bluredImage, cv::Size(3, 3), 0, 0);
            cv::Sobel(bluredImage, *outputArray, CV_8U, 1, 1);
        }
};

// Concrete Strategy
class CannyEdgeDetection: public EdgeDetectionBehavior {
    public:
        void detectEdge(cv::Mat* inputArray, cv::Mat* outputArray){
            cv::Mat bluredImage;
            cv::GaussianBlur(*inputArray, bluredImage, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
            cv::Canny(bluredImage, *outputArray, 100, 200);
        }
};

// Concrete Strategy
class LaplacianEdgeDetection: public EdgeDetectionBehavior {
    public:
        void detectEdge(cv::Mat* inputArray, cv::Mat* outputArray){
            cv::Mat bluredImage;
            cv::GaussianBlur(*inputArray, bluredImage, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
            cv::Laplacian(bluredImage, *outputArray, CV_8U);
        }
};

// Context
class Imagem {

    private:

        std::string in_path;
        std::string out_path;

        cv::Mat imagem;
        EdgeDetectionBehavior* edgeDetectionBehavior;
    
    public:
        
        Imagem(std::string in, std::string out){
            edgeDetectionBehavior = nullptr;
            in_path = in;
            out_path = out;
            imagem = cv::imread(in_path, cv::IMREAD_GRAYSCALE);
        }

        ~Imagem(){
            if (edgeDetectionBehavior)
                delete edgeDetectionBehavior;
        }

        void setEdgeDetectionBehavior(EdgeDetectionBehavior* e){
            if (edgeDetectionBehavior)
                delete edgeDetectionBehavior;
            edgeDetectionBehavior = e;
        }

        void performEdgeDetection(){
            if (edgeDetectionBehavior){
                cv::Mat output;
                edgeDetectionBehavior->detectEdge(&imagem, &output);
                imagem = output;
            }
        }

        void saveImage(){
            cv::imwrite(out_path, imagem);
        }

};

int main(){

    Imagem img1 = Imagem("img/imagem1.jpg", "img/saida_imagem1.jpg");
    img1.setEdgeDetectionBehavior(new SobelEdgeDetection());

    Imagem img2 = Imagem("img/imagem2.jpg", "img/saida_imagem2.jpg");
    img2.setEdgeDetectionBehavior(new CannyEdgeDetection());
    
    Imagem img3 = Imagem("img/imagem3.jpg", "img/saida_imagem3.jpg");
    img3.setEdgeDetectionBehavior(new LaplacianEdgeDetection());

    Imagem* lista_imagens[] = {&img1, &img2, &img3};

    for (Imagem* img: lista_imagens){
        img->performEdgeDetection();
        img->saveImage();
    }
    
    return 0;
}
