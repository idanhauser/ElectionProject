#pragma once
#include "ElectionRound.h"

namespace elec
{
	class RegularElectionRound :public elec::ElectionRound
	{
	public:
		RegularElectionRound() = delete;
		explicit RegularElectionRound(int date[DATE_SIZE]);
	virtual bool addNewDistrict(const char str[MAX_SIZE], int numberRepresentatives, int& districtId) override;
		virtual ~RegularElectionRound() override;
	};
}
