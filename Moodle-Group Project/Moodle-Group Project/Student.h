#pragma once
#include <string>
#include "Main.h"

struct Student {
	int no; 
	std::string StudentID;
	std::string firstName, lastName;
	bool gender; // 0 is male; 1 is female.
	std::string dob; // date of birth.
	int socialID;
	std::string password = "123"; //hash string
	Nodecourse* list_enrolled_course = nullptr;
	int number_enrolled_course = 0;

	std::string Class;
	/*
	Student(int no, int StudentID, std::string firstName, std::string lastName, bool gender, std::string dob, int socialID, std::string password) {
		this->no = no;
		this->StudentID = StudentID;
		this->firstName = firstName;
		this->lastName = lastName;
		this->gender = gender;
		this->dob = dob;
		this->socialID = socialID;
		this->password = password;
	}
	*/


	Student* Login(Student* studentQuery, int& totalStudent);
	// this function will return the pointer to that student if login successfully, else it will return a nullptr if the pass or id is incorrect (so use this and make them repeat the login process)

	void changePassWord();
	void viewProfile();
	void viewCourses();
	void enroll_Course(Course& newcourse);
	void viewScoreboard();
};

void exportCSVToSave(Student* studentQuery, int& toltalStudent, std::string sourceFile);
//Use this function to save all student into a csv;
bool readExpoted(Student*& destination, int& toltalStudent, std::string sourceFile);
// this is quite similar with importCSVArray, but this is use to read the csv file saved by exportCSVArray, !! DO NOT USE THIS TO READ WHAT THE TEACHER GIVE !!
bool importCSVArray(Student*& destination, int& toltalStudent, std::string sourceFile);
//it will return false if file not found or there is no data in the file;||just put the address of the csv to the sourceFile. 
//do it like this: importData(students,n,"Moodle-Group Project\ImportStudent.csv")
//becareful, the function will create new, not add to existing array.
//   !! USE THIS TO READ WHAT THE TEACHER GIVE !!





