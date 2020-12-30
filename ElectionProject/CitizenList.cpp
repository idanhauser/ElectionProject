//code verison 2.5
#include "Utils.h"
using namespace std;
#include "Citizen.h"
#include "CitizenList.h"
namespace elec {

	CitizenList::CitizenList() : _logicSize(0), _phySize(MAX_SIZE), _citizens(new Citizen* [MAX_SIZE]) 
	{
	}




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




	//const CitizenList& CitizenList::operator=(const CitizenList& other)
	//{
	//	this->_citizens = other._citizens;
	//	this->_logicSize = other._logicSize;
	//	this->_phySize = other._phySize;
	//	return *this;
	//}







}



