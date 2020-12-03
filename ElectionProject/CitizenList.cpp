//code verison 1.0
using namespace std;
#include "Citizen.h"
#include "CitizenList.h"
namespace elec {



	CitizenList::CitizenList() : _logicSize(0), _phySize(MAX_SIZE), _citizens(new Citizen* [MAX_SIZE]) //roee: not sure about these values for the sizes...//idan : these are the values.
	{
	}


	CitizenList::CitizenList(const CitizenList& other) :_logicSize(other._logicSize), _phySize(other._phySize), _citizens(new Citizen* [other._phySize])
	{
		int len = other.getLogicSize();
		for (int i = 0; i < len; ++i)
		{
			_citizens[i] = other._citizens[i];
		}
	}



	CitizenList::~CitizenList()
	{
		for (int i = 0; i < _phySize; i++)
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


	bool CitizenList::addToList(Citizen* citizen) 
													 
	{
		if (_logicSize == _phySize)
		{
			realloc(_phySize * 2);

		}
		_citizens[_logicSize++] = citizen;
		return true;
	}



	int CitizenList::getLogicSize() const
	{
		return _logicSize;
	}

	ostream& operator<<(ostream& os, const CitizenList& citizen)
	{
		int len = citizen.getLogicSize();
		for (int i = 0; i < len; i++)
		{
			os << citizen._citizens[i] << endl;
		}
		return os;
	}
}

