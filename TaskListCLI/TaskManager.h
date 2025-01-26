#pragma once
#include "Task.h"

#include <string>
#include <vector>

class TaskManager
{
public:
	static void queryCommand(const std::vector<std::string>& argsVec);

private:
	static void addTask(const std::vector<std::string>& argsVec);
	static void updateTask(const std::vector<std::string>& argsVec);
	static void deleteTask(const std::vector<std::string>& argsVec);
	static void changeTaskStatus(const std::vector<std::string>& argsVec, Task::Status status);
	static void list(const std::vector<std::string>& argsVec);
	static void clearList(const std::vector<std::string>& argsVec);

	static const std::string jsonFilename;
};

