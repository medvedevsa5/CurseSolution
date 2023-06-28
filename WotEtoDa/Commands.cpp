#include <fstream>
#include <iomanip>
#include <sstream>

#include "Commands.h"
#include "Exceptions.h"
#include "StreamScanner.h"
#include "HuffmanTree.h"
#include "EncodingTable.h"
#include "DecodingTable.h"

std::string Encode::operator()(const std::string& fileName)
{
    std::ifstream fileToEncode(fileName, std::ios::binary);
    if (!fileToEncode)
    {
        throw FileNotFoundException(fileName);
    }

    StreamScanner scanner;
    std::vector<char> fileChars;
    scanner.scan(fileToEncode, fileChars);

    fileToEncode.close();

    HuffmanTree tree(scanner);
    EncodingTable table;
    tree.fillEncodingTable(table);

    std::vector<char> code;
    table.encode(fileChars, code, scanner);

    std::string outputFileName = fileName + ".out";
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile)
    {
        throw FileCreationException(fileName + ".out");
    }

    std::vector<char> serializedMap;
    table.serializeMap(serializedMap);

    char format[FORMAT_CODE_LENGTH + 1] = FORMAT_CODE;
    outputFile.write(reinterpret_cast<const char*>(&format), sizeof(format));

    // Размер файла до сжатия
    size_t fileSize = scanner.getFileSize();
    outputFile.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));

    std::vector<char> fileNameRaw(fileName.begin(), fileName.end());

    // Длина названия файла
    size_t fileNameSize = fileName.size();
    outputFile.write(reinterpret_cast<const char*>(&fileNameSize), sizeof(fileNameSize));

    // Название файла
    outputFile.write(fileName.data(), fileNameRaw.size() * sizeof(char));

    // Количество пар ключ-значение
    size_t mapKeyCount = table.getMapSize();
    outputFile.write(reinterpret_cast<const char*>(&mapKeyCount), sizeof(mapKeyCount));

    // Размер сериализованного словаря
    size_t vectorDataSize = serializedMap.size() * sizeof(char);
    outputFile.write(reinterpret_cast<const char*>(&vectorDataSize), sizeof(vectorDataSize));

    // Сериализованный словарь
    outputFile.write(serializedMap.data(), vectorDataSize);

    // Размер закодированного файла
    size_t codeSize = code.size() * sizeof(char);
    outputFile.write(reinterpret_cast<const char*>(&codeSize), sizeof(codeSize));

    // Код Хаффмана
    outputFile.write(code.data(), code.size()*sizeof(char));

    if (!outputFile)
    {
        throw FileWritingException(outputFileName);
    }

    return "File has been encoded succesfuly";
}

std::string Decode::operator()(const std::string& fileName)
{
	std::ifstream fileToDecode(fileName, std::ios::binary);
	if (!fileToDecode.is_open())
	{
		throw FileNotFoundException(fileName);
	}

    char format[FORMAT_CODE_LENGTH + 1]{};
    fileToDecode.read(reinterpret_cast<char*>(&format), sizeof(format));

    if (strcmp(format, FORMAT_CODE) != 0)
    {
        throw InvalidFormatException();
    }

    size_t fileSize = 0;
    fileToDecode.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));

    size_t fileNameSize = 0;
    fileToDecode.read(reinterpret_cast<char*>(&fileNameSize), sizeof(fileNameSize));

    std::vector<char> fileNameRaw(fileNameSize);
    fileToDecode.read(fileNameRaw.data(), fileNameSize);
    std::string outputFileName(fileNameRaw.begin(), fileNameRaw.end());

	size_t tableKeyCount = 0;
	fileToDecode.read(reinterpret_cast<char*>(&tableKeyCount), sizeof(tableKeyCount));

	size_t dataSize = 0;
	fileToDecode.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));

	DecodingTable table;
	table.deserialize(fileToDecode, tableKeyCount);

    size_t codeSize = 0;
    fileToDecode.read(reinterpret_cast<char*>(&codeSize), sizeof(codeSize));

    std::vector<char> code(codeSize);
    fileToDecode.read(code.data(), codeSize);

    if (!fileToDecode)
    {
        throw FileWritingException(fileName);
    }

    fileToDecode.close();

    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile)
    {
        throw FileCreationException(outputFileName);
    }

    std::vector<char> result;
    table.decode(code, result, fileSize);

    outputFile.write(result.data(), result.size() * sizeof(char));

    if (!fileToDecode)
    {
        throw FileWritingException(outputFileName);
    }

    return "File has been decoded successfuly";
}

std::string Analyze::operator()(const std::string& fileName)
{
    StreamScanner scanner;
    std::ifstream fstream(fileName, std::ios::binary);
    if (!fstream)
    {
        throw FileNotFoundException(fileName);
    }

    scanner.scan(fstream);
    
    HuffmanTree ht(scanner);

    EncodingTable table;

    ht.fillEncodingTable(table);

    double ratio = table.calculateCompressionRatio(scanner);

    std::string message = "Theoretical compression ratio is ";

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << ratio * 100;
    message += ss.str();

    return message;
}
