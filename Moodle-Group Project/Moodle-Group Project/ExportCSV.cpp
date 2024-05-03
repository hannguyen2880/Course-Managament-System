#include<string>
#include<fstream>
#include<sstream>

using namespace std;

#include "Main.h"
#include "Student.h"
#include "Course.h"
#include "Staff.h"
#include "Node.h"

void cleanUpStudent(NodeStudent*& pHead)
{
	while (pHead != nullptr)
	{
		NodeStudent* temp = pHead->pNext;
		delete pHead;
		pHead = temp;
	}
}
void exportCSVToSave(Student* studentQuery, int& toltalStudent, std::string sourceFile = "AllStudents.csv")
{
	ofstream fout;
	fout.open(sourceFile);
	fout << "no,StudentID,firstName,lastName,gender,dob,socialID,Class,password";
	for (int i = 0; i < toltalStudent; i++)
	{
		fout << endl;
		fout << studentQuery[i].no << "," << studentQuery[i].StudentID << "," << studentQuery[i].firstName << ","
			<< studentQuery[i].lastName << "," << studentQuery[i].gender << "," << studentQuery[i].dob << ","
			<< studentQuery[i].socialID << "," << studentQuery[i].Class << "," << studentQuery[i].password;
	}
	fout.close();

}
void parseCSVSpecial(NodeStudent*& head, int& n, ifstream& fin)
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

		getline(inputString, cur->data.Class, ',');

		getline(inputString, cur->data.password, ',');
		line = "";
		n++;
	}
	cur->pNext = nullptr;
	head = dummy->pNext;
	delete dummy;
}
bool readExpoted(Student*& destination, int& toltalStudent, std::string sourceFile)
{
	ifstream fin;
	fin.open(sourceFile);
	if (!fin)
		return false;
	NodeStudent* head = nullptr;
	int i = 0;
	parseCSVSpecial(head, toltalStudent, fin);
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
		destination[i].Class = cur->data.Class;
		destination[i].password = cur->data.password;
		cur = cur->pNext;
	}
	cleanUpStudent(head);
	fin.close();
	return true;
}
void Course::exportStudentToCSV(std::string fileName)
{
	ofstream fout;
	fout.open(fileName);
	fout << "no,StudentID,firstName,lastName,gender,dob,socialID";
	NodeStudent* cur = students;
	for (int i = 0; i < totalStudent; i++)
	{
		fout << endl << i + 1 << "," << cur->data.StudentID << "," << cur->data.firstName << "," << cur->data.lastName << ","
			<< cur->data.gender << "," << cur->data.dob << "," << cur->data.socialID;
		cur = cur->pNext;
	}
	fout.close();
}
void exportStaffToCSV(Staff* staffQuery, int& totalStaff, std::string fileName)
{
	ofstream fout;
	fout.open(fileName);
	fout << "name,StaffID,username,password";
	for (int i = 0; i < totalStaff; i++)
	{
		fout << endl;
		fout << staffQuery[i].name << "," << staffQuery[i].staffID << "," << staffQuery[i].username << "," << staffQuery[i].password;
	}
	fout.close();
}
void saveStudentScore(Nodecourse*& course, std::string fileName)
{
	ofstream fout;
	fout.open(fileName);
	fout << "StudentID,StudentFullName,totalMark,finalMark,midtermMark,otherMark";
	NodeScore* Sco = course->data.scores;
	if (Sco == nullptr)
	{
		NodeStudent* Stu = course->data.students;
		for (int i = 0; i < course->data.totalStudent; i++)
			fout << endl << Stu->data.StudentID << "," << Stu->data.lastName << " " << Stu->data.firstName << "," << 0 << ","
			<< 0 << "," << 0 << "," << 0;
	}
	else
		for (int i = 0; i < course->data.totalStudent; i++)
		{

			fout << endl << Sco->data.studentID << "," << Sco->data.studentFullName << "," << Sco->data.totalMark << ","
				<< Sco->data.finalMark << "," << Sco->data.midtermMark << "," << Sco->data.otherMark;
			Sco = Sco->pNext;
		}
	fout.close();

}
void saveAllCourses(Nodecourse*& course, int& totalCourse, std::string fileName = "AllCourses.csv")
{
	ofstream fout;
	fout.open(fileName);
	fout << "ID,name,className,teacher,credits,maxStudent,WeekDate,Sess,Semester,SemStart,SemEnd,SchoolYear,totalStudent,StudentDataFile";
	Nodecourse* cur = course;
	for (int i = 0; i < totalCourse; i++)
	{
		fout << endl << cur->data.courseID << "," << cur->data.courseName << "," << cur->data.className << "," << cur->data.teacherName << "," << cur->data.nCredits
			<< "," << cur->data.maxStudents << "," << cur->data.weekDate << "," << cur->data.session << "," << cur->data.sem.no << "," << cur->data.sem.startDate
			<< "," << cur->data.sem.endDate << "," << cur->data.sem.schoolYear << "," << cur->data.totalStudent;

		string fname = cur->data.courseID + "-" + char(cur->data.sem.no + 48) + "-" + cur->data.sem.schoolYear + ".csv";
		saveStudentScore(cur, fname);
		fout << "," << fname;
		cur = cur->pNext;
	}
	fout.close();
}

void exportCSVclasses(std::string* Classes, int nClasses)
{
	ofstream fout;
	fout.open("classes.csv");
	fout << nClasses;
	for (int i = 0; i < nClasses; i++)
		fout << "," << Classes[i];
	fout.close();
}
void exportStudentFromCourseToCSV(Nodecourse*& courses, std::string& fileName, std::string& CourseID)
{
	ofstream fout(fileName);
	fout.close();
	fout.open(fileName);
/*	if (!fout.is_open())
	{
		std::cout << "File not found!\n";
		return;
	}
*/
	Nodecourse* cur = nullptr;
	Nodecourse* courseCur = courses;

	while (courseCur != nullptr)
	{
		if (courseCur->data.courseID == CourseID)
		{
			cur = courseCur;
			break;
		}
		courseCur = courseCur->pNext;
	}

	if (cur == nullptr)
	{
		std::cout << "No such course found!\n";
		return;
	}

	NodeScore* students = cur->data.scores;
	fout << "StudentID,StudentFullName,totalMark,finalMark,midtermMark,otherMark";
	int i = 1;
	while (students != NULL)
	{
		fout << std::endl << students->data.studentID << "," << students->data.studentFullName << "," << students->data.totalMark << "," << students->data.finalMark
			<< "," << students->data.midtermMark << "," << students->data.otherMark;
		students = students->pNext;
	}

	std::cout << "Exported successfully!\n";
	fout.close();
}
bool saveSemeter(semester*& semArrs, int& nSemesters)
{
	ofstream fout;
	fout.open("semeter.csv");
	if (!fout)
		return false;
	fout << nSemesters;
	for (int i = 0; i < nSemesters; i++)
		fout << endl << semArrs[i].no << " " << semArrs[i].schoolYear << " " << semArrs[i].startDate << " " << semArrs[i].endDate;
	fout.close();
	return true;
}