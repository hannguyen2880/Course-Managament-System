#pragma once
#include "Main.h"
#include "Student.h"
#include "Course.h"
#include "Scoreboard.h"

struct NodeStudent {
	Student data;
	NodeStudent* pNext;
};

void AddStudentAtBeginning(NodeStudent*& pHead, Student& stus, int& cntNode, NodeScore*& scores);
void remove_a_Studentnode(NodeStudent*& pHead, Student& student, int& cntNode);

struct Nodecourse {
	Course data;
	Nodecourse* pNext;
};

void AddNodeCourseAtBeginning(Nodecourse*& pHead, Course& newcourse, int& cntNode);
void RemoveNodeCourse(Nodecourse*& pHead, Course& course, int& cntNode);
void deleteListStudent(NodeStudent*& pHead);
void deleteListScore(NodeScore*& pHead);
void deleteListCourse(Nodecourse*& pHead);

struct NodeScore {
	scoreboard data;
	NodeScore* pNext;
};

void AddNodeScoreAtBeginning(NodeScore*& pHead, scoreboard& newscore, int& cntNode);