#include "Task.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>

Task::Task(int _id, const std::string& _description, const std::string& _status)
	: id(_id), description(_description), status(stringToStatus(_status)), 
	createdAt(getCurrentTime()), updatedAt(createdAt){ }

Task::Task(int _id, const std::string& _description, const std::string& _status, const std::string& _createdAt, const std::string& _updatedAt)
: id(_id), description(_description), status(stringToStatus(_status)), 
	createdAt(_createdAt), updatedAt(_updatedAt){ }


int Task::getId() const
{
	return id;
}

std::string Task::getDescription() const
{
	return description;
}

void Task::setDescription(const std::string& _description)
{
	description = _description;
	makeUpdated();
}

std::string Task::statusToString() const
{
	switch (status) {
	case Status::TODO:
		return "todo";
	case Status::IN_PROGRESS:
		return "in-progress";
	case Status::DONE:
		return "done";
	default:
		return "unknown";
	}
}

Task::Status Task::stringToStatus(const std::string& statusStr)
{
	if (statusStr == "todo") {
		return Status::TODO;
	}
	else if (statusStr == "in-progress") {
		return Status::IN_PROGRESS;
	}
	else if (statusStr == "done") {
		return Status::DONE;
	}
	throw std::invalid_argument("Invalid status string: " + statusStr);
}

std::string Task::getStatus() const
{
	return statusToString();
}

void Task::setStatus(const std::string& _status)
{
	try {
		Task::Status convertedStatus = stringToStatus(_status);
		status = convertedStatus;
		makeUpdated();
	}
	catch (std::invalid_argument const& ex) {
		std::cout << ex.what() << '\n';
	}
}

void Task::setStatus(Status _status)
{
	status = _status;
	makeUpdated();
}

std::string Task::getCreatedAt() const
{
	return createdAt;
}

std::string Task::getUpdatedAt() const
{
	return updatedAt;
}

void Task::makeUpdated()
{
	updatedAt = getCurrentTime();
}

std::string Task::getCurrentTime() const
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);
	std::tm now_tm = *std::localtime(&now_time);

	std::stringstream ss;
	ss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S"); // Format: "2025-01-24T10:00:00"

	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Task& t)
{
	os << "Id: " << t.getId() << '\n';
	os << "Description: " << t.getDescription() << '\n';
	os << "Status: " << t.getStatus() << '\n';
	os << "Created at: " << t.getCreatedAt() << '\n';
	os << "Updated at: " << t.getUpdatedAt() << '\n';

	return os;

}
