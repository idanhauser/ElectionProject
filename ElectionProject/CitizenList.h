//code verison 2.5
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



	public:
		CitizenList();

		//const CitizenList& operator=(const CitizenList&);

		~CitizenList();
		void realloc(int new_size);
		bool addToList(Citizen& citizen);
		int getLogicSize() const;
		const Citizen& getCitizenByIndex(int index) const;
		Citizen& getCitizenByIndex(int index);
		Citizen** getCitizens();

	};
}



