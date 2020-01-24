/*
 * Manager.h
 *
 *  Created on: Nov 30, 2019
 *      Author: Nathaniel Lee
 */
#include <map> // using stl map
#include <string>
#include <fstream>
#include <iostream>
#ifndef MANAGER_H_
#define MANAGER_H_
using namespace std;

class Manager
{
private:
	// private member is a map
	map <string, string> myMap;
public:
	// constructor
	Manager();
	// gives value of abreviation department to full name of dept
	bool findDeptName(string s, string &ss);
};



#endif /* MANAGER_H_ */
