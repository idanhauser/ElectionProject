//code verison 1.0
#include <string>
#include <iostream>
#include "District.h"
#include "CitizenList.h"
using namespace std;

namespace elec {
	int District::snGenerator = 100;


	/**
	 * \brief constructor for district
	 * \param name the name of the district
	 */
	District::District(const char* name, int numOfReps) : _serialNum(snGenerator++), _name(new char[strlen(name) + 1]), _numOfReps(numOfReps),
	                                       _Citizens( CitizenList()), _votersPercentage(0), _electedMembersArr(CitizenList())
	{
		strcpy(this->_name, name);
	}
/*
	District::District(const District& other)
	{
		this->_serialNum = other._serialNum;
		this->_electionResult = other._electionResult;
		setName(const_cast<const char*>(other._name));

		setEligibleCitizens(other._eligibleCitizens, other.logicSizeEligciti);
	}
	*/



	District::~District()
	{
		delete[] _name;
		//delete[] _Citizens;//idan : im not sure
	}
	
	const char* District::getName() const
	{
		return _name;
	}

	const CitizenList& District::getEligibleCitizens() const
		{
			return _Citizens;
		}
		
	double District::getVotersPercentage() const
	{
		return _votersPercentage;
	}

	CitizenList District::getElectionResults() const
	{
		return _electedMembersArr;
	}

	int District::getSerialNum() const
	{
		return _serialNum;
	}

	int District::getNumberOfCitizens() const
	{
		return _Citizens.getLogicSize();
	}

	int District::getNumOfReps() const {
		return _numOfReps;
	}

	ostream& operator<<(ostream& os, const District& district)
	{
		os << "District " << district._name << ", id: " << (int)district._serialNum <<
			"has " << district.getNumberOfCitizens() << " citizens." << endl;
		os << "The voters percentage is: " << (double)district._votersPercentage << "and the election's result is " << 
			(int)district._electedMembersArr << "." << endl;
		os << "The people that live in this district are:" <<endl << district._Citizens << endl;
		return os;
	}


	bool District::addToElectedMembersArr(Citizen* partyMember) { //not sure if 'Citizen*'. otherwise creates bug
		static int i = 0;
		if (_electedMembersArr.addToList(partyMember))
			return true;
		else
			return false;
		
	}




}
