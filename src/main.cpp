
#include "ThreadSimulation.h"

#include <gtest/gtest.h>
/*

philosopherBase {
    time_to_die_timer
    time_to_eat_timer
    time_to_sleep_timer
}

cyclus: eat --> sleep --> think --> eat
simulation stops if philospher dies of starvation or they have eaten enough times


Your(s) program(s) should take the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: The number of philosophers and also the number
of forks.
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
• Each philosopher has a number ranging from 1 to number_of_philosophers.
• Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

*/

// Your(s) program(s) should take the following arguments:
// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]


#include <chrono>
#include <iostream>
#include <thread>
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
