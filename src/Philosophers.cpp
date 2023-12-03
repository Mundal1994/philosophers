#include "Philosophers.h"

#include <chrono>
#include <iostream>

Philosophers::Philosophers(int nbr, State state, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount, Forks* forkLeft, Forks* forkRight, std::chrono::system_clock::time_point startTimer)
    : m_nbr(nbr), m_state(state), m_timeToDie(timeToDie), m_timeToEat(timeToEat), m_timeToSleep(timeToSleep), m_mustEatCount(mustEatCount), m_startTimer(startTimer)
{
    m_forks[LEFT] = forkLeft;
    m_forks[RIGHT] = forkRight;
    m_thread = std::thread(startStateLogic);
};

int64_t Philosophers::currentTimeInMilliSeconds() {
    const auto end = std::chrono::high_resolution_clock::now();
    
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(m_startTimer - end).count();
    return milliseconds;
}

void Philosophers::pickUpFork() {
    while (!m_forks[LEFT]->getStatus() || !m_forks[RIGHT]->getStatus()) {
        checkIfDead();
    }
    m_forks[LEFT]->setStatus(true);
    m_forks[RIGHT]->setStatus(true);
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " has taken a fork" << std::endl;
    changeState();
}

void Philosophers::startEating() {
    
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is eating" << std::endl;
    std::this_thread::sleep_for(m_timeToEat);
    
    m_forks[LEFT]->setStatus(false);
    m_forks[RIGHT]->setStatus(false);

    m_lastMealTimer = std::chrono::high_resolution_clock::now();
    m_eatCount++;
    if (m_eatCount == m_mustEatCount) {
        m_state = FINISHED;
    }
    changeState();
}

void Philosophers::goToSleep() {
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is eating" << std::endl;
    std::this_thread::sleep_for(m_timeToSleep);
    checkIfDead();
    changeState();
}

void Philosophers::startThinking() {
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is thinking" << std::endl;
    while (!m_forks[LEFT]->getStatus() || !m_forks[RIGHT]->getStatus()) {
        checkIfDead();
    }
    changeState();
}

void Philosophers::checkIfDead() {
    const auto end = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(m_lastMealTimer - end);
    if (milliseconds >= m_timeToDie) {
        m_state = DEAD;
        std::cout << milliseconds.count() << " milliseconds: " << m_nbr << " died" << std::endl;
    }
}

void Philosophers::startStateLogic() {
    switch(m_state) {
        case FORK:
            pickUpFork();
            break;
        case EATING:
            startEating();
            break;
        case SLEEPING:
            goToSleep();
            break;
        case THINKING:
            startThinking();
            break;
        case DEAD:
            break;
        case FINISHED:
            break;
        default:
            break;
    }
    changeState();
}

void Philosophers::changeState() {
    switch(m_state) {
        case FORK:
            pickUpFork();
            m_state = EATING;
            break;
        case EATING:
            startEating();
            m_state = SLEEPING;
            break;
        case SLEEPING:
            goToSleep();
            m_state = THINKING;
            break;
        case THINKING:
            startThinking();
            m_state = FORK;
            break;
        case DEAD:
            break;
        case FINISHED:
            break;
        default:
            break;
    }
}
