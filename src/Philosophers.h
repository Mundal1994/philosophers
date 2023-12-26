#pragma once

#include <array>
#include <chrono>
#include <memory>

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

    Philosophers(int nbr, State state, int timeToDie, int timeToEat, int timeToSleep, int mustEatCount, std::chrono::system_clock::time_point startTimer, bool &endGame, int total);
    void init();

    auto currentTimeInMilliSeconds();

    void pickUpFork();
    void startEating();
    void goToSleep();
    void startThinking();

    void changeState();
    void checkIfDead();

    void printMessage(int nbr, std::string str);
private:
    const int m_nbr;
    State m_state;
    const std::chrono::milliseconds m_timeToDie;
    const std::chrono::milliseconds m_timeToEat;
    const std::chrono::milliseconds m_timeToSleep;
    const int m_mustEatCount;
    int m_eatCount;
    std::chrono::high_resolution_clock::time_point m_startTimer;
    std::chrono::high_resolution_clock::time_point m_lastMealTimer;

    bool &m_endGame;
    int m_totalPhilo;
};
