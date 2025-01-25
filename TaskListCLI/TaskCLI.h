#pragma once
#include <vector>
#include <string>
//Class focused on parsing command-line arguments and calling proper methods

class TaskCLI
{
public:
	enum class Command {
		ADD,
		UPDATE,
		DELETE,
		MARK_TODO,
		MARK_IN_PROGRESS,
		MARK_DONE,
		LIST,
		CLEAR
	};

	static void parseArguments(const std::vector<std::string>& argsVec);
	static Command stringToCommand(const std::string& commandStr);
	static std::string commandToString(const Command command);
	static void printHelp();

};

