#include<string>
#include<fstream>
#include<sstream>

using namespace std;

#include "Main.h"
#include "Student.h"
#include "Course.h"
#include "Staff.h"
#include "Node.h"

struct StaffNode
{
	Staff data;
	StaffNode* next = nullptr;
};
void cleanUpStaff(StaffNode*& pHead)
{
	while (pHead != nullptr)
	{
		StaffNode* temp = pHead->next;
		delete pHead;
		pHead = temp;
	}
}
void cleanUp(NodeStudent*& pHead)
{
	while (pHead != nullptr)
	{
		NodeStudent* temp = pHead->pNext;
		delete pHead;
		pHead = temp;
	}
}
void parseCSV(NodeStudent*& head, int& n, ifstream& fin)
{
	NodeStudent* dummy = new NodeStudent;
	NodeStudent* cur = dummy;
	string line;
	getline(fin, line);//this line is here to remove the format header
	line = "";
	while (getline(fin, line))
	{
		cur->pNext = new NodeStudent;
		cur = cur->pNext;

		string temps;
		stringstream inputString(line);
		//no
		temps = "";
		getline(inputString, temps, ',');
		cur->data.no = atoi(temps.c_str());
		//studentID
		getline(inputString, cur->data.StudentID, ',');
		//firstName
		getline(inputString, cur->data.firstName, ',');
		//lastname
		getline(inputString, cur->data.lastName, ',');
		//gender
		temps = "";
		getline(inputString, temps, ',');
		if (temps[0] == '0')
			cur->data.gender = 0;
		else
			cur->data.gender = 1;
		//date of birth
		getline(inputString, cur->data.dob, ',');
		//socialID
		temps = "";
		getline(inputString, temps, ',');
		cur->data.socialID = atoi(temps.c_str());

		line = "";
		n++;
	}
	cur->pNext = nullptr;
	head = dummy->pNext;
	delete dummy;
}
bool importCSVArray(Student*& destination, int& toltalStudent, std::string sourceFile)
{
	ifstream fin;
	fin.open(sourceFile);
	if (!fin)
		return false;
	NodeStudent* head = nullptr;
	int i = 0;
	parseCSV(head, toltalStudent, fin);
	if (toltalStudent == 0)
		return false;
	destination = new Student[toltalStudent];
	NodeStudent* cur = head;
	for (int i = 0; i < toltalStudent; i++)
	{
		destination[i].no = cur->data.no;
		destination[i].StudentID = cur->data.StudentID;
		destination[i].firstName = cur->data.firstName;
		destination[i].lastName = cur->data.lastName;
		destination[i].gender = cur->data.gender;
		destination[i].dob = cur->data.dob;
		destination[i].socialID = cur->data.socialID;
		cur = cur->pNext;
	}
	cleanUp(head);
	fin.close();
	return true;
}
bool importStudentCSVToCourse(NodeStudent*& studentList, int& toltalStudent, std::string sourceFile)
{
	ifstream fin;
	fin.open(sourceFile);
	if (!fin)
		return false;
	NodeStudent* head = nullptr;
	int i = 0;
	parseCSV(head, toltalStudent, fin);
	studentList = head;
	return true;
}

void parseCSVStaff(StaffNode*& head, int& n, ifstream& fin)
{
	StaffNode* dummy = new StaffNode;
	StaffNode* cur = dummy;
	string line;
	getline(fin, line);//this line is here to remove the format header
	line = "";
	while (getline(fin, line))
	{
		cur->next = new StaffNode;
		cur = cur->next;

		string temps;
		stringstream inputString(line);

		getline(inputString, cur->data.name, ',');

		getline(inputString, cur->data.staffID, ',');

		getline(inputString, cur->data.username, ',');

		getline(inputString, cur->data.password, ',');

		line = "";
		n++;
	}
	cur->next = nullptr;
	head = dummy->next;
	delete dummy;
}
bool importStaffFromCSV(Staff*& staffQuery, int& totalStaff, std::string sourceFile)
{
	ifstream fin;
	fin.open(sourceFile);
	if (!fin)
		return false;
	StaffNode* head = nullptr;
	int i = 0;
	parseCSVStaff(head, totalStaff, fin);
	if (totalStaff == 0)
		return false;
	staffQuery = new Staff[totalStaff];
	StaffNode* cur = head;

	for (int i = 0; i < totalStaff; i++)
	{
		staffQuery[i].name = cur->data.name;
		staffQuery[i].staffID = cur->data.staffID;
		staffQuery[i].username = cur->data.username;
		staffQuery[i].password = cur->data.password;
		cur = cur->next;
	}
	cleanUpStaff(head);
	fin.close();
	return true;
}

