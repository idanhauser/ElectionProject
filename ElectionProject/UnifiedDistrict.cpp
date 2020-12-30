//code verison 2.0              
#include "UnifiedDistrict.h"
#include <iostream>
namespace elec
{
	UnifiedDistrict::UnifiedDistrict(const char* name, int numOfReps, int numOfParties) : District(name, numOfReps, numOfParties),
		_partyLeader(nullptr)
	{
	}	

	UnifiedDistrict::~UnifiedDistrict()
	{

	}



	const Citizen* UnifiedDistrict::getPartyLeader() const
	{
		return _partyLeader;
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
		os << "**********************************" << endl;
		os << "Unified Type District " << district.getName() << ", its ID is: " << (int)district.getSerialNum() << " has " << district.getNumberOfCitizens() << " citizens." << endl;
		os << "Number of representatives is : " << (double)district.getNumOfReps() << endl;
		os << "Precentage of voters: " << district.getVotersPrecentage() << "%" << endl;
		//TODO to check if the next commented line is needed
		/*<< "and the election's result is " <<(int)district._electionResult << "." << endl;*/
		for (int i = 0; i < district.getRepsByPartyLogicSize(); i++)
			if (district.getRepsByPartyID(i) != 0)
			{
				os << "Only Party Id " << i << " Leader" << endl;
				os<<"Gets all " << district.getRepsByPartyID(i) << " reps from the district." << endl;
				os << "The other party leaders get None" << endl;
			}
		os << "**********************************" << endl;
		return os;
	}


















}
