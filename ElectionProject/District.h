//code verison 3.1

#pragma once
#include <vector>

using namespace std;
#include <string>
#include <vector>

namespace elec
{
	class LoadElectionSystem;
	class Citizen;

	class District
	{
	protected:
		static int snGenerator;
		int _serialNum;
		 
		string _name;
		vector<Citizen*> _citizens;
		double _votersPercentage;
		vector<int> _repsByPartyID;
		int _numOfReps;
		int _electionResult;
		int _numberOfVotesinDist;
		District(const District& other);
		const District& operator=(const District&);

	public:
		District(LoadElectionSystem& loader);
		District() = delete;
		District(string& name, int numOfReps, int numOfParties);
		virtual ~District();
		virtual void toOs(ostream& os) const = 0;
		friend ostream& operator<<(ostream& os, const District& district);

		/// <summary>
		/// this function to get the leader this dist chosen.
		/// </summary>
		/// <returns>citizen which is the party leader</returns>
		virtual const Citizen* getPartyLeader() const;
		/// <summary>
		/// this function helps us to set the leader this dist chosen.
		/// </summary>
		/// <returns>true if evertything is good else false.</returns>
		virtual bool setLeader(const Citizen* leader);

		Citizen& getCitizenByIndex(int idx);
		const Citizen& getCitizenByIndex(int index) const;

		virtual const string& getName() const;
		const double getVotersPrecentage() const;



		int getSerialNum() const;
		int getNumberOfCitizens() const;
		
		void addCitizen(Citizen& citz) noexcept(false);
		//todo: to any getCitizenById i need to handle an error.
		const Citizen& getCitizenById(int id) const;
		Citizen& getCitizenById(int id);
		
		int getNumOfReps() const;
		bool setVotersPrecentage(const int num);
		
		bool isCitizenExist(int id) const;
		/// <summary>
		/// returns how many citizrn has voted
		/// </summary>
		/// <returns>the amount of citizen voted.</returns>
		int getVotingCitizensAmountInDistrict() const;
		/// <summary>
		/// this function calculate the VotersPrecentage in the dist.
		/// </summary>
		/// <param name="">int</param>
		void operator++(int);
		/// <summary>
		/// the logic count of reps of a party in this dist.
		/// </summary>
		/// <returns>returns the ammount</returns>
		bool setRepsArrByPartyID(int partyID, int repsAmount);
		int getRepsByPartyID(int partyID) const;
		bool updateRepsArr();
		const vector<Citizen*>& getCitizens() const;
		/// <summary>
		/// saving the citizens in the list
		/// </summary>
		/// <param name="outFile">the file we want to write to</param>
		void save(ofstream& outFile) const;

	};
}