//code verison 3.0
#pragma once
#include <string>
using namespace std;

namespace elec {
	class District;

	class DistrictList
	{
	private:
		int _logicSize;
		int _phySize;
		District** _districts;
		const DistrictList& operator=(const DistrictList&);

	public:
		DistrictList();
		~DistrictList();

		
		void realloc(int new_size);
		bool addToList(District& district);
		District& getDistcritById(int id);
		const District & getDistcritById (int id) const;
		void isCitizenExist(int id, int& distIndex) const;
		int getLogicSize() const;
		void isDistcritExist(int id) const;
		const District& getDistcritByIndex(int index) const;
		District& getDistcritByIndex(int index);



	};
}
