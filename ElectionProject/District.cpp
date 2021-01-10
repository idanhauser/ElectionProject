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
			Citizen* citiz = new Citizen(loader,*this);
			_citizens.push_back(citiz);
		}
		//reading numOfParties:
		reader.read(rcastc(&_numOfParties), sizeof(int));
		_repsByPartyID = new int[MAX_SIZE];
		for (int i = 0; i < _numOfParties; i++)
		{
			_repsByPartyID[i] = 0;
		}
	}

	District::District(string& name, int numOfReps, int numOfParties) : _serialNum(snGenerator++), _name(name),
		_citizens(), _votersPercentage(0), _repsByPartyID(new int[MAX_SIZE]), _numOfParties(numOfParties), _repsByPartyLogicSize(numOfParties),
		 _repsByPartyPhySize(MAX_SIZE), _numOfReps(numOfReps), _electionResult(0),_numberOfVotesinDist(0)
	{

		for (int i = 0; i < numOfParties; i++)
		{
			_repsByPartyID[i] = 0;
		}
	}

	District::~District()
	{
		delete[] _repsByPartyID;

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



	const Citizen& District::getCitizenByIndex(int index) const
	{
		if (index < _citizens.size())
			return *_citizens.at(index);
	}

	Citizen& District::getCitizenByIndex(int index)
	{
		if (index < _citizens.size())
			return *_citizens.at(index);
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
		return _citizens.size();
	}

	void District::addCitizen(Citizen& citz) noexcept(false)
	{
	
			_citizens.push_back(&citz);
		
	/*	else
		{
			string msg = "Add Citizen";
			throw NullObjectException(msg);
		}*/
	}
	
	bool District::addRepToArr()
	{
		if (_repsByPartyLogicSize == _repsByPartyPhySize)
		{
			reallocRepsByPartyID(_repsByPartyPhySize * 2);

		}
		_repsByPartyID[_numOfParties] = 0;
		return true;
	}
	
	//use only if you know that citizen exist
	const Citizen& District::getCitizenById(int id) const
	{
		
		auto j = _citizens.begin();
		bool found = false;
		for (; j !=_citizens.end() && !found; ++j)
		{
			if ((*j)->getCitizenID() == id)
			{
				found=true;

			}
		}//todo: to check if works
		return (**j);
	}

	Citizen& District::getCitizenById(int id)
	{
		auto j = _citizens.begin();
		bool found = false;
		for (; j != _citizens.end() && !found; ++j)
		{
			if ((*j)->getCitizenID() == id)
			{
				found = true;

			}
		}//todo: to check if works
		return (**j);
	}

	int District::getNumOfReps() const
	{
		return _numOfReps;
	}


	bool District::isCitizenExist(int id) const
	{
		bool found = false;

		for (auto i = _citizens.begin(); i != _citizens.end() && !found; ++i)
		{
			if ((*i)->getCitizenID() == id)
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


		for (auto i = _citizens.begin(); i!=_citizens.end(); ++i)
		{
			if((*i)->hasVoted())
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
		numOfCitizens = _citizens.size();
		//saving citizens list's len
		outFile.write(rcastcc(&numOfCitizens), sizeof(int));
		//saving citizens:
		for (auto i = _citizens.begin(); i !=_citizens.end(); ++i)
		{
			(*i)->save(outFile);
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
	void District::reallocRepsByPartyID(int new_size)
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

	const vector<Citizen*>& District::getCitizens() const
	{
		return _citizens;
	}

	bool District::addDistToArr()
	{
		if (_repsByPartyLogicSize == _repsByPartyPhySize)
		{
			reallocRepsByPartyID(_repsByPartyPhySize * 2);

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
