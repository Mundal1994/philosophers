#pragma once

class Forks{
private:
    const int m_nbr;
    bool m_status {false};
public:
    Forks(int nbr);

    bool getStatus() const;
    void setStatus(bool status);
};
