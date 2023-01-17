// Name: Ryan Locke
// Seneca Student ID: 034748129
// Seneca email: rclocke1@myseneca.ca
// Date of completion: April 16, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H__
#define SDDS_CUSTOMERORDER_H__
#include <iostream>
#include<algorithm>
#include<vector>
#include<list>
#include"Station.h"

namespace sdds
{
    class CustomerOrder
    {
        struct Item
        {
            std::string m_itemName;
            size_t m_serialNumber{ 0 };
            bool m_isFilled{ false };

            Item(const std::string& src) : m_itemName(src)
            {
            };
        };

        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item** m_lstItem{};
        static size_t m_widthField;
    public:
        CustomerOrder();
        CustomerOrder(const std::string&);
        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(const CustomerOrder&) = delete;
        CustomerOrder(CustomerOrder&&) noexcept;
        CustomerOrder& operator=(CustomerOrder&&) noexcept;
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station&, std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif