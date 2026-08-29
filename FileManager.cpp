#include "FileManager.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <sstream>

FileManager::FileManager(const std::string& dataDir) : dataDirectory(dataDir) {}

bool FileManager::ensureDataDirectory() 
{
    struct stat info;
    
    if (stat(dataDirectory.c_str(), &info) != 0) 
    {
        // Directory doesn't exist, create it
        #ifdef _WIN32
            if (mkdir(dataDirectory.c_str()) != 0) {
        #else
            if (mkdir(dataDirectory.c_str(), 0755) != 0) {
        #endif
            return false;
        }
    } 
    else if (!(info.st_mode & S_IFDIR)) 
    {
        // Path exists but is not a directory
        return false;
    }
    
    return true;
}

std::string FileManager::getFilePath(const std::string& filename) const 
{
    return dataDirectory + "/" + filename;
}

bool FileManager::writeToFile(const std::string& filename, const std::string& data) 
{
    std::string filepath = getFilePath(filename);
    std::ofstream file(filepath, std::ios::out | std::ios::trunc);
    
    if (!file.is_open()) 
    {
        return false;
    }
    
    file << data;
    file.close();
    
    return file.good();
}

std::string FileManager::readFromFile(const std::string& filename) 
{
    std::string filepath = getFilePath(filename);
    std::ifstream file(filepath, std::ios::in);
    
    if (!file.is_open()) 
    {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    return buffer.str();
}

bool FileManager::fileExists(const std::string& filename) const 
{
    std::string filepath = getFilePath(filename);
    struct stat info;
    return stat(filepath.c_str(), &info) == 0;
}

bool FileManager::writeLinesToFile(const std::string& filename, const std::vector<std::string>& lines) 
{
    std::string filepath = getFilePath(filename);
    std::ofstream file(filepath, std::ios::out | std::ios::trunc);
    
    if (!file.is_open()) 
    {
        return false;
    }
    
    for (const auto& line : lines) 
    {
        file << line << "\n";
    }
    
    file.close();
    return file.good();
}

std::vector<std::string> FileManager::readLinesFromFile(const std::string& filename) 
{
    std::vector<std::string> lines;
    std::string filepath = getFilePath(filename);
    std::ifstream file(filepath, std::ios::in);
    
    if (!file.is_open()) 
    {
        return lines;
    }
    
    std::string line;
    while (std::getline(file, line)) 
    {
        lines.push_back(line);
    }
    
    file.close();
    return lines;
}

bool FileManager::deleteFile(const std::string& filename) 
{
    std::string filepath = getFilePath(filename);
    return std::remove(filepath.c_str()) == 0;
}
