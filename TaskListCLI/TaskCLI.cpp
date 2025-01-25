#include "TaskCLI.h"
#include "Task.h"
#include "TaskManager.h"

#include <iostream>


void TaskCLI::parseArguments(const std::vector<std::string>& argsVec)
{
    if (argsVec.size() <= 1) {
        TaskCLI::printHelp();
        return;
    }

    TaskManager::queryCommand(argsVec);
}

TaskCLI::Command TaskCLI::stringToCommand(const std::string& commandStr)
{
    if (commandStr == "add")
        return Command::ADD;
    else if (commandStr == "update")
        return Command::UPDATE;
    else if (commandStr == "delete")
        return Command::DELETE;
    else if (commandStr == "mark-todo")
        return Command::MARK_TODO;
    else if (commandStr == "mark-in-progress")
        return Command::MARK_IN_PROGRESS;
    else if (commandStr == "mark-done")
        return Command::MARK_DONE;
    else if (commandStr == "list")
        return Command::LIST;
    else if (commandStr == "clear")
        return Command::CLEAR;

    throw std::invalid_argument("Invalid command: " + commandStr);
}

std::string TaskCLI::commandToString(const Command command)
{
    switch (command) {
    case Command::ADD:
        return "add";
    case Command::UPDATE:
        return "update";
    case Command::DELETE:
        return "delete";
    case Command::MARK_TODO:
        return "mark-todo";
    case Command::MARK_IN_PROGRESS:
        return "mark-in-progress";
    case Command::MARK_DONE:
        return "mark-done";
    case Command::LIST:
        return "list";
    case Command::CLEAR:
        return "clear";
    default:
        return "unknown";
    }
}

void TaskCLI::printHelp()
{
    std::cout << "Please enter one of the following commands." << '\n';
    std::cout << "  add \"task name\"" << '\n';
    std::cout << "  update id# \"new task name\"" << '\n';
    std::cout << "  delete id#" << '\n';
    std::cout << "  mark-in-progress id#" << '\n';
    std::cout << "  mark-done id#" << '\n';
    std::cout << "  list [done/ todo/ in-progress]" << '\n';
    std::cout << "  clear\n";
}



