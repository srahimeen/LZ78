#include "LZ78.h"

void LZ78::compress(const string fileToCompress, const string outputFileName)
{
	// Compression Variables
	map<string, int> dictionary;
	string charstream;			// the sequence to be compressed
	string codestream; 			// the compressed output
	string character;			// the character of the charstream under examination by the algorithm
	string prefix; 				// the sequence of characters being compared to entries in the dictionary
	
	charstream = fileRead(fileToCompress);
	
	for(size_t x = 0; x < charstream.length() ; ++x)
	{
		character = charstream.substr(x,1);

		if(dictionary.count(prefix+character))
			prefix += character;
		else
		{
			if (prefix.empty())
				codestream += "00000000";
			else
				codestream += decToBin(dictionary[prefix]);

			codestream += stringToASCII(character);

			dictionary[prefix+character] = dictionary.size() + 1;

			prefix.clear();
		}
	}
	cout << "Compression Ratio: " << (double)codestream.length() / (charstream.length() * 8) << endl;
	fileWriteBin(outputFileName,codestream);
}

void LZ78::decompress(const string fileToDecompress, const string outputFileName)
{
	// Decompression Variables
	map<int, string> dictionary;
	string charstream;			// the the decomressed string
	string codestream; 			// the compressed input
	string character;			// the character immediately after the current codeword
	int codeword; 			    // the current dictionary entry being processed

	codestream = fileRead(fileToDecompress);

	for (size_t x = 0; x < codestream.length(); ++++x)
	{
		codeword = binToDec(codestream[x]);
		character = codestream.substr(x + 1, 1);

		if (codeword != 0)
			charstream += dictionary[codeword];
		charstream += character;

		if (codeword != 0)
			dictionary[dictionary.size() + 1] = dictionary[codeword] + character;
		else
			dictionary[dictionary.size() + 1] = character;
	}
	fileWrite(outputFileName, charstream);
}

string LZ78::decToBin(const int& input) const
{
	return bitset<8>(input).to_string();
}

int LZ78::binToDec(const char& input) const
{
	bitset<8> dec(input);
	return dec.to_ulong();
}

string LZ78::stringToASCII(const string& input) const
{
	return bitset<8>(input[0]).to_string();
}

char LZ78::ASCIIToChar(const string& input) const
{
	return (char)bitset<8>(input).to_ulong();
}

string LZ78::fileRead(const string filename)
{
	ifstream t(filename);
	stringstream buffer;
	buffer << t.rdbuf();

	string input = buffer.str();
	return input;
}

void LZ78::fileWrite(const string filename, const string input)
{
	ofstream out(filename);
	out << input;
	out.close();
}

void LZ78::fileWriteBin(const string filename, const string input)
{
	string eightBits;
	long temp;
	char output;
	ofstream out(filename);

	for (int x = 0; x < input.length(); x += 8)
	{
		eightBits = input.substr(x, 8);
		temp = strtol(eightBits.c_str(),0, 2);
		output = temp & 0xffl;
		out << output;
	}
		
	out.close();
}