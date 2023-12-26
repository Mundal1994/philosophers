#include "ThreadSimulation.h"

#include <iostream>
#include <sstream>

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

    void printDebugInfo(std::string str) {
        std::stringstream msg;
        msg << str << std::endl;
        std::cout << msg.str();
    }
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

    if (totalPhilo < 50) {
        if (status) {
            printDebugInfo("mutex is unlocked: philosopher" + std::to_string(rightForkIndx + 1) + " picked up forks " + std::to_string(leftForkIndx) + " and " + std::to_string(rightForkIndx));
        } else {
            printDebugInfo("mutex is unlocked: philosopher" + std::to_string(rightForkIndx + 1) + " put down forks " + std::to_string(leftForkIndx) + " and " + std::to_string(rightForkIndx));
        }

        int i = 0;
        std::stringstream msg;
        msg << "forks: ";
        while (i < totalPhilo) {
            if (m_forks[i]) {
                msg << "true, ";
            } else {
                msg << "false, ";
            }
            ++i;
        }
        printDebugInfo(msg.str());
    }

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
    std::cout << "Simulation ended" << std::endl;
}
