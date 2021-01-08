//code verison 3.0
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




	void DistrictList::isCitizenExist(int id,int & distIndex) const noexcept(false)
	{
		distIndex = -1;
		
		bool found = false;
		for (int i = 0; i < _logicSize && !found; ++i)
		{
			if (_districts[i]->isCitizenExist(id))
			{
				distIndex = i;
				found = true;
			}
		}
		if(!found)
		{
			throw CitizenNotExistException(id);
		}
	}

	int DistrictList::getLogicSize() const
	{
		return _logicSize;
	}

	void DistrictList::isDistcritExist(int id) const noexcept(false)
	{
		bool found = false;
		for (int i = 0; i < _logicSize && !found; ++i)
		{
			if (i == abs(id - DISTRICT_ID_INIT))
			{
				found = true;
			}
		}
		if(!found)
		{
			throw DistcritsNotExistException(id);
		}
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
