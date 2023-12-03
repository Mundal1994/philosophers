
#include "ThreadSimulation.h"

#include <iostream>
#include <gtest/gtest.h>
/*

philosopherBase {
    time_to_die_timer
    time_to_eat_timer
    time_to_sleep_timer
}

Philosopher {
    number: 
    right_fork_in_use: 
    left_fork_in_use (needs to be pointer to other philosopher):
    currentAction: 
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


---

Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
*/

// Your(s) program(s) should take the following arguments:
// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]

void printUsage(void) {
    std::cout << "Usage: ./philo number_of_philosphers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]" << std::endl;
    std::cout << "[number_of_times_each_philosopher_must_eat] is optional" << std::endl;
}

bool isDigit(int argc, char **argv) {
    int i = 1;
    while (i < argc) {
        int j = 0;
        int commaCount = 0;
        while (argv[i][j] != '\0') {
            if (argv[i][j] == 46) {
                commaCount++;
                if (commaCount > 1) {
                    std::cout << "Too many commas" << std::endl;
                    return false;
                }
            } else if (argv[i][j] < 48 || argv[i][j] > 57) {
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

    //collectData();

    int i = 1;
    int total = argc;
    while (i < total) {
        std::cout << argv[i++] << std::endl;
    }
    testing::InitGoogleTest();
    return (RUN_ALL_TESTS());
}
