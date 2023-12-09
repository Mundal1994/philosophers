#include "Philosophers.h"

#include <chrono>
#include <iostream>

Philosophers::Philosophers(int nbr, State state, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount, Forks* forkLeft, Forks* forkRight, std::chrono::system_clock::time_point startTimer)
    : m_nbr(nbr),
    m_state(state),
    m_timeToDie(std::chrono::milliseconds(timeToDie)),
    m_timeToEat(std::chrono::milliseconds(timeToEat)),
    m_timeToSleep(std::chrono::milliseconds(timeToSleep)),
    m_mustEatCount(mustEatCount),
    m_startTimer(startTimer)
{
    m_forks[LEFT] = forkLeft;
    m_forks[RIGHT] = forkRight;
};

void Philosophers::init() {
    std::cout << "------------" << std::endl;
    std::cout << "Philosopher " << m_nbr << std::endl;
    switch (m_state) {
        case State::EATING:
            std::cout << "init state: eating" << std::endl;
            break;
        case State::SLEEPING:
            std::cout << "init state: sleeping" << std::endl;
            break;
        case State::THINKING:
            std::cout << "init state: thinking" << std::endl;
            break;
        default:
            break;
    }
    
    m_thread = std::thread(&Philosophers::changeState, this);
}

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
}

void Philosophers::startEating() {
    
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is eating" << std::endl;
    //std::this_thread::sleep_for(m_timeToEat);
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is FINISHED eating" << std::endl;
    
    
    m_forks[LEFT]->setStatus(false);
    m_forks[RIGHT]->setStatus(false);

    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " put down forks" << std::endl;
    
    m_lastMealTimer = std::chrono::high_resolution_clock::now();
    m_eatCount++;
    if (m_eatCount == m_mustEatCount) {
        m_state = State::FINISHED;
        std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " switched to FINISHED state" << std::endl;
    
    }
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is DONE eating" << std::endl;
}

void Philosophers::goToSleep() {
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is sleeping" << std::endl;
    std::this_thread::sleep_for(m_timeToSleep);
    checkIfDead();
}

void Philosophers::startThinking() {
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is thinking" << std::endl;
    while (!m_forks[LEFT]->getStatus() || !m_forks[RIGHT]->getStatus()) {
        checkIfDead();
    }
}

void Philosophers::checkIfDead() {
    const auto end = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(m_lastMealTimer - end);
    if (milliseconds >= m_timeToDie) {
        m_state = State::DEAD;
        std::cout << milliseconds.count() << " milliseconds: " << m_nbr << " died" << std::endl;
    }
}

void Philosophers::changeState() {
    switch(m_state) {
        case State::FORK:
            pickUpFork();
            m_state = State::EATING;
            break;
        case State::EATING:
            startEating();
            m_state = State::SLEEPING;
            break;
        case State::SLEEPING:
            goToSleep();
            m_state = State::THINKING;
            break;
        case State::THINKING:
            startThinking();
            m_state = State::FORK;
            break;
        case State::DEAD:
            std::cout << "philosopher: " << m_nbr << " is dead. end game" << std::endl;
            break;
        case State::FINISHED:
            std::cout << "philosopher: " << m_nbr << " finished" << std::endl;
            break;
        default:
            break;
    }
    changeState();
}
