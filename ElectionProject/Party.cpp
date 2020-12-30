//code verison 2.0
#include "Party.h"
#include <algorithm>
#include <fstream>

#include "Citizen.h"
#include "CitizenList.h"


namespace elec {

	int Party::pdGenerator = PARTY_ID_INIT;


	Party::Party(const char* partyName, int PMCandidateID, int numOfDist, Citizen& partyLeader) : _partyID(pdGenerator++),
		_name(new char[strlen(partyName) + 1]),
		_PMCandidateID(PMCandidateID), _partyMembers(new CitizenList()), _representativesByDist(new CitizenList[numOfDist]),
		_partyLeader(partyLeader), _numOfDist(numOfDist),_VotingPercentagesDistrict(new double[MAX_SIZE]),_logicSize(0),_phySize(MAX_SIZE)
	{
		_partyMembers->addToList(partyLeader);
		strcpy(this->_partyName, partyName);
		for (int i = 0; i < numOfDist; i++)
		{
			_VotingPercentagesDistrict[i] = 0;
		}

	}

	Party::Party(LoadElectionSystem& loader, Citizen& partyLeader, int numOfDist): _partyMembers(new CitizenList()),
		_representativesByDist(new CitizenList[numOfDist]), _partyLeader(partyLeader)
	{
		ifstream& reader = loader.getReader();
		int nameLen;
		int numOfElements = 0;
		//Reading serial num of party _partyID:
		reader.read(rcastc(&_partyID), sizeof(int));
		pdGenerator = _partyID;
		//Reading len of name:
		reader.read(rcastc(&nameLen), sizeof(int));
		_name = new char[nameLen];
		//Reading name:
		reader.read(rcastc(_name), sizeof(char) * nameLen);
		//Reading _PMCandidateID//TODO: need to connect leader
		reader.read(rcastc(&_PMCandidateID), sizeof(int));
		//Reading _numOfDist
		reader.read(rcastc(&_numOfDist), sizeof(int));
		//Reading _phySize
		reader.read(rcastc(&_phySize), sizeof(int));
		_VotingPercentagesDistrict = new double[_phySize];
		//Reading _logicSize
		reader.read(rcastc(&_logicSize), sizeof(int));
		//Reading double arr:
		for (int i = 0; i < _logicSize; ++i)
		{
			reader.read(rcastc(&_VotingPercentagesDistrict[i]), sizeof(int));
		}
		//to continue saving to file from this point lefts: _partyMembers list,_representativesByDist,
		//Reading _partyMembers list
			//Reding number of objects:
	//	loader.getWriter().read(rcastc(&numOfElements), sizeof(int));
	//	for (int i = 0; i < numOfElements; ++i)//TODO : TO Change will be fill when matching between citizen to a party.
	//	{
	//		int idOfReps;
	//		loader.getWriter().read(rcastc(&idOfReps), sizeof(int));
	//	}
	//	//Save _representativesByDist list:
	////save number of objects(=cols in arr):
	//	loader.getWriter().read(rcastc(&numOfElements), sizeof(int));
	//	//reaing from file num of cols in arr:
	//	for (int i = 0; i < numOfElements; ++i)//TODO : TO Change will be fill when matching between citizen to a party.
	//	{
	//		int numOfRepsDist;
	//		loader.getWriter().read(rcastc(&numOfRepsDist), sizeof(int));
	//		//reading party members ids
	//		for (int j = 0; j < numOfRepsDist; ++j)
	//		{
	//			int rpusid;
	//			loader.getWriter().read(rcastc(&rpusid), sizeof(int));
	//		}
	//	}
	}
	Party::~Party()
	{
		delete[] _VotingPercentagesDistrict;
		delete[] _name;
	}


	bool Party::setPMCandidateID(int idNum) {
		_PMCandidateID = idNum;
		return true;
	}

	const int Party::getPartyID() const
	{
		return _partyID;
	}

	const char* Party::getPartyName() const
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

	bool Party::AddAnotherColumn()
	{
		CitizenList* new_memory = new CitizenList[_numOfDist ];
		for (int i = 0; i < min(_numOfDist , _numOfDist); ++i) //todo: idan: fix min
		{
			new_memory[i] = (_representativesByDist[i]);
		}
		_representativesByDist = new_memory;

		return true;
	}

	bool Party::addDistToArr()
	{
		if (_logicSize == _phySize)
		{
			realloc(_phySize * 2);

		}
		_VotingPercentagesDistrict[_numOfDist] = 0;
		_logicSize++;
		return true;
	}

	bool Party::updateDistricts()
	{
		_numOfDist++;
		return AddAnotherColumn() && addDistToArr();
	}


