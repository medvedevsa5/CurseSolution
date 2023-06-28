#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <string>
#include <memory>
#include <bitset>
#include <stack>

#include "HuffmanTree.h"
#include "StreamScanner.h"
#include "Constants.h"

bool HuffmanTree::NodeComparator::operator()(Node* left, Node* right)
{
	return left->frequency > right->frequency;
}

void HuffmanTree::traverseTree(Node& root, EncodingTable& table)
{
	// «аменен рекурсивный обход дерева на итеративный
	// с использованием стека STL и pair
	std::stack<std::pair<Node*, std::vector<bool>>> stack;
	stack.push(std::make_pair(&root, std::vector<bool>()));

	while (!stack.empty())
	{
		Node* node = stack.top().first;
		std::vector<bool> code = stack.top().second;
		stack.pop();

		if (node->left == nullptr && node->right == nullptr)
		{
			table.insertCode(node->key, code);
		}

		if (node->left != nullptr)
		{
			std::vector<bool> leftCode = code;
			leftCode.push_back(false);
			stack.push(std::make_pair(node->left, leftCode));
		}

		if (node->right != nullptr)
		{
			std::vector<bool> rightCode = code;
			rightCode.push_back(true);
			stack.push(std::make_pair(node->right, rightCode));
		}
	}
}

void HuffmanTree::destroy(Node* node)
{
	std::stack<Node*> stack;
	if (root_)
	{
		stack.push(root_);
	}

	while (!stack.empty())
	{
		Node* node = stack.top();
		stack.pop();

		if (node->left)
		{
			stack.push(node->left);
		}

		if (node->right)
		{
			stack.push(node->right);
		}

		delete node;
	}
}

HuffmanTree::HuffmanTree(const StreamScanner& src)
{
	// —обственна€ п. очередь заменена на STL
	std::priority_queue <Node*, std::vector<Node*>, NodeComparator> queue;

	for (int i = 0; i < SYMBOL_SIZE; i++)
	{
		int probability = src.getProbability(i);
		if (probability != 0)
		{
			auto aux = new Node
			{
				nullptr,
				nullptr,
				(char)i,
				src.getProbability((char)i)
			};

			queue.push(aux);
		}
	}

	while (queue.size() != 1)
	{
		Node* left = queue.top();
		queue.pop();
		Node* right = queue.top();
		queue.pop();

		int priority = left->frequency + right->frequency;

		Node* newNode = new Node
		{
			left,
			right,
			'\0',
			priority
		};

		queue.push(newNode);
	}

	root_ = queue.top();
}

EncodingTable& HuffmanTree::fillEncodingTable(EncodingTable& table)
{
	traverseTree(*root_, table);
	return table;
}

HuffmanTree::~HuffmanTree() noexcept
{
	destroy(root_);
}


