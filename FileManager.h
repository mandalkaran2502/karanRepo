#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include <fstream>

/**
 * @brief FileManager class for handling file I/O operations
 * Handles persistence storage using filesystem
 */
class FileManager {
private:
    std::string dataDirectory;

public:
    /**
     * @brief Constructor
     */
    explicit FileManager(const std::string& dataDir = "data");

    /**
     * @brief Check if data directory exists, create if not
     */
    bool ensureDataDirectory();

    /**
     * @brief Write data to file
     */
    bool writeToFile(const std::string& filename, const std::string& data);

    /**
     * @brief Read data from file
     */
    std::string readFromFile(const std::string& filename);

    /**
     * @brief Check if file exists
     */
    bool fileExists(const std::string& filename) const;

    /**
     * @brief Get full file path
     */
    std::string getFilePath(const std::string& filename) const;

    /**
     * @brief Write lines to file
     */
    bool writeLinesToFile(const std::string& filename, const std::vector<std::string>& lines);

    /**
     * @brief Read lines from file
     */
    std::vector<std::string> readLinesFromFile(const std::string& filename);

    /**
     * @brief Delete file
     */
    bool deleteFile(const std::string& filename);

    /**
     * @brief Get data directory
     */
    std::string getDataDirectory() const { return dataDirectory; }
};

#endif // FILE_MANAGER_H
