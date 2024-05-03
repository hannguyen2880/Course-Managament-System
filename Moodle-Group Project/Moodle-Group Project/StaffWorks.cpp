#include <iostream>
#include <fstream>
#include "Implement.h"
#include "Course.h"
#include "Node.h"
#include "Staff.h"

//void createSchoolYear() {
//	SchoolYear* newYear = new SchoolYear;
//	std::cout << "Start year - End year: ";
//	std::cin.ignore();
//	getline(std::cin, newYear->year);
//	if (saveYearToFile(newYear)) std::cout << "Saved successfully!\n";
//}
bool saveYearToFile(SchoolYear* newYear) {
	std::ofstream fout;
	fout.open("SchoolYears.csv", std::ios::app);
	if (!fout)
		return false;
	fout << newYear->year << ", ";
	fout.close();
	delete newYear;
	return true;
}


//void createSemester() {
//	semester* newSemester = new semester;
//	std::cout << "Semester number:";
//	std::cin >> newSemester->no;
//	std::cout << "Start date:";
//	std::cin >> newSemester->startDate;
//	std::cout << "End date:";
//	std::cin >> newSemester->endDate;
//	std::cout << "School year:";
//	saveSemesterToFile(newSemester);
//}

/*bool saveSemesterToFile(semester* newSemester) {
	std::ofstream fout;
	fout.open("Semesters.csv", std::ios::app);
	if (!fout)	return false;
	fout << newSemester->no << ", ";
	fout << newSemester->startDate << ", ";
	fout << newSemester->endDate << ", ";
	fout.close();
	delete newSemester;
	return true;
}*/


void create1stClasses() {
	Class* newClass = new Class;
	std::cout << "Name:";
	std::cin >> newClass->name;
	saveClassToFile(newClass);
}
bool saveClassToFile(Class* newClass) {
	std::ofstream fout;
	fout.open("Classes.csv", std::ios::app);
	if (!fout)
		return false;
	fout << newClass->name << ", ";
	fout.close();
	delete newClass;
	return true;
}

void add_Student_to_course(Nodecourse*& courses, int& nCourses, Student* studentQuery, int& totalStudent)
{
	std::string inputCourseID;
	std::string inputStudentID;
	int student_index;
	Nodecourse* course = nullptr;

	// find the course
	std::cout << "Enter course ID: ";
	std::cin >> inputCourseID;
	bool found = false;
	Nodecourse* cur = courses;
	while (cur)
	{
		if (cur->data.courseID == inputCourseID)
		{
			found = true;
			course = cur;
			break;
		}
		cur = cur->pNext;
	}

	if (!found)
	{
		std::cout << "Cannot find that course.\n";
		return;
	}

	// find the student
	std::cout << "Enter student ID to add to course: ";
	std::cin >> inputStudentID;
	found = false;
	for (int i = 0; i < totalStudent; ++i)
	{
		if (studentQuery[i].StudentID == inputStudentID)
		{
			found = true;
			student_index = i;
			break;
		}
	}

	if (!found)
	{
		std::cout << "Cannot find that student.\n";
		return;
	}

	AddStudentAtBeginning(course->data.students, studentQuery[student_index], course->data.totalStudent, course->data.scores);
	studentQuery[student_index].enroll_Course(course->data);
}

void remove_student_from_course(Nodecourse*& courses, int& nCourses, Student* studentQuery, int& totalStudent)
{
	std::string inputCourseID;
	std::string inputStudentID;
	std::cout << "Enter student ID: ";
	std::cin >> inputStudentID;
	std::cout << "Enter course ID: ";
	std::cin >> inputCourseID;

	//Student* student;
	//Course* course;
	int x = 0;
	bool found = false;
	for (int i = 0; i < totalStudent; ++i) {
		if (studentQuery[i].StudentID == inputStudentID) {
			found = true;
			x = i;
			break;
		}
	}
	if (!found) {
		std::cout << "Cannot find that student.\n";
		return;
	}
	found = false;
	Nodecourse* cur = courses;
	while (cur) {
		if (cur->data.courseID == inputCourseID) {
			found = true;
			break;
		}
		cur = cur->pNext;
	}
	if (!found) {
		std::cout << "Cannot find that course.\n";
		return;
	}
	//
	remove_a_Studentnode(cur->data.students, studentQuery[x], cur->data.totalStudent);
	
	//
	NodeScore* tmp = cur->data.scores;
	if (tmp->data.studentID == inputStudentID) {
		NodeScore* tmp2 = tmp;
		tmp = tmp->pNext;
		delete tmp2;
		cur->data.scores = tmp;
	}
	else while (tmp) {
		if (tmp->data.studentID == inputStudentID) {
			NodeScore* tmp2 = tmp;
			tmp = tmp->pNext;
			delete tmp2;
			break;
		}
		tmp = tmp->pNext;
	}

	//
	RemoveNodeCourse(studentQuery[x].list_enrolled_course, cur->data, studentQuery[x].number_enrolled_course);
	std::cout << "Removing successfully" << std::endl;
}

