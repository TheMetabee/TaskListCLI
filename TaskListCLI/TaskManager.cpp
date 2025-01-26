#include "TaskManager.h"
#include "Task.h"
#include "TaskCLI.h"
#include "JSONParser.h"

#include <iostream>

const std::string TaskManager::jsonFilename = "jsonTaskList.json";

void TaskManager::queryCommand(const std::vector<std::string>& argsVec)
{
	try {
		TaskCLI::Command command = TaskCLI::stringToCommand(argsVec[1]);

		switch (command) {
		case TaskCLI::Command::ADD:
			TaskManager::addTask(argsVec);
			break;
		case TaskCLI::Command::UPDATE:
			TaskManager::updateTask(argsVec);
			break;
		case TaskCLI::Command::DELETE:
			TaskManager::deleteTask(argsVec);
			break;
		case TaskCLI::Command::MARK_TODO:
			TaskManager::changeTaskStatus(argsVec, Task::Status::TODO);
			break;
		case TaskCLI::Command::MARK_IN_PROGRESS:
			TaskManager::changeTaskStatus(argsVec, Task::Status::IN_PROGRESS);
			break;
		case TaskCLI::Command::MARK_DONE:
			TaskManager::changeTaskStatus(argsVec, Task::Status::DONE);
			break;
		case TaskCLI::Command::LIST:
			TaskManager::list(argsVec);
		case TaskCLI::Command::CLEAR:
			TaskManager::clearList(argsVec);
			break;
		}
	}
	catch (std::invalid_argument const& ex) {
		std::cout << ex.what() << '\n';
	}
}

void TaskManager::addTask(const std::vector<std::string>& argsVec)
{
	if (argsVec.size() < 3)
		throw std::invalid_argument("Missing description argument.");
	if (argsVec[2].empty())
		throw std::invalid_argument("Description is empty.");

	std::string description = argsVec[2];

	//check if file exists. If it does, load tasks
	if (JSONParser::jsonFileExists()) {
		auto tasks = JSONParser::loadTasksFromFile(jsonFilename);

		//get largest id from tasks to set new task 1 higher 
		int largestId = 0;
		for (auto& task : tasks) {
			if (task.getId() > largestId)
				largestId = task.getId();
		}

		Task newTask = { largestId + 1, description };
		
		//add task to vector and save back to file
		tasks.push_back(newTask);
		JSONParser::saveTasksToFile(tasks);
		std::cout << "Added new task:\n" << newTask << std::endl;
	}
	else {
		//file doesnt exist, so assume new
		std::vector<Task> tasks;

		Task newTask = { 1, description };
		
		//add task to vector and save back to file
		tasks.push_back(newTask);
		JSONParser::saveTasksToFile(tasks);
		std::cout << "Added new task:\n" << newTask << std::endl;
	}
}

void TaskManager::updateTask(const std::vector<std::string>& argsVec)
{
	int id{};

	if (argsVec.size() < 4)
		throw std::invalid_argument("Too few arguments.");
	if(argsVec[2].empty())
		throw std::invalid_argument(argsVec[2] +  " must be the id number.");

	try {
		id = std::stoi(argsVec[2]);
	}
	catch (std::exception& e) {
		std::cout << argsVec[2] << " must be the id number." << std::endl;
		return;
	}

	if (argsVec[3].empty())
		throw std::invalid_argument("Description is empty.");

	std::string description = argsVec[3];

	//check if file exists. if not, this is invalid
	if (!JSONParser::jsonFileExists) {
		std::cout << "Task list is empty. Nothing to update." << std::endl;
		return;
	}

	auto tasks = JSONParser::loadTasksFromFile(jsonFilename);

	if (tasks.empty()) {
		std::cout << "Task list is empty. Nothing to update." << std::endl;
		return;
	}

	//check if the task is actually in the file. If so, update it
	//if not, notify user
	bool found = false;
	for (auto& task : tasks) {
		if (task.getId() == id) {
			found = true;
			task.setDescription(description);
			JSONParser::saveTasksToFile(tasks);
			std::cout << "Task successfully updated (ID: " << id << ")\n";
			std::cout << task << std::endl;
			break;
		}
	}

	if (!found) {
		std::cout << "Task ID: " << id << " was not found in list." << std::endl;
	}

}

