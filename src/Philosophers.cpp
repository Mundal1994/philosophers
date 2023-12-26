#include "Philosophers.h"
#include "ThreadSimulation.h"

#include <iostream>
#include <sstream>

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

auto Philosophers::currentTimeInMilliSeconds() {
    using namespace std::chrono;
    
    return duration_cast<milliseconds>(high_resolution_clock::now() - m_startTimer).count();
}

void Philosophers::printMessage(const int nbr, const std::string str) {
    std::stringstream msg;
    msg << currentTimeInMilliSeconds() << " milliseconds: " << nbr << str << std::endl;
    std::cout << msg.str();
}

void Philosophers::init() {
    std::stringstream msg;
    m_lastMealTimer = std::chrono::high_resolution_clock::now();

    switch (m_state) {
        case State::FORK:
            msg << " init state: pick fork";
            break;
        case State::SLEEPING:
            msg << " init state: sleeping";
            break;
        default:
            break;
    }
    printMessage(m_nbr, msg.str());
}

void Philosophers::pickUpFork() {
    while (!ThreadSimulation::pickUpForkOrPutDown(m_nbr - 1, m_totalPhilo, true)) {
        checkIfDead();
        if (State::DEAD == m_state) {
            return;
        }
    }
    
    printMessage(m_nbr, " has taken a fork");
}

void Philosophers::startEating() {
    printMessage(m_nbr, " is eating");
    
    std::this_thread::sleep_until(std::chrono::high_resolution_clock::now() + m_timeToEat);
    
    ThreadSimulation::pickUpForkOrPutDown(m_nbr - 1, m_totalPhilo, false);
    
    m_lastMealTimer = std::chrono::high_resolution_clock::now();
    m_eatCount++;
    if (m_eatCount == m_mustEatCount) {
        m_state = State::FINISHED;
    }
}

void Philosophers::goToSleep() {
    printMessage(m_nbr, " is sleeping");

    std::this_thread::sleep_until(std::chrono::high_resolution_clock::now() + m_timeToSleep);

    checkIfDead();
}

void Philosophers::startThinking() {
    printMessage(m_nbr, " is thinking");
}

void Philosophers::checkIfDead() {
    const auto end = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_lastMealTimer).count();

    if (milliseconds >= m_timeToDie.count()) {
        m_state = State::DEAD;
        printMessage(m_nbr, " died");
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
            m_endGame = true;
            return;
        case State::FINISHED:
            if (m_endGame) {
                printMessage(m_nbr, " stopped because other philosopher died");
                return;
            }
            printMessage(m_nbr, " finished");
            return;
        default:
            break;
    }
    changeState();
}