void deleteCourse(Nodecourse*& courses, int& nCourses, Student* studentQuery, int& totalStudent)
{
	std::cout << "Enter course ID you want to delete: ";
	std::string inputCourseID;
	std:: cin >> inputCourseID;
	Nodecourse* cur = courses;

	if (!cur)
	{
		std::cout << "No such course found\n";
		return;
	}
	while (cur != nullptr)
	{
		if (cur->data.courseID == inputCourseID)
		{
			deleteListStudent(cur->data.students);
			deleteListScore(cur->data.scores);
			deleteCourseFromStudentArr(studentQuery, totalStudent, cur->data);
			RemoveNodeCourse(courses, cur->data, nCourses);
			std::cout << "Deleted successfully!\n";
			return;
		}
		cur = cur->pNext;
	}
	std::cout << "No such course found\n";
	
}

void viewScoreboard_of_aCourse(Nodecourse*& courses) {
	std::cout << "Enter the course ID you want to view the scoreboard: ";
	std::string inputCourseID;
	std::cin >> inputCourseID;
	
	Nodecourse* cur = courses;

	while (cur != nullptr)
	{
		if (cur->data.courseID == inputCourseID)
		{
			break;
		}
		cur = cur->pNext;
	}

	if (!cur) 
	{
		std::cout << "No such course found\n";
		return;
	}

	NodeScore* scoreCur = cur->data.scores;
	// return if there is no scoreboard in the course
	if (scoreCur == nullptr)
	{
		std::cout << "No student to show\n";
		return;
	}

	std::cout << "The scoreboard of this course is: \n";
	while (scoreCur != nullptr)
	{
		scoreboard board = scoreCur->data;

		
		std::cout << "Student ID: " << board.studentID << "\n";
		std::cout << "Full name: " << board.studentFullName << "\n";
		std::cout << "Total Mark: " << board.totalMark << "\n";
		std::cout << "Midterm Mark: " << board.midtermMark << "\n";
		std::cout << "Final Mark: " << board.finalMark << "\n";
		std::cout << "Other Mark: " << board.otherMark << "\n";
		std::cout << "-----\n";

		scoreCur = scoreCur->pNext;
	}
	return;
}

void updateStudentResult(Student* studentQuery, int& totalStudent) {
	bool found_course = false;
	std::cout << "Input the ID of course you want to change the result: ";
	std::string inputCourseID;
	std::cin >> inputCourseID;
	std::cout << "Input student ID of the student that you want to update the result: ";
	std::string inputID;
	std::cin >> inputID;
	Student student;
	for (int i = 0; i < totalStudent; ++i) {
		if (studentQuery[i].StudentID == inputID) {
			student = studentQuery[i];
			break;
		}
	}
	Nodecourse* cur = student.list_enrolled_course;

	if (!cur) {
		std::cout << "No such student found\n";
		return;
	}
	while (cur != nullptr)
	{
		if (cur->data.courseID == inputCourseID)
		{
			found_course = true;
			break;
		}
		cur = cur->pNext;
	}

	if (!found_course) {
		std::cout << "No such course found!\n";
		return;
	}

	std::cout << "Press:\n";
	std::cout << "1. If you want to change the final mark.\n";
	std::cout << "2. If you want to change the midterm mark.\n";
	std::cout << "3. If you want to change the other mark.\n";
	std::cout << "Or you can press 0 when completing changing.\n";
	std::cout << "What's your choice?: ";
	int choice;
	std::cin >> choice;

	NodeScore* curSco = cur->data.scores;
	while (curSco != NULL) {
		if (curSco->data.studentID == inputID) break;
		curSco = curSco->pNext;
	}

	while (true) {
		if (choice == 0) return;
		while (choice > 3 || choice < 0) {
			std::cout << "Choose your choice again: ";
			std::cin >> choice;
		}
		switch (choice)
		{
		case 1: {
			std::cout << "What's new final mark?: ";
			std::cin >> curSco->data.finalMark;
			break;
		}
		case 2: {
			std::cout << "What's new midterm mark?: ";
			std::cin >> curSco->data.midtermMark;
			break;
		}
		case 3: {
			std::cout << "What's new other mark?: ";
			std::cin >> curSco->data.otherMark;
			break;
		}
		default:
			break;
		}
		std::cout << "What's your next choice?: ";
		std::cin >> choice;
	}
}

