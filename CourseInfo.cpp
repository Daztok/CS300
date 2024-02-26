/**Joel Hays
*Project 2
*CS-300
*/


#include <iostream>
#include <regex>
#include "CourseInfo.h"

/**
 * Default constructor
 */
CourseInfo::CourseInfo() {
	//set root to nullptr
	root = nullptr;
}

/**
 * Destructor
 */
CourseInfo::~CourseInfo() {
	//recurse from root deleting every node
	destroyAll(root);
}


 //Traverse the tree in order
void CourseInfo::InOrder() {
	//call inOrder function and pass root
	inOrder(root);
}


//Traverse the tree in post-order 
void CourseInfo::PostOrder() {
	//postOrder root
	postOrder(root);
}


//Traverse the tree in pre-order
void CourseInfo::PreOrder() {
	//preOrder root
	preOrder(root);
}

//Insert a course
void CourseInfo::Insert(CourseObject courseObject) {
	//if root equal to nullptr
	if (root == nullptr) {
		//root is equal to new node course
		root = new Node(courseObject);
	}
	else {
		//add root Node and course
		this->addNode(root, courseObject);
	}
}

//Add a course to some node (recursive)
void CourseInfo::addNode(Node* node, CourseObject courseObject) {
	//if new node is smaller than current add to left
	if (node != nullptr && (node->courseObject.getCourseNumber().compare(courseObject.getCourseNumber()) > 0)) {
		//if there is no left node
		if (node->left == nullptr) {
			//this node becomes new left node
			node->left = new Node(courseObject);
			return;
		}
		//else recurse down the left node
		else {
			this->addNode(node->left, courseObject);
		}
	}
	//else
	else if (node != nullptr && (node->courseObject.getCourseNumber().compare(courseObject.getCourseNumber()) < 0)) {
		//if no right node
		if (node->right == nullptr) {
			//this node becomes right
			node->right = new Node(courseObject);
			return;
		}
		//else if node is larger than add to right
		else {
			//recurse down the right node
			this->addNode(node->right, courseObject);
		}
	}
}

//Remove a course
void CourseInfo::Remove(std::string courseNumber) {
	//remove node root courseNumber
	this->removeNode(root, courseNumber);
}

void CourseInfo::inOrder(Node* node) {
	//if node is not equal to null ptr
	if (node != nullptr) {
		//inOrder left
		inOrder(node->left);
		//output courseNumber and courseName
		std::cout << node->courseObject.getCourseNumber() << ", "
			<< node->courseObject.getCourseTitle() << std::endl;
		//inOrder right
		inOrder(node->right);
	}
}

void CourseInfo::postOrder(Node* node) {
	//if node is not equal to nullptr
	if (node != nullptr) {
		//postOrder left
		postOrder(node->left);
		//postOrder right
		postOrder(node->right);
		//output courseNumber and courseName
		std::cout << node->courseObject.getCourseNumber() << ", "
			<< node->courseObject.getCourseTitle() << std::endl;
	}
}

void CourseInfo::preOrder(Node* node) {
	//if node is not equal to nullptr
	if (node != nullptr) {
		//output courseNumber and courseName
		std::cout << node->courseObject.getCourseNumber() << ", "
			<< node->courseObject.getCourseTitle() << std::endl;
		//preOrder left
		preOrder(node->left);
		//preOrder right
		preOrder(node->right);
	}
}

//Search for a course
CourseObject CourseInfo::Search(std::string courseNumber) {
	//convert courseNumber to upper case
	transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
	//set current node equal to root
	Node* cur = root;
	//loop downwards until bottom reached or matching courseNumber found
	while (cur != nullptr) {
		//if match found, return current course
		if (cur->courseObject.getCourseNumber().compare(courseNumber) == 0) {
			return cur->courseObject;
		}
		//if course is smaller than current node then traverse left
		else if (courseNumber.compare(cur->courseObject.getCourseNumber()) < 0) {
			cur = cur->left;
		}
		//else larger so traverse right
		else {
			cur = cur->right;
		}
	}
	//course not found so return empty course.
	CourseObject course;
	return course;
}

Node* CourseInfo::removeNode(Node* node, const std::string courseNumber) {
	if (node == nullptr) {
		return node;
	}
	//if course is smaller than current node then traverse left
	else if (courseNumber.compare(node->courseObject.getCourseNumber()) < 0) {
		node->left = removeNode(node->left, courseNumber);
	}
	//else if course is larger than current node then traverse right
	else if (courseNumber.compare(node->courseObject.getCourseNumber()) > 0) {
		node->right = removeNode(node->right, courseNumber);
	}
	//else match point found
	else {
		//leaf node
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			node = nullptr;
		}
		//else if left child
		else if (node->left != nullptr && node->right == nullptr) {
			Node* tmp = node;
			node = node->left;
			delete tmp;
			tmp = nullptr;
		}
		//else if right child
		else if (node->left == nullptr && node->right != nullptr) {
			Node* tmp = node;
			node = node->right;
			delete tmp;
			tmp = nullptr;
		}
		//else both children
		else {
			//find the minimum of the right subtree nodes for bst
			Node* tmp = node;
			while (tmp->left != nullptr) {
				tmp = tmp->left;
			}
			node->courseObject = tmp->courseObject;
			node->right = removeNode(node->right, tmp->courseObject.getCourseNumber());
		}
	}
	return node;
}

void CourseInfo::destroyAll(Node* node) {
	//if node is not equal to nullptr
	if (node != nullptr) {
		//call for destruction of any children
		destroyAll(node->left);
		destroyAll(node->right);
		//remove the current node
		delete node;
		node = nullptr;
	}
}