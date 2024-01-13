
#include "ThreadSimulation.h"

#include <gtest/gtest.h>

std::vector<bool> ThreadSimulation::m_forks {{false, false}};
std::mutex ThreadSimulation::m_mutex;

void printUsage(void) {
    std::cout << "Usage: ./philo number_of_philosphers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]" << std::endl;
    std::cout << "[number_of_times_each_philosopher_must_eat] is optional" << std::endl;
}

bool isDigit(int argc, char **argv) {
    int i = 1;
    while (i < argc) {
        int j = 0;
        while (argv[i][j] != '\0') {
            if (argv[i][j] < 48 || argv[i][j] > 57) {
                std::cout << "Not a digit" << std::endl;
                return false;
            }
            j++;
        }
        i++;
    }
    return true;
}

int main (int argc, char **argv) {
    if (argc < 5 || argc > 6 || !isDigit(argc, argv)) {
        printUsage();
        return (0);
    }

    const int philosopherTotal {std::stoi(argv[1], 0, 10)};
    const int timeToDie {std::stoi(argv[2], 0, 10)};
    const int timeToEat {std::stoi(argv[3], 0, 10)};
    const int timeToSleep {std::stoi(argv[4], 0, 10)};
    const int mustEat {argc == 6 ? std::stoi(argv[5], 0, 10) : -1};

    std::cout << "total: " << philosopherTotal << " timetodie: " << timeToDie << " timetoeat: " << timeToEat << " timetosleep: " << timeToSleep << " mustEat: " << mustEat << std::endl;
    ThreadSimulation simulation {philosopherTotal, timeToDie, timeToEat, timeToSleep, mustEat};
    simulation.initSimulation();
    
    return (0);
    //testing::InitGoogleTest();
    //return (RUN_ALL_TESTS());
}
