#include "Forks.h"

#include <iostream>
#include <thread>

Forks::Forks(int nbr) : m_nbr(nbr) {};

int Forks::getNbr() const {
    return m_nbr;
}

bool Forks::getStatus() const {
    return m_status;
}

void Forks::setStatus(bool status) {
    m_status = status;
}

bool Forks::isInitialized() {
    //const std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << "isInitialized: thread #" << std::this_thread::get_id() << std::endl;
    //m_mutex.lock();
    if (m_isInitialized) {
        return true;
    }

    m_isInitialized = true;
    setStatus(true);

    //m_mutex.unlock();
    return false;
}

void Forks::deInitialize() {
    //const std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << "deInitialize: thread #" << std::this_thread::get_id() << std::endl;
    
    //m_mutex.lock();

    setStatus(false);
    m_isInitialized = false;

    //m_mutex.unlock();
}
