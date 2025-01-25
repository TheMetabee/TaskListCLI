#pragma once
#include <string>

class Task
{
public:
	enum class Status {
		NONE,
		TODO,
		IN_PROGRESS,
		DONE
	};

	Task(int _id, const std::string& _description, const std::string& _status = "todo");
	Task(int _id, const std::string& _description, const std::string& _status, 
		const std::string& _createdAt, const std::string& _updatedAt);
	int getId() const;
	std::string getDescription() const;
	void setDescription(const std::string& _description);
	std::string statusToString() const;
	static Status stringToStatus(const std::string& statusStr);
	std::string getStatus() const;
	void setStatus(const std::string& _status);
	void setStatus(Status _status);
	std::string getCreatedAt() const;
	std::string getUpdatedAt() const;
	void makeUpdated(); //will set updatedAt to current time
	std::string getCurrentTime() const;

	friend std::ostream& operator<<(std::ostream& os, const Task& t);

private:
	int id;
	std::string description;
	Status status;
	std::string createdAt;
	std::string updatedAt;

	
};

