#include "Utils.h"
#include <iostream>

void Utils::deleteList(const std::string& filename)
{
    if (filename.empty())
        return;

    if (std::remove(filename.c_str()) == 0) {
        std::cout << "List cleared successfully.\n";
    }
    else {
        std::perror("Error deleting the file.");
    }
    
}
