#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

#define N 6

int blocks[4]; //4 blocks in the cross section
int list[N+1];
int len;
int nmbr_events;
int event;

class Car {
private:
    int id;
    int priority;
    std::string location;
    std::string action;

public:
    Car(int carId) {
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

enum class State {
    FREE,
    OCCUPIED,
    PROCESSING
};

int main() {
    // Initialize random seed
    srand(time(0));
    
    State currentState = State::FREE;
    
    switch(currentState) {
        case State::FREE:
            std::cout << "State = FREE." << std::endl;
            
            //possible events: A car spawns, A car approaches
            
            event = randomizer(2);
            
            if (event == 1) // Spawn car
            {
                spawnCar();
            }
            else if (event == 2)
            {
                std::cout << "State Change. car approaches" << std::endl;
                currentState = State::OCCUPIED;
            }
        
            // Print information of all cars
            for (const Car& car : cars) {
                car.printCarInfo();
                std::cout << std::endl;
            }
            
            
            break;
        case State::OCCUPIED:
            std::cout << "State = OCCUPIED." << std::endl;
            
            
            
            break;
        case State::PROCESSING:
            std::cout << "State = PROCESSING." << std::endl;
            
            
            
            break;
        default:
            std::cout << "Invalid state." << std::endl;
    }
    
    
}
