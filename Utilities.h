// Name: Ryan Locke
// Seneca Student ID: 034748129
// Seneca email: rclocke1@myseneca.ca
// Date of completion: April 16, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H__
#define SDDS_UTILITIES_H__
#include <iostream>
#include<algorithm>
#include<vector>
#include<list>

namespace sdds
{
    class Utilities
    {
        static char m_delimiter;
        size_t m_widthField = 1;
    public:
        Utilities();
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
    std::string removeSpaces(const std::string& s);
}
#endif