//code verison 3.1
#include "Citizen.h"

#include <fstream>



#include "District.h"
#include "LoadElectionSystem.h"
#include "Party.h"

namespace elec
{
	Citizen::Citizen(string& citizen_name, int id_num, int birthYear, const Party* party,
		const District& district) : _name(citizen_name), _idNum(id_num),
		_birthYear(birthYear),  _hasVoted(false), _party(nullptr),
		_partyId(-1), _district(district)
	{
		
	}

	Citizen::Citizen(LoadElectionSystem& loader, const District& district):_district(district)
	{

		int partyId = -1;
		ifstream& reader = loader.getReader();
		//Reading len of name:

		//Reading name:
		reader.read(rcastc(&_name), sizeof(string) );
		//Reading _idNum
		reader.read(rcastc(&_idNum), sizeof(int));
		//Reading _birthYear
		reader.read(rcastc(&_birthYear), sizeof(int));
		//reading _hasVoted
		reader.read(rcastc(&_hasVoted), sizeof(bool));
		//reading _partyID:
		reader.read(rcastc(&partyId), sizeof(int));
		if(partyId!=-1)
		{
			_partyId = partyId;
		}
		else
		{
			_partyId = -1;
		}
	}

	Citizen::~Citizen()
	{

	}


	

	void Citizen::setParty(const Party* party)  noexcept(false)
	{
		if (party == nullptr)
		{
			throw "Couldn't set party to citizen.";
		}
		_party = party;
		_partyId = party->getPartyID();

	}

	bool Citizen::setHasVoted(bool voted)
	{
		_hasVoted = voted;
		return true;
	}

	const string Citizen::getCitizenName() const
	{
		return _name;

	}

 int Citizen::getCitizenID() const
	{
		return _idNum;

	}


	int Citizen::getCitizenBirthYear() const
	{
		return _birthYear;

	}

	 int Citizen::getDistrictNum() const
	{
		return _district.getSerialNum();

	}

	int Citizen::GetPartyId() const
	{
		return _partyId;
	}

	bool Citizen::hasVoted() const
	{
		return _hasVoted;
	}

	const Party* Citizen::getParty() const
	{
		return _party;
	}

	const District& Citizen::getDistrict() const
	{
		return _district;
	}

	void Citizen::save(ofstream& outFile) const
	{
		
		int isParty=-1;

		//save name of dist:
		//saving name
		outFile.write(rcastcc(&_name), sizeof(string));
		//saving _idNum
		outFile.write(rcastcc(&_idNum), sizeof(int));
		//saving _birthYear
		outFile.write(rcastcc(&_birthYear), sizeof(int));
		//saving _hasVoted
		outFile.write(rcastcc(&_hasVoted), sizeof(bool));
		//saving _party Id
		if(_party!=__nullptr)
		{
			isParty = _party->getPartyID();
		}
		//if the citizen also represnt a party we save the party's ID, else we save -1 for nullptr
		outFile.write(rcastcc(&isParty), sizeof(int));
	}

	ostream& operator<<(ostream& os, const Citizen& citizen)
	{
		os << citizen._name << ", " << (int)citizen._idNum << ", born in " << (int)citizen._birthYear << endl;
		if (citizen._hasVoted)
		{
			os << "and he voted this election round." << endl;
		}
		else
		{
			os << "and he didn't vote this election round." << endl;
		}
		return os;
	}
}


