#pragma once
#include "ElectionMain.h"
namespace elec
{

	class Citizen;

	class District
	{
	private:
		static int snGenerator;
		int _serialNum;
		char* _name;
		Citizen** _eligibleCitizens;
		double _votersPercentage;
		int _electionResult;

		
		int phySizeEligciti;
		int logicSizeEligciti;
		District(const District& other);//we don't want the ability to duplicate a district
		const District& operator=(const District&);

	public:
		friend class Citizen;
		District() = delete;///we delete default constructor
		District(const char* name);
	
		~District();
		friend ostream& operator<<(ostream& os, const District& district);
		bool setName(const char* name);
		bool setEligibleCitizens(Citizen** eligible_Citizens, int size);

		const char* getName() const;
		double getVotersPercentage() const;
		int getElectionResults()const;
		int getSerialNum() const;
		//TODO:print function with operator..
	//	friend ostream& operator<<(ostream& os, const District& district);

	};
}