#include "ThreadSimulation.h"

#include <iostream>

ThreadSimulation::ThreadSimulation(int total, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount)
    : m_totalPhilosophers(total)
{
    initForks();
    initPhilosophers(timeToDie, timeToEat, timeToSleep, mustEatCount);
};

int ThreadSimulation::getTotalPhilosophers(void) const {
    return (m_totalPhilosophers);
}

void ThreadSimulation::initForks() {
    m_forks.reserve(m_totalPhilosophers);

    int i = 0;
    while (i < m_totalPhilosophers) {
        m_forks.push_back(false);
        ++i;
    }
}

namespace {
    int leftForkCalc(int &nbr, int &totalPhilo) {
        int result {nbr == 0 ? totalPhilo - 1 : nbr - 1};
        if (nbr == totalPhilo) {
            return (-1);
        }
        return (result);
    };
}

bool ThreadSimulation::pickUpForkOrPutDown(int rightForkIndx, int totalPhilo, bool status) {
    std::lock_guard<std::mutex> lock(m_mutex);

    const int leftForkIndx {leftForkCalc(rightForkIndx, totalPhilo)};

    if (leftForkIndx == -1 && m_forks[rightForkIndx] != status) {
        m_forks[rightForkIndx] = status;
    } else if (m_forks[leftForkIndx] != status && m_forks[rightForkIndx] != status) {
        m_forks[leftForkIndx] = status;
        m_forks[rightForkIndx] = status;
    } else {
        return false;
    }
    std::cout << "mutex is unlocked ";
    if (status) {
        std::cout << "philosopher " << rightForkIndx + 1 << " picked up forks " << leftForkIndx << " and " << rightForkIndx << std::endl;
    } else {
        std::cout << "philosopher " << rightForkIndx + 1<< " put down forks " << leftForkIndx << " and " << rightForkIndx << std::endl;
    }

    int i = 0;
    std::cout << "forks: ";
    while (i < totalPhilo) {
        if (m_forks[i]) {
            std::cout << "true, ";
        } else {
            std::cout << "false, ";
        }
        ++i;
    }
    std::cout << std::endl;

    return true;
}

void ThreadSimulation::initPhilosophers(int timeToDie, int timeToEat, int timeToSleep, int mustEatCount) {
    m_philo.reserve(m_totalPhilosophers);

    int i = 0;
    Philosophers::State state = Philosophers::State::FORK;
    const auto startTimer = std::chrono::high_resolution_clock::now();
    while (i < m_totalPhilosophers) {
        switch (state) {
        case Philosophers::State::FORK:
            if (m_totalPhilosophers == 0) {
                m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, startTimer, m_endGame, m_totalPhilosophers});
            } else {
                m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, startTimer, m_endGame, m_totalPhilosophers});
            }
            state = Philosophers::State::SLEEPING;
            break;
        case Philosophers::State::SLEEPING:
            m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, startTimer, m_endGame, m_totalPhilosophers});
            state = Philosophers::State::THINKING;
            break;
        case Philosophers::State::THINKING:
            m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, startTimer, m_endGame, m_totalPhilosophers});
            state = Philosophers::State::FORK;
            break;
        default:
            break;
        }
        ++i;
    }
}

void ThreadSimulation::initSimulation() {
    int i {0};
    m_threads.reserve(m_totalPhilosophers);
    while (i < m_totalPhilosophers) {
        m_philo[i].init();
        m_threads.push_back(std::thread(&Philosophers::changeState, m_philo[i]));
        ++i;
    }
    i = 0;
    while (i < m_totalPhilosophers) {
        if (m_threads[i].joinable()) {
            m_threads[i].join();
        }
        ++i;
    }
    std::cout << "simulation ended" << std::endl;
}
