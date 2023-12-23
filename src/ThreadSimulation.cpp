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
        m_forks.push_back(Forks {i + 1});
        ++i;
    }
}

void ThreadSimulation::initPhilosophers(int timeToDie, int timeToEat, int timeToSleep, int mustEatCount) {
    m_philo.reserve(m_totalPhilosophers);

    int i = 0;
    Philosophers::State state = Philosophers::State::FORK;
    const auto startTimer = std::chrono::high_resolution_clock::now();
    std::cout << "før while loop" << std::endl;
    while (i < m_totalPhilosophers) {
        switch (state) {
        case Philosophers::State::FORK:
            std::cout << "pick fork state" << std::endl;
            if (m_totalPhilosophers == 0) {
                m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, nullptr, &m_forks[i], startTimer, m_endGame});
            } else {
                m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, &m_forks[i - 1 < 0 ? m_totalPhilosophers - 1 : i - 1], &m_forks[i], startTimer, m_endGame});
            }
            state = Philosophers::State::SLEEPING;
            break;
        case Philosophers::State::SLEEPING:
        std::cout << "pick sleeping state" << std::endl;
            m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, &m_forks[i - 1], &m_forks[i], startTimer, m_endGame});
            state = Philosophers::State::THINKING;
            break;
        case Philosophers::State::THINKING:
        std::cout << "pick thinking state" << std::endl;
            m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, &m_forks[i - 1], &m_forks[i], startTimer, m_endGame});
            state = Philosophers::State::FORK;
            break;
        default:
            break;
        }
        ++i;
    }
    std::cout << "efter while loop" << std::endl;
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
}
