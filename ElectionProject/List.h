#pragma once
#pragma  warning(disable:4996)



namespace elec {
	class Citizen;

	class List
	{
	private:
		int logicSizeMembers;
		int phySizeMembers;
		Citizen** _List;



	public:
		List();
		List(Citizen* pmCandidate); //roee: should get the pmCandidate as arg to init the partyList

		Citizen** reallocCitizenArray(Citizen** citizens, int old_size, int new_size);
		bool addListMember(Citizen* citizen); //roee: was changed
		bool deleteList();


	};
}



