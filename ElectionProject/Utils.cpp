//code verison 1.0
#include "Utils.h"

using namespace std;
namespace elec {


	void showMainMenu()
	{
		short userChoise;
		Menu_Choices	choice = Menu_Choices::addDistrict;
		while (choice != Menu_Choices::exit_menu)
		{
			cout << "Election Menu:" << endl;
			cout << "Press 1 to add a district\n";
			cout << "Press 2 to add a citizen\n";
			cout << "Press 3 to add a party\n";
			cout << "Press 4 to add a citizen as a party representative\n";
			cout << "Press 5 to view all counties\n";
			cout << "Press 6 to view all citizens\n";
			cout << "Press 7 to view all parties\n";
			cout << "Press 8 to voting\n";
			cout << "Press 9 to Presenting the election result\n";
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
				break;
			case Menu_Choices::addCitizen:
				cout << endl;
				cout << "-------------" << endl;
				cout << "Add Citizen" << endl;
				cout << "-------------" << endl;
				addCitizen();
				break;
			case Menu_Choices::addParty:
				cout << endl;
				cout << "-------------" << endl;
				cout << "Add A Party" << endl;
				cout << "-------------" << endl;
				addParty();
				break;
			case Menu_Choices::addPartyRepresentative:
				cout << endl;
				cout << "-------------" << endl;
				cout << "Add A Party Representative" << endl;
				cout << "-------------" << endl;
				addPartyRepresentative();
				break;
			case Menu_Choices::viewDistricts:
				cout << "-------------" << endl;
				cout << "View Districts" << endl;
				cout << "-------------" << endl;
				viewDistricts();
				break;
			case Menu_Choices::viewCitizens:
				cout << "-------------" << endl;
				cout << "View Citizens" << endl;
				cout << "-------------" << endl;
				viewCitizens();
				break;
			case Menu_Choices::viewParties:
				cout << "-------------" << endl;
				cout << "View Parties" << endl;
				cout << "-------------" << endl;
				viewParties();
				break;
			case Menu_Choices::voting:
				cout << "-------------" << endl;
				cout << "Voting" << endl;
				cout << "-------------" << endl;
				break;
			case Menu_Choices::results:
				cout << "-------------" << endl;
				cout << "Results" << endl;
				cout << "-------------" << endl;
				break;
			case Menu_Choices::exit_menu:
				cout << "Bye-bye.\n";
				// rest of code here
				break;
			default:
				cout << "Not a Valid Choice. \n";
				cout << endl;
				break;
			}
		}
	}

	void addDistrict()
	{
		char name[MAX_SIZE];
		int numberRepresentatives;
		cout << "Insert a district's name and a number of representatives:" << endl;
		cin >> name >> numberRepresentatives;

	}

	void addCitizen()
	{
		int id, birtyear, districtId;
		char name[MAX_SIZE];


		cout << "Insert a citizen name,id ,birth year, district:" << endl;
		cin >> name >> id >> birtyear >> districtId;

	}

	void addParty()
	{
		int idPd;
		char name[MAX_SIZE];


		cout << "Insert a party name,id of PD of party:" << endl;
		cin >> name >> idPd >> idPd;

	}

	void addPartyRepresentative()
	{
		int partyId, representId, districtId;


		cout << "Insert a representative citizen's id ,district's id, party's id:" << endl;
		cin >> representId >> districtId >> partyId >> districtId;
	}

	void viewDistricts()
	{

	}

	void viewCitizens()
	{
	}

	void viewParties()
	{
	}
}