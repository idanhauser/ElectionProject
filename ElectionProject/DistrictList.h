//code verison 3.1
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
		bool isCitizenExist(int id, int& distIndex) const;
		int getLogicSize() const;
		const District& getDistcritByIndex(int index) const;
		District& getDistcritByIndex(int index);



	};
}
