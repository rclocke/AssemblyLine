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
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
	static size_t m_count = 0;

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
		Utilities util;
		size_t next_pos = 0;
		auto more = true;
		std::string record;
		std::string nextRecord;
		std::ifstream f(file);

		while (!f.eof())
		{
			std::getline(f, record);
			next_pos = 0;

			nextRecord = util.extractToken(record, next_pos, more); 
			auto station1 = find_if(stations.begin(), stations.end(), [nextRecord](Workstation* s)
				{
					return s->getItemName() == nextRecord;
				});

			if (more)
			{
				nextRecord = util.extractToken(record, next_pos, more);
			}
			else
			{
				nextRecord = "";
			}

			if (station1 != stations.end())
			{
				auto station2 = find_if(stations.begin(), stations.end(), [nextRecord](Workstation* s)
					{
						return s->getItemName() == nextRecord;
					});
				if (station2 != stations.end())
				{
					(*station1)->setNextStation(*station2);
				}
				else
				{
					(*station1)->setNextStation(nullptr);
				}

				m_activeLine.push_back(*station1);
			}
		}
		for (auto i = m_activeLine.begin(); i != m_activeLine.end(); i++)
		{
			int value = count_if(m_activeLine.begin(), m_activeLine.end(), [i](Workstation* s)
				{
					return s->getNextStation() == *i;
				});

			if (value == 0)
			{
				m_firstStation = *i;
				break;
			}
		}

		m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations()
    {
		vector<Workstation*> temp;
		temp.push_back(m_firstStation);
		temp.push_back(m_firstStation->getNextStation());

		for_each(m_activeLine.begin(), m_activeLine.end() - 2,[&](Workstation* station)
			{
				temp.push_back(temp.back()->getNextStation());
			});

		m_activeLine = temp;
    }

    bool LineManager::run(std::ostream& os)
    {
		os << "Line Manager Iteration: " << ++m_count << std::endl;

		if (g_pending.size() > 0)
		{
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws)
			{
				ws->fill(os);
			});

		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws)
			{
				ws->attemptToMoveOrder();
			});

		if ((g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder)
		{
			return true;
		}
		return false;
    }

    void LineManager::display(std::ostream& os) const
    {
		for (size_t i = 0; i < m_activeLine.size(); i++)
		{
			m_activeLine[i]->display(os);
		}
    }
}