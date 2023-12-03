#pragma once

/*
    threads???
    time_to_die
    time_to_eat
    time_to_sleep
    times_philosophers_must_eat
    philosphers[]

    setupPhilosophers
*/

class ThreadSimulation {
private:
    const int m_timeToDie;
    const int m_timeToEat;
    const int m_timeToSleep;
    const int m_mustEatCount;
    // thread of philosphers?
public:
    ThreadSimulation(int timeToDie, int timeToEat, int timeToSleep)
        : m_timeToDie(timeToDie), m_timeToEat(timeToEat), m_timeToSleep(timeToSleep), m_mustEatCount(-1) {};

    ThreadSimulation(int timeToDie, int timeToEat, int timeToSleep, int mustEatCount)
        : m_timeToDie(timeToDie), m_timeToEat(timeToEat), m_timeToSleep(timeToSleep), m_mustEatCount(mustEatCount) {};

    int getTimeToDie(void) const {
        return (m_timeToDie);
    }

    int getTimeToEat(void) const {
        return (m_timeToEat);
    }

    int getTimeToSleep(void) const {
        return (m_timeToSleep);
    }

    int getMustEatCount(void) const {
        return (m_mustEatCount);
    }
};
