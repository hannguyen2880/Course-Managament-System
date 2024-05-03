#include "Node.h"

void deleteListStudent(NodeStudent*& pHead) {
	while (pHead != nullptr) {
		NodeStudent* temp = pHead;
		pHead = pHead->pNext;
		delete temp;
	}
}
void deleteListScore(NodeScore*& pHead) {
	while (pHead != nullptr) {
		NodeScore* temp = pHead;
		pHead = pHead->pNext;
		delete temp;
	}
}

void deleteListCourse(Nodecourse*& pHead) {
	while (pHead != nullptr) {
		Nodecourse* temp = pHead;
		pHead = pHead->pNext;
		deleteListStudent(temp->data.students);
		deleteListScore(temp->data.scores);
		delete temp;
	}
}

void AddStudentAtBeginning(NodeStudent*& pHead, Student& stus, int& cntNode, NodeScore*& scores) 
{
	NodeScore* scoreCur = new NodeScore;

	// set all scores to zero
	scoreCur->data.finalMark = 0;
	scoreCur->data.midtermMark = 0;
	scoreCur->data.otherMark = 0;
	scoreCur->data.totalMark = 0;

	scoreCur->data.studentID = stus.StudentID;
	scoreCur->data.studentFullName = stus.lastName + " " + stus.firstName;

	scoreCur->pNext = scores;
	scores = scoreCur;
	
	++cntNode;
	NodeStudent* cur = new NodeStudent;
	cur->data = stus;
	cur->pNext = pHead;

	

	pHead = cur;
	std::cout << "Student added!\n";
}

void remove_a_Studentnode(NodeStudent*& pHead, Student& student, int& cntNode) {
	if (!pHead) return;
	//deleteListCourse(student.list_enrolled_course);
	if (pHead->data.StudentID == student.StudentID) {
		// remove at Beginning
		NodeStudent* temp = pHead;
		pHead = pHead->pNext;
		delete temp;
		--cntNode;
		return;
	}
	NodeStudent* cur = pHead->pNext, * prev = pHead;
	while (cur) {
		if (cur->data.StudentID == student.StudentID) {
			NodeStudent* temp = cur;
			cur = cur->pNext;
			delete temp;

			prev->pNext = cur;
			--cntNode;
			return;
		}
		prev = cur;
		cur = cur->pNext;
	}
	// remove score board
}

void AddNodeCourseAtBeginning(Nodecourse*& pHead, Course& newcourse, int& cntNode) 
{
	++cntNode;
	Nodecourse* cur = new Nodecourse;
	cur->data = newcourse;
	cur->pNext = pHead;
	pHead = cur;
	// std::cout << "Student enrolled in course!\n";
}
void RemoveNodeCourse(Nodecourse*& pHead, Course& course, int& cntNode) {
	if (!pHead) return;
	//deleteListStudent(course.students);
	//deleteListScore(course.scores);
	if (pHead->data.courseID == course.courseID) {
		// remove at Beginning
		Nodecourse* temp = pHead;
		pHead = pHead->pNext;
		delete temp;
		--cntNode;
		return;
	}
	Nodecourse* cur = pHead->pNext, * prev = pHead;

	while (cur) {
		if (cur->data.courseID == course.courseID) {
			Nodecourse* temp = cur;
			cur = cur->pNext;
			delete temp;

			prev->pNext = cur;
			--cntNode;
			return;
		}
		prev = cur;
		cur = cur->pNext;
	}
}

void AddNodeScoreAtBeginning(NodeScore*& pHead, scoreboard& newscore, int& cntNode) {
	++cntNode;
	NodeScore* cur = new NodeScore;
	cur->data = newscore;
	cur->pNext = pHead;
	pHead = cur;
}