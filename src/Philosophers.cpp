#include "Philosophers.h"
#include "ThreadSimulation.h"
#include <chrono>
#include <iostream>

Philosophers::Philosophers(int nbr, State state, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount, std::chrono::system_clock::time_point startTimer, bool &endGame, int total)
    : m_nbr(nbr),
    m_state(state),
    m_timeToDie(std::chrono::milliseconds(timeToDie)),
    m_timeToEat(std::chrono::milliseconds(timeToEat)),
    m_timeToSleep(std::chrono::milliseconds(timeToSleep)),
    m_mustEatCount(mustEatCount),
    m_startTimer(startTimer),
    m_endGame(endGame),
    m_totalPhilo(total)
{
};

void Philosophers::init() {
    std::cout << "------------" << std::endl;
    std::cout << "Philosopher " << m_nbr << std::endl;
    m_lastMealTimer = std::chrono::high_resolution_clock::now();

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
}

auto Philosophers::currentTimeInMilliSeconds() {
    using namespace std::chrono;
    
    return duration_cast<milliseconds>(high_resolution_clock::now() - m_startTimer).count();
}

void Philosophers::pickUpFork() {
    while (!ThreadSimulation::pickUpForkOrPutDown(m_nbr - 1, m_totalPhilo, true)) {
        checkIfDead();
        if (State::DEAD == m_state) {
            return;
        }
    }
    
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " has taken a fork" << std::endl;
}

void Philosophers::startEating() {
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is eating " << m_eatCount << "/" << m_mustEatCount << std::endl;
    
    std::this_thread::sleep_until(std::chrono::high_resolution_clock::now() + m_timeToEat);
    
    ThreadSimulation::pickUpForkOrPutDown(m_nbr - 1, m_totalPhilo, false);
    
    m_lastMealTimer = std::chrono::high_resolution_clock::now();
    m_eatCount++;
    if (m_eatCount == m_mustEatCount) {
        m_state = State::FINISHED;
    }
}

void Philosophers::goToSleep() {
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is sleeping" << std::endl;
    std::this_thread::sleep_until(std::chrono::high_resolution_clock::now() + m_timeToSleep);
    checkIfDead();
}

void Philosophers::startThinking() {
    std::cout << currentTimeInMilliSeconds() << " milliseconds: " << m_nbr << " is thinking" << std::endl;
}

void Philosophers::checkIfDead() {
    const auto end = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_lastMealTimer).count();

    if (milliseconds >= m_timeToDie.count()) {
        m_state = State::DEAD;
        std::cout << milliseconds << " milliseconds: " << m_nbr << " died" << std::endl;
    }
}

void Philosophers::changeState() {
    if (m_endGame) {
        m_state = State::FINISHED;
    }
    switch(m_state) {
        case State::FORK:
            m_state = State::EATING;
            pickUpFork();
            break;
        case State::EATING:
            m_state = State::SLEEPING;
            startEating();
            break;
        case State::SLEEPING:
            m_state = State::THINKING;
            goToSleep();
            break;
        case State::THINKING:
            m_state = State::FORK;
            startThinking();
            break;
        case State::DEAD:
            std::cout << "philosopher: " << m_nbr << " died" << std::endl;
            m_endGame = true;
            return;
        case State::FINISHED:
            if (m_endGame) {
                std::cout << "philosopher: " << m_nbr << " stopped because other philosopher died" << std::endl;
                return;
            }
            std::cout << "philosopher: " << m_nbr << " finished" << std::endl;
            return;
        default:
            break;
    }
    changeState();
}
