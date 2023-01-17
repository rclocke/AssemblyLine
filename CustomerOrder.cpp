// Name: Ryan Locke
// Seneca Student ID: 034748129
// Seneca email: rclocke1@myseneca.ca
// Date of completion: April 17, 2022
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
#include <future>
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder()
    {

    }

    CustomerOrder::CustomerOrder(const std::string& str)
    {
        Utilities util;
        bool more = true;
        size_t nextPos = 0;

        m_name = util.extractToken(str, nextPos, more);
        m_product = util.extractToken(str, nextPos, more);
        m_cntItem = 0;
        size_t startPos = nextPos;

        while (more)
        {
            util.extractToken(str, nextPos, more);
            m_cntItem++;
        }

        m_lstItem = new Item * [m_cntItem];

        for (size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(util.extractToken(str, startPos, more));
        }

        if (util.getFieldWidth() > m_widthField)
        {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder&)
    {
        throw("----> ERROR: Cannot make copies.");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept
    {
        *this = std::move(order);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept
    {
        if (this != &order)
        {
            if (m_lstItem)
            {
                for (size_t i = 0; i < m_cntItem; i++)
                {
                    delete this->m_lstItem[i];
                }
            }
            delete[] m_lstItem;

            m_name = order.m_name;
            m_product = order.m_product;
            m_cntItem = order.m_cntItem;
            m_lstItem = order.m_lstItem;

            order.m_lstItem = nullptr;
        }

        return *this;
    }

    CustomerOrder::~CustomerOrder()
    {
        if (m_lstItem)
        {
            for (size_t i = 0; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            m_lstItem = nullptr;
        }
    }

    bool CustomerOrder::isOrderFilled() const
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (!m_lstItem[i]->m_isFilled)
            {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == itemName)
            {
                if (!m_lstItem[i]->m_isFilled)
                {
                    return false;
                }
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os)
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (!m_lstItem[i]->m_isFilled && m_lstItem[i]->m_itemName == station.getItemName())
            {
                if (station.getQuantity() > 0)
                {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    station.updateQuantity();
                    m_lstItem[i]->m_isFilled = true;

                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    return;
                }
                else
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << m_product << std::endl;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << '[' << setw(6) << setfill('0') <<right << m_lstItem[i]->m_serialNumber << setfill(' ') << "] ";
            os << setw(m_widthField) << left << m_lstItem[i]->m_itemName << " - ";
            if (m_lstItem[i]->m_isFilled)
            {
                os << "FILLED" << std::endl;
            }
            else
            {
                os << "TO BE FILLED" << std::endl;
            }
        }
    }
}