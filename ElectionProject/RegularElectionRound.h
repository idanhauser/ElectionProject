//code verison 2.5
#pragma once
#include "ElectionRound.h"

namespace elec
{
	class LoadElectionSystem;

	class RegularElectionRound :public elec::ElectionRound
	{
	public:
		RegularElectionRound() = delete;
		explicit RegularElectionRound(LoadElectionSystem& loader);
		explicit RegularElectionRound(int date[DATE_SIZE]);
		virtual bool addNewDistrict(const char str[MAX_SIZE], int numberRepresentatives, int& districtId,
		                            DistcritType districtType) override;
		virtual ~RegularElectionRound() override;

		virtual void save(ofstream& outFile) const override;
	};
}
