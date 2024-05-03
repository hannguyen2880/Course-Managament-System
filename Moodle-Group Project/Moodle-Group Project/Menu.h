#pragma once

#include "Main.h"
#include "Staff.h"
#include "Student.h"
#include "Course.h"
#include "Scoreboard.h"
#include "Node.h"
void Student_menu(Student*& studentQuery, int& totalStudent);
void Staff_menu(Staff*& staffQuery, int& totalStaff, Nodecourse*& courses, int& nCourses, Class*& classes, std::string*& strclasses, int& nClasses, Student*& studentQuery, int& nStudents, semester*& semesterQuery, int& nSemesters);
