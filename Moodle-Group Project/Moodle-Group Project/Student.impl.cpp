#include "Student.h"
#include <iostream>
#include "Node.h"
#include "Course.h"
Student* Student::Login(Student* studentQuery, int& totalStudent) {
	//Student t = Student(1, 23125055, "Nguyen", "Han", 1, "250305", 123, "123");
	std::cout << "Student ID: ";
	std::string id; std::cin >> id;
	std::cout << "Password: ";
	std::string password;
	//std::cin >> password;
	std::cin.ignore();
	std::getline(std::cin, password);

	for (int i = 0; i < totalStudent; i++)
	{
		if (studentQuery[i].StudentID == id && studentQuery[i].password == password)
		{
			std::cout << "Login Successfully\n";
			return &studentQuery[i];
		}
	}
	std::cout << "ID or Password is incorrect\n";
	return NULL;
}

void Student::changePassWord() {
	std::string oldPass, newPass, reNewPass;
	std::cin.ignore();
	std::cout << "Enter the old password: ";
	std::getline(std::cin, oldPass);
	if (oldPass == Student::password) {
		std::cout << "Enter the new password: ";
		std::getline(std::cin, newPass);
		std::cout << "Confirm: ";
		std::getline(std::cin, reNewPass);
		if (newPass == reNewPass) {
			Student::password = newPass;
			std::cout << "Changed password successfully.\n";
			return;
		}
		else {
			std::cout << "The passwords are not match.\n";
			return;
		}
	}
	else {
		std::cout << "Wrong password.\n";
		return;
	}
}

void Student::viewProfile() {
	std::cout << "Number: " << no << std::endl;
	std::cout << "Student's ID: " << StudentID << std::endl;
	std::cout << "First Name: " << firstName << std::endl;
	std::cout << "Last Name: " << lastName << std::endl;
	std::cout << "Gender: ";
	if (gender) std::cout << "Female" << std::endl;
	else std::cout << "Male" << std::endl;
	std::cout << "Date of birth: " << dob << std::endl;
	std::cout << "Social ID: " << socialID << std::endl;
	std::cout << "Password: " << password << std::endl;
	return;
}

void Student::viewCourses() {
	Nodecourse* cur = list_enrolled_course;
	std::cout << "Here's the list of your courses: \n";

	if (!cur)
	{
		std::cout << "You are not enrolled in any courses\n";
		return;
	}

	while (cur != nullptr)
	{
		std::cout << (cur->data).courseID << ": " << (cur->data).courseName << '\n';
		cur = cur->pNext;
	}
}

void Student::enroll_Course(Course& newcourse) 
{
	AddNodeCourseAtBeginning(list_enrolled_course, newcourse, number_enrolled_course);
	
}

void Student::viewScoreboard()
{
	Nodecourse* cur = list_enrolled_course;

	// Loop through the list of course 
	while (cur != nullptr)
	{
		// make a current pointer to loop through the list of scores
		NodeScore* scoreCur = (cur->data).scores;

		// Loop through the list of scores in the course the find the right student
		while (scoreCur)
		{
			if ((scoreCur->data).studentID == StudentID)
			{
				std::cout << "Here's your score board in " << (cur->data).courseID << '\n';
				std::cout << "Midterm mark: " << (scoreCur->data).midtermMark << '\n';
				std::cout << "Final mark: " << (scoreCur->data).finalMark << '\n';
				std::cout << "Total mark: " << (scoreCur->data).totalMark << '\n';
				std::cout << "Other mark: " << (scoreCur->data).otherMark << '\n';
				break;
			}
			scoreCur = scoreCur->pNext;
		}
		cur = cur->pNext;
	}
}
