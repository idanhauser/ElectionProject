//code verison 2.0
#pragma once
#include "Party.h"
using namespace std;
namespace elec {
	class Party;

	class PartyList
	{
	private:
		int _logicSize;
		int _phySize;
		Party** _parties;


		const PartyList& operator=(const PartyList&);


	public:
		PartyList();
		~PartyList();
		void realloc(int new_size);
		bool addToList(Party& Party);
		int getLogicSize() const;
		const Party& getPartyByIndex(int index) const;
		Party& getPartyByIndex(int index);
		bool IsPartyExist(int partyId) const;
	};
}
