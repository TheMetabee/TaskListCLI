#pragma once
#include "Task.h"

#include <vector>
#include <memory>

class JSONParser
{
public:
	static std::string taskToJson(const Task& task);
	static void saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename = "");
	static Task jsonToTask(const std::string& json);
	static std::vector<Task> loadTasksFromFile(const std::string& filename = "");
	static bool jsonFileExists(const std::string& filename = "");
	static void deleteList(const std::string& filename = "");

private:
	static const std::string jsonFilename;
};

