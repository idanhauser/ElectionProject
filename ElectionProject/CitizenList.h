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
		//	CitizenList(const CitizenList& other);//idan:should be in private and with friend class, but cant make it work

		~CitizenList();
		void realloc(int new_size);
		bool addToList(Citizen* citizen);
		int getLogicSize() const;
		const Citizen& getCitizenByIndex(int index) const;
		Citizen& getCitizenByIndex(int index);
		//int isCitizenExist(int id) const;
		////const Citizen& getCitizenById(int id) const;
		////Citizen& getCitizenById(int id);

	

		//CitizenList(Citizen* pmCandidate);
	};
}



