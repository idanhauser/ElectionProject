//code verison 2.5
#pragma once

#include "District.h"

namespace elec
{


	class UnifiedDistrict :public District
	{
		const Citizen* _partyLeader;
	public:
		UnifiedDistrict(const char* name, int numOfReps, int numOfParties);
		virtual ~UnifiedDistrict() override;

		const Citizen* getPartyLeader() const override;
		bool setLeader(const Citizen* leader)  override;
		
		//friend ostream& operator<<(ostream& os, const UnifiedDistrict& district);

		virtual void toOs(ostream& os) const override;

	
	
	};

}
