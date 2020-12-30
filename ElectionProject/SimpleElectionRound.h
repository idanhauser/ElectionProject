﻿//code verison 2.0
#pragma once
#include "ElectionRound.h"

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
		virtual bool addNewDistrict(const char str[MAX_SIZE], int number_representatives, int& districtId, DistcritType districtType)override ;
		virtual ~SimpleElectionRound() override;
		virtual void save(ofstream& outFile) const override;
	};
}