#include <iostream>
#include "Menu.h"

using namespace std;

void Student_menu(Student*& studentQuery, int& totalStudent) {
	cout << "Login to your account\n";
	Student* user = NULL;
	user = user->Login(studentQuery, totalStudent);
	while (user == NULL) {
		cout << "------------------------------\n";
		cout << "1. Login again\n";
		cout << "0. Back\n";
		cout << "Your choice: "; int login_again; cin >> login_again;
		cout << "------------------------------\n";
		while (login_again != 0 && login_again != 1) {
			cout << "Invalid choice!\n";
			cout << "Your choice: ";  cin >> login_again;
			cout << "------------------------------\n";
		}
		if (login_again == 1) user = user->Login(studentQuery, totalStudent);
		else return;
	}
	while (1) {
		cout << "------------------------------\n";
		cout << "1. View profile\n";
		cout << "2. View course\n";
		cout << "3. View scoreboard\n";
		cout << "4. Change password\n";
		cout << "0. Log out\n";
		cout << "Your choice: "; int action; cin >> action;
		cout << "------------------------------\n";
		switch (action)
		{
		case 1:
		{
			user->viewProfile();
			cout << "------------------------------\n";
			break;
		}
		case 2:
		{
			user->viewCourses();
			cout << "------------------------------\n";
			break;
		}
		case 3:
		{
			user->viewScoreboard();
			cout << "------------------------------\n";
			break;
		}
		case 4:
		{
			user->changePassWord();
			cout << "------------------------------\n";
			break;
		}
		case 0:
			return;
		default:
		{
			cout << "Invalid choice!\n";
			cout << "------------------------------\n";
			break;
		}
		}
	}
}
void Staff_menu(Staff*& staffQuery, int& totalStaff, Nodecourse*& courses, int& nCourses, Class*& classes, string*& strclasses, int& nClasses, Student*& studentQuery, int& nStudents, semester*& semesterQuery, int& nSemesters) {
	cout << "Login to your account\n";
	Staff* user = NULL;
	user = user->Login(staffQuery, totalStaff);
	while (user == NULL) {
		cout << "------------------------------\n";
		cout << "1. Login again\n";
		cout << "0. Back\n";
		cout << "Your choice: "; int login_again; cin >> login_again;
		cout << "------------------------------\n";
		while (login_again != 0 && login_again != 1) {
			cout << "Invalid choice!\n";
			cout << "Your choice: "; cin >> login_again;
			cout << "------------------------------\n";
		}
		if (login_again == 1) user = user->Login(staffQuery, totalStaff);
		else return;
	}
	while (1) {
		cout << "------------------------------\n";
		cout << "1. View profile\n";
		cout << "2. Work site\n";
		cout << "3. View list\n";
		cout << "4. Change password\n";
		cout << "0. Log out\n";
		cout << "Your choice: "; int action; cin >> action;
		cout << "------------------------------\n";
		switch (action)
		{
		case 1:
		{
			user->viewProfile();
			cout << "------------------------------\n";
			break;
		}
		case 2:
		{
			bool run = 1;
			while (run) {
				cout << "1. Create a school year\n";
				cout << "2. Create a semester\n";
				cout << "3. Create classes\n";
				cout << "4. Add students to class\n";
				cout << "5. Update course's information\n";
				cout << "6. Add a student to a course\n";
				cout << "7. Remove a student from a course\n";
				cout << "8. Remove a course\n";
				cout << "9. Update students result\n";
				cout << "10. Add a course to a semester\n";
				cout << "11. Export students from a course to CSV file\n";
				cout << "12. Import scoreboard to a course\n";
				cout << "0. Back\n";
				cout << "Your choice: "; int yc2; cin >> yc2;
				cout << "------------------------------\n";
				switch (yc2)
				{
				case 1:
				{
					createSchoolYear();
					cout << "------------------------------\n";
					break;
				}
				case 2:
				{
					semester sem;
					createSemester(semesterQuery, nSemesters, sem);
					cout << "------------------------------\n";
					break;
				}
				case 3:
				{
					user->createClasses(strclasses, nClasses);
					cout << "------------------------------\n";
					break;
				}
				case 4:
				{
					addStudentToClass(strclasses, nClasses, studentQuery, nStudents);
					cout << "------------------------------\n";
					break;
				}
				case 5:
				{
					user->updateCourseInfo(courses);
					cout << "------------------------------\n";
					break;
				}
				case 6:
				{
					add_Student_to_course(courses, nCourses, studentQuery, nStudents);
					cout << "------------------------------\n";
					break;
				}
				case 7:
				{
					remove_student_from_course(courses, nCourses, studentQuery, nStudents);
					cout << "------------------------------\n";
					break;
				}
				case 8:
				{
					deleteCourse(courses, nCourses, studentQuery, nStudents);
					cout << "------------------------------\n";
					break;
				}
				case 9:
				{
					updateStudentResult(studentQuery, nStudents);
					cout << "------------------------------\n";
					break;
				}
				case 10:
				{
					addCoursetoSemester(courses, nCourses, semesterQuery, nSemesters);
					cout << "------------------------------\n";
					break;
				}
				case 11:
				{
					string filename, CourseID;
					cin.ignore(1000, '\n');
					cout << "Please enter the course's ID: "; getline(cin, CourseID);
					cout << "Please enter the filename: "; getline(cin, filename);
					exportStudentFromCourseToCSV(courses, filename, CourseID);
					cout << "------------------------------\n";
					break;
				}
				case 12:
				{
					cin.ignore(1000, '\n');
					cout << "Please enter the courseID: "; string CourseID; getline(cin, CourseID);
					Course* temp;
					if (!searchcourse(courses, temp, CourseID)) {
						cout << "Course not found!\n";
						break;
					}
					cout << "Please enter the filename: "; string filename; getline(cin, filename);
					importScoreBoard(*temp, filename);
					cout << "Importing successfully!\n";
					cout << "------------------------------\n";
					break;
				}
				case 0:
					run = 0;
					break;
				default:
				{
					cout << "Invalid choice!\n";
					cout << "------------------------------\n";
					break;
				}
				}
			}
			break;
		}
		case 3:
		{
			bool run = 1;
			while (run) {
				cout << "1. View list of courses\n";
				cout << "2. View list of classes\n";
				cout << "3. View list of students in a course\n";
				cout << "4. View list of students in a class\n";
				cout << "5. View list of scoreboard of a class\n";
				cout << "6. View scoreboard of a course\n";
				cout << "0. Back\n";
				cout << "Your choice: "; int yc2; cin >> yc2;
				cout << "------------------------------\n";
				switch (yc2)
				{
				case 1:
				{
					user->viewListOfCourses(courses);
					cout << "------------------------------\n";
					break;
				}
				case 2:
				{
					user->viewListOfClasses(studentQuery, nStudents);
					cout << "------------------------------\n";
					break;
				}
				case 3:
				{
					user->viewListOfStudentsInCourse(courses);
					cout << "------------------------------\n";
					break;
				}
				case 4:
				{
					user->viewListOfStudentsInClass(studentQuery, nStudents);
					cout << "------------------------------\n";
					break;
				}
				case 5:
				{
					user->viewScoreboardOfClass(studentQuery, nStudents);
					cout << "------------------------------\n";
					break;
				}
				case 6:
				{
					viewScoreboard_of_aCourse(courses);
					cout << "------------------------------\n";
					break;
				}
				case 0:
					run = 0;
					break;
				default:
				{
					cout << "Invalid choice!\n";
					cout << "------------------------------\n";
					break;
				}
				}
			}
			break;
		}
		case 4:
		{
			user->changePassWord();
			break;
		}
		case 0:
			return;
		default:
			break;
		}
	}
}
