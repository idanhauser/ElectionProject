
#include "ElectionRound.h"

//code verison 1.0
#include <iostream>


#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"
using namespace std;

namespace elec
{
	ElectionRound::ElectionRound(int date[8])/*:_citizens(CitizenList()),_districts(DistrictList()),_parties(PartyList())*/
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



}

