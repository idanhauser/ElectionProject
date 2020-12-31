//code verison 2.5
#include "District.h"

#include <fstream>

#include "Citizen.h"
#include <iostream>
#include "CitizenList.h"
#include "LoadElectionSystem.h"
using namespace std;

namespace elec {
	int District::snGenerator = DISTRICT_ID_INIT;

	District::District(LoadElectionSystem& loader)
	{
		int numOfCitizens = 0;
		int nameLen;
		ifstream& reader = loader.getReader();
		//Reading serial num:
		reader.read(rcastc(&_serialNum), sizeof(int));
		snGenerator = _serialNum;
		//Reading len of name:
		reader.read(rcastc(&nameLen), sizeof(int));
		_name = new char[nameLen];
		//Reading name:
		reader.read(rcastc(_name), sizeof(char) * nameLen);
		//Reading _votersPercentage
		reader.read(rcastc(&_votersPercentage), sizeof(double));
		//Reading _electionResult
		reader.read(rcastc(&_electionResult), sizeof(int));
		//Reading _numOfReps
		reader.read(rcastc(&_numOfReps), sizeof(int));
		//reading _numberOfVotesinDist
		reader.read(rcastc(&_numberOfVotesinDist), sizeof(int));
		//reading citizens list:
			//reading citizen list len
		reader.read(rcastc(&numOfCitizens), sizeof(int));
		//reading citizens:
 		for (int i = 0; i < numOfCitizens; ++i)
		{
			Citizen* dist = new Citizen(loader,*this);
			_Citizens.addToList(*dist);
		}
		//reading numOfParties:
		reader.read(rcastc(&_numOfParties), sizeof(int));
		_repsByPartyID = new int[MAX_SIZE];
		for (int i = 0; i < _numOfParties; i++)
		{
			_repsByPartyID[i] = 0;
		}
	}

	District::District(const char* name, int numOfReps, int numOfParties) : _serialNum(snGenerator++), _name(new char[strlen(name) + 1]),
		_Citizens(CitizenList()), _votersPercentage(0), _repsByPartyID(new int[MAX_SIZE]), _numOfParties(numOfParties), _repsByPartyLogicSize(numOfParties),
		 _repsByPartyPhySize(MAX_SIZE), _numOfReps(numOfReps), _electionResult(0),_numberOfVotesinDist(0)
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

	Citizen& District::getCitizenByIndex(int idx) 
	{
		return _Citizens.getCitizenByIndex(idx);
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
		_repsByPartyID[_numOfParties] = 0;
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
			if (_Citizens.getCitizenByIndex(i).hasVoted())
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

	void District::save(ofstream& outFile) const
	{
		int numOfCitizens;
		int nameLen = strlen(_name) + 1;
		//save serialNumOfDist:
		outFile.write(rcastcc(&_serialNum), sizeof(int));
		//save name of dist:
			//saving name len
		outFile.write(rcastcc(&nameLen), sizeof(int));
		//saving name
		outFile.write(rcastcc(_name), sizeof(char) * nameLen);
		//saving _votersPercentage
		outFile.write(rcastcc(&_votersPercentage), sizeof(double));
		//saving _electionResult
		outFile.write(rcastcc(&_electionResult), sizeof(int));
		//saving _numOfReps
		outFile.write(rcastcc(&_numOfReps), sizeof(int));
		//saving _numberOfVotesinDist
		outFile.write(rcastcc(&_numberOfVotesinDist), sizeof(int));
		//save citizens list:
		numOfCitizens = _Citizens.getLogicSize();
		//saving citizens list's len
		outFile.write(rcastcc(&numOfCitizens), sizeof(int));
		//saving citizens:
		for (int i = 0; i < numOfCitizens; ++i)
		{
			_Citizens.getCitizenByIndex(i).save(outFile);
		}
		//saving numofParties:
		outFile.write(rcastcc(&_numOfParties), sizeof(int));
	}
	int District::getRepsByPartyID(int partyID) const
	{
		return _repsByPartyID[partyID - PARTY_ID_INIT];

	}

	bool District::setRepsArrByPartyID(int partyID, int repsAmount)
	{
			_repsByPartyID[partyID - PARTY_ID_INIT] = repsAmount;
			return true;
	}
	int District::getRepsByPartyLogicSize() const
	{
		return _repsByPartyLogicSize;
	}
	void District::realloc(int new_size)
	{
		int* new_memory = new int[new_size];

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
	bool District::updateRepsArr()
	{
		_numOfParties++;
		return AddAnotherColumn() && addDistToArr();
	}

	bool District::AddAnotherColumn()
	{
		int* new_memory = new int[_numOfParties];
		for (int i = 0; i < min(_numOfParties, _repsByPartyPhySize); ++i)
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
		os << typeid(district).name() + 12 << " "<< district.getName() << ", it's id is " << district.
			getSerialNum() << " has " << district.getNumberOfCitizens() << " citizens." << endl;
		os << "Number of representatives is : " << static_cast<double>(district.getNumOfReps()) << endl;
		os << "Precentage of voters: " << district.getVotersPrecentage() << "%" << endl;
		district.toOs(os);
		os << "**********************************" << endl;
		return os;
	}
}
