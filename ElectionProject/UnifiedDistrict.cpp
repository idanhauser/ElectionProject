//code verison 2.0              
#include "UnifiedDistrict.h"
#include <iostream>
namespace elec
{


	UnifiedDistrict::UnifiedDistrict(char* name, int numOfReps) : District(name, numOfReps),
		_partyLeader(nullptr)
	{
	}

	Citizen* UnifiedDistrict::getPartyLeader() const
	{
		return this->getPartyLeader();
	}

	bool UnifiedDistrict::setLeader(const Citizen* leader)
	{
		if (leader != nullptr)
		{
			_partyLeader = leader;
			return true;
		}
		return false;
	}


	ostream& operator<<(ostream& os, const UnifiedDistrict& district)
	{
		os << "District " << district.getName() << ", its ID is: " << (int)district.getSerialNum() << " has " << district.getNumberOfCitizens() << " citizens." << endl;
		os << "Number of representatives is : " << (double)district.getNumOfReps() << endl;
		os << "Precentage of voters: " << district.getVotersPrecentage() << "%" << endl;
		//TODO to check if the next commented line is needed
		/*<< "and the election's result is " <<(int)district._electionResult << "." << endl;*/
		for (int i = 0; i < district.getRepsByPartyLogicSizeLogicSize(); i++)
			if (!district.getRepsByPartyID(i))
			{
				os << "The District Gives " << district.getRepsByPartyID(i) <<
					" Reps only for party id: " << i << endl;
			}
		return os;
	}
}
