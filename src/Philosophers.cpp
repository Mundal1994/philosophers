#include "Philosophers.h"

#include <chrono>
#include <iostream>

Philosophers::Philosophers(int nbr, State state, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount, Forks* forkLeft, Forks* forkRight, std::chrono::high_resolution_clock::time_point startTimer, bool &endGame)
    : m_nbr(nbr),
    m_state(state),
    m_timeToDie(std::chrono::milliseconds(timeToDie)),
    m_timeToEat(std::chrono::milliseconds(timeToEat)),
    m_timeToSleep(std::chrono::milliseconds(timeToSleep)),
    m_mustEatCount(mustEatCount),
    m_startTimer(startTimer),
    m_endGame(endGame)
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

auto Philosophers::currentTimeInMilliSeconds() {
    using namespace std::chrono;
    
    return duration_cast<milliseconds>(high_resolution_clock::now() - m_startTimer).count();
}

void Philosophers::pickUpFork() {
    while (m_forks[LEFT]->isInitialized()) {
        checkIfDead();
    }
    while (m_forks[RIGHT]->isInitialized()) {
        checkIfDead();
    }
    
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " has taken a fork" << std::endl;
}

void Philosophers::startEating() {
    
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is eating" << std::endl;
    std::this_thread::sleep_for(m_timeToEat);
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is FINISHED eating" << std::endl;
    
    
    m_forks[LEFT]->deInitialize();
    m_forks[RIGHT]->deInitialize();

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
    if (m_endGame && m_state != State::DEAD) {
        m_state = State::FINISHED;
    }
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
            m_endGame = true;
            break;
        case State::FINISHED:
            if (m_endGame) {
                return;
            }
            std::cout << "philosopher: " << m_nbr << " finished" << std::endl;
            return;
        default:
            break;
    }
    changeState();
}
