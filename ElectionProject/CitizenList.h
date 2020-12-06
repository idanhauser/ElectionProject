//code verison 1.0
#pragma once
#pragma  warning(disable:4996)

using namespace std;

namespace elec {
	class Citizen;

	class CitizenList
	{
	private:
		int _logicSize;
		int _phySize;
		Citizen** _citizens;


		const CitizenList& operator=(const CitizenList&);

	public:
		CitizenList();
		CitizenList(const CitizenList& other);//idan:should be in private and with friend class, but cant make it work
		//	friend class Citizen;
		
		~CitizenList();
		void realloc(int new_size);
		bool addToList(Citizen* citizen);
		int getLogicSize() const;
		friend ostream& operator<<(ostream& os, const CitizenList& citizen);
		Citizen* findCitizenByID(int citizenID);
		Citizen* getCitizenByIndex(int indx);
		void printList();
		//CitizenList(Citizen* pmCandidate);
	};
}



