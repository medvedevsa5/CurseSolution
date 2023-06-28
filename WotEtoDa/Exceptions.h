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

class FileCreationException : public std::exception
{
public:
    FileCreationException(const std::string& fileName) : errorMessage_("File can't be open/created: " + fileName)
    {}

    const char* what() const noexcept override
    {
        return errorMessage_.c_str();
    }

private:
    std::string errorMessage_;
};

class FileWritingException : public std::exception
{
public:
    FileWritingException(const std::string& fileName) : errorMessage_("Cannot write to the file. " + fileName)
    { }

    const char* what() const noexcept override
    {
        return errorMessage_.c_str();
    }

private:
    std::string errorMessage_;
};

class CommandNotFoundException : public std::exception
{
public:
    CommandNotFoundException() : errorMessage_("Command not found.")
    {
    }

    const char* what() const noexcept override
    {
        return errorMessage_.c_str();
    }

private:
    std::string errorMessage_;
};

class InvalidFormatException : public std::exception
{
public:
    InvalidFormatException() : errorMessage_("Format of the compressed file is invalid.")
    {
    }

    const char* what() const noexcept override
    {
        return errorMessage_.c_str();
    }

private:
    std::string errorMessage_;
};

class ReadingCommandStreamException : public std::exception
{
public:
    ReadingCommandStreamException() : errorMessage_("Something happend to the input stream.")
    { }

    const char* what() const noexcept override
    {
        return errorMessage_.c_str();
    }

private:
    std::string errorMessage_;
};

class BadTableException : public std::exception
{
    public:
        BadTableException() : errorMessage_("Huffman table is unusable.")
        { }

        const char* what() const noexcept override
        {
            return errorMessage_.c_str();
        }

private:
    std::string errorMessage_;
};