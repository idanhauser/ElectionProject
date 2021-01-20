//code verison 3.2
#pragma once
#include <fstream>
#include <string>
#include "Utils.h"
#include <algorithm>
namespace elec
{
	class LoadElectionSystem
	{
	private:
		 ifstream _inFile;
		 bool _isFileNotOk;
	public:
		LoadElectionSystem()=default;
		LoadElectionSystem(string fileName) noexcept(false);


		///closing the file.
		 ~LoadElectionSystem();
		/// <summary>
		/// checks what 
///  of election the file holds.
		/// </summary>
		/// <returns>return election type regular or simple.</returns>
		ElectionType getElectionType();
		/// <summary>
		/// checks if file is ok and we can read from it.
		/// </summary>
		/// <returns>true if the file is good to read from else false.</returns>
		bool CheckFile() const;
		 /// <summary>
		 /// returns to file we read from
		 /// </summary>
		 /// <returns>the file we read from.</returns>
		 ifstream& getReader();
	};
}