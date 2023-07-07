#include <iostream>
#include <iomanip>
#include <vector>

// <<Interface>>
class Command {
    public:
        virtual void execute() = 0;
        virtual std::string toString() = 0;
};


// Command - função dummy
class NoCommand: public Command {
    public:

        void execute(){
            return;
        }

        std::string toString(){
            return "No Command";
        }
};

/*
    Drivers para os dispositivos
*/

class Light {
    public:

        std::string location;

        Light(std::string location){
            this->location = location;
        }

        void on(){
            std::cout << location << " Light is on" << std::endl;
        }

        void off(){
            std::cout << location << " Light is off" << std::endl;
        }
};

class CeilingFan {
    public:

        int speed;                                                  // 0- Off; 1- Low; 2- Medium; 3-High
        std::string location;

        CeilingFan(std::string location){
            this->location = location;
        }

        CeilingFan(){
            speed = 0;
        }

        void highSpeed(){
            speed = 3;
            std::cout << location << " Ceilling Fan is on high" << std::endl;
        }

        void mediumSpeed(){
            speed = 2;
            std::cout << location << " Ceilling Fan is on medium" << std::endl;
        }

        void lowSpeed(){
            speed = 1;
            std::cout << location << " Ceilling Fan is on low" << std::endl;
        }

        int getSpeed(){
            return speed;
        }

        void off(){
            speed = 0;
            std::cout << location << " Ceilling Fan is off" << std::endl;
        }
};

class Stereo {
    public:

        int volume;
        std::string location;

        Stereo(std::string location){
            volume = 10;
            this->location = location;
        }

        void off(){
            std::cout << location << " Stereo is off" << std::endl;
        }

        void on(){
            std::cout << location << " Stereo is on" << std::endl;
        }
        
        void setCD(){
            std::cout << location << " Stereo is set for CD input" << std::endl;
        }
        
        void setDVD(){
            std::cout << location << " Stereo is set for DVD input" << std::endl;
        }
        
        void setRadio(){
            std::cout << location << " Stereo is set for radio" << std::endl;
        }
        
        void setVolume(int volume){
            if (volume > 100)
                this->volume = 100;
            else if (volume < 0)
                this->volume = 0;
            else
                this->volume = volume;

            std::cout << location << " Stereo volume set to " << this->volume << std::endl;
        }

        int getVolume(){
            return volume;
        }
};

class GarageDoor {
    public:

        void up(){
            std::cout << " Garage door is up" << std::endl;
        }

        void down(){
            std::cout << " Garage door is down" << std::endl;
        }
};

/*
    Comandos para os dispositivos
*/

class LightOnCommand: public Command {
    public:

        Light* light;

        LightOnCommand(Light* light){
            this->light = light;
        }

        ~LightOnCommand(){
            light = nullptr;
        }

        void execute(){
            light->on();
        }

        std::string toString(){
            return "Light On Command";
        }

};

class LightOffCommand: public Command {
    public:

        Light* light;

        LightOffCommand(Light* light){
            this->light = light;
        }

        ~LightOffCommand(){
            light = nullptr;
        }

        void execute(){
            light->off();
        }

        std::string toString(){
            return "Light Off Command";
        }
};

class CeilingFanHighCommand: public Command {
    public:

        CeilingFan* ceilingFan;

        CeilingFanHighCommand(CeilingFan* ceilingFan){
            this->ceilingFan = ceilingFan;
        }

        ~CeilingFanHighCommand(){
            ceilingFan = nullptr;
        }

        void execute(){
            ceilingFan->highSpeed();
        }

        std::string toString(){
            return "Ceilling Fan High On Command";
        }
};

class CeilingFanMediumCommand: public Command {
    public:

        CeilingFan* ceilingFan;

        CeilingFanMediumCommand(CeilingFan* ceilingFan){
            this->ceilingFan = ceilingFan;
        }

        ~CeilingFanMediumCommand(){
            ceilingFan = nullptr;
        }

        void execute(){
            ceilingFan->mediumSpeed();
        }

        std::string toString(){
            return "Ceilling Fan Medium On Command";
        }
};

class CeilingFanLowCommand: public Command {
    public:

        CeilingFan* ceilingFan;

        CeilingFanLowCommand(CeilingFan* ceilingFan){
            this->ceilingFan = ceilingFan;
        }

        ~CeilingFanLowCommand(){
            ceilingFan = nullptr;
        }

        void execute(){
            ceilingFan->lowSpeed();
        }

