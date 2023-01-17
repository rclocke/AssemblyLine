// Name: Ryan Locke
// Seneca Student ID: 034748129
// Seneca email: rclocke1@myseneca.ca
// Date of completion: April 16, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H__
#define SDDS_LINEMANAGER_H__
#include <iostream>
#include<algorithm>
#include<vector>
#include<list>
#include"Workstation.h"

namespace sdds
{
    class LineManager
    {
        std::vector<Workstation*> m_activeLine{};
        size_t m_cntCustomerOrder{};
        Workstation* m_firstStation{};
    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif