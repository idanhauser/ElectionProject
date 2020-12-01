#include "List.h"

namespace elec {


	List::List() : phySizeMembers(2), logicSizeMembers(1) //roee: not sure about these values for the sizes
	{
		delete[] this->_List;
		this->_List = new Citizen * [phySizeMembers];
		/*for (int i = 0; i < size; ++i)
		{
			this->_List[i] = Members[i];
		}*/
	}

	List::List(Citizen* pmCandidate) : phySizeMembers(2), logicSizeMembers(1) //roee: same here
	{
		delete[] this->_List;
		this->_List = new Citizen * [phySizeMembers];
		/*for (int i = 0; i < size; ++i)
		{
			this->_List[i] = Members[i];
		}*/
		addListMember(pmCandidate);
	}

	Citizen** List::reallocCitizenArray(Citizen** old_memory, int old_size, int new_size) //roee: moved yours over here.
	{																					 //just added to min std, But Im not sure its cool..
		Citizen** new_memory = new Citizen * [new_size];
		for (int i = 0; i < std::min(old_size, new_size); i++)
			new_memory[i] = old_memory[i];

		delete[] old_memory;
		//old_memory = new_memory;
		return new_memory;
	}

	bool List::addListMember(Citizen* citizen) //roee: changed the origin u gave me. Do u think it should get one citizen at a time?
	{
		if (logicSizeMembers == phySizeMembers)
		{
			_List = List::reallocCitizenArray(_List, phySizeMembers, phySizeMembers * 2);
			phySizeMembers *= 2;
		}
		if (logicSizeMembers < phySizeMembers)
		{
			_List[logicSizeMembers++] = citizen;
		}
		else
		{
			//error
			return false;
		}
		return true;
	}

	bool List::deleteList() //roee: is it good? lol
	{
		for (int i = 0; i < phySizeMembers; i++)
			delete[] _List[i];
		return true;
	}






}