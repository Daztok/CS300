/**Joel Hays
*Project 2
*CS-300
*/
#ifndef CourseClass_H
#define CourseClass_H

#include <string>
#include <vector>

class CourseObject {
	// private fields for a course object.
private:
	std::string courseNumber;
	std::string courseTitle;
	std::vector<std::string> coursePrereq;
	// public methods for a course object.
public:
	CourseObject() = default;
	CourseObject(std::string& number, std::string& title, std::vector<std::string>& prereq);
	std::string getCourseNumber();
	std::string getCourseTitle();
	std::vector<std::string> getCoursePrereq();
	std::string courseToString();
};

#endif
