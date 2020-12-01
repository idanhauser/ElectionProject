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
		Citizen** _eligibleCitizens; //roee: should change to "List" type
		double _votersPercentage;
		int _electionResult;

		
		int phySizeEligciti;  //roee: =delete
		int logicSizeEligciti; //roee: =delete
		District(const District& other);//we don't want the ability to duplicate a district
		
	public:
		//friend class Citizen;
		District() = delete;///we delete default constructor
		District(const char* name);
	
		~District();

		bool setName(const char* name);
		bool setEligibleCitizens(Citizen** eligible_Citizens, int size); //roee: need to change from citizen** to list.

		const char* getName() const;
		double getVotersPercentage() const;
		int getElectionResults()const;
		int getSerialNum() const;
		//TODO:print function with operator..
	//	friend ostream& operator<<(ostream& os, const District& district);
	
	
	/* //roee: 
		bool Party::addEligibleCitizens(Citizen* citizen)
		{
			return _eligibleCitizens.addListMember(citizen);
		}*/

	};
}