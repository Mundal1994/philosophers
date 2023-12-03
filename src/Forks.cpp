#include "Forks.h"

Forks::Forks(int nbr) : m_nbr(nbr) {};

bool Forks::getStatus() const {
    return m_status;
}

void Forks::setStatus(bool status) {
    m_status = status;
}
