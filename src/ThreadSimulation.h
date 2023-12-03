#pragma once

#include "Philosophers.h"

#include <thread>
#include <vector>

/*
    threads???
    time_to_die
    time_to_eat
    time_to_sleep
    times_philosophers_must_eat
    philosphers[]

    setupPhilosophers
*/

class ThreadSimulation {
private:
    const int m_totalPhilosophers;
    std::vector<Philosophers> m_philo;
    std::vector<Forks> m_forks;
    // thread of philosphers?
public:
    ThreadSimulation(int total, int timeToDie, int timeToEat, int timeToSleep);
    ThreadSimulation(int total, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount);

    int getTotalPhilosophers(void) const;

    void initForks();
    void initPhilosophers(int timeToDie, int timeToEat, int timeToSleep, int mustEatCount);
};
