#pragma once

#include "Philosophers.h"

#include <thread>

class ThreadSimulation {
private:
    const int m_totalPhilosophers;
    std::vector<Philosophers> m_philo;
    bool m_endGame {false};
    std::vector<std::thread> m_threads;
    static std::vector<bool> m_forks;
    static std::mutex m_mutex;
public:
    ThreadSimulation(int total, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount);

    static bool pickUpForkOrPutDown(int nbr, int totalPhilo, bool pickUp);
    
    int getTotalPhilosophers(void) const;

    void initForks();
    void initPhilosophers(int timeToDie, int timeToEat, int timeToSleep, int mustEatCount);
    void initSimulation();
};
