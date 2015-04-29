#ifndef LZ78_H
#define LZ78_H

#include <string>
#include <map>
#include <vector>
#include <bitset>
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/*	
	LZ78 compression program created using the algorithm outlined in the following link:
	http://oldwww.rasip.fer.hr/research/compress/algorithms/fund/lz/lz78.html

	By:
	Muhaimen Shamsi
	Emily Pretorius
	Soufin Rahimeen
	Nick Olson
*/


class LZ78
{
public:
	// Compresses the charstream using the LZ78 compression algorithm
	void compress(const string fileToCompress, const string outputFileName);
	void decompress(const string fileToDecompress, const string outputFileName);

private:
	//Conversions between decimal, binary and ASCII
	string decToBin(const int& input) const;
	int binToDec(const char& input) const;
	string stringToASCII(const string& input) const;
	char ASCIIToChar(const string& input) const;

	//Read a file and store in a string: for getting the input file to compress
	string fileRead(const string filename);

	// Write a string to a file: for writing a decompressed string to a file
	void fileWrite(const string  filename, const string input);

	// Write a binary String to a file: for writing a compressed binary string to a file
	void fileWriteBin(const string filename, const string input);
};

#endif