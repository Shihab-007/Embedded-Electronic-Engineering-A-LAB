#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include<unistd.h>
#include <iterator>
#include <algorithm>

unsigned int microsecond = 1000000;

#define N 6

int blocks[4]; //4 blocks in the cross section
int list[N+1]; 
int len;
int nmbr_events;
int event;
int random_car;

std::string targetStatus; //for checking how many cars have the same status
int count = 0; //for checking how many cars have the same status

std::string currentLoc;
std::string currentAc;
int actionSwitch;
std::string currentStatus;
int currentTiming;

class Car {
private:
    int id;
    int priority;
    int timing; // timing for cars: starts at 0 - at 1 is approaching - at 2 is either approaching or stops - at 3 is crossing or starting - at 4 leaves or crosses(if stop) 
    std::string location;
    std::string action;
    std::string status;
    

public:
    Car(int carId): status("Out of Range"), timing(0) {
        id = carId;
        priority = rand() % 3 + 1;

        // Randomly assign location
        int locationIndex = rand() % 4;
        switch (locationIndex) {
            case 0:
                location = "A";
                break;
            case 1:
                location = "B";
                break;
            case 2:
                location = "C";
                break;
            case 3:
                location = "D";
                break;
        }

        // Randomly assign action
        int actionIndex = rand() % 3;
        switch (actionIndex) {
            case 0:
                action = "Straight";
                break;
            case 1:
                action = "Left Turn";
                break;
            case 2:
                action = "Right Turn";
                break;
        }
    }

    void printCarInfo() const {
        std::cout << "Car ID: " << id << std::endl;
        std::cout << "Priority: " << priority << std::endl;
        std::cout << "Location: " << location << std::endl;
        std::cout << "Action: " << action << std::endl;
    }
    
    void printCarStatus() const {
        std::cout << "Car ID: " << id << std::endl;
        std::cout << "priority: " << priority << std::endl;
    }
    
    void printCarStatusOnly()
    {
        std::cout << "\nstatus: " << status << "\n" << std::endl;
    }
    
    void setCarStatus()
    {
        currentStatus = status;
    }
    
    void printCurrentStatus()
    {
        std::cout << "\nCurrentStatus: " << currentStatus << "\n" << std::endl;
    }
    
    void printcurrentTiming()
    {
        std::cout << "\nCurrentTiming: " << currentTiming << "\n" << std::endl;
    }
    
    void setCarTiming() const
    {
        currentTiming = timing;
    }
    
    void timingAdvance()
    {   
        timing=timing+1;
    }
    
    void printTiming()
    {
        std::cout << "\nTiming of car: " << id << "\n= " << timing << std::endl;
    }
    
    void setCarInfo() const{
        currentAc = action;
        currentLoc = location;
        
        std::cout << "\nCurrentLoc = '" << currentLoc << "'\n" << std::ends;
    }

    int getID() const {
        return id;
    }
    
    
    void statusAdvance(){
        
        std::cout << "\nOld status: " << status << "\n" << std::ends;
        
        if (status == "Out of Range")
        {
            status = "approaching";
        }
        else if (status == "approaching")
        {
            status = "crossing";   
        }
        else if (status == "crossing")
        {
            status = "Out of Range";
            timing = 0;
        }
        
        else if (status == "stop")
        {
            status = "crossing";
            timing = 3;
        }
        
        std::cout << "\nNew Status: " << status << "\n" << std::ends;
    }
    
    void statusStop()
    {
        if (status == "approaching")
        {
            status = "stop";
        }
        else
        {   
            std::cout << "Can't stop the car at this state, please use statusAdvance. current status:  " << status << std::ends;
        }
    }
    
    std::string getStatus() {
        return status;
    }
};

void checkCarID(const Car& car) {
    int carID = car.getID();
    std::cout << "Checking car ID: " << carID << std::endl;
    // Perform other operations with the car ID...
}

std::vector<Car> cars;

void spawnCar() {
    const int maxCars = 6;
    if (cars.size() < maxCars) {
        int carId = cars.size() + 1;
        Car car(carId);
        cars.push_back(car);
        std::cout << "Car spawned with ID: " << carId << std::endl;
    } else {
        std::cout << "Cannot spawn more cars. Maximum limit reached." << std::endl;
    }
}

