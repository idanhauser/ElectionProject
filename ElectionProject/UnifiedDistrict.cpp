﻿//code verison 2.5              
#include "UnifiedDistrict.h"
#include <iostream>

#include "Utils.h"

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

	const char* UnifiedDistrict::getName() const
	{
		return District::getName();
	}

	void UnifiedDistrict::toOs(ostream& os) const
	{
		int repByParty=0;
		int repSize = District::getRepsByPartyLogicSize();
		for (int i = 0; i < repSize; i++)
		{
			repByParty = District::getRepsByPartyID(i + PARTY_ID_INIT);
			if (repByParty != 0)
			{
				os << "Only Party Id " << i << " Leader" << endl;
				os << "Gets all " << repByParty << " reps from the district." << endl;
				os << "The other party leaders get None" << endl;
			}
		}
	}



















}
