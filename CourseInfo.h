/**Joel Hays
*Project 2
*CS-300
*/
#ifndef CourseInfo_H
#define CourseInfo_H

#include <string>
#include <vector>
#include "Course.h"

struct Node {
	CourseObject courseObject;
	Node* left;
	Node* right;

	// default node .constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// initialize course
	Node(CourseObject newCourseObject) :
		Node() {
		courseObject = newCourseObject;
	}
};

class CourseInfo {
private:
	Node* root;
	void addNode(Node* node, CourseObject courseObject);
	void inOrder(Node* node);
	void postOrder(Node* node);
	void preOrder(Node* node);
	void destroyAll(Node* node);
	Node* removeNode(Node* node, std::string courseNumber);
public:
	CourseInfo();
	virtual ~CourseInfo();
	void InOrder();
	void PostOrder();
	void PreOrder();
	void Insert(CourseObject courseObject);
	void Remove(std::string courseNumber);
	CourseObject Search(std::string courseNumber);
};

#endif