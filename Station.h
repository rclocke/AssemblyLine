// Name: Ryan Locke
// Seneca Student ID: 034748129
// Seneca email: rclocke1@myseneca.ca
// Date of completion: April 16, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H__
#define SDDS_STATION_H__
#include <iostream>
#include<algorithm>
#include<vector>
#include<list>

namespace sdds
{
    class Station
    {
        int m_stationID{};
        std::string m_itemName{};
        std::string m_stationDesc{};
        unsigned int m_serialNum{};
        unsigned int m_itemsInStock{};
        static int m_widthField;
        static int m_id_generator;
    public:
        Station(const std::string&);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}
#endif