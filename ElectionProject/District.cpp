//code verison 3.1
#include "District.h"

#include <fstream>
#include <string>
#include "Citizen.h"
#include <iostream>
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
	}

	District::District(string& name, int numOfReps, int numOfParties) : _serialNum(snGenerator++), _name(name),
		_citizens(), _votersPercentage(0), _repsByPartyID(numOfParties),  _numOfReps(numOfReps), _electionResult(0),_numberOfVotesinDist(0)
	{

	}

	District::~District()
	{
		for (auto j = _citizens.begin(); j != _citizens.end(); ++j)
		{
			delete (*j);
		}
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
	
	
	//use only if you know that citizen exist
	const Citizen& District::getCitizenById(int id) const noexcept(false)
	{
		const Citizen* cit = nullptr;
		auto j = _citizens.begin();
		bool found = false;
		for (; j !=_citizens.end() && !found; ++j)
		{
			if ((*j)->getCitizenID() == id)
			{
				found=true;
				cit = (*j);
			}
		}
		if (found)
		{
			return *cit;
		}
		throw CitizenNotExistException(id);
	}

	Citizen& District::getCitizenById(int id) noexcept(false)
	{
		Citizen* cit = nullptr;
		auto j = _citizens.begin();
		bool found = false;
		for (; !found && j != _citizens.end(); ++j)
		{
			if ((*j)->getCitizenID() == id)
			{
				found = true;
				cit = (*j);
			}
		}
		if(found)
		{
			return *cit;
		}
		throw CitizenNotExistException(id);
		
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

	const vector<Citizen*>& District::getCitizens() const
	{
		return _citizens;
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
