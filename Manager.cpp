/*
 * Manager.cpp
 *
 *  Created on: Dec 6, 2019
 *      Author: Nathaniel Lee
 */

#include "Manager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>

// manager constructor reads file and begins pairing
Manager::Manager()
	{
		ifstream input;
		input.open("a9.ini");
		string buf;
		string ab;
		string name;
		while (getline(input,buf) && !input.eof())
		{
			ab = buf.substr(0,5);
			name = buf.substr(5,18);
			myMap.insert(pair<string,string>(ab, name));


		}
	}
// table look up passes back value of abreviation dept to full name dept if found
	bool Manager::findDeptName(string s, string &ss)
	{
		bool flag = false;
		map<string,string>::iterator it;
		for (it = myMap.begin() ; it != myMap.end(); it++)
				{
					if (s == it->first)
					{
						ss = (it->second);
						flag = true;
					}
				}
		return flag;
	}


