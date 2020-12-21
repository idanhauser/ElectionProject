//code verison 2.0
#include "Utils.h"
using namespace std;
#include "District.h"
#include "DistrictList.h"

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



	//DistrictList::DistrictList(const DistrictList& other) :_logicSize(other._logicSize),_phySize(other._phySize), _districts(new District*[other._phySize])
	//{
	//	int len = other.getLogicSize();
	//	for (int i = 0; i < len; ++i)
	//	{
	//		_districts[i] = other._districts[i];
	//	}
	//}


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



	/*const Citizen& DistrictList::getCitizenById(int id) const
	{
	 Citizen* citizen;
		for (int i = 0; i < _logicSize; ++i)
		{
			citizen = &_districts[i]->getCitizenById(id);
		}
		return  citizen;
	}*/

	bool DistrictList::isCitizenExist(int id,int & distIndex) const
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
		return found;
	}

	int DistrictList::getLogicSize() const
	{
		return _logicSize;
	}

	bool DistrictList::isDistcritExist(int id) const
	{
		bool found = false;
		for (int i = 0; i < _logicSize && !found; ++i)
		{
			if (i == abs(id - DISTRICT_ID_INIT))
			{
				found = true;
			}
		}
		return found;
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
