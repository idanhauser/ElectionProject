// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//code verison 1.0

#include <iostream>
#include "Utils.h"
#include "ElectionRound.h"
using namespace std;

using namespace elec;
int dateArr[] = { 2,7,0,1,2,0,2,0 };
ElectionRound election(dateArr);

void showMainMenu();
void addDistrict();
void addCitizen();
void addParty();
void addPartyRepresentative();
void viewDistricts();
void viewCitizens();
void viewParties();
void voting();
void results();





int main()
{


	cout << "Election ";
	election.printElectionDate();
	cout << endl << "-------------" << endl;
	showMainMenu();

	cout << "goodbye" << endl;




}

void showMainMenu()
{
	short userChoise;
	Menu_Choices choice = Menu_Choices::addCitizen;
	while (choice != Menu_Choices::exit_menu)
	{
		cout << "Election Menu:" << endl;
		cout << "Press 1 to add a district" << endl;
		cout << "Press 2 to add a citizen" << endl;
		cout << "Press 3 to add a party" << endl;
		cout << "Press 4 to add a citizen as a party representative" << endl;
		cout << "Press 5 to view all district" << endl;
		cout << "Press 6 to view all citizens" << endl;
		cout << "Press 7 to view all parties" << endl;
		cout << "Press 8 to voting" << endl;
		cout << "Press 9 to Presenting the election result" << endl;
		cout << "Press 10 to exit" << endl;

		cin >> userChoise;
		choice = static_cast<Menu_Choices>(userChoise);
		switch (choice)
		{

		case Menu_Choices::addDistrict:
			cout << endl;
			cout << "-------------" << endl;
			cout << "Add District" << endl;
			cout << "-------------" << endl;
			addDistrict();
			cout << endl;
			break;
		case Menu_Choices::addCitizen:
			cout << endl;
			cout << "-------------" << endl;
			cout << "Add Citizen" << endl;
			cout << "-------------" << endl;
			addCitizen();
			cout << endl;
			break;
		case Menu_Choices::addParty:
			cout << endl;
			cout << "-------------" << endl;
			cout << "Add A Party" << endl;
			cout << "-------------" << endl;
			addParty();
			cout << endl;
			break;
		case Menu_Choices::addPartyRepresentative:
			cout << endl;
			cout << "-------------" << endl;
			cout << "Add A Party Representative" << endl;
			cout << "-------------" << endl;
			addPartyRepresentative();
			cout << endl;
			break;
		case Menu_Choices::viewDistricts:
			cout << "-------------" << endl;
			cout << "View Districts" << endl;
			cout << "-------------" << endl;
			viewDistricts();
			cout << endl;
			break;
		case Menu_Choices::viewCitizens:
			cout << "-------------" << endl;
			cout << "View Citizens" << endl;
			cout << "-------------" << endl;
			viewCitizens();
			cout << endl;
			break;
		case Menu_Choices::viewParties:
			cout << "-------------" << endl;
			cout << "View Parties" << endl;
			cout << "-------------" << endl;
			viewParties();
			cout << endl;
			break;
		case Menu_Choices::voting:
			cout << "-------------" << endl;
			cout << "Voting" << endl;
			cout << "-------------" << endl;
			voting();
			cout << endl;
			break;
		case Menu_Choices::results:
			cout << "-------------" << endl;
			cout << "Results" << endl;
			cout << "-------------" << endl;
			results();
			cout << endl;
			break;
		case Menu_Choices::exit_menu:
			cout << "Bye-bye." << endl;
			break;
		default:
			cout << "Not a Valid Choice. \n Try again";

			cout << endl;
			break;
		}
	}
}


void addDistrict()
{
	int districtId;
	char name[MAX_SIZE];
	int numberRepresentatives;
	cout << "Insert a district's name and a number of representatives:" << endl;
	cin >> name >> numberRepresentatives;
	if (!election.addNewDistrict(name, numberRepresentatives, districtId))
	{
		cout << "Error:District " << name << " was't added." << endl;
	}
	else
	{
		cout << "District " << name << " added. \n And its id is " << districtId << endl;
	}

}

void addCitizen()
{
	int id, birtyear, districtId;
	char name[MAX_SIZE];
	const int currYear = election.getYear();
	cout << "Insert a citizen name,id ,birth year, district:" << endl;
	cin >> name >> id >> birtyear >> districtId;

	if (currYear - birtyear >= 18)
	{
		if (!election.addNewCitizen(name, id, birtyear, districtId))
		{


			cout << "Error:Citizen with that id is already exist or/and cistrict doesn't exist." << endl;

		}
		else
		{
			cout << "Citizen " << name << " added." << endl;
		}
	}
	else
	{
		cout << "Error:" << name << " is too young to vote." << endl;
	}
}

void addParty()
{
	int idPd;
	char name[MAX_SIZE];
	int partyId;
	cout << "Insert a party name,id of PD of party:" << endl;
	cin >> name >> idPd;
	if (!election.addNewParty(name, idPd, partyId))
	{
		cout << "Error:Party leader doesn't exist" << endl;
	}
	else
	{
		cout << "Party " << name << " added.\nAnd its id is " << partyId << endl;
	}
}

void addPartyRepresentative()
{
	int partyId, representId, districtId;


	cout << "Insert a representative citizen's id ,district's id, party's id:" << endl;
	cin >> representId >> districtId >> partyId;
	election.addNewPartyRepresentative(representId, partyId, districtId);
}

void viewDistricts()
{
	election.viewAllDistricts();
}

void viewCitizens()
{
	election.viewAllCitizens();
}

void viewParties()
{
	election.viewAllParties();
}

void voting()
{
	int partyId, citizenId;
	cout << "Insert a citizen's id and the party's id he wants to vote to:" << endl;
	cin >> citizenId >> partyId;
	if (!election.votingAction(citizenId, partyId))
	{
		cout << "Error:Citizen already voted or citizen doesn't exist" << endl;
	}
	else
	{
		cout << "Vote was successful inserted." << endl;
	}

}

void results()
{
	election.theResults();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