int randomizer(int nmbr_events){
    int event;
    event = rand() % nmbr_events+1;
    return event;
}

void blockUpdateCross()
{   
    if(currentAc=="Right Turn")
    {
        actionSwitch = 1;
    }
    else if(currentAc=="Straight")
    {
        actionSwitch = 2;
    }
    else if(currentAc=="Left Turn")
    {
        actionSwitch = 3;
    }
    
    if (currentLoc == "A")
    {
        switch(actionSwitch)
        {
            case 1:
                blocks[0] = 1;
                break;
            case 2:
                blocks[0] = 1;
                blocks[2] = 1;
                break;
            case 3:
                blocks[0] = 1;
                blocks[2] = 1;
                blocks[3] = 1;
                break;
        }
    }
        
    if (currentLoc == "B")
    {
        switch(actionSwitch)
        {
            case 1:
                blocks[3] = 1;
                break;
            case 2:
                blocks[1] = 1;
                blocks[3] = 1;
                break;
            case 3:
                blocks[0] = 1;
                blocks[1] = 1;
                blocks[3] = 1;
                break;
        }
    }
        
    if (currentLoc == "C")
    {
        switch(actionSwitch)
        {
            case 1:
                blocks[1] = 1;
                break;
            case 2:
                blocks[0] = 1;
                blocks[1] = 1;
                break;
            case 3:
                blocks[0] = 1;
                blocks[1] = 1;
                blocks[2] = 1;
                break;
        }
    }
        
    if (currentLoc == "D")
    {
        switch(actionSwitch)
        {
            case 1:
                blocks[2] = 1;
                break;
            case 2:
                blocks[2] = 1;
                blocks[3] = 1;
                break;
            case 3:
                blocks[1] = 1;
                blocks[2] = 1;
                blocks[3] = 1;
                break;
        }
    }
    
    std::cout << "Blocks array =" << std::ends;
    using namespace std;
      copy(blocks,
           blocks + sizeof(blocks) / sizeof(blocks[0]),
           ostream_iterator<short>(cout, "\n"));
}

void blockUpdateLeave()
{   
    if(currentAc=="Right Turn")
    {
        actionSwitch = 1;
    }
    else if(currentAc=="Straight")
    {
        actionSwitch = 2;
    }
    else if(currentAc=="Left Turn")
    {
        actionSwitch = 3;
    }
    
    if (currentLoc == "A")
    {
        switch(actionSwitch)
        {
            case 1:
                blocks[0] = 0;
                break;
            case 2:
                blocks[0] = 0;
                blocks[2] = 0;
                break;
            case 3:
                blocks[0] = 0;
                blocks[2] = 0;
                blocks[3] = 0;
                break;
        }
    }
        
    if (currentLoc == "B")
    {
        switch(actionSwitch)
        {
            case 1:
                blocks[3] = 0;
                break;
            case 2:
                blocks[1] = 0;
                blocks[3] = 0;
                break;
            case 3:
                blocks[0] = 0;
                blocks[1] = 0;
                blocks[3] = 0;
                break;
        }
    }
        
    if (currentLoc == "C")
    {
        switch(actionSwitch)
        {
            case 1:
                blocks[1] = 0;
                break;
            case 2:
                blocks[0] = 0;
                blocks[1] = 0;
                break;
            case 3:
                blocks[0] = 0;
                blocks[1] = 0;
                blocks[2] = 0;
                break;
        }
    }
        
    if (currentLoc == "D")
    {
        switch(actionSwitch)
        {
            case 1:
                blocks[2] = 0;
                break;
            case 2:
                blocks[2] = 0;
                blocks[3] = 0;
                break;
            case 3:
                blocks[1] = 0;
                blocks[2] = 0;
                blocks[3] = 0;
                break;
        }
    }
    
    std::cout << "Blocks array =" << std::ends;
    using namespace std;
      copy(blocks,
           blocks + sizeof(blocks) / sizeof(blocks[0]),
           ostream_iterator<short>(cout, "\n"));
}


