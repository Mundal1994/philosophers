#include "ThreadSimulation.h"

ThreadSimulation::ThreadSimulation(int timeToDie, int timeToEat, int timeToSleep)
    : m_timeToDie(timeToDie), m_timeToEat(timeToEat), m_timeToSleep(timeToSleep), m_mustEatCount(-1) {};

ThreadSimulation::ThreadSimulation(int timeToDie, int timeToEat, int timeToSleep, int mustEatCount)
    : m_timeToDie(timeToDie), m_timeToEat(timeToEat), m_timeToSleep(timeToSleep), m_mustEatCount(mustEatCount) {};

int ThreadSimulation::getTimeToDie(void) const {
    return (m_timeToDie);
}

int ThreadSimulation::getTimeToEat(void) const {
    return (m_timeToEat);
}

int ThreadSimulation::getTimeToSleep(void) const {
    return (m_timeToSleep);
}

int ThreadSimulation::getMustEatCount(void) const {
    return (m_mustEatCount);
}
