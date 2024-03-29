﻿//code verison 3.1
#include "Utils.h"
using namespace std;
#include "District.h"
#include "DistrictList.h"
#include "Exceptions.h"
namespace elec {
	

	DistrictList::DistrictList() : _logicSize(0), _phySize(MAX_SIZE), _districts(new District* [MAX_SIZE]) {}

	DistrictList::~DistrictList()
	{
		for (int i = 0; i < _logicSize; i++)
		{
			delete _districts[i];
		}
		delete[] _districts;
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


	bool DistrictList::addToList(District& district)
	{
		if (_logicSize == _phySize)
		{
			realloc(_phySize * 2);

		}
		_districts[_logicSize++] = &district;
		return true;
	}

	District& DistrictList::getDistcritById(int id)
	{
		return *_districts[abs(id - DISTRICT_ID_INIT)];
	}

	const District& DistrictList::getDistcritById(int id) const
	{
		return *_districts[abs(id - DISTRICT_ID_INIT)];
	}






	int DistrictList::getLogicSize() const
	{
		return _logicSize;
	}


	const District& DistrictList::getDistcritByIndex(int index) const
	{
		if (index < _logicSize)
			return *_districts[index];
	}

	District& DistrictList::getDistcritByIndex(int index)
	{
		if (index < _logicSize)
			return *_districts[index];
	}


}
