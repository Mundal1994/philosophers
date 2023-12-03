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

/*Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
*/