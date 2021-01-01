
//code verison 3.0

#include <iostream>
#include <fstream>

#include "Utils.h"
#include "ElectionRound.h"
#include "LoadElectionSystem.h"
#include "RegularElectionRound.h"
#include "SimpleElectionRound.h"
using namespace std;

using namespace elec;

ElectionRound* election = nullptr;
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
void saveElections();
bool loadElection();
void StartMenu();

bool isExit = false;
int main()
{

	cout << "Election ";
	cout << endl << "-------------" << endl;
	StartMenu();


}

void initElection();

void StartMenu()
{
	short userChoise;
	Start_MenuChoices choice = Start_MenuChoices::startNewElectionRound;
	while (choice != Start_MenuChoices::exit_menu && !isExit)
	{
		cout << "Main Election Menu:" << endl;
		cout << "Press 1 to start election round" << endl;
		cout << "Press 2 to load election round" << endl;
		cout << "Press 3 to exit" << endl;


		cin >> userChoise;
		choice = static_cast<Start_MenuChoices>(userChoise);
		switch (choice)
		{
		case Start_MenuChoices::startNewElectionRound:
			cout << endl;
			cout << "-------------" << endl;
			cout << "start New Election Round" << endl;
			cout << "-------------" << endl;
			initElection();
			cout << endl;
			break;
		case Start_MenuChoices::loadElection:
			cout << endl;
			cout << "-------------" << endl;
			cout << "Load election round from file" << endl;
			cout << "-------------" << endl;
			if (loadElection())
			{
				cout << "Election was loaded successfully." << endl;
				showMainMenu();
			}
			else
			{
				cout << "Election was not loaded successfully." << endl;
			}
			cout << endl;
			break;
		case Start_MenuChoices::exit_menu:
			cout << "Bye-bye." << endl;
			break;
		default:
			cout << "Not a Valid Choice. \n Try again";

			cout << endl;
			break;
		}
	}
}

void initElection()
{

	int numofreps = 0;
	int date_y;
	int date_d;
	int date_m;
	int dateArr[DATE_SIZE];
	short typeInput;

	cout << "Enter election's date (dd mm yyyy)" << endl;
	cin >> date_d >> date_m >> date_y;
	for (int i = DATE_SIZE - 1; i >= 0; --i)
	{
		if (i >= DATE_SIZE - 4)
		{
			dateArr[i] = date_y % 10;
			date_y /= 10;
		}
		else if (i >= 2)
		{
			dateArr[i] = date_m % 10;
			date_m /= 10;
		}
		else
		{
			dateArr[i] = date_d % 10;
			date_d /= 10;
		}
	}
	cout << "\nChoose type of Election:\n 1 - Regular Election.\n 2 - Simple Election." << endl;
	cin >> typeInput;
	ElectionType choice = static_cast<ElectionType>(typeInput);
	if (choice == ElectionType::RegularElectionRound)
	{
		election = new RegularElectionRound(dateArr);
	}
	else
	{
		cout << "Enter number of reps" << endl;
		cin >> numofreps;
		while (numofreps <= 0)
		{
			cout << "Number of reps can't be negative or zero, please insert netrual number" << endl;
			cin >> numofreps;
		}
		election = new SimpleElectionRound(dateArr, numofreps);
	}
	showMainMenu();
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
		cout << "Press 5 to view all districts" << endl;
		cout << "Press 6 to view all citizens" << endl;
		cout << "Press 7 to view all parties" << endl;
		cout << "Press 8 to voting" << endl;
		cout << "Press 9 to Presenting the election result" << endl;
		cout << "Press 10 to exit" << endl;
		cout << "Press 11 to save election system into file" << endl;
		cout << "Press 12 load election system" << endl;
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
			isExit = true;
			break;
		case Menu_Choices::saveElection:
			cout << "-------------" << endl;
			cout << "Save Election" << endl;
			cout << "-------------" << endl;
			saveElections();
			cout << endl;
			break;
		case Menu_Choices::loadElection:
			cout << "-------------" << endl;
			cout << "Load Election" << endl;
			cout << "-------------" << endl;
			if (loadElection())
			{
				cout << "Election was loaded successfully." << endl;
			}
			else
			{
				cout << "Election was not loaded successfully." << endl;
			}
			cout << endl;
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

	int districtId = DISTRICT_ID_INIT;
	char name[MAX_SIZE];
	int numberRepresentatives;
	int userChoise = 0;
	if (typeid(*election) == typeid(SimpleElectionRound))
	{
		cout << "ERROR: You chose 'Simple election round' therefor you can not add districts." << endl;
	}
	else
	{
		cout << "Insert a district's name and a number of representatives:" << endl;
		cin >> name >> numberRepresentatives;
		cout << "Choose district type:" << endl;
		cout << "Press 1 for unified District" << endl;
		cout << "Press 2 for divided District" << endl;
		cin >> userChoise;
		DistcritType distType = static_cast<DistcritType>(userChoise);
		if (numberRepresentatives >= 0)
		{
			if (!election->addNewDistrict(name, numberRepresentatives, districtId, distType))
			{
				cout << "Error:District " << name << " wasn't added." << endl;
			}
			else
			{
				cout << "District " << name << " added. \n And its id is " << districtId << endl;
			}
		}
		else
		{
			cout << "ERROR: Negative number of representatives is not allowed." << endl;
		}
	}
}

