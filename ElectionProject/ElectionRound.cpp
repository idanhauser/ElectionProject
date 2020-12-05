//code verison 1.0
#include "ElectionRound.h"
#include <iostream>
#include "CitizenList.h"
#include "DistrictList.h"
#include "PartyList.h"

using namespace std;

namespace elec
{
	const int MAX_SIZE = 1024;
	ElectionRound::ElectionRound(int date[8]) :_districts(DistrictList()), _citizens(CitizenList()), _parties(PartyList())
	{

		for (int i = 0; i < 8; ++i)
		{
			this->_date[i] = date[i];
		}
	}
	
	void ElectionRound::printElectionDate() const
	{
		for (int i = 0; i < 8; ++i)
		{
			cout << static_cast<char>(_date[i] + '0');
			if (i == 1 || i == 3)
			{
				cout <<'.';
			}
		}
	}

	void ElectionRound::addNewDistrict(char name[MAX_SIZE], int numberResentatives)
	{
		District* dist = new District(name, numberResentatives);
		_districts.addToList(*dist);
	}


}

