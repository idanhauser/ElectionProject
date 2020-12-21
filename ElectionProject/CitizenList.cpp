//code verison 2.0
#include "Utils.h"
using namespace std;
#include "Citizen.h"
#include "CitizenList.h"
namespace elec {

	CitizenList::CitizenList() : _logicSize(0), _phySize(MAX_SIZE), _citizens(new Citizen* [MAX_SIZE]) //roee: not sure about these values for the sizes...//idan : these are the values.
	{
	}


	/*	CitizenList::CitizenList(const CitizenList& other) :_logicSize(other._logicSize), _phySize(other._phySize), _citizens(new Citizen* [other._phySize])
		{
			int len = other.getLogicSize();
			for (int i = 0; i < len; ++i)
			{
				_citizens[i] = other._citizens[i];
			}
		}*/



	CitizenList::~CitizenList()
	{
		for (int i = 0; i < _logicSize; i++)
		{
			delete _citizens[i];
		}
		delete[] _citizens;
	}

	void CitizenList::realloc(int new_size)
	{
		Citizen** new_memory = new Citizen * [new_size];

		for (int i = 0; i < min(new_size, _phySize); ++i)
		{
			new_memory[i] = this->_citizens[i];
		}
		if (_logicSize >= 1)
		{
			delete[] _citizens;
		}

		_phySize = new_size;
		_citizens = new_memory;
	}


	bool CitizenList::addToList(Citizen& citizen)

	{
		if (_logicSize == _phySize)
		{
			realloc(_phySize * 2);

		}
		_citizens[_logicSize++] = &citizen;
		return true;
	}



	int CitizenList::getLogicSize() const
	{
		return _logicSize;
	}

	const Citizen& CitizenList::getCitizenByIndex(int index) const
	{
		if (index < _logicSize)
			return *_citizens[index];
	}

	Citizen& CitizenList::getCitizenByIndex(int index)
	{
		if (index < _logicSize)
			return *_citizens[index];
	}

	Citizen** CitizenList::getCitizens()
	{
		return _citizens;
	}



	//int CitizenList::isCitizenExist(int id) const
	//{
	//	int savePlace = -1;
	//	for (int i = 0; i < _logicSize && savePlace == -1; ++i)
	//	{
	//		if (_citizens[i]->getCitizenID() == id)
	//		{
	//			savePlace = i;
	//		}
	//	}
	//	return savePlace;

	//}


	const CitizenList& CitizenList::operator=(const CitizenList& other)
	{
		this->_citizens = other._citizens;
		this->_logicSize = other._logicSize;
		this->_phySize = other._phySize;
		return *this;
	}
	//roee
	/*

	Citizen* CitizenList::findCitizenByID(int citizenID) { //return 0 for ignoring not finding error even its not possible
		for (int i = 0; i < getLogicSize(); i++) {
			if (_citizens[i]->getCitizenID() == citizenID)
				return _citizens[i];
		}
		return 0;
	}

	Citizen* CitizenList::getCitizenByIndex(int indx) {
		return _citizens[indx];
	}*/
//*roee
/*
	void CitizenList::printList() {
		for (int i = 0; i < getLogicSize(); i++)
			cout << getCitizenByIndex(i)->getCitizenName();
	}
	*/







}



