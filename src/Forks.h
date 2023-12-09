#pragma once

#include <mutex>

class Forks{
private:
    const int m_nbr;
    bool m_status {false};
    std::mutex m_mutex;
public:
    Forks(int nbr);

    bool getStatus() const;
    void setStatus(bool status);
};
