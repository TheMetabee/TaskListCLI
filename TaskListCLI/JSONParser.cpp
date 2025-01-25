#include "JSONParser.h"
#include <fstream>
#include <cstdio>
#include <iostream>

const std::string JSONParser::jsonFilename = "jsonTaskList.json";

std::string JSONParser::taskToJson(const Task& task)
{
    std::string json = "{";
    json += "\"id\": " + std::to_string(task.getId()) + ",";
    json += "\"description\": \"" + task.getDescription() + "\",";
    json += "\"status\": \"" + task.getStatus() + "\",";
    json += "\"createdAt\": \"" + task.getCreatedAt() + "\",";
    json += "\"updatedAt\": \"" + task.getUpdatedAt() + "\"";
    json += "}";
    return json;
}

void JSONParser::saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename)
{
    std::string _filename{};
    if (filename.empty())
        _filename = JSONParser::jsonFilename;
    else
        _filename = _filename;

    std::ofstream file(_filename);
    file << "[\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        file << taskToJson(tasks[i]);
        if (i != tasks.size() - 1) {
            file << ",\n";
        }
    }
    file << "\n]";
}

Task JSONParser::jsonToTask(const std::string& json)
{

    auto getValue = [](const std::string& json, const std::string& key) -> std::string {
        size_t keyPos = json.find("\"" + key + "\"");
        if (keyPos == std::string::npos) {
            throw std::runtime_error("Key \"" + key + "\" not found in JSON.");
        }

        size_t colonPos = json.find(":", keyPos);
        if (colonPos == std::string::npos) {
            throw std::runtime_error("No colon found after key \"" + key + "\".");
        }

        // Find the start of the value, skipping whitespace and quotes
        size_t start = json.find_first_not_of(" \t\n\r", colonPos + 1);

        if (start == std::string::npos) {
            throw std::runtime_error("Value for key \"" + key + "\" not found.");
        }

        // Determine if it's a quoted string
        if (json[start] == '"') {
            // Find the closing quote for the string
            size_t end = json.find('"', start + 1);
            if (end == std::string::npos) {
                throw std::runtime_error("Unterminated string value for key \"" + key + "\".");
            }
            return json.substr(start + 1, end - start - 1); // Extract value without quotes
        }
        else {
            // If not a string, find the next comma or closing brace
            size_t end = json.find_first_of(",}", start);
            if (end == std::string::npos) {
                throw std::runtime_error("Malformed JSON: Couldn't find end of value for key \"" + key + "\".");
            }
            return json.substr(start, end - start); // Extract raw value
        }
        };

    Task task = {
        std::stoi(getValue(json, "id")),            // Parse "id" as integer
        getValue(json, "description"),             // Parse "description" as string
        getValue(json, "status"),                  // Parse "status" as string
        getValue(json, "createdAt"),               // Parse "createdAt" as string
        getValue(json, "updatedAt")                // Parse "updatedAt" as string
    };

    return task;
}

std::vector<Task> JSONParser::loadTasksFromFile(const std::string& filename)
{
    std::string _filename{};
    if (filename.empty())
        _filename = JSONParser::jsonFilename;
    else
        _filename = _filename;

    std::ifstream file(_filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + _filename);
    }

    std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::vector<Task> tasks;

    size_t start = json.find("[");
    size_t end = json.find("]");
    if (start == std::string::npos || end == std::string::npos) {
        throw std::runtime_error("Invalid JSON array format.");
    }

    std::string tasksArray = json.substr(start + 1, end - start - 1);
    size_t pos = 0;
    while (pos < tasksArray.size()) {
        size_t taskStart = tasksArray.find("{", pos);
        size_t taskEnd = tasksArray.find("}", taskStart);
        if (taskStart == std::string::npos || taskEnd == std::string::npos) {
            break;
        }
        std::string taskJson = tasksArray.substr(taskStart, taskEnd - taskStart + 1);
        tasks.push_back(jsonToTask(taskJson)); // Convert to unique_ptr
        pos = taskEnd + 1;
    }

    return tasks;
}

bool JSONParser::jsonFileExists(const std::string& filename)
{
    std::string _filename{};
    if (filename.empty())
        _filename = JSONParser::jsonFilename;
    else
        _filename = _filename;

    std::ifstream file(_filename);

    if (file.fail()) {
        return false;
    }

    return true;
}

void JSONParser::deleteList(const std::string& filename)
{
    std::string _filename{};
    if (filename.empty())
        _filename = JSONParser::jsonFilename;
    else
        _filename = _filename;

    if (std::remove(_filename.c_str()) == 0) {
        std::cout << "List cleared successfully.\n";
    }
    else {
        std::perror("Error deleting the file.");
    }
}

