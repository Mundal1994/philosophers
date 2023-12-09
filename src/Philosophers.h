#pragma once

#include "Forks.h"

#include <array>
#include <memory>
#include <thread>

class Philosophers {
public:
    enum class State {
        FORK,
        EATING,
        SLEEPING,
        THINKING,
        DEAD,
        FINISHED,
    };

    Philosophers(int nbr, State state, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount, Forks* forkLeft, Forks* forkRight, std::chrono::system_clock::time_point startTimer);
    void init();

    int64_t currentTimeInMilliSeconds();

    void pickUpFork();
    void startEating();
    void goToSleep();
    void startThinking();

    void startStateLogic();
    void changeState();
    void checkIfDead();
private:
    enum ForkSide {
        LEFT = 0,
        RIGHT = 1,
    };

    const int m_nbr;
    State m_state;
    const std::chrono::milliseconds m_timeToDie;
    const std::chrono::milliseconds m_timeToEat;
    const std::chrono::milliseconds m_timeToSleep;
    const int m_mustEatCount;
    int m_eatCount;
    std::chrono::system_clock::time_point m_startTimer;
    std::chrono::system_clock::time_point m_lastMealTimer;

    std::array<Forks*, 2> m_forks;
    std::thread m_thread;
};
