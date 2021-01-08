//code verison 3.1
#pragma once

#include "District.h"
#include <string>
namespace elec
{


	class UnifiedDistrict :public District
	{
		const Citizen* _partyLeader;
	public:
		UnifiedDistrict(string& name, int numOfReps, int numOfParties);
		UnifiedDistrict(LoadElectionSystem& loader);
		virtual ~UnifiedDistrict() override;

		virtual const Citizen* getPartyLeader() const override ;
		virtual bool setLeader(const Citizen* leader) override;
		/// <summary>
/// printing function of this class
/// </summary>
/// <param name="os">the file we print to.</param>
		virtual void toOs(ostream& os) const override;

	
	
	};

}
