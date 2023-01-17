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
#include "Utilities.h"

using namespace std;

namespace sdds
{
    char Utilities::m_delimiter{};

    Utilities::Utilities()
    {
        m_widthField = 1;
    }

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        std::string token{};
        int new_pos = str.find_first_of(getDelimiter(), next_pos);
        if (str[next_pos] == m_delimiter)
        {
            more = false;
            throw("error");
        }
        else
        {
            if (str.find(getDelimiter(), next_pos) == std::string::npos)
            {
                token = str.substr(next_pos);
                more = false;
            }
            else
            {
                token = str.substr(next_pos, new_pos - next_pos);
                more = true;
                next_pos = new_pos + 1;
            }

            if (m_widthField < token.length())
            {
                m_widthField = token.length();
            }
        }
        return removeSpaces(token);
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }

    string removeSpaces(const std::string& s)
    {
        int endString;
        std::string str{};
        endString = s.find_last_not_of(" ");
        str = s.substr(0, endString + 1);
        endString = s.find_first_not_of(" ");

        return str.substr(endString, str.length());
    }
}