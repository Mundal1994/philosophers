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
    ThreadSimulation(int timeToDie, int timeToEat, int timeToSleep);
    ThreadSimulation(int timeToDie, int timeToEat, int timeToSleep, int mustEatCount);

    int getTimeToDie(void) const;
    int getTimeToEat(void) const;
    int getTimeToSleep(void) const;
    int getMustEatCount(void) const;
};