        std::string toString(){
            return "Ceilling Fan Low On Command";
        }
};

class CeilingFanGetSpeedCommand: public Command {
    public:

        CeilingFan* ceilingFan;

        CeilingFanGetSpeedCommand(CeilingFan* ceilingFan){
            this->ceilingFan = ceilingFan;
        }

        ~CeilingFanGetSpeedCommand(){
            ceilingFan = nullptr;
        }

        void execute(){
            switch (ceilingFan->getSpeed()){
                case 0:
                    std::cout << "Fan is off" << std::endl;
                    break;
                case 1:
                    std::cout << "Fan is set to low speed" << std::endl;
                    break;
                case 2:
                    std::cout << "Fan is set to medium speed" << std::endl;
                    break;
                case 3:
                    std::cout << "Fan is set to high speed" << std::endl;
                    break;
                default:
                    break;
            }
        }

        std::string toString(){
            return "Ceilling Fan Get Speed Command";
        }
};

class CeilingFanOffCommand: public Command {
    public:

        CeilingFan* ceilingFan;

        CeilingFanOffCommand(CeilingFan* ceilingFan){
            this->ceilingFan = ceilingFan;
        }

        ~CeilingFanOffCommand(){
            ceilingFan = nullptr;
        }

        void execute(){
            ceilingFan->off();
        }

        std::string toString(){
            return "Ceilling Fan Off Command";
        }
};

class StereoOnWithCDCommand: public Command {
    public:

        Stereo* stereo;

        StereoOnWithCDCommand(Stereo* stereo){
            this->stereo = stereo;
        }

        ~StereoOnWithCDCommand(){
            stereo = nullptr;
        }

        void execute(){
            stereo->on();
            stereo->setCD();
        }

        std::string toString(){
            return "Stereo On with CD Command";
        }
};

class StereoOnWithDVDCommand: public Command {
    public:

        Stereo* stereo;

        StereoOnWithDVDCommand(Stereo* stereo){
            this->stereo = stereo;
        }

        ~StereoOnWithDVDCommand(){
            stereo = nullptr;
        }

        void execute(){
            stereo->on();
            stereo->setDVD();
        }

        std::string toString(){
            return "Stereo On with DVD Command";
        }
};

class StereoOnWithRadioCommand: public Command {
    public:

        Stereo* stereo;

        StereoOnWithRadioCommand(Stereo* stereo){
            this->stereo = stereo;
        }

        ~StereoOnWithRadioCommand(){
            stereo = nullptr;
        }

        void execute(){
            stereo->on();
            stereo->setRadio();
        }

        std::string toString(){
            return "Stereo On with Radio Command";
        }
};

class StereoOffCommand: public Command {
    public:

        Stereo* stereo;

        StereoOffCommand(Stereo* stereo){
            this->stereo = stereo;
        }

        ~StereoOffCommand(){
            stereo = nullptr;
        }

        void execute(){
            stereo->off();
        }

        std::string toString(){
            return "Stereo Off Command";
        }
};

class StereoIncreaseVolumeCommand: public Command {
    public:

        Stereo* stereo;

        StereoIncreaseVolumeCommand(Stereo* stereo){
            this->stereo = stereo;
        }

        ~StereoIncreaseVolumeCommand(){
            stereo = nullptr;
        }

        void execute(){
            stereo->setVolume(stereo->getVolume()+1);
        }

        std::string toString(){
            return "Increase Stereo Volume Command";
        }
};

class StereoDecreaseVolumeCommand: public Command {
    public:

        Stereo* stereo;

        StereoDecreaseVolumeCommand(Stereo* stereo){
            this->stereo = stereo;
        }

        ~StereoDecreaseVolumeCommand(){
            stereo = nullptr;
        }

        void execute(){
            stereo->setVolume(stereo->getVolume()-1);
        }

        std::string toString(){
            return "Decrease Stereo Volume Command";
        }
};

class GarageDoorUpCommand: public Command {
    public:

        GarageDoor* garageDoor;

        GarageDoorUpCommand(GarageDoor* garageDoor){
            this->garageDoor = garageDoor;
        }

        ~GarageDoorUpCommand(){
            garageDoor = nullptr;
        }

        void execute(){
            garageDoor->up();
        }

        std::string toString(){
            return "Garage Up Command";
        }
};

class GarageDoorDownCommand: public Command {
    public:

        GarageDoor* garageDoor;

        GarageDoorDownCommand(GarageDoor* garageDoor){
            this->garageDoor = garageDoor;
        }

