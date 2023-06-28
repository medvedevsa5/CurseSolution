#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(void)
{
	//We build the tree depending on the string
	char bld[] = "abracadabra";
	htTree *codeTree = buildTree(bld);
	//We build the table depending on the Huffman tree
	hlTable *codeTable = buildTable(codeTree);

	char enc[] = "abracadabra";
	//We encode using the Huffman table
	encode(codeTable, enc);
	//We decode using the Huffman tree
	//We can decode string that only use symbols from the initial string
	char dec[] = "01011101101011000101110";
	decode(codeTree, dec);
	//Output : 0011 1110 1011 0001 0010 1010 1100 1111 1000 1001
	return 0;
}