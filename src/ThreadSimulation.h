#pragma once

#include "Philosophers.h"

#include <thread>
#include <vector>

class ThreadSimulation {
private:
    const int m_totalPhilosophers;
    std::vector<Philosophers> m_philo;
    std::vector<Forks> m_forks;
    bool m_endGame {false};
    // thread of philosphers?
public:
    ThreadSimulation(int total, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount);

    int getTotalPhilosophers(void) const;

    void initForks();
    void initPhilosophers(int timeToDie, int timeToEat, int timeToSleep, int mustEatCount);
    void initSimulation();
};
