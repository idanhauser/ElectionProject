#include "ElectionMain.h"

namespace elecMain {
	void mainMenu()
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
				cout << "Add a district \n";
				// rest of code here
				break;
			case Menu_Choices::addCitizen:
				cout << "Add a citizen\n";
				// rest of code here
				break;
			case Menu_Choices::addParty:
				cout << "Add a party\n";
				// rest of code here
				break;
			case Menu_Choices::addPartyRepresentative:
				cout << "Add a citizen as a party representative\n";
				// rest of code here
				break;
			case Menu_Choices::viewCountie:
				cout << "View all counties\n";
				// rest of code here
				break;
			case Menu_Choices::viewCitizens:
				cout << "View all citizens\n";
				// rest of code here
				break;
			case Menu_Choices::viewParties:
				cout << "View all parties.\n";
				// rest of code here
				break;
			case Menu_Choices::voting:
				cout << "Voting\n";
				// rest of code here
				break;
			case Menu_Choices::results:
				cout << "Results\n";
				// rest of code here
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
}