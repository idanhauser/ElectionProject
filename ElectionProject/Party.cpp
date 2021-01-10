//code verison 3.1
#include "Party.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Citizen.h"
#include "CitizenList.h"


namespace elec {

	int Party::pdGenerator = PARTY_ID_INIT;


	Party::Party(const string& partyName, int PMCandidateID, int numOfDist, Citizen& partyLeader) : _partyID(pdGenerator++),
		_name(partyName),
		_PMCandidateID(PMCandidateID), _partyMembers(new CitizenList()), _representativesByDist(new CitizenList[numOfDist]),
		_partyLeader(partyLeader), _VotingPercentagesDistrict(numOfDist)
	{
		_partyMembers->addToList(partyLeader);

	}

	Party::Party(LoadElectionSystem& loader, Citizen& partyLeader, int numOfDist): _partyMembers(new CitizenList()),
		_representativesByDist(new CitizenList[numOfDist]), _partyLeader(partyLeader)
	{
		ifstream& reader = loader.getReader();
		//Reading serial num of party _partyID:
		reader.read(rcastc(&_partyID), sizeof(int));
		pdGenerator = _partyID;
		//Reading name:
		reader.read(rcastc(&_name), sizeof(string));
		//Reading _PMCandidateID//
		reader.read(rcastc(&_PMCandidateID), sizeof(int));
		//Reading double arr:
		for (int i = 0; i < _VotingPercentagesDistrict.size(); ++i)
		{
			reader.read(rcastc(&_VotingPercentagesDistrict[i]), sizeof(double));
		}
	}
	Party::~Party()
	{
	}


	bool Party::setPMCandidateID(int idNum) {
		_PMCandidateID = idNum;
		return true;
	}

	const int Party::getPartyID() const
	{
		return _partyID;
	}

	bool Party::addToRepByDists(CitizenList& reps, int district)
	{
		_representativesByDist[district] = reps;
		return true;
	}

	const string Party::getPartyName() const
	{
		return _name;
	}

	int Party::getPartyPMCandidateID() const
	{
		return _PMCandidateID;
	}

	const CitizenList& Party::getPartyMembers() const
	{

		return *_partyMembers;
	}

	bool Party::addToMembers(Citizen& citizen) 
	{
		return _partyMembers->addToList(citizen);
	}



	bool Party::updateDistricts()
	{
		_VotingPercentagesDistrict.resize(_VotingPercentagesDistrict.size() + 1);
		return true;
	}


	string Party::printPartyRepsFromDistrictByAmount(int num, int districtID) const
	{
		string output;
		CitizenList& represnts = _representativesByDist[abs(districtID - DISTRICT_ID_INIT)];
		int amountToPrint = min(num, represnts.getLogicSize());
		if(amountToPrint==0)
		{
			output.append("\n The are no any representatives.(user didn't add any representatives). \n");
		}
		else
		{
			cout << "And they are:" << endl;
			for (int i = 0; i < amountToPrint; ++i)
			{
				cout << (represnts.getCitizenByIndex(i)).getCitizenName() << endl;
			}
		}
		output += "**********************************\n";
		return output;
	}


	bool Party::addToRepresentativesByDis(Citizen& citizen, int distIndex) 
	{
		return  _representativesByDist[distIndex].addToList(citizen);
	}

	Citizen& Party::getPartyLeader() const
	{
		return _partyLeader;
	}

	double Party::getVotingPercentagesByDistcritIdx(int index) const
	{
		return _VotingPercentagesDistrict[index];
	}



	void Party::save(ofstream& outFile) const
	{

		//save serialNumOfParty:
		outFile.write(rcastcc(&_partyID), sizeof(int));
		//saving name
		outFile.write(rcastcc(&_name), sizeof(string));
		//saving _PMCandidateID
		outFile.write(rcastcc(&_PMCandidateID), sizeof(int));
		//saving double arr:
		for (int i = 0; i < _VotingPercentagesDistrict.size(); ++i)
		{
			outFile.write(rcastcc(&_VotingPercentagesDistrict[i]), sizeof(double));
		}

		
		
	}

	CitizenList* Party::getRepresentativesByDis() const
	{
		return _representativesByDist;
	}

	/// <summary>
	/// adding a citizen as a party member, adds to the party member list and to the
	/// Representatives list By the district they represnt.
	/// </summary>
	/// <param name="citizen">the citizen we want to add to the lists</param>
	/// <param name="distIndex">the district he represnt</param>
	/// <returns>true if everything is ok else false </returns>
	bool Party::addPartyMember( Citizen& citizen, int distIndex)
	{
		bool addtodis = false, addtomembers = false;
		addtodis = addToRepresentativesByDis(citizen, distIndex);
		addtomembers = addToMembers(citizen);
		return addtomembers && addtodis;
	}


	bool  Party::setVotingPercentagesDistrict(double num, int districtID)
	{
		_VotingPercentagesDistrict[districtID - DISTRICT_ID_INIT] = num;
		return true;
	}



	ostream& operator<<(ostream& os, const Party& party)
	{
		os << "**********************************" << endl;
		os << party._name << ","<< static_cast<int>(party._partyID) << endl<<"The party leader candidate name and ID is " << party.getPartyLeader().getCitizenName() << ", " <<
			static_cast<int>(party.getPartyPMCandidateID()) << "." << endl << "Party members are:" << endl;
		int sizeOfPartyMemberList = party.getPartyMembers().getLogicSize();
		if (sizeOfPartyMemberList > 1)
		{
			for (int i = 1; i < sizeOfPartyMemberList; ++i)
			{
				os << party.getPartyMembers().getCitizenByIndex(i).getCitizenName() << endl;
			}
		}
		else
		{
			os << "There are no any party member in this party." << endl;
		}
		os << "**********************************" << endl;
		return os;
	}
}
