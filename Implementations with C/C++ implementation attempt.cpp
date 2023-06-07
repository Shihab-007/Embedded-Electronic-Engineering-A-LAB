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

std::string currentLoc;
std::string currentAc;
std::string currentStatus;
std::string currentTiming;

class Car {
private:
    int id;
    int priority;
    int timing;
    std::string location;
    std::string action;
    std::string status;
    

public:
    Car(int carId) {
        id = carId;
        priority = rand() % 3 + 1;
        timing = 0;
        status = "out of range";
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
        std::cout << "timing: " << timing << std::endl;
        std::cout << "priority: " << priority << std::endl;
        std::cout << "status: " << status << std::endl;
    }
    
    void setCarInfo() const{
        currentTiming = timing;
        currentStatus = status;
        currentAc = action;
        currentLoc = location;
    }

    int getID() const {
        return id;
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

// void blockUpdate()
// {
//     return 0;
// }

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

enum class State {
    FREE,
    OCCUPIED,
    PROCESSING
};

int main() {
    // Initialize random seed
    srand(time(0));
    spawnCar();
    
    State currentState = State::FREE;
    while(true)
    {
    switch(currentState) {
        case State::FREE:
        
            while(true)
            {
                std::cout << "State = FREE." << std::endl;
            
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
                else if (event == 2)
                {   
                    random_car = rand() % cars.size()+1;
                    Car(random_car).printCarStatus();
                    std::cout << "State Change. car approaches" << std::endl;
                    currentState = State::OCCUPIED;
                    enqueue();
                    Car(random_car).setCarInfo();
                    
                    
                    break;
                }
            
                
            }
            
            
            
            break;
        case State::OCCUPIED:
            std::cout << "State = OCCUPIED." << std::endl;
            usleep(3*microsecond);
            currentState = State::FREE;
            break;
            
            
            
            break;
        case State::PROCESSING:
            std::cout << "State = PROCESSING." << std::endl;
            
            
            
            break;
        default:
            std::cout << "Invalid state." << std::endl;
    }
    
    }
}
