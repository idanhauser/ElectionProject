#pragma once
#include "ElectionMain.h"
namespace elec
{

	class Citizen;

	class District
	{
	private:
		static int snGenerator;
		int serialNum;
		char* name;
		Citizen* eligibleCitizens;
		int phySizeEligciti;
		int logicSizeEligciti;
		double votersPercentage;


	public:
		District() = delete;///we delete default constructor
		District(const char* name,const Citizen* eligibleCitizens, int eligcit_size_);
		District(const District& other);
		~District();

		bool setName(const char* name);
		bool setEligibleCitizens(Citizen* eligible_Citizens, int size);

		const char* getName() const;
		 Citizen* getEligibleCitizens() const;
		double getVotersPercentage() const;


	};
}