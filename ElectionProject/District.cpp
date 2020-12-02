
#include <string>
#include <iostream>
#include "District.h"

namespace elec {
	int District::snGenerator = 100;


	District::District(const District& other)
	{
		this->_serialNum = other._serialNum;
		this->_electionResult = other._electionResult;
		setName(const_cast<const char*>(other._name));

		setEligibleCitizens(other._eligibleCitizens, other.logicSizeEligciti);
	}

	/**
	 * \brief constructor for district
	 * \param name the name of the district
	 */
	District::District(const char* name) : _name(new char[strlen(_name) + 1]), _serialNum(snGenerator++),
		_eligibleCitizens(new Citizen* [MAX_SIZE]), logicSizeEligciti(0),
		phySizeEligciti(MAX_SIZE), _votersPercentage(0), _electionResult(0)
	{
		long namelen = strlen(name);
		this->_name = new char[namelen + 1];
		strncpy(this->_name, name, namelen);
		_eligibleCitizens = nullptr;

	}

	District::~District()
	{
		delete[] _name;
		delete[] _eligibleCitizens;
	}

	bool District::setName(const char* name)
	{
		long namelen = strlen(name);
		delete[] name;
		this->_name = new char[namelen + 1];
		strncpy(this->_name, name, namelen);
		return true;
	}
	//roee: I think now when we have the list func it will be better to chagne it
	bool District::setEligibleCitizens(Citizen** eligibleCitizens, int size)
	{
		delete[] this->_eligibleCitizens;
		phySizeEligciti = size * 2;
		logicSizeEligciti = size;
		this->_eligibleCitizens = new Citizen * [phySizeEligciti];
		for (int i = 0; i < size; ++i)
		{
			this->_eligibleCitizens[i] = eligibleCitizens[i];
		}
		return true;
	}


	const char* District::getName() const
	{
		return _name;
	}
	//idan commented
	/*	Citizen** District::getEligibleCitizens() const
		{
			return _eligibleCitizens;
		}
		*/
	double District::getVotersPercentage() const
	{
		return _votersPercentage;
	}

	int District::getElectionResults() const
	{
		return _electionResult;
	}

	int District::getSerialNum() const
	{
		return _serialNum;
	}


	ostream& operator<<(ostream& os, const District& district)
	{
		os << "the district: " << district.getName() << " its id is: " << (int)district.getSerialNum() << " the voters percentage is: " << (double)district.getVotersPercentage() << "and the election's result: " << (int)district.getElectionResults() << endl;
		return os;
	}
}