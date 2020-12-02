
using namespace std;
#include "Citizen.h"
#include "CitizenList.h"
namespace elec {



	CitizenList::CitizenList() : _logicSize(0), _phySize(MAX_SIZE), _citizens(new Citizen* [MAX_SIZE]) //roee: not sure about these values for the sizes...//idan : these are the values.
	{
	}

	//let remove it, and the ctor of the Party will add this prime sminister to the list
	/*CitizenList::CitizenList(Citizen* pmCandidate) : _logicSize(0), _phySize(MAX_SIZE), _citizens(new Citizen* [MAX_SIZE])//roee: same here//idan : these are the values.
	{
		addToList(pmCandidate);
	}*/
	//roee: is it good? lol//idan:yes, but you also need to delete the array itself + in the for you delete an object not an array..so it
   //, and also it should be void not bool(?)

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


	bool CitizenList::addToList(Citizen* citizen) //roee: changed the origin u gave me. Do u think it should get one citizen at a time?
													 //idan: yes because in the menu i have option of "add a citizen" so everytime i add only one citizen
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

