#pragma once
#ifndef _HUFFMAN_TREE_
#define _HUFFMAN_TREE_

#include "StreamScanner.h"
#include "EncodingTable.h"


// ��� ������ ������������� � ����� ����������� ������, � �������
// ������ �� ������ �� ������������� ��������� �++, � �������
// �� ������� ������ ������������ direct member initialization.
// https://youtu.be/2jJumNzcp6Y 6:10-7:20
class HuffmanTree
{
private:
	struct Node
	{
		Node* left = nullptr;
		Node* right = nullptr;
		
		char key = '\0';
		int frequency = 0;
	};

	class NodeComparator
	{
	public:
		bool operator()(Node* left, Node* right);
	};

	Node* root_ = nullptr;

	void traverseTree(Node& root, EncodingTable& table);
	void destroy(Node* node);

public:
	HuffmanTree() noexcept = delete; // ����� ��� ����� ������?

	HuffmanTree(const StreamScanner& src);

	HuffmanTree(const HuffmanTree& src) = delete; // user-defined, �� �� user-provided
	HuffmanTree(HuffmanTree&& src) = delete;
	HuffmanTree operator=(const HuffmanTree& src) = delete;
	HuffmanTree operator=(HuffmanTree&& src) = delete;

	EncodingTable& fillEncodingTable(EncodingTable& table);

	~HuffmanTree() noexcept;
};


#endif // _HUFFMAN_TREE_