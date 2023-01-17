// Name: Ryan Locke
// Seneca Student ID: 034748129
// Seneca email: rclocke1@myseneca.ca
// Date of completion: April 16, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include<cstring>
#include<string>
#include <iomanip>
#include <exception> 
#include <sstream>
#include <algorithm>
#include "Workstation.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    Workstation::Workstation(const std::string& str) : Station(str)
    {
        m_pNextStation = nullptr;
    }

    void Workstation::fill(std::ostream& os)
    {
        if (m_orders.size() > 0)
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder()
    {
        if (m_orders.size() > 0)
        {
            if (m_orders.front().isItemFilled(getItemName()) || getQuantity() <= 0)
            {
                if (m_pNextStation)
                {
                    *m_pNextStation += move(m_orders.front());
                    m_orders.pop_front();
                    return true;
                }
                else
                {
                    if (m_orders.front().isOrderFilled())
                    {
                        g_completed.push_back(move(m_orders.front()));
                    }
                    else
                    {
                        g_incomplete.push_back(move(m_orders.front()));
                    }
                    m_orders.pop_front();
                    return true;
                }
            }
        }
        return false;
    }

    void Workstation::setNextStation(Workstation* station = nullptr)
    {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const
    {
        os << getItemName() << " --> ";
        if (m_pNextStation)
        {
            os << m_pNextStation->getItemName() << std::endl;;
        }
        else
        {
            os << "End of Line" << std::endl;
        }
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}