//code verison 2.0
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
	}

	District::District(const char* name, int numOfReps) : _serialNum(snGenerator++), _name(new char[strlen(name) + 1]),
		_Citizens(CitizenList()), _votersPercentage(0), _electionResult(0), _numOfReps(numOfReps), _numberOfVotesinDist(0)
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

	Citizen& District::getCitizenByIndex(int idx) 
	{
		return _Citizens.getCitizenByIndex(idx);
	}
	//todo: to delete.
	// District& District::operator=( District& other)
	//{
	//	if(this!=&other)
	//	{
	//		strcpy(_name, other._name);
	//		_electionResult = other._electionResult;
	//		_numOfReps = other._numOfReps;
	//		_serialNum = other._serialNum;
	//		_numberOfVotesinDist = other._numberOfVotesinDist;
	//		_votersPercentage = other._votersPercentage;
	//		
	//		for (int i = 0; i < other._Citizens.getLogicSize(); ++i)
	//		{
	//			this->addCitizen(&other.getCitizenByIndex(i));
	//		}
	//	}
	//	return *this;
	//}

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
			if (_Citizens.getCitizenByIndex(i).hasVoted())
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

	void District::save(ofstream& outFile) const
	{
		int numOfElements = 0;
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
		numOfElements = _Citizens.getLogicSize();
		//saving citizens list's len
		outFile.write(rcastcc(&numOfElements), sizeof(int));
		//saving citizens:
		for (int i = 0; i < numOfElements; ++i)
		{
			_Citizens.getCitizenByIndex(i).save(outFile);
		}

	}


	ostream& operator<<(ostream& os, const District& district)
	{
		os << "District " << district._name << ", its ID is: " << (int)district._serialNum << " has " << district.getNumberOfCitizens() << " citizens." << endl;
		os << "Number of representatives is : " << (double)district._numOfReps << endl;
		//TODO to check if the next commented line is needed
		/*<< "and the election's result is " <<(int)district._electionResult << "." << endl;*/

		return os;
	}



}
