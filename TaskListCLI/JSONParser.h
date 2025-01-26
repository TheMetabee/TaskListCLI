#pragma once
#include "Task.h"

#include <vector>
#include <memory>

class JSONParser
{
public:
	std::string taskToJson(const Task& task);
	void saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename);
	Task jsonToTask(const std::string& json);
	std::vector<Task> loadTasksFromFile(const std::string& filename);
	bool jsonFileExists(const std::string& filename);

private:
	std::string getValue(const std::string& json, const std::string& key) const;

};

