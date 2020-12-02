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

		DistrictList(const DistrictList& other);

	public:
		DistrictList();
		~DistrictList();
		const DistrictList& operator=(const DistrictList&);//idan:should be in private and with friend class, but cant make it work
		//friend class District;
		void realloc(int new_size);
		bool addToList(District* district);
		
		int getLogicSize() const;
		friend ostream& operator<<(ostream& os, const DistrictList& district);

	};
}
