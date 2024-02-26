/**Joel Hays
*Project 2
*CS-300
*/



#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "CourseInfo.h"

/**
 * Display the course information to the console (std::cout)
 *
 * @param course struct containing the course info
 */
void displayCourseInfo(CourseObject courseObject) {
	std::vector<std::string> coursePrereq = courseObject.getCoursePrereq();
	std::string prereq;
	// formats output for prereq, if there are any
	if (coursePrereq.size() == 1) {
		prereq = courseObject.getCoursePrereq()[0];
	}
	else if (coursePrereq.size() > 1) {
		for (int i = 0; i < coursePrereq.size() - 1; i++) {
			prereq += coursePrereq[i] + ", ";
		}
		prereq += coursePrereq.back();
	}
	else {
		prereq = "n/a";
	}

	// prints out the course details
	std::cout << courseObject.getCourseNumber() << ", "
		<< courseObject.getCourseTitle() << std::endl;
	std::cout << "Prerequisites: " << prereq << std::endl;
}

/**
 * Load an input file containing courses into a container
 *
 * @param inputFilePath the path to the input file to load
 * @return a container holding all the courses read
 */
void loadCourseInfo(const std::string& inputFilePath, CourseInfo* courseInfoBst) {
	std::cout << "Loading input file " << inputFilePath << std::endl;

	std::ifstream file(inputFilePath);
	std::string currentLine;
	try {
		while (std::getline(file, currentLine)) {
			std::stringstream ss(currentLine);
			std::string word, number, title;
			std::vector<std::string> prereq;
			int index = 0;
			while (!ss.eof()) {
				getline(ss, word, ',');
				word = std::regex_replace(word, std::regex(R"(\r\n|\r|\n)"), "");
				if (index == 0) {
					number = word;
				}
				else if (index == 1) {
					title = word;
				}
				else {
					prereq.push_back(word);
				}
				index++;
			}
			// create a data structure and add to the collection of courses
			CourseObject courseObject = CourseObject(number, title, prereq);
			// add this course to the tree
			courseInfoBst->Insert(courseObject);
		}
	}
	catch (std::ifstream::failure& e) {
		std::cerr << e.what() << std::endl;
	}

	file.close();
}

int main() {
	// Define a binary search tree to hold all courses
	CourseInfo* courseInfoBst;
	courseInfoBst = new CourseInfo();
	CourseObject courseObject;
	std::string inputPath, courseKey;

	std::cout << "Welcome to the degree planner and course information." << std::endl << std::endl;

	int choice = 0;
	while (choice != 4) {
		std::cout << "  1. Load File" << std::endl;
		std::cout << "  2. Print Course List" << std::endl;
		std::cout << "  3. Print Course" << std::endl;
		std::cout << "  4. Exit" << std::endl << std::endl;
		std::cout << "Please select any option of 1 through 4: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			std::cout << "Enter the path the to input file:  ";
			std::cin >> inputPath;
			// Complete the method call to load the courses
			loadCourseInfo(inputPath, courseInfoBst);
			break;
		case 2:
			std::cout << "Here is a list of the current courses in alphanumeric order:" << std::endl << std::endl;
			courseInfoBst->InOrder();
			break;
		case 3:
			std::cout << "Please enter the course number to show it's information. ";
			std::cin >> courseKey;
			courseObject = courseInfoBst->Search(courseKey);

			if (!courseObject.getCourseNumber().empty()) {
				displayCourseInfo(courseObject);
			}
			else {
				std::cout << courseKey << " is not currently in the database. Going back to main menu." << std::endl;
			}
			break;
		case 4:
			std::cout << "Good bye." << std::endl;
			break;
		default:
			std::cout << choice << " is not a valid option." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		std::cout << std::endl;
	}

	return 0;
}