	void Party::printPartyRepsFromDistrictByAmount(int num, int districtID) const
	{
		CitizenList& represnts = _representativesByDist[abs(districtID - DISTRICT_ID_INIT)];
		int amountToPrint = min(num, represnts.getLogicSize());
		cout << "The Reps are: " << endl;
		for (int i = 0; i < amountToPrint; ++i)
		{
			cout << (represnts.getCitizenByIndex(i)).getCitizenName() << endl;

		}
	}


	bool Party::addToRepresentativesByDis(Citizen& citizen, int distIndex) 
	{
		return  _representativesByDist[distIndex].addToList(citizen);
	}

	Citizen& Party::getPartyLeader() const
	{
		return _partyLeader;
	}

	double Party::getVotingPercentagesByDistrictIdx(int index) const
	{
		return _VotingPercentagesDistrict[index];
	}

	/*void Party::addVotingToPartyFromDistIdx(int index)
	{
		_VotingPercentagesDistrict[index]++;
	}*/

	void Party::save(ofstream& outFile) const
	{
		int numOfObj=0;
		int nameLen = strlen(_name) + 1;
		//save serialNumOfParty:
		outFile.write(rcastcc(&_partyID), sizeof(int));
		//save name of dist:
			//saving name len
		outFile.write(rcastcc(&nameLen), sizeof(int));
		//saving name
		outFile.write(rcastcc(_name), sizeof(char) * nameLen);
		//saving _PMCandidateID
		outFile.write(rcastcc(&_PMCandidateID), sizeof(int));
		//saving _numOfDist
		outFile.write(rcastcc(&_numOfDist), sizeof(int));
		//saving _phySize
		outFile.write(rcastcc(&_phySize), sizeof(int));
		//saving _logicSize
		outFile.write(rcastcc(&_logicSize), sizeof(int));
		//saving double arr:
		for (int i = 0; i < _logicSize; ++i)
		{
			outFile.write(rcastcc(&_VotingPercentagesDistrict[i]), sizeof(double));
		}
		////Save _partyMembers list:
		//	//save number of objects:
		//numOfObj = _partyMembers->getLogicSize();
		//	//saving to file num of party members:
		//outFile.write(rcastcc(&numOfObj), sizeof(int));
		//	//saving party members ids
		//for (int i = 0; i < numOfObj; ++i)
		//{
		//	int represntId = _partyMembers->getCitizenByIndex(i).getCitizenID();
		//	outFile.write(rcastcc(&represntId), sizeof(int));
		//}
		////Save _representativesByDist list:
		//	//save number of objects(=cols in arr):
		//numOfObj = _representativesByDist->getLogicSize();
		//	//saving to file num of cols in arr:
		//outFile.write(rcastcc(&numOfObj), sizeof(int));
		//	//saving to file num of cols in arr:
		//for (int i = 0; i < numOfObj; ++i)
		//{
		//	int numOfRepsDist = _representativesByDist[i].getLogicSize();
		//		//saving the number of repsInDist[i]:
		//	outFile.write(rcastcc(&numOfRepsDist), sizeof(int));
		//		//saving party members ids
		//	for (int j = 0; j < numOfRepsDist; ++j)
		//	{
		//		int represntId = _partyMembers->getCitizenByIndex(i).getCitizenID();
		//		outFile.write(rcastcc(&represntId), sizeof(int));
		//	}
		//}
		


		
		
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

	void Party::realloc(int new_size)
	{
		double* new_memory = new double[new_size];

		for (int i = 0; i < min(new_size, _phySize); ++i)
		{
			new_memory[i] = _VotingPercentagesDistrict[i];
		}
		if (_logicSize >= 1)
		{
			delete[] _VotingPercentagesDistrict;
		}

		_phySize = new_size;
		_VotingPercentagesDistrict = new_memory;
	}

	bool  Party::setVotingPercentagesDistrict(double num, int districtID)
	{
		_VotingPercentagesDistrict[districtID - DISTRICT_ID_INIT] = num;
		return true;
	}



	ostream& operator<<(ostream& os, const Party& party)
	{
		os << "**********************************" << endl;
		os << party._partyName << ","<< (int)party._partyID << endl<<"The party leader candidate name and ID is " << party.getPartyLeader().getCitizenName() << ", " <<
			(int)party.getPartyPMCandidateID() << "." << endl << "Party members are:" << endl;
		for (int i = 1; i < party.getPartyMembers().getLogicSize(); ++i)
		{
			os << party.getPartyMembers().getCitizenByIndex(i).getCitizenName() << endl;
		}
		os << "**********************************" << endl;
		return os;
	}
}
