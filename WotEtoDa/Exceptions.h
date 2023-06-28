#pragma once

#include <exception>
#include <string>

class FileNotFoundException : public std::exception
{
public:
    FileNotFoundException(const std::string& fileName) : errorMessage_("File not found: " + fileName) 
    {}

    const char* what() const noexcept override
    {
        return errorMessage_.c_str();
    }

private:
    std::string errorMessage_;
};