int blockCheck()
{
   if(currentAc=="Right Turn")
    {
        actionSwitch = 1;
    }
    else if(currentAc=="Straight")
    {
        actionSwitch = 2;
    }
    else if(currentAc=="Left Turn")
    {
        actionSwitch = 3;
    }
    
    if (currentLoc == "A")
    {
        switch(actionSwitch)
        {
            case 1:
                if (blocks[0] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
            case 2:
                if(blocks[0] == 1 || blocks[2] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
            case 3:
                if(blocks[0] == 1 || blocks[2] == 1 || blocks[3] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
        }
    }
        
    if (currentLoc == "B")
    {
        switch(actionSwitch)
        {
            case 1:
                if(blocks[3] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
            case 2:
                if(blocks[1] == 1 || blocks[3] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
            case 3:
                if(blocks[0] == 1 || blocks[1] == 1 || blocks[3] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
                
        }
    }
        
    if (currentLoc == "C")
    {
        switch(actionSwitch)
        {
            case 1:
                if(blocks[1] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
            case 2:
                if(blocks[0] == 1 || blocks[1] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
            case 3:
                if(blocks[0] == 1 || blocks[1] == 1 || blocks[2] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
        }
    }
        
    if (currentLoc == "D")
    {
        switch(actionSwitch)
        {
            case 1:
                if(blocks[2] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
            case 2:
                if(blocks[2] == 1 || blocks[3] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
            case 3:
                if(blocks[1] == 1 || blocks[2] == 1 || blocks[3] == 1)
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                
                break;
        }
    } 
}

void enqueue()
{   
    std::cout << "Enqueueing car with ID: " << random_car << std::endl;
    list[len++] = random_car;
    std::cout << "\nLen = : " << len << std::endl;
    std::cout << "\nList =" << std::endl;
    using namespace std;
      copy(list,
           list + sizeof(list) / sizeof(list[0]),
           ostream_iterator<short>(cout, "\n"));
}

void dequeue()
{   
    std::cout << "\nDequeuing" << std::endl;
    
    int i = 0;
        len -= 1;
        while (i < len)
        {
                list[i] = list[i + 1];
                i++;
        }
        list[i] = 0;
    std::cout << "\nLen = : " << len << std::endl;
    std::cout << "\nList =" << std::endl;
    using namespace std;
      copy(list,
           list + sizeof(list) / sizeof(list[0]),
           ostream_iterator<short>(cout, "\n"));
}

enum class State {
    FREE,
    OCCUPIED,
    PROCESSING
};

int main() {
    // Initialize random seed
    srand(time(0));
    
    
    State currentState = State::FREE;
    while(true)
    {
    switch(currentState) {
        case State::FREE:
        
            std::cout << "State = FREE." << std::endl;
            spawnCar();
            spawnCar();
            spawnCar();
            spawnCar();
            spawnCar();
            spawnCar();
            
            while(true)
            {
                
            
                //possible events: A car spawns, A car approaches
                
                std::cout << cars.size() << std::ends;
                
                usleep(3*microsecond);
                event = randomizer(2);
                
                // Print information of all cars
                for (const Car& car : cars) {
                    car.printCarInfo();
                    std::cout << std::endl;
                }
                
                if (event == 1) // Spawn car
                {
                    spawnCar();
                }
                else if (event == 2) //car approaches
                {   
                    random_car = rand() % cars.size()+1;
                    
                    Car(random_car).printCarStatus();
                    cars[random_car-1].statusAdvance();
                    
                    cars[random_car-1].printCarStatusOnly();
                    cars[random_car-1].setCarStatus();
                    cars[random_car-1].printCurrentStatus();
                    cars[random_car-1].timingAdvance();
                    cars[random_car-1].setCarTiming();
                    cars[random_car-1].printcurrentTiming();
                    std::cout << "State Change. car approaches" << std::endl;
                    currentState = State::OCCUPIED;
                    enqueue();
                    
                    cars[random_car-1].statusAdvance();
                    cars[random_car-1].printCarStatusOnly();
                    cars[random_car-1].setCarStatus();
                    cars[random_car-1].printCurrentStatus();
                    
                    cars[random_car-1].setCarInfo();
                    blockUpdateCross();
                    
                    break;
                }
            
                
            }
            
            break;
            
        case State::OCCUPIED:
            
            std::cout << "State = OCCUPIED." << std::endl;
            
            while(true)
            {
              usleep(3*microsecond);
              
              
              for (int i = 0; i<len; i++)
              {     
                    random_car = list[i];
                    cars[random_car-1].setCarTiming();
                    cars[random_car-1].setCarStatus();
                    cars[random_car-1].setCarInfo();
                    std::cout << "timing of car '" << random_car << "' = " << currentTiming << std::endl;
                    
                    
                    if (currentTiming == 4 && currentStatus == "crossing")
                    {
                        dequeue();
                        cars[random_car-1].statusAdvance();
                        blockUpdateLeave();
                        std::cout << "Car '" << random_car << "' has left the cross section\n" << std::endl;
                    }
                    
                    else if(currentTiming == 2 && currentStatus == "approaching")
                    {
                        if (blockCheck() == 1)
                        {   
                            std::cout<<"this car can go\n" << std::ends;
                            cars[random_car-1].statusAdvance();
                            blockUpdateCross();
                        }
                        else if (blockCheck()==0)
                        {
                            std::cout<<"this car has to stop\n" << std::ends;
                            cars[random_car-1].statusStop();
                        }
                    }
                    
                    else if (currentStatus == "stop")
                    {
                        if (blockCheck() == 1)
                        {   
                            std::cout<<"this car can go now\n" << std::ends;
                            cars[random_car-1].statusAdvance();
                            blockUpdateCross();
                        }
                        else if (blockCheck()==0)
                        {
                            std::cout<<"this car can not start yet\n" << std::ends;
                        }
                    }
              }
              
              event = randomizer(2);     
              if (event == 1) //time passes for every car
              {
                   targetStatus=cars[0].getStatus();
               if (targetStatus == "crossing" || targetStatus == "approaching" || targetStatus == "leaving")
               {
                   cars[0].timingAdvance();
                   std::cout << "\ntiming advanced\n" << std::endl;
               }
                targetStatus=cars[1].getStatus();
               if (targetStatus == "crossing" || targetStatus == "approaching" || targetStatus == "leaving")
               {
                   cars[1].timingAdvance();
                   std::cout << "\ntiming advanced\n" << std::endl;
               }
               targetStatus=cars[2].getStatus();
               if (targetStatus == "crossing" || targetStatus == "approaching" || targetStatus == "leaving")
               {
                   cars[2].timingAdvance();
                   std::cout << "\ntiming advanced\n" << std::endl;
               }
               targetStatus=cars[3].getStatus();
               if (targetStatus == "crossing" || targetStatus == "approaching" || targetStatus == "leaving")
               {
                   cars[3].timingAdvance();
                   std::cout << "\ntiming advanced\n" << std::endl;
               }
               targetStatus=cars[4].getStatus();
               if (targetStatus == "crossing" || targetStatus == "approaching" || targetStatus == "leaving")
               {
                   cars[4].timingAdvance();
                   std::cout << "\ntiming advanced\n" << std::endl;
               }
               targetStatus=cars[5].getStatus();
               if (targetStatus == "crossing" || targetStatus == "approaching" || targetStatus == "leaving")
               {
                   cars[5].timingAdvance();
                   std::cout << "\ntiming advanced\n" << std::endl;
               }
              }
               
              if (event == 2) //another car approaches
              {
                   currentStatus = "";
                   
                    while (true)
                    {
                        random_car = rand() % cars.size()+1;
                        currentStatus = cars[random_car-1].getStatus();
                        if (currentStatus == "Out of Range")
                        {
                            break;
                        }
                   }
                   
                   cars[random_car-1].statusAdvance();
                   cars[random_car-1].timingAdvance();
                   enqueue();
                   std::cout << "\nnew approaching car with ID: " << random_car << "\n" << std::ends;
              }
               
            }
            
    
            
            
            
            break;
            
        default:
            std::cout << "Invalid state." << std::endl;
    }
    
    }
}
