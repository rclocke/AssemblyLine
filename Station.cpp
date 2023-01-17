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
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
    int Station::m_widthField = 0;
    int Station::m_id_generator = 0;

    Station::Station(const std::string& record)
    {
        bool flag = false;
        size_t pos{};
        Utilities util;
        m_itemName = util.extractToken(record, pos, flag);
        m_serialNum = std::stoi(util.extractToken(record, pos, flag));
        m_itemsInStock = std::stoi(util.extractToken(record, pos, flag));
        m_widthField = util.getFieldWidth();
        m_stationDesc = util.extractToken(record, pos, flag);
        m_id_generator++;
        m_stationID = m_id_generator;
    }

    const std::string& Station::getItemName() const
    {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber()
    {
        return m_serialNum++;
    }

    size_t Station::getQuantity() const
    {
        return m_itemsInStock;
    }

    void Station::updateQuantity()
    {
        if (m_itemsInStock > 0)
        {
            m_itemsInStock--;
        }
    }

    void Station::display(std::ostream& os, bool full) const
    {
        if (full)
        {
            os << std::setw(3) << std::setfill('0') << right << m_stationID << " | ";
            os << std::setw(m_widthField) << std::setfill(' ') << left << m_itemName << " | ";
            os << std::setw(6) << std::setfill('0') << right << m_serialNum << " | ";
            os << std::setw(4) << std::setfill(' ') << m_itemsInStock << " | ";
            os << m_stationDesc << endl;
        }
        else
        {
            os << std::setw(3) << std::setfill('0') << right << m_stationID << " | ";
            os << std::setw(m_widthField) << std::setfill(' ') << left << m_itemName << " | ";
            os << std::setw(6) << std::setfill('0') << right << m_serialNum << " | " << endl;
        }
    }
}