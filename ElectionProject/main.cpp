
//code verison 3.1

#include <iostream>
#include <fstream>
#include <vector>

#include "Exceptions.h"
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

	short typeInput;
	bool isDataValid = true;


	cout << "\nChoose type of Election:\n 1 - Regular Election.\n 2 - Simple Election." << endl;
	cin >> typeInput;

	while (typeInput != 1 && typeInput != 2)
	{
		cout << "There is no option: " << typeInput << ". please try again" << endl;
		cout << "\nChoose type of Election:\n 1 - Regular Election.\n 2 - Simple Election." << endl;
		cin >> typeInput;
	}
	ElectionType choice = static_cast<ElectionType>(typeInput);

	while (isDataValid)
	{
		cout << "Enter election's date (dd mm yyyy)" << endl;
		cin >> date_d >> date_m >> date_y;

		try
		{
			if (choice == ElectionType::RegularElectionRound)
			{
				election = new RegularElectionRound(date_d, date_m, date_y);
			}
			else
			{
				cout << "Enter number of reps" << endl;
				cin >> numofreps;
				election = new SimpleElectionRound(date_d, date_m, date_y, numofreps);
			}
			isDataValid = false;
		}
		catch (DayException& day)
		{
			day.Error();
			cout << day.getMessage();
			cout << "\nPlease try again." << endl;
		}
		catch (MonthException& month)
		{
			month.Error();
			cout << month.getMessage();
			cout << "\nPlease try again." << endl;
		}
		catch (DayMonthException& e)
		{
			e.Error();
			cout << e.getMessage();
			cout << "\nPlease try again." << endl;
		}
		cout << endl;
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
	string name;
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
		try
		{
			election->addNewDistrict(name, numberRepresentatives, districtId, distType);
			cout << "District " << name << " added. \n And its id is " << districtId << endl;
		}
		catch (exception& ex)
		{
			cout << "Error:" << ex.what() << endl;;
		}
		catch (ElectionSystemException& e)
		{
			e.Error();
			cout << e.getMessage();
		}
	}
}
constexpr  int checkLen(int id)
{
	int count = 0;
	do {
		++count;
		id /= 10;
	} while (id);
	return count;
}
void addCitizen()
{
	int birtyear, districtId = DISTRICT_ID_INIT;
	string name;
	int id;

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


		try {
			if (election->getYear() - birtyear < 18)
			{
				throw AgeException(birtyear, election->getYear());

			}

		}
		catch (AgeException& e)
		{
			e.Error();
			cout << e.getMessage();
		}
		try {
			const int lenofId = checkLen(id);
			if (lenofId != 9)
			{
				throw invalid_argument("The len of the id is is too short, when it must be 9 digits.\n");
			}
		}
		catch (exception& ex)
		{
			cout <<"Error : " <<ex.what();
			cout << "Citizen wasn't added";
			return;
		}
		try {
			if (name.find_first_not_of(' ') == std::string::npos)
			{
				throw invalid_argument("Invalid name: empty name.");
			}
		}
		catch (exception& ex)
		{
			cout << "Error:" << ex.what() << endl;
			cout << "Citizen wasn't added";
			return;
		}
		try {
			if (name.find_first_of("0123456789") != std::string::npos)
			{
				throw invalid_argument("Name contains digits");

			}
		}
		catch (exception& ex)
		{
			cout << "Error:" << ex.what() << endl;
			cout << "Citizen wasn't added";
			return;
		}
		try {
			election->addNewCitizen(name, id, birtyear, districtId);
			cout << "Citizen " << name << " added." << endl;
		}
	catch(ElectionSystemException& ex)
	{
		ex.Error();
		cout << "ERROR :" << ex.getMessage();
		cout << "Citizen wasn't added";
		return;
	}






	//if (typeid(*election) == typeid(RegularElectionRound)) {
	//	cout << "Error:Citizen with that id is already exist or/and district doesn't exist." << endl;
	//}
	//else
	//{
	//	cout << "Error:Citizen with that id is already exist." << endl;
	//}



}





void addParty()
{
	int idPd;
	string name;
	int partyId;
	cout << "Insert a party name,id of PD of party:" << endl;
	cin >> name >> idPd;
	try {
		const int lenofId = checkLen(idPd);
		if (lenofId != 9)
		{
			throw invalid_argument("The len of the id is is too short, when it must be 9 digits.\n");
		}
	}
	catch (exception& ex)
	{
		cout << "Error : " << ex.what();
		cout << "Citizen wasn't added";
		return;
	}
	try {
		election->addNewParty(name, idPd, partyId);
		cout << "Party " << name << " added.\nAnd its id is " << partyId << endl;
	}
	catch(ElectionSystemException&ex)
	{
		ex.Error();
		cout<<ex.getMessage()<<endl;
		cout << "Error:Party leader doesn't exist" << endl;
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
void viewDistricts() noexcept(false)
{
	try
	{
		election->viewAllDistricts();
	}
	catch (ResultsException msg)
	{
		cout << "ERROR: " << msg.getMessage() << endl;
	}
}


void viewCitizens()
{
	try
	{
		election->viewAllCitizens();

	}
	catch (ResultsException msg)
	{
		cout << msg.getMessage() << endl;
	}

}

void viewParties()
{
	try
	{
		election->viewAllParties();

	}
	catch (string& msg)
	{
		cout << msg << endl;
	}

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
	try
	{
		election->theResults();
		cout << *election << endl;
	}
	catch (ResultsException msg)
	{
		cout <<  msg.getMessage() << endl;
	}
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

	ifstream _inFile;


	char fileName[MAX_SIZE];
	cout << "Enter name of the file you want to load" << endl;
	cin >> fileName;
	try {

		LoadElectionSystem loader(fileName);



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
		catch (const ifstream::failure& ex)
		{
			return false;
		}
		return true;


}



