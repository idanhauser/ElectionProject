//code verison 3.0
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


		~CitizenList();
		void realloc(int new_size);
		bool addToList(Citizen& citizen);
		int getLogicSize() const;
		const Citizen& getCitizenByIndex(int index) const;
		Citizen& getCitizenByIndex(int index);
		Citizen** getCitizens();

	};
}



