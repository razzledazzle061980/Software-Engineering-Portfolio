// ============================================================================
//    Author: Kenneth Perkins
//    Date:   Dec 5, 2020
//    Taken From: http://programmingnotes.org/
//    File:  Utils.h
//    Description: Handles general utility functions
// ============================================================================
#pragma once
#include <string>
#include <algorithm>
#include <cctype>

namespace Utils {
    /**
    * FUNCTION: getFilePath
    * USE: Returns the path from a given file path
    * @param path: The path of the file
    * @return: The path from the given file path
    */
    std::string getFilePath(const std::string& path) {
        auto pathEnd = path.find_last_of("/\\");
        auto pathName = pathEnd == std::string::npos ? path : path.substr(0, pathEnd);
        return pathName;
    }

    /**
    * FUNCTION: getFileName
    * USE: Returns the file name from a given file path
    * @param path: The path of the file
    * @return: The file name from the given file path
    */
    std::string getFileName(const std::string& path) {
        auto fileNameStart = path.find_last_of("/\\");
        auto fileName = fileNameStart == std::string::npos ? path : path.substr(fileNameStart + 1);
        return fileName;
    }

    /**
    * FUNCTION: getFileExtension
    * USE: Returns the file extension from a given file path
    * @param path: The path of the file
    * @return: The file extension from the given file path
    */
    std::string getFileExtension(const std::string& path) {
        auto fileName = getFileName(path);
        auto extStart = fileName.find_last_of('.');
        auto ext = extStart == std::string::npos ? "" : fileName.substr(extStart + 1);
        std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) {
            return static_cast<unsigned char>(std::tolower(c));
            });
        return ext;
    }
}// http://programmingnotes.org/