bool importScoreBoard(Course& course, std::string fileName)
{
	ifstream fin;
	fin.open(fileName);
	if (!fin) return false;
	NodeScore* dummy = new NodeScore; 
	NodeScore* cur = dummy;
	string line;
	getline(fin, line);//this line is here to remove the format header
	line = "";
	while (getline(fin, line))
	{
		cur->pNext = new NodeScore;
		cur = cur->pNext;

		string temps;
		stringstream inputString(line);

		getline(inputString, cur->data.studentID, ',');
		getline(inputString, cur->data.studentFullName, ',');

		temps = "";
		getline(inputString, temps, ',');
		cur->data.totalMark = atof(temps.c_str());

		temps = "";
		getline(inputString, temps, ',');
		cur->data.finalMark = atof(temps.c_str());

		temps = "";
		getline(inputString, temps, ',');
		cur->data.midtermMark = atof(temps.c_str());

		temps = "";
		getline(inputString, temps, ',');
		cur->data.otherMark = atof(temps.c_str());
	}
	fin.close();
	cur->pNext = nullptr;
	course.scores = dummy->pNext;
	delete dummy;
	return true;
}

void import1Course(Course& course, std::string line, Student* studentQuery, int totalStudent)
 {
	string temps;
	stringstream inputString(line);

	getline(inputString,course.courseID, ',');
	getline(inputString, course.courseName, ',');
	getline(inputString, course.className, ',');
	getline(inputString, course.teacherName, ',');

	temps = "";
	getline(inputString, temps, ',');
	course.nCredits= atoi(temps.c_str());

	temps = "";
	getline(inputString, temps, ',');
	course.maxStudents = atoi(temps.c_str());

	getline(inputString, course.weekDate, ',');
	getline(inputString, course.session, ',');

	temps = "";
	getline(inputString, temps, ',');
	course.sem.no = atoi(temps.c_str());

	getline(inputString, course.sem.startDate, ',');
	getline(inputString, course.sem.endDate, ',');
	getline(inputString, course.sem.schoolYear, ',');
	
	temps = "";
	getline(inputString, temps, ',');
	course.totalStudent = atoi(temps.c_str());


	std::string scoreFile;
	getline(inputString, scoreFile, ',');
	importScoreBoard(course, scoreFile);


	NodeStudent* dummy = new NodeStudent;
	NodeStudent* cur = dummy;
	NodeScore* curScore = course.scores;

	for (int i = 0; i < course.totalStudent; i++)
	{
		cur->pNext = new NodeStudent;
		cur = cur->pNext;
		temps = curScore->data.studentID;
		curScore = curScore->pNext;

		for (int j = 0; j < totalStudent; j++)
		{
			if (temps == studentQuery[j].StudentID)
			{
				cur->data = studentQuery[i];
				studentQuery[j].enroll_Course(course);
				//studentQuery[j].number_enrolled_course++;
				break;
			}
		}

	}

	cur->pNext = nullptr;
	course.students = dummy->pNext;
	delete dummy;

}


bool importCourse(Nodecourse*& course, int& totalCourse, Student* studentQuery, int totalStudent,std::string sourceFile = "AllCourses.csv")
{
	ifstream fin;
	fin.open(sourceFile);
	if (!fin)
		return false;
	Nodecourse* dummy = new Nodecourse;
	Nodecourse* cur = dummy;
	string line;
	getline(fin, line);//this line is here to remove the format header
	line = "";
	while (getline(fin, line))
	{
		totalCourse++;
		cur->pNext = new Nodecourse;
		cur = cur->pNext;
		import1Course(cur->data, line, studentQuery, totalStudent);
	}
	fin.close();
	cur->pNext = nullptr;
	course = dummy->pNext;
	delete dummy;
	if (!course)
		return false;
	return true;
}

void importCSVclasses(std::string*& Classes, int& nClasses)
{
	ifstream fin;
	fin.open("classes.csv");
	if (!fin)
		return;
	string line;
	getline(fin, line);
	string temp;
	stringstream inputString(line);

	getline(inputString,temp, ',');
	nClasses = atoi(temp.c_str());
	Classes = new std::string[nClasses];
	for (int i = 0; i < nClasses; i++)
	{

		getline(inputString, Classes[i], ',');

	}
	fin.close();
}

bool createScoreBoard1Cousre(NodeScore*& scores, NodeStudent*& studentList)
{
	NodeStudent* stu = studentList;
	if (stu == nullptr)
		return false;
	NodeScore* dummy = new NodeScore;
	NodeScore* cur = dummy;
	int k = 1;
	while (stu != nullptr)
	{
		cur->pNext = new NodeScore;
		cur = cur->pNext;
		cur->data.no = k++;
		cur->data.studentID = stu->data.StudentID;
		cur->data.studentFullName = stu->data.lastName + " " + stu->data.firstName;
		cur->data.totalMark = 0;
		cur->data.finalMark = 0;
		cur->data.midtermMark = 0;
		cur->data.otherMark = 0;
		stu = stu->pNext;
	}
	scores = dummy->pNext;
	cur->pNext = nullptr;
	delete dummy;
	return true;
}

bool loadSemeterFromSave(semester*& semArrs, int& nSemesters)
{
	ifstream fin;
	fin.open("semeter.txt");
	if (!fin)
		return false;
	fin >> nSemesters;
	semArrs = new semester[nSemesters];
	for (int i = 0; i < nSemesters; i++)
	{
		//fin.getline();
		fin >> semArrs[i].no;
		fin >> semArrs[i].schoolYear;
		fin >> semArrs[i].startDate;
		fin >> semArrs[i].endDate;
	}
	return true;
}