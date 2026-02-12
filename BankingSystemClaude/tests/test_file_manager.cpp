#include <gtest/gtest.h>
#include "FileManager.h"
#include <vector>

class FileManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        testDataDir = "test_data";
        fileManager = std::make_unique<FileManager>(testDataDir);
        fileManager->ensureDataDirectory();
    }

    void TearDown() override {
        // Clean up test files
        fileManager->deleteFile("test_file.txt");
        fileManager->deleteFile("test_lines.txt");
        fileManager->deleteFile("empty_file.txt");
    }

    std::string testDataDir;
    std::unique_ptr<FileManager> fileManager;
};

// Test data directory creation
TEST_F(FileManagerTest, EnsureDataDirectory) {
    EXPECT_TRUE(fileManager->ensureDataDirectory());
}

// Test write and read file
TEST_F(FileManagerTest, WriteAndReadFile) {
    std::string testData = "Hello, World!\nThis is a test.";
    EXPECT_TRUE(fileManager->writeToFile("test_file.txt", testData));
    
    std::string readData = fileManager->readFromFile("test_file.txt");
    EXPECT_EQ(readData, testData);
}

// Test file exists
TEST_F(FileManagerTest, FileExists) {
    std::string testData = "Test data";
    fileManager->writeToFile("test_file.txt", testData);
    
    EXPECT_TRUE(fileManager->fileExists("test_file.txt"));
    EXPECT_FALSE(fileManager->fileExists("nonexistent_file.txt"));
}

// Test write lines to file
TEST_F(FileManagerTest, WriteLinesToFile) {
    std::vector<std::string> lines = {
        "Line 1",
        "Line 2",
        "Line 3"
    };
    
    EXPECT_TRUE(fileManager->writeLinesToFile("test_lines.txt", lines));
    
    std::string content = fileManager->readFromFile("test_lines.txt");
    EXPECT_FALSE(content.empty());
}

// Test read lines from file
TEST_F(FileManagerTest, ReadLinesFromFile) {
    std::vector<std::string> lines = {
        "First line",
        "Second line",
        "Third line"
    };
    
    fileManager->writeLinesToFile("test_lines.txt", lines);
    std::vector<std::string> readLines = fileManager->readLinesFromFile("test_lines.txt");
    
    EXPECT_EQ(readLines.size(), lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
        EXPECT_EQ(readLines[i], lines[i]);
    }
}

// Test empty file
TEST_F(FileManagerTest, EmptyFile) {
    EXPECT_TRUE(fileManager->writeToFile("empty_file.txt", ""));
    std::string content = fileManager->readFromFile("empty_file.txt");
    EXPECT_EQ(content, "");
}

// Test read non-existent file
TEST_F(FileManagerTest, ReadNonExistentFile) {
    std::string content = fileManager->readFromFile("nonexistent.txt");
    EXPECT_EQ(content, "");
}

// Test get file path
TEST_F(FileManagerTest, GetFilePath) {
    std::string filepath = fileManager->getFilePath("test.txt");
    EXPECT_NE(filepath.find(testDataDir), std::string::npos);
    EXPECT_NE(filepath.find("test.txt"), std::string::npos);
}

// Test delete file
TEST_F(FileManagerTest, DeleteFile) {
    fileManager->writeToFile("temp_file.txt", "Temporary data");
    EXPECT_TRUE(fileManager->fileExists("temp_file.txt"));
    
    EXPECT_TRUE(fileManager->deleteFile("temp_file.txt"));
    EXPECT_FALSE(fileManager->fileExists("temp_file.txt"));
}

// Test delete non-existent file
TEST_F(FileManagerTest, DeleteNonExistentFile) {
    EXPECT_FALSE(fileManager->deleteFile("nonexistent.txt"));
}

// Test large file
TEST_F(FileManagerTest, LargeFile) {
    std::string largeData;
    for (int i = 0; i < 10000; ++i) {
        largeData += "This is line " + std::to_string(i) + "\n";
    }
    
    EXPECT_TRUE(fileManager->writeToFile("large_file.txt", largeData));
    std::string readData = fileManager->readFromFile("large_file.txt");
    EXPECT_EQ(readData, largeData);
    
    fileManager->deleteFile("large_file.txt");
}

// Test special characters in file
TEST_F(FileManagerTest, SpecialCharacters) {
    std::string specialData = "Special chars: !@#$%^&*()_+-=[]{}|;':\",./<>?`~\n";
    specialData += "Unicode: ₹ € £ ¥ © ® ™\n";
    specialData += "Newlines and tabs:\n\tTabbed line\n";
    
    EXPECT_TRUE(fileManager->writeToFile("special_file.txt", specialData));
    std::string readData = fileManager->readFromFile("special_file.txt");
    EXPECT_EQ(readData, specialData);
    
    fileManager->deleteFile("special_file.txt");
}

// Test overwrite existing file
TEST_F(FileManagerTest, OverwriteFile) {
    fileManager->writeToFile("overwrite_test.txt", "Original content");
    fileManager->writeToFile("overwrite_test.txt", "New content");
    
    std::string content = fileManager->readFromFile("overwrite_test.txt");
    EXPECT_EQ(content, "New content");
    
    fileManager->deleteFile("overwrite_test.txt");
}

// Test multiple sequential writes
TEST_F(FileManagerTest, MultipleWrites) {
    for (int i = 0; i < 5; ++i) {
        std::string filename = "multi_" + std::to_string(i) + ".txt";
        std::string content = "Content " + std::to_string(i);
        EXPECT_TRUE(fileManager->writeToFile(filename, content));
    }
    
    for (int i = 0; i < 5; ++i) {
        std::string filename = "multi_" + std::to_string(i) + ".txt";
        std::string content = fileManager->readFromFile(filename);
        EXPECT_EQ(content, "Content " + std::to_string(i));
        fileManager->deleteFile(filename);
    }
}

// Test get data directory
TEST_F(FileManagerTest, GetDataDirectory) {
    EXPECT_EQ(fileManager->getDataDirectory(), testDataDir);
}
