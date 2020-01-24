//============================================================================
// Name        : NathanielLeeA9.cpp
// Author      : Nathaniel Lee
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector> // using stl vector class
#include <fstream>
#include <iomanip>
#include <map> // using stl map class
#include "Manager.h"
using namespace std;

struct Grade // data structure that holds grade information
{
	string dept;
	string courseNum;
	string credit;
	string grade;
};

struct Student // student structure that holds student information with  their grades
{
	string studentID;
	string name;
	vector<Grade*> grades;
};
// function prototypes that fulfill querries requirements
void displayCS(vector<Student*>);
void displayENGR(vector<Student*>);
void displayFailEng(vector<Student*>);
// function prototype that deletes dynamically allocated memory
void deleteDyn(vector<Student*>);

int main(int inputCount, char * inputsPointersArray[]) { // main function contains command line arguments

	// vector of student pointers
	vector<Student*>students;
	// all variables that will be needed in extracting file data
	ifstream inputFile;
		string get;
		string ID;
		string studentID;
		string studentName;
		string dept;
		string course;
		string credit;
		string grade;
		string fileName;
		string fileDate;
		//cout << "inputCount " << inputCount << endl;
			int inputsProcessed;
			string s;
			// for loop that displays arguments passed as command line arguments
			for (inputsProcessed = 0; inputsProcessed < inputCount; inputsProcessed++)
			{
				s = inputsPointersArray[inputsProcessed];
				//cout << s << endl;
				if (inputsProcessed == 1)
				{
					fileName = s;
					//cout << s << endl;
				}
				if (inputsProcessed == inputCount - 1)
				{
					// assumes a passed paramter are valid numerics
					// a dangerous assumtion
					fileDate = s;

				}
			}
			cout << "File Name : " << fileName << endl;
			cout << "File Date: " << fileDate << endl;
			cout << endl;

		//inputFile.open("a9data.txt");
		// open file name that was passed as a command line arguments
		inputFile.open(fileName);
		// two pointers of our two different structures
		Student *p;
		Grade*q;
		// if file exists then proceed
		if(!inputFile.fail())
		{
			//while file can still get line and it has not reached end of file
			while (getline(inputFile, get, '\n') && !inputFile.eof())
			{
				// first character will always be ID in file
				ID = get.substr(0,1);
				// if ID begins with 1, it will be a student's general information
				if (ID == "1")
				{
					// dynamic memory allocation
					p = new Student;

					studentID = get.substr(1,6);
					p -> studentID = studentID;
					studentName = get.substr(7,14);
					// trying to erase the \n character at every name's last char position
					studentName.erase(studentName.size()-1,1);
					p->name = studentName;
					// push that student pointer into our vector of student pointers
					students.push_back(p);


				}
				// if ID is 2, it will be the student's grade information
				if (ID == "2"){
				// dynamic memory allocation
				q = new Grade;
				dept = get.substr(1,6);
				dept.erase(dept.size()-1,1);

				q -> dept = dept;

				course = get.substr(6,4);
				q -> courseNum = course;

				credit = get.substr(10,1);
				q->credit = credit;

				grade = get.substr(11,1);
				q->grade = grade;

				p->grades.push_back(q);


				}
				// if file not working
				else if (ID != "1" && ID != "2")
				{
					cout << "not working" << endl;
				}


			}// end of while loop for reading file
			// close file
			inputFile.close();
		}

		// if file DNE
		else
		{
			cout << "File not found" << endl;
			exit(44);
		}
		// after file information has been read, we instantitate a manager class object
		// once constructor executes, pairing and table look up will call itself
		Manager manager;
		//map<string,string>::iterator it;

		// student pointer vector iterator
		vector<Student*>::iterator z;
		int x = 0;
		int y = 0;

		float points = 0;
		float gpa = 0;
		float pointsTemp;

		int credit1 = 0;
		int totalCredit = 0;
		// for loop that displays all students and their grades
		for (z = students.begin(); z != students.end(); z++)
		{

			cout << students.at(x)->name << " ";
			cout << students.at(x)->studentID << " ";
			cout << "Transcript: " << endl;
			cout << endl;
			vector<Grade*>::iterator u;
			// if student has grades
			if (students.at(x)->grades.size() > 0)
			{
				for (u = students.at(x)->grades.begin() ; u!= students.at(x)->grades.end(); u++)
				{
						string s;
						if (manager.findDeptName(students.at(x)->grades.at(y)->dept, s))
						{
							s.erase(s.size()-1,1);
						}
						else
						{
							s = "Unknown Department";

						}

						cout << s << " ";

						cout << students.at(x)->grades.at(y)->courseNum << " ";
						cout << students.at(x)->grades.at(y)->credit << " ";
						cout << students.at(x)->grades.at(y)->grade <<endl;
						credit1 = stoi(students.at(x)->grades.at(y)->credit);
						// calculating points based on grade case
						if (students.at(x)->grades.at(y)->grade == "A")
						{
							pointsTemp = 4 * credit1;
						}
						if (students.at(x)->grades.at(y)->grade == "B")
						{
							pointsTemp = 3 * credit1;
						}
						if (students.at(x)->grades.at(y)->grade == "C")
						{
							pointsTemp = 2 * credit1;
						}
						if (students.at(x)->grades.at(y)->grade == "D")
						{
							pointsTemp = 1 * credit1;
						}
									// calculating grade point average
						totalCredit += credit1;
						points += pointsTemp;
									// increment grade vector position
						y++;
						}
						gpa = (points / totalCredit);
						cout << setprecision(2) << fixed << "Student " << students.at(x)->studentID << " GPA: " << gpa;
						pointsTemp = 0;
						credit1 = 0;
						points = 0;
						totalCredit = 0;
						y = 0;
						cout << endl;
						cout << endl;
								// increment student vector position
						x++;
			}
			// if students do not have grades
			else
			{
				cout << "Student has no transcript" << endl;
			}
			}

				// end of transcript list statement
				cout << "End of Student List, there are " << x << " students listed" << endl << endl;
				// starting last part of assignment
				cout << "Beginning of Queries" << endl << endl;
				// calling 3 query functions
				displayCS(students);
				cout << endl;
				displayENGR(students);
				cout << endl;
				cout << endl;
				displayFailEng(students);
				cout << endl;

				// delete dynamically allocated memory
				deleteDyn(students);


	return 0;
}
// function that displays the student A34567 computer sciences classes
void displayCS(vector <Student *> students)
{
	int count = 0;
	int secondCount = 0;
	vector<Student*>::iterator myIt;
	for (myIt = students.begin(); myIt != students.end(); myIt++)
	{
		if (students.at(count)->studentID == "A34567")
		{
			cout << "Student " << students.at(count)->studentID << ": " << students.at(count)->name  << " is taking these COMSC classes:"<<  endl;
			vector<Grade*> ::iterator gIT;
			for (gIT = students.at(count)->grades.begin(); gIT != students.at(count)->grades.end(); gIT++)
			{
				//cout << students.at(count)->grades.at(secondCount)->dept << endl;
				if (students.at(count)->grades.at(secondCount)->dept == "COMSC")
				{

						cout << students.at(count)->grades.at(secondCount)->dept<< " ";
						cout << students.at(count)->grades.at(secondCount)->courseNum << " ";
						cout << students.at(count)->grades.at(secondCount)->credit << " ";
						cout << students.at(count)->grades.at(secondCount)->grade <<endl;

				}
				secondCount++;
			}
			secondCount = 0;


		}
		count++;
	}
}
// displays the engineering classes of student A56789 with its GPA
void displayENGR(vector<Student*> students)
{

	int count = 0;
		int secondCount = 0;
		vector<Student*>::iterator myIt;
		float points=0;
		int tempPoints =0;
		int totalCredit = 0;
		int credit = 0;
		for (myIt = students.begin(); myIt != students.end(); myIt++)
		{
			if (students.at(count)->studentID == "A56789")
			{
				cout << "Student " << students.at(count)->studentID << ": " << students.at(count)->name  << " is taking these ENGR classes:"<<  endl;
				vector<Grade*> ::iterator gIT;
				for (gIT = students.at(count)->grades.begin(); gIT != students.at(count)->grades.end(); gIT++)
				{


					if (students.at(count)->grades.at(secondCount)->dept == "ENGR ")
					{
							cout << students.at(count)->grades.at(secondCount)->dept<< " ";
							cout << students.at(count)->grades.at(secondCount)->courseNum << " ";
							cout << students.at(count)->grades.at(secondCount)->credit << " ";
							cout << students.at(count)->grades.at(secondCount)->grade <<endl;

							credit  = stoi(students.at(count)->grades.at(secondCount)->credit);
							if (students.at(count)->grades.at(secondCount)->grade == "A")
							{
								tempPoints = (4 * credit);
							}
							else if(students.at(count)->grades.at(secondCount)->grade == "B")
							{
								tempPoints = (3 * credit);
							}
							else if(students.at(count)->grades.at(secondCount)->grade == "C")
							{
								tempPoints = (2 * credit);
							}
							else if(students.at(count)->grades.at(secondCount)->grade == "D")
							{
								tempPoints = (1 * credit);
							}

							totalCredit += credit;
							points += tempPoints;
					}
					secondCount++;
				}
				secondCount = 0;


			}
			count++;
		}
		cout << setprecision(2) << fixed << "Engineering GPA: " << points / totalCredit;
}
// displays all students who have not taken an english class, or who have failed an english 101
void displayFailEng(vector<Student*> students)
{
	int count = 0;
			int secondCount = 0;
			int engCount = 0;
			vector<Student*>::iterator myIt;
			for (myIt = students.begin(); myIt != students.end(); myIt++)
			{

					vector<Grade*> ::iterator gIT;
					for (gIT = students.at(count)->grades.begin(); gIT != students.at(count)->grades.end(); gIT++)
					{

						if (students.at(count)->grades.at(secondCount)->dept == "ENGL ")
						{
							engCount++;

							if (students.at(count)->grades.at(secondCount)->grade == "D" || students.at(count)->grades.at(secondCount)->grade == "F")
							{

								cout << students.at(count)->name << " has not passed an English course" << endl;

							}


						}

						secondCount++;

					}
					if (engCount == 0)
					{
							cout << students.at(count)->name << " has not passed an English course" << endl;
					}
					engCount = 0;
					secondCount = 0;



				count++;
			}
}
void deleteDyn(vector<Student*> students)
{
	vector<Student*>::iterator z;
			int x = 0;
			int y = 0;


			// for loop that displays all students and their grades
			for (z = students.begin(); z != students.end(); z++)
			{

				vector<Grade*>::iterator u;
				// if student has grades
				if (students.at(x)->grades.size() > 0)
				{
					for (u = students.at(x)->grades.begin() ; u!= students.at(x)->grades.end(); u++)
					{
							delete students.at(x)->grades.at(y);

										// increment grade vector position
							y++;
					}

							y = 0;

									// increment student vector position
							delete students.at(x);
							x++;
				}
			}
				//cout << "Dynamically allocated memory deleted!" << endl;
}
