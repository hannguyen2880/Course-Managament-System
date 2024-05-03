#pragma warning(disable:6385)
#include <iostream>
#include <vector>
#include "Staff.h"
#include "Node.h"

Staff* Staff::Login(Staff* staffQuery, int& totalStaff) {
	//Staff stf = Staff("Nguyen Huu Nha", "ongthanvatly", 123, "123");
	std::cout << "Username: ";
	std::string username;
	std::cin.ignore();
	std::getline(std::cin, username);
	std::cout << "Password: ";
	std::string password;
	std::getline(std::cin, password);
	for (int i = 0; i < totalStaff; i++)
	{
		if (staffQuery[i].username == username && staffQuery[i].password == password)
		{
			std::cout << "Login Successfully\n";
			return &staffQuery[i];
		}
	}
	std::cout << "Username or Password is incorrect\n";
	return NULL;
}

void Staff::changePassWord() 
{
	// Enter old password
	std::cin.ignore();
	std::cout << "Enter old password: ";
	std::string oldPass;
	std::cin >> oldPass;

	// Check if old password is correct
	while (1)
	{
		if (oldPass == password)
		{
			std::cin.ignore();
			std::cout << "Type in new password: ";
			std::string password1;
			std::cin >> password1;
			std::cin.ignore();
			std::cout << "Confirm password: ";
			std::string password2;
			std::cin >> password2;
			int res = password1.compare(password2);

			if (res == 0)
			{
				password = password1;
				std::cout << "Password changed!\n";
			}
			else
			{
				std::cout << "Confirm password incorrect!\n";
				std::cout << "------------------------------\n";
			}
			break;
		}
		else
		{
			std::cin.ignore(); 
			std::cout << "Wrong password! Type again (type 0 to exit): ";
			std::cin >> oldPass;
			// control the loop
			if (oldPass == "0") break;
		}
	}

	return;
}

void Staff::viewProfile() 
{
	std::cout << "Here's your profile\n";
	std::cout << "Staff ID: " << staffID << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Username: " << username << std::endl;
	// should not show password
	return;
}

void Staff::createClasses(std::string*& classes, int& nClasses)
{
	//importCSVclasses(classes, nClasses);
	std::cout << "How many classes do you want to create?: ";
	int num_of_classes; std::cin >> num_of_classes;
	nClasses += num_of_classes;
	std::string* temp_classes = new std::string[nClasses];
	for (int i = 0; i < nClasses - num_of_classes; i++) {
		temp_classes[i] = classes[i];
	}
	std::cout << "Input name of those classes:\n";
	for (int i = 0; i < num_of_classes; i++) {
		std::cin >> temp_classes[i + nClasses - num_of_classes];
	}
	exportCSVclasses(temp_classes, nClasses);
	delete[] classes;
	classes = temp_classes;
	std::cout << "Create successfully!\n";
}

void Staff::viewListOfCourses(Nodecourse* courses) 
{
	std::cout << "The list of courses in our program is:\n";
	Nodecourse* cur = courses;
	while (cur != NULL) {
		std::cout << cur->data.courseName << std::endl;
		cur = cur->pNext;
	}
}

void Staff::viewListOfStudentsInCourse(Nodecourse* courses)
{
	std::cout << "Enter the course ID you want to view: ";
	std::string inputCourseID;
	//std::cin.ignore();
	std::cin >> inputCourseID;

	Nodecourse* cur = nullptr;
	Nodecourse* courseCur = courses;

	while (courses != NULL)
	{
		if (courses->data.courseID == inputCourseID)
		{
			cur = courses;
			break;
		}
		courses = courses->pNext;
	}

	if (cur == NULL) 
	{
		std::cout << "No such course found!\n";
		return;
	}

	NodeStudent* students = cur->data.students;

	while (students != NULL) 
	{
		std::cout << students->data.StudentID << " " << students->data.firstName << " " << students->data.lastName << std::endl;
		students = students->pNext;
	}
}