void TaskManager::deleteTask(const std::vector<std::string>& argsVec)
{
	int id{};

	if(argsVec.size() < 3)
		throw std::invalid_argument("Must enter id number of task.");

	try {
		id = std::stoi(argsVec[2]);
	}
	catch (std::exception& e) {
		std::cout << argsVec[2] << " must be the id number." << std::endl;
		return;
	}

	//check if file exists. if not, this is invalid
	if (!JSONParser::jsonFileExists) {
		std::cout << "Task list is empty. Nothing to delete." << std::endl;
		return;
	}

	auto tasks = JSONParser::loadTasksFromFile(jsonFilename);

	if (tasks.empty()) {
		std::cout << "Task list is empty. Nothing to update." << std::endl;
		return;
	}

	//check if the task is actually in the file. If so, delete it
	//if not, notify user
	bool found = false;
	for (std::vector<Task>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
		if (it->getId() == id) {
			found = true;
			tasks.erase(it);
			JSONParser::saveTasksToFile(tasks);
			std::cout << "Task was successfully deleted (ID: " << id << ")\n";
			break;
		}
	}

	if (!found) {
		std::cout << "Task ID: " << id << " was not found in list." << std::endl;
	}
}

void TaskManager::changeTaskStatus(const std::vector<std::string>& argsVec, Task::Status status)
{
	int id{};

	if (argsVec.size() < 3)
		throw std::invalid_argument("Must enter id number of task.");

	try {
		id = std::stoi(argsVec[2]);
	}
	catch (std::exception& e) {
		std::cout << argsVec[2] << " must be the id number." << std::endl;
		return;
	}

	//check if file exists. if not, this is invalid
	if (!JSONParser::jsonFileExists) {
		std::cout << "Task list is empty. Nothing to update." << std::endl;
		return;
	}

	auto tasks = JSONParser::loadTasksFromFile(jsonFilename);

	if (tasks.empty()) {
		std::cout << "Task list is empty. Nothing to update." << std::endl;
		return;
	}

	bool found = false;
	for (std::vector<Task>::iterator it = tasks.begin(); it != tasks.end(); ++it) {
		if (it->getId() == id) {
			found = true;
			it->setStatus(status);
			JSONParser::saveTasksToFile(tasks);
			std::cout << "Task set to " << it->statusToString() << " (ID: " << id << ")\n";
			std::cout << *it << std::endl;
			break;
		}
	}

	if (!found) {
		std::cout << "Task ID: " << id << " was not found in list." << std::endl;
	}
}


void TaskManager::list(const std::vector<std::string>& argsVec)
{
	Task::Status status = Task::Status::NONE;
	std::string statusStr{};

	if (argsVec.size() > 2) {
		status = Task::stringToStatus(argsVec[2]);
		statusStr = argsVec[2];
	}

	//check if file exists. if not, this is invalid
	if (!JSONParser::jsonFileExists) {
		std::cout << "Task list is empty. Nothing to show." << std::endl;
		return;
	}

	auto tasks = JSONParser::loadTasksFromFile(jsonFilename);

	if (tasks.empty()) {
		std::cout << "Task list is empty. Nothing to show." << std::endl;
		return;
	}

	if (status == Task::Status::NONE) {
		for (auto& task : tasks) {
			std::cout << JSONParser::taskToJson(task) << std::endl;
		}
	}
	else {

		for (auto& task : tasks) {
			if(task.getStatus() == statusStr)
				std::cout << JSONParser::taskToJson(task) << std::endl;
		}
	}
	
}

void TaskManager::clearList(const std::vector<std::string>& argsVec)
{
	JSONParser::deleteList();
}
