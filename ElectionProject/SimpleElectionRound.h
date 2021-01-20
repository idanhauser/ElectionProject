//code verison 3.2
#pragma once
#include "ElectionRound.h"
#include <algorithm>
#include <string>
namespace elec
{


	class SimpleElectionRound :public ElectionRound
	{
	public:

		int _numOfReps;
	public:
		explicit SimpleElectionRound(LoadElectionSystem& loader);
		explicit SimpleElectionRound(int date_d, int date_m, int date_y, int numOfReps) noexcept(false);
		int getNumOfReps() const;
		virtual void addNewDistrict(string& str, int number_representatives, int& districtId,
			DistcritType districtType) override;
		virtual ~SimpleElectionRound() override;
		virtual void save(ofstream& outFile) const override;
	};
}