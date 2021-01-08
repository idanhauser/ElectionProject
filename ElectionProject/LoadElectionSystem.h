﻿//code verison 3.1
#pragma once
#include <fstream>
#include <string>
#include "Utils.h"

namespace elec
{
	class LoadElectionSystem
	{
	private:
		 ifstream _inFile;
		 bool _isFileNotOk;
	public:
		LoadElectionSystem() = delete;
		LoadElectionSystem(string fileName);


		///closing the file.
		 ~LoadElectionSystem();
		/// <summary>
		/// checks what type of election the file holds.
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