#pragma once

#include <mutex>

class Forks{
private:
    const int m_nbr;
    bool m_status {false};
    bool m_isInitialized {false};
    //std::mutex m_mutex;
public:
    Forks(int nbr);

    int getNbr() const;
    bool getStatus() const;
    void setStatus(bool status);
    bool isInitialized();
    void deInitialize();
};
