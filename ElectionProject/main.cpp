
//code verison 2.0

#include <iostream>
#include <ctime>
#include "Utils.h"
#include "ElectionRound.h"
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


void StartMenu();

bool isExit = false;
int main()
{

	cout << "Election ";
	cout << endl << "-------------" << endl;
	StartMenu();




	cout << "bye" << endl;


}

void initElection();

void StartMenu()
{
	int chosen;
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
			//loadElectionFromFile();
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
	int datearr[DATE_SIZE];
	int type;
	cout << "Enter election's date (ddmmyyyy)" << endl;
	cin >> date_d >> date_m >> date_y;
	for (int i = DATE_SIZE-1; i >= 0; --i)
	{
		if (i >= DATE_SIZE - 4)
		{
			datearr[i] = date_y % 10;
			date_y /= 10;
		}
		else if(i>=2)
		{
			datearr[i] = date_m % 10;
			date_m /= 10;
		}
		else
		{
			datearr[i] = date_d % 10;
			date_d /= 10;
		}
	}
	cout << "\nChoose type of menu 1 - for standart, 2 - for new" << endl;
	cin >> type;
	if (type == 1)
	{
		election = new RegularElectionRound(datearr);
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
		election = new SimpleElectionRound(datearr, numofreps);
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
	int numberRepresentatives = 0;
	RegularElectionRound* regularElec = dynamic_cast<RegularElectionRound*>(election);
	if (regularElec != nullptr)
	{
		cout << "Insert a district's name and a number of representatives:" << endl;
		cin >> name >> numberRepresentatives;
		if (numberRepresentatives >= 0)
		{
			if (!regularElec->addNewDistrict(name, numberRepresentatives, districtId))
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
			cout << "Negative number of representatives is not allowed." << endl;
		}
	}
	else
	{
		if (!election->addNewDistrict(name, numberRepresentatives, districtId))
		{
			cout << "ERROR: You chose 'Simple election round' therefor you can not add districts." << endl;
		}
	}
}

void addCitizen()
{
	int id, birtyear, districtId=DISTRICT_ID_INIT;
	char name[MAX_SIZE];
	const int currYear = election->getYear();

	if (typeid(*election)==typeid(RegularElectionRound))
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
	int partyId, representId, districtId=DISTRICT_ID_INIT;

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
}



