#pragma once
#include <string>
#include "Main.h"
#include "Scoreboard.h"

struct SchoolYear {
	std::string year;
};

struct semester {
	int no;
	std::string startDate, endDate;
	std::string schoolYear;
	//schoolYear year;

	//bool saveSemesterToFile(semester* newSemester);
};

struct Class {
	std::string name;

	//bool saveClassToFile(Class* newClass);
};

struct Course 
{
	std::string courseID;
	std::string courseName, className, teacherName;
	int nCredits;
	int maxStudents, totalStudent;
	std::string weekDate, session;
	// a CSV file of students in the course import
	NodeStudent* students = nullptr; // maximum 50

	semester sem;
	NodeScore* scores;
	
	void exportStudentToCSV(std::string fileName);
};


void createSchoolYear();
bool saveYearToFile(SchoolYear* newYear);
//void createSemester();
//bool saveSemesterToFile(semester* newSemester);
void create1stClasses();
bool saveClassToFile(Class* newClass);
void deleteCourse(Nodecourse* &courses, int& nCourses, Student* studentQuerry, int& totalStudent);

void add_Student_to_course(Nodecourse*& courses, int& nCourses, Student* studentQuerry, int& totalStudent);
void remove_student_from_course(Nodecourse*& courses, int& nCourses, Student* studentQuerry, int& totalStudent);
//use for saving courses to a csv file. use at the end of a program.
void saveAllCourses(Nodecourse*& course, int& totalCourse, std::string fileName);
//use to import courses from csv file (the same format with the saveCourse file). Use this at the start of a program!.
bool importCourse(Nodecourse*& course, int& totalCourse,Student* studentQuery, int totalStudent, std::string sourceFile);

void viewScoreboard_of_aCourse(Nodecourse*& courses);

void updateStudentResult(Student* studentQuery, int& totalStudent);
//make sure to ask user to input the filename, else it would break
void exportStudentFromCourseToCSV(Nodecourse*& courses,std::string& fileName,std::string& CourseID);
//please create scoreboard for the student you just imported, this function is right below this
bool importStudentCSVToCourse(NodeStudent*& studentList, int& toltalStudent, std::string sourceFile);
//here is the function to create the scoreboard for those students // the scores and student list is in the same course
//ex :createScoreBoard1Cousre(cs162.scores,cs162.studentList);
bool createScoreBoard1Cousre(NodeScore*& scores, NodeStudent*& studentList);

void addCoursetoSemester(Nodecourse*& courses, int& nCourses, semester* semesterQuery, int& nSemesters);