//code verison 1.0
#pragma once

#include <string>
#include <iostream>
#include "CitizenList.h"
#include "Utils.h"
namespace elec
{
	class CitizenList;
	class Citizen;

	class District
	{
	private:
		static int snGenerator;
		int _serialNum;
		char* _name;
		CitizenList _Citizens;
		double _votersPercentage;
		CitizenList _electedMembersArr;
		int _numOfReps;

		District(const District& other);
		const District& operator=(const District&);

	public:
		//friend class Citizen;//TODO:idan do we need it? 
		District() = delete;///we delete default constructor
		District(const char* name, int numOfReps);

		~District();
		friend ostream& operator<<(ostream& os, const District& district);
		friend class CitizenList;
		

		const CitizenList& getEligibleCitizens() const;
		const char* getName() const;
		double getVotersPercentage() const;
		CitizenList getElectionResults()const;
		int getSerialNum() const;
		int getNumberOfCitizens() const;
		int getNumOfReps()const;
		bool addToElectedMembersArr(Citizen* partyMember) ;

	};
}