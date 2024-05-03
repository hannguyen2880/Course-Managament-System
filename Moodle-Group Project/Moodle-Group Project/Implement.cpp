#include "Implement.h"
#include "Student.h"
#include "Course.h"
#include "Node.h"

void addCoursetoStudent(Student* studentsQuery, int& totalStudent, Course& course) {
	// this course is just exported a list of students in this course
	for (int i = 0; i < totalStudent; ++i) {
		// course.student is a ponter
		NodeStudent* cur = course.students;
		while (cur) {
			if (cur->data.StudentID == studentsQuery[i].StudentID) {
				studentsQuery[i].enroll_Course(course);
			}
			cur = cur->pNext;
		}
	}
}

void deleteCourseFromStudentArr(Student* studentsQuerry, int& totalStudent, Course& course)
{
	for (int i = 0; i < totalStudent; ++i)
	{
		RemoveNodeCourse(studentsQuerry[i].list_enrolled_course, course, studentsQuerry[i].number_enrolled_course);
	}
}

//void combine(Student* arr, int& n, Student* arr1, int& nStudents1, Student* arr2, int& nStudents2) {
//	n = nStudents1 + nStudents2;
//	arr = new Student[n];
//
//	for (int i = 0; i < nStudents1; ++i) arr[i] = arr1[i];
//	for (int i = nStudents1; i < n; ++i) arr[i] = arr2[i - nStudents1];
//}