void addCitizen()
{
	int id, birtyear, districtId = DISTRICT_ID_INIT;
	char name[MAX_SIZE];
	const int currYear = election->getYear();

	if (typeid(*election) == typeid(RegularElectionRound))
	{
		cout << "Insert a citizen name,id ,birth year, district:" << endl;
		cin >> name >> id >> birtyear >> districtId;
	}
	else
	{
		cout << "Insert a citizen name,id ,birth year:" << endl;
		cin >> name >> id >> birtyear;
	}
	if (currYear - birtyear >= 18)
	{
		if (!election->addNewCitizen(name, id, birtyear, districtId))
		{
			if (typeid(*election) == typeid(RegularElectionRound)) {
				cout << "Error:Citizen with that id is already exist or/and district doesn't exist." << endl;
			}
			else
			{
				cout << "Error:Citizen with that id is already exist." << endl;
			}
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
	if (!election->addNewParty(name, idPd, partyId))
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
	int partyId, representId, districtId = DISTRICT_ID_INIT;

	if (typeid(*election) == typeid(RegularElectionRound)) {
		cout << "Insert a representative citizen's id, district's id, party's id:" << endl;
		cin >> representId >> districtId >> partyId;
	}
	else
	{
		cout << "Insert a representative citizen's id, party's id:" << endl;
		cin >> representId >> partyId;
	}
	if (!election->addNewPartyRepresentative(representId, partyId, districtId))
	{
		if (typeid(*election) == typeid(RegularElectionRound)) {
			cout << "Error:Citizen and/or district and/or party doesn't exist." << endl;
		}
		else
		{
			cout << "Error:Citizen and/or party doesn't exist." << endl;
		}
	}
	else
	{
		cout << "Party's representative added." << endl;
	}


}
void viewDistricts()
{
	election->viewAllDistricts();
}


void viewCitizens()
{
	election->viewAllCitizens();
}

void viewParties()
{
	election->viewAllParties();
}

void voting()
{
	int partyId, citizenId;
	cout << "Insert a citizen's id and the party's id he wants to vote to:" << endl;
	cin >> citizenId >> partyId;
	if (!election->votingAction(citizenId, partyId))
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
	election->theResults();
	cout << *election << endl;
}

void saveElections()
{
	char fileName[MAX_SIZE];
	cout << "Enter name of file to save" << endl;
	cin >> fileName;
	ofstream outFile(fileName, ios::binary | ios::trunc);

	if (!outFile) {
		cout << "error outfile" << endl;
		exit(-1);
	}


	cout << "Saving election system..." << endl;
	election->save(outFile);
	cout << "election system saved successfully." << endl;
}

bool loadElection()
{
	bool loadedSuccessfully = true;
	ifstream _inFile;
	


	char fileName[MAX_SIZE];
	cout << "Enter name of the file you want to load" << endl;
	cin >> fileName;

	LoadElectionSystem loader(fileName);
	if (!loader.CheckFile())
	{
		cout << "error infile" << endl;
		loadedSuccessfully = false;
	}
	else
	{
		delete election;
		ElectionType type = loader.getElectionType();

		if (type == ElectionType::RegularElectionRound)
		{
			election = new RegularElectionRound(loader);
		}
		else
		{
			election = new SimpleElectionRound(loader);
		}

	}
	return loadedSuccessfully;

}



