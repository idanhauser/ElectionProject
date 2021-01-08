//code verison 3.0
#pragma once
#include "ElectionRound.h"
#include <string>
namespace elec
{


	class SimpleElectionRound :public ElectionRound
	{
	public:

		int _numOfReps;
	public:
		explicit SimpleElectionRound(LoadElectionSystem& loader);
		explicit SimpleElectionRound(int date[DATE_SIZE],int numOfReps);
		int getNumOfReps() const;
		virtual bool addNewDistrict(string& str, int number_representatives, int& districtId, DistcritType districtType)override ;
		virtual ~SimpleElectionRound() override;
		virtual void save(ofstream& outFile) const override;
	};
}