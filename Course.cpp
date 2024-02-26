/**Joel Hays
*Project 2
*CS-300
*/


#include "Course.h"
#include <string>

/// Constructor for creating a Course object.
///
/// \param id the id value for the course.
/// \param name the name for the course.
/// \param prerequisites the list of any prerequisites for the course.
CourseObject::CourseObject(std::string& number, std::string& title, std::vector<std::string>& prereq) {
	this->courseNumber = number;
	this->courseTitle = title;
	this->coursePrereq = prereq;
}

/// Getter for the course id.
/// \return courseId
std::string CourseObject::getCourseNumber() {
	return this->courseNumber;
}

/// Getter for the course name.
/// \return courseName
std::string CourseObject::getCourseTitle() {
	return this->courseTitle;
}

/// Getter for the list of course prerequisites.
/// \return coursePrerequisites
std::vector<std::string> CourseObject::getCoursePrereq() {
	return this->coursePrereq;
}

/// Returns a concatenated string of course values.
/// \return string with courseId and courseName
std::string CourseObject::courseToString() {
	return this->courseNumber + ", " + this->courseTitle;
}