void Staff::viewListOfClasses(Student* studentQuery, int& nStudents)
{
	std::vector<std::string> classes;
	classes.push_back(studentQuery[0].Class);

	std::cout << "Here is the list of classes\n";

	for (int i = 0; i < nStudents; i++)
	{
		for (int j = 0; j < classes.size(); j++)
		{
			if (classes[j] == studentQuery[i].Class) break;
			if (j == classes.size() - 1)
			{
				classes.push_back(studentQuery[i].Class);
				break;
			}
		}
	}

	for (std::string i : classes)
	{
		std::cout << i << std::endl;
	}
	
}

void Staff::viewListOfStudentsInClass(Student* studentQuery, int& nStudents) {
	std::cout << "Enter the classname: ";
	std::string Class; std::cin >> Class;

	bool found = false;
	for (int i = 0; i < nStudents; ++i) 
	{
		if (studentQuery[i].Class == Class)
		{
			if (!found) 
			{
				found = true;
				std::cout << "List of Students in this class is:\n";
			}
			std::cout << "ID: " << studentQuery[i].StudentID << ". Full name: ";
			std::cout << studentQuery[i].firstName << " " << studentQuery[i].lastName << "\n";
		}
	}
	if (!found) std::cout << "No such class found.\n";
}

void Staff::updateCourseInfo(Nodecourse*& courses) {
	std::cout << "Enter the course ID you want to update: ";
	std::string inputCourseID;
	std::cin.ignore();
	getline(std::cin, inputCourseID);
	Nodecourse* cur = courses;
	while (cur != NULL) {
		if (cur->data.courseID == inputCourseID) {
			break;
		}
		cur = cur->pNext;
	}
	if (cur == NULL) {
		std::cout << "No such course found!\n";
		return;
	}
	while (true) {
		std::cout << "What do you want to update?\n";
		std::cout << "1. Course ID\n";
		std::cout << "2. Course Name\n";
		std::cout << "3. Class name\n";
		std::cout << "4. Teacher name\n";
		std::cout << "5. The number of credits\n";
		std::cout << "6. Max students in this course\n";
		std::cout << "7. Day in the week of the course\n";
		std::cout << "8. The session that the course will be performed\n";
		std::cout << "0. Back\n";
		std::cout << "Your choice: ";
		int choice; std::cin >> choice;
		std::cout << "------------------------------\n";

		switch (choice)
		{
		case 1: 
		{
			std::cout << "Input the course ID you want to update: ";
			std::cin.ignore();
			getline(std::cin, cur->data.courseID);
			std::cout << "Updating successfully!\n";
			std::cout << "------------------------------\n";
			break;
		}
		case 2:
		{
			std::cout << "Input new course name: ";
			std::cin.ignore();
			getline(std::cin, cur->data.courseName);
			std::cout << "Updating successfully!\n";
			std::cout << "------------------------------\n";
			break;
		}
		case 3: 
		{
			std::cout << "Input new class name: ";
			std::cin.ignore();
			getline(std::cin, cur->data.className);
			std::cout << "Updating successfully!\n";
			std::cout << "------------------------------\n";
			break;
		}
		case 4: 
		{
			std::cout << "Input new teacher's name: ";
			std::cin.ignore();
			getline(std::cin,cur->data.teacherName);
			std::cout << "Updating successfully!\n";
			std::cout << "------------------------------\n";
			break;
		}
		case 6:
		{
			std::cout << "Input new maxStudents in this course: ";
			int newMax;
			std::cin >> newMax;
			if (cur->data.totalStudent <= newMax) cur->data.maxStudents = newMax;
			else std::cout << "Cannot update this information. The current total students in this course is bigger than your value you input";
			std::cout << "Updating successfully!\n";
			std::cout << "------------------------------\n";
			break;
		}
		case 5: 
		{
			std::cout << "Input new number of credits: ";
			std::cin >> cur->data.nCredits;
			std::cout << "Updating successfully!\n";
			std::cout << "------------------------------\n";
			break;
		}
		case 7: 
		{
			std::cout << "Input new day in the week of the course: ";
			std::cin.ignore();
			getline(std::cin, cur->data.weekDate);
			std::cout << "Updating successfully!\n";
			std::cout << "------------------------------\n";
			break;
		}
		case 8: 
		{
			std::cout << "Input new session that the course will be held: ";
			std::cin.ignore();
			getline(std::cin, cur->data.session);
			std::cout << "Updating successfully!\n";
			std::cout << "------------------------------\n";
			break;
		}
		case 0:
		{
			return;
		}
		default:
		{
			std::cout << "Invalid choice!\n";
			std::cout << "------------------------------\n";
			break;
		}
		}
	}
}

