//code verison 3.1
#include "District.h"

#include <fstream>
#include <string>
#include "Citizen.h"
#include <iostream>
#include "CitizenList.h"
#include "Exceptions.h"
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
		//Reading name:
		reader.read(rcastc(&_name), sizeof(string));
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

	District::District(string& name, int numOfReps, int numOfParties) : _serialNum(snGenerator++), _name(name),
		_Citizens(CitizenList()), _votersPercentage(0), _repsByPartyID(numOfParties),
		_numOfReps(numOfReps), _electionResult(0),_numberOfVotesinDist(0)
	{

	}

	District::~District()
	{
		
	}

	const string& District::getName() const
	{
		return _name;
	}

	const Citizen* District::getPartyLeader() const
	{
		return nullptr;
	}

	bool District::setLeader(const Citizen* leader)
	{
		return false;
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

	void District::addCitizen(Citizen* citz) noexcept(false)
	{
		if (citz != nullptr)
		{
			_Citizens.addToList(*citz);
		}
		else
		{
			string msg = "Add Citizen";
			throw NullObjectException(msg);
		}
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

	bool  District::setVotersPrecentage(const int num) {
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
		//save serialNumOfDist:
		outFile.write(rcastcc(&_serialNum), sizeof(int));

		//saving name
		outFile.write(rcastcc(&_name), sizeof(string));
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

	bool District::updateRepsArr()
	{
		_repsByPartyID.resize(_repsByPartyID.size() + 1);
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