        ~GarageDoorDownCommand(){
            garageDoor = nullptr;
        }

        void execute(){
            garageDoor->down();
        }

        std::string toString(){
            return "Garage Down Command";
        }
};

/*
    Controle remoto para acoplar comandos
*/

class RemoteControl {

    private:

        NoCommand* dummy;

    public:

        int n_slots;
        std::vector<Command*> onCommands;
        std::vector<Command*> offCommands;

        RemoteControl(int n_slots=10){
            this->n_slots = n_slots;

            dummy = new NoCommand();

            for (int i=0; i<n_slots; i++){
                onCommands.insert(onCommands.begin()+i, dummy);
                offCommands.insert(offCommands.begin()+i, dummy);
            }
        }

        ~RemoteControl(){
            for (int i=0; i<n_slots; i++){
                onCommands.insert(onCommands.begin()+i, nullptr);
                offCommands.insert(offCommands.begin()+i, nullptr);
            }
            delete dummy;
        }

        void setCommand(int slot, Command* onCommand, Command* offCommand){
            onCommands.insert(onCommands.begin()+slot, onCommand);
            offCommands.insert(offCommands.begin()+slot, offCommand);
        }
        
        void onButtonWasPushed(int slot){
            onCommands[slot]->execute();
        }

        void offButtonWasPushed(int slot){
            offCommands[slot]->execute();
        }
        
        void toString(){
            std::cout << "- - - Remote Control - - -" << std::endl;
            
            for (int i=0; i<n_slots; i++){
                std::cout << "[Slot " << i << "] " << onCommands[i]->toString() << " /// " 
                    << offCommands[i]->toString() << std::endl;
            }
            std::cout << std::endl;
        }
};

class RemoteLoader {

    public:

        RemoteControl* remoteControl;

        void main(){
            
            remoteControl = new RemoteControl(7);
            
            Light* livingRoomLight = new Light("Living Room");
            Light* kitchenLight = new Light("Kitchen");
            CeilingFan* ceilingFan= new CeilingFan("Living Room");
            GarageDoor* garageDoor = new GarageDoor();
            Stereo* stereo = new Stereo("Living Room");
            
            LightOnCommand* livingRoomLightOn = new LightOnCommand(livingRoomLight);
            LightOffCommand* livingRoomLightOff = new LightOffCommand(livingRoomLight);
            LightOnCommand* kitchenLightOn = new LightOnCommand(kitchenLight);
            LightOffCommand* kitchenLightOff = new LightOffCommand(kitchenLight);
            CeilingFanHighCommand* ceilingFanOn = new CeilingFanHighCommand(ceilingFan);
            CeilingFanOffCommand* ceilingFanOff = new CeilingFanOffCommand(ceilingFan);
            GarageDoorUpCommand* garageDoorUp = new GarageDoorUpCommand(garageDoor);
            GarageDoorDownCommand* garageDoorDown = new GarageDoorDownCommand(garageDoor);
            StereoOnWithCDCommand* stereoOnWithCD = new StereoOnWithCDCommand(stereo);
            StereoOffCommand* stereoOff = new StereoOffCommand(stereo);
            
            remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);
            remoteControl->setCommand(1, kitchenLightOn, kitchenLightOff);
            remoteControl->setCommand(2, ceilingFanOn, ceilingFanOff);
            remoteControl->setCommand(3, stereoOnWithCD, stereoOff);
            
            remoteControl->toString();

            remoteControl->onButtonWasPushed(0);
            remoteControl->offButtonWasPushed(0);
            remoteControl->onButtonWasPushed(1);
            remoteControl->offButtonWasPushed(1);
            remoteControl->onButtonWasPushed(2);
            remoteControl->offButtonWasPushed(2);
            remoteControl->onButtonWasPushed(3);
            remoteControl->offButtonWasPushed(3);

            delete remoteControl;
            delete livingRoomLightOn;
            delete livingRoomLightOff;
            delete kitchenLightOn;
            delete kitchenLightOff;
            delete ceilingFanOn;
            delete ceilingFanOff;
            delete garageDoorUp;
            delete garageDoorDown;
            delete stereoOnWithCD;
            delete stereoOff;
            delete livingRoomLight;
            delete kitchenLight;
            delete ceilingFan;
            delete garageDoor;
            delete stereo;
        }
};

int main(){
    RemoteLoader remoteLoader = RemoteLoader();
    remoteLoader.main();
}