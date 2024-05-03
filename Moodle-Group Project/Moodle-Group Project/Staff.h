#pragma once
#include <string>
#include "Main.h"
#include "Course.h"

struct schoolYear;
struct semester;
struct Class;

struct Staff {
	std::string name, username;
	std::string staffID;
	std::string password;

	/*
	Staff(std::string name, std::string username, int staffID, std::string password) {
		this->name = name;
		this->username = username;
		this->staffID = staffID;
		this->password = password;
	}
	*/

	Staff* Login(Staff* staffQuery, int& totalStaff);
	// staffQuery is the array that contain the staffs, totalStaff is the total staffs in that array
	// this function will return the pointer to that Staff if login successfully,
	// else it will return a nullptr if the pass or username is incorrect (so use this and make them repeat the login process)

	void changePassWord();
	void viewProfile();
	void createClasses(std::string*& classes, int& nClasses);
	void updateCourseInfo(Nodecourse*& courses);

	// viewing functions of Staff structures
	void viewListOfCourses(Nodecourse* courses);
	void viewListOfStudentsInCourse(Nodecourse* courses); 
	void viewListOfClasses(Student* studentQuery, int& nStudents);
	void viewListOfStudentsInClass(Student* studentQuery, int& nStudents);

	// viewing scoreboard in Staff
	void viewScoreboardOfClass(Student* studentQuery, int& totalStudent);
};
void importCSVclasses(std::string*& Classes, int& nClasses);
void exportCSVclasses(std::string* Classes, int nClasses);
bool importScoreBoard(Course& cur, std::string fileName);
bool importStaffFromCSV(Staff*& staffQuery, int& totalStaff, std::string sourceFile);
void exportStaffToCSV(Staff* staffQuery, int& totalStaff, std::string fileName);
bool addStudentToClass(std::string* classes, int nClasses, Student*& studentQuery, int& totalStudent);
//
void createSchoolYear(void);
void createSemester(semester*& semArrs, int& nSemesters, semester& sem);
bool searchcourse(Nodecourse* courses, Course*& temp, std::string CourseID);
bool saveSemeter(semester*& semArrs, int& nSemesters);
bool loadSemeterFromSave(semester*& semArrs, int& nSemesters);