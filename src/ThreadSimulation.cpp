#include "ThreadSimulation.h"

ThreadSimulation::ThreadSimulation(int total, int timeToDie, int timeToEat, int timeToSleep)
    : m_totalPhilosophers(total)
{// , m_timeToDie(timeToDie), m_timeToEat(timeToEat), m_timeToSleep(timeToSleep), m_mustEatCount(-1)
    initForks();
    initPhilosophers(timeToDie, timeToEat, timeToSleep, -1);
};

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
    Philosophers::State state = Philosophers::EATING;
    const auto startTimer = std::chrono::high_resolution_clock::now();
    while (i < m_totalPhilosophers) {
        switch (state) {
        case Philosophers::EATING:
            if (m_totalPhilosophers == 0) {
                m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, nullptr, &m_forks[i + 1], startTimer});
            } else {
                m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, &m_forks[i - 1 < 0 ? m_totalPhilosophers - 1 : i - 1], &m_forks[i + 1], startTimer});
            }
            state = Philosophers::SLEEPING;
            break;
        case Philosophers::SLEEPING:
            m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, &m_forks[i - 1], &m_forks[i + 1], startTimer});
            state = Philosophers::THINKING;
            break;
        case Philosophers::THINKING:
            m_philo.push_back(Philosophers{i + 1, state, timeToDie, timeToEat, timeToSleep, mustEatCount, &m_forks[i - 1], &m_forks[i + 1], startTimer});
            state = Philosophers::EATING;
            break;
        default:
            break;
        }
        ++i;
    }
}
