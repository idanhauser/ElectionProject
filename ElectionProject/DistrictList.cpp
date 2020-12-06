//code verison 1.0
using namespace std;
#include "District.h"
#include "DistrictList.h"

namespace elec {
	

	DistrictList::DistrictList() : _logicSize(0), _phySize(MAX_SIZE), _districts(new District* [MAX_SIZE]) {}

	DistrictList::~DistrictList()
	{
		for (int i = 0; i < _phySize; i++)
		{
			delete _districts[i];
		}
		delete[] _districts;
	}

	DistrictList::DistrictList(const DistrictList& other) :_logicSize(other._logicSize),_phySize(other._phySize), _districts(new District*[other._phySize])
	{
		int len = other.getLogicSize();
		for (int i = 0; i < len; ++i)
		{
			_districts[i] = other._districts[i];
		}
	}


	void DistrictList::realloc(int new_size)
	{
		District** new_memory = new District * [new_size];

		for (int i = 0; i < min(new_size, _phySize); ++i)
		{
			new_memory[i] = this->_districts[i];
		}
		if (_logicSize >= 1)
		{
			delete[] _districts;
		}

		_phySize = new_size;
		_districts = new_memory;
	}


	bool DistrictList::addToList(District* District)
	{
		if (_logicSize == _phySize)
		{
			realloc(_phySize * 2);

		}
		_districts[_logicSize++] = District;
		return true;
	}


	int DistrictList::getLogicSize() const
	{
		return _logicSize;
	}

	ostream& operator<<(ostream& os, const DistrictList& district)
	{

		int len = district.getLogicSize();
		for (int i = 0; i < len; i++)
		{
			os << district._districts[i] << endl;
		}
		return os;
	}



	/**************************************/
		//roee:
	class DistrictList;

	District* DistrictList::findDistrictByID( int id) { //return 0 for ignoring not finding error even its not possible
		for (int i = 0; i < getLogicSize(); i++)
			if (_districts[i]->getSerialNum() == id)
				return _districts[i];
		return 0;
	}
	/**************************************/








}
