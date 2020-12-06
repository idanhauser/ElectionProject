//code verison 1.0
#include "ElectionRound.h"
#include <iostream>

#include "Party.h"


using namespace std;

namespace elec
{
	ElectionRound::ElectionRound(int date[8]) :_districts(DistrictList()), _parties(PartyList())
	{

		for (int i = 0; i < 8; ++i)
		{
			this->_date[i] = date[i];
		}
	}

	void ElectionRound::printElectionDate() const
	{
		for (int i = 0; i < 8; ++i)
		{
			cout << static_cast<char>(_date[i] + '0');
			if (i == 1 || i == 3)
			{
				cout << '.';
			}
		}
	}

	bool ElectionRound::addNewDistrict(char name[MAX_SIZE], int numberResentatives, int& districtId)
	{
		bool districtAdded = false;
		District* dist = new District(name, numberResentatives);
		districtId = dist->getSerialNum();
		districtAdded = _districts.addToList(*dist);
		return districtAdded;
	}


	bool ElectionRound::addNewCitizen(char* name, int id, int birthyear, int districtId)
	{
		bool citizenAdded = false;
		if (_districts.isDistcritExist(districtId))
		{
			Citizen* citiz = new Citizen(name, id, birthyear, districtId, nullptr, _districts.getDistcritById(districtId));
			citizenAdded = _districts.getDistcritById(districtId).addCitizen(*citiz);
		}

		return citizenAdded;
	}

	bool ElectionRound::addNewParty(char* name, int pdId, int& partyid)
	{
		int distIndex;
		bool partyAdded = false;
		if (_districts.isCitizenExist(pdId, distIndex))
		{
			Party* par = new Party(name, pdId);
			partyid = par->getPartyID();
			_districts.getDistcritByIndex(distIndex).getCitizenById(pdId).setParty(par);
			partyAdded = _parties.addToList(par);
		}
		return partyAdded;
	}

	void ElectionRound::viewAllDistricts() const
	{
		int len = _districts.getLogicSize();
		if (len > 0)
		{
			for (int i = 0; i < len; ++i)
			{
				cout << _districts.getDistcritByIndex(i) << endl;
			}
		}
		else
		{
			cout << "There are no districts to show." << endl;
		}
	}

	void ElectionRound::viewAllCitizens() const
	{
		int len = _districts.getLogicSize();
		if (len > 0)
		{
			for (int i = 0; i < len; ++i)
			{
				int lenofcitizen = _districts.getDistcritByIndex(i).getNumberOfCitizens();
				if (lenofcitizen > 0)
					cout << "The citizens who live in " << _districts.getDistcritByIndex(i).getName() << "are: " << endl;

				for (int j = 0; j < lenofcitizen; ++j)
				{
					cout << _districts.getDistcritByIndex(i).getEligibleCitizens().getCitizenByIndex(j) << endl;
				}

			}
		}
		else
		{
			cout << "There are no citizens to show." << endl;
		}
	}

	void ElectionRound::viewAllParties() const
	{
		int len = _parties.getLogicSize();
		if (len > 0)
		{
			for (int i = 0; i < len; ++i)
			{
				cout << _parties.getPartyByIndex(i) << endl;
			}
		}
		else
		{
			cout << "There are no parties to show." << endl;
		}
	}
}

