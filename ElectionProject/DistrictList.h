//code verison 1.0
#pragma once

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
		//DistrictList(const DistrictList& other);//idan:should be in private and with friend class, but cant make it work
		
		void realloc(int new_size);
		bool addToList(District& district);
		District& getDistcritById(int id);
		const District & getDistcritById (int id) const;
		bool isCitizenExist(int id, int& distIndex) const;
		int getLogicSize() const;
		bool isDistcritExist(int id) const;
		const District& getDistcritByIndex(int index) const;
		 District& getDistcritByIndex(int index) ;



//		/*********************************/
////roee:
//		District* findDistrictByID(int id);
//
//		/*********************************/
	};
}