void Staff::viewScoreboardOfClass(Student* studentQuery, int& totalStudent)
{
	std::cout << "Enter the name of class you want view scoreboard: ";
	std::string inputClass;
	std::cin >> inputClass;

	std::cout << "Enter the semester you want to view scoreboard: ";
	int inputSem;
	std::cin >> inputSem;

	bool found = false;

	// loop through all the students
	for (int i = 0; i < totalStudent; i++)
	{
		if (studentQuery[i].Class == inputClass)
		{
			// loop through the list of courses
			Nodecourse* courseCur = studentQuery[i].list_enrolled_course;

			// variable to calculate the GPA in this semester
			double semGPA = 0;
			int count = 0;


			bool printStudent = false; // control variable to see if the student is printed
			while (courseCur)
			{
				// find the right semester
				if (courseCur->data.sem.no == inputSem)
				{
					// print out scores from list of scores
					if (!found)
					{
						found = true;
						std::cout << "\nHere's the list of scores of students in class " << inputClass << " in semester " << inputSem << '\n';
					}

					if (!printStudent)
					{
						std::cout << studentQuery[i].StudentID << " ";
						std::cout << studentQuery[i].lastName << " " << studentQuery[i].firstName << '\n';
						printStudent = true;
					}

					NodeScore* scoreCur = courseCur->data.scores;

					while (scoreCur)
					{
						if (scoreCur->data.studentID == studentQuery[i].StudentID)
						{
							std::cout << "Final mark of course " << courseCur->data.courseID << ": " << scoreCur->data.finalMark << '\n';
							
							semGPA += scoreCur->data.totalMark;
							count++;
						}

						scoreCur = scoreCur->pNext;
					}
				}

				courseCur = courseCur->pNext;
			}

			// print out semester GPA
			semGPA = semGPA / count;
			if (printStudent)
			{
				std::cout << "GPA in semester " << ": " << semGPA << '\n';
				std::cout << "------------------------------\n";
			}

			printStudent = false;
			
		}
	}

	if (!found)
	{
		std::cout << "Class or semester not found\n";
		std::cout << "----------------------------\n";
	}

	return;
}

bool addStudentToClass(std::string* classes, int nClasses, Student*& studentQuery, int& totalStudent)
{
	std::cout << "Enter the classname: ";
	std::string Class; std::cin >> Class;
	bool found = false;
	for (int i = 0; i < nClasses; i++)
		if (Class == classes[i])
		{
			found = true;
			break;
		}
	if (!found)
	{
		std::cout << "Class not found!";
		return false;
	}
	std::cout << "Enter the source file (.csv): ";
	std::string fileName; std::cin >> fileName;
	Student* temp = nullptr;
	int num = 0;
	if (!importCSVArray(temp, num, fileName))
	{
		std::cout << "File not found!";
		return false;
	}
	if(num < 1)
		return false;
	Student* newQuery = new Student[totalStudent+num + 1];
	for (int i = 0; i < totalStudent; i++)
	{
		newQuery[i] = studentQuery[i];
	}
	for (int i = 0; i < num; i++)
	{
		newQuery[i + totalStudent] = temp[i];
		newQuery[i + totalStudent].Class = Class;
	}
	delete[] temp;
	delete[]studentQuery;
	studentQuery = newQuery;
	totalStudent += num;
	std::cout << "Added successfully!\n";
	return true;
}
