//code verison 2.0
#include "District.h"
#include "Citizen.h"
#include <iostream>
#include "CitizenList.h"

using namespace std;

namespace elec {
	int District::snGenerator = DISTRICT_ID_INIT;

	District::District(const char* name, int numOfReps) : _serialNum(snGenerator++), _name(new char[strlen(name) + 1]),
		_Citizens(CitizenList()), _votersPercentage(0), _electionResult(0), _numOfReps(numOfReps),_numberOfVotesinDist(0)
	{
		strcpy(this->_name, name);
	}

	District::~District()
	{
		delete[] _name;
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

	int District::getSerialNum() const
	{
		return _serialNum;
	}

	int District::getNumberOfCitizens() const
	{
		return _Citizens.getLogicSize();
	}

	bool District::addCitizen(Citizen* citz)
	{
		_Citizens.addToList(*citz);
		return true;
	}
	//use only if you know that citizen exist
	const Citizen& District::getCitizenById(int id) const
	{
		int savePlace = -1;
		for (int j = 0; j < _Citizens.getLogicSize(); ++j)
		{
			if (_Citizens.getCitizenByIndex(j).getCitizenID() == id)
			{
				savePlace = j;
			
			}
		}
		return _Citizens.getCitizenByIndex(savePlace);
	}

	Citizen& District::getCitizenById(int id)
	{
		int savePlace = -1;
		int len = _Citizens.getLogicSize();
		for (int j = 0; j < len && savePlace == -1; ++j)
		{
			if (_Citizens.getCitizenByIndex(j).getCitizenID() == id)
			{
				savePlace = j;
			}
		}
		return _Citizens.getCitizenByIndex(savePlace);
	}

	int District::getNumOfReps() const
	{
		return _numOfReps;
	}


	bool District::isCitizenExist(int id) const
	{
		bool found = false;
		int len = _Citizens.getLogicSize();
		for (int i = 0; i < len && !found; ++i)
		{
			if (_Citizens.getCitizenByIndex(i).getCitizenID() == id)
			{
				found = true;
			}
		}
		return found;
	}

	/// <summary>
	/// the function counts how many citizen voted in this distcrit.
	/// </summary>
	/// <returns>the amount people who voted</returns>
	int District::getVotingCitizensAmountInDistrict() const
	{
		int counter = 0;
		for (int i = 0; i < _Citizens.getLogicSize(); ++i)
		{
			if(_Citizens.getCitizenByIndex(i).hasVoted())
			{
				counter++;
			}
		}
		return counter;
	}

	void District::operator++(int)
	{
		_numberOfVotesinDist++;
		_votersPercentage = (_numberOfVotesinDist / getNumberOfCitizens()) * 100;
	}


	ostream& operator<<(ostream& os, const District& district)
	{
		os << "District " << district._name << ", its ID is: " << (int)district._serialNum <<" has "<< district.getNumberOfCitizens() << " citizens." << endl;
		os << "Number of representatives is : " << (double)district._numOfReps << endl;
		//TODO to check if the next commented line is needed
		/*<< "and the election's result is " <<(int)district._electionResult << "." << endl;*/
		
		return os;
	}



}