void createSchoolYear() {
	std::string schoolyear;
	std::cout << "Enter a school year you want to create ('start year'-'end year')";
	std::cout << "\nFor example: '2022-2023'\n";
	std::cout << "School year: ";
	std::cin.ignore();
	getline(std::cin, schoolyear);
	//std::cin >> schoolyear;
	std::cout << "Created successfully!\n";
}

void createSemester(semester*& semArrs, int& nSemesters, semester& sem) {
	std::cout << "Which school year does this semester belong to (yyyy-yyyy): ";
	std::cin >> sem.schoolYear;

	std::cout << "Enter the semester you want to build (1,2 or 3): ";
	std::cin >> sem.no;	

	std::cout << "Enter starting date of this semester (dd/mm/yyyy): ";
	std::cin >> sem.startDate;

	std::cout << "Enter end date of this semester (dd/mm/yyyy): ";
	std::cin >> sem.endDate;
	if (nSemesters == 0) {
		semArrs = new semester[1];
		++nSemesters;
		semArrs[0] = sem;
	}
	else {
		++nSemesters;
		semester* tmpArrs = new semester[nSemesters];
		for (int i = 0; i < nSemesters - 1; ++i) {
			tmpArrs[i] = semArrs[i];
		}
		
		tmpArrs[nSemesters - 1] = sem;
		delete[] semArrs;
		semArrs = new semester[nSemesters];
		
		for (int i = 0; i < nSemesters; ++i) {
			semArrs[i] = tmpArrs[i];
		}
		delete[] tmpArrs;
	}
	std::cout << "Created successfully!\n";
}

bool searchcourse(Nodecourse* courses, Course*& temp, std::string CourseID)
{
	Nodecourse* courseCur = courses;
	while (courseCur != nullptr)
	{
		if (courseCur->data.courseID == CourseID) {
			temp = &(courseCur->data);
			return 1;
		}
		courseCur = courseCur->pNext;
	}

	if (courseCur == nullptr) return 0;

}

void inputCourse(Course& course) {
	std::cout << "Enter course ID: ";
	std::cin.ignore();
	std::getline(std::cin, course.courseID);

	std::cout << "Enter course name: ";
	std::getline(std::cin, course.courseName);

	std::cout << "Enter class name: ";
	std::getline(std::cin, course.className);

	std::cout << "Enter teacher name: ";
	std::getline(std::cin, course.teacherName);

	std::cout << "Enter number of credits: ";
	std::cin >> course.nCredits;

	std::cout << "Enter maximum number of students in the course: ";
	std::cin >> course.maxStudents;

	std::cout << "Enter day of the week (MON / TUE / WED / THU / FRI / SAT): ";
	std::cin.ignore();
	std::getline(std::cin, course.weekDate);

	std::cout << "Enter the session that the course will be ped S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30): ";
	std::getline(std::cin, course.session);
}

void addCoursetoSemester(Nodecourse*& courses, int& nCourses, semester* semesterQuery, int& nSemesters) {
	Course course;
	inputCourse(course);
	semester sem;
	std::cout << "Enter school year of the semester (yyyy-yyyy): ";
	std::string schoolyear;
	std::cin >> schoolyear;
	std::cout << "Enter the semester (1, 2 or 3): ";
	int no;
	std::cin >> no;
	bool found = false;
	for (int i = 0; i < nSemesters; ++i) {
		if (semesterQuery[i].no == no && semesterQuery[i].schoolYear == schoolyear) {
			course.sem = semesterQuery[i];
			found = true;
			break;
		}
	}
	if (!found) {
		std::cout << "Cannot find that semester!\n";
		return;
	}
	// initialize the list of score as null
	course.scores = nullptr;
	AddNodeCourseAtBeginning(courses, course, nCourses);
	std::cout << "Adding successfully!\n";

	std::cout << "-----Upload enrolled students file-----\n";
	std::cout << "Please enter the name of the source file: ";
	std::string sourceFile; std::cin.ignore(); std::getline(std::cin, sourceFile);

	if (importStudentCSVToCourse(course.students, course.totalStudent, sourceFile)) std::cout << "Uploading successfully!\n";
	else std::cout << "Uploading unsuccessfully!\n";

	if (createScoreBoard1Cousre(course.scores, course.students)) std::cout << "The scoreboard of the course was generated!\n";
	else std::cout << "Something wrong with the program! Please contact your service provider!\n";
}
