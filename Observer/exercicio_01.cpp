/*
    Os códigos foram baseados no conteúdo sobre Observer do livro Head
    First Design Patterns. Na referência em questão é possível encontrar 
    os códigos utilizados no livro para os outros displays (que não são 
    exibidos propriamente no livro). Tomei essa abordagem para produzir
    os mesmos resultados/saídas apresentadas no livro.

    Referência: https://github.com/bethrobson/Head-First-Design-Patterns
*/

#include <iostream>
#include <list>

// <<Interface>>
class Observer {
    public:
        virtual void update(float temp, float humidity, float pressure) = 0;
};

// <<Interface>>
class DisplayElement {
    public:
        virtual void display() = 0;
};

// <<Interface>>
class Subject {

    protected:

        std::list<Observer*>* observers;

    public:

        virtual void registerObserver(Observer* o) = 0;
        virtual void removeObserver(Observer* o) = 0;
        virtual void notifyObservers() = 0;

};

class WeatherData: public Subject {

    private:

        float temperature;
        float humidity;
        float pressure;

    public:

        WeatherData(){
            observers = new std::list<Observer*>;
        }

        WeatherData(float temp, float humidity, float pressure):
            temperature(temp), humidity(humidity), pressure(pressure)
        {
            observers = new std::list<Observer*>;
        }

        ~WeatherData(){
            if (observers)
                delete observers;
        }

        void registerObserver(Observer* o){
            observers->push_back(o);
        }

        void removeObserver(Observer* o){
            observers->remove(o);
        }
        
        void notifyObservers(){
            for (std::list<Observer*>::iterator it=observers->begin(); it != observers->end(); it++)
                (*it)->update(temperature, humidity, pressure);
        }
        
        float getTemperature(){
            return temperature;
        }
        
        float getHumidity(){
            return humidity;
        }
        
        float getPressure(){
            return pressure;
        }
        
        void measurementsChanged(){
            notifyObservers();
        }

        void setMeasurements(float temperature, float humidity, float pressure){
            this->temperature = temperature;
            this->humidity = humidity;
            this->pressure = pressure;
            measurementsChanged();
        }

};

class CurrentConditionsDisplay: public Observer, public DisplayElement {

    private:

        float temperature = 0;
        float humidity = 0;
        Subject* weatherData = nullptr;

    public:

        CurrentConditionsDisplay(Subject* weatherData) {
            this->weatherData = weatherData;
            weatherData->registerObserver(this);
        }

        ~CurrentConditionsDisplay(){
            weatherData->removeObserver(this);
        }

        void update(float temperature, float humidity, float pressure){
            this->temperature = temperature;
            this->humidity = humidity;
            display();
        }

        void display(){
            std::cout << "Current conditions" << std::endl;
            std::cout << temperature << "F degrees and "
                        << humidity << "% humidity" << std::endl << std::endl;
        }
};

class StatisticsDisplay: public Observer, public DisplayElement {
    
    private:
    
        float maxTemp = 0;
        float minTemp = 200;
        float tempSum = 0;
        int numReadings = 0;
        Subject* weatherData = nullptr;

    public:

        StatisticsDisplay(Subject* weatherData){
            this->weatherData = weatherData;
            weatherData->registerObserver(this);
        }

        ~StatisticsDisplay(){
            weatherData->removeObserver(this);
        }

        void update(float temperature, float humidity, float pressure){
            tempSum += temperature;
            numReadings++;

            if (temperature > maxTemp)
                maxTemp = temperature;
            
            if (temperature < minTemp)
                minTemp = temperature;

            display();
        }

        void display(){
            std::cout << "Statistics" << std::endl;
            std::cout << "Avg/Max/Min temperature = " << (tempSum / numReadings) << "/"
                        << maxTemp << "/" << minTemp << std::endl << std::endl; 
        }
};

class ForecastDisplay: public Observer, public DisplayElement {

    private:

        float currentPressure = 29.92f;  
        float lastPressure;
        Subject* weatherData;

    public:

        ForecastDisplay(Subject* weatherData){
            this->weatherData = weatherData;
            weatherData->registerObserver(this);
        }

        ~ForecastDisplay(){
            weatherData->removeObserver(this);
        }

        void update(float temp, float humidity, float pressure){
            lastPressure = currentPressure;
            currentPressure = pressure;
            
            display();
        }

        void display() {
            std::cout << "Forecast" << std::endl;
            if (currentPressure > lastPressure)
                std::cout << "Improving weather on the way!" << std::endl;
            else if (currentPressure == lastPressure)
                std::cout << "More of the same" << std::endl;
            else if (currentPressure < lastPressure)
                std::cout << "Watch out for cooler, rainy weather" << std::endl;
            
            std::cout << std::endl;
        }
};

// Implementação própria para exemplo
class ThirdPartyDisplay: public Observer, public DisplayElement {
    
    private:

        float deltaTemp = 0;
        Subject* weatherData = nullptr;

    public:

        ThirdPartyDisplay(Subject* weatherData){
            this->weatherData = weatherData;
            weatherData->registerObserver(this);
        }

        ~ThirdPartyDisplay(){
            weatherData->removeObserver(this);
        }

        void update(float temp, float humidity, float pressure){
            deltaTemp = temp-deltaTemp;
            display();
        }

        void display(){
            std::cout << "Third Party" << std::endl;
            std::cout << "Temperature variation: " << deltaTemp << "F" << std::endl << std::endl;
        }
};

int main(){

    // Concrete Subject
    WeatherData* weatherData = new WeatherData();

    // Concrete Observers
    CurrentConditionsDisplay* currentDisplay = new CurrentConditionsDisplay(weatherData);
    StatisticsDisplay* statisticsDisplay = new StatisticsDisplay(weatherData);
    ForecastDisplay* forecastDisplay = new ForecastDisplay(weatherData);
    ThirdPartyDisplay* thirdPartyDisplay = new ThirdPartyDisplay(weatherData);

    // Atualização dos dados do clima
    weatherData->setMeasurements(80, 65, 30.4f);
    std::cout << "----------------" << std::endl;
    weatherData->setMeasurements(82, 70, 29.2f);
    std::cout << "----------------" << std::endl;
    weatherData->setMeasurements(78, 90, 29.2f);

    // Desalocação de memória
    delete currentDisplay;
    delete statisticsDisplay;
    delete forecastDisplay;
    delete thirdPartyDisplay;
    delete weatherData;

    return 0;
}