#include <fstream>

#include "Commands.h"
#include "Exceptions.h"
#include "StreamScanner.h"
#include "HuffmanTree.h"
#include "EncodingTable.h"
#include "DecodingTable.h"

#include <iostream> // DELETE

// 
void Encode::operator()(const std::string& fileName)
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

    std::ofstream outputFile(fileName + ".out", std::ios::binary);
    if (!outputFile)
    {
        //throw FileCreationException(fileName + ".out");
    }

    std::vector<char> serializedMap;
    table.serializeMap(serializedMap);

    // Размер файла до сжатия
    size_t fileSize = scanner.getFileSize();
    outputFile.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));

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

    outputFile.close();
}

void Decode::operator()(const std::string& fileName)
{
	std::ifstream fileToDecode(fileName, std::ios::binary);
	if (!fileToDecode.is_open())
	{
		throw FileNotFoundException(fileName);
	}

    size_t fileSize = 0;
    fileToDecode.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));

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

    fileToDecode.close();

    std::ofstream outputFile(fileName + ".out", std::ios::binary);
    if (!outputFile)
    {
        //throw FileCreationException(fileName + ".out");
    }

    std::vector<char> result;
    table.decode(code, result, fileSize);

    outputFile.write(result.data(), result.size() * sizeof(char));

    outputFile.close();
}

void Analyze::operator()(const std::string& fileName)
{
}
