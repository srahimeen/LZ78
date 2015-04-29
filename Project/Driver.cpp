#include "LZ78.h"
#include <iostream>

int main()
{
	LZ78 test;
	test.compress("CompressorInput.txt", "CompressorOutput.txt");	
	test.decompress("CompressorOutput.txt", "DecompressorOutput.txt");
	return 0;
}
