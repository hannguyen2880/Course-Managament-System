#include <iostream>
#include <string>

using namespace std;

#include "Student.h"
#include "Staff.h"
#include "Menu.h"

int main() {
	// import CSV files!
	int totalStudent = 0;
	Student* studentQuery = nullptr;
	readExpoted(studentQuery, totalStudent, "AllStudents.csv");

	int totalStaff = 0;
	Staff* staffQuery = nullptr;
	importStaffFromCSV(staffQuery, totalStaff, "staffInfo.csv");

	int nCourses = 0;
	Nodecourse* courses = nullptr;
	importCourse(courses, nCourses, studentQuery, totalStudent, "AllCourses.csv");
	Class* classes = new Class;
	int nClasses = 0;
	string* strclasses = nullptr;
	importCSVclasses(strclasses, nClasses);

	semester* semesterQuery = nullptr;
	int nSemesters = 0;
	if(!loadSemeterFromSave(semesterQuery,nSemesters))
		std::cout << "Something Wrong!";
	while (1) {
		cout << "Are you a student or an academic staff?\n";
		cout << "1. Student\n";
		cout << "2. Academic Staff\n";
		cout << "0. Exit\n";
		cout << "Your choice: "; int role; cin >> role;
		cout << "------------------------------\n";
		switch (role)
		{
		case 1:
		{
			Student_menu(studentQuery, totalStudent);
			break;
		}
		case 2:
		{
			Staff_menu(staffQuery, totalStaff, courses, nCourses, classes, strclasses, nClasses, studentQuery, totalStudent, semesterQuery, nSemesters);
			break;
		}
		case 0:
		{
			saveSemeter(semesterQuery, nSemesters);
			exportCSVToSave(studentQuery, totalStudent, "AllStudents.csv");
			exportStaffToCSV(staffQuery, totalStaff, "staffInfo.csv");
			saveAllCourses(courses, nCourses, "AllCourses.csv");
			return 0;
		}
		default:
			cout << "Invalid choice!\n";
			cout << "------------------------------\n";
			break;
		}
	}
	/*for (int i = 0; i < nSemesters; ++i) {
		cout << semesterQuery[i].schoolYear << "\n";
	}*/
	delete[] studentQuery;
	delete[] staffQuery;
	delete[] strclasses;
	delete classes;

	// delete All Courses
	deleteListCourse(courses);
}
