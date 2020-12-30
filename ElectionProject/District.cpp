//code verison 2.0
#include "District.h"
#include "Citizen.h"
#include <iostream>
#include "CitizenList.h"

using namespace std;

namespace elec {
	int District::snGenerator = DISTRICT_ID_INIT;

	District::District(const char* name, int numOfReps, int numOfParties) : _serialNum(snGenerator++), _name(new char[strlen(name) + 1]),
		_Citizens(CitizenList()), _votersPercentage(0), _repsByPartyID(new int[MAX_SIZE]), _repsByPartyLogicSize(numOfParties),
		_repsByPartyPhySize(MAX_SIZE), _numOfReps(numOfReps), _numberOfVotesinDist(0)
	{
		strcpy(this->_name, name);
		for (int i = 0; i < numOfParties; i++)
		{
			_repsByPartyID[i] = 0;
		}
	}

	District::~District()
	{
		delete[] _repsByPartyID;
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

	const double District::getVotersPrecentage() const
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
	
	bool District::addrepToArr()
	{
		if (_repsByPartyLogicSize == _repsByPartyPhySize)
		{
			realloc(_repsByPartyPhySize * 2);

		}
		_repsByPartyID[numOfParties] = 0;
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

	bool  District::settVotersPrecentage(const int num) {
		_votersPercentage = num;
		return true;
	}

	void District::operator++(int)
	{
		_numberOfVotesinDist++;
		_votersPercentage = (_numberOfVotesinDist / getNumberOfCitizens()) * 100;
	}

	//ostream& operator<<(ostream& os, const District& district)
	//{
	//	//district.toOs(ostream & os);

	//	os << "District " << district._name << ", its ID is: " << (int)district._serialNum <<" has "<< district.getNumberOfCitizens() << " citizens." << endl;
	//	os << "Number of representatives is : " << (double)district._numOfReps << endl;
	//	os << "Precentage of voters: " << district.getVotersPrecentage() << "%" << endl;
	//	//TODO to check if the next commented line is needed
	//	/*<< "and the election's result is " <<(int)district._electionResult << "." << endl;*/
	//	
	//	return os;
	//}

	void District::realloc(int new_size)
	{
		int* new_memory = new int [new_size];

		for (int i = 0; i < min(new_size, _repsByPartyPhySize); ++i)
		{
			new_memory[i] = _repsByPartyID[i];
		}
		if (_repsByPartyLogicSize >= 1)
		{
			delete[] _repsByPartyID;
		}

		_repsByPartyPhySize = new_size;
		_repsByPartyID = new_memory;
	}

	int District::getRepsByPartyLogicSize() const
	{
		return _repsByPartyLogicSize;
	}

	bool District::setRepsArrByPartyID(int partyID, int repsAmount)
	{
		_repsByPartyID[partyID - PARTY_ID_INIT] = repsAmount;
		return true;
	}

	int District::getRepsByPartyID(int partyID) const
	{
		return _repsByPartyID[partyID - PARTY_ID_INIT];
		
	}

	bool District::updateRepsArr()
	{
		numOfParties++;
		return AddAnotherColumn() && addDistToArr();
	}

	bool District::AddAnotherColumn()
	{
		int* new_memory = new int[numOfParties];
		for (int i = 0; i < min(numOfParties, _repsByPartyPhySize); ++i)
		{
			new_memory[i] = (_repsByPartyID[i]);
		}
		_repsByPartyID = new_memory;

		return true;
	}

	bool District::addDistToArr()
	{
		if (_repsByPartyLogicSize == _repsByPartyPhySize)
		{
			realloc(_repsByPartyPhySize * 2);

		}
		_repsByPartyID[_repsByPartyLogicSize++] = 0;
		
		return true;
	}

	ostream& operator<<(ostream& os, const District& district)
	{
		os << "**********************************" << endl;
		os << typeid(district).name() + 12 << " "<< district.getName() << ", it's id is" << district.
			getSerialNum() << " has " << district.getNumberOfCitizens() << " citizens." << endl;
		os << "Number of representatives is : " << static_cast<double>(district.getNumOfReps()) << endl;
		os << "Precentage of voters: " << district.getVotersPrecentage() << "%" << endl;
		//TODO to check if the next commented line is needed
	/*<< "and the election's result is " <<(int)district._electionResult << "." << endl;*/
		district.toOs(os);
		os << "**********************************" << endl;
		return os;
	}
}
