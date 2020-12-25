//code verison 2.0              
#include "UnifiedDistrict.h"

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

	UnifiedDistrict::~UnifiedDistrict()
	{
	}
}
