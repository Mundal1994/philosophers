#pragma once
/*

Philosopher {
    number: 
    right_fork_in_use: 
    left_fork_in_use (needs to be pointer to other philosopher):
    stateChange: 
}

Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
*/
class Philosophers {
private:
    enum State {
        EATING,
        SLEEPING,
        THINKING,
    };

    const int m_nbr;
    bool m_rightForkInUse;// have these be their own static class
    bool m_leftForkInUse;// have this be their own static class
    State m_stateChange;
public:
    Philosophers(int nbr);
};
