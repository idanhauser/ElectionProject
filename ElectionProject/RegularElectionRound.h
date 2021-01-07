//code verison 3.0
#pragma once
#include "ElectionRound.h"
#include <string>
namespace elec
{
	class LoadElectionSystem;

	class RegularElectionRound :public ElectionRound
	{
	public:
		RegularElectionRound() = delete;
		explicit RegularElectionRound(LoadElectionSystem& loader);
		explicit RegularElectionRound(int date_d, int date_m, int date_y)noexcept(false);
		virtual bool addNewDistrict(string& name, int numberRepresentatives, int& districtId,
		                            DistcritType districtType) override;
		virtual ~RegularElectionRound() override;

		virtual void save(ofstream& outFile) const override;
	};